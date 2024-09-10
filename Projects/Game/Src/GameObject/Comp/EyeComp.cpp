#include "EyeComp.h"
#include "PlayerComp.h"
#include "TransformComp.h"
#include "LineComp.h"
#include "LineCollisionComp.h"
#include "EyeStateComp.h"
#include "EaseingComp.h"
#include "LineRenderDataComp.h"

void EyeComp::Init()
{
	transformComp_ = object_.AddComp<TransformComp>();
	beamLineComp_ = object_.AddComp<LineComp>();
	beamLineCollisionComp_ = object_.AddComp<LineCollisionComp>();
	beamLineRenderDataComp_ = object_.AddComp<LineRenderDataComp>();
	eyeStateComp_ = object_.AddComp<EyeStateComp>();
	easeingComp_ = object_.AddComp<EaseingComp>();
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
	beamLineComp_->end.y += playerTransformComp_->scale.y;
}

void EyeComp::Event() {

	if (playerComp_.empty()) {
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
			beamLineComp_->end = collsionCbjectTransFormComp->translate;
		}
		isCollision = true;
	}

	// 状態
	switch (eyeStateComp_->state) {
		// 探してる
	case EyeStateComp::State::kSearch:
		// 初期化
		eyeStateComp_->aimCount = 0.0f;
		eyeStateComp_->aimFixedCount = 0.0f;
		eyeStateComp_->fireCount = 0.0f;
		isEasesingStart_ = false;


		// 探している最中にプレイヤーを直視できたら狙う
		if(not isCollision){
			eyeStateComp_->state = EyeStateComp::State::kAim;
		}

		beamLineRenderDataComp_->color = 0x00ff00ff;


		break;
		// 狙いを定める
	case EyeStateComp::State::kAim:
		beamLineRenderDataComp_->color = 0xff0000ff;

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

		easeingComp_->GetEaseing().Update();

		// ビームの終わりをプレイヤーにする
		beamLineComp_->end = playerTransformComp_->translate;

		// 時間を加算
		eyeStateComp_->aimCount += object_.GetDeltaTime();

		// 狙いを定めてる最中の時間を超えたら固定
		if (eyeStateComp_->GetAimTime() <= eyeStateComp_->aimCount) {
			eyeStateComp_->state = EyeStateComp::State::kAimFixed;

			aimDirection_ = beamLineComp_->GetDirection();
		}

		break;
		// 狙いを固定
	case EyeStateComp::State::kAimFixed:
		beamLineRenderDataComp_->color = 0xff00ffff;
		// 時間を加算
		eyeStateComp_->aimFixedCount += object_.GetDeltaTime();

		// 固定時間を超えたら発射
		if (eyeStateComp_->GetAimFixedTime() <= eyeStateComp_->aimFixedCount) {
			eyeStateComp_->state = EyeStateComp::State::kFire;
		}

		break;
		// 発射
	case EyeStateComp::State::kFire:
		beamLineRenderDataComp_->color = 0xffff;

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
