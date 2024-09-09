#include "CloudTex2D.hlsli"
#include "../PerlinNoise.hlsli"
#include "../Normal.hlsli"

PixelShaderOutPut3 main(VertexOutPut input)
{
	PixelShaderOutPut3 output;

    uint32_t textureID = kTexture2DData[input.instanceID].textureID;
	
	float32_t4 textureColor = textures[textureID].Sample(smp, input.uv);
    if(textureColor.w < 0.1f){
        discard;
    }

    // お水の処理
	const float32_t2 kRandomVec = kWaterData[input.instanceID].randomVec;
    const float32_t kDensity = kWaterData[input.instanceID].density;
    
    float32_t3 perlinNormal = CreateNormal(input.uv, kRandomVec, kDensity);
    float32_t3 normal = input.normal;
    float32_t3 tangent = NormalToTangent(perlinNormal);
    float32_t3 binormal = CalcBinormal(perlinNormal, tangent);
    float32_t3 blendNormal = BlendNormal(perlinNormal, tangent, binormal, normal);
    
    // 色
    output.color0 = textureColor * kColor[input.instanceID].color;

    // 法線
    output.color1.xyz = blendNormal;
    output.color1.w = 1.0f;

    // ポジション
    output.color2 = input.worldPosition;

    return output;
}