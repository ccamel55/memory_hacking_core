#pragma once

#include <d3d9.h>

#include <memory>
#include <exception>

namespace CORE::DX9 {

	// vertex format, specified by these flags
	//	x y z w | ARGB DWORD | tx ty
	constexpr auto D3DFVF_CUSTOM = (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);

	struct T_Vertex {

		T_Vertex() {
			col = 0xFFFFFFFF;

			std::memset(pos, 0, sizeof(pos));
			std::memset(tex, 0, sizeof(tex));
		}

		T_Vertex(float x, float y, DWORD cols, float tx, float ty) {
			pos[0] = x;
			pos[1] = y;

			col = cols;

			tex[0] = tx;
			tex[1] = ty;

			pos[2] = 0.f;
			pos[3] = 1.f;
		}

		float pos[4]; // x y z w
		DWORD col;
		float tex[2]; // tx ty
	};

	class C_VertexBuffer {
	public:
		C_VertexBuffer() {

		}

		~C_VertexBuffer() {
			release();
		}

		void create(IDirect3DDevice9* device, size_t bufferSize);
		void bindData(const void* data, size_t size);
		void apply();
		void release();
	private:
		IDirect3DDevice9* _device{};
		IDirect3DVertexBuffer9* _vertexBuffer{};
	};
}