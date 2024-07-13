#pragma once
#include "Actor.h"

class Ship : public Actor
{
public:
	Ship(Game* game);
	
	void UpdateActor(float deltaTime) override;
	void ActorInput(const uint8_t* keyState) override;

	void Init();

private:
	float mLaserCooldown;
	bool mCrash;				//�Փˌ��m
	float mCrashingTime;		//�Փˉ��o����
	float mCrashCooldown;		//�Փˉ��o��A���Z�b�g�����܂ŃX�v���C�g����������
	Vector2 mCrashPos;		//�Փ˂����Ƃ��̈ʒu
	float mCrashRot;			//�Փ˂����Ƃ��̌���
	class CircleComponent* mCircle; 
	class SomeSpriteComponent* mSSC;
	class InputComponent* mIC;
};

