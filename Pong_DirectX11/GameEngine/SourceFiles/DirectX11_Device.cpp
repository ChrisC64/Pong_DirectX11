#include "..\HeaderFiles\DirectX11_Device.h"
using namespace Microsoft::WRL;
using namespace DirectX;

DirectX11_Device::DirectX11_Device() : m_HWnd(0),
m_bVsync(false),
m_pD3dDevice(NULL),
m_pD3dImmediateContext(0),
m_pSwapChain(0),
m_pBackBuffer(0),
m_pRenderTargetView(0),
m_pVertexBuffer(0),
m_pVertexLayout(0),
m_pPosColorBuffer(0),
m_pConstantBuffer(nullptr),
m_pSwapChain1(0),
m_ScreenHeight(0),
m_ScreenWidth(0),
m_pPixelShaderSolid(0),
m_pD3dImmediateContext1(0)
{
    m_Color[0] = 0.0f;
    m_Color[1] = 0.2f;
    m_Color[2] = 0.4f;
    m_Color[3] = 1.0f;
    m_Cube = Cube();
}


DirectX11_Device::~DirectX11_Device()
{
    Shutdown();
}

ID3D11DeviceContext * DirectX11_Device::GetDeviceContext()
{
    return nullptr;
}

ID3D11RenderTargetView * DirectX11_Device::GetRenderTargetView()
{
    return nullptr;
}

ID3D11Device * DirectX11_Device::GetDevice()
{
    return nullptr;
}

IDXGISwapChain * DirectX11_Device::GetSwapChain()
{
    return nullptr;
}

HWND * DirectX11_Device::GetHWND()
{
    return nullptr;
}

