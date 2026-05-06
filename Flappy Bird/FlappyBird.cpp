#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Bird.cpp"
#include "Pipe.cpp"
#include "CreatePipes.cpp"

#include <fstream>

using namespace sf;

int main()
{
    enum class State
    {
        PAUSED,
        GAME_OVER,
        PLAYING
    };

    State state = State::PAUSED;

    Vector2f resolution;

    resolution.x = 1920;
    resolution.y = 1080;

    RenderWindow window(VideoMode(resolution.x,resolution.y),"Flappy Bird", Style::Fullscreen);

    View mainView(FloatRect(0,0, resolution.x,resolution.y));

    Clock clock;

    // Texture bgTexture;
    // bgTexture.loadFromFile(
    //     "assets/background.png");

    // Sprite background;
    // background.setTexture(bgTexture);

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

    Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setCharacterSize(70);
    gameOverText.setPosition(650, 450);

    // SoundBuffer flapBuffer;
    // flapBuffer.loadFromFile("assets/flap.wav");

    // Sound flapSound;
    // flapSound.setBuffer(flapBuffer);

    // SoundBuffer hitBuffer;
    // hitBuffer.loadFromFile("assets/hit.wav");

    // Sound hitSound;
    // hitSound.setBuffer(hitBuffer);

    // Music bgMusic;
    // bgMusic.openFromFile("assets/bgmusic.ogg");

    // bgMusic.setLoop(true);
    // bgMusic.play();

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

                if (event.key.code==Keyboard::Enter)
                {
                    if (state ==State::PAUSED)
                    {
                        state =State::PLAYING;
                    }
                    else if (state ==State::PLAYING)
                    {
                        state=State::PAUSED;
                    }
                }

                if (event.key.code ==Keyboard::Space && state == State::PLAYING)
                {
                    bird.flap();
                    //flapSound.play();
                }

                if (event.key.code ==Keyboard::R && state == State::GAME_OVER)
                {
                    score = 0;
                    delete[] pipes;
                    pipes = createPipes(numPipes,resolution.x,pipeGap);
                    bird.reset();
                    state = State::PLAYING;
                }

                if (event.key.code == Keyboard::Num1)
                {
                    pipeGap = 300;
                }

                if (event.key.code == Keyboard::Num2)
                {
                    pipeGap = 220;
                }

                if (event.key.code==Keyboard::Num3)
                {
                    pipeGap = 170;
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
                if(pipes[i].isOffScreen()){
                    float gapY = 100+rand()%400;
                    pipes[i].spawn(resolution.x,gapY,pipeGap);
                }

                if (pipes[i].checkCollision(bird.getPosition()))
                {
                    //hitSound.play();
                    state =State::GAME_OVER;
                }

                if (pipes[i].isPassed(bird.getCenter().x))
                {
                    score++;
                }
            }

            if (bird.getCenter().y <0 ||bird.getCenter().y >resolution.y)
            {
                //hitSound.play();
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

        // window.draw(background);

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

        window.display();
    }

    delete[] pipes;

    return 0;
}