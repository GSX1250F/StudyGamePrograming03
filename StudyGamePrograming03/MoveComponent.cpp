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
	
	Vector2 vel = mOwner->GetVelocity();	//�������x�擾
	Vector2 pos = mOwner->GetPosition();	//�����ʒu�擾
	pos += vel * deltatime;					// x = x0 + vt
	float spin = mOwner->GetSpin();		//�����p�x�擾
	spin += mSpinSpeed * deltatime;			// �� = ��0 + ��t 

	mForwardAccel = mForwardForce / mMass;
	vel += Vector2(Math::Cos(spin), -Math::Sin(spin)) * mForwardAccel * deltatime - mForwardResist * Vector2(vel.x * Math::Abs(vel.x), vel.y * Math::Abs(vel.y));	// v = v0 + at
	
	mSpinAccel = mSpinForce / ( mMass * mRadius) - mSpinResist * mSpinSpeed * Math::Abs(mSpinSpeed) ;	// a_�� = �� / rm
	mSpinSpeed += mSpinAccel * deltatime;	// �� = ��0 + at


	//if (!Math::NearZero(mForwardSpeed)){}		// �ω����قڃ[���̂Ƃ��͍X�V���Ȃ��B
	//if (!Math::NearZero(mSpinSpeed)){}		// �ω����قڃ[���̂Ƃ��͍X�V���Ȃ��B
	
	//���b�s���O�����@�{���͂����ɏ����ׂ��ł͂Ȃ��B
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
