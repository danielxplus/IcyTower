#include "Assets.h"

Assets::Assets()
{
    this->loadTexture("game_icon", "icon.png");
    this->loadTexture("game_logo", "logo.png");
    this->loadTexture("menu_bg", "menu_bg.png");

    this->loadTexture("wall_left", "long_left.png");
    this->loadTexture("wall_right", "long_right.png");
    this->loadTexture("bat", "bat.png");
    this->loadTexture("game_bg", "bg1.png");

    this->loadTexture("combo_meter", "combo.png");
    this->loadTexture("combo_bar", "combo_bar.png");

    this->loadTexture("stopwatch", "stopwatch.png");
    this->loadTexture("stopwatch_handle", "stopwatch_handle.png");

    this->loadTexture("gift_attack", "gift_attack.png");
    this->loadTexture("gift_gravity", "gift_gravity.png");
    this->loadTexture("gift_length", "gift_length.png");

    this->loadImage("dave", "dave.bmp");
    this->loadImage("harold", "harold.bmp");
    this->loadImage("kirby", "Kirby.bmp");

    // COMBO SOUNDS:
    this->loadSound("alright", "Alright.mp3");
    this->loadSound("amazing", "Amazing.mp3");
    this->loadSound("extreme", "Extreme.mp3");
    this->loadSound("fanastic", "Fantastic.mp3");
    this->loadSound("good", "Good.mp3");
    this->loadSound("great", "Great.mp3");
    this->loadSound("no_way", "NoWay.mp3");
    this->loadSound("splendid", "Splendid.mp3");

    // SOUND FX:
    this->loadSound("menu_bgm", "bgm.mp3");

    this->loadSound("ring", "ring.ogg");
    this->loadSound("hurry_up", "HurryUp.mp3");
    this->loadSound("game_over", "GameOver.mp3");
    this->loadSound("new_high_score", "NewHighScore.mp3");

    // Dave:
    this->loadSound("dave_bgm", "disco_bgm.mp3");
    this->loadSound("ahey", "ahey.ogg");
    this->loadSound("cmonyo", "cmonyo.ogg");
    this->loadSound("diggin", "diggin.ogg");
    this->loadSound("goinon", "goinon.ogg");
    this->loadSound("ho", "ho.ogg");
    this->loadSound("stayinalive", "stayinalive.ogg");
    this->loadSound("watchit", "watchit.ogg");

    // Kirby:
    this->loadSound("kirby_bgm", "KBgm.mp3");
    this->loadSound("kirby_death", "KDeath.wav");
    this->loadSound("kirby_hello", "KHello.wav");

    // Harold:
    this->loadSound("harold_bgm", "harold_bgm.mp3");
    this->loadSound("edge", "edge.wav");
    this->loadSound("falling", "falling.wav");
    this->loadSound("hello", "hello.wav");
    this->loadSound("jump_high", "jump_hi.wav");
    this->loadSound("jump_low", "jump_lo.wav");
    this->loadSound("jump_mid", "jump_mid.wav");

    // Floors:
    this->loadTexture("woodboard", "woodboard.png");
    this->loadImage("floors", "floors.bmp");
}

//=======================================================================
Assets& Assets::getInstance()
{
    static Assets instance;
    return instance;
}

//=======================================================================
void Assets::loadTexture(const std::string& name, const std::string& filename)
{
    sf::Texture texture;
    texture.loadFromFile(filename);
    m_texture[name] = std::move(texture);
}

//=======================================================================
void Assets::loadImage(const std::string& name, const std::string& filename)
{
    sf::Image image;
    image.loadFromFile(filename);
    m_image[name] = std::move(image);
}

//=======================================================================
void Assets::loadSound(const std::string& name, const std::string& filename)
{
    sf::SoundBuffer sound;
    sound.loadFromFile(filename);
    m_soundbuffer[name] = std::move(sound);
}

//=======================================================================
const sf::SoundBuffer& Assets::getSound(const std::string& name) const
{
    return m_soundbuffer.at(name);
}

//=======================================================================
const sf::Texture& Assets::getTexture(const std::string& name) const
{
    return m_texture.at(name);
}

//=======================================================================
const sf::Image& Assets::getImage(const std::string& name) const
{
    return m_image.at(name);
}