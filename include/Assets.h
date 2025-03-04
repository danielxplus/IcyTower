#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <string>

class Assets
{
public:
    Assets();
    static Assets& getInstance();
    void loadTexture(const std::string& name, const std::string& filename);
    void loadImage(const std::string& name, const std::string& filename);
    void loadSound(const std::string& name, const std::string& filename);

    const sf::Texture& getTexture(const std::string& name) const;
    const sf::Image& getImage(const std::string& name) const;
    const sf::SoundBuffer& getSound(const std::string& name) const;
    Assets& operator=(const Assets&) = delete;

private:
    std::unordered_map <std::string, sf::Texture> m_texture;
    std::unordered_map <std::string, sf::Image> m_image;
    std::unordered_map <std::string, sf::SoundBuffer> m_soundbuffer;
};

static const struct playerData
{
    sf::Image bmp_file;
    sf::IntRect animation;

    sf::SoundBuffer sound_edge;
    sf::SoundBuffer sound_jump_low;
    sf::SoundBuffer sound_jump_mid;
    sf::SoundBuffer sound_jump_high;
    sf::SoundBuffer sound_hello;
    sf::SoundBuffer sound_jump_falling;

    sf::Music player_bgm;
};