#include "Player.h"

Player::Player(){
    m_Texture.loadFromFile("graphics/player.png");
    m_Sprite.setTexture(m_Texture);
    m_Sprite.setOrigin(25,25);

    m_Health = START_HEALTH;
    m_MaxHealth = START_HEALTH;
    m_Speed = START_SPEED;
}
void Player::spawn(int startX,int startY,IntRect arena){
    m_arena.left = arena.left;
    m_arena.top = arena.top;
    m_arena.width = arena.width;
    m_arena.height = arena.height;
}

void Player::moveLeft(){
    m_MovingLeft=true;
}
void Player::moveRight(){
    m_MovingRight=true;
}
void Player::moveUp(){
    m_MovingUp=true;
}
void Player::moveDown(){
    m_MovingDown=true;
}

void Player::stopLeft(){
    m_MovingLeft=false;
}
void Player::stopRight(){
    m_MovingRight=false;
}
void Player::stopUp(){
    m_MovingUp=false;
}
void Player::stopDown(){
    m_MovingDown=false;
}