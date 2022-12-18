#include "Directx9Render.hpp"

using namespace CORE::DX9;

// called on init and reset
void C_DX9Render::bindDevice(IDirect3DDevice9* device) {

	// call once!
	if (m_bInit || device == NULL) {
		return;
	}

	m_bInit = true;
	m_pDevice = device;

	// get viewport and set screen size
	m_pDevice->GetViewport(&m_cViewport);
	m_cScreenSize = { static_cast<long>(m_cViewport.Width), static_cast<long>(m_cViewport.Height) };

	m_cOldState.create(m_pDevice, false);
	m_cNewState.create(m_pDevice, true);

	m_cMainBuffer.create(m_pDevice, MAX_VERTICES);

	// init all fonts
	for (auto& font : m_mFonts) {
		font.second.bind(m_pDevice);
	}
}

void C_DX9Render::invalidateDevice() {

	if (!m_bInit) {
		return;
	}

	m_pDevice = NULL;
	m_bInit = false;

	m_aDrawBatchs.clear();

	for (auto& font : m_mFonts) {
		// only do the texture, no need to recalc bitmap 
		font.second.m_cFontTexture.release();
	}

	release();
}

void C_DX9Render::release() {
	m_cMainBuffer.release();
	m_cOldState.release();
	m_cNewState.release();
}

void C_DX9Render::startDraw() {

	// make sure we have at least 1 batch to draw into
	m_aDrawBatchs.emplace_back();
}

void C_DX9Render::finishDraw() {

	// bind our draw data
	m_cNewState.apply();
	m_cMainBuffer.apply();

	for (const auto& batch : m_aDrawBatchs) {

		if (batch.m_iVertexCount <= 0) {
			continue;
		}

		// bind our draw data to our vertex buffer, write the whole array fuck it
		m_cMainBuffer.bindData(batch.m_aVertices.data(), MAX_VERTICES);

		size_t vertexOffset = 0;

		for (const auto& primitive : batch.m_aPrimitives) {

			m_pDevice->SetTexture(0, primitive.m_pTexture);
			m_pDevice->DrawPrimitive(primitive.m_iType, vertexOffset, primitive.m_iCount);

			vertexOffset += primitive.m_iSize;
		}
	}

	// restore old state
	m_aDrawBatchs.clear();
	m_cOldState.apply();
}

void C_DX9Render::addToBatch(const std::vector<T_Vertex>& data, D3DPRIMITIVETYPE type, size_t primitiveCount, IDirect3DTexture9* tex) {

	if (data.size() > MAX_VERTICES) {
		throw std::exception("number of vertices exceeded max vertex count");
	}

	// new lot to accomodate us
	if (data.size() + m_aDrawBatchs.back().m_iVertexCount > MAX_VERTICES) {
		m_aDrawBatchs.emplace_back();
	}

	auto& curBatch = m_aDrawBatchs.back();

	if (curBatch.m_aPrimitives.empty() || curBatch.m_aPrimitives.back().m_iType != type || curBatch.m_aPrimitives.back().m_pTexture != tex) {
		curBatch.m_aPrimitives.emplace_back(type, tex);
	}

	// copy our data into drawBatch
	curBatch.m_aPrimitives.back().m_iCount += primitiveCount;
	curBatch.m_aPrimitives.back().m_iSize += data.size();

	std::memcpy(&curBatch.m_aVertices[curBatch.m_iVertexCount], data.data(), data.size() * sizeof(T_Vertex));
	curBatch.m_iVertexCount += data.size();
}

void C_DX9Render::breakBatch() {
	m_aDrawBatchs.back().m_aPrimitives.emplace_back(D3DPT_FORCE_DWORD, static_cast<IDirect3DTexture9*>(NULL));
}

void C_DX9Render::addFont(hash_t font, const std::string family, size_t height, size_t weight) {

	if (m_mFonts.count(font) != 0) {
		return;
	}

	// add!!!
	m_mFonts.insert({ font, std::move(T_Font(family, height, weight)) });

	if (m_bInit && m_pDevice) {
		// already initalized so we want to do it manually
		m_mFonts.at(font).bind(m_pDevice);
	}
}

POINT& C_DX9Render::getScreenSize() {
	return m_cScreenSize;
}

