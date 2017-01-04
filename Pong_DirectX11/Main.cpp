#include <iostream>
#include <Windows.h>
#include <memory>
#include "GameEngine\HeaderFiles\DirectX11_Device.h"
#include "GameEngine\HeaderFiles\DataStructs.h"
#include "Actors\HeaderFiles\cube.h"
#include "pch.h"
/******
*   GLOBAL VARIABLES
******/
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define WINDOW_TITLE L"Chris Carlos"
using namespace LunaSolEngine;
HWND				g_hWnd;          // Handle to the window
HINSTANCE			g_hInstance;	// Handle to the aplication instance
bool				g_bWindowed;	// Boolean for window or full-screen mode
                                    // Timer Variables
__int64 g_cntsPerSec;
__int64 g_currTimeStamp;
__int64 g_prevTimeStamp;
float   g_secsPerCnt;
float   g_deltaTime;

// Direct X global variables declared below (when created)
DirectX11_Device g_Device;
DirectXRender g_Render;
// Entry point for the game or application

int WINAPI WinMain(HINSTANCE hInstance,     // Handle to the Window
    HINSTANCE hPrevInstance,                // Handle to the previous Window
    LPSTR lpCmdLine,                        // Command line string
    int lpCmdShow);                         // Show window value

LRESULT CALLBACK WndProc(HWND hWnd,			// Handle to the window
    UINT message,							// Incoming Message
    WPARAM wparam,							// Message Info
    LPARAM lparam);							// Message info

                                            // Here is where we will create our window to use
