#pragma once
#include "..\..\pch.h"
#include "..\HeaderFiles\DirectX11_Device.h"
#include <memory>


class DirectXRender
{
public:
    DirectXRender();
    ~DirectXRender();
    HRESULT SetRender(std::unique_ptr<DirectX11_Device> device);

    // MATRICES
    DirectX::XMMATRIX m_World;
    DirectX::XMMATRIX m_View;
    DirectX::XMMATRIX m_Projection;

    // DirectX Objects //
    Microsoft::WRL::ComPtr<IDXGISwapChain> m_pSwapChain;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_pImmediateContext;
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_pRenderTarget;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_pDepthStencilView;
    Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pPixelShader;
    Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pSolidShader;
    Microsoft::WRL::ComPtr<ID3D11VertexShader> m_pVertexShader;
    Microsoft::WRL::ComPtr<ID3D11Buffer> m_pConstantBuffer;
    /* Name: Draw()
    Params: IMesh
    Returns: Void
    Info: Draws the object to the screen. 
    */
    //void Draw(std::shared_ptr<IObject> object);
private:
    /*Microsoft::WRL::ComPtr<IDXGISwapChain> m_pSwapChain;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_pImmediateContext;
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_pRenderTarget;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_pDepthStencilView;
    Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pPixelShader;
    Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pSolidShader;
    Microsoft::WRL::ComPtr<ID3D11VertexShader> m_pVertexShader;
    Microsoft::WRL::ComPtr<ID3D11Buffer> m_pConstantBuffer;*/

    //// MATRICES
    //DirectX::XMMATRIX m_World;
    //DirectX::XMMATRIX m_View;
    //DirectX::XMMATRIX m_Projection;

    UINT m_ScreenWidth;
    UINT m_ScreenHeight;
    //TODO: We want to set up where this class only holds references to the objects from DirectX_Device. This object will be passed into the Render() of each IObjects.
    // Also, I may want to think about putting all my shader objects into a specific class whereby I can then call them from a class. ShaderClass->PixelShader() for example. 
    // In the end, I want this class to store the objects we'll need to use only for rendering, this should make the object itself small. In face we shouldn't have a "Device" reference. 
    // Think about removing. Then we pass this class into a IObject's Draw() and that IObject will have Shader's it will use from the IShader class. 

    // Private Methods //
    void InitMatrices();
};

