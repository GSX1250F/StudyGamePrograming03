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
	mRadius(1.0f),
	mForwardForce(0.0f),
	mSpinForce(0.0f)
{
}

MoveComponent::~MoveComponent()
{
}

void MoveComponent::Update(float deltatime)
{
	
	Vector2 vel = mOwner->GetVelocity();	//初期速度取得
	Vector2 pos = mOwner->GetPosition();	//初期位置取得
	pos += vel * deltatime;					// x = x0 + vt
	float spin = mOwner->GetSpin();		//初期角度取得
	spin += mSpinSpeed * deltatime;			// Θ = Θ0 + ωt 

	mForwardAccel = mForwardForce / mMass;
	vel += Vector2(Math::Cos(spin), -Math::Sin(spin)) * mForwardAccel * deltatime - mForwardResist * Vector2(vel.x * Math::Abs(vel.x), vel.y * Math::Abs(vel.y));	// v = v0 + at
	
	mSpinAccel = mSpinForce / ( mMass * mRadius) - mSpinResist * mSpinSpeed * Math::Abs(mSpinSpeed) ;	// a_Θ = ω / rm
	mSpinSpeed += mSpinAccel * deltatime;	// ω = ω0 + at


	//if (!Math::NearZero(mForwardSpeed)){}		// 変化がほぼゼロのときは更新しない。
	//if (!Math::NearZero(mSpinSpeed)){}		// 変化がほぼゼロのときは更新しない。
	
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

	mOwner->SetVelocity(vel);
	mOwner->SetPosition(pos);
	mOwner->SetSpin(spin);

	

}