void InitWindow(void)
{
    WNDCLASSEX wndClass;
    ZeroMemory(&wndClass, sizeof(wndClass));

    // set up the window
    wndClass.cbSize = sizeof(WNDCLASSEX);			// size of window structure
    wndClass.lpfnWndProc = (WNDPROC)WndProc;				// message callback
    wndClass.lpszClassName = WINDOW_TITLE;					// class name
    wndClass.hInstance = g_hInstance;					// handle to the application
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);	// default cursor
    wndClass.hbrBackground = (HBRUSH)(COLOR_WINDOWFRAME);	// background brush

                                                            // register a new type of window
    RegisterClassEx(&wndClass);

    g_hWnd = CreateWindow(
        WINDOW_TITLE, WINDOW_TITLE, 							// window class name and title
        g_bWindowed ? WS_OVERLAPPEDWINDOW | WS_VISIBLE : (WS_POPUP | WS_VISIBLE),// window style
        CW_USEDEFAULT, CW_USEDEFAULT,							// x and y coordinates
        SCREEN_WIDTH, SCREEN_HEIGHT,							// width and height of window
        NULL, NULL,												// parent window and menu
        g_hInstance,											// handle to application
        NULL);

    // Display the window
    ShowWindow(g_hWnd, SW_SHOW);
    UpdateWindow(g_hWnd);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int lpCmdShow)
{
    // Set some variables that will be used in InitWindow()
    g_hInstance = hInstance;
    g_bWindowed = true;
    GameStruct::DataStructs::VertLayoutPosNorm simpArr[8];
    simpArr[0] = { DirectX::XMFLOAT3(-1.0f, 1.0f, -1.0f),  DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f) };
    simpArr[1] = { DirectX::XMFLOAT3(1.0f, 1.0f, -1.0f),   DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f) };
    simpArr[2] = { DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f),    DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f) };
    simpArr[3] = { DirectX::XMFLOAT3(-1.0f, 1.0f, 1.0f),   DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f) };
    simpArr[4] = { DirectX::XMFLOAT3(-1.0f, -1.0f, -1.0f), DirectX::XMFLOAT3(0.0f, -1.0f, 0.0f) };
    simpArr[5] = { DirectX::XMFLOAT3(1.0f, -1.0f, -1.0f),  DirectX::XMFLOAT3(0.0f, -1.0f, 0.0f) };
    simpArr[6] = { DirectX::XMFLOAT3(1.0f, -1.0f, 1.0f),   DirectX::XMFLOAT3(0.0f, -1.0f, 0.0f) };
    simpArr[7] = { DirectX::XMFLOAT3(-1.0f, -1.0f, 1.0f),  DirectX::XMFLOAT3(0.0f, -1.0f, 0.0f) };

    // Light Cube
    GameStruct::DataStructs::VertLayoutPosNorm lightArr[8];
    lightArr[0] = { DirectX::XMFLOAT3(-1.0f, -1.0f, 1.0f),  DirectX::XMFLOAT3(-1.0f, 0.0f, 0.0f) };
    lightArr[1] = { DirectX::XMFLOAT3(-1.0f, -1.0f, -1.0f), DirectX::XMFLOAT3(-1.0f, 0.0f, 0.0f) };
    lightArr[2] = { DirectX::XMFLOAT3(-1.0f, 1.0f, -1.0f),  DirectX::XMFLOAT3(-1.0f, 0.0f, 0.0f) };
    lightArr[3] = { DirectX::XMFLOAT3(-1.0f, 1.0f, 1.0f),   DirectX::XMFLOAT3(-1.0f, 0.0f, 0.0f) };
    lightArr[4] = { DirectX::XMFLOAT3(1.0f, -1.0f, 1.0f),   DirectX::XMFLOAT3(1.0f, 0.0f, 0.0f) };
    lightArr[5] = { DirectX::XMFLOAT3(1.0f, -1.0f, -1.0f),  DirectX::XMFLOAT3(1.0f, 0.0f, 0.0f) };
    lightArr[6] = { DirectX::XMFLOAT3(1.0f, 1.0f, -1.0f),   DirectX::XMFLOAT3(1.0f, 0.0f, 0.0f) };
    lightArr[7] = { DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f),    DirectX::XMFLOAT3(1.0f, 0.0f, 0.0f) };

    // Third Cube
    GameStruct::DataStructs::VertLayoutPosNorm thirdArr[8];
    thirdArr[0] = { DirectX::XMFLOAT3(-1.0f, -1.0f, -1.0f), DirectX::XMFLOAT3(0.0f, 0.0f, -1.0f) };
    thirdArr[1] = { DirectX::XMFLOAT3(1.0f, -1.0f, -1.0f),  DirectX::XMFLOAT3(0.0f, 0.0f, -1.0f) };
    thirdArr[2] = { DirectX::XMFLOAT3(1.0f, 1.0f, -1.0f),   DirectX::XMFLOAT3(0.0f, 0.0f, -1.0f) };
    thirdArr[3] = { DirectX::XMFLOAT3(-1.0f, 1.0f, -1.0f),  DirectX::XMFLOAT3(0.0f, 0.0f, -1.0f) };
    thirdArr[5] = { DirectX::XMFLOAT3(-1.0f, -1.0f, 1.0f),  DirectX::XMFLOAT3(0.0f, 0.0f, 1.0f) };
    thirdArr[6] = { DirectX::XMFLOAT3(1.0f, -1.0f, 1.0f),   DirectX::XMFLOAT3(0.0f, 0.0f, 1.0f) };
    thirdArr[7] = { DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f),    DirectX::XMFLOAT3(0.0f, 0.0f, 1.0f) };
    thirdArr[0] = { DirectX::XMFLOAT3(-1.0f, 1.0f, 1.0f),   DirectX::XMFLOAT3(0.0f, 0.0f, 1.0f) };

    Cube spinCube = Cube(simpArr);
    Cube lightCube = Cube(lightArr);
    Cube thirdCube = Cube(thirdArr);
    //TODO: Set up so we initialize our buffers for the types of objects we are creating instead of one buffer based on just one type in our previous work. 
    // Program will also require us to make multiple cubes and add those vertexlayout buffers we need for the different cubes.
    // Afterward we should make sure our Render is set up properly, research more on these smart pointers. I think we need to consider how we make them and pass them into 
    // the functions that require a unique_ptr or shared_ptr. These will probably need shared_ptr for our Render argument in our IObjects, not a shared_ptr, right?

    // Initialize the window
    InitWindow();

    if (!g_Device.InitDevice(SCREEN_WIDTH, SCREEN_HEIGHT, g_hWnd, g_bWindowed)) {
        return 0;
    }
    g_Render.SetRender(std::make_unique<DirectX11_Device>(g_Device));
    // Use msg structure for catching windows Messages
    MSG msg;
    ZeroMemory(&msg, sizeof(msg));

    // Enter Windows Main loop here
    while (msg.message != WM_QUIT)
    {
        // Basic windows Peek message to handle messages appropriately
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            //Draw here
        }
    }
    UnregisterClass(WINDOW_TITLE, g_hInstance);
    return 0;
}

// Windows procedure callback function; handle our windows messages here
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam)
{
    switch (message)
    {
        case (WM_PAINT):
        {
            InvalidateRect(hWnd, NULL, TRUE);
            break;
        }

        case(WM_DESTROY):
        {
            PostQuitMessage(0);
            break;
        }

        case(WM_KEYDOWN):
        {
            switch (wparam)
            {
                case VK_ESCAPE:
                {
                    PostQuitMessage(0);
                    break;
                }
            }
        }
    }

    return DefWindowProc(hWnd, message, wparam, lparam);
}