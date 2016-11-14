#include "..\HeaderFiles\Cube.h"

using namespace DirectX;

Cube::Cube() : 
m_PosX(0),
m_PosY(0),
m_PosZ(0),
m_RotX(0),
m_RotY(0),
m_RotZ(0),
m_ScaleX(0),
m_ScaleY(0),
m_ScaleZ(0)
{
    Init();
}


Cube::~Cube()
{
}

Cube::Cube(DirectX::XMFLOAT3 posArr[], DirectX::XMFLOAT3 normArr[]) :
    m_PosX(0),
    m_PosY(0),
    m_PosZ(0),
    m_RotX(0),
    m_RotY(0),
    m_RotZ(0),
    m_ScaleX(0),
    m_ScaleY(0),
    m_ScaleZ(0)
{
    if (!posArr || !normArr)
    {
        Init(); // default initializer
        return;
    }

    if ((sizeof(posArr) / sizeof(posArr[0])) == 8 || (sizeof(normArr) / sizeof(normArr[0])) == 8)
    {
        int count = 0;
        for (unsigned int i = 0; i < (sizeof(posArr) / sizeof(posArr[0])); i++)
        {
            m_VertexLayout[count] = { posArr[count], normArr[count] };
        }
    }
}

Cube::Cube(VertexLayout vertLayArr[]) :
    m_PosX(0),
    m_PosY(0),
    m_PosZ(0),
    m_RotX(0),
    m_RotY(0),
    m_RotZ(0),
    m_ScaleX(0),
    m_ScaleY(0),
    m_ScaleZ(0)
{
    if (!vertLayArr)
    {
        Init();
        return;
    }

    if ((sizeof(vertLayArr) / sizeof(vertLayArr[0])) != 8)
    {
        Init();
        return;
    }

    int count = 0;
    for (unsigned int i = 0; i < (sizeof(vertLayArr) / sizeof(vertLayArr[0])); i++)
    {
        m_VertexLayout[count] = { vertLayArr[count].Pos, vertLayArr[count].Normal };
    }
}

