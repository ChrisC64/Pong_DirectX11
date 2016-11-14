#pragma once
#include "IObject.h"
class NormalObject :
    public IObject
{
public:
    NormalObject();
    ~NormalObject();
    virtual void Draw(std::shared_ptr<DirectXRender> render);
};

