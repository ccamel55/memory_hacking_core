#include "Directx9Render.hpp"

#include <cmath>

using namespace CORE::DX9;

// called on init and reset
void C_DX9Render::bindDevice(IDirect3DDevice9* device) {

	// call once!
	if (_init || device == NULL) {
		return;
	}

	_init = true;
	_device = device;

	// get viewport and set screen size
	_device->GetViewport(&_viewport);
	_screenSize = { static_cast<long>(_viewport.Width), static_cast<long>(_viewport.Height) };

	_mainBuffer.create(_device, MAX_VERTICES);

	_newState.create(_device, true);
	_oldState.create(_device, false);

	// init all fonts
	for (auto& font : _fonts) {
		font.second.bind(_device);
	}
}

void C_DX9Render::invalidateDevice() {

	if (!_init) {
		return;
	}

	_device = NULL;
	_init = false;

	_drawBatchs.clear();

	for (auto& font : _fonts) {
		// only do the texture, no need to recalc bitmap 
		font.second.m_cFontTexture.release();
	}

	release();
}

void C_DX9Render::release() {

	_mainBuffer.release();
	_oldState.release();
	_newState.release();
}

void C_DX9Render::startDraw() {

	// make sure we have at least 1 batch to draw into
	_drawBatchs.emplace_back();
}

void C_DX9Render::finishDraw() {

	// bind our draw data
	_newState.apply();
	_mainBuffer.apply();

	for (const auto& batch : _drawBatchs) {

		if (batch.m_iVertexCount <= 0) {
			continue;
		}

		// bind our draw data to our vertex buffer, write the whole array fuck it
		_mainBuffer.bindData(batch.m_aVertices.data(), MAX_VERTICES);

		size_t vertexOffset = 0;

		for (const auto& primitive : batch.m_aPrimitives) {

			_device->SetTexture(0, primitive.m_pTexture);
			_device->DrawPrimitive(primitive.m_iType, vertexOffset, primitive.m_iCount);

			vertexOffset += primitive.m_iSize;
		}
	}

	// restore old state
	_drawBatchs.clear();
	_oldState.apply();
}

void C_DX9Render::addToBatch(const std::vector<T_Vertex>& data, D3DPRIMITIVETYPE type, size_t primitiveCount, IDirect3DTexture9* tex) {

	if (data.size() > MAX_VERTICES) {
		throw std::exception("number of vertices exceeded max vertex count");
	}

	// new lot to accomodate us
	if (data.size() + _drawBatchs.back().m_iVertexCount > MAX_VERTICES) {
		_drawBatchs.emplace_back();
	}

	auto& curBatch = _drawBatchs.back();

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
	_drawBatchs.back().m_aPrimitives.emplace_back(D3DPT_FORCE_DWORD, static_cast<IDirect3DTexture9*>(NULL));
}

void C_DX9Render::addFont(hash_t font, const std::string& family, size_t height, size_t weight) {

	if (_fonts.count(font) != 0) {
		return;
	}

	// add!!!
	_fonts.insert({ font, std::move(T_Font(family, height, weight)) });

	if (_init && _device) {
		// already initalized so we want to do it manually
		_fonts.at(font).bind(_device);
	}
}

POINT& C_DX9Render::getScreenSize() {
	return _screenSize;
}

size_t C_DX9Render::getStringWidth(hash_t font, const std::string& text) {
	return _fonts.at(font).m_cFontBitmap.getStringWidth(text);
}

size_t C_DX9Render::getStringHeight(hash_t font) {
	return _fonts.at(font).m_cFontBitmap.getStringHeight();
}