void Cube::Init()
{
    // Vertex Layout setup
    //TODO: Problem here is not using the other NORMALS when doing our lighting. This will cause issues. Should we create our Structures for POS/NORMALs and assign one to each Cube object?
    m_VertexLayout[0] = { XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT3(0.0f, 1.0f, 0.0f) };
    m_VertexLayout[1] = { XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT3(0.0f, 1.0f, 0.0f) };
    m_VertexLayout[2] = { XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT3(0.0f, 1.0f, 0.0f) };
    m_VertexLayout[3] = { XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT3(0.0f, 1.0f, 0.0f) };

    m_VertexLayout[4] = { XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT3(0.0f, -1.0f, 0.0f) };
    m_VertexLayout[5] = { XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT3(0.0f, -1.0f, 0.0f) };
    m_VertexLayout[6] = { XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT3(0.0f, -1.0f, 0.0f) };
    m_VertexLayout[7] = { XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT3(0.0f, -1.0f, 0.0f) };
    
    m_VertexLayout[8] = { XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT3(-1.0f, 0.0f, 0.0f) };
    m_VertexLayout[9] = { XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT3(-1.0f, 0.0f, 0.0f) };
    m_VertexLayout[10] = { XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT3(-1.0f, 0.0f, 0.0f) };
    m_VertexLayout[11] = { XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT3(-1.0f, 0.0f, 0.0f) };

    m_VertexLayout[12] = { XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT3(1.0f, 0.0f, 0.0f) };
    m_VertexLayout[13] = { XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT3(1.0f, 0.0f, 0.0f) };
    m_VertexLayout[14] = { XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT3(1.0f, 0.0f, 0.0f) };
    m_VertexLayout[15] = { XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT3(1.0f, 0.0f, 0.0f) };
    
    m_VertexLayout[16] = { XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT3(0.0f, 0.0f, -1.0f) };
    m_VertexLayout[17] = { XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT3(0.0f, 0.0f, -1.0f) };
    m_VertexLayout[18] = { XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT3(0.0f, 0.0f, -1.0f) };
    m_VertexLayout[19] = { XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT3(0.0f, 0.0f, -1.0f) };
    
    m_VertexLayout[20] = { XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 1.0f) };
    m_VertexLayout[21] = { XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 1.0f) };
    m_VertexLayout[22] = { XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 1.0f) };
    m_VertexLayout[23] = { XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 1.0f) };

    // Index List setup
    //m_IndexList[0] = 3; m_IndexList[1] = 1; m_IndexList[2] = 0;
    //m_IndexList[3] = 2; m_IndexList[4] = 1; m_IndexList[5] = 3;

    //m_IndexList[6] = 0; m_IndexList[7] = 5; m_IndexList[8] = 4;
    //m_IndexList[9] = 1; m_IndexList[10] = 5; m_IndexList[11] = 0;

    //m_IndexList[12] = 3; m_IndexList[13] = 4; m_IndexList[14] = 7;
    //m_IndexList[15] = 0; m_IndexList[16] = 4; m_IndexList[17] = 3;

    //m_IndexList[18] = 1; m_IndexList[19] = 6; m_IndexList[20] = 5;
    //m_IndexList[21] = 2; m_IndexList[22] = 6; m_IndexList[23] = 1;

    //m_IndexList[24] = 2; m_IndexList[25] = 7; m_IndexList[26] = 6;
    //m_IndexList[27] = 3; m_IndexList[28] = 7; m_IndexList[29] = 2;

    //m_IndexList[30] = 6; m_IndexList[31] = 4; m_IndexList[32] = 5;
    //m_IndexList[33] = 7; m_IndexList[34] = 4; m_IndexList[35] = 6;
    m_IndexList[0] = 3; m_IndexList[1] = 1; m_IndexList[2] = 0;
    m_IndexList[3] = 2; m_IndexList[4] = 1; m_IndexList[5] = 3;
    
    m_IndexList[6] = 6; m_IndexList[7] = 4; m_IndexList[8] = 5;
    m_IndexList[9] = 7; m_IndexList[10] = 4; m_IndexList[11] = 6;
    
    m_IndexList[12] = 11; m_IndexList[13] = 9; m_IndexList[14] = 8;
    m_IndexList[15] = 10; m_IndexList[16] = 9; m_IndexList[17] = 11;

    m_IndexList[18] = 14; m_IndexList[19] = 12; m_IndexList[20] = 13;
    m_IndexList[21] = 15; m_IndexList[22] = 12; m_IndexList[23] = 14;

    m_IndexList[24] = 19; m_IndexList[25] = 17; m_IndexList[26] = 16;
    m_IndexList[27] = 18; m_IndexList[28] = 17; m_IndexList[29] = 19;

    m_IndexList[30] = 22; m_IndexList[31] = 20; m_IndexList[32] = 21;
    m_IndexList[33] = 23; m_IndexList[34] = 20; m_IndexList[35] = 22;
}

unsigned int Cube::GetVertexListByteWidth()
{
    return sizeof(m_VertexLayout);
}

void * Cube::GetVertexLayoutAddress()
{
    return m_VertexLayout;
}

unsigned int Cube::GetIndexListByteWidth()
{
    return sizeof(m_IndexList);
}

float Cube::GetPosX()
{
    return m_PosX;
}

float Cube::GetPosY()
{
    return m_PosY;
}

float Cube::GetPosZ()
{
    return m_PosZ;
}

float Cube::GetRotX()
{
    return m_RotX;
}

float Cube::GetRotY()
{
    return m_RotY;
}

float Cube::GetRotZ()
{
    return m_RotZ;
}

float Cube::GetScaleX()
{
    return m_ScaleX;
}

float Cube::GetScaleY()
{
    return m_ScaleY;
}

float Cube::GetScaleZ()
{
    return m_ScaleZ;
}

void Cube::SetPosX(float p)
{
    m_PosX = p;
}

void Cube::SetPosY(float p)
{
    m_PosY = p;
}

void Cube::SetPosZ(float p)
{
    m_PosZ = p;
}

void Cube::SetRotX(float r)
{
    m_RotX = r;
}

void Cube::SetRotY(float r)
{
    m_RotY = r;
}

void Cube::SetRotZ(float r)
{
    m_RotZ = r;
}

void Cube::SetScaleX(float s)
{
    m_ScaleX = s;
}

void Cube::SetScaleY(float s)
{
    m_ScaleY = s;
}

void Cube::SetScaleZ(float s)
{
    m_ScaleZ = s;
}
