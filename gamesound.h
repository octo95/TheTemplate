#pragma once
#include <Audio/Sound.hpp>
#include "tile.h"

namespace Tmpl8
{
	// Define the SoundType as a vector of shared pointers to Audio::Sound
    typedef std::vector<std::shared_ptr<Audio::Sound>> SoundType;

    class GameSound
    {
        public:
		    // Global volume for all sounds
            float globalVolume = 0.1f;

            // All SFX paths
            const std::string snd_damage = "assets/audio/SFX/snd_damage.wav";
            const std::string snd_level_finished = "assets/audio/SFX/snd_level_finished.wav";
            const std::string snd_select = "assets/audio/SFX/snd_select.wav";
            const std::string snd_fall = "assets/audio/SFX/snd_fall.wav";
            const std::string snd_fall_strong = "assets/audio/SFX/snd_fall_strong.wav";
            const std::string snd_collect = "assets/audio/SFX/snd_collect.wav";
            const std::string snd_hover = "assets/audio/SFX/snd_hover.wav";
            const std::string snd_break_wall = "assets/audio/SFX/snd_break_wall.wav";
            const std::string snd_slide = "assets/audio/SFX/snd_slide.wav";
            const std::string snd_rolling = "assets/audio/SFX/snd_rolling.wav";

            // All MUS paths
            const std::string mus_level = "assets/audio/Music/mus_level.wav";
            const std::string mus_menu = "assets/audio/Music/mus_menu.mp3";

		    // Functions
            void playSound(const std::string& filePath);
            void playRollingSound(const std::string& filePath);
            void playMusic(const std::string& filePath);
            void stopMusic();
            void stopRollingSound();

        private:
            bool rollingSoundPlaying = false;
            SoundType activeSounds;  // For storing active sound effects
            SoundType activeMusics;  // For storing active music tracks
    };
}
