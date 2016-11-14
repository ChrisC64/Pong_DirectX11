#ifndef DATA_STRUCTS
#define DATA_STRUCTS

namespace GameStruct
{
    class DataStructs
    {
    public:
        struct VertexLayout
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
    };
}
#endif