#pragma once

#include "../RenderImpl.hpp"

namespace CORE::GL3 {

	class C_GL3Render : public Singleton< C_GL3Render>, public C_RenderImpl {
	public:
		/* render API functions */
		void addFont(hash_t font, const std::string& family, size_t height, size_t weight) override;
		POINT& getScreenSize() override;

		size_t getStringWidth(hash_t font, const std::string& text) override;
		size_t getStringHeight(hash_t font) override;

		void drawString(float x, float y, hash_t font, DWORD col, const std::string& text, uint8_t flags = 0) override;
		void drawStringOutline(float x, float y, hash_t font, DWORD col, DWORD colOutline, const std::string& text, uint8_t flags = 0) override;
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
		POINT _screenSize{};
	};
}