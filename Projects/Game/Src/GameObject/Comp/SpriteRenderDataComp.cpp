#include "SpriteRenderDataComp.h"
#include "Engine/Graphics/TextureManager/TextureManager.h"

#ifdef _DEBUG
#include "imgui.h"
#include "Utils/FileUtils.h"
#endif // _DEBUG

const std::array<std::string, uint32_t(SpriteRenderDataComp::Offset::kNum)> SpriteRenderDataComp::kOffsetEnumString_ = {
    "kMiddle",
    "kUp",
    "kUnder",
    "kLeft",
    "kRight",
    "kLeftUp",
    "kRightUp",
    "kLeftUnder",
    "kRightUnder"
};

const std::array<Mat4x4, uint32_t(SpriteRenderDataComp::Offset::kNum)> SpriteRenderDataComp::kOffsetMatrix = {
    Mat4x4::MakeTranslate(Vector3::kZero),
    Mat4x4::MakeTranslate(Vector3(0.0f, -1.0f, 0.0f) * 0.5f),
    Mat4x4::MakeTranslate(Vector3(0.0f, 1.0f, 0.0f) * 0.5f),
    Mat4x4::MakeTranslate(Vector3(1.0f, 0.0f, 0.0f) * 0.5f),
    Mat4x4::MakeTranslate(Vector3(-1.0f, 0.0f, 0.0f) * 0.5f),
    Mat4x4::MakeTranslate(Vector3(1.0f, -1.0f, 0.0f) * 0.5f),
    Mat4x4::MakeTranslate(Vector3(-1.0f, -1.0f, 0.0f) * 0.5f),
    Mat4x4::MakeTranslate(Vector3(1.0f, 1.0f, 0.0f) * 0.5f),
    Mat4x4::MakeTranslate(Vector3(-1.0f, 1.0f, 0.0f) * 0.5f)
};

void SpriteRenderDataComp::Init() {
    type = BlendType::kNone;
    color = Vector4::kIdentity;
    fileName = TextureManager::kWhiteTexturePath;


#ifdef _DEBUG
    filePaths_ = Lamb::GetFilePathFormDir("./", ".png");
    auto bmp = Lamb::GetFilePathFormDir("./", ".bmp");
    filePaths_.insert(filePaths_.end(), bmp.begin(), bmp.end());
#endif // _DEBUG

    texHandle = 0;
}

void SpriteRenderDataComp::FirstUpdate() {
#ifdef _DEBUG
    euler_ = uvTransform.rotate.ToEuler();
    uvTransform.rotate = Quaternion::EulerToQuaternion(euler_);
#endif // _DEBUG
    offsetTransform_ = kOffsetMatrix[static_cast<uint32_t>(offsetType)];

    userOffsetTransformMatrix_ = userOffsetTransform.GetMatrix();
}

void SpriteRenderDataComp::Debug([[maybe_unused]]const std::string& guiName)
{
#ifdef _DEBUG
	if (ImGui::TreeNode(guiName.c_str())) {
        // コンボボックスを使ってenumの値を選択する
        if (ImGui::BeginCombo("BlendType", kBlendTypeStrs[static_cast<uint32_t>(type)].c_str()))
        {
            for (uint32_t i = 0; i < static_cast<uint32_t>(BlendType::kNum); ++i)
            {
                bool isSelected = (type == static_cast<BlendType>(i));
                if (ImGui::Selectable(kBlendTypeStrs[i].c_str(), isSelected))
                {
                    type = static_cast<BlendType>(i);
                }
                if (isSelected)
                {
                    ImGui::SetItemDefaultFocus();
                }
            }
            ImGui::EndCombo();
        }

        // コンボボックスを使ってenumの値を選択する
        if (ImGui::BeginCombo("Offset", kOffsetEnumString_[static_cast<uint32_t>(offsetType)].c_str()))
        {
            for (uint32_t i = 0; i < static_cast<uint32_t>(Offset::kNum); ++i)
            {
                bool isSelected = (offsetType == static_cast<Offset>(i));
                if (ImGui::Selectable(kOffsetEnumString_[i].c_str(), isSelected))
                {
                    offsetType = static_cast<Offset>(i);
                }
                if (isSelected)
                {
                    ImGui::SetItemDefaultFocus();
                }
            }
            ImGui::EndCombo();
        }

        offsetTransform_ = kOffsetMatrix[static_cast<uint32_t>(offsetType)];


        euler_ = uvTransform.rotate.ToEuler();
        euler_ *= Lamb::Math::kToDegree<float>;

        ImGui::ColorEdit4("color", color.data());
        ImGui::NewLine();
        ImGui::Text("uv");
        ImGui::DragFloat3("scale", uvTransform.scale.data(), 0.001f);
        ImGui::DragFloat3("rotate", euler_.data(), 0.001f);
        ImGui::DragFloat3("translate", uvTransform.translate.data(), 0.001f);

        ImGui::NewLine();
        ImGui::Text("user offset");
        ImGui::DragFloat3("user scale", userOffsetTransform.scale.data(), 0.001f);
        ImGui::DragFloat3("user translate", userOffsetTransform.translate.data(), 0.001f);

        euler_ *= Lamb::Math::kToRadian<float>;
        uvTransform.rotate = Quaternion::EulerToQuaternion(euler_);

        ImGui::Text("texture %s", fileName.c_str());

        if (ImGui::Button("ファイルパス再読み込み")) {
            size_t size = filePaths_.size();
            filePaths_.clear();
            filePaths_.reserve(size);
            filePaths_ = Lamb::GetFilePathFormDir("./", ".png");
            auto bmp = Lamb::GetFilePathFormDir("./", ".bmp");
            filePaths_.insert(filePaths_.end(), bmp.begin(), bmp.end());
        }

        if (ImGui::TreeNode("テクスチャ読み込み")) {
            for (auto itr = filePaths_.begin(); itr != filePaths_.end(); itr++) {
                if (ImGui::Button(itr->string().c_str())) {
                    fileName = itr->string();
                    Lamb::SafePtr textureManager = TextureManager::GetInstance();
                    textureManager->LoadTexture(fileName);
                    texHandle = textureManager->GetHandle(fileName);
                }
            }
            ImGui::TreePop();
        }


		ImGui::TreePop();
	}
#endif // _DEBUG

}

