#include "gamesound.h"

namespace Tmpl8
{
    void GameSound::playSound(const std::string& filePath)
    {
        auto sound = std::make_shared<Audio::Sound>(filePath);
        sound->setLooping(false);
        sound->setVolume(globalVolume);
        sound->play();  
        activeSounds.push_back(sound); 
    }

    void GameSound::playMusic(const std::string& filePath)
    {
        stopMusic();
        auto music = std::make_shared<Audio::Sound>(filePath, Audio::Sound::Type::Stream);
        music->setLooping(true);  
        music->setVolume(globalVolume);
        music->play();            
        activeMusics.push_back(music); 
    }

    void GameSound::stopMusic()
    {
        for (auto& music : activeMusics)
        {
            if (music)  music->stop();  
        }
        activeMusics.clear(); 
    }

    // UNUSED
    void GameSound::playRollingSound(const std::string& filePath)
    {
        if (rollingSoundPlaying) return;
        auto snd_rolling = std::make_shared<Audio::Sound>(filePath);
        snd_rolling->setLooping(true);
        snd_rolling->setVolume(globalVolume / 2.0f);
        snd_rolling->play();
        activeSounds.push_back(snd_rolling);
        rollingSoundPlaying = true;
    }

    void GameSound::stopRollingSound()
    {
        for (auto i = activeSounds.begin(); i != activeSounds.end(); )
        {
            auto& sound = *i;
            if (sound && sound->isPlaying() && sound->isLooping())
            {
                sound->stop();
                i = activeSounds.erase(i);
            }
            else
            {
                ++i;
            }
        }
        rollingSoundPlaying = false;
    }
}
