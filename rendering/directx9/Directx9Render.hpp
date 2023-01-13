#pragma once
#pragma comment(lib, "d3d9.lib")

#include "../../singleton.hpp"
#include "../../cryptography/fn1v.hpp"

#include "../../type/Bitflag.hpp"

#include "../BitmapFont.hpp"
#include "../RenderImpl.hpp"
#include "../CircleCache.hpp"

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

	class C_DX9Render : public Singleton< C_DX9Render>, public C_RenderImpl {
	public:
		C_DX9Render() {
			C_CircleCache::get().cache();
		}

		void bindDevice(IDirect3DDevice9* device);
		void invalidateDevice();
		void release();
		void startDraw();
		void finishDraw();
		void addToBatch(const std::vector<T_Vertex>& data, D3DPRIMITIVETYPE type, size_t primitiveCount, IDirect3DTexture9* tex = NULL);
		void breakBatch();
		void applyRenderState();
	public:
		/* render API functions */
		void addFont(hash_t font, const std::string& family, size_t height, size_t weight) override;
		POINT& getScreenSize() override;

		size_t getStringWidth(hash_t font, const std::string& text) override;
		size_t getStringHeight(hash_t font) override;
		float getFrameTime() override;

		void drawString(float x, float y, hash_t font, DWORD col, const std::string& text, bit_flag_t flags = 0) override;
		void drawStringOutline(float x, float y, hash_t font, DWORD col, DWORD colOutline, const std::string& text, bit_flag_t flags = 0) override;
		void drawRect(float x, float y, float w, float h, DWORD col) override;
		void drawRectFill(float x, float y, float w, float h, DWORD col);
		void drawRectFillGradientH(float x, float y, float w, float h, DWORD colL, DWORD colR) override;
		void drawRectFillGradientV(float x, float y, float w, float h, DWORD colT, DWORD colB) override;
		void drawCircle(float x, float y, float r, DWORD col) override;
		void drawCircleFill(float x, float y, float r, DWORD col) override;
		void drawCircleFillGradient(float x, float y, float r, DWORD colO, DWORD colI) override;
		void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, DWORD col) override;
		void drawTriangleFill(float x1, float y1, float x2, float y2, float x3, float y3, DWORD col) override;
	private:
		bool _init{};
		IDirect3DDevice9* _device{};

		POINT _screenSize{};
		D3DVIEWPORT9 _viewport{};

		C_RenderState _oldState{};
		C_VertexBuffer _mainBuffer{};

		std::vector<T_RenderBatch> _drawBatchs{};
		std::unordered_map<hash_t, T_Font> _fonts{};
	};
}