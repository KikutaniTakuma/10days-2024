#pragma once
#include "../Object.h"
#include "Drawers/Model/Model.h"


class UISpriteRenderDataComp : public IComp {
public:
	enum class Offset{
		kMiddle,
		kUp,
		kUnder,
		kLeft,
		kRight,
		kLeftUp,
		kRightUp,
		kLeftUnder,
		kRightUnder,

		kNum
	};

private:
	static const std::array<std::string, uint32_t(Offset::kNum)> kOffsetEnumString_;

public:
	static const std::array<Mat4x4, uint32_t(Offset::kNum)> kOffsetMatrix;

public:
	using IComp::IComp;

	~UISpriteRenderDataComp() = default;

	void Init() override;

	void FirstUpdate() override;


	void Debug(const std::string& guiName) override;

	const Mat4x4& GetOffsetMatrix() const;
	const Mat4x4& GetUserOffsetMatrix() const;

	void Save(nlohmann::json& json) override;
	void Load(nlohmann::json& json) override;

	void Load() override;

public:
	BlendType type;
	Vector4 color;
	std::string fileName;
	QuaternionTransform uvTransform;
	uint32_t texHandle = 0;
	
	Offset offsetType = Offset::kMiddle;

	QuaternionTransform userOffsetTransform;

private:
	Mat4x4 offsetTransform_ = Mat4x4::kIdentity;
	Mat4x4 userOffsetTransformMatrix_ = Mat4x4::kIdentity;

private:
#ifdef _DEBUG
	Vector3 euler_;
	std::vector<std::filesystem::path> filePaths_;
#endif // _DEBUG

};