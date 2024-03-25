#include "MoveComponent.h"
#include "Actor.h"
#include "Math.h"

MoveComponent::MoveComponent(Actor* owner, int updateOrder) 
	: Component(owner), 
	mMoveForce(Vector2::Zero),
	mMoveAccel(Vector2::Zero),
	mRotForce(0.0f),
	mRotAccel(0.0f),
	mMoveResist(0.0f),
	mRotResist(0.0f)
{
	
}

MoveComponent::~MoveComponent()
{
}

void MoveComponent::Update(float deltatime)
{
	// Actorの重心速度と回転速度を更新
	// Actorの位置と角度はActorのUpdateで更新
	if (mOwner->GetMass() != 0) {
		mMoveAccel = mMoveForce * (1 / mOwner->GetMass());	//重心加速度の計算
	}
	else { mMoveAccel = Vector2::Zero; }
	if (mOwner->GetImoment() != 0 && mOwner->GetRadius() != 0) {
		mRotAccel = mRotForce / mOwner->GetImoment() / mOwner->GetRadius();	//回転加速度の計算
	}
	else { mRotAccel = 0; }
	mOwner->SetVelocity(mOwner->GetVelocity() + mMoveAccel * deltatime);	//v = vo + at
	mOwner->SetRotSpeed(mOwner->GetRotSpeed() + mRotAccel * deltatime);		//ω = ωo + ωt
}
