#include<SFML/Graphics.hpp>
#include<sstream>

using namespace sf;
using namespace std;

void updateBranches(int);
const int NUM_BRANCHES=6;

enum class side{LEFT,RIGHT,NONE};
side branchPositions[NUM_BRANCHES];
Sprite Branches[NUM_BRANCHES];

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
messageText.setOrigin((textRect.left + textRect.width) / 2.0, (textRect.top + textRect.height) / 2.0);
messageText.setPosition(resolution.x / 2.0, resolution.y / 2.0);

//Branch
Texture branchTexture;
branchTexture.loadFromFile("graphics/branch.png");
for(int i=0;i<NUM_BRANCHES;i++){
    Branches[i].setTexture(branchTexture);
    Branches[i].setOrigin(220,20);
    Branches[i].setPosition(-2000,-2000);
}

// Score
Text scoreText;
scoreText.setFont(font);
scoreText.setFillColor(Color::Red);
scoreText.setCharacterSize(75);
scoreText.setString("Score = 0");
scoreText.setPosition(20, 20);
int score = 0;

updateBranches(1);
updateBranches(2);
updateBranches(3);
updateBranches(4);
updateBranches(5);

//Player
Texture playerTexture;
playerTexture.loadFromFile("graphics/player.png");
Sprite playerSprite;
playerSprite.setTexture(playerTexture);
playerSprite.setPosition(resolution.x/2+150+50,resolution.y-250);

//Game Loop
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
        messageText.setString("Time Out!!!");
        textRect = messageText.getLocalBounds();
        messageText.setOrigin(textRect.left + textRect.width / 2.0, textRect.top + textRect.height / 2.0);
        messageText.setPosition(resolution.x / 2.0, resolution.y / 2.0);
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
    std::stringstream ss;
    ss<<"Score = "<<score;
    scoreText.setString(ss.str());
    for(int i=0;i<NUM_BRANCHES;i++){
        float branchHeight=i*150;
        if(branchPositions[i]==side::LEFT){
        Branches[i].setPosition(resolution.x/2-200,branchHeight);
        Branches[i].setRotation(180);//flip //argument in degree
        }
        else if(branchPositions[i]==side::RIGHT){
        Branches[i].setPosition(resolution.x/2+200,branchHeight);
        Branches[i].setRotation(0);
        }
        else{
          Branches[i].setPosition(3000,branchHeight);
        }
        updateBranches(1);
        updateBranches(2);
        updateBranches(3);
        updateBranches(4);
        updateBranches(5);

    }
   }
    window.clear();
    window.draw(backgroundSprite);
    window.draw(cloudSprite1);
    window.draw(cloudSprite2);
    window.draw(cloudSprite3);
    for(int i=0;i<NUM_BRANCHES;i++){
        window.draw(Branches[i]);
    }
    window.draw(treeSprite);
    window.draw(beeSprite1);
    window.draw(playerSprite);
    // window.draw(beeSprite2);
    // window.draw(beeSprite3);
    // window.draw(beeSprite4);
    if (paused){
        window.draw(messageText);
    }
    window.draw(scoreText);
    window.draw(timeBar);
    window.display();
}
return 0;
}

void updateBranches(int seed){
   //Shift each position one place to right
   for(int i=NUM_BRANCHES;i>0;i--){
      branchPositions[i]=branchPositions[i-1];
   }
   //update 0th position
   srand(time(0)+seed);
   int r=rand()%3;
   switch(r){
    case 0:branchPositions[0]=side::LEFT;
           break;
    case 1:branchPositions[1]=side::RIGHT;
           break;
    default:branchPositions[2]=side::NONE; 
   } 
}