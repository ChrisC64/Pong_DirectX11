#pragma once

#include <memory>
#include "..\..\GameEngine\HeaderFiles\DirectXRender.h"
/*********************************************************************************************
* Our Mesh Objects, this is where the input layout of our objects will reside and we pass
* the renderer to our mesh objects in order to render each mesh the way its designed to appear.
***********************************************************************************************/

namespace LunaSolEngine
{
    class IMesh
    {
    public:
        //IMesh();
        virtual ~IMesh();
        //TOOD: Let's look into using SmartPointers perhaps? 
        virtual void* GetVertexLayoutAddress() = 0;
        /* Name: GetVertexListByteWidth();
        Param: void
        Return: unsigned int
        Info: Returns size of our mVertexLayout array size
        */
        virtual unsigned int GetVertexListByteWidth() = 0;
        /* Name: GetIndexListByteWidth();
        Param: void
        Return: usigned int
        Info: Retreive the size of the index array for index buffer
        */
        virtual unsigned int GetIndexListByteWidth() = 0;

        /* Name: Draw()
        Param: void
        Return void
        Info: Draw the mesh object
        */
        virtual void Draw(std::shared_ptr<DirectXRender> Render) = 0;

        /*  Name: CreateVertexLayout(unsigned int size, <T&> Contents)
        Param: unsigned int, <T&>
        Return: void
        Info: Create the Mesh's VertexLayout based upon the passed <T&> given of size int.
        */
    };

}
