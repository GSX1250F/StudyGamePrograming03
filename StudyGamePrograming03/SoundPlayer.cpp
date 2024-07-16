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
    Mix_CloseAudio();               // SDL_Mixer�N���[�Y 
}


void SoundPlayer::Play()
{
    // �Đ��҂����ʉ����Đ�
    for (auto ck : mPendingPlayChunks)
    {
        if (ck.control == "replay")
        {
            // �`�����l���w��̏ꍇ�͈�x�Đ����~�߂čĐ�����B
            if (ck.channel >= 0) { Mix_HaltChannel(ck.channel); }
            Mix_PlayChannel(ck.channel, ck.chunk, ck.repeat);
        }
        if (ck.control == "pause")
        {
            // �ꎞ��~����B�`�����l����-1�̂Ƃ��͑S�`�����l�����ꎞ��~�B
            Mix_Pause(ck.channel);
        }
        if (ck.control == "stop")
        {
            // ��~����B�`�����l����-1�̂Ƃ��͑S�`�����l�����~�B
            Mix_HaltChannel(ck.channel);
        }
        if (ck.control == "resume")
        {
            // �ĊJ����B�`�����l����-1�̂Ƃ��͑S�`�����l�����ĊJ�B
            Mix_Resume(ck.channel);
        }
        if (ck.control == "play")
        {
            // �`�����l���w��̏ꍇ�́A�Đ����͉������Ȃ��B
            if ((ck.channel >= 0 && Mix_Playing(ck.channel) <= 0) || (ck.channel < 0))
            { 
                Mix_PlayChannel(ck.channel, ck.chunk, ck.repeat);
            }
        }
    }
    // �Đ���A�z����N���A
    mPendingPlayChunks.clear();

    // �Đ��҂����y���Đ�
    for (auto mc : mPendingPlayMusics)
    {
        Mix_PlayMusic(mc.music, mc.repeat);            // ���ʉ��Đ�
    }
    // �Đ���A�z����N���A
    mPendingPlayChunks.clear();
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

Mix_Music* SoundPlayer::GetMusic(const std::string& filename)
{
    Mix_Music* music = nullptr;
    // ���łɃ��[�h�ς݂Ȃ�A���̉���Ԃ��B
    auto iter = mMusics.find(filename);
    if (iter != mMusics.end())
    {
        music = iter->second;
    }
    else
    {
        // �t�@�C�����烍�[�h
        music = Mix_LoadMUS(filename.c_str());
        if (!music)
        {
            SDL_Log("���y�t�@�C���̓ǂݍ��݂Ɏ��s���܂��� %s", filename.c_str());
            return nullptr;
        }
        mMusics.emplace(filename.c_str(), music);
    }

    return music;
}

void SoundPlayer::SetPendingPlayChunk(ChunkControl chunkCtl)
{
    // �Đ��҂����ʉ��̔z��ɉ�����B
    mPendingPlayChunks.emplace_back(chunkCtl);
}

void SoundPlayer::SetPendingPlayMusic(MusicControl musicCtl)
{
    // �Đ��҂����y�̔z��ɉ�����B
    mPendingPlayMusics.emplace_back(musicCtl);
}
