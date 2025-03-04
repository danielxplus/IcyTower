#include "Timer.h"

bool registerTimer = Factory::registerit("Timer", []() -> std::unique_ptr<Object> { return std::make_unique<Timer>(); });

bool Timer::started = false;

void Timer::setBasic(float& x, float& y, Layer& layer)
{
    this->m_layer = layer;
}

void Timer::init()
{
    m_cur_level = 0;
    Camera::setCamLevel(m_cur_level);

    m_clock_sprite.setTexture(m_assets.getTexture("stopwatch"));
    m_clock_sprite.setOrigin(37, 47);
    m_clock_sprite.setPosition(37, 47); // Initial position

    m_clock_handle_sprite.setTexture(m_assets.getTexture("stopwatch_handle"));
    m_clock_handle_sprite.setOrigin(37, 47);
    m_clock_handle_sprite.setPosition(const_timer_start_pos_x, const_timer_start_pos_y); // Initial position
}

void Timer::render(sf::RenderWindow& window)
{
    // Set the camera position based on the first platform's layer
    m_layer.cam_posY = Game::m_platforms[0]->m_layer.cam_posY;
    m_layer.view.reset(sf::FloatRect(0, m_layer.cam_posY, 640, 480));

    // Position the clock and handle sprites based on the camera
    m_clock_sprite.setPosition(37, m_layer.cam_posY + 60);
    m_clock_handle_sprite.setPosition(37, m_layer.cam_posY + 60);

    // Render the sprites
    m_layer.render(window, m_clock_sprite);
    m_layer.render(window, m_clock_handle_sprite);

}

void Timer::reset()
{
    m_cur_level = 0;
    Camera::setCamLevel(m_cur_level);
    m_clock.restart();
    hurrying = berserk = shaking = started = false;
    m_clock_handle_sprite.setRotation(0);
}

void Timer::logic()
{
    static int phase = 0;
    if (phase == 0)
    {
        if (started)
        {
            m_cur_level = 1;
            Camera::setCamLevel(m_cur_level);
            m_clock.restart();
            phase++;
        }
    }
    m_time = m_clock.getElapsedTime();
    if (started)
    {
        if (phase == 1)
        {
            m_clock_handle_sprite.setRotation(m_time.asSeconds() * 12);

            if (m_time.asSeconds() > 30)
            {
                shaking = true; // Start shaking
                hurrying = true; // Start hurry up animation
                if (Menu::bool_sound)
                {
                    m_ring_buffer.openFromFile("ring.ogg");
                    m_ring_buffer.setVolume(100);
                    m_ring_buffer.play();
                    m_timer_buffer.openFromFile("HurryUp.mp3");
                    m_timer_buffer.setVolume(100);
                    m_timer_buffer.play();
                }
                if (m_cur_level < 5)
                {
                    m_cur_level++;
                    m_clock.restart();
                    Camera::setCamLevel(m_cur_level);
                }
                else
                {
                    Camera::setCamLevel(m_cur_level);
                    phase++;
                }
            }
        }
        else if (phase == 2)
        {
            m_cur_level = 6;
            berserk = true; // Set berserk state
            shaking = true; // Start shaking
            m_clock_handle_sprite.rotate(-3);
        }
    }
    else if (phase != 0)
    {
        phase = 0; // Reset phase if not started
    }
}

bool Timer::getstarted()
{
    return started;
}

void setStarted(bool start)
{
    Timer::started = start;
}
