#pragma once
#include "..\..\pch.h"
#include "DirectX11_Device.h"
#include <memory>


class DirectXRender
{
public:
    DirectXRender();
    DirectXRender(std::unique_ptr<DirectX11_Device> device);
    ~DirectXRender();

    /* Name: Draw()
    Params: IMeshObject
    Returns: Void
    Info: Draws the object to the screen. 
    */
    void Draw(std::shared_ptr<IMeshObject> mesh);
private:
    Microsoft::WRL::ComPtr<DirectX11_Device> m_pDevice;
    Microsoft::WRL::ComPtr<IDXGISwapChain> m_pSwapChain;
    //TODO: We want to set up where this class only holds references to the objects from DirectX_Device. This object will be passed into the Render() of each IObjects.
    // Also, I may want to think about putting all my shader objects into a specific class whereby I can then call them from a class. ShaderClass->PixelShader() for example. 
    // In the end, I want this class to store the objects we'll need to use only for rendering, this should make the object itself small. In face we shouldn't have a "Device" reference. 
    // Think about removing. Then we pass this class into a IObject's Draw() and that IObject will have Shader's it will use from the IShader class. 
};

