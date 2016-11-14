#pragma once
#include "..\..\pch.h"
#ifdef _DEBUG
#include <Windows.h>
#define TRACE(x) OutputDebugString(x)
#endif _DEBUG

#include "..\..\Actors\HeaderFiles\Cube.h"

// Add libraries //
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "Dxgi.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "d3dcompiler.lib")

#define ASSERT(x) {(x > 0) ? true : false;}
#define SAFE_RELEASE(x) if(x){x.Get()->Release(); x = nullptr;}

class DirectX11_Device
{
private:

    struct SimpleVertex
    {
        DirectX::XMFLOAT3 Pos;
        DirectX::XMFLOAT3 Normal;

    };

    Cube m_Cube; // Test object

    // Window Variables //
    HWND                    m_HWnd;          // Handler to the window
    bool                    m_bVsync;        // Boolean for vertical syncing
    UINT                    m_ScreenWidth;   // Width of the Screen
    UINT                    m_ScreenHeight;  // Height of screen

    // MATRICES
    DirectX::XMMATRIX m_World;
    DirectX::XMMATRIX m_World2;
    DirectX::XMMATRIX m_View;
    DirectX::XMMATRIX m_Projection;

    // Direct3D Variables // 
    Microsoft::WRL::ComPtr<ID3D11Device>           m_pD3dDevice;    // Pointer to the D3D Device
    Microsoft::WRL::ComPtr<ID3D11Device1>          m_pDxDevice1;    // Pointer to the DxDevice1 (DirectX 11.1 or greater)
    Microsoft::WRL::ComPtr<ID3D11DeviceContext>    m_pD3dImmediateContext;// Pointer to the D3D Device Context; Device Context manages the GPU Pipeline for rendering graphics and determining how they will be rendered
    Microsoft::WRL::ComPtr<ID3D11DeviceContext1>   m_pD3dImmediateContext1;
    Microsoft::WRL::ComPtr<IDXGISwapChain>         m_pSwapChain;    // Pointer to the Swap Chain buffer
    Microsoft::WRL::ComPtr<IDXGISwapChain1>        m_pSwapChain1;

#ifdef _DEBUG
    Microsoft::WRL::ComPtr<ID3D11Debug>           m_pDebug; // Debug device
#endif 
    
    // Video buffers //
    Microsoft::WRL::ComPtr<ID3D11Texture2D>        m_pBackBuffer;
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_pRenderTargetView;

    // Textures //
    Microsoft::WRL::ComPtr<ID3D11Texture2D>        m_pDepthStencilBuffer;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_pDepthStencilView;
    Microsoft::WRL::ComPtr<ID3D11Texture2D>        m_pTexture2D;

    // BUffers //
    Microsoft::WRL::ComPtr<ID3D11Buffer>           m_pVertexBuffer;
    Microsoft::WRL::ComPtr<ID3D11Buffer>           m_pPosColorBuffer;
    Microsoft::WRL::ComPtr<ID3D11Buffer>           m_pIndexBuffer;
    Microsoft::WRL::ComPtr<ID3D11Buffer>           m_pConstantBuffer;

    // Input Layout //
    Microsoft::WRL::ComPtr<ID3D11InputLayout>      m_pVertexLayout;
    // Feature Level
    D3D_FEATURE_LEVEL                              m_FeatureLevel;         // Feature level support
    // Compiler Items //
    Microsoft::WRL::ComPtr<ID3DBlob>               m_pVSBlob;
    Microsoft::WRL::ComPtr<ID3DBlob>               m_pPSBlob;
    Microsoft::WRL::ComPtr<ID3DBlob>               m_pErrorMsgBlob;
    Microsoft::WRL::ComPtr<ID3D11PixelShader>      m_pPixelShader;
    Microsoft::WRL::ComPtr<ID3D11PixelShader>      m_pPixelShaderSolid;
    Microsoft::WRL::ComPtr<ID3D11VertexShader>     m_pVertexShader;

    // Color //
    float                   m_Color[4];

    // Booleans //
    bool                    m_bIsPaused;       // Pause application

    // Temp Use for practice //
    DirectX::XMMATRIX m_ScaleMat;
    DirectX::XMMATRIX m_TranslationMat;
    DirectX::XMMATRIX m_RotationMat;

    // POS and COLOR struct //
    struct VertexPC
    {
        DirectX::XMFLOAT3 pos;
        DirectX::XMFLOAT4 color;
    };

    struct Vertex2
    {
        DirectX::XMFLOAT3 pos;
        DirectX::XMFLOAT3 normal;
        DirectX::XMFLOAT2 Tex0;
        DirectX::XMFLOAT2 Tex1;
    };

    struct ConstantBuffer
    {
        DirectX::XMMATRIX world;
        DirectX::XMMATRIX view;
        DirectX::XMMATRIX proj;
        DirectX::XMFLOAT4 vLightDir[2];
        DirectX::XMFLOAT4 vLightColor[2];
        DirectX::XMFLOAT4 vOutputColor;
    };
public:
    DirectX11_Device();
    ~DirectX11_Device();

