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
}
