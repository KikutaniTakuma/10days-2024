#include "EyeComp.h"
#include "PlayerComp.h"
#include "TransformComp.h"
#include "LineComp.h"
#include "LineCollisionComp.h"
#include "EyeStateComp.h"
#include "EaseingComp.h"
#include "LineRenderDataComp.h"
#include "ChildrenObjectComp.h"
#include "LineConvertTransformComp.h"

#include "Engine/Graphics/RenderingManager/RenderingManager.h"
#include "SpriteRenderDataComp.h"
#include "CloudComp.h"
#include "CsvDataComp.h"

#include "EyeAudioComp.h"

void EyeComp::Init()
{
	transformComp_ = object_.AddComp<TransformComp>();
	beamLineComp_ = object_.AddComp<LineComp>();
	beamLineCollisionComp_ = object_.AddComp<LineCollisionComp>();
	beamLineRenderDataComp_ = object_.AddComp<LineRenderDataComp>();
	eyeStateComp_ = object_.AddComp<EyeStateComp>();
	easeingComp_ = object_.AddComp<EaseingComp>();
	childrenObjectComp_ = object_.AddComp<ChildrenObjectComp>();
	object_.AddComp<EyeAudioComp>();

	Vector4 bloomColor = 0xd56ff9ff;
	RenderingManager::GetInstance()->SetBloomColor({ bloomColor.color.r,bloomColor.color.g,bloomColor.color.b });
}

void EyeComp::SetPlayerComp(PlayerComp* playerComp) {
	playerComp_ = playerComp;
	if (playerComp_.empty()) {
		return;
	}
	playerTransformComp_ = playerComp_->getObject().GetComp<TransformComp>();
	beamLineComp_->end = playerTransformComp_->translate;

	playerObbComp_ = playerComp_->getObject().GetComp<ObbComp>();
}

void EyeComp::SetBeamTransformComp() {
	for (const auto& i : childrenObjectComp_->GetObjects()) {
		if (i->HasComp<LineConvertTransformComp>()) {
			childrenBeamLineComp_ = i->GetComp<LineComp>();
			childrenTransformComp_ = i->GetComp<TransformComp>();
			childrenTransformComp_->SetParent(nullptr);
			if (i->HasComp<SpriteRenderDataComp>()) {
				childrenBeamRenderDataComp_ = i->GetComp<SpriteRenderDataComp>();
			}
		}
	}
}

void EyeComp::Save(nlohmann::json& json) {
	SaveCompName(json);
}

void EyeComp::Load([[maybe_unused]]nlohmann::json& json) {
}

void EyeComp::FirstUpdate() {
	if (playerComp_.empty()) {
		return;
	}

	// ビームの始まりをEyeのポジションにする
	beamLineComp_->start = transformComp_->translate;
	// ビームの終わりをプレイヤーにして当たり判定をとる
	beamLineComp_->end = playerTransformComp_->translate;

	if (eyeStateComp_->state == EyeStateComp::State::kAimFixed or eyeStateComp_->state == EyeStateComp::State::kFire) {
		beamLineComp_->end = beamLineComp_->start + aimDirection_ * ((aimPoint_ - beamLineComp_->start).Length() + playerTransformComp_->scale.Length() * 3.0f);
	}
}

