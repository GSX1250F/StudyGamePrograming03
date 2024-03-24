#include "MoveComponent.h"
#include "Actor.h"
#include "Math.h"

MoveComponent::MoveComponent(Actor* owner, int updateOrder) 
	: Component(owner), 
	mMoveForce(Vector2::Zero),
	mMoveAccel(Vector2::Zero),
	mRotForce(0.0f),
	mRotAccel(0.0f),
	mMoveResist(1.0f),
	mRotResist(1.0f)
{
	
}

MoveComponent::~MoveComponent()
{
}

void MoveComponent::Update(float deltatime)
{
	// Actorの重心速度と回転速度を更新
	// Actorの位置と角度はActorのUpdateで更新
	mMoveAccel = mMoveForce * (1 / mOwner->GetMass());	//重心加速度の計算
	mRotAccel = mRotForce / mOwner->GetMass();	//回転加速度の計算
	mOwner->SetVelocity(mOwner->GetVelocity() + mMoveAccel * deltatime);	//v = vo + at
	mOwner->SetRotation(mOwner->GetRotSpeed() + mRotAccel * deltatime);	//ω = ωo + ωt
}
