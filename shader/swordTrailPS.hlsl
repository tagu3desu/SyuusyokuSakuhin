#include "common.hlsl"

Texture2D g_SwordTexture : register(t0);
SamplerState g_SamplerState : register(s0);

void main(in PS_IN In ,out float4 outDiffuse :SV_Target)
{
    //–@ü‚ğ³‹K‰»‚µ‚ÄŠi”[
    
    
    
    outDiffuse = g_SwordTexture.Sample(g_SamplerState, In.TexCoord);
    

}