bool DirectX11_Device::InitDevice(const int SCREEN_WIDTH, const int SCREEN_HEIGHT, HWND hWnd, bool isFullScreen)
{
    TRACE(L"Init Device called!\n");
    m_HWnd = hWnd;
    // Relies on device being created to check MSAA, should not createDeviceAndSwapChain below, instead create device, then set up SwapChain
    HRESULT hr;
    UINT creationFlags = 0;
#ifdef _DEBUG
    creationFlags = D3D11_CREATE_DEVICE_DEBUG;
#elif 
    creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#endif

    D3D_DRIVER_TYPE driverTypes[] =
    {
        D3D_DRIVER_TYPE_HARDWARE,
        D3D_DRIVER_TYPE_WARP,
        D3D_DRIVER_TYPE_SOFTWARE
    };

    UINT numDriverTypes = ARRAYSIZE(driverTypes);

    // Set up Feature Level Desc array
    D3D_FEATURE_LEVEL featureLevels[] =
    {
        D3D_FEATURE_LEVEL_11_1,
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
        D3D_FEATURE_LEVEL_9_3,
        D3D_FEATURE_LEVEL_9_2,
        D3D_FEATURE_LEVEL_9_1
    };
    UINT numFeatureLevels = ARRAYSIZE(featureLevels);
    
    // Create a device - not device and swapchain
    for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
    {
        // Create the device now
        hr = D3D11CreateDevice(
            nullptr,                                            // IDXGI Adapter
            driverTypes[driverTypeIndex],                       // D3D Driver type: Use hardware
            nullptr,                                            // HMODULE: handle to DLL software rasterizer
            creationFlags,                                      // HMODULE Software
            featureLevels,                                      // Feature Levels
            numFeatureLevels,                                   // number of feature levels
            D3D11_SDK_VERSION,                                  // SDK Version
            m_pD3dDevice.GetAddressOf(),                        // pointer to the device
            &m_FeatureLevel,                                    // selected feature level type
            m_pD3dImmediateContext.GetAddressOf()               // Immediate context
        );

        if (hr == E_INVALIDARG) {
            TRACE(L"INVALID, Trying to create the device again\n");
            // D3D_FEATURE_LEVEL_11_1 is not supported
            hr = D3D11CreateDevice(
                nullptr,                                            // IDXGI Adapter
                driverTypes[driverTypeIndex],                       // D3D Driver type: Use hardware
                nullptr,                                            // HMODULE: handle to DLL software rasterizer
                creationFlags,                                      // HMODULE Software
                featureLevels,                                      // Feature Levels
                numFeatureLevels - 1,                               // number of feature levels
                D3D11_SDK_VERSION,                                  // SDK Version
                m_pD3dDevice.GetAddressOf(),                        // pointer to the device
                &m_FeatureLevel,                                    // selected feature level type
                m_pD3dImmediateContext.GetAddressOf()               // Immediate context
            );
        }

        if (SUCCEEDED(hr))
            break;
    }

    if (FAILED(hr))
    {
#if defined(_DEBUG)
        TRACE(L"Failed to create device. Devie creation failure\n");
#endif
        MessageBox(m_HWnd, L"Failed to Create Device", L"Device Creation Failed", MB_ICONERROR);
        return false;
        throw(hr);
    }

    //Find Screen size
    RECT rc;
    GetClientRect(m_HWnd, &rc);
    m_ScreenWidth = rc.right - rc.left;
    m_ScreenHeight = rc.bottom - rc.top;
    
    if (!CreateSwapChain())
        return false;
    if (FAILED(hr))
        return false;

    SetViewPort(m_ScreenWidth, m_ScreenHeight);
    
    //Compile Shaders
    TRACE(L"Compiling shaders...\n");
    hr = CompileShaders();
    if (FAILED(hr))
    {
        TRACE(L"Failed to compile shaders\n");
        return false;
    }
    hr = InitRenderTarget();
    if (FAILED(hr))
    {
        TRACE(L"Failed to initialize Render Target\n");
        return false;
    }
    hr = CreateInputLayout();
    if (FAILED(hr))
    {
        TRACE(L"Failed to create input layout\n");
        return false;
    }
    hr = InitVertBuffer();
    if (FAILED(hr))
    {
        TRACE(L"Failed to intialize vertex buffer\n");
        return false;
    }
    hr = InitConstantBuffer();
    if (FAILED(hr))
    {
        TRACE(L"Failed to initialize constant buffer\n");
        return false;
    }
    hr = CreateTexture2DDesc();
    if (FAILED(hr))
    {
        TRACE(L"Failed to create Texture2D and Depth Stencil buffers for device");
        return false;
    }
    // Set up world
    InitWorldMatrix();
#ifdef _DEBUG
    if (FAILED(CreateDebugDevice()))
    {
        TRACE(L"Failed to create debug device\n");
    }
#endif
    return true;
}

HRESULT DirectX11_Device::InitRenderTarget()
{
    TRACE(L"Creating render target\n");
    HRESULT hr;
    // Create Back Buffer
    ComPtr<ID3D11Texture2D> pBackBuffer = nullptr;
    hr = m_pSwapChain.Get()->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(pBackBuffer.GetAddressOf()));
    if (FAILED(hr))
        return hr;

    // Create Render Target View
    hr = m_pD3dDevice.Get()->CreateRenderTargetView(pBackBuffer.Get(), nullptr, m_pRenderTargetView.GetAddressOf());
    pBackBuffer.Reset();
    if (FAILED(hr))
        return hr;
    m_pD3dImmediateContext.Get()->OMSetRenderTargets(1, m_pRenderTargetView.GetAddressOf(), nullptr);

    return S_OK;
}

void DirectX11_Device::SetViewPort(int width, int height)
{
    TRACE(L"Setting up viewport\n");
    // Setup the viewport
    D3D11_VIEWPORT vp;
    vp.Width = (FLOAT)width;
    vp.Height = (FLOAT)height;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;

    m_pD3dImmediateContext.Get()->RSSetViewports(1, &vp);
}

