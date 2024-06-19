#include "Game.h"
#include <SDL.h>
#include <SDL_image.h>
#include <algorithm>
#include "Actor.h"
#include "SpriteComponent.h"
#include "Ship.h"
#include "Asteroid.h"
#include "BackGround.h"
#include "ClearPict.h"
#include "Random.h"

Game::Game()
	:mWindow(nullptr),
	mRenderer(nullptr),
	mIsRunning(true),
	mUpdatingActors(false),
	mWindowWidth(1024),
	mWindowHeight(768)
{
}

bool Game::Initialize()
{
	// SDL������
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
	{
		SDL_Log("SDL���������ł��܂���: %s", SDL_GetError());
		return false;
	}
	// SDL�E�B���h�E���쐬
	mWindow = SDL_CreateWindow("Game Programming in C++", 100, 100, mWindowWidth, mWindowHeight, 0);
	if (!mWindow)
	{
		SDL_Log("�E�B���h�E�̍쐬�Ɏ��s���܂���: %s", SDL_GetError());
		return false;
	}
	// SDL�����_���[���쐬
	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!mRenderer)
	{
		SDL_Log("�����_���[�̍쐬�Ɏ��s���܂���: %s", SDL_GetError());
		return false;
	}
	// SDL_image��������
	if (IMG_Init(IMG_INIT_PNG) == 0)
	{
		SDL_Log("SDL_image���������ł��܂���: %s", SDL_GetError());
		return false;
	}

	Random::Init();		//�����ݒ�̏�����?

	LoadData();

	mTicksCount = SDL_GetTicks();

	return true;
}

void Game::RunLoop()
{
	while (mIsRunning)
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void Game::ProcessInput()
{
	SDL_Event event;
	// �L���[�ɃC�x���g������ΌJ��Ԃ�
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			mIsRunning = false;
		}
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)	// �L�[�������ꂽ����s����
		{
			mIsRunning = false;
		}
		
		mUpdatingActors = true;
		for (auto actor : mActors)
		{
			actor->ProcessInput(event);
		}
		mUpdatingActors = false;
	}	
}

void Game::UpdateGame()
{
	// �f���^�^�C���̌v�Z
	// �O�̃t���[������ 16ms �o�܂ő҂�
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));

	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;

	// �f���^�^�C�����ő�l�Ő�������
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}
	mTicksCount = SDL_GetTicks();

	// ���ׂẴA�N�^�[���X�V
	mUpdatingActors = true;
	for (auto actor : mActors)
	{
		actor->Update(deltaTime);
	}
	mUpdatingActors = false;

	// �҂��A�N�^�[��mActors�Ɉړ�
	for (auto pending : mPendingActors)
	{
		mActors.emplace_back(pending);
	}
	mPendingActors.clear();

	// ���񂾃A�N�^�[���ꎞ�z��ɒǉ�
	std::vector<Actor*> deadActors;
	for (auto actor : mActors)
	{
		if (actor->GetState() == Actor::EDead)
		{
			deadActors.emplace_back(actor);
		}
	}

	// ���񂾃A�N�^�[���폜
	for (auto actor : deadActors)
	{
		delete actor;
	}
}

void Game::GenerateOutput()
{
	SDL_SetRenderDrawColor(mRenderer, 220, 220, 220, 255);
	SDL_RenderClear(mRenderer);

	// ���ׂẴX�v���C�g�R���|�[�l���g��`��
	for (auto sprite : mSprites)
	{
		sprite->Draw(mRenderer);
	}

	SDL_RenderPresent(mRenderer);
}

void Game::Shutdown()
{
	UnloadData();
	IMG_Quit();
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}

void Game::LoadData()
{
	//�v���C���[�̉F���D���쐬
	mShip = new Ship(this);

	// ���f�����ŏ��ɕ�������
	int initialNumAsteroids = 15;		//�����l
	for (int i = 0; i < initialNumAsteroids; i++)
	{
		AddAsteroid();
	}

	//�w�i���쐬
	new BackGround(this);

	mClearPict = new ClearPict(this);
}

void Game::UnloadData()
{
	// �A�N�^�[��z�񂩂����
	while (!mActors.empty())
	{
		delete mActors.back();
	}

	// �e�N�X�`����z�񂩂����
	for (auto i : mTextures)
	{
		SDL_DestroyTexture(i.second);
	}
	mTextures.clear();
}

SDL_Texture* Game::GetTexture(const std::string& filename)
{
	SDL_Texture* tex = nullptr;

	auto iter = mTextures.find(filename);
	if (iter != mTextures.end())
	{
		tex = iter->second;
	}
	else
	{
		// �t�@�C�����烍�[�h
		SDL_Surface* surf = IMG_Load(filename.c_str());
		if (!surf)
		{
			SDL_Log("�e�N�X�`���t�@�C���̓ǂݍ��݂Ɏ��s���܂��� %s", filename.c_str());
			return nullptr;
		}

		// �T�[�t�F�C�X����e�N�X�`�����쐬
		tex = SDL_CreateTextureFromSurface(mRenderer, surf);
		SDL_FreeSurface(surf);
		if (!tex)
		{
			SDL_Log("�T�[�t�F�C�X����e�N�X�`���ɕϊ�����̂Ɏ��s���܂��� %s", filename.c_str());
			return nullptr;
		}

		mTextures.emplace(filename.c_str(), tex);
	}
	return tex;
}

void Game::AddActor(Actor* actor)
{
	// �A�N�^�[���X�V���́A�҂��A�N�^�[�ɒǉ�����
	if (mUpdatingActors)
	{
		mPendingActors.emplace_back(actor);
	}
	else
	{
		mActors.emplace_back(actor);
	}
}

void Game::RemoveActor(Actor* actor)
{
	// �����������A�N�^�[���҂��A�N�^�[�ɂ���ꍇ
	auto iter = std::find(mPendingActors.begin(), mPendingActors.end(), actor);
	if (iter != mPendingActors.end())
	{
		// �z��̈�ԍŌ�ƌ������A��������
		std::iter_swap(iter, mPendingActors.end() - 1);
		mPendingActors.pop_back();
	}

	// �����������A�N�^�[���A�N�^�[�ɂ���ꍇ
	iter = std::find(mActors.begin(), mActors.end(), actor);
	if (iter != mActors.end())
	{
		// �z��̈�ԍŌ�ƌ������A��������
		std::iter_swap(iter, mActors.end() - 1);
		mActors.pop_back();
	}
}

void Game::AddSprite(SpriteComponent* sprite)
{
	// �X�V���Ŕz��ɑ}������
	int myDrawOrder = sprite->GetDrawOrder();
	auto iter = mSprites.begin();
	for (; iter != mSprites.end(); ++iter)
	{
		if (myDrawOrder < (*iter)->GetDrawOrder())
		{
			break;
		}
	}

	mSprites.insert(iter, sprite);
}

void Game::RemoveSprite(SpriteComponent* sprite)
{
	auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
	mSprites.erase(iter);
}

//Game Specific
void Game::AddAsteroid()
{
	Asteroid* ast = new Asteroid(this);	
	mAsteroids.emplace_back(ast);	//���f������������Ƃ��͔z��̈�ԍŌ�ɒǉ�����B
}

void Game::RemoveAsteroid(Asteroid* ast)
{
	auto iter = std::find(mAsteroids.begin(), mAsteroids.end(), ast);
	if (iter != mAsteroids.end())
	{
		mAsteroids.erase(iter);
	}
}



