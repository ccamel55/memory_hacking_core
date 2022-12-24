#include "VertexBuffer.hpp"

using namespace CORE::DX9;

void C_VertexBuffer::create(IDirect3DDevice9* device, size_t bufferSize) {

	_device = device;

	// create a new buffer
	if (FAILED(_device->CreateVertexBuffer(bufferSize * sizeof(T_Vertex), D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY, D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1, D3DPOOL_DEFAULT, &_vertexBuffer, nullptr))) {
		throw std::exception("failed to create vertex buffer");
	}
}

void C_VertexBuffer::bindData(const void* data, size_t size) {

	void* dataPtr = NULL;
	_vertexBuffer->Lock(0, 0, &dataPtr, D3DLOCK_DISCARD);
	{
		// memcpy fast!!!!!!!!!!!!!!!!!!!!!
		std::memcpy(dataPtr, data, size * sizeof(T_Vertex));
	}
	_vertexBuffer->Unlock();
}

void C_VertexBuffer::apply() {
	_device->SetFVF(D3DFVF_CUSTOM);
	_device->SetStreamSource(0, _vertexBuffer, 0, sizeof(T_Vertex));
}

void C_VertexBuffer::release() {

	if (_vertexBuffer) {
		_vertexBuffer->Release();
		_vertexBuffer = NULL;
	}
}