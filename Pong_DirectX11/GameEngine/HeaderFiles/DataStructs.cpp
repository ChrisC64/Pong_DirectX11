#include "DataStructs.h"
using namespace GameStruct;

std::shared_ptr<std::vector<GameStruct::DataStructs::VertLayoutPosNorm>> GameStruct::DataStructs::CreateVertLayoutPosNorm(const unsigned int size, std::vector<float> layout)
{
    if (size < 0 || layout.size() < 0 || (layout.size() % 6 != 0))
    {
        return nullptr;
    }
    // Create VertLayoutPosNorm vector based on size / 6, because there are 6 floats per layout of PosNorm structs.
    std::shared_ptr<std::vector<VertLayoutPosNorm>> temp;

    temp.get()->resize(size);

    for (int i = 0; i < temp.get()->size(); i++)
    {
        VertLayoutPosNorm item(layout.at(i), layout.at(i + 1), layout.at(i + 2), layout.at(i + 3), layout.at(i + 4), layout.at(i + 5));
        temp.get()->push_back(item);
    }

    return std::move(temp);
}
