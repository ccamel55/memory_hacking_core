#include "StateManager.hpp"

using namespace CORE::DX9;

void C_RenderState::create(IDirect3DDevice9* device, bool buildCustom) {

    m_pDevice = device;

    // create state block and we can capture current state
    if (FAILED(m_pDevice->CreateStateBlock(D3DSBT_ALL, &m_pStateBlock))) {
        throw std::exception("failed to create state block");
    }

    if (buildCustom) {

        // build a new state using our custom settings
        m_pDevice->BeginStateBlock();

        m_pDevice->SetPixelShader(nullptr);
        m_pDevice->SetVertexShader(nullptr);

        m_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
        m_pDevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
        m_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
        m_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
        m_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
        m_pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
        m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
        m_pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
        m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
        m_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
        m_pDevice->SetRenderState(D3DRS_SEPARATEALPHABLENDENABLE, TRUE);
        m_pDevice->SetRenderState(D3DRS_SRCBLENDALPHA, D3DBLEND_ONE);
        m_pDevice->SetRenderState(D3DRS_DESTBLENDALPHA, D3DBLEND_INVSRCALPHA);
        m_pDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, TRUE);
        m_pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);
        m_pDevice->SetRenderState(D3DRS_RANGEFOGENABLE, FALSE);
        m_pDevice->SetRenderState(D3DRS_SPECULARENABLE, FALSE);
        m_pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);
        m_pDevice->SetRenderState(D3DRS_CLIPPING, TRUE);
        m_pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

        m_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
        m_pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
        m_pDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
        m_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
        m_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
        m_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
        m_pDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
        m_pDevice->SetTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_DISABLE);

        m_pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
        m_pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

        m_pDevice->EndStateBlock(&m_pStateBlock);
    }
    else {
        m_pStateBlock->Capture();
    }
}

void C_RenderState::apply() {
    m_pStateBlock->Apply();
}

void C_RenderState::release() {

    if (m_pStateBlock) {
        m_pStateBlock->Release();
        m_pStateBlock = NULL;
    }
}