void DirectX11_Device::Render()
{
    // Update our time
    static float t = 0.0f;
    static ULONGLONG timeStart = 0;
    ULONGLONG timeCur = GetTickCount64();
    if (timeStart == 0)
        timeStart = timeCur;
    t = (timeCur - timeStart) / 1000.0f;
    // Rotate object
    m_World = XMMatrixRotationY(t);
    
    // Set up lighting parameters
    XMFLOAT4 vLightDirs[2] =
    {
        XMFLOAT4(-0.577f, 0.577f, -0.577f, 1.0f),
        XMFLOAT4(0.0f, 0.0f, -1.0f, 1.0f),
    };
    XMFLOAT4 vLightColors[2] =
    {
        XMFLOAT4(0.10f, 0.50f, 0.25f, 1.0f),
        XMFLOAT4(0.5f, 0.0f, 0.5f, 1.0f)
    };

    // Rotate the second light around the origin
    XMMATRIX mRotate = XMMatrixRotationY(-2.0f * t);
    XMVECTOR vLightDir = XMLoadFloat4(&vLightDirs[1]);
    vLightDir = XMVector3Transform(vLightDir, mRotate);
    XMStoreFloat4(&vLightDirs[1], vLightDir);

    // Matrices used for spinning, orbiting, translating, and scaling the two cubes we'll be presenting
    /*XMMATRIX mSpin = XMMatrixRotationZ(-t);
    XMMATRIX mOrbit = XMMatrixRotationY(-t * 2.0f);
    XMMATRIX mTranslate = XMMatrixTranslation(-4.0f, 0.0f, 0.0f);
    XMMATRIX mScale = XMMatrixScaling(0.3f, 0.3f, 0.3f);*/
    
    /*m_World2 = mScale * mSpin * mTranslate * mOrbit;*/
    // Clear the back buffer
    m_pD3dImmediateContext.Get()->ClearRenderTargetView(m_pRenderTargetView.Get(), DirectX::Colors::MidnightBlue);
    // Clear the depth buffer
    m_pD3dImmediateContext.Get()->ClearDepthStencilView(m_pDepthStencilView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);
    
    // Update Constant Buffer (First Cube)
    ConstantBuffer cb;
    cb.world = XMMatrixTranspose(m_World);
    cb.view = XMMatrixTranspose(m_View);
    cb.proj = XMMatrixTranspose(m_Projection);
    cb.vLightDir[0] = vLightDirs[0];
    cb.vLightDir[1] = vLightDirs[1];
    cb.vLightColor[0] = vLightColors[0];
    cb.vLightColor[1] = vLightColors[1];
    cb.vOutputColor = XMFLOAT4(0, 0, 0, 0);
    m_pD3dImmediateContext.Get()->UpdateSubresource(m_pConstantBuffer.Get(), 0, nullptr, &cb, 0, 0);

    // Render Object (First cube)
    m_pD3dImmediateContext.Get()->VSSetShader(m_pVertexShader.Get(), nullptr, 0);
    m_pD3dImmediateContext.Get()->VSSetConstantBuffers(0, 1, m_pConstantBuffer.GetAddressOf());
    m_pD3dImmediateContext.Get()->PSSetShader(m_pPixelShader.Get(), nullptr, 0);
    m_pD3dImmediateContext.Get()->PSSetConstantBuffers(0, 1, m_pConstantBuffer.GetAddressOf());
    m_pD3dImmediateContext.Get()->DrawIndexed(36, 0, 0);

    // Draw second cube
    //ConstantBuffer cb2;
    //cb2.world = XMMatrixTranspose(m_World2);
    //cb2.view = XMMatrixTranspose(m_View);
    //cb2.proj = XMMatrixTranspose(m_Projection);
    //m_pD3dImmediateContext.Get()->UpdateSubresource(m_pConstantBuffer.Get(), 0, nullptr, &cb2, 0, 0);
    //// Render cube
    //m_pD3dImmediateContext.Get()->DrawIndexed(36, 0, 0);

    // Render each light (CPU work)
    for (int m = 0; m < 2; m++)
    {
        XMMATRIX mLight = XMMatrixTranslationFromVector(5.0f * XMLoadFloat4(&vLightDirs[m]));
        XMMATRIX mLightScale = XMMatrixScaling(0.2f, 0.2f, 0.2f);
        mLight = mLightScale * mLight;

        // Update the world variable to reflect the current light
        cb.world = XMMatrixTranspose(mLight);
        cb.vOutputColor = vLightColors[m];
        m_pD3dImmediateContext.Get()->UpdateSubresource(m_pConstantBuffer.Get(), 0, nullptr, &cb, 0, 0);

        m_pD3dImmediateContext.Get()->PSSetShader(m_pPixelShaderSolid.Get(), nullptr, 0);
        m_pD3dImmediateContext.Get()->DrawIndexed(36, 0, 0);
    }

    // Present the scene
    m_pSwapChain.Get()->Present(0, 0);
}

