#include "SoundManager.h"
#include <fstream>
#include <iostream>
#include <filesystem>
#include "StringUtils.h"

SoundManager* SoundManager::sharedInstance = NULL;

SoundManager* SoundManager::getInstance() {
    if (sharedInstance == NULL) {
        //initialize
        sharedInstance = new SoundManager();
    }

    return sharedInstance;
}

SoundManager::SoundManager() {}

bool SoundManager::loadSound(const std::string& name, const std::string& filename) {
    std::string fullPath = STREAMING_PATH + filename;

    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile(fullPath)) {
        std::cerr << "Failed to load sound: " << fullPath << std::endl;
        return false;
    }
    soundBuffers[name] = buffer;
    sf::Sound sound;
    sound.setBuffer(soundBuffers[name]);
    sounds[name] = sound;
    return true;
}

void SoundManager::playSound(const std::string& name) {
    if (sounds.find(name) != sounds.end()) {
        sounds[name].setVolume(soundVolume);
        sounds[name].play();
    }
    else {
        std::cerr << "Sound not found: " << name << std::endl;
    }
}

bool SoundManager::loadMusic(const std::string& filename) {
    std::string fullPath = STREAMING_PATH + filename;

    if (!backgroundMusic.openFromFile(fullPath)) {
        std::cerr << "Failed to load music: " << fullPath << std::endl;
        return false;
    }
    return true;
}

void SoundManager::playMusic(bool loop) {
    backgroundMusic.setVolume(musicVolume);
    backgroundMusic.setLoop(loop);
    backgroundMusic.play();
}

void SoundManager::stopMusic() {
    backgroundMusic.stop();
}

void SoundManager::setSoundVolume(float volume) {
    soundVolume = volume;
    for (auto& [name, sound] : sounds) {
        sound.setVolume(volume);
    }
}

void SoundManager::setMusicVolume(float volume) {
    musicVolume = volume;
    backgroundMusic.setVolume(volume);
}

void SoundManager::loadfromAudioList()
{
    for (const auto& entry : std::filesystem::directory_iterator(STREAMING_PATH)) {
        if (entry.is_regular_file())
        {
            std::string filename = entry.path().filename().string();
            std::string name = StringUtils::split(filename, '.')[0];

            if (entry.path().extension() == ".wav" || entry.path().extension() == ".ogg" || entry.path().extension() == ".mp3")
            {
                if (loadSound(name, filename))
                    std::cout << "Loaded sound: " << name << std::endl;

                else
                    std::cerr << "Failed to load sound: " << filename << std::endl;
            }
        }
    }
}
