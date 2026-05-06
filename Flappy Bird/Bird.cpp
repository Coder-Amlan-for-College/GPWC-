#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Bird
{
private:

    const float GRAVITY = 900.0f;
    const float FLAP_SPEED = -350.0f;

    Vector2f m_Position;

    Texture m_Texture;
    Sprite m_Sprite;

    float m_Velocity;

public:

    Bird();

    void spawn(Vector2f resolution);

    void flap();

    void update(float dt);

    FloatRect getPosition();

    Sprite getSprite();

    Vector2f getCenter();

    void reset();
};

Bird::Bird()
{
    m_Texture.loadFromFile("assets/Bird.png");

    m_Sprite.setTexture(m_Texture);

    m_Sprite.setScale(0.4f, 0.4f);

    m_Velocity = 0;
}

void Bird::spawn(Vector2f resolution)
{
    m_Position.x = resolution.x / 4;
    m_Position.y = resolution.y / 2;

    m_Sprite.setPosition(m_Position);
}

void Bird::flap()
{
    m_Velocity = FLAP_SPEED;
}

void Bird::update(float dt)
{
    m_Velocity += GRAVITY * dt;

    m_Position.y += m_Velocity * dt;

    m_Sprite.setPosition(m_Position);
}

FloatRect Bird::getPosition()
{
    return m_Sprite.getGlobalBounds();
}

Sprite Bird::getSprite()
{
    return m_Sprite;
}

Vector2f Bird::getCenter()
{
    return m_Position;
}

void Bird::reset()
{
    m_Position.x = 500;
    m_Position.y = 540;

    m_Velocity = 0;
}