HRESULT DirectX11_Device::CreateDepthStencilView()
{
    if (!m_pD3dDevice || !m_pD3dImmediateContext)
    {
        TRACE(L"Device or Context is not set, cannot create depth stencil view");
        return E_FAIL;
    }
    /*HRESULT hr;
    D3D11_DEPTH_STENCIL_VIEW_DESC dsv;
    ZeroMemory(&dsv, sizeof(dsv));
    dsv.Format = descDepth.Format;
    dsv.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
    dsv.Texture2D.MipSlice = 0;*/
    return E_NOTIMPL;
}

HRESULT DirectX11_Device::CompileFile(WCHAR * fileName, LPCSTR entryPoint, LPCSTR shaderModel, ID3DBlob ** ppBlobOut)
{
    HRESULT hr;
    DWORD dwShaderFlag = D3DCOMPILE_ENABLE_STRICTNESS;

#ifdef _DEBUG
    dwShaderFlag |= D3DCOMPILE_DEBUG;
    dwShaderFlag |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif 
    ComPtr<ID3DBlob> pErrorBlob;

    hr = D3DCompileFromFile(fileName, nullptr, nullptr, entryPoint, shaderModel, dwShaderFlag, 0, ppBlobOut, &pErrorBlob);

    if (FAILED(hr))
    {
       if (pErrorBlob)
        {
            OutputDebugStringA(reinterpret_cast<const char*>(pErrorBlob->GetBufferPointer()));
            pErrorBlob.Reset();
            return hr;
        }
    }

    if (pErrorBlob)
    {
        pErrorBlob.Reset();
    }

    return S_OK;
}

HRESULT DirectX11_Device::CompileShaders()
{
    if (!m_pD3dDevice)
    {
        TRACE(L"No Device found!\n");
        return E_FAIL;
    }

    HRESULT hr;
    LPCSTR profile = "vs_5_0";
    hr = CompileFile(L"VertexShader.hlsl", "VS", profile, m_pVSBlob.GetAddressOf());
    if (FAILED(hr))
    {
        //Release blob
        TRACE(L"Failed to compile Vertex Shader\n");
        m_pVSBlob.Reset();
        return hr;
    }

    // Create the Vertex Shader
    hr = m_pD3dDevice.Get()->CreateVertexShader(m_pVSBlob.Get()->GetBufferPointer(), m_pVSBlob.Get()->GetBufferSize(), nullptr, m_pVertexShader.GetAddressOf());

    if (FAILED(hr))
    {
        //Failed to create VS
        TRACE(L"Failed to create vertex shader with device\n");
        m_pVSBlob.Reset();
        return hr;
    }

    profile = "ps_5_0";
    hr = CompileFile(L"PixelShader.hlsl", "PS", profile, m_pPSBlob.GetAddressOf());

    if (FAILED(hr))
    {
        TRACE(L"Failed to compile PS\n");
        m_pPSBlob.Reset();
        return hr;
    }

    hr = m_pD3dDevice.Get()->CreatePixelShader(m_pPSBlob.Get()->GetBufferPointer(), m_pPSBlob.Get()->GetBufferSize(), nullptr, m_pPixelShader.GetAddressOf());

    if (FAILED(hr))
    {
        TRACE(L"Failed to create PS\n");
        m_pPSBlob.Reset();
        return hr;
    }

    // NEW PIXEL SHADER SOLID //
    profile = "ps_5_0";
    hr = CompileFile(L"PixelShader.hlsl", "PSSolid", profile, m_pPSBlob.GetAddressOf());

    if (FAILED(hr))
    {
        TRACE(L"Failed to compile PSSolid\n");
        m_pPSBlob.Reset();
        return hr;
    }

    hr = m_pD3dDevice.Get()->CreatePixelShader(m_pPSBlob.Get()->GetBufferPointer(), m_pPSBlob.Get()->GetBufferSize(), nullptr, m_pPixelShaderSolid.GetAddressOf());

    if (FAILED(hr))
    {
        TRACE(L"Failed to create PSSolid\n");
        m_pPSBlob.Reset();
        return hr;
    }


    // Set primitive topology
    m_pD3dImmediateContext.Get()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    return S_OK;
}

