#pragma once
#include <DirectXMath.h>
#include "..\..\pch.h"
#include "GameActor.h"
#include "..\..\GameEngine\HeaderFiles\IMeshObject.h"

using namespace DirectX;
using namespace GameStruct;
using VertexLayout = GameStruct::DataStructs::VertexLayout;
class Cube : public GameActor, public IMeshObject
{
private:
    /*struct VertexLayout
    {
        DirectX::XMFLOAT3 Pos;
        DirectX::XMFLOAT3 Normal;
        VertexLayout::VertexLayout()
        {
            CopyFloat3(DirectX::XMFLOAT3(0, 0, 0), this->Pos);
            CopyFloat3(DirectX::XMFLOAT3(0, 0, 0), this->Normal);
        }
        VertexLayout::VertexLayout(DirectX::XMFLOAT3 xmPos, DirectX::XMFLOAT3 xmNorm)
        {
            CopyFloat3(xmPos, this->Pos);
            CopyFloat3(xmNorm, this->Normal);
        }

        void CopyFloat3(DirectX::XMFLOAT3 &targ, DirectX::XMFLOAT3 &dest)
        {
            dest.x = targ.x;
            dest.y = targ.y;
            dest.z = targ.z;
        }
    };

    struct VertexLayout_Position
    {
        DirectX::XMFLOAT3 Pos;
        VertexLayout_Position::VertexLayout_Position(DirectX::XMFLOAT3 xmf3)
        {
            CopyFloat3(xmf3);
        }

        void CopyFloat3(DirectX::XMFLOAT3 &xm)
        {
            this->Pos.x = xm.x;
            this->Pos.y = xm.y;
            this->Pos.z = xm.z;
        }
    };

    struct VertexLayout_Normal
    {
        DirectX::XMFLOAT3 Normal;
        VertexLayout_Normal::VertexLayout_Normal(DirectX::XMFLOAT3 xmf3)
        {
            CopyFloat3(xmf3);
        }

        void CopyFloat3(DirectX::XMFLOAT3 &xm)
        {
            this->Normal.x = xm.x;
            this->Normal.y = xm.y;
            this->Normal.z = xm.z;
        }
    };*/

public:
    Cube();
    ~Cube();
    Cube(DirectX::XMFLOAT3 posArr[], DirectX::XMFLOAT3 normArr[]);
    Cube(VertexLayout vertLayArr[]);

    unsigned short m_IndexList[36]; // Index layout for trianglist
    VertexLayout m_VertexLayout[24l]; // Our Vertex array used in our Vertex description
    
    // GET METHODS //

    /* Name: GetPosX/GetPosY/GetPosZ
    Param: void
    Return: float
    Info: Get X/Y/Z Position
    */
    float GetPosX();
    float GetPosY();
    float GetPosZ();

    /* Name: GetRotX/ GetRotY / GetRotZ
    Param: void
    return float
    Info: Get X/Y/Z Rotation
    */
    float GetRotX();
    float GetRotY();
    float GetRotZ();

    /* Name: GetScaleX / GetScaleY / GetScaleZ
    Param: void
    Return: float
    Info: Get X/Y/Z Scale
    */
    float GetScaleX();
    float GetScaleY();
    float GetScaleZ();
    
    // SET METHODS //
    
    /* Name: SetPosX / SetPosY / SetPosZ
    Param: Float
    Return: void
    Info: Set X/Y/Z Pos
    */
    void SetPosX(float);
    void SetPosY(float);
    void SetPosZ(float);

    /* Name: SetRotX / SetRotY / SetRotZ
    Param: float
    Return: void
    Info: Set X/Y/Z Rotation
    */
    void SetRotX(float);
    void SetRotY(float);
    void SetRotZ(float);

    /* Name: SetScaleX / SetScaleY / SetScaleZ
    Param: float
    Return: void
    Info: set X/Y/Z Scale
    */
    void SetScaleX(float);
    void SetScaleY(float);
    void SetScaleZ(float);

    
    // Inherited via IMeshObject
    virtual unsigned int GetVertexListByteWidth() override;
    virtual void* GetVertexLayoutAddress() override;
    virtual unsigned int GetIndexListByteWidth() override;

private:
    float m_PosX, m_PosY, m_PosZ; // Position of Cube
    float m_RotX, m_RotY, m_RotZ; // Rotation
    float m_ScaleX, m_ScaleY, m_ScaleZ; // scale

    /* Name: Init()
    Param: void
    Return: void
    Info: Sets up cube
    */
    void Init();

};

