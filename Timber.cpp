#include<SFML/Graphics.hpp>
using namespace sf;

int main(){
Vector2f resolution;
resolution.x=VideoMode::getDesktopMode().width;
resolution.y=VideoMode::getDesktopMode().height;

VideoMode vm(resolution.x,resolution.y);
RenderWindow window(vm,"Timber!!!");

Texture backgroundTexture;
backgroundTexture.loadFromFile("graphics/background.png");

Sprite backgroundSprite;
backgroundSprite.setTexture(backgroundTexture);
backgroundSprite.setPosition(0,0);

Texture treeTexture;
treeTexture.loadFromFile("graphics/tree.png");

Sprite treeSprite;
treeSprite.setTexture(treeTexture);
treeSprite.setPosition(resolution.x/2-300/2.0,0.0);

Texture beeTexture;
beeTexture.loadFromFile("graphics/bee.png");
Sprite beeSprite1,beeSprite2,beeSprite3,beeSprite4;
beeSprite1.setTexture(beeTexture);
beeSprite1.setPosition(resolution.x/2.0+300/2.0+20,resolution.y/2);

beeSprite2.setTexture(beeTexture);
beeSprite2.setPosition(resolution.x/2.0-300/2.0,resolution.y/3);

beeSprite3.setTexture(beeTexture);
beeSprite3.setPosition(resolution.x/2.0,resolution.y/2.0);

beeSprite4.setTexture(beeTexture);
beeSprite4.setPosition(resolution.x/2.0-300/2.0-65,resolution.y/1.5);

Texture cloudTexture;
cloudTexture.loadFromFile("graphics/cloud.png");
Sprite cloudSprite;
cloudSprite.setTexture(cloudTexture);
cloudSprite.setPosition(0,0);
Clock deltaClock,clock;
float beeSpeed = 300.0f;
bool paused=false;
Time dt;

while(window.isOpen()){
    Event event;
    while(window.pollEvent(event)){
        if(event.type==Event::Closed){
            window.close();
        }
    }
    if(Keyboard::isKeyPressed(Keyboard::Escape)){
        window.close();
    }
    dt = deltaClock.restart();
    if(!paused){
        if(beeSprite1.getPosition().x<-100){
            beeSprite1.setPosition(resolution.x,800);
    }
    else{
        beeSprite1.setPosition(beeSprite1.getPosition().x-beeSpeed*dt.asSeconds(),800);
    }
    }

    window.clear();
    window.draw(backgroundSprite);
    window.draw(treeSprite);
    window.draw(beeSprite1);
    window.draw(beeSprite2);
    window.draw(beeSprite3);
    window.draw(beeSprite4);
    window.draw(cloudSprite);
    window.display();
}
return 0;
}