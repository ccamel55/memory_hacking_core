#include "BitmapFont.hpp"

#include <fstream>

using namespace CORE;

C_BitmapFont::C_BitmapFont() {
    _bitmapPtr = NULL;
    _bitmapHandle = NULL;

    _width = 0;
    _height = 0;

    std::memset(&_texCoords, 0, sizeof(_texCoords));
}

C_BitmapFont::~C_BitmapFont() {
    release();
}

void C_BitmapFont::release() {
    DeleteObject(_bitmapHandle);
}

void C_BitmapFont::setFont(const std::string& fontFamily, size_t height, size_t weight) {

    // super ghetto way, we can fix this laterzzz
    if (height > 60) {
        _width = 2048; 
        _height = 2048;
    }
    else if (height > 30) {
        _width = 1024;
        _height = 1024;
    }
    else if (height > 15) {
        _width = 512;
        _height = 512;
    }
    else {
        _width = 256;
        _height = 256;
    }

    // Prepare to create a bitmap
    BITMAPINFO bmi = {};
    ZeroMemory(&bmi.bmiHeader, sizeof(BITMAPINFOHEADER));

    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = _width;
    bmi.bmiHeader.biHeight = -_height;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biCompression = BI_RGB;
    bmi.bmiHeader.biBitCount = 32;

    // Create a DC and a bitmap for the font
    const auto hDC = CreateCompatibleDC(NULL);
    const auto hbmBitmap = CreateDIBSection(hDC, &bmi, DIB_RGB_COLORS, reinterpret_cast<void**>(&_bitmapPtr), NULL, 0);

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
    x = _spacing = static_cast<DWORD>(ceil(size.cy * 0.3f));

    for (char c = 32; c < 127; c++) {

        str[0] = c;
        GetTextExtentPoint32(hDC, str, 1, &size);

        const auto charExtentX = size.cx;
        const auto charExtentY = size.cy;

        if (static_cast<int>(x + charExtentX + _spacing) > _width) {
            x = _spacing;
            y += charExtentY + 1;
        }

        ExtTextOut(hDC, x, y, ETO_OPAQUE, NULL, str, 1, NULL);

        auto& texCoord = _texCoords[c - 32];

        texCoord._x1 = static_cast<float>(x - _spacing) / _width;
        texCoord._y1 = static_cast<float>(y) / _height;

        texCoord._x2 = static_cast<float>(x + charExtentX + _spacing) / _width;
        texCoord._y2 = static_cast<float>(y + charExtentY) / _height;

        texCoord._w = (texCoord._x2 - texCoord._x1) * _width;
        texCoord._h = (texCoord._y2 - texCoord._y1) * _height;

        x += charExtentX + (2 * _spacing);
    }

    SelectObject(hDC, hbmOld);
    SelectObject(hDC, hFontOld);
    DeleteObject(hFont);
    DeleteDC(hDC);
}

float C_BitmapFont::getStringHeight() {
    return (_texCoords[0]._y2 - _texCoords[0]._y1) * _height;
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

        ret += (_texCoords[c - 32]._x2 - _texCoords[c - 32]._x1) * _width - 2.f * _spacing;
    }

    return ret;
}

uint32_t* C_BitmapFont::getFontBitmap() {
    return _bitmapPtr;
}

int C_BitmapFont::getWidth() {
    return _width;
}

int C_BitmapFont::getHeight() {
    return _height;
}

DWORD C_BitmapFont::getSpacing() {
    return _spacing;
}

T_TexCoord& C_BitmapFont::getTextCoords(size_t c) {
    return _texCoords.at(c);
}
