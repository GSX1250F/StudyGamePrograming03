#include "BackGround.h"
#include "Game.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"

BackGround::BackGround(Game* game)
{
	//MoveComponent�쐬
	MoveComponent* mc = new MoveComponent(this);
	mc->SetVelocity(Vector2(scrollspeed, 0.0f));

	//�X�v���C�g�R���|�[�l���g�쐬�A�e�N�X�`���ݒ�
	SpriteComponent* sc = new SpriteComponent(this, updateorder);
	sc->SetTexture(game->GetTexture(filename));
	offset = sc->GetTexWidth();

	SetPosition(Vector2(GetGame()->mWindowWidth * 0.5f + id * offset, GetGame()->mWindowHeight * 0.5f));

	//�w�i���Q�[���ɒǉ�
	game->AddBackGround(this);
}

