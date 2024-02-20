#include "Ship.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "InputComponent.h"
#include "Game.h"
#include "Random.h"

Ship::Ship(Game* game) : Actor(game)
{
	//�����_���Ȍ����ŏ�����
	SetPosition(Vector2(1024.0f / 2.0f, 768.0f / 2.0f));
	SetRotation(Random::GetFloatRange(0.0f, Math::TwoPi));
	

	//�X�v���C�g�R���|�[�l���g�쐬�A�e�N�X�`���ݒ�
	SpriteComponent* sc = new SpriteComponent(this);
	sc->SetTexture(game->GetTexture("Assets/Ship.png"));

	//MoveComponent�쐬�A�O�i���x�̏�����
	MoveComponent* mc = new MoveComponent(this);
	mc->SetForwardSpeed(0.0f);

	//InputComponent�쐬
	InputComponent* mc = new InputComponent(this);
}

Ship::~Ship()
{
}
