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
    for (auto iter = mChunks.begin(); iter != mChunks.end(); iter++)
    {
        Mix_FreeChunk(iter->second);
    }
    mChunks.clear();
    for (auto iter = mMusics.begin(); iter != mMusics.end(); iter++)
    {
        Mix_FreeMusic(iter->second);
    }
    mMusics.clear();
}

void SoundPlayer::Shutdown()
{
    Mix_CloseAudio();               // SDL_Mixerクローズ 
}


void SoundPlayer::Play()
{
    // 再生待ち効果音を再生
    for (auto ck : mPendingPlayChunks)
    {
        if (ck.control == "replay")
        {
            // チャンネル指定の場合は一度再生を止めて再生する。
            if (ck.channel >= 0) { Mix_HaltChannel(ck.channel); }
            Mix_PlayChannel(ck.channel, ck.chunk, ck.repeat);
        }
        if (ck.control == "pause")
        {
            // 一時停止する。チャンネルが-1のときは全チャンネルを一時停止。
            Mix_Pause(ck.channel);
        }
        if (ck.control == "stop")
        {
            // 停止する。チャンネルが-1のときは全チャンネルを停止。
            Mix_HaltChannel(ck.channel);
        }
        if (ck.control == "resume")
        {
            // 再開する。チャンネルが-1のときは全チャンネルを再開。
            Mix_Resume(ck.channel);
        }
        if (ck.control == "play")
        {
            // チャンネル指定の場合は、再生中は何もしない。
            if ((ck.channel >= 0 && Mix_Playing(ck.channel) <= 0) || (ck.channel < 0))
            { 
                Mix_PlayChannel(ck.channel, ck.chunk, ck.repeat);
            }
        }
    }
    // 再生後、配列をクリア
    mPendingPlayChunks.clear();

    // 再生待ち音楽を再生
    for (auto mc : mPendingPlayMusics)
    {
        Mix_PlayMusic(mc.music, mc.repeat);            // 効果音再生
    }
    // 再生後、配列をクリア
    mPendingPlayChunks.clear();
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

Mix_Music* SoundPlayer::GetMusic(const std::string& filename)
{
    Mix_Music* music = nullptr;
    // すでにロード済みなら、その音を返す。
    auto iter = mMusics.find(filename);
    if (iter != mMusics.end())
    {
        music = iter->second;
    }
    else
    {
        // ファイルからロード
        music = Mix_LoadMUS(filename.c_str());
        if (!music)
        {
            SDL_Log("音楽ファイルの読み込みに失敗しました %s", filename.c_str());
            return nullptr;
        }
        mMusics.emplace(filename.c_str(), music);
    }

    return music;
}

void SoundPlayer::SetPendingPlayChunk(ChunkControl chunkCtl)
{
    // 再生待ち効果音の配列に加える。
    mPendingPlayChunks.emplace_back(chunkCtl);
}

void SoundPlayer::SetPendingPlayMusic(MusicControl musicCtl)
{
    // 再生待ち音楽の配列に加える。
    mPendingPlayMusics.emplace_back(musicCtl);
}
