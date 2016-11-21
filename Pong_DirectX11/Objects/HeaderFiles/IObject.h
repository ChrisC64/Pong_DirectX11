#pragma once
#include "..\..\GameEngine\HeaderFiles\DirectXRender.h"
#include <memory>
class IObject
{
public:
    //IObject();
    virtual ~IObject();
    virtual void Draw(std::shared_ptr<DirectXRender> render) = 0;
};