#include "common.hlsl"


void main(in VS_SKINIG_IN In, out PS_IN Out)
{
    float4x4 SkiningTransform = float4x4(1.0f, 0.0f, 0.0f, 0.0f,
								 0.0f, 1.0f, 0.0f, 0.0f,
								 0.0f, 0.0f, 1.0f, 0.0f,
								 0.0f, 0.0f, 0.0f, 1.0f);
	
    SkiningTransform = bonrTransform[In.Index.x] * In.Weight.x
					  + bonrTransform[In.Index.y] * In.Weight.y
					  + bonrTransform[In.Index.z] * In.Weight.z
					  + bonrTransform[In.Index.w] * In.Weight.w;
	
	
	matrix wvp;
	wvp = mul(World, View);
	wvp = mul(wvp, Projection);
	
    float4 normal = float4(In.Normal.xyz, 0.0);
	
    float4 transpos = mul(SkiningTransform, float4(In.Position.xyz, 1.0f));
	
    float4 transNormal = mul(SkiningTransform,normal);
	
    float4 worldNormal = mul(transNormal, World);
	
	
	worldNormal = normalize(worldNormal);

	float light = -dot(Light.Direction.xyz,worldNormal.xyz);
	light = saturate(light);

	Out.Diffuse = In.Diffuse * Material.Diffuse * light * Light.Diffuse;
	Out.Diffuse += In.Diffuse * Material.Ambient * Light.Ambient;
	Out.Diffuse += Material.Emission;
	Out.Diffuse.a = In.Diffuse.a * Material.Diffuse.a;

	Out.Position = mul( transpos, wvp );
	Out.TexCoord = In.TexCoord;

}