void C_DX9Render::drawString(float x, float y, hash_t font, DWORD col, const std::string& text, uint8_t flags) {

	if (flags & E_FONT_FLAGS::FONT_OUTLINE) {
		drawStringOutline(x, y, font, col, 0xFF000000, text, flags);
		return;
	}

	auto& myFont = _fonts.at(font);
	const auto spacing = myFont.m_cFontBitmap.getSpacing();

	float posX = x + 0.5f;
	float posY = y + 0.5f;

	if (flags & E_FONT_FLAGS::FONT_CENTER_Y) {
		posY -= round(myFont.m_cFontBitmap.getStringHeight() * 0.5f) + 1.f;
	}

	if (flags & E_FONT_FLAGS::FONT_CENTER_X) {
		posX -= round(myFont.m_cFontBitmap.getStringWidth(text) * 0.5f);
	}

	if (flags & E_FONT_FLAGS::FONT_ALIGN_R) {
		posX -= myFont.m_cFontBitmap.getStringWidth(text);
	}

	posX -= spacing;

	for (const auto& c : text) {

		const auto& curMetrics = myFont.m_cFontBitmap.getTextCoords(c - 32);

		if (c != ' ') {

			const std::vector<T_Vertex> vertices = {
				{posX,					posY,					col, curMetrics._x1, curMetrics._y1},
				{posX + curMetrics._w,	posY,					col, curMetrics._x2, curMetrics._y1},
				{posX + curMetrics._w,	posY + curMetrics._h,	col, curMetrics._x2, curMetrics._y2},

				{posX + curMetrics._w,	posY + curMetrics._h,	col, curMetrics._x2, curMetrics._y2},
				{posX,					posY + curMetrics._h,	col, curMetrics._x1, curMetrics._y2},
				{posX,					posY,					col, curMetrics._x1, curMetrics._y1},
			};

			addToBatch(vertices, D3DPT_TRIANGLELIST, 2, myFont.m_cFontTexture.getTexture());
		}

		// mmmm premium text spacing!!
		posX += curMetrics._w - 2.f * spacing;
	}
}

void C_DX9Render::drawStringOutline(float x, float y, hash_t font, DWORD col, DWORD colOutline, const std::string& text, uint8_t flags) {

	auto& myFont = _fonts.at(font);
	const auto spacing = myFont.m_cFontBitmap.getSpacing();

	float posX = x + 0.5f;
	float posY = y + 0.5f;

	if (flags & E_FONT_FLAGS::FONT_CENTER_Y) {
		posY -= (myFont.m_cFontBitmap.getStringHeight() * 0.5f) + 1.f;
	}

	if (flags & E_FONT_FLAGS::FONT_CENTER_X) {
		posX -= (myFont.m_cFontBitmap.getStringWidth(text) * 0.5f);
	}

	if (flags & E_FONT_FLAGS::FONT_ALIGN_R) {
		posX -= myFont.m_cFontBitmap.getStringWidth(text);
	}

	posX -= spacing;

	for (const auto& c : text) {

		const auto& curMetrics = myFont.m_cFontBitmap.getTextCoords(c - 32);

		if (c != ' ') {

			// big fucking oof
			const std::vector<T_Vertex> vertices = {
				{posX - 1.f,				posY,						colOutline, curMetrics._x1, curMetrics._y1},
				{posX + curMetrics._w - 1.f,posY,						colOutline, curMetrics._x2, curMetrics._y1},
				{posX + curMetrics._w - 1.f,posY + curMetrics._h,		colOutline, curMetrics._x2, curMetrics._y2},


				{posX + curMetrics._w - 1.f,posY + curMetrics._h,		colOutline, curMetrics._x2, curMetrics._y2},
				{posX - 1.f,				posY + curMetrics._h,		colOutline, curMetrics._x1, curMetrics._y2},
				{posX - 1.f,				posY,						colOutline, curMetrics._x1, curMetrics._y1},

				{posX + 1.f,				posY,						colOutline, curMetrics._x1, curMetrics._y1},
				{posX + curMetrics._w + 1.f,posY,						colOutline, curMetrics._x2, curMetrics._y1},
				{posX + curMetrics._w + 1.f,posY + curMetrics._h,		colOutline, curMetrics._x2, curMetrics._y2},


				{posX + curMetrics._w + 1.f,posY + curMetrics._h,		colOutline, curMetrics._x2, curMetrics._y2},
				{posX + 1.f,				posY + curMetrics._h,		colOutline, curMetrics._x1, curMetrics._y2},
				{posX + 1.f,				posY,						colOutline, curMetrics._x1, curMetrics._y1},

				{posX,						posY + 1.f,					colOutline, curMetrics._x1, curMetrics._y1},
				{posX + curMetrics._w,		posY + 1.f,					colOutline, curMetrics._x2, curMetrics._y1},
				{posX + curMetrics._w,		posY + curMetrics._h + 1.f,	colOutline, curMetrics._x2, curMetrics._y2},

				{posX + curMetrics._w,		posY + curMetrics._h + 1.f,	colOutline, curMetrics._x2, curMetrics._y2},
				{posX,						posY + curMetrics._h + 1.f,	colOutline, curMetrics._x1, curMetrics._y2},
				{posX,						posY + 1.f,					colOutline, curMetrics._x1, curMetrics._y1},

				{posX,						posY - 1.f,					colOutline, curMetrics._x1, curMetrics._y1},
				{posX + curMetrics._w,		posY - 1.f,					colOutline, curMetrics._x2, curMetrics._y1},
				{posX + curMetrics._w,		posY + curMetrics._h - 1.f,	colOutline, curMetrics._x2, curMetrics._y2},

				{posX + curMetrics._w,		posY + curMetrics._h - 1.f,	colOutline, curMetrics._x2, curMetrics._y2},
				{posX,						posY + curMetrics._h - 1.f,	colOutline, curMetrics._x1, curMetrics._y2},
				{posX,						posY - 1.f,					colOutline, curMetrics._x1, curMetrics._y1},


				{posX,						posY,						col,		curMetrics._x1, curMetrics._y1},
				{posX + curMetrics._w,		posY,						col,		curMetrics._x2, curMetrics._y1},
				{posX + curMetrics._w,		posY + curMetrics._h,		col,		curMetrics._x2, curMetrics._y2},

				{posX + curMetrics._w,		posY + curMetrics._h,		col,		curMetrics._x2, curMetrics._y2},
				{posX,						posY + curMetrics._h,		col,		curMetrics._x1, curMetrics._y2},
				{posX,						posY,						col,		curMetrics._x1, curMetrics._y1},
			};

			addToBatch(vertices, D3DPT_TRIANGLELIST, 2 * 5, myFont.m_cFontTexture.getTexture());
		}

		// mmmm premium text spacing!!
		posX += curMetrics._w - 2.f * spacing;
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
		const auto& lookup = _circleLookup.at(i);
		vertices.emplace_back(x + r * lookup.cos, y + r * lookup.sin, col, 0.f, 0.f);
	}

	addToBatch(vertices, D3DPT_LINESTRIP, CIRCLE_SEGMENTS, NULL);
	breakBatch();
}

