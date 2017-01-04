#pragma once
#include <memory>
#include <vector>
#include "..\..\pch.h"
//TODO: Remove deendency on DirectX later on

namespace GameStruct
{
    class DataStructs
    {
    public:
        //TODO: Renamed to avoid confusion when we create new vertex layouts; this has to also change to allow some kind of "Contract" (Interface)
        // and to denote what layout is being used when we have multiple kinds for rendering. 
        struct VertLayoutPosNorm
        {
            DirectX::XMFLOAT3 Pos;
            DirectX::XMFLOAT3 Normal;
            VertLayoutPosNorm::VertLayoutPosNorm()
            {
                CopyFloat3(DirectX::XMFLOAT3(0, 0, 0), this->Pos);
                CopyFloat3(DirectX::XMFLOAT3(0, 0, 0), this->Normal);
            }

            VertLayoutPosNorm::VertLayoutPosNorm(DirectX::XMFLOAT3 xmPos, DirectX::XMFLOAT3 xmNorm)
            {
                CopyFloat3(xmPos, this->Pos);
                CopyFloat3(xmNorm, this->Normal);
            }

            VertLayoutPosNorm::VertLayoutPosNorm(float posX, float posY, float posZ, float normX, float normY, float normZ)
            {
                CopyPos(posX, posY, posZ);
                CopyNorm(normX, normY, normZ);
            }

            void CopyFloat3(DirectX::XMFLOAT3 &targ, DirectX::XMFLOAT3 &dest)
            {
                dest.x = targ.x;
                dest.y = targ.y;
                dest.z = targ.z;
            }

            void CopyPos(float x, float y, float z)
            {
                this->Pos.x = x;
                this->Pos.y = y;
                this->Pos.z = z;
            }

            void CopyNorm(float x, float y, float z)
            {
                this->Normal.x = x;
                this->Normal.y = y;
                this->Normal.z = z;
            }
        };
        // TODO: Sharder specific. Should be moved to shader types when we create those classes
        struct ConstantBuffer
        {
            DirectX::XMMATRIX world;
            DirectX::XMMATRIX view;
            DirectX::XMMATRIX proj;
            DirectX::XMFLOAT4 vLightDir[2];
            DirectX::XMFLOAT4 vLightColor[2];
            DirectX::XMFLOAT4 vOutputColor;
        };

        enum VERT_LAYOUT_TYPE
        {
            POS_NORM
        };

        // Wonder if I can do this, pass a enum, and create a unknown type later? Would this be a good idea?

        /* Name: CreateVertLayoutPosNorm
        Return: std::shared_ptr<VertLayoutPosNorm>
        Param: const unsigned int, std::vector<float> layout
        Info: Will created a VertLayoutPosNorm structure and return as a shared_ptr. The size is for how many VertLayoutPosNorm items we need. 
        */
        std::shared_ptr<std::vector<VertLayoutPosNorm>> CreateVertLayoutPosNorm(const unsigned int size, std::vector<float> layout);

    private:

    };
}