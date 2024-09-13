#pragma once
#include "../Object.h"


class SpriteRenderComp : public IComp {
public:
	using IComp::IComp;

	~SpriteRenderComp() = default;

	void Init() override;

	void Draw(CameraComp* cameraComp) override;

	void Save(nlohmann::json& json) override;
	void Load(nlohmann::json& json) override;

	void Debug(const std::string& guiName);

public:
	// 描画するかのフラグ
	// trueなら描画
	bool isDraw = true;

private:
	Lamb::SafePtr<class Texture2D> tex2D_;

	Lamb::SafePtr<class SpriteRenderDataComp> renderDataComp_;

	Lamb::SafePtr<class TransformComp> transformComp_;
};