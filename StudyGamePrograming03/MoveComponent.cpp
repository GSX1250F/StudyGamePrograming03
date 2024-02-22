#include "MoveComponent.h"
#include "Actor.h"
#include "Math.h"

MoveComponent::MoveComponent(Actor* owner, int updateOrder) 
	: Component(owner), 
	mSpinSpeed(0.0f),
	mForwardSpeed(0.0f),
	mSpinAccel(0),
	mForwardAccel(0),
	mMass(1.0f),
	mForwardForce(0.0f),
	mSpinForce(0.0f)
{
}

MoveComponent::~MoveComponent()
{
}

void MoveComponent::Update(float deltatime)
{
	
	float spin = mOwner->GetSpin();
	Vector2 vel = mOwner->GetVelocity();
	Vector2 pos = mOwner->GetPosition();

	mForwardAccel = mForwardForce / mMass;
	mSpinAccel = mRadius * mSpinForce / mMass;
	//mForwardSpeed += mForwardAccel * deltatime;
	
	if (!Math::NearZero(mSpinAccel))		// 変化がほぼゼロのときは更新しない。
	{
		mSpinSpeed += mSpinAccel * deltatime;
		spin += mSpinSpeed * deltatime;
		mOwner->SetSpin(spin);
	}
	if (!Math::NearZero(mForwardAccel))		// 変化がほぼゼロのときは更新しない。
	{
		vel += Vector2(Math::Cos(spin), -Math::Sin(spin)) * mForwardAccel * deltatime;
		pos += vel * deltatime;
		
		//ラッピング処理　本当はここに書くべきではない。
		if (pos.x < -15.0f ) 
		{
			pos.x = 1024.0f; 
		}
		else if (pos.x > 1024.0f + 15.0f)
		{
			pos.x = 0.0f;
		}
		if (pos.y < -15.0f ) 
		{
			pos.y = 768.0f;
		}
		else if (pos.y < - 15.0f)
		{
			pos.y = 768.0f;
		}
		else if (pos.y > 768.0f + 15.0f)
		{
			pos.y = 0.0f;
		}

		mOwner->SetPosition(pos);
		mOwner->SetRotation(Math::Atan2(pos.x, pos.y));
	}
	

}
