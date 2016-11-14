//--------------------------------------------------------------------------------------
// Constant Buffer Variables
//--------------------------------------------------------------------------------------
cbuffer ConstantBuffer : register(b0)
{
    matrix World;
    matrix View;
    matrix Projection;
    float4 vLightDir[2];
    float4 vLightColor[2];
    float4 vOutputColor;
}

//--------------------------------------------------------------------------------------
//struct VS_OUTPUT
//{
//    float4 Pos : SV_POSITION;
//    float4 Color : COLOR0;
//};
struct VS_INPUT
{
    float4 Pos : POSITION;
    float3 Norm : NORMAL;
};

struct PS_INPUT
{
    float4 Pos : SV_POSITION;
    float3 Norm : TEXCOORD0;
};


//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------

//float4 VS(float4 Pos : POSITION) : SV_POSITION
//{
//    return Pos;
//}

PS_INPUT VS(VS_INPUT input)
{
    PS_INPUT output = (PS_INPUT)0;
    output.Pos = mul(input.Pos, World);
    output.Pos = mul(output.Pos, View);
    output.Pos = mul(output.Pos, Projection);
    output.Norm = mul(float4(input.Norm, 1), World).xyz;
    return output;
}

//VS_OUTPUT VS(float4 Pos : POSITION, float4 Color : COLOR) 
//{
//    /*Pos.w = 1.0f;*/
//    VS_OUTPUT output = (VS_OUTPUT)0;
//    output.Pos = mul(Pos, World);
//    output.Pos = mul(output.Pos, View);
//    output.Pos = mul(output.Pos, Projection);
//    output.Color = Color;
//    return output;
//}
//cbuffer cbPerObject
//{
//    float4x4 gWorldViewProj;
//};
//
//struct VertexOut
//{
//    float4 PosH : SV_POSITION;
//    float4 Color : COLOR;
//};
//
//struct VertexIn
//{
//    float3 PosL : POSITION;
//    float4 Color : COLOR;
//};
//
//VertexOut main(VertexIn vin)
//{
//    VertexOut vOut;
//
//    vOut.PosH = mul(float4(vin.PosL, 1.0f), gWorldViewProj);
//
//    vOut.Color = vin.Color;
//
//    return vOut;
//}

//float4 main( float4 pos : POSITION) : SV_POSITION
//{
//    return pos;
//}