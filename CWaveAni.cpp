#include "pch.h"
#include "CWaveAni.h"
#include "CWave.h"
#include "CObj.h"
#include "CAnimator.h"
#include "CAnimation.h"

CWaveAni::CWaveAni()
{
	// Animator 에서 사용할 Image 로딩
	GetAnimator()->LoadAnimation(L"animation\\WAVE_UP.anim");
	GetAnimator()->LoadAnimation(L"animation\\WAVE_UPM.anim");
	GetAnimator()->LoadAnimation(L"animation\\WAVE_DOWN.anim");
	GetAnimator()->LoadAnimation(L"animation\\WAVE_DOWNM.anim");
	GetAnimator()->LoadAnimation(L"animation\\WAVE_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\WAVE_LEFTM.anim");
	GetAnimator()->LoadAnimation(L"animation\\WAVE_RIGHT.anim");
	GetAnimator()->LoadAnimation(L"animation\\WAVE_RIGHTM.anim");
}

CWaveAni::~CWaveAni()
{
}
