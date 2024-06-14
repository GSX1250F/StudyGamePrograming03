#pragma once
#include "SDL.h"
#include <unordered_map>
#include <string>
#include <vector>

class Game
{
public:
	Game();
	bool Initialize();
	void RunLoop();
	void Shutdown();

	void AddActor(class Actor* actor);
	void RemoveActor(class Actor* actor);

	void AddSprite(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);

	SDL_Texture* GetTexture(const std::string& fileName);

	void SetRunning(bool isrunning) { mIsRunning = isrunning; }


	//Game-specific	
	void AddAsteroid(class Asteroid* ast);
	void RemoveAsteroid(class Asteroid* ast);
	std::vector<class Asteroid*>& GetAsteroids() { return mAsteroids; }


	//�Q�[���E�B���h�E�̑傫��
	int mWindowWidth;
	int mWindowHeight;

private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	void LoadData();
	void UnloadData();

	// �e�N�X�`���̔z��
	std::unordered_map<std::string, SDL_Texture*> mTextures;

	// ���ׂẴA�N�^�[
	std::vector<class Actor*> mActors;
	// ���ׂĂ̑҂��A�N�^�[
	std::vector<class Actor*> mPendingActors;

	// ���ׂĂ̕`�悳���X�v���C�g�R���|�[�l���g
	std::vector<class SpriteComponent*> mSprites;

	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	Uint32 mTicksCount;
	bool mIsRunning;
	// �A�N�^�[���X�V����
	bool mUpdatingActors;


	//Game-specific
	class Ship* mShip; // �v���C���[�̉F���D
	std::vector<class Asteroid*> mAsteroids; //���f��
};