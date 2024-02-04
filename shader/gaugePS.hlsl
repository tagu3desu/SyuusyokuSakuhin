
#include "common.hlsl"


//static const float pi = 3.1415926535f;

void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
    outDiffuse = float4(0.0f, 0.0f, 0.0f, 1.0f);
    //float2 uv = In.TexCoord - 0.5;
   
    //float angle = atan2(uv.x, uv.y);
    //angle += pi;

    
    //float nowHp = Param.hp.x;
    //float maxHp = Param.hp.y;
    //float beforHp = Param.hp.z;
    
    // //UV値からピクセルへのスケール変換
    //float gage = frac(angle * 0.5f / pi) * Param.hp.y;
    ////HPゲージのグレー部分を作成する
    //outDiffuse.rgb += Param.lostColor.rgb * step(beforHp, gage);
    ////HPゲージの緑部分を作成する
    //outDiffuse.rgb += Param.baseColor.rgb * (1.0f - step(nowHp, gage));
    ////HPゲージの赤色部分を作成する
    //outDiffuse.rgb += Param.diffColor.rgb * (1.0f - step(beforHp, gage)) * step(nowHp, gage);
    
    //float dist = length(uv) / 0.5;
    //outDiffuse.a = (1.0 - step(1.0, dist)) * step(0.9, dist);
   
    
    //横HPゲージ
   {
    
        float nowHp = param.hp.x;
        float maxHp = param.hp.y;
        float beforHp = param.hp.z;
    
        //UV値からピクセルへのスケール変換
        float gage = In.TexCoord.x * maxHp;
        //HPゲージのグレー部分を作成する
        outDiffuse.rgb += param.lostColor.rgb * step(beforHp, gage);
        //HPゲージの緑部分を作成する
        outDiffuse.rgb += param.baseColor.rgb * (1.0f - step(nowHp, gage));
        //HPゲージの赤色部分を作成する
        outDiffuse.rgb += param.diffColor.rgb * (1.0f - step(beforHp, gage)) * step(nowHp, gage);
    }
    
    
}
//bool step(a, b)
//{
//    if (gauge >= nowHp)
//    {
//        return 1;
//    }
//    else
//    {
//        return 0;
//    }

//}