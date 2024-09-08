#include "EaseingComp.h"

void EaseingComp::Init() {
	ease_ = std::make_unique<Easeing>();
}

void EaseingComp::Finalize() {
	ease_.reset();
}

Easeing& EaseingComp::GetEaseing()
{
	return *ease_;
}
