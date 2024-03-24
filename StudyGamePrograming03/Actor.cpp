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

	// ~ComponentではRemoveActorが呼び出されるので、別の種類のループを使う
	while (!mComponents.empty())
	{
		delete mComponents.back();
	}
}

void Actor::Update(float deltaTime)
{
	if (mState == EActive || mState == EPaused)
	{
		// 位置情報を更新
		mCoordinate += mVelocity * deltaTime;
		mRotation += mRotSpeed * deltaTime;
		ConvertToPos();		//xy座標系を画面座標系に変換
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

//新しく追加されたインプット用関数
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

//機能追加するときオーバーライドするインプット用関数
void Actor::ActorInput(const uint8_t* keyState)
{
}

void Actor::ConvertToPos()
{
	// xy座標系を画面座標系に変換　(x,y)→(p,q)
	// 単純に、x,y１ずつをピクセル1ずつでとりあえず仕込む
	mPosition.x = mCoordinate.x + GetGame()->mWindowWidth / 2;
	mPosition.y = GetGame()->mWindowHeight / 2 - mCoordinate.y;

 
}

void Actor::AddComponent(Component* component)
{
	// ソート済みの配列で挿入点を見つける
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

	// イテレータの位置の前に要素を挿入する
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