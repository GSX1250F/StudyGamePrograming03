#include "SoundPlayer.h"
#include <SDL.h>
#include <SDL_mixer.h>
#include <algorithm>
#include "SoundComponent.h"

SoundPlayer::SoundPlayer(Game* game) : mGame(game)
{}

SoundPlayer::~SoundPlayer()
{}

bool SoundPlayer::Initialize()
{
    // SDL������
    if (SDL_Init(SDL_INIT_AUDIO) < 0)
    {
        SDL_Log("SDL�̏������Ɏ��s���܂���: %s", SDL_GetError());
        return false;
    }
    // SDL_mixer������
    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) < 0)
    {
        SDL_Log("SDL_mixer�̏������Ɏ��s���܂���: %s", SDL_GetError());
        return false;
    }
    // ������������16�ɐݒ�
    if (Mix_AllocateChannels(16) < 0)
    {
        SDL_Log("�����������̐ݒ�Ɏ��s���܂���: %s", SDL_GetError());
        return false;
    }

	return true;
}

void SoundPlayer::UnloadData()
{
    mChunks.clear();
}

void SoundPlayer::Shutdown()
{
    Mix_CloseAudio();               // SDL_Mixer�N���[�Y 
}


void SoundPlayer::Play()
{
    // ���ׂẴT�E���h�R���|�[�l���g���Đ�
    for (auto sndC : mSndCmpnts)
    {
        if (sndC->GetPlayable())
        {
            sndC->Play();

        }
    }
    // �폜�҂��T�E���h�R���|�[�l���g���ꎞ�z��ɒǉ��B
    std::vector<SoundComponent*> deadSndCmpnts;
    for (auto sndC : mSndCmpnts)
    {
        if (sndC->GetPendingRemove())
        {
            deadSndCmpnts.emplace_back(sndC);
        }
    }
    // �폜�҂��T�E���h�R���|�[�l���g���폜
    for (auto sndC : deadSndCmpnts)
    {
        RemoveSndCmpnt(sndC);
    }
}

void SoundPlayer::AddSndCmpnt(SoundComponent* sndC)
{
    mSndCmpnts.emplace_back(sndC);
}

void SoundPlayer::RemoveSndCmpnt(SoundComponent* sndC)
{
    auto iter = std::find(mSndCmpnts.begin(), mSndCmpnts.end(), sndC);
    mSndCmpnts.erase(iter);
}

Mix_Chunk* SoundPlayer::GetChunk(const std::string& filename)
{
    Mix_Chunk* chunk = nullptr;

    // ���łɃ��[�h�ς݂Ȃ�A���̉���Ԃ��B
    auto iter = mChunks.find(filename);
    if (iter != mChunks.end())
    {
        chunk = iter->second;
    }
    else
    {
        // �t�@�C�����烍�[�h
        chunk = Mix_LoadWAV(filename.c_str());
        if (!chunk)
        {
            SDL_Log("���ʉ��t�@�C���̓ǂݍ��݂Ɏ��s���܂��� %s", filename.c_str());
            return nullptr;
        }
        mChunks.emplace(filename.c_str(), chunk);
    }

    return chunk;
}
