#include "Platform.h"
#include <iostream>

bool registerPlatform = Factory::registerit("Platform", []() -> std::unique_ptr<Object> { return std::make_unique<Platform>(); });

//=========================================================
void Platform::setBasic(float& floor, float& y, Layer& layer)
{
    this->init();
    this->m_positionX = floor;

	this->m_floor = floor;
    this->origin_floor = floor;
    this->m_position = generatePos();
    this->m_length = generateLen();
    platform_sprite.setTexture(platform_texture);
    platform_sprite.setPosition(m_position, m_floor * const_dist_between_platforms * -1 + 508);
    m_vector = FloorTypes::getIntRects(FloorTypes::Type::Snow);
    plat_start_pos = m_position;
    plat_end_pos = m_position + m_vector[0].width + m_length * m_vector[1].width + m_vector[2].width;
}
//=========================================================

void Platform::init()
{
    platform_image = m_assets.getImage("floors");
    platform_image.createMaskFromColor(sf::Color(36, 255, 0, 255));
    platform_texture.loadFromImage(platform_image);
}
//=========================================================

void Platform::render(sf::RenderWindow& window)
{
   
    platform_sprite.setTextureRect(m_vector[0]);
    window.draw(platform_sprite);

    platform_sprite.move(m_vector[0].width, 0);
    platform_sprite.setTextureRect(m_vector[1]);

    for (int i = 0; i < m_length; i++)
    {
        window.draw(platform_sprite);
        platform_sprite.move(m_vector[1].width, 0);
    }

    platform_sprite.setTextureRect(m_vector[2]);
    window.draw(platform_sprite);

    platform_sprite.setPosition(plat_start_pos, platform_sprite.getPosition().y);

    floor_sign_sprite.setPosition((int)floor_text.getPosition().x - 19, (int)floor_text.getPosition().y - 12);
    window.draw(floor_sign_sprite);

    window.draw(floor_text);
}
//=========================================================

void Platform::reset()
{
    m_layer.cam_posY = 0;
    m_layer.reset();
    m_floor = origin_floor-7;
    regenerate();
}
//=========================================================

void Platform::logic()
{
    if (m_layer.view.getCenter().y - 270 <= const_dist_between_platforms * (this->getFloor()) * -1)
    {
        regenerate();
    }
    else if (m_floor % 4 == 0 && m_floor % 10 != 0)
    {
        int diff = Menu::difficulty;

        const int min_x = 50;  // Set your minimum X boundary
        const int max_x = 520; // Set your maximum X boundary
        // Move platform left and right
        static bool direction = true;
        if (m_position <= min_x)
        {
            direction = true; // Move right
        }
        else if (m_position >= max_x)
        {
            direction = false; // Move left
        }

        if (direction)
        {
            m_position += 2 * diff;
        }
        else
        {
            m_position -= 2 * diff;
        }

        plat_start_pos = m_position;
        plat_end_pos = m_position + m_vector[0].width + m_length * m_vector[1].width + m_vector[2].width;
        platform_sprite.setPosition(m_position, getPosY());
    }
}

//=========================================================
float Platform::getPosX()
{
    return m_positionX;
}

//=========================================================
float Platform::getPosY()
{
    return platform_sprite.getPosition().y;
}

//=========================================================
float Platform::getStartX()
{
    return plat_start_pos;
}

//=========================================================
float Platform::getEndX()
{
    return plat_end_pos;
}

//=========================================================
bool Platform::collison(sf::Sprite sprite, float m_posX)
{
    if ((m_posX >= plat_start_pos - sprite.getTextureRect().width / 2) &&
        (m_posX <= plat_start_pos + sprite.getTextureRect().width / 2))
    {
        return true;
    }
    return false;
}
//=========================================================

int Platform::getFloor()
{
    return m_floor;
}
//=========================================================
void Platform::regenerate()
{
    m_floor += 7;
    m_positionX = m_floor;
    m_position = generatePos();
    m_length = generateLen();
    platform_sprite.setPosition(m_position, m_floor * const_dist_between_platforms * -1 + 508);


    int floorType = getFloorType(m_floor);
    m_vector = FloorTypes::getIntRects(floorType);

    plat_start_pos = m_position;
    plat_end_pos = m_position + m_vector[0].width + m_length * m_vector[1].width + m_vector[2].width;

    if (m_floor % 10 == 0)
    {
        floor_sign_sprite.setTexture(m_assets.getTexture("woodboard"));

        floor_text.setString(std::to_string(m_floor));
        floor_text.setFont(DefaultFont::getFont());
        floor_text.setCharacterSize(const_text_size_small);
        floor_text.setOutlineThickness(const_text_outline_small);
        floor_text.setScale(0.75, 0.75);
        floor_text.setOutlineColor(sf::Color::Black);
        floor_text.setFillColor(sf::Color::White);
        floor_text.setOrigin(floor_text.getLocalBounds().width / 2, floor_text.getLocalBounds().height / 2);

        if (m_floor % 50 != 0)
        {
            floor_text.setPosition((plat_start_pos + plat_end_pos) / 2, platform_sprite.getPosition().y + m_vector[0].height / 2 + 12);
        }
        else
        {
            floor_text.setPosition(320, platform_sprite.getPosition().y + m_vector[0].height / 2 + 12);
        }
    }
}

//=========================================================
int Platform::getFloorType(int floor)
{
    static const std::vector<std::pair<int, int>> floorRanges =
    {
        {50, FloorTypes::Type::Snow},
        {100, FloorTypes::Type::Ice},
        {150, FloorTypes::Type::Wood},
        {200, FloorTypes::Type::Metal},
        {250, FloorTypes::Type::Bone},
        {300, FloorTypes::Type::Gum},
        {350, FloorTypes::Type::Rainbow}
    };

    for (const auto& range : floorRanges)
    {
        if (floor < range.first) {
            return range.second;
        }
    }
    return -1;  // default case if no match
}

//=========================================================
int Platform::generatePos()
{
    if (active_power_up)
    {
        activated = true;
        active_power_up = false;
    }

    if ((m_floor != 1 && m_floor % 50 != 0) && !activated)
    {
        std::random_device rd;
        std::mt19937 rand(rd());
        std::uniform_int_distribution<> pos(75, 445);
        return pos(rand);
    }

    if (activated && counter < 15)
    {
        counter++;
        return 50;
    }
    else if (counter == 15)
    {
        activated = false;
        counter = 0;
    }

    return 50;
}

//=========================================================
int Platform::generateLen()
{
    if (active_power_up)
    {
        activated = true;
        active_power_up = false;
    }

    if ((m_floor != 1 && m_floor % 50 != 0) && !activated)
    {
        std::random_device rd;
        std::mt19937 rand(rd());

        if (m_position <= 315)
        {
            std::uniform_int_distribution<> len(5, 13);
            return len(rand);
        }
        else if (m_position > 315)
        {
            int temp = m_position;
            for (int i = 5; i <= 13; i++)
            {
                temp += 16;
                if (temp > 445)
                {
                    std::uniform_int_distribution<> len(5, i);
                    return len(rand);
                }
            }
        }
    }

    if (activated && counter < 15)
    {
        counter++;
        return 36;
    }
    else if (counter == 15)
    {
        activated = false;
        counter = 0;
    }

    return 36;
}