void C_DX9Render::drawCircleFill(float x, float y, float r, DWORD col) {

	std::vector<T_Vertex> vertices;
	vertices.emplace_back(x, y, col, 0.f, 0.f);

	for (size_t i = 0; i <= CIRCLE_SEGMENTS; i++) {
		const auto& lookup = _circleLookup.at(i);
		vertices.emplace_back(x + r * lookup.cos, y + r * lookup.sin, col, 0.f, 0.f);
	}

	addToBatch(vertices, D3DPT_TRIANGLEFAN, CIRCLE_SEGMENTS, NULL);
	breakBatch();
}

void C_DX9Render::drawCircleFillGradient(float x, float y, float r, DWORD colO, DWORD colI) {

	std::vector<T_Vertex> vertices;
	vertices.emplace_back(x, y, colI, 0.f, 0.f);

	for (size_t i = 0; i <= CIRCLE_SEGMENTS; i++) {
		const auto& lookup = _circleLookup.at(i);
		vertices.emplace_back(x + r * lookup.cos, y + r * lookup.sin, colO, 0.f, 0.f);
	}

	addToBatch(vertices, D3DPT_TRIANGLEFAN, CIRCLE_SEGMENTS, NULL);
	breakBatch();
}

void C_DX9Render::drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, DWORD col) {

	const std::vector<T_Vertex> vertices = {
		{x1, y1, col, 0.f, 0.f},
		{x2, y2, col, 0.f, 0.f},

		{x2, y2, col, 0.f, 0.f},
		{x3, y3, col, 0.f, 0.f},

		{x3, y3, col, 0.f, 0.f},
		{x1, y1, col, 0.f, 0.f},
	};

	addToBatch(vertices, D3DPT_LINELIST, 3, NULL);
}

void C_DX9Render::drawTriangleFill(float x1, float y1, float x2, float y2, float x3, float y3, DWORD col) {

	const std::vector<T_Vertex> vertices = {
		{x1, y1, col, 0.f, 0.f},
		{x2, y2, col, 0.f, 0.f},
		{x3, y3, col, 0.f, 0.f},
	};

	addToBatch(vertices, D3DPT_TRIANGLELIST, 1, NULL);
}