void C_DX9Render::drawString(float x, float y, hash_t font, DWORD col, const std::string& text, uint8_t flags) {

	if (flags & OUTLINE) {
		drawStringOutline(x, y, font, col, 0xFF000000, text, flags);
		return;
	}

	auto& myFont = m_mFonts.at(font);
	const auto spacing = myFont.m_cFontBitmap.getSpacing();

	float posX = x + 0.5f;
	float posY = y + 0.5f;

	if (flags & CENTER_Y) {
		posY -= (myFont.m_cFontBitmap.getStringHeight() * 0.5f) + 1.f;
	}

	if (flags & CENTER_X) {
		posX -= (myFont.m_cFontBitmap.getStringWidth(text) * 0.5f);
	}

	if (flags & ALIGN_R) {
		posX -= myFont.m_cFontBitmap.getStringWidth(text);
	}

	posX -= spacing;

	for (const auto& c : text) {

		const auto& curMetrics = myFont.m_cFontBitmap.getTextCoords(c - 32);

		if (c != ' ') {

			const std::vector<T_Vertex> vertices = {
				{posX,					posY,					col, curMetrics.x1, curMetrics.y1},
				{posX + curMetrics.w,	posY,					col, curMetrics.x2, curMetrics.y1},
				{posX + curMetrics.w,	posY + curMetrics.h,	col, curMetrics.x2, curMetrics.y2},

				{posX + curMetrics.w,	posY + curMetrics.h,	col, curMetrics.x2, curMetrics.y2},
				{posX,					posY + curMetrics.h,	col, curMetrics.x1, curMetrics.y2},
				{posX,					posY,					col, curMetrics.x1, curMetrics.y1},
			};

			addToBatch(vertices, D3DPT_TRIANGLELIST, 2, myFont.m_cFontTexture.getTexture());
		}

		// mmmm premium text spacing!!
		posX += curMetrics.w - 2.f * spacing;
	}
}

void C_DX9Render::drawStringOutline(float x, float y, hash_t font, DWORD col, DWORD colOutline, const std::string& text, uint8_t flags) {

	auto& myFont = m_mFonts.at(font);
	const auto spacing = myFont.m_cFontBitmap.getSpacing();

	float posX = x + 0.5f;
	float posY = y + 0.5f;

	if (flags & CENTER_Y) {
		posY -= (myFont.m_cFontBitmap.getStringHeight() * 0.5f) + 1.f;
	}

	if (flags & CENTER_X) {
		posX -= (myFont.m_cFontBitmap.getStringWidth(text) * 0.5f);
	}

	if (flags & ALIGN_R) {
		posX -= myFont.m_cFontBitmap.getStringWidth(text);
	}

	posX -= spacing;

	for (const auto& c : text) {

		const auto& curMetrics = myFont.m_cFontBitmap.getTextCoords(c - 32);

		if (c != ' ') {

			// big fucking oof
			const std::vector<T_Vertex> vertices = {
				{posX - 1.f,				posY,					colOutline, curMetrics.x1, curMetrics.y1},
				{posX + curMetrics.w - 1.f,	posY,					colOutline, curMetrics.x2, curMetrics.y1},
				{posX + curMetrics.w - 1.f,	posY + curMetrics.h,	colOutline, curMetrics.x2, curMetrics.y2},


				{posX + curMetrics.w - 1.f,	posY + curMetrics.h,	colOutline, curMetrics.x2, curMetrics.y2},
				{posX - 1.f,				posY + curMetrics.h,	colOutline, curMetrics.x1, curMetrics.y2},
				{posX - 1.f,				posY,					colOutline, curMetrics.x1, curMetrics.y1},

				{posX + 1.f,				posY,					colOutline, curMetrics.x1, curMetrics.y1},
				{posX + curMetrics.w + 1.f,	posY,					colOutline, curMetrics.x2, curMetrics.y1},
				{posX + curMetrics.w + 1.f,	posY + curMetrics.h,	colOutline, curMetrics.x2, curMetrics.y2},


				{posX + curMetrics.w + 1.f,	posY + curMetrics.h,	colOutline, curMetrics.x2, curMetrics.y2},
				{posX + 1.f,				posY + curMetrics.h,	colOutline, curMetrics.x1, curMetrics.y2},
				{posX + 1.f,				posY,					colOutline, curMetrics.x1, curMetrics.y1},

				{posX,					posY + 1.f,					colOutline, curMetrics.x1, curMetrics.y1},
				{posX + curMetrics.w,	posY + 1.f,					colOutline, curMetrics.x2, curMetrics.y1},
				{posX + curMetrics.w,	posY + curMetrics.h + 1.f,	colOutline, curMetrics.x2, curMetrics.y2},

				{posX + curMetrics.w,	posY + curMetrics.h + 1.f,	colOutline, curMetrics.x2, curMetrics.y2},
				{posX,					posY + curMetrics.h + 1.f,	colOutline, curMetrics.x1, curMetrics.y2},
				{posX,					posY + 1.f,					colOutline, curMetrics.x1, curMetrics.y1},

				{posX,					posY - 1.f,					colOutline, curMetrics.x1, curMetrics.y1},
				{posX + curMetrics.w,	posY - 1.f,					colOutline, curMetrics.x2, curMetrics.y1},
				{posX + curMetrics.w,	posY + curMetrics.h - 1.f,	colOutline, curMetrics.x2, curMetrics.y2},

				{posX + curMetrics.w,	posY + curMetrics.h - 1.f,	colOutline, curMetrics.x2, curMetrics.y2},
				{posX,					posY + curMetrics.h - 1.f,	colOutline, curMetrics.x1, curMetrics.y2},
				{posX,					posY - 1.f,					colOutline, curMetrics.x1, curMetrics.y1},


				{posX,					posY,					col, curMetrics.x1, curMetrics.y1},
				{posX + curMetrics.w,	posY,					col, curMetrics.x2, curMetrics.y1},
				{posX + curMetrics.w,	posY + curMetrics.h,	col, curMetrics.x2, curMetrics.y2},

				{posX + curMetrics.w,	posY + curMetrics.h,	col, curMetrics.x2, curMetrics.y2},
				{posX,					posY + curMetrics.h,	col, curMetrics.x1, curMetrics.y2},
				{posX,					posY,					col, curMetrics.x1, curMetrics.y1},
			};

			addToBatch(vertices, D3DPT_TRIANGLELIST, 2 * 5, myFont.m_cFontTexture.getTexture());
		}

		// mmmm premium text spacing!!
		posX += curMetrics.w - 2.f * spacing;
	}
}

