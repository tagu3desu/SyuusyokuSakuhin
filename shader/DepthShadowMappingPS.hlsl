
#include "common.hlsl"

Texture2D g_Texture : register(t0);
Texture2D g_TextureDepthShadow : register(t1);
Texture2D g_TextureNormal : register(t2);
SamplerState g_SamplerState : register(s0);


void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
	//�e�N�X�`������F���T���v�����O����
    outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);
    outDiffuse *= In.Diffuse;

    In.ShadowPosition.xyz /= In.ShadowPosition.w;
    In.ShadowPosition.x = In.ShadowPosition.x * 0.5 + 0.5;
    In.ShadowPosition.y = -In.ShadowPosition.y * 0.5 + 0.5;

    float depth = g_TextureDepthShadow.Sample(g_SamplerState, In.ShadowPosition.xy);
	
    if (depth < In.ShadowPosition.z - 0.001)
    {
        outDiffuse.rgb *= 0.5;
    }

}
