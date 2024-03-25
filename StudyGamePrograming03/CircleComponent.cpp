#include "CircleComponent.h"
#include "Actor.h"

CircleComponent::CircleComponent(Actor* owner) : Component(owner)
{
	//半径はActorの半径で初期化
	mRadius = mOwner->GetRadius();
	//Actorの慣性モーメントを設定。一様の円板とする。(I=1/2*mR^2)
	mOwner->SetImoment(mOwner->GetScale()*mOwner->GetScale()*mRadius*mRadius/2);
}

float CircleComponent::GetRadius() const
{
	return mOwner->GetScale() * mRadius;
}

const Vector2& CircleComponent::GetCenter() const
{
	return  mOwner->GetPosition();
}

bool Intersect(const CircleComponent& a, const CircleComponent& b)
{
	// ２つのCircleComponentの中心間距離を計算
	Vector2 diff = a.GetCenter() - b.GetCenter();
	float dist = diff.Length();

	// ２つのCircleComponentの半径の和を計算 
	float sumRadius = a.GetRadius() + b.GetRadius();

	// 中心間距離 <= 半径の和 のとき、衝突したと判定
	if (dist <= sumRadius)
	{
		return true;
	}
	else
	{
		return false;
	}
}