    // GET METHODS //
    ID3D11DeviceContext* GetDeviceContext();
    ID3D11RenderTargetView* GetRenderTargetView();
    ID3D11Device* GetDevice();
    IDXGISwapChain* GetSwapChain();
    HWND* GetHWND();

    /* Name: InitDevice(HWND hwnd)
    Params: Hwnd (Handler to window)
    Return: HRESULT
    Info: This function is used to initalize and set up our D3D Device
    */
    bool InitDevice(const int SCREEN_WIDTH, const int SCREEN_HEIGHT, HWND hWnd, bool isFullScreen);

    /* Name: InitRenderTarget()
    Param: Void
    Return: HRESULT
    Info: To keep things clean, initialize the buffer and scene in this function
    while being called within the class only.
    */
    HRESULT InitRenderTarget();

    /* Name: SetViewPort(int width, int height)
    Param: Int width, Int Height
    Return: void
    Info: Set the viewport for display. Take in Width and Height in pixels
    */
    void SetViewPort(int width, int height);

    /* Name: Render(float dt)
    Param: float deltaTime
    Return: void
    Info: Render a frame
    */
    void Render();

    /*  Name: CreateDepthStencilView()
    Param: Void
    Retrn: HRESULT
    Info: Init and set up the Depth Stencil buffer device
    */
    HRESULT CreateDepthStencilView();

    /*  Name: CompileFile
    Param: WCHAR*, LPCSTR, LPCSTR, ID3DBlob**
    Return: HRESULT
    Info: Enable us to compile the necessary shader files in a contained function
    versus making the various calls in other places of the code.
    */
    HRESULT CompileFile(WCHAR* fileName, LPCSTR entryPoint, LPCSTR shaderModel, ID3DBlob** ppBlobOut);

    /*  Name: CompileShaders
    Param: void
    Return: bool
    Info: Here we'll compile the shader files we have currently.
    */
    HRESULT CompileShaders();

    /*  Name: InitSwapChain()
    Param: Void
    Info: Set up the Swap Chain Description in this function. Helps keep code a little neater.
    */
    HRESULT SetSwapChainDesc();

    /*  Name: CalcFps()
    Param: Void
    Info: Calculate the Frames per second
    */
    //void CalcFps();

    /*  Name: InitVertBuffer
    Param: Void
    Info: Initialize D3DApp's vertex buffer for displaying our 3D Object
    */
    HRESULT InitVertBuffer();

    /*  Name: InitIndexBuffer
    Param: void
    Info: Initialize our D3DApp's index buffer
    */
    HRESULT InitIndexBuffer();

    /*  Name: InitWorldMatrix
    Param: void
    Info: This is going to set our Matrices used for our world, lookAt, Eye, Up, view, and Projection.
    */
    //void InitWorldMatrix();

    /*  Name: InitConstantBuffer
    Param: void
    Info: Initialize the constant buffer that will be used for our world, view, and proj matrices.
    */
    HRESULT InitConstantBuffer();

    /*  Name: SetRasterizerState()
    Param: void
    Info: Set the Rasterizer description for the device.
    */
    void SetRasterState();

    /*Name: CreateSwapChain();
    Param: void
    Return: boolean - isSuccessful
    Info: Set up the swap chain in our InitDevice();
    */
    bool CreateSwapChain();

    /* Name: Shutdown(void)
    Paras: void
    Return: void
    Info: Release all COM objects and free up memory in use.
    */
    void Shutdown();

    /* Name: CreateSwapChain();
    Params: void
    Return: DXGI_SWAP_CHAIN_DESC
    Info: Create a swap chain, for now doesn't take any parameters to create a specialized SCD
    */
    DXGI_SWAP_CHAIN_DESC CreateSwapChainDesc();

    /* Name: CreateInputLayout()
    Param: void
    Return: HRESULT
    Info: S_OK if we successfully create and set our input layout
    */
    HRESULT CreateInputLayout();

    /* Name: InitWorldMatrix()
    Param: void
    Return: void
    Info: Initialize the world matrix
    */
    void InitWorldMatrix();

    /* Name: CreateTexture2DDesc()
    Param: void
    Return: HRESULT
    Info: Create the D3D11_TEXTURE2D_DESC 
    */
    HRESULT CreateTexture2DDesc();

    /* Name: CreateDebugDevice()
    Param: Void
    Return: HRESULT
    Info: Create a debug device
    */
    HRESULT CreateDebugDevice();

    /* Name: GetImmediateContext()
    Param: void
    Return: Microsoft::WRL::ComPtr<ID3D11DeviceContext>
    Info: Returns a ComPtr to the COM Object ID3D11DeviceContext
    */
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> GetImmediateContext();
};

