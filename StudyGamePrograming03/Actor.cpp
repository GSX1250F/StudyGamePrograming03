#include "Actor.h"
#include "Game.h"
#include "Component.h"
#include <algorithm>

Actor::Actor(Game* game)
	:mState(EActive),
	mPosition(Vector2::Zero),
	mVelocity(Vector2::Zero),
	mScale(1.0f),
	mRotation(0.0f),
	mRotSpeed(0.0f),
	mMass(1.0f),
	mRadius(0.0f),
	mGame(game)
{
	mGame->AddActor(this);
}

Actor::~Actor()
{
	mGame->RemoveActor(this);

	// ~Component�ł�RemoveActor���Ăяo�����̂ŁA�ʂ̎�ނ̃��[�v���g��
	while (!mComponents.empty())
	{
		delete mComponents.back();
	}
}

void Actor::Update(float deltaTime)
{
	if (mState == EActive || mState == EPaused)
	{
		// �ʒu�����X�V
		mCoordinate += mVelocity * deltaTime;
		mRotation += mRotSpeed * deltaTime;
		ConvertToPos();		//xy���W�n����ʍ��W�n�ɕϊ�
		UpdateComponents(deltaTime);
		UpdateActor(deltaTime);
	}
}

void Actor::UpdateComponents(float deltaTime)
{
	for (auto comp : mComponents)
	{
		comp->Update(deltaTime);
	}
}

void Actor::UpdateActor(float deltaTime)
{
}

//�V�����ǉ����ꂽ�C���v�b�g�p�֐�
void Actor::ProcessInput(const uint8_t* keyState)
{
	if (mState == EActive)
	{
		// First process input for components
		for (auto comp : mComponents)
		{
			comp->ProcessInput(keyState);
		}

		ActorInput(keyState);
	}
}

//�@�\�ǉ�����Ƃ��I�[�o�[���C�h����C���v�b�g�p�֐�
void Actor::ActorInput(const uint8_t* keyState)
{
}

void Actor::ConvertToPos()
{
	// xy���W�n����ʍ��W�n�ɕϊ��@(x,y)��(p,q)
	// �P���ɁAx,y�P�����s�N�Z��1���łƂ肠�����d����
	mPosition.x = mCoordinate.x + GetGame()->mWindowWidth / 2;
	mPosition.y = GetGame()->mWindowHeight / 2 - mCoordinate.y;

 
}

void Actor::AddComponent(Component* component)
{
	// �\�[�g�ς݂̔z��ő}���_��������
	int myOrder = component->GetUpdateOrder();
	auto iter = mComponents.begin();
	for (;
		iter != mComponents.end();
		++iter)
	{
		if (myOrder < (*iter)->GetUpdateOrder())
		{
			break;
		}
	}

	// �C�e���[�^�̈ʒu�̑O�ɗv�f��}������
	mComponents.insert(iter, component);
}

void Actor::RemoveComponent(Component* component)
{
	auto iter = std::find(mComponents.begin(), mComponents.end(), component);
	if (iter != mComponents.end())
	{
		mComponents.erase(iter);
	}
}