#pragma once
#include "..\HeaderFiles\IObject.h"
#include "..\..\GameEngine\HeaderFiles\DataStructs.h"

class NormalObject :
    public IObject
{
public:
    NormalObject();
    ~NormalObject();
    virtual void Draw(std::shared_ptr<DirectXRender> render) override;
};