void EyeComp::Event() {

	if (playerComp_.empty() or playerComp_->GetIsGoal()) {
		return;
	}

	// 当たっていたらポインタを持っている
	// 持っていなかったらプレイヤーを直視できてる
	bool isCollision = false;
	Lamb::SafePtr mostNearCollisionObjectPtr = beamLineCollisionComp_->GetMostNearCollisionObjectPtr();
	if (mostNearCollisionObjectPtr.have()) {
		Lamb::SafePtr collsionCbjectTransFormComp = mostNearCollisionObjectPtr->GetComp<TransformComp>();
		// 長さを当たっているオブジェクトの長さにする
		if (eyeStateComp_->state == EyeStateComp::State::kAimFixed or eyeStateComp_->state == EyeStateComp::State::kFire) {
			beamLineComp_->end = beamLineComp_->start + aimDirection_ * (collsionCbjectTransFormComp->translate - beamLineComp_->start).Length();
		}
		else {
			beamLineComp_->end = beamLineComp_->start + beamLineComp_->GetDirection() * (collsionCbjectTransFormComp->translate - beamLineComp_->start).Length();
		}

		if (mostNearCollisionObjectPtr->HasComp<CloudComp>() and not isDeleteCloud_ and eyeStateComp_->state == EyeStateComp::State::kFire) {

			int32_t mussX = mostNearCollisionObjectPtr->GetComp<CloudComp>()->GetMassX();
			int32_t mussY = mostNearCollisionObjectPtr->GetComp<CloudComp>()->GetMassY();

			playerComp_->getObject().GetComp<CsvDataComp>()->SetNumber(mussX, mussY, 0);

			mostNearCollisionObjectPtr->GetComp<CloudComp>()->SetIsDead(true);

			isDeleteCloud_ = true;

		}

		isCollision = true;

	}

	Vector4 bloomColor = 0xd56ff9ff;

	// 状態
	switch (eyeStateComp_->state) {
		// 探してる
	case EyeStateComp::State::kSearch:
		// 初期化
		eyeStateComp_->aimCount = 0.0f;
		eyeStateComp_->aimFixedCount = 0.0f;
		eyeStateComp_->fireCount = 0.0f;
		isDeleteCloud_ = false;

		// 探している最中にプレイヤーを直視できたら狙う
		// かつ、プレイヤーが透明じゃない
		if(not isCollision and not playerComp_->GetIsInvisible()){
			eyeStateComp_->state = EyeStateComp::State::kAim;
		}

		beamLineRenderDataComp_->color = 0x00ff00ff;

		// もしイージングしてなかったら開始する
		if (not isEasesingStart_) {
			easeingComp_->GetEaseing().Start(easeingComp_->isLoop, easeingComp_->spdT, easeingComp_->type);
			isEasesingStart_ = true;
			easeingStartPosX = transformComp_->translate.x;
		}
		// イージングが開始されたら
		else if (isEasesingStart_ and easeingComp_->GetEaseing().GetIsActive()) {
			// イージングさせて近づけさせる
			transformComp_->translate.x = easeingComp_->GetEaseing().Get(easeingStartPosX, playerTransformComp_->translate.x);
		}
		// それ以外は完全に一致させる
		else {
			transformComp_->translate.x = playerTransformComp_->translate.x;
		}

		break;
		// 狙いを定める
	case EyeStateComp::State::kAim:
		beamLineRenderDataComp_->color = 0xff0000ff;
		bloomColor = beamLineRenderDataComp_->color;
		RenderingManager::GetInstance()->SetBloomColor({ bloomColor.color.r,bloomColor.color.g,bloomColor.color.b });
		childrenTransformComp_->scale = Vector3::kIdentity * 2.0f;

		// 狙いを定めている最中にプレイヤーを直視できなくなったらSearchに移行
		if(isCollision){
			eyeStateComp_->state = EyeStateComp::State::kSearch;
		}

		// もしイージングしてなかったら開始する
		if (not isEasesingStart_) {
			easeingComp_->GetEaseing().Start(easeingComp_->isLoop, easeingComp_->spdT, easeingComp_->type);
			isEasesingStart_ = true;
			easeingStartPosX = transformComp_->translate.x;
		}
		// イージングが開始されたら
		else if (isEasesingStart_ and easeingComp_->GetEaseing().GetIsActive()) {
			// イージングさせて近づけさせる
			transformComp_->translate.x = easeingComp_->GetEaseing().Get(easeingStartPosX, playerTransformComp_->translate.x);
		}
		// それ以外は完全に一致させる
		else {
			transformComp_->translate.x = playerTransformComp_->translate.x;
		}

		// ビームの終わりをプレイヤーにする
		beamLineComp_->end = playerTransformComp_->translate;

		// 時間を加算
		eyeStateComp_->aimCount += object_.GetDeltaTime();

		// 狙いを定めてる最中の時間を超えたら固定
		if (eyeStateComp_->GetAimTime() <= eyeStateComp_->aimCount) {
			eyeStateComp_->state = EyeStateComp::State::kAimFixed;

			aimPoint_ = playerTransformComp_->translate;
			aimDirection_ = (aimPoint_ - beamLineComp_->start).Normalize();
		}

		break;
		// 狙いを固定
	case EyeStateComp::State::kAimFixed:
		isEasesingStart_ = false;

		// 時間を加算
		eyeStateComp_->aimFixedCount += object_.GetDeltaTime();

		// 固定時間を超えたら発射
		if (eyeStateComp_->GetAimFixedTime() <= eyeStateComp_->aimFixedCount) {
			eyeStateComp_->state = EyeStateComp::State::kFire;
		}

		break;
		// 発射
	case EyeStateComp::State::kFire:
		childrenTransformComp_->scale = Vector3::kIdentity * 10.0f;
		beamLineRenderDataComp_->color = 0xd56ff9ff;
		bloomColor = beamLineRenderDataComp_->color;
		RenderingManager::GetInstance()->SetBloomColor({ bloomColor.color.r,bloomColor.color.g,bloomColor.color.b });

		// 時間を加算
		eyeStateComp_->fireCount += object_.GetDeltaTime();

		// 当たり判定の結果を設定
		playerComp_->SetIsBeamCollision(playerObbComp_->IsCollision(beamLineComp_->start, beamLineComp_->end));

		if (eyeStateComp_->GetFireTime() <= eyeStateComp_->fireCount) {
			eyeStateComp_->state = EyeStateComp::State::kSearch;
		}

		break;
	default:
		// ここに入ったらエラー
		throw Lamb::Error::Code<EyeComp>("State error", ErrorPlace);
		break;
	}

}

void EyeComp::Update() {
	if (childrenBeamLineComp_.empty()) {
		return;
	}
	
	if (eyeStateComp_->state != EyeStateComp::State::kSearch) {
		childrenBeamLineComp_->start = beamLineComp_->start;
		childrenBeamLineComp_->end = beamLineComp_->end;
	}
	else {
		beamLineComp_->start = Vector3::kZero;
		beamLineComp_->end = Vector3::kZero;
		childrenBeamLineComp_->start = Vector3::kZero;
		childrenBeamLineComp_->end = Vector3::kZero;
	}

	if (childrenBeamRenderDataComp_.empty()) {
		return;
	}

	childrenBeamRenderDataComp_->color = beamLineRenderDataComp_->color;
}

bool EyeComp::IsFire() const {
	return eyeStateComp_->state == EyeStateComp::State::kFire;
}

bool EyeComp::IsAiming() const {
	return eyeStateComp_->state == EyeStateComp::State::kAim;
}

bool EyeComp::IsAimFixed() const {
	return eyeStateComp_->state == EyeStateComp::State::kAimFixed;
}
