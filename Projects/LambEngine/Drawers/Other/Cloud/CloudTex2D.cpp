#include "CloudTex2D.h"
#include "Engine/Graphics/TextureManager/TextureManager.h"
#include "Engine/Graphics/RenderContextManager/RenderContextManager.h"
#include "Utils/SafePtr.h"

#ifdef _DEBUG
#include "Utils/FileUtils.h"

#include "imgui.h"
#endif // _DEBUG

const LoadFileNames CloudTex2D::kFileNames_ =
LoadFileNames{
	.resourceFileName{"./Resources/EngineResources/Texture2D/Texture2D.obj"},
	.shaderName = ShaderFileNames{
		.vsFileName = "./Resources/Shaders/CloudTex2D/CloudTex2D.VS.hlsl",
		.psFileName = "./Resources/Shaders/CloudTex2D/CloudTex2D.PS.hlsl"
	}
};

CloudTex2D::CloudTex2D() :
	BaseDrawer()
{}

void CloudTex2D::Load()
{
	Lamb::SafePtr renderContextManager = RenderContextManager::GetInstance();

	renderContextManager->Load<WaterRenderContext>(kFileNames_, 3);

	renderSet = renderContextManager->Get(kFileNames_);
}

void CloudTex2D::Draw(
	const Mat4x4& worldMatrix,
	const Mat4x4& camera,
	Vector2 randomVec,
	float32_t density,
	uint32_t color,
	BlendType blend
) {
	Lamb::SafePtr renderContext = renderSet->GetRenderContextDowncast<WaterRenderContext>(blend);

	renderContext->SetShaderStruct(
		ShaderData{
			.randomVec = randomVec,
			.normal = Vector3(0.0f,1.0f,0.0f),
			.tangent = Vector3(0.0f,0.0f,1.0f),
			.density = density
		}
	);

	BaseDrawer::Draw(worldMatrix, camera, color, blend);
}

void CloudTex2D::AllDraw(BlendType blend)
{
	Lamb::SafePtr renderContext = renderSet->GetRenderContext(blend);
	renderContext->Draw();
	renderContext->ResetDrawCount();
}
