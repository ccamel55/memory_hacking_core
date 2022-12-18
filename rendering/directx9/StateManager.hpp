#pragma once

#include <d3d9.h>
#include <exception>

namespace CORE::DX9 {

	class C_RenderState {
	public:
		C_RenderState() {
			m_pDevice = NULL;
			m_pStateBlock = NULL;
		}

		~C_RenderState() {
			release();
		}

		void create(IDirect3DDevice9* device, bool buildCustom);
		void apply();
		void release();
	private:
		IDirect3DDevice9* m_pDevice;
		IDirect3DStateBlock9* m_pStateBlock;
	};
}