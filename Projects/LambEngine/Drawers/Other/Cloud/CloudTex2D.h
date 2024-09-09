#pragma once

#pragma once
#include "../../BaseDrawer.h"
#include "Engine/Graphics/RenderContextManager/RenderContext/RenderContext.h"

/// <summary>
/// 板ポリ描画
/// </summary>
class CloudTex2D : public BaseDrawer {
public:
	static constexpr uint32_t kMaxDrawCount = 2048u;

	struct ShaderData {
		Vector2 randomVec;
		Vector3 normal;
		Vector3 tangent;
		float32_t density = 0.0_f32;
	};

	using WaterRenderContext = RenderContext<ShaderData, kMaxDrawCount>;
private:

	static const LoadFileNames kFileNames_;

public:
	CloudTex2D();
	CloudTex2D(const CloudTex2D&) = default;
	CloudTex2D(CloudTex2D&&) = default;
	~CloudTex2D() = default;

	CloudTex2D& operator=(const CloudTex2D&) = default;
	CloudTex2D& operator=(CloudTex2D&&) = default;

public:
	void Load();

	void Draw(
		const Mat4x4& worldMatrix,
		const Mat4x4& camera,
		Vector2 randomVec,
		float32_t density,
		uint32_t color,
		BlendType blend
	);
	void AllDraw(BlendType blend);
};