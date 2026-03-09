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

// beeSprite2.setTexture(beeTexture);
// beeSprite2.setPosition(resolution.x/2.0-300/2.0,resolution.y/3);

// beeSprite3.setTexture(beeTexture);
// beeSprite3.setPosition(resolution.x/2.0,resolution.y/2.0);

// beeSprite4.setTexture(beeTexture);
// beeSprite4.setPosition(resolution.x/2.0-300/2.0-65,resolution.y/1.5);

Clock clock;
float beeSpeed=0.0f;
float beeHeight=0.0f;
bool beeActive=false;

Texture cloudTexture;
cloudTexture.loadFromFile("graphics/cloud.png");

//Height 0-150
Sprite cloudSprite1;
cloudSprite1.setTexture(cloudTexture);
cloudSprite1.setPosition(-200,0);
float cloudSpeed1=0.0f;
float cloudHeight1=0.0f;
bool  cloudActive1=false;

//Height 150-300
Sprite cloudSprite2;
cloudSprite2.setTexture(cloudTexture);
cloudSprite2.setPosition(-200,150);
float cloudSpeed2=0.0f;
float cloudHeight2=0.0f;
bool  cloudActive2=false;

//Height 300-450
Sprite cloudSprite3;
cloudSprite3.setTexture(cloudTexture);
cloudSprite3.setPosition(-200,300);
float cloudSpeed3=0.0f;
float cloudHeight3=0.0f;
bool  cloudActive3=false;


RectangleShape timeBar;
float timeBarStartWidth=400.0f;
float timeBarHeight=80.0f;
timeBar.setSize(Vector2f(timeBarStartWidth,timeBarHeight));
timeBar.setFillColor(Color::Red);
timeBar.setPosition(resolution.x/2.0-timeBarStartWidth/2.0,resolution.y-100.0);
float timeRemaining = 6.0f;
float timeBarWidthPerSecond = timeBarStartWidth/timeRemaining;
bool paused=true;

//message Text
Font font;
font.loadFromFile("fonts/KOMIKAP_.ttf");
Text messageText;
messageText.setFont(font);
messageText.setFillColor(Color::White);
messageText.setCharacterSize(100);
messageText.setString("Press Enter key to Start");
FloatRect textRect=messageText.getLocalBounds();


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
    if(Keyboard::isKeyPressed(Keyboard::Return)){//Keyboard::Enter-->Both works
        paused=!paused;
        timeRemaining=5.0f;
    }
    if(!paused){
    Time dt = clock.restart();
    timeRemaining -= dt.asSeconds();
    if(timeRemaining<=0.0){
        paused=true;
    }
    timeBar.setSize(Vector2f(timeBarWidthPerSecond*timeRemaining,timeBarHeight));
    if(!cloudActive1){
        srand((int)(time)(0)*10);
        cloudSpeed1=rand()%200;

        srand((int)(time)(0)*10);
        cloudHeight1=rand()%100;
        cloudSprite1.setPosition(-200,cloudHeight1);
        cloudActive1=true;
    }
    else{
        cloudSprite1.setPosition(cloudSprite1.getPosition().x+cloudSpeed1*dt.asSeconds(),cloudSprite1.getPosition().y);
        if(cloudSprite1.getPosition().x>resolution.x+100){
            cloudActive1=false;
        }
    }
    if(!cloudActive2){
        srand((int)(time)(0)*10);
        cloudSpeed2=rand()%150;

        srand((int)(time)(0)*10);
        cloudHeight2=rand()%100+100;
        cloudSprite2.setPosition(-200,cloudHeight2);
        cloudActive2=true;
    }
    else{
        cloudSprite2.setPosition(cloudSprite2.getPosition().x+cloudSpeed2*dt.asSeconds(),cloudSprite2.getPosition().y);
        if(cloudSprite2.getPosition().x>1920){
            cloudActive2=false;
        }
    }
    if(!cloudActive3){
        srand((int)(time)(0)*10);
        cloudSpeed3=rand()%100;

        srand((int)(time)(0)*10);
        cloudHeight3=rand()%100+200;
        cloudSprite3.setPosition(-200,cloudHeight3);
        cloudActive3=true;
    }
    else{
        cloudSprite3.setPosition(cloudSprite3.getPosition().x+cloudSpeed3*dt.asSeconds(),cloudSprite3.getPosition().y);
        if(cloudSprite3.getPosition().x>1920){
            cloudActive3=false;
        }
    }
    if(!beeActive){
        srand(time(0)*10);
        beeSpeed=rand()%200+200;
        srand(time(0)*20);
        beeHeight=rand()%500+500;
        beeSprite1.setPosition(2000,beeHeight);
        beeActive=true;
    }
    else{
        beeSprite1.setPosition(beeSprite1.getPosition().x-beeSpeed*dt.asSeconds(),beeSprite1.getPosition().y);
        if(beeSprite1.getPosition().x < -100){
            beeActive=false;
        }
    }
   }
    window.clear();
    window.draw(backgroundSprite);
    window.draw(cloudSprite1);
    window.draw(cloudSprite2);
    window.draw(cloudSprite3);
    window.draw(treeSprite);
    window.draw(beeSprite1);
    // window.draw(beeSprite2);
    // window.draw(beeSprite3);
    // window.draw(beeSprite4);
    window.draw(timeBar);
    window.display();
}
return 0;
}