#include "InputComponent.h"
#include "Actor.h"


InputComponent::InputComponent(Actor* owner, int updateOrder) 
	: MoveComponent(owner)
{}

InputComponent::~InputComponent()
{}

void InputComponent::ProcessInput(const SDL_Event event)
{
	//古典物理学でMoveComponentのための計算
	//MoveComponentには前進か回転方向の力の最大値だけを渡す
	float forwardforce = 0.0f;
	float rotforce = 0.0f;
	if (event.type == SDL_KEYDOWN)
	{
		switch (event.key.keysym.sym)
		{
			case SDLK_UP:
				forwardforce = mMaxForwardForce;
				break;
			case SDLK_DOWN:
				forwardforce = - mMaxForwardForce;
				break;
			case SDLK_LEFT:
				rotforce = mMaxRotForce;		//角度の＋方向はCCW
				break;
			case SDLK_RIGHT:
				rotforce = - mMaxRotForce;		//角度の＋方向はCCW
				break;
		}
		
	}
	SetMoveForce(forwardforce * mOwner->GetForward());
	SetRotForce(rotforce);
}

