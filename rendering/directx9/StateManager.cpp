#include "StateManager.hpp"

using namespace CORE::DX9;

void C_RenderState::create(IDirect3DDevice9* device) {

    _device = device;

    // create state block and we can capture current state
    if (FAILED(_device->CreateStateBlock(D3DSBT_ALL, &_stateBlock))) {
        throw std::exception("failed to create state block");
    }
}

void C_RenderState::capture() {
    _stateBlock->Capture();
}

void C_RenderState::apply() {
    _stateBlock->Apply();
}

void C_RenderState::release() {

    if (_stateBlock) {
        _stateBlock->Release();
        _stateBlock = NULL;
    }
}