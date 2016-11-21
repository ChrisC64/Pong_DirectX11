#pragma once
#include "..\..\pch.h"
#include "..\..\GameEngine\HeaderFiles\DirectXRender.h"
#include "..\..\GameEngine\HeaderFiles\DataStructs.h"
#include "..\..\GameEngine\HeaderFiles\IMesh.h"
#include "..\..\Objects\HeaderFiles\IObject.h"
#include "GameActor.h"
#include <memory>

//#include "..\..\Objects\HeaderFiles\NormalObject.h"

using VertLayout = GameStruct::DataStructs::VertexLayout;

class Cube : 
    public GameActor, public IMesh, public IObject
{
public:
    Cube();
    ~Cube();
    Cube(DirectX::XMFLOAT3 posArr[], DirectX::XMFLOAT3 normArr[]);
    Cube(VertLayout vertLayArr[]);

    unsigned short m_IndexList[36]; // Index layout for trianglist
    VertLayout m_VertexLayout[24]; // Our Vertex array used in our Vertex description
    
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

    
    // Inherited via IMesh
    virtual unsigned int GetVertexListByteWidth();
    virtual void* GetVertexLayoutAddress();
    virtual unsigned int GetIndexListByteWidth();
    virtual void Draw(std::shared_ptr<DirectXRender> render);

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