#include "BitmapFont.hpp"

using namespace CORE;

C_BitmapFont::C_BitmapFont() {
    m_pBitmap = NULL;
    m_hBitmap = NULL;

    m_iWidth = 0;
    m_iHeight = 0;

    std::memset(&m_aTexCoOrds, 0, sizeof(m_aTexCoOrds));
}

C_BitmapFont::~C_BitmapFont() {
    release();
}

void C_BitmapFont::release() {
    DeleteObject(m_hBitmap);
}

void C_BitmapFont::setFont(const std::string& fontFamily, size_t height, size_t weight) {

    // super ghetto way, we can fix this laterzzz
    if (height > 60) {
        m_iWidth = 2048;
        m_iHeight = 2048;
    }
    else if (height > 30) {
        m_iWidth = 1024;
        m_iHeight = 1024;
    }
    else if (height > 15) {
        m_iWidth = 512;
        m_iHeight = 512;
    }
    else {
        m_iWidth = 256;
        m_iHeight = 256;
    }

    // Prepare to create a bitmap
    BITMAPINFO bmi = {};
    ZeroMemory(&bmi.bmiHeader, sizeof(BITMAPINFOHEADER));

    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = m_iWidth;
    bmi.bmiHeader.biHeight = -m_iHeight;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biCompression = BI_RGB;
    bmi.bmiHeader.biBitCount = 32;

    // Create a DC and a bitmap for the font
    const auto hDC = CreateCompatibleDC(NULL);
    const auto hbmBitmap = CreateDIBSection(hDC, &bmi, DIB_RGB_COLORS, reinterpret_cast<void**>(&m_pBitmap), NULL, 0);

    SetMapMode(hDC, MM_TEXT);

    // Create a font.
    // By specifying ANTIALIASED_QUALITY, we might get an antialiased font, but this is not guaranteed.
    const auto hFont = CreateFont(height, 0, 0, 0, weight, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, VARIABLE_PITCH, fontFamily.c_str());

    const auto hbmOld = SelectObject(hDC, hbmBitmap);
    const auto hFontOld = SelectObject(hDC, hFont);

    // Set text properties
    SetTextColor(hDC, RGB(255, 255, 255));
    SetBkColor(hDC, 0x00000000);
    SetTextAlign(hDC, TA_TOP);

    // Loop through all printable character and output them to the bitmap..
    // Meanwhile, keep track of the corresponding tex coords for each character.
    DWORD x = 0;
    DWORD y = 0;

    char str[2] = "x";
    SIZE size;

    // Calculate the spacing between characters based on line height
    GetTextExtentPoint32(hDC, TEXT(" "), 1, &size);
    x = m_iSpacing = static_cast<DWORD>(ceil(size.cy * 0.3f));

    for (char c = 32; c < 127; c++) {

        str[0] = c;
        GetTextExtentPoint32(hDC, str, 1, &size);

        const auto charExtentX = size.cx;
        const auto charExtentY = size.cy;

        if (static_cast<int>(x + charExtentX + m_iSpacing) > m_iWidth) {
            x = m_iSpacing;
            y += charExtentY + 1;
        }

        ExtTextOut(hDC, x, y, ETO_OPAQUE, NULL, str, 1, NULL);

        auto& texCoord = m_aTexCoOrds[c - 32];

        texCoord.x1 = static_cast<float>(x - m_iSpacing) / m_iWidth;
        texCoord.y1 = static_cast<float>(y) / m_iHeight;

        texCoord.x2 = static_cast<float>(x + charExtentX + m_iSpacing) / m_iWidth;
        texCoord.y2 = static_cast<float>(y + charExtentY) / m_iHeight;

        texCoord.w = (texCoord.x2 - texCoord.x1) * m_iWidth;
        texCoord.h = (texCoord.y2 - texCoord.y1) * m_iHeight;

        x += charExtentX + (2 * m_iSpacing);
    }

    SelectObject(hDC, hbmOld);
    SelectObject(hDC, hFontOld);
    DeleteObject(hFont);
    DeleteDC(hDC);
}

float C_BitmapFont::getStringHeight() {
    return (m_aTexCoOrds[0].y2 - m_aTexCoOrds[0].y1) * m_iHeight;
}

float C_BitmapFont::getStringWidth(const std::string& text) {

    if (text.empty()) {
        return 0.f;
    }

    float ret = 0.f;

    for (const auto& c : text) {

        if (c - 32 < 0 || c - 32 >= 128 - 32) {
            continue;
        }

        ret += (m_aTexCoOrds[c - 32].x2 - m_aTexCoOrds[c - 32].x1) * m_iWidth - 2.f * m_iSpacing;
    }

    return ret;
}

DWORD* C_BitmapFont::getFontBitmap() {
    return m_pBitmap;
}

int C_BitmapFont::getWidth() {
    return m_iWidth;
}

int C_BitmapFont::getHeight() {
    return m_iHeight;
}

DWORD C_BitmapFont::getSpacing() {
    return m_iSpacing;
}

T_TexCoOrd& C_BitmapFont::getTextCoords(size_t c) {
    return m_aTexCoOrds.at(c);
}