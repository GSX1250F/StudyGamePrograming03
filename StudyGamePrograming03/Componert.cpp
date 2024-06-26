#include "Component.h"
#include "Actor.h"

Component::Component(Actor* owner, int updateOrder)	:mOwner(owner),	mUpdateOrder(updateOrder)
{
	// アクターのヴェクターに追加
	mOwner->AddComponent(this);
}

Component::~Component()
{
	mOwner->RemoveComponent(this);
}
