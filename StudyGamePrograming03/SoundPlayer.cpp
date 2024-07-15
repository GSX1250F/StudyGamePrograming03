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
    // SDL初期化
    if (SDL_Init(SDL_INIT_AUDIO) < 0)
    {
        SDL_Log("SDLの初期化に失敗しました: %s", SDL_GetError());
        return false;
    }
    // SDL_mixer初期化
    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) < 0)
    {
        SDL_Log("SDL_mixerの初期化に失敗しました: %s", SDL_GetError());
        return false;
    }
    // 同時発声数を16に設定
    if (Mix_AllocateChannels(16) < 0)
    {
        SDL_Log("同時発声数の設定に失敗しました: %s", SDL_GetError());
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
    Mix_CloseAudio();               // SDL_Mixerクローズ 
}


void SoundPlayer::Play()
{
    // すべてのサウンドコンポーネントを再生
    for (auto sndC : mSndCmpnts)
    {
        if (sndC->GetPlayable())
        {
            sndC->Play();

        }
    }
    // 削除待ちサウンドコンポーネントを一時配列に追加。
    std::vector<SoundComponent*> deadSndCmpnts;
    for (auto sndC : mSndCmpnts)
    {
        if (sndC->GetPendingRemove())
        {
            deadSndCmpnts.emplace_back(sndC);
        }
    }
    // 削除待ちサウンドコンポーネントを削除
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

    // すでにロード済みなら、その音を返す。
    auto iter = mChunks.find(filename);
    if (iter != mChunks.end())
    {
        chunk = iter->second;
    }
    else
    {
        // ファイルからロード
        chunk = Mix_LoadWAV(filename.c_str());
        if (!chunk)
        {
            SDL_Log("効果音ファイルの読み込みに失敗しました %s", filename.c_str());
            return nullptr;
        }
        mChunks.emplace(filename.c_str(), chunk);
    }

    return chunk;
}
