#include "Bat.h"
#include "Ball.h"
#include<sstream>
#include<SFML/Graphics.hpp>

using namespace sf;

int main(){
   Vector2f resolution;
   resolution.x = VideoMode::getDesktopMode().width;
   resolution.y=VideoMode::getDesktopMode().height;
   VideoMode vm(resolution.x,resolution.y);
   RenderWindow window(vm,"Pong!!!",Style::Fullscreen);
   
   int score=0;
   int lives=3;
   Bat bat(window.getSize().x/2.0,window.getSize().y-10);

   Ball ball(window.getSize().x/2.0,0);

   Font font;
   font.loadFromFile("fonts/KOMIKAP_.ttf");
   
   Text hud;
   hud.setFont(font);

   hud.setCharacterSize(75.0);
   hud.setFillColor(Color::Red);

   hud.setPosition(20.0,20.0);

   Clock clock;
   while(window.isOpen()){
     Event event;
     while(window.pollEvent(event)){
        if(event.type==Event::Closed){
            window.close();
        }
        if(Keyboard::isKeyPressed(Keyboard::Escape)){
            window.close();
        }
     }
     if(Keyboard::isKeyPressed(Keyboard::Left)){
        if(bat.get_Position().left<=0){
            bat.stopLeft();
        }
        else{
            bat.moveLeft();
        }
     }
     else{
        bat.stopLeft();
     }
     if(Keyboard::isKeyPressed(Keyboard::Right)){
        if(bat.get_Position().left+bat.get_Position().width>=resolution.x){
            bat.stopRight();
        }
        else{
            bat.moveRight();
        }
     }
     else{
        bat.stopRight();
     }
     if(Keyboard::isKeyPressed(Keyboard::Up)){
        if(bat.get_Position().top<=0){
            bat.stopUp();
        }
        else{
            bat.moveUp();
        }
     }
     else{
        bat.stopUp();
     }
     if(Keyboard::isKeyPressed(Keyboard::Down)){
        if(bat.get_Position().top + bat.get_Shape().getSize().y >= window.getSize().y){
            bat.stopDown();
        }
        else{
            bat.moveDown();
        }
     }
     else{
        bat.stopDown();
     }
   Time dt = clock.restart();
   bat.update(dt);
   ball.update(dt);

   std::stringstream ss;
   ss<<"Score: "<<score<<" Lives: "<<lives;
   hud.setString(ss.str());

   //Handle Ball Hitting the bottom
   if(ball.getPosition().top>=window.getSize().y){
     lives--;
     if(lives<=0){
        lives=3;
        score=0;
     }
     ball.reboundBottom();
     //ball.update(dt);
   }
   //Handle Ball Hitting the top
   if(ball.getPosition().top<=0){
    score++;
    ball.reboundBatOrTop();
   }
   //Handle Ball hitting sides
   if(ball.getPosition().left<=0 || ball.getPosition().left+ball.getPosition().width>=window.getSize().x){
            ball.reboundSides();     
   }
   if(ball.getPosition().intersects(bat.get_Position())){
      score++;
      ball.updateSpeed();
      ball.reboundBatOrTop();
      ball.update(dt);
      bat.update(dt);
   }
   window.clear();
   window.draw(ball.getShape());
   window.draw(bat.get_Shape());
   window.draw(hud);
   window.display();
   }
  return 0;
}