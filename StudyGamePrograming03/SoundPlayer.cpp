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
        SDL_Log("Mixerの初期化に失敗しました: %s", SDL_GetError());
        return false;
    }
    // Initialize SDL_mixer 
    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
    {
        SDL_Log("Mix_OpenAudioの初期化に失敗しました: %s", SDL_GetError());
        return false;
    }        
	return true;
}

void SoundPlayer::Shutdown()
{
    // quit SDL_mixer
    Mix_CloseAudio();
}

void SoundPlayer::UnloadData()
{
    while (mSoundControls.size() > 0)
    {
        Mix_FreeChunk(mSoundControls[0]->AliasName);
        mSoundControls.erase(mSoundControls.begin());
    }
}

void SoundPlayer::Play()
{
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
    //音声ファイルを開き、mControlsとmAliasNamesリストに登録し、AliasNameを返す
    //std::string cmd;
    //Dim cmd As String
    int i = mAliasNames.size();
    //ファイルオープン
    Mix_Chunk* alias;
    alias = Mix_LoadMUS
    cmd = "open " & fileName & " alias " & "AliasName" + i
        If mciSendString(cmd, Nothing, 0, 0) < > 0 Then
        Return Nothing
        Else
        mAliasNames.Add("AliasName" & i)
        mControls.Add("")
        Return mAliasNames(i)
        End If
}

void SoundPlayer::SetSoundControl(Mix_Chunk* aliasName, std::string control)
{
}
