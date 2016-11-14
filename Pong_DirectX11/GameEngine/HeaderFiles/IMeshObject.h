#pragma once
class IMeshObject
{
public:
    IMeshObject();
    ~IMeshObject();

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
};

