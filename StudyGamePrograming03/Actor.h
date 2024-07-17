#pragma once
#include <vector>
#include "Math.h"
#include <cstdint>
#include <SDL.h>

class Actor
{
public:
	enum State
	{
		EActive,		//�ғ���
		EPaused,		//�X�V��~��
		EDead			//�폜�Ώ�
	};

	Actor(class Game* game);
	virtual ~Actor();

	// �Q�[������Ăяo�����Process Input(�I�[�o�[���C�h�s��)
	void ProcessInput(const uint8_t* keyState);
	// �A�N�^�[�Ǝ��̓��͏���(�I�[�o�[���C�h�\)
	virtual void ActorInput(const uint8_t* keyState);

	// �Q�[������Ăяo�����X�V�֐�(�I�[�o�[���C�h�s��)
	void Update(float deltaTime);
	// �A�N�^�[�Ǝ��̍X�V����(�I�[�o�[���C�h�\)
	virtual void UpdateActor(float deltaTime);
	
	// �Q�b�^�[�E�Z�b�^�[
	// �ʒu
	const Vector2& GetPosition() const { return mPosition; }
	void SetPosition(const Vector2& pos) { mPosition = pos; }
	// �g�嗦�i���ʂ͕ς��Ȃ��B���a�ɉe������j
	const float& GetScale() const { return mScale; }
	void SetScale(const float& scale) { mScale = scale; }
	// ��]
	const float& GetRotation() const { return mRotation; }
	void SetRotation(const float& rotation) { mRotation = rotation; }
	// ���a
	const float& GetRadius() const { return mRadius * mScale; }	//�g�嗦���l��
	void SetRadius(const float& radius) { mRadius = radius; }

	// �����̒P�ʃx�N�g��
	Vector2 GetForward() const { return Vector2(Math::Cos(mRotation), -Math::Sin(mRotation)); }

	// ���
	State GetState() const { return mState; }
	void SetState(State state) { mState = state; }

	class Game* GetGame() { return mGame; }

	// Add/remove components
	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);

private:
	State mState;			//�A�N�^�[���
	Vector2 mPosition;		//��ʏ�̈ʒu
	float mScale;			//�g�嗦
	float mRotation;		//��]
	float mRadius;			//���a�i�g�嗦�͖����j
	std::vector<class Component*> mComponents;
	class Game* mGame;
};
