#include "MoveComponent.h"
#include "Actor.h"
#include "Math.h"

MoveComponent::MoveComponent(Actor* owner, int updateOrder) : Component(owner), mAngularSpeed(0.0f),mForwardSpeed(0.0f)
{
}

MoveComponent::~MoveComponent()
{
}

void MoveComponent::Update(float deltatime)
{
	if (!Math::NearZero(mAngularSpeed))		// �ω����قڃ[���̂Ƃ��͍X�V���Ȃ��B
	{
		float rot = mOwner->GetRotation();
		rot += mAngularSpeed * deltatime;
		mOwner->SetRotation(rot);
	}
	if (!Math::NearZero(mForwardSpeed))		// �ω����قڃ[���̂Ƃ��͍X�V���Ȃ��B
	{
		Vector2 pos = mOwner->GetPosition();
		pos += mOwner->GetForward() * mForwardSpeed * deltatime;
		mOwner->SetPosition(pos);
	}

}
