#include "InputComponent.h"
#include "Actor.h"


InputComponent::InputComponent(Actor* owner, int updateOrder) 
	: MoveComponent(owner)
{}

InputComponent::~InputComponent()
{}

void InputComponent::ProcessInput(const SDL_Event event)
{
	//ŒÃ“T•¨—Šw‚ÅMoveComponent‚Ì‚½‚ß‚ÌŒvŽZ
	//MoveComponent‚É‚Í‘Oi‚©‰ñ“]•ûŒü‚Ì—Í‚ÌÅ‘å’l‚¾‚¯‚ð“n‚·
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
				rotforce = mMaxRotForce;		//Šp“x‚Ì{•ûŒü‚ÍCCW
				break;
			case SDLK_RIGHT:
				rotforce = - mMaxRotForce;		//Šp“x‚Ì{•ûŒü‚ÍCCW
				break;
		}
		
	}
	SetMoveForce(forwardforce * mOwner->GetForward());
	SetRotForce(rotforce);
}

