#include "SoundPlayer.h"
#include <SDL.h>
#include <SDL_mixer.h>
#include <algorithm>
#include "SoundComponent.h"

SoundPlayer::SoundPlayer(Game* game)
{}

SoundPlayer::~SoundPlayer()
{}

bool SoundPlayer::Initialize()
{
    // Initialize SDL.
    if (SDL_Init(SDL_INIT_AUDIO) < 0)
    {
        SDL_Log("Mixer�̏������Ɏ��s���܂���: %s", SDL_GetError());
        return false;
    }
    // Initialize SDL_mixer 
    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
    {
        SDL_Log("Mix_OpenAudio�̏������Ɏ��s���܂���: %s", SDL_GetError());
        return false;
    }        
	return true;
}

void SoundPlayer::UnloadData()
{
    while (mAliasNames.size() > 0)
    {
        Mix_FreeChunk(mAliasNames[0]);
        mAliasNames.erase(mAliasNames.begin());
    }
}

void SoundPlayer::Shutdown()
{
    // quit SDL_mixer
    Mix_CloseAudio();
}


void SoundPlayer::Play()
{
    //Control�ɉ�����AliasName��MCI�R���g���[�����s���B
    int i;
    if (mControls.size() > 0)
    {
        for (int i = 0; i < mControls.size(); i++)
        {
            if (mControls[i].substr(0, 4) == "play")
            {
                ControlPlay(i);
            }
            else if (mControls[i].substr(0, 6) == "replay")
            {
                ControlReplay(i);
            }
            else if (mControls[i].substr(0, 4) == "stop")
            {
                ControlStop(i);
            }
            else if (mControls[i].substr(0, 5) == "pause")
            {
                ControlPause(i);
            }
        }
        //control��delete�̏���
        bool flag = false;
        i = 0;
        while (flag == false)
        {
            if (mControls[i].substr(0, 6) == "delete")
            {
                std::string status = ControlGetStatus(i);
                if (status.substr(0, 7) == "playing")
                {
                    //�������Ȃ�
                }
                else
                {
                    ControlClose(mAliasNames[i]);
                    mAliasNames.erase(mAliasNames.begin() + i);
                    mControls.erase(mControls.begin() + i);
                    i -= 1;
                }
            }
            i += 1;
            if (i >= mControls.size() - 1)
            {
                flag = true;
            }
        }
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

Mix_Chunk* SoundPlayer::GetAliasName(std::string fileName)
{
    //�����t�@�C�����J���AmControls��mAliasNames���X�g�ɓo�^���AAliasName��Ԃ�
    int i = mAliasNames.size();
    //�t�@�C���I�[�v��
    Mix_Chunk* alias = Mix_LoadWAV(fileName.c_str());
    if (alias == NULL) 
    {
        return nullptr;
    }
    else
    {
        mAliasNames.emplace_back(alias);
        mControls.emplace_back("");
        return mAliasNames[i];
    }
}

void SoundPlayer::SetSoundControl(Mix_Chunk* aliasName, std::string control)
{
    if (mAliasNames.size() > 0)
    {
        for (int i = 0; i < mAliasNames.size(); i++)
        {
            if (mAliasNames[i] == aliasName)
            {
                mControls[i] = mControls[i] + control;
                break;
            }
        }
    }
}

std::string SoundPlayer::ControlGetStatus(int id)
{
    return std::string();
}

void SoundPlayer::ControlPlay(int id)
{
}

void SoundPlayer::ControlReplay(int id)
{
}

void SoundPlayer::ControlPause(int id)
{
}

void SoundPlayer::ControlStop(int id)
{
}

void SoundPlayer::ControlResume(int id)
{
}

void SoundPlayer::ControlClose(Mix_Chunk* aliasName)
{
}
