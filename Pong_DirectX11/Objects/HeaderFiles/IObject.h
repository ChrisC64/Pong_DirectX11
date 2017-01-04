#pragma once
#include "..\..\GameEngine\HeaderFiles\DirectXRender.h"

/************************************
* This class will be our physics object types. When we create objects, we'll associate with them specific 
* attributes that will be utilized by our physics engine later to control their behavior. These merely
* Will contain specific values and possible functions. For example, a SolidObject will be one that has
* properties of a "wall" where it cannot be passed through.
*/

namespace LunaSolEngine
{
    class IObject
    {
    public:
        //IObject();
        virtual ~IObject();
        virtual void Update() = 0;
    };
}