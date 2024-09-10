#include "BgmComp.h"
#include "AudioComp.h"

void BgmComp::Init() {
	audioComp_ = object_.AddComp<AudioComp>();
}

void BgmComp::FirstUpdate() {
	if (not audioComp_->GetAudio().IsStart()) {
		audioComp_->GetAudio().Start(audioComp_->volume, audioComp_->isLoop);
	}
}
