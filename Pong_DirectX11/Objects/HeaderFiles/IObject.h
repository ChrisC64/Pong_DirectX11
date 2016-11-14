#pragma once
#include <memory>
#include "..\..\GameEngine\HeaderFiles\DirectXRender.h"
class IObject
{
public:
    IObject();
    ~IObject();
    virtual void Draw(std::shared_ptr<DirectXRender> render) = 0;
};