HRESULT DirectX11_Device::SetSwapChainDesc()
{
    return E_NOTIMPL;
}

HRESULT DirectX11_Device::InitVertBuffer()
{
    if (!m_pD3dDevice || !m_pD3dImmediateContext)
        return E_FAIL;
    HRESULT hr;
    // Create Vertex buffer
    D3D11_BUFFER_DESC bd;
    ZeroMemory(&bd, sizeof(bd));
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = m_Cube.GetVertexListByteWidth();
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bd.CPUAccessFlags = 0;
    // Initialize subresource - Location of data
    D3D11_SUBRESOURCE_DATA InitData;
    ZeroMemory(&InitData, sizeof(InitData));
    InitData.pSysMem = m_Cube.GetVertexLayoutAddress();
    // Create buffer
    hr = m_pD3dDevice.Get()->CreateBuffer(&bd, &InitData, m_pVertexBuffer.GetAddressOf());
    if (FAILED(hr))
    {
        TRACE(L"Failed to Create Vertex Buffer\n");
        return hr;
    }
    // Set vertex buffer
    UINT stride = sizeof(GameStruct::DataStructs::VertexLayout);
    UINT offset = 0;
    m_pD3dImmediateContext.Get()->IASetVertexBuffers(0, 1, m_pVertexBuffer.GetAddressOf(), &stride, &offset);

    // CREATE INDEX BUFFER //
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = m_Cube.GetIndexListByteWidth();
    bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
    bd.CPUAccessFlags = 0;
    InitData.pSysMem = m_Cube.m_IndexList;
    hr = m_pD3dDevice.Get()->CreateBuffer(&bd, &InitData, m_pIndexBuffer.GetAddressOf());
    if (FAILED(hr))
        return hr;
    // Set index buffer
    m_pD3dImmediateContext.Get()->IASetIndexBuffer(m_pIndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);
    return S_OK;
}

HRESULT DirectX11_Device::InitIndexBuffer()
{
    if (!m_pD3dDevice || !m_pD3dImmediateContext)
        return E_FAIL;

    // Create Vertex buffer
    D3D11_BUFFER_DESC bd;
    ZeroMemory(&bd, sizeof(bd));

    // Create index buffer
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = m_Cube.GetIndexListByteWidth();
    bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
    bd.CPUAccessFlags = 0;

    D3D11_SUBRESOURCE_DATA InitData;
    ZeroMemory(&InitData, sizeof(InitData));
    InitData.pSysMem = m_Cube.m_IndexList;

    HRESULT hr = m_pD3dDevice.Get()->CreateBuffer(&bd, &InitData, m_pIndexBuffer.GetAddressOf());
    if (FAILED(hr))
    {
        TRACE(L"Failed to create Index buffer");
        return hr;
    }
    // Set index buffer
    m_pD3dImmediateContext.Get()->IASetIndexBuffer(m_pIndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);
    return S_OK;
}

