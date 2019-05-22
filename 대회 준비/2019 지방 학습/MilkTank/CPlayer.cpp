#include "DXUT.h"
#include "Header.h"

CPlayer::CPlayer(D3DXVECTOR2 pos, CCamera * camrea)
	: CMatrix(), camera(camera), velocity_Y(0), jumpCount(1), upgrade(0), 
	homingMissile(10.0f), longShot(10.0f), powerUp(10.0f), doubleJump(10.0f), speedUp(false),
	attackTimer(0), attackTime(0.05f), attackIntervalTimer(0), attackIntervalTime(0.5f),
	isAttacking(false), isAttackInterval(false), isDie(false),
	isInvincible(true), invincibleTimaer(0), invincibleTimae(2),
	mainAttackCounter(0), mainAttackCount(1),
	skyAttackCounter(0), skyAttackCount(5),
	homingAttackCounter(0), homingAttackCount(2)
{
	position = pos;
	ground_Y_Pos = pos.y;
	center = D3DXVECTOR2(100, 50);
}

void CPlayer::Update(float deltaTime)
{
}

void CPlayer::Render(LPD3DXSPRITE sprite)
{
}

void CPlayer::Move(int dir, float deltaTime)
{
}

void CPlayer::Attack()
{
}

void CPlayer::Jump()
{
}
