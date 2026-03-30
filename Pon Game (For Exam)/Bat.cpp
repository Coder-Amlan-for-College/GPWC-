#include "Bat.h"
using namespace sf;

Bat::Bat(float startX,float startY){
    m_Position.x=startX;
    m_Position.y=startY;
    m_Shape.setSize(Vector2f(100.0,10.0));
    m_Shape.setPosition(m_Position);
}
FloatRect Bat::get_Position(){
    return m_Shape.getGlobalBounds();
}

RectangleShape Bat::get_Shape(){
    return m_Shape;
}
void Bat::moveUp(){
    m_MovingUp=true;
}
void Bat::moveDown(){
    m_MovingDown=true;
}

//moveRight()
void Bat::moveRight(){
    m_MovingRight=true;
}

//moveLeft()
void Bat::moveLeft(){
    m_MovingLeft=true;
}

void Bat::stopRight(){
    m_MovingRight=false;
}

void Bat::stopLeft(){
    m_MovingLeft=false;
}
void Bat::stopUp(){
    m_MovingUp=false;
}

void Bat::stopDown(){
    m_MovingDown=false;
}

//update
void Bat::update(Time dt){
    if(m_MovingLeft){
        m_Position.x -= m_Speed*dt.asSeconds();
    }
    if(m_MovingRight){
        m_Position.x += m_Speed*dt.asSeconds();
    }
    if(m_MovingUp){
        m_Position.y += m_Speed*dt.asSeconds();
    }
    if(m_MovingDown){
        m_Position.y -= m_Speed*dt.asSeconds();
    }
    
    m_Shape.setPosition(m_Position);
}