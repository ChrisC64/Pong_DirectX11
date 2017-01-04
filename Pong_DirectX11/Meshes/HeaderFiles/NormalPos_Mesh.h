#pragma once
#include <vector>

#include "IMesh.h"
#include "..\..\GameEngine\HeaderFiles\DataStructs.h"
namespace LunaSolEngine
{
    class NormalPos_Mesh : public IMesh
    {
    public:
        NormalPos_Mesh();
        ~NormalPos_Mesh();
        GameStruct::DataStructs m_DataStruct;
        // Inherited via IMesh
        virtual void * GetVertexLayoutAddress() override;
        virtual unsigned int GetVertexListByteWidth() override;
        virtual unsigned int GetIndexListByteWidth() override;
        virtual void Draw(std::shared_ptr<DirectXRender> Render) override;

        bool CreateVertexLayout(const unsigned int size, std::vector<float> layout);
        bool CreateIndexLayout(const unsigned int size, std::vector<int> layout);
    private:
        std::shared_ptr<std::vector<GameStruct::DataStructs::VertLayoutPosNorm>> m_vecPosNormLayout;
        std::vector<int> m_vecIndexLayout;
    };
}

