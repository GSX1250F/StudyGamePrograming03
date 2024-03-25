#pragma once
#include <vector>
#include "Math.h"
#include <cstdint>

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

	// ゲームから呼び出される更新関数(オーバーライド不可)
	void Update(float deltaTime);
	// アクターが持つ全コンポーネントを更新(オーバーライド不可)
	void UpdateComponents(float deltaTime);
	// アクター独自の更新処理(オーバーライド可能)
	virtual void UpdateActor(float deltaTime);

	// ゲームから呼び出されるProcess Input(オーバーライド不可)
	void ProcessInput(const uint8_t* keyState);
	// アクター独自の入力処理(オーバーライド可能)
	virtual void ActorInput(const uint8_t* keyState);

	// Getters/setters
	const Vector2& GetPosition() const { return mPosition; }
	void SetPosition(const Vector2& pos) { mPosition = pos; }
	const Vector2& GetVelocity() const { return mVelocity; }
	void SetVelocity(const Vector2& vel) { mVelocity = vel; }
	float GetScale() const { return mScale; }
	void SetScale(float scale) { mScale = scale; }
	float GetRotation() const { return mRotation; }
	void SetRotation(float rotation) { mRotation = rotation; }
	float GetRadius() const { return mRadius * mScale; }
	void SetRadius(float radius) { mRadius = radius; }
	float GetRotSpeed() const { return mRotSpeed; }
	void SetRotSpeed(float rotspeed) { mRotSpeed = rotspeed; }
	float GetMass() const { return mMass; }
	void SetMass(float mass) { mMass = mass; }
	float GetImoment() const { return mImoment; }		
	void SetImoment(float moment) { mImoment = moment; }

	Vector2 GetForward() const { return Vector2(Math::Cos(mRotation), -Math::Sin(mRotation)); }		//向きの単位ベクトル

	State GetState() const { return mState; }
	void SetState(State state) { mState = state; }

	class Game* GetGame() { return mGame; }


	// Add/remove components
	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);

private:
	// アクターの状態
	State mState;

	// 移動
	Vector2 mPosition;		//画面上の位置
	Vector2 mVelocity;		//速度x,y
	float mScale;			//拡大率
	float mRotation;		//回転
	float mRotSpeed;		//回転速度
	float mMass;			//質量
	float mRadius;			//半径
	float mImoment;			//慣性モーメント
	
	std::vector<class Component*> mComponents;
	class Game* mGame;
};
