#include "common.hlsl"

Texture2D g_SwordTexture : register(t0);
SamplerState g_SamplerState : register(s0);

void main(in PS_IN In ,out float4 outDiffuse :SV_Target)
{
    //�@���𐳋K�����Ċi�[
    
    
    
    outDiffuse = g_SwordTexture.Sample(g_SamplerState, In.TexCoord);
    

}