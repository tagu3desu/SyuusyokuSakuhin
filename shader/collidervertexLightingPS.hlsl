

#include "common.hlsl"


Texture2D g_Texture : register(t0);
SamplerState g_SamplerState : register(s0);


void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
    //float4 MaterialColor = param.collidercollor;

    //float4 MaterialColor = float4(0.0f,1.0f,0.0f,1.0f);
	
	if (Material.TextureEnable)
	{
		outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);
        outDiffuse *= In.Diffuse;
        outDiffuse.rgb += param.collidercollor.rgb;
        
    }
	else
	{
        outDiffuse = In.Diffuse;
        outDiffuse.rgb += param.collidercollor.rgb;
    }
	

}
