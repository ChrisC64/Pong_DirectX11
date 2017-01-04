#include "..\HeaderFiles\NormalPos_Mesh.h"
using namespace LunaSolEngine;


NormalPos_Mesh::NormalPos_Mesh() : m_vecPosNormLayout(0),
m_vecIndexLayout(0),
m_DataStruct()
{
}


NormalPos_Mesh::~NormalPos_Mesh()
{
}

void* NormalPos_Mesh::GetVertexLayoutAddress()
{
    return m_vecPosNormLayout.get();
}

unsigned int NormalPos_Mesh::GetVertexListByteWidth()
{
    return m_vecPosNormLayout.get()->size() * sizeof(GameStruct::DataStructs::VertLayoutPosNorm);
}

unsigned int NormalPos_Mesh::GetIndexListByteWidth()
{
    return m_vecIndexLayout.size() * sizeof(int);
}

bool LunaSolEngine::NormalPos_Mesh::CreateVertexLayout(const unsigned int size, std::vector<float> layout)
{
    m_vecPosNormLayout = m_DataStruct.CreateVertLayoutPosNorm(size, layout);
    if (m_vecPosNormLayout)
        return true;
    else
        return false;
}

bool LunaSolEngine::NormalPos_Mesh::CreateIndexLayout(const unsigned int size, std::vector<int> layout)
{
    if (size != layout.size())
        return false;
    m_vecIndexLayout.resize(size);
    for (unsigned int i = 0; i < size; i++)
    {
        m_vecIndexLayout.at(i) = layout.at(i);
    }
}

void NormalPos_Mesh::Draw(std::shared_ptr<DirectXRender> Render)
{
}
