#include "StateManager.hpp"

using namespace CORE::DX9;

void C_RenderState::create(IDirect3DDevice9* device, bool buildCustom) {

    _device = device;

    // create state block and we can capture current state
    if (FAILED(_device->CreateStateBlock(D3DSBT_ALL, &_stateBlock))) {
        throw std::exception("failed to create state block");
    }

    if (buildCustom) {

        // build a new state using our custom settings
        _device->BeginStateBlock();

        _device->SetPixelShader(nullptr);
        _device->SetVertexShader(nullptr);

        _device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
        _device->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
        _device->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
        _device->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
        _device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
        _device->SetRenderState(D3DRS_ZENABLE, FALSE);
        _device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
        _device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
        _device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
        _device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
        _device->SetRenderState(D3DRS_SEPARATEALPHABLENDENABLE, TRUE);
        _device->SetRenderState(D3DRS_SRCBLENDALPHA, D3DBLEND_ONE);
        _device->SetRenderState(D3DRS_DESTBLENDALPHA, D3DBLEND_INVSRCALPHA);
        _device->SetRenderState(D3DRS_SCISSORTESTENABLE, TRUE);
        _device->SetRenderState(D3DRS_FOGENABLE, FALSE);
        _device->SetRenderState(D3DRS_RANGEFOGENABLE, FALSE);
        _device->SetRenderState(D3DRS_SPECULARENABLE, FALSE);
        _device->SetRenderState(D3DRS_STENCILENABLE, FALSE);
        _device->SetRenderState(D3DRS_CLIPPING, TRUE);
        _device->SetRenderState(D3DRS_LIGHTING, FALSE);

        _device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
        _device->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
        _device->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
        _device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
        _device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
        _device->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
        _device->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
        _device->SetTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_DISABLE);

        _device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
        _device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

        _device->EndStateBlock(&_stateBlock);
    }
    else {
        _stateBlock->Capture();
    }
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