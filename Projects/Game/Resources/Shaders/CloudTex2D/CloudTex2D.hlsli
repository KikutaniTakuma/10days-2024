#include "../Lamb.hlsli"

struct ShaderData {
    float32_t2 randomVec;
    float32_t3 normal;
    float32_t3 tangent;
    float32_t density;
};

StructuredBuffer<ShaderData> kShaderData : register(t2);