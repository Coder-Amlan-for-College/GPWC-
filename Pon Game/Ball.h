#pragma once

#include<SFML/Graphics.hpp>
using namespace sf;

class Ball{
    private:
       //Position
       Vector2f m_Position;
       //Shape
       CircleShape m_Shape;
       //Speed
       float m_Speed=1000.0f;
       //X Direction
       float m_DirectionX=0.2f;
       //Y Direction
       float m_DirectionY=0.2f;
    
    public:
      Ball(float startX,float startY);

      FloatRect getPosition();

      CircleShape getShape();

      float getXVelocity();

      void reboundBatOrTop();

      void reboundSides();
      //reboundBottom()
      void reboundBottom();

      //update(Time)
      void update(Time dt);
};