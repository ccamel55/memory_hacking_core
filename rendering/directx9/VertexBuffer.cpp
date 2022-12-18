#include "VertexBuffer.hpp"

using namespace CORE::DX9;

void C_VertexBuffer::create(IDirect3DDevice9* device, size_t bufferSize) {

	m_pDevice = device;

	// create a new buffer
	if (FAILED(m_pDevice->CreateVertexBuffer(bufferSize * sizeof(T_Vertex), D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY, D3DFVF_CUSTOM, D3DPOOL_DEFAULT, &m_pVertexBuffer, nullptr))) {
		throw std::exception("failed to create vertex buffer");
	}
}

void C_VertexBuffer::bindData(const void* data, size_t size) {

	void* dataPtr = NULL;
	m_pVertexBuffer->Lock(0, 0, &dataPtr, D3DLOCK_DISCARD);
	{
		// memcpy fast!!!!!!!!!!!!!!!!!!!!!
		std::memcpy(dataPtr, data, size * sizeof(T_Vertex));
	}
	m_pVertexBuffer->Unlock();
}

void C_VertexBuffer::apply() {
	m_pDevice->SetFVF(D3DFVF_CUSTOM);
	m_pDevice->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(T_Vertex));
}

void C_VertexBuffer::release() {

	if (m_pVertexBuffer) {
		m_pVertexBuffer->Release();
		m_pVertexBuffer = NULL;
	}
}