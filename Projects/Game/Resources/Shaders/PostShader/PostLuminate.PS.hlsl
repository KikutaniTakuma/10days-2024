#include "Post.hlsli"
#include "../OutputStructs.hlsli"

struct LuminanceThreshold{
    float32_t3 num;
};

ConstantBuffer<LuminanceThreshold> gLuminanceThreshold : register(b1);

PixelShaderOutPut main(Output input) {
    float32_t4 color;

    color = tex.Sample(smp, input.uv);
    PixelShaderOutPut output;

    if(color.x == gLuminanceThreshold.num.x
       && color.y == gLuminanceThreshold.num.y
       && color.z == gLuminanceThreshold.num.z
    ){
        output.color = color;
    }else{
        discard;
    }

    return output;
}