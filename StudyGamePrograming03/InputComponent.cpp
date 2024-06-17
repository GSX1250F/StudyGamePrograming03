#include "InputComponent.h"
#include "Actor.h"


InputComponent::InputComponent(Actor* owner, int updateOrder) 
	: MoveComponent(owner)
{}

InputComponent::~InputComponent()
{}

void InputComponent::ProcessInput(const SDL_Event event)
{
	//�ÓT�����w��MoveComponent�̂��߂̌v�Z
	//MoveComponent�ɂ͑O�i����]�����̗͂̍ő�l������n��
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
				rotforce = mMaxRotForce;		//�p�x�́{������CCW
				break;
			case SDLK_RIGHT:
				rotforce = - mMaxRotForce;		//�p�x�́{������CCW
				break;
		}
		
	}
	SetMoveForce(forwardforce * mOwner->GetForward());
	SetRotForce(rotforce);
}

