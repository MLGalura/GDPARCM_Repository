#pragma once
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <filesystem>
#include <fstream>
#include <string>

class SoundManager {
public:
    static SoundManager* getInstance();

    bool loadSound(const std::string& name, const std::string& filename);
    void playSound(const std::string& name);

    bool loadMusic(const std::string& filename);
    void playMusic(bool loop = true);

    void stopMusic();

    void setSoundVolume(float volume);
    void setMusicVolume(float volume);

private:
    SoundManager();
    SoundManager(SoundManager const&) {};             // copy constructor is private
    SoundManager& operator=(SoundManager const&) {};  // assignment operator is private
    static SoundManager* sharedInstance;

    std::unordered_map<std::string, sf::SoundBuffer> soundBuffers;
    std::unordered_map<std::string, sf::Sound> sounds;
    sf::Music backgroundMusic;

    const std::string STREAMING_PATH = "Media/Sounds/";
    float soundVolume = 100.0f;
    float musicVolume = 100.0f;
};