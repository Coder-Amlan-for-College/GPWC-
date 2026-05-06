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

    float m_GapY;
    float m_GapSize;
    float m_BaseTopY;
    float m_BaseBottomY;

    float m_Time;

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

    m_TopPipe.setScale(1.3f, -2.8f);
    m_BottomPipe.setScale(1.3f, 2.8f);
    m_Speed = 300;

    m_Passed = false;

    m_OscillationOffset=rand()%360;
    m_OscillationSpeed=2.0f;

    m_Time=0.0f;
}

void Pipe::spawn(float startX,float gapY,float gapSize)
{
    m_GapY = gapY;
    m_GapSize = gapSize;
    m_Time = 0;

    float topY =gapY - gapSize / 2;
    float bottomY =gapY + gapSize / 2;

    m_TopPipe.setPosition(startX,topY);
    m_BottomPipe.setPosition(startX,bottomY);
    m_Passed = false;
}

void Pipe::update(float dt)
{
    m_Time += dt;
    float oscillation=std::sin(m_Time * 2.0f) * 80;
    m_GapY += oscillation * dt;

    if (m_GapY < 250)
    {
        m_GapY = 250;
    }

    if (m_GapY > 800)
    {
        m_GapY = 800;
    }

    float x =m_TopPipe.getPosition().x- m_Speed * dt;

    // TOP PIPE
    m_TopPipe.setPosition(x,m_GapY - m_GapSize / 2);

    // BOTTOM PIPE
    m_BottomPipe.setPosition(x,m_GapY + m_GapSize / 2);
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