void C_DX9Render::drawRect(float x, float y, float w, float h, DWORD col) {

	const std::vector<T_Vertex> vertices = {
		{x,		y,		col, 0.f, 0.f},
		{x + w, y,		col, 0.f, 0.f},

		{x + w, y,		col, 0.f, 0.f},
		{x + w,	y + h,	col, 0.f, 0.f},

		{x + w,	y + h,	col, 0.f, 0.f},
		{x,		y + h,	col, 0.f, 0.f},

		{x,		y + h,	col, 0.f, 0.f},
		{x,		y,		col, 0.f, 0.f},
	};

	addToBatch(vertices, D3DPT_LINELIST, 4, NULL);
}

void C_DX9Render::drawRectFill(float x, float y, float w, float h, DWORD col) {

	const std::vector<T_Vertex> vertices = {
		{x,		y,		col, 0.f, 0.f},
		{x + w, y,		col, 0.f, 0.f},
		{x + w,	y + h,	col, 0.f, 0.f},

		{x + w,	y + h,	col, 0.f, 0.f},
		{x,		y + h,	col, 0.f, 0.f},
		{x,		y,		col, 0.f, 0.f},
	};

	addToBatch(vertices, D3DPT_TRIANGLELIST, 2, NULL);
}

void C_DX9Render::drawRectFillGradientH(float x, float y, float w, float h, DWORD colL, DWORD colR) {

	const std::vector<T_Vertex> vertices = {
		{x,		y,		colL, 0.f, 0.f},
		{x + w, y,		colR, 0.f, 0.f},
		{x + w,	y + h,	colR, 0.f, 0.f},

		{x + w,	y + h,	colR, 0.f, 0.f},
		{x,		y + h,	colL, 0.f, 0.f},
		{x,		y,		colL, 0.f, 0.f},
	};

	addToBatch(vertices, D3DPT_TRIANGLELIST, 2, NULL);
}

void C_DX9Render::drawRectFillGradientV(float x, float y, float w, float h, DWORD colT, DWORD colB) {

	const std::vector<T_Vertex> vertices = {
		{x,		y,		colT, 0.f, 0.f},
		{x + w, y,		colT, 0.f, 0.f},
		{x + w,	y + h,	colB, 0.f, 0.f},

		{x + w,	y + h,	colB, 0.f, 0.f},
		{x,		y + h,	colB, 0.f, 0.f},
		{x,		y,		colT, 0.f, 0.f},
	};

	addToBatch(vertices, D3DPT_TRIANGLELIST, 2, NULL);
}

void C_DX9Render::drawCircle(float x, float y, float r, DWORD col) {

	std::vector<T_Vertex> vertices;

	for (size_t i = 0; i <= CIRCLE_SEGMENTS; i++) {
		const auto& lookup = m_aCircleLookup.at(i);
		vertices.emplace_back(x + r * lookup.cos, y + r * lookup.sin, col, 0.f, 0.f);
	}

	addToBatch(vertices, D3DPT_LINESTRIP, CIRCLE_SEGMENTS, NULL);
	breakBatch();
}

void C_DX9Render::drawCircleFill(float x, float y, float r, DWORD col) {

	std::vector<T_Vertex> vertices;
	vertices.emplace_back(x, y, col, 0.f, 0.f);

	for (size_t i = 0; i <= CIRCLE_SEGMENTS; i++) {
		const auto& lookup = m_aCircleLookup.at(i);
		vertices.emplace_back(x + r * lookup.cos, y + r * lookup.sin, col, 0.f, 0.f);
	}

	addToBatch(vertices, D3DPT_TRIANGLEFAN, CIRCLE_SEGMENTS, NULL);
	breakBatch();
}

void C_DX9Render::drawCircleFillGradient(float x, float y, float r, DWORD colO, DWORD colI) {

	std::vector<T_Vertex> vertices;
	vertices.emplace_back(x, y, colI, 0.f, 0.f);

	for (size_t i = 0; i <= CIRCLE_SEGMENTS; i++) {
		const auto& lookup = m_aCircleLookup.at(i);
		vertices.emplace_back(x + r * lookup.cos, y + r * lookup.sin, colO, 0.f, 0.f);
	}

	addToBatch(vertices, D3DPT_TRIANGLEFAN, CIRCLE_SEGMENTS, NULL);
	breakBatch();
}