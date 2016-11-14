//#include "VertexShader.hlsl"
cbuffer ConstantBuffer : register(b0)
{
    matrix World;
    matrix View;
    matrix Projection;
    float4 vLightDir[2];
    float4 vLightColor[2];
    float4 vOutputColor;
}

struct PS_INPUT
{
    float4 Pos : SV_POSITION;
    float3 Norm : TEXCOORD0;
};

//struct PS_INPUT
//{
//    float4 Position : SV_POSITION;
//    float4 Normal : COLOR0;
//};
float4 PS(PS_INPUT input) : SV_Target
{
    float4 finalColor = 0;

    //do NdotL lighting for 2 lights
    for (int i = 0; i<2; i++)
    {
        finalColor += saturate(dot((float3)vLightDir[i],input.Norm) * vLightColor[i]);
    }
    finalColor.a = 1;
    return finalColor;
}
//float4 PS( PS_INPUT input) : SV_Target
//{
//    return input.Color;
//}

float4 PSSolid(PS_INPUT input) : SV_Target
{
    return vOutputColor;
}