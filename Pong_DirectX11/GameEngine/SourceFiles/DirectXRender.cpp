#include "..\HeaderFiles\DirectXRender.h"
using namespace LunaSolEngine;


DirectXRender::DirectXRender()
{
}

DirectXRender::~DirectXRender()
{
}

HRESULT DirectXRender::SetRender(std::unique_ptr<DirectX11_Device> device)
{
    if (!device)
    { 
        return E_FAIL;
    }
    // Set up or objects from the Device
    if(!(m_pSwapChain = device->GetSwapChain())) // Should make Exception Handlers
    { 
        TRACE(L"Failed to get SwapChain from the device, NULL OBJECT\n");
        return E_FAIL;
    }
    if (!(m_pImmediateContext = device->GetImmediateContext()))
    {
        TRACE(L"Failed to get ImmediateContext from the device, NULL OBJECT\n");
        return E_FAIL;
    }
    if(!(m_pRenderTarget = device->GetRenderTargetView()))
    {
        TRACE(L"Failed to get Render Target View from the device, NULL OBJECT\n");
        return E_FAIL;
    }
    if (!(m_pDepthStencilView = device->GetDepthStencilView()))
    {
        TRACE(L"Failed to get Depth Stencil View from the device, NULL OBJECT\n");
        return E_FAIL;
    }
    if (!(m_pPixelShader = device->GetPixelShader()))
    {
        TRACE(L"Failed to get the Pixel Shader from the device, NULL OBJECT\n");
        return E_FAIL;
    }
    if (!(m_pSolidShader = device->GetSolidShader()))
    {
        TRACE(L"Failed to get the Solid shader from the device, NULL OBJECT\n");
        return E_FAIL;
    }
    if (!(m_pVertexShader = device->GetVertexShader()))
    {
        TRACE(L"Failed to get thes Vertex Shader from the device, NULL OBJECT\n");
        return E_FAIL;
    }
    if (!(m_pConstantBuffer = device->GetConstantBuffer()))
    {
        TRACE(L"Failed to get the constant buffer from the device, NULL OBJECT\n");
        return E_FAIL;
    }

    m_ScreenHeight = device->GetScreenHeight();
    m_ScreenWidth = device->GetScreenWidth();
    
    return S_OK;
}

void DirectXRender::InitMatrices()
{
    // Initialize World Matrix
    m_World = DirectX::XMMatrixIdentity();
    DirectX::XMVECTOR Eye = DirectX::XMVectorSet(0.0f, 4.0f, -10.0f, 0.0f);
    DirectX::XMVECTOR At = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
    DirectX::XMVECTOR Up = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

    m_View = DirectX::XMMatrixLookAtLH(Eye, At, Up);
    // Initialize Projection Matrix
    m_Projection = DirectX::XMMatrixPerspectiveFovLH(DirectX::XM_PIDIV2, m_ScreenWidth / (FLOAT)m_ScreenHeight, 0.01f, 100.0f);
}

//void DirectXRender::Draw(std::shared_ptr<IObject> object)
//{
//    
//}
