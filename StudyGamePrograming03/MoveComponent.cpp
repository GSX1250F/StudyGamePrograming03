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
	// Actor�̏d�S���x�Ɖ�]���x���X�V
	// Actor�̈ʒu�Ɗp�x��Actor��Update�ōX�V
	mMoveAccel = mMoveForce * (1 / mOwner->GetMass());	//�d�S�����x�̌v�Z
	mRotAccel = mRotForce / mOwner->GetMass();	//��]�����x�̌v�Z
	mOwner->SetVelocity(mOwner->GetVelocity() + mMoveAccel * deltatime);	//v = vo + at
	mOwner->SetRotation(mOwner->GetRotSpeed() + mRotAccel * deltatime);	//�� = ��o + ��t
}
