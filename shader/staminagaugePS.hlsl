
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
    
    // //UV�l����s�N�Z���ւ̃X�P�[���ϊ�
    //float gage = frac(angle * 0.5f / pi) * Param.hp.y;
    ////HP�Q�[�W�̃O���[�������쐬����
    //outDiffuse.rgb += Param.lostColor.rgb * step(beforHp, gage);
    ////HP�Q�[�W�̗Ε������쐬����
    //outDiffuse.rgb += Param.baseColor.rgb * (1.0f - step(nowHp, gage));
    ////HP�Q�[�W�̐ԐF�������쐬����
    //outDiffuse.rgb += Param.diffColor.rgb * (1.0f - step(beforHp, gage)) * step(nowHp, gage);
    
    //float dist = length(uv) / 0.5;
    //outDiffuse.a = (1.0 - step(1.0, dist)) * step(0.9, dist);
   
    //��HP�Q�[�W
   {
    
        float nowStamina = param.stamina.x;
        float maxStamina = param.stamina.y;
        float beforStamina = param.stamina.z;
    
        //UV�l����s�N�Z���ւ̃X�P�[���ϊ�
        float gage = In.TexCoord.x * maxStamina;
        //�X�^�~�i�Q�[�W�̃O���[�������쐬����
        outDiffuse.rgb += param.lostColor.rgb * step(beforStamina, gage);
        //�X�^�~�i�Q�[�W�̃I�����W�������쐬����
        outDiffuse.rgb += param.baseStaminaColor.rgb * (1.0f - step(nowStamina, gage));
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