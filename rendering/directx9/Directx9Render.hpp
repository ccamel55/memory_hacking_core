#pragma once

#include "../../../Singleton.hpp"
#include "../../cryptography/fn1v.hpp"

#include "../BitmapFont.hpp"

#include "StateManager.hpp"
#include "VertexBuffer.hpp"
#include "Texture.hpp"

#include <d3d9.h>
#include <d3dx9.h>

#include <array>
#include <vector>
#include <unordered_map>


namespace CORE::DX9 {

	constexpr size_t MAX_VERTICES = 2048 * 6;

	enum E_FONT_FLAGS : char {
		ALIGN_L = 1 << 0,
		ALIGN_R = 1 << 1,
		OUTLINE = 1 << 2,
		CENTER_X = 1 << 3,
		CENTER_Y = 1 << 4,
	};

	struct T_Primitive {

		T_Primitive() {
			m_iCount = 0;
			m_iSize = 0;

			m_iType = D3DPT_FORCE_DWORD;
			m_pTexture = NULL;
		}

		T_Primitive(D3DPRIMITIVETYPE type, IDirect3DTexture9* tex) {
			m_iCount = 0;
			m_iSize = 0;

			m_iType = type;
			m_pTexture = tex;
		}

		size_t m_iCount;
		size_t m_iSize;

		D3DPRIMITIVETYPE m_iType;
		IDirect3DTexture9* m_pTexture;
	};

	struct T_RenderBatch {

		T_RenderBatch() {
			m_iVertexCount = 0;
			m_aPrimitives.clear();

			// clean new array
			std::memset(&m_aVertices, 0, sizeof(m_aVertices));
		}

		std::vector<T_Primitive> m_aPrimitives;

		size_t m_iVertexCount;
		std::array<T_Vertex, MAX_VERTICES> m_aVertices;
	};

	struct T_Font {

		T_Font() {
			m_cFontTexture;
			m_cFontBitmap;
		}

		~T_Font() {
			m_cFontTexture.release();
			m_cFontBitmap.release();
		}

		T_Font(const std::string& fontFamily, size_t height, size_t weight) {
			m_cFontBitmap.setFont(fontFamily, height, weight);
			m_cFontTexture;
		}

		void bind(IDirect3DDevice9* device) {
			m_cFontTexture.bindBitmap(device, m_cFontBitmap.getFontBitmap(), m_cFontBitmap.getWidth(), m_cFontBitmap.getHeight());
		}

		C_Texture m_cFontTexture;
		C_BitmapFont m_cFontBitmap;
	};

	struct T_Circle {
		float cos;
		float sin;
	};

	class C_DX9Render : public Singleton< C_DX9Render> {
	public:
		C_DX9Render() {

			m_pDevice = NULL;
			m_bInit = false;

			m_cScreenSize = { 0, 0 };
			m_cViewport = { 0, 0, 0, 0 };

			m_cOldState = {};
			m_cNewState = {};
			m_cMainBuffer = {};

			m_aDrawBatchs.clear();
			m_mFonts;

			// build lookup circle
			for (size_t i = 0; i <= CIRCLE_SEGMENTS; i++) {
				m_aCircleLookup.at(i).cos = std::cos(6.283185f * (i / static_cast<float>(CIRCLE_SEGMENTS)));
				m_aCircleLookup.at(i).sin = std::sin(6.283185f * (i / static_cast<float>(CIRCLE_SEGMENTS)));
			}
		}

		~C_DX9Render() {

			for (auto& font : m_mFonts) {
				font.second.m_cFontTexture.release();
				font.second.m_cFontBitmap.release();
			}

			release();
		}

		void bindDevice(IDirect3DDevice9* device);
		void invalidateDevice();
		void release();
		void startDraw();
		void finishDraw();
		void addFont(hash_t font, const std::string family, size_t height, size_t weight);
		POINT& getScreenSize();
		void addToBatch(const std::vector<T_Vertex>& data, D3DPRIMITIVETYPE type, size_t primitiveCount, IDirect3DTexture9* tex = NULL);
		void breakBatch();
	public:
		void drawString(float x, float y, hash_t font, DWORD col, const std::string& text, uint8_t flags = 0);
		void drawStringOutline(float x, float y, hash_t font, DWORD col, DWORD colOutline, const std::string& text, uint8_t flags = 0);
		void drawRect(float x, float y, float w, float h, DWORD col);
		void drawRectFill(float x, float y, float w, float h, DWORD col);
		void drawRectFillGradientH(float x, float y, float w, float h, DWORD colL, DWORD colR);
		void drawRectFillGradientV(float x, float y, float w, float h, DWORD colT, DWORD colB);
		void drawCircle(float x, float y, float r, DWORD col);
		void drawCircleFill(float x, float y, float r, DWORD col);
		void drawCircleFillGradient(float x, float y, float r, DWORD colO, DWORD colI);
	private:
		bool m_bInit;
		IDirect3DDevice9* m_pDevice;

		POINT m_cScreenSize;
		D3DVIEWPORT9 m_cViewport;

		C_RenderState m_cOldState;
		C_RenderState m_cNewState;
		C_VertexBuffer m_cMainBuffer;

		std::vector<T_RenderBatch> m_aDrawBatchs;
		std::unordered_map<hash_t, T_Font> m_mFonts;

		static constexpr size_t CIRCLE_SEGMENTS = 64;
		std::array<T_Circle, CIRCLE_SEGMENTS + 1> m_aCircleLookup;
	};
}