#pragma once

#include <d3d9.h>
#include <exception>

namespace CORE::DX9 {

	class C_RenderState {
	public:
		C_RenderState() {
		
		}

		~C_RenderState() {
			release();
		}

		void create(IDirect3DDevice9* device);
		void capture();
		void apply();
		void release();
	private:
		IDirect3DDevice9* _device{};
		IDirect3DStateBlock9* _stateBlock{};

		IDirect3DVertexShader9* _vertexShader{};
		IDirect3DVertexDeclaration9* _vertexDeclaration{};
	};
}