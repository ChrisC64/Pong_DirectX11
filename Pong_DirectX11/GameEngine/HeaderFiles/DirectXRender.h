#pragma once
#include "..\..\pch.h"
#include "..\HeaderFiles\DirectX11_Device.h"
#include <memory>

namespace LunaSolEngine
{
    class DirectXRender
    {
    public:
        DirectXRender();
        ~DirectXRender();
        HRESULT SetRender(std::unique_ptr<LunaSolEngine::DirectX11_Device> device);

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
        // Private Methods //
        void InitMatrices();
    };
}