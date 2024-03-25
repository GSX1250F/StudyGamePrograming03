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
	// ActorΜdS¬xΖρ]¬xπXV
	// ActorΜΚuΖpxΝActorΜUpdateΕXV
	if (mOwner->GetMass() != 0) {
		mMoveAccel = mMoveForce * (1 / mOwner->GetMass());	//dSΑ¬xΜvZ@F=ma  a=F*(1/m)
		//οRΝ = ¬³*οRW    Έ¬ = -¬³*οRW/ΏΚ
		Vector2 movedecel = mOwner->GetVelocity() * mMoveResist *0.01 * (1 / mOwner->GetMass());
		mMoveAccel -= movedecel;
	}
	else { mMoveAccel = Vector2::Zero; }
	if (mOwner->GetImoment() != 0 && mOwner->GetRadius() != 0) {
		mRotAccel = mRotForce * mOwner->GetRadius() / mOwner->GetImoment();	//ρ]Α¬xΜvZ Fr=Ia  a=Fr/I
		//οRΝ = ¬³*οRW    Έ¬ = -¬³*οRW*Όa/΅«[g
		float rotdecel = mOwner->GetRotSpeed() * mOwner->GetRadius() * mRotResist / mOwner->GetImoment();
		mRotAccel -= rotdecel;
	}
	else { mRotAccel = 0; }
	mOwner->SetVelocity(mOwner->GetVelocity() + mMoveAccel * deltatime);	//v = vo + at
	mOwner->SetRotSpeed(mOwner->GetRotSpeed() + mRotAccel * deltatime);		//Φ = Φo + Φt
}
