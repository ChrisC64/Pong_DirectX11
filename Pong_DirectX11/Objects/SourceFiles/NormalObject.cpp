#include "..\HeaderFiles\NormalObject.h"



NormalObject::NormalObject()
{
}


NormalObject::~NormalObject()
{
}
// Perhaps make a boolean? Return false if we don't draw for some reason and handle the error.
void NormalObject::Draw(std::shared_ptr<DirectXRender> render)
{
    //if (!render)
    //{
    //    return;
    //}
    ////TODO: This should probably not be here in the call of the object, but higher up. 
    //static float t = 0.0f;
    //static ULONGLONG timeStart = 0;
    //ULONGLONG timeCur = GetTickCount64();
    //if (timeStart == 0)
    //    timeStart = timeCur;
    //t = (timeCur - timeStart) / 1000.0f;

    //render->m_World = XMMatrixRotationY(t);

    //// Set up lighting parameters
    //XMFLOAT4 vLightDirs[2] =
    //{
    //    XMFLOAT4(-0.577f, 0.577f, -0.577f, 1.0f),
    //    XMFLOAT4(0.0f, 0.0f, -1.0f, 1.0f),
    //};
    //XMFLOAT4 vLightColors[2] =
    //{
    //    XMFLOAT4(0.10f, 0.50f, 0.25f, 1.0f),
    //    XMFLOAT4(0.5f, 0.0f, 0.5f, 1.0f)
    //};

    //// Rotate the second light around the origin
    //XMMATRIX mRotate = XMMatrixRotationY(-2.0f * t);
    //XMVECTOR vLightDir = XMLoadFloat4(&vLightDirs[1]);
    //vLightDir = XMVector3Transform(vLightDir, mRotate);
    //XMStoreFloat4(&vLightDirs[1], vLightDir);

    //// Clear the back buffer
    //render->m_pImmediateContext.Get()->ClearRenderTargetView(render->m_pRenderTarget.Get(), DirectX::Colors::MidnightBlue);
    //// Clear the depth buffer
    //render->m_pImmediateContext.Get()->ClearDepthStencilView(render->m_pDepthStencilView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);

    //GameStruct::DataStructs::ConstantBuffer cb;
    //cb.world = XMMatrixTranspose(render->m_World);
    //cb.view = XMMatrixTranspose(render->m_View);
    //cb.proj = XMMatrixTranspose(render->m_Projection);
    //cb.vLightDir[0] = vLightDirs[0];
    //cb.vLightDir[1] = vLightDirs[1];
    //cb.vLightColor[0] = vLightColors[0];
    //cb.vLightColor[1] = vLightColors[1];
    //cb.vOutputColor = XMFLOAT4(0, 0, 0, 0);
    //render->m_pImmediateContext.Get()->UpdateSubresource(render->m_pConstantBuffer.Get(), 0, nullptr, &cb, 0, 0);

    //// Render Object (First cube)
    //render->m_pImmediateContext.Get()->VSSetShader(render->m_pVertexShader.Get(), nullptr, 0);
    //render->m_pImmediateContext.Get()->VSSetConstantBuffers(0, 1, render->m_pConstantBuffer.GetAddressOf());
    //render->m_pImmediateContext.Get()->PSSetShader(render->m_pPixelShader.Get(), nullptr, 0);
    //render->m_pImmediateContext.Get()->PSSetConstantBuffers(0, 1, render->m_pConstantBuffer.GetAddressOf());
    //render->m_pImmediateContext.Get()->DrawIndexed(36, 0, 0);

    //// Present the scene
    //render->m_pSwapChain.Get()->Present(0, 0);
}
