#pragma once
#include <vector>
#include "Math.h"
#include <SDL.h>

class Actor
{
public:
	enum State
	{
		EActive,		//稼働中
		EPaused,		//更新停止中
		EDead			//削除対象
	};

	Actor(class Game* game);
	virtual ~Actor();

	// ゲームから呼び出されるProcess Input(オーバーライド不可)
	void ProcessInput(const uint8_t* keyState);
	// アクター独自の入力処理(オーバーライド可能)
	virtual void ActorInput(const uint8_t* keyState);

	// ゲームから呼び出される更新関数(オーバーライド不可)
	void Update(float deltaTime);
	// アクター独自の更新処理(オーバーライド可能)
	virtual void UpdateActor(float deltaTime);
	
	// ゲッター・セッター
	// 位置
	const Vector2& GetPosition() const { return mPosition; }
	void SetPosition(const Vector2& pos) { mPosition = pos; }
	// 拡大率（質量は変えない。半径に影響する）
	const float& GetScale() const { return mScale; }
	void SetScale(const float& scale) { mScale = scale; }
	// 回転
	const float& GetRotation() const { return mRotation; }
	void SetRotation(const float& rotation) { mRotation = rotation; }
	// 半径
	const float& GetRadius() const { return mRadius * mScale; }	//拡大率を考慮
	void SetRadius(const float& radius) { mRadius = radius; }

	// 向きの単位ベクトル
	Vector2 GetForward() const { return Vector2(Math::Cos(mRotation), -Math::Sin(mRotation)); }

	// 状態
	State GetState() const { return mState; }
	void SetState(State state) { mState = state; }

	class Game* GetGame() { return mGame; }

	// Add/remove components
	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);

private:
	State mState;			//アクター状態
	Vector2 mPosition;		//画面上の位置
	float mScale;			//拡大率
	float mRotation;		//回転
	float mRadius;			//半径（拡大率は無視）
	std::vector<class Component*> mComponents;
	class Game* mGame;
};
