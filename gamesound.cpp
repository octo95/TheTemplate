#include "gamesound.h"
// The audio of the game is handled with the help of the Audio library made by Jeremiah: https://github.com/jpvanoosten/Audio

namespace Tmpl8
{
    // Function to play a sound effect.
    void GameSound::playSound(const std::string& filePath)
    {
        // Don't loop the SFX, put it at a specific volume and play it by adding it to the activeSounds.
        auto sound = std::make_shared<Audio::Sound>(filePath);
        sound->setLooping(false);
        sound->setVolume(globalVolume);
        sound->play();  
        activeSounds.push_back(sound); 
    }

    // Function to play a music.
    void GameSound::playMusic(const std::string& filePath)
    {
        // Stop any previous music, loop the music, put it at a specific volume and play it by adding it to the activeMusics.
        stopMusic();
        auto music = std::make_shared<Audio::Sound>(filePath, Audio::Sound::Type::Stream);
        music->setLooping(true);  
        music->setVolume(globalVolume);
        music->play();            
        activeMusics.push_back(music); 
    }

    // Helper function to stop previous musics.
    void GameSound::stopMusic()
    {
        for (auto& music : activeMusics)
        {
            if (music)  music->stop();  
        }
        activeMusics.clear(); 
    }

    // UNUSED (makes the game lag)
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