const Mat4x4& SpriteRenderDataComp::GetOffsetMatrix() const
{
    return offsetTransform_;
}

const Mat4x4& SpriteRenderDataComp::GetUserOffsetMatrix() const
{
    return userOffsetTransformMatrix_;
}

void SpriteRenderDataComp::Save(nlohmann::json& json)
{
    SaveCompName(json);

    json["BlendType"] = kBlendTypeStrs[size_t(type)];
    json["color"] = nlohmann::json::array();
    for (auto& i : color) {
        json["color"].push_back(i);
    }
    json["offsetType"] = kOffsetEnumString_[size_t(offsetType)];
    json["fileName"] = fileName;
    json["uvTransform"]["scale"] = nlohmann::json::array();
    for (auto& i : uvTransform.scale) {
        json["uvTransform"]["scale"].push_back(i);
    }
    json["uvTransform"]["rotate"] = nlohmann::json::array();
    for (auto& i : uvTransform.rotate) {
        json["uvTransform"]["rotate"].push_back(i);
    }
    json["uvTransform"]["translate"] = nlohmann::json::array();
    for (auto& i : uvTransform.translate) {
        json["uvTransform"]["translate"].push_back(i);
    }
    json["userOffsetTransform"]["scale"] = nlohmann::json::array();
    for (auto& i : userOffsetTransform.scale) {
        json["userOffsetTransform"]["scale"].push_back(i);
    }
    json["userOffsetTransform"]["rotate"] = nlohmann::json::array();
    for (auto& i : userOffsetTransform.rotate) {
        json["userOffsetTransform"]["rotate"].push_back(i);
    }
    json["userOffsetTransform"]["translate"] = nlohmann::json::array();
    for (auto& i : userOffsetTransform.translate) {
        json["userOffsetTransform"]["translate"].push_back(i);
    }


}

void SpriteRenderDataComp::Load(nlohmann::json& json)
{
    std::string&& blendType = json["BlendType"].get<std::string>();
    for (size_t count = 0; const auto & i : kBlendTypeStrs) {
        if (blendType == i) {
            type = BlendType(count);
            break;
        }
        count++;
    }

    for (size_t i = 0; i < json["color"].size(); i++) {
        color[i] = json["color"][i];
    }
    std::string&& offsetTypeStr = json["offsetType"].get<std::string>();
    for (size_t count = 0; const auto & i : kOffsetEnumString_) {
        if (offsetTypeStr == i) {
            offsetType = Offset(count);
            break;
        }
        count++;
    }
    fileName = json["fileName"].get<std::string>();

    if (json.contains("uvTransform")) {
        for (size_t i = 0; i < uvTransform.scale.size(); i++) {
            uvTransform.scale[i] = json["uvTransform"]["scale"][i];
        }
        for (size_t i = 0; i < uvTransform.rotate.m.size(); i++) {
            uvTransform.rotate.m[i] = json["uvTransform"]["rotate"][i];
        }
        for (size_t i = 0; i < uvTransform.translate.size(); i++) {
            uvTransform.translate[i] = json["uvTransform"]["translate"][i];
        }
    }
    else {
        uvTransform.scale = Vector3::kIdentity;
        uvTransform.rotate.vector4 = Vector4::kWIdentity;
        uvTransform.translate = Vector3::kZero;

    }

    if (json.contains("userOffsetTransform")) {
        for (size_t i = 0; i < userOffsetTransform.scale.size(); i++) {
            userOffsetTransform.scale[i] = json["userOffsetTransform"]["scale"][i];
        }
        for (size_t i = 0; i < userOffsetTransform.rotate.m.size(); i++) {
            userOffsetTransform.rotate.m[i] = json["userOffsetTransform"]["rotate"][i];
        }
        for (size_t i = 0; i < userOffsetTransform.translate.size(); i++) {
            userOffsetTransform.translate[i] = json["userOffsetTransform"]["translate"][i];
        }
    }
    else {
        userOffsetTransform.scale = Vector3::kIdentity;
        userOffsetTransform.rotate.vector4 = Vector4::kWIdentity;
        userOffsetTransform.translate = Vector3::kZero;
    }
}

void SpriteRenderDataComp::Load()
{
    Lamb::SafePtr textureManager = TextureManager::GetInstance();
    textureManager->LoadTexture(fileName);
    texHandle = textureManager->GetHandle(fileName);
}
