#pragma once
#ifndef _BOSS_H
#define _BOSS_H

#include "EnemyBase.h"

enum class EBossState : int {
	PREPARE_AWAKING = 0,
	AWAKING = 1,
	MOVING = 2,
	SHOOTING = 3,
	MOVING_AND_SHOOTING = 4,
	PREPARE_SPLEEPING = 5,
	SLEEPING = 6
};

class CBoss : public CEnemyBase {
private:
	static int __cloneCount;
	static std::unordered_map<int, CBoss*> __cloneBosses;

	EBossState state = EBossState::PREPARE_AWAKING;
	EBossState prevState;
	std::string keyDisplay; // key of animation for rendering

	bool sleeping;
	int stepMove;

	DWORD prevShootingTime;
	int shootingTimes;

	void SetState(EBossState nextState);

	void OnPrepareAwaking();
	void OnAwaking();
	void OnMoving();
	void OnShooting();
	void OnMovingAndShooting();
	void OnPrepareSleeping();
	void OnSleeping();

	void DirectiveAwaking();
	void CallNextClone();
	void CallSleepingClone();
	void InitiateNewClone();

public:
	CBoss();

	void Update(DWORD dt) override;
	void Render() override;

	void OnCollision(CCollider2D* self, LPCOLLISIONEVENT coEvent) override;

	static std::unordered_map<int, CBoss*> GetCloneBooses() { return __cloneBosses; }
};

#endif // !_BOSS_H
