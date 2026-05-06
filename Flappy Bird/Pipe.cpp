#pragma once
#include <SFML/Graphics.hpp>
#include<cmath>
using namespace sf;

class Pipe
{
private:

    Texture m_Texture;

    Sprite m_TopPipe;
    Sprite m_BottomPipe;

    float m_Speed;

    bool m_Passed;

    float m_OscillationOffset;
    float m_OscillationSpeed;

public:

    Pipe();

    void spawn(float startX,float gapY,float gapSize);

    void update(float dt);

    bool isOffScreen();

    bool checkCollision(FloatRect birdBounds);

    bool isPassed(float birdX);

    Sprite getTopSprite();

    Sprite getBottomSprite();
};

Pipe::Pipe()
{
    m_Texture.loadFromFile("assets/Pipes.png");

    m_TopPipe.setTexture(m_Texture);
    m_BottomPipe.setTexture(m_Texture);

    m_TopPipe.setScale(0.5f, -0.7f);
    m_BottomPipe.setScale(0.5f, 0.7f);

    m_Speed = 300;

    m_Passed = false;

    m_OscillationOffset=rand()%360;
    m_OscillationSpeed=2.0f;
}

void Pipe::spawn(float startX,float gapY,float gapSize)
{
    m_TopPipe.setPosition(startX, gapY);

    m_BottomPipe.setPosition(startX,gapY + gapSize);
}

void Pipe::update(float dt)
{
    m_TopPipe.move(-m_Speed * dt, 0);
    m_BottomPipe.move(-m_Speed * dt, 0);

    float oscillation = std::sin(m_OscillationOffset+clock()*0.001f*m_OscillationSpeed)*40;
    m_TopPipe.move(0,oscillation*dt);
    m_BottomPipe.move(0,oscillation*dt);
}

bool Pipe::isOffScreen()
{
    return m_TopPipe.getPosition().x < -200;
}

bool Pipe::checkCollision(FloatRect birdBounds)
{
    return birdBounds.intersects(m_TopPipe.getGlobalBounds())||birdBounds.intersects(m_BottomPipe.getGlobalBounds());
}

bool Pipe::isPassed(float birdX)
{
    if (!m_Passed &&m_TopPipe.getPosition().x < birdX)
    {
        m_Passed = true;
        return true;
    }

    return false;
}

Sprite Pipe::getTopSprite()
{
    return m_TopPipe;
}

Sprite Pipe::getBottomSprite()
{
    return m_BottomPipe;
}