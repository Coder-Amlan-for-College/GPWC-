#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Bird.cpp"
#include "Pipe.cpp"
#include "CreatePipes.cpp"

#include <fstream>

using namespace sf;

int main()
{
    enum class State{
    LEVEL_SELECT,
    PAUSED,
    GAME_OVER,
    PLAYING};

    State state = State::LEVEL_SELECT;
    Vector2f resolution;
    resolution.x = 1920;
    resolution.y = 1080;

    RenderWindow window(VideoMode(resolution.x,resolution.y),"Flappy!!!");

    View mainView(FloatRect(0,0, resolution.x,resolution.y));

    Clock clock;

    Font font;
    font.loadFromFile("assets/KOMIKAP_.ttf");

    Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(50);
    scoreText.setPosition(50, 30);
    scoreText.setFillColor(Color::Black);

    Text highScoreText;
    highScoreText.setFont(font);
    highScoreText.setCharacterSize(50);
    highScoreText.setPosition(1400, 30);
    highScoreText.setFillColor(Color::Black);

    Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setCharacterSize(70);
    gameOverText.setPosition(650, 450);
    gameOverText.setFillColor(Color::Black);

    Text pauseText;
    pauseText.setFont(font);
    pauseText.setFillColor(Color::Black);
    pauseText.setCharacterSize(100);
    pauseText.setString("GAME PAUSED\nPRESS ENTER");

    FloatRect pauseRect = pauseText.getLocalBounds();

    pauseText.setOrigin((pauseRect.left + pauseRect.width) / 2.0f,(pauseRect.top + pauseRect.height) / 2.0f);
    pauseText.setPosition(resolution.x / 2.0f,resolution.y / 2.0f);

    Text levelText;
    levelText.setFont(font);
    levelText.setFillColor(Color::Black);
    levelText.setCharacterSize(80);

    levelText.setString(
        "SELECT DIFFICULTY\n\n"
        "1 - EASY\n"
        "2 - MEDIUM\n"
        "3 - HARD");

    FloatRect levelRect = levelText.getLocalBounds();

    levelText.setOrigin((levelRect.left + levelRect.width) / 2.0f,(levelRect.top + levelRect.height) / 2.0f);

    levelText.setPosition(resolution.x / 2.0f,resolution.y / 2.0f);

    SoundBuffer flapBuffer;
    flapBuffer.loadFromFile("sounds/flap.mp3");
    Sound flapSound;
    flapSound.setBuffer(flapBuffer);

    SoundBuffer hitBuffer;
    hitBuffer.loadFromFile("sounds/hit.mp3");
    Sound hitSound;
    hitSound.setBuffer(hitBuffer);

    SoundBuffer pointBuffer;
    pointBuffer.loadFromFile("sounds/point.mp3");
    Sound pointSound;
    pointSound.setBuffer(pointBuffer);
  
    SoundBuffer dieBuffer;
    dieBuffer.loadFromFile("sounds/die.mp3");
    Sound dieSound;
    dieSound.setBuffer(dieBuffer);    
     
    SoundBuffer swooshBuffer;
    swooshBuffer.loadFromFile("sounds/swoosh.mp3");
    Sound swooshSound;
    swooshSound.setBuffer(swooshBuffer);

    Bird bird;
    bird.spawn(resolution);

    float pipeGap = 250;

    int numPipes = 5;

    Pipe* pipes =createPipes(numPipes,resolution.x,pipeGap);

    int score = 0;

    int highScore = 0;

    std::ifstream inFile("highscore.txt");

    if (inFile.is_open())
    {
        inFile >> highScore;
    }

    while (window.isOpen())
    {
        Event event;

        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }

            if (event.type == Event::KeyPressed)
            {
                if (event.key.code==Keyboard::Escape)
                {
                    window.close();
                }

                if (event.key.code == Keyboard::Enter)
                {
                    swooshSound.play();
                    if (state == State::PLAYING)
                    {
                        state = State::PAUSED;
                    }
                    else if (state == State::PAUSED)
                    {
                        state = State::PLAYING;     
                        clock.restart();
                    }
                }

                if (event.key.code ==Keyboard::Space && state == State::PLAYING)
                {
                    bird.flap();
                    flapSound.play();
                }

                if (event.key.code ==Keyboard::R && state == State::GAME_OVER)
                {
                    swooshSound.play();
                    score = 0;
                    delete[] pipes;
                    pipes = createPipes(numPipes,resolution.x,pipeGap);
                    bird.reset();
                    state = State::PLAYING;
                }

                if (state == State::LEVEL_SELECT)
                {
                    if (event.key.code == Keyboard::Num1)
                    {
                        swooshSound.play();
                        pipeGap = 300;
                        state = State::PLAYING;
                    }

                    if (event.key.code == Keyboard::Num2)
                    {
                        swooshSound.play();
                        pipeGap = 220;
                        state = State::PLAYING;
                    }

                    if (event.key.code == Keyboard::Num3)
                    {
                        swooshSound.play();
                        pipeGap = 170;
                        state = State::PLAYING;
                    }
                }
            }
        }

        Time dt = clock.restart();

        float dtAsSeconds=dt.asSeconds();

        if (state==State::PLAYING)
        {
            bird.update(dtAsSeconds);

            for (int i = 0;i < numPipes;i++)
            {
                pipes[i].update(dtAsSeconds);
                if (pipes[i].isOffScreen())
                {
                    float farthestX = 0;
                    for (int j = 0; j < numPipes; j++)
                    {
                        float currentX =pipes[j].getTopSprite().getPosition().x;

                        if (currentX > farthestX)
                        {
                            farthestX = currentX;
                        }
                    }                    
                    float gapY=250+rand()%400;
                    pipes[i].spawn(farthestX + 450,gapY,pipeGap);
                }

                if (pipes[i].checkCollision(bird.getPosition()))
                {
                    hitSound.play();
                    dieSound.play();
                    state =State::GAME_OVER;
                }

                if (pipes[i].isPassed(bird.getCenter().x))
                {
                    pointSound.play();
                    score++;

                }
            }

            if (bird.getCenter().y <0 ||bird.getCenter().y >resolution.y)
            {
                hitSound.play();
                state=State::GAME_OVER;
            }

            if (score > highScore)
            {
                highScore = score;
                std::ofstream outFile("highscore.txt");
                outFile<< highScore;
            }
        }

        scoreText.setString( "Score : " +std::to_string(score));

        highScoreText.setString("High Score : " +std::to_string(highScore));

        gameOverText.setString("GAME OVER\nPress R To Restart");

        window.clear(Color::White);

        window.setView(mainView);


        for (int i = 0;i < numPipes;i++)
        {
            window.draw(pipes[i].getTopSprite());

            window.draw(pipes[i].getBottomSprite());
        }

        window.draw(bird.getSprite());

        window.draw(scoreText);

        window.draw(highScoreText);

        if (state ==State::GAME_OVER)
        {
            window.draw(gameOverText);
        }
        if (state == State::PAUSED)
        {
            window.draw(pauseText);
        }

        if (state == State::LEVEL_SELECT)
        {
            window.draw(levelText);
        }

        window.display();
    }

    delete[] pipes;

    return 0;
}