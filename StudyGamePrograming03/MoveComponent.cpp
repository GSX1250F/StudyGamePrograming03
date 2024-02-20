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
	if (!Math::NearZero(mAngularSpeed))		// 変化がほぼゼロのときは更新しない。
	{
		float rot = mOwner->GetRotation();
		rot += mAngularSpeed * deltatime;
		mOwner->SetRotation(rot);
	}
	if (!Math::NearZero(mForwardSpeed))		// 変化がほぼゼロのときは更新しない。
	{
		Vector2 pos = mOwner->GetPosition();
		pos += mOwner->GetForward() * mForwardSpeed * deltatime;
		
		//ラッピング処理　本当はここに書くべきではない。
		if (pos.x < -15.0f ) 
		{
			pos.x = 1024.0f + 15.0f; 
		}
		else if (pos.x > 1024.0f + 15.0f)
		{
			pos.x = 0.0f - 15.0f;
		}
		if (pos.y < -15.0f ) 
		{
			pos.y = 768.0f + 15.0f;
		}
		else if (pos.x > 768.0f + 15.0f)
		{
			pos.x = 0.0f - 15.0f;
		}

		mOwner->SetPosition(pos);
	}

}