HRESULT DirectX11_Device::InitConstantBuffer()
{
    if (!m_pD3dDevice)
        return E_FAIL;
    HRESULT hr;
    D3D11_BUFFER_DESC bd;
    ZeroMemory(&bd, sizeof(bd));
    // Create the constant buffer
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = sizeof(ConstantBuffer);
    bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    bd.CPUAccessFlags = 0;
    hr = m_pD3dDevice.Get()->CreateBuffer(&bd, nullptr, m_pConstantBuffer.GetAddressOf());
    if (FAILED(hr))
        return hr;
    return S_OK;
}

void DirectX11_Device::SetRasterState()
{
}

bool DirectX11_Device::CreateSwapChain()
{
    HRESULT hr;
    // Obtain DXGI Factory since we used NULL for above
    ComPtr<IDXGIFactory1> dxgiFactory = nullptr;
    ComPtr<IDXGIDevice> dxgiDevice = nullptr;
    TRACE(L"Obtaining DXGI Factory\n");
    hr = m_pD3dDevice.As(&dxgiDevice);
    if (SUCCEEDED(hr))
    {
        // Get Adapter - Display Sub-system - of the device (graphics card or motherboard, may vary on device)
        IDXGIAdapter* adapter = nullptr;
        hr = dxgiDevice->GetAdapter(&adapter);
        if (SUCCEEDED(hr))
        {
            hr = adapter->GetParent(__uuidof(IDXGIFactory1), reinterpret_cast<void**>(dxgiFactory.GetAddressOf()));
            adapter->Release();
        }
        dxgiDevice.Reset();
    }
    if (FAILED(hr))
        return false;

    // Create swap chain
    ComPtr<IDXGIFactory2> dxgiFactory2 = nullptr;
    TRACE(L"Creating swap chain\n");

    hr = dxgiFactory.As(&dxgiFactory2);
    if (dxgiFactory2)
    {
        TRACE(L"DirectX 11.1 or later device detected!\n");
        // DirectX 11.1 or later
        hr = m_pD3dDevice.Get()->QueryInterface(__uuidof(ID3D11Device1), reinterpret_cast<void**>(m_pDxDevice1.GetAddressOf()));
        if (SUCCEEDED(hr))
        {
            m_pD3dImmediateContext.As(&m_pD3dImmediateContext1);
        }

        DXGI_SWAP_CHAIN_DESC1 sd;
        ZeroMemory(&sd, sizeof(sd));
        sd.Width = m_ScreenWidth;
        sd.Height = m_ScreenHeight;
        sd.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        sd.SampleDesc.Count = 1;
        sd.SampleDesc.Quality = 0;
        sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        sd.BufferCount = 1;

        hr = dxgiFactory2.Get()->CreateSwapChainForHwnd(m_pD3dDevice.Get(), m_HWnd, &sd, nullptr, nullptr, m_pSwapChain1.GetAddressOf());
        if (SUCCEEDED(hr))
        {
            hr = m_pSwapChain1.As(&m_pSwapChain);
        }
        dxgiFactory2.Reset();
    }
    else
    {
        TRACE(L"DirectX 11.0 device detected!\n");
        // DirectX 11.0 systems
        DXGI_SWAP_CHAIN_DESC sd;
        ZeroMemory(&sd, sizeof(sd));
        sd.BufferCount = 1;
        sd.BufferDesc.Width = m_ScreenWidth;
        sd.BufferDesc.Height = m_ScreenHeight;
        sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        sd.BufferDesc.RefreshRate.Numerator = 60;
        sd.BufferDesc.RefreshRate.Denominator = 1;
        sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        sd.OutputWindow = m_HWnd;
        sd.SampleDesc.Count = 1;
        sd.SampleDesc.Quality = 0;
        sd.Windowed = TRUE;

        hr = dxgiFactory->CreateSwapChain(m_pD3dDevice.Get(), &sd, &m_pSwapChain);
    }

    //dxgiFactory->MakeWindowAssociation(m_HWnd, DXGI_MWA_NO_ALT_ENTER);
    if (dxgiFactory)
        dxgiFactory.Reset();
    return true;
}

void DirectX11_Device::Shutdown()
{
    if (m_pD3dImmediateContext) { m_pD3dImmediateContext.Get()->ClearState(); }
    m_pBackBuffer.Reset();
    m_pConstantBuffer.Reset();
    m_pDepthStencilBuffer.Reset();
    m_pDepthStencilView.Reset();
    m_pTexture2D.Reset();
    m_pErrorMsgBlob.Reset();
    m_pIndexBuffer.Reset();
    m_pVertexLayout.Reset();
    m_pPixelShader.Reset();
    m_pPixelShaderSolid.Reset();
    m_pVertexShader.Reset();
    m_pPosColorBuffer.Reset();
    m_pPSBlob.Reset();
    m_pRenderTargetView.Reset();
    m_pSwapChain.Reset();
    m_pSwapChain1.Reset();
    m_pVertexBuffer.Reset();
    m_pVSBlob.Reset();
    m_pD3dImmediateContext.Reset();
    m_pD3dImmediateContext1.Reset();
//#ifdef _DEBUG
//    HRESULT hr;
//    hr = m_pDebug.Get()->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);
//    if (FAILED(hr))
//        TRACE(L"Failed to report live objects");
//    m_pDebug.Reset();
//#endif
    m_pD3dDevice.Reset();
    m_pDxDevice1.Reset();
}

DXGI_SWAP_CHAIN_DESC DirectX11_Device::CreateSwapChainDesc()
{
    DXGI_SWAP_CHAIN_DESC swapChainDesc;
    //Zero memory
    ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));

    HRESULT hr;
    //Find Screen size
    RECT rc;
    GetClientRect(m_HWnd, &rc);
    UINT width = rc.right - rc.left;
    UINT height = rc.bottom - rc.top;

    UINT msaaQuality = 1;
    //UINT sample;
    if (m_pD3dDevice)
    {
        if (m_pD3dDevice)
        {
            for (UINT sampleCount = 1; sampleCount < D3D11_MAX_MULTISAMPLE_SAMPLE_COUNT; sampleCount++)
            {
                hr = m_pD3dDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, sampleCount, &msaaQuality);
                if (hr != S_OK)
                {
#if defined(_DEBUG)
                    TRACE(L"Do not use this one...\n");
#endif 
                }
                if (hr == S_OK)
                {
#if defined(_DEBUG)
                    //TRACE(L"Sample count %s MSAA Quality %s \n", sampleCount, msaaQuality);
#endif

                    std::cout << "Sample count: " << sampleCount << " MaxQualty: " << msaaQuality << std::endl;
                }
            }
        }
    }

    // Set the swap chain structure
    swapChainDesc.BufferCount = 1;                                   // Size of back buffer
    swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;    // Set the display buffer format (32 bit format)
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;     // Use the surface or resource as an output render only
    swapChainDesc.OutputWindow = m_HWnd;                              // Handler to the window that will be used
    swapChainDesc.SampleDesc.Count = 8;                              // How many multi samples to use
    swapChainDesc.SampleDesc.Quality = 0;
    swapChainDesc.Windowed = true;                                   // Window mode
    swapChainDesc.BufferDesc.Width = width;                          // Back buffer width
    swapChainDesc.BufferDesc.Height = height;                        // Backk buffer height
    swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;    // Allow full-screen switching
    swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;             // Refresh Rate top
    swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;            // Refresh Rate Bottom 60 / 1 = 60FPS

    return swapChainDesc;
}

HRESULT DirectX11_Device::CreateInputLayout()
{
    if (!m_pD3dDevice || !m_pD3dImmediateContext)
        return E_FAIL;
    HRESULT hr;
    //Set Vertex Input Layout
    /*D3D11_INPUT_ELEMENT_DESC vertDesc[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
    };*/

    D3D11_INPUT_ELEMENT_DESC vertDesc[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
    };

    UINT numElements = ARRAYSIZE(vertDesc);
    // Create Inputlayout
    hr = m_pD3dDevice->CreateInputLayout(vertDesc, numElements, m_pVSBlob.Get()->GetBufferPointer(), m_pVSBlob.Get()->GetBufferSize(), m_pVertexLayout.GetAddressOf());

    if (FAILED(hr))
    {
        TRACE(L"Failed to create Input Layout\n");
        MessageBox(m_HWnd, L"Failed to create Input Layout", L"Input Layout Create Failed", MB_ICONERROR);
        return hr;
    }
    // Set Input Layout
    m_pD3dImmediateContext->IASetInputLayout(m_pVertexLayout.Get());

    return S_OK;
}

void DirectX11_Device::InitWorldMatrix()
{
    // Initialize World Matrix
    m_World = XMMatrixIdentity();
    m_World2 = XMMatrixIdentity();
    XMVECTOR Eye = XMVectorSet(0.0f, 4.0f, -10.0f, 0.0f);
    XMVECTOR At = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
    XMVECTOR Up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

    m_View = XMMatrixLookAtLH(Eye, At, Up);
    // Initialize Projection Matrix
    m_Projection = XMMatrixPerspectiveFovLH(XM_PIDIV2, m_ScreenWidth / (FLOAT)m_ScreenHeight, 0.01f, 100.0f);
}

HRESULT DirectX11_Device::CreateTexture2DDesc()
{
    if (!m_pD3dDevice)
        return E_FAIL;
    HRESULT hr;
    D3D11_TEXTURE2D_DESC texDesc;
    ZeroMemory(&texDesc, sizeof(texDesc));
    texDesc.Width = m_ScreenWidth;
    texDesc.Height = m_ScreenHeight;
    texDesc.MipLevels = 1;
    texDesc.ArraySize = 1;
    texDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    texDesc.SampleDesc.Count = 1;
    texDesc.SampleDesc.Quality = 0;
    texDesc.Usage = D3D11_USAGE_DEFAULT;
    texDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    texDesc.CPUAccessFlags = 0;
    texDesc.MiscFlags = 0;
    hr = m_pD3dDevice.Get()->CreateTexture2D(&texDesc, nullptr, m_pDepthStencilBuffer.GetAddressOf());
    if (FAILED(hr))
    {
        TRACE(L"Failed to create Texture2D\n");
        return hr;
    }
    D3D11_DEPTH_STENCIL_VIEW_DESC dsv;
    ZeroMemory(&dsv, sizeof(dsv));
    dsv.Format = texDesc.Format;
    dsv.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
    dsv.Texture2D.MipSlice = 0;
    hr = m_pD3dDevice.Get()->CreateDepthStencilView(m_pDepthStencilBuffer.Get(), &dsv, m_pDepthStencilView.GetAddressOf());
    if (FAILED(hr))
    {
        TRACE(L"Failed to create depth stencil view\n");
        return hr;
    }
    m_pD3dImmediateContext.Get()->OMSetRenderTargets(1, m_pRenderTargetView.GetAddressOf(), m_pDepthStencilView.Get());
    return hr;
}

HRESULT DirectX11_Device::CreateDebugDevice()
{
    if (!m_pD3dDevice)
        return E_FAIL;
    HRESULT hr = m_pD3dDevice.As(&m_pDebug);
    return hr;
}

Microsoft::WRL::ComPtr<ID3D11DeviceContext> DirectX11_Device::GetImmediateContext()
{
    return m_pD3dImmediateContext;
}
