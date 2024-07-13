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
        return false;
    }
    // Initialize SDL_mixer 
    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
    {
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
    //音声ファイルを開き、SoundControlリストに登録し、AliasNameを返す
    std::string cmd;

        Dim scl As New SoundControl
        scl.AliasName = "aliasName" & mSoundControls.Count    'aliasName = "aliasName" + id
        scl.Control = ""

        'ファイルオープン
        cmd = "open """ + fileName + """ alias " + scl.AliasName
        If mciSendString(cmd, Nothing, 0, 0) < > 0 Then
        Return Nothing
        Else
        mSoundControls.Add(scl)
        Return scl.AliasName
        End If
}

void SoundPlayer::SetSoundControl(Mix_Chunk* aliasName, std::string control)
{
}
