#include <SFML/Graphics.hpp>
#include "Player.cpp"

using namespace sf;

//Declare createBackground() passing VertexArray rVA and arena as parameters
//This returns tile size
int createBackground(VertexArray &rVA,IntRect arena);

int main()
{
	// The game will always be in one of four states
    enum class State{PAUSED,PLAYING,GAME_OVER,LEVELING_UP};
	// Start with the GAME_OVER state
	State state=State::GAME_OVER;
	// Get the screen resolution and create an SFML window
    Vector2f resolution;
	resolution.x = 1920;
	resolution.y = 1080;

	RenderWindow window(VideoMode(resolution.x,resolution.y),"Zombie Arena");
	// Create a an SFML View for the main action
    View mainView(FloatRect(0,0,resolution.x,resolution.y));
	// Here is our clock for timing everything
	Clock clock;
	// How long has the PLAYING state been active
    int gameTimeTotal;
	// Where is the mouse in relation to world coordinates
    Vector2f mouseWorldPosition;
	// Where is the mouse in relation to screen coordinates
    Vector2i mouseScreenPosition;
	// Create an instance of the Player class
	Player player;
	// The boundaries of the arena
	IntRect arena;

	//****Declare the background vertex array
	VertexArray background;
	
	//****Create and load the texture for background vertex array
    Texture backgroundTexture;
    backgroundTexture.loadFromFile("graphics/background_sheet.png");

	// The main game loop
	while (window.isOpen())
	{
		/*
		************
		Handle input
		************
		*/

		// Handle events
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::KeyPressed)
			{
				// Pause a game while playing
				if(event.key.code==Keyboard::Return && state==State::PLAYING){
					state==State::PAUSED;
				}
				// Restart while paused
				if(event.key.code==Keyboard::Return && state==State::PAUSED){
					state==State::PLAYING;
					clock.restart();
				}
	
				// Start a new game while in GAME_OVER state
                if(event.key.code==Keyboard::Return && state==State::GAME_OVER){
					state==State::PLAYING;
				}
				//some code will be added for playing state later

			}
		}// End event polling


		 // Handle the player quitting
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		// Handle controls while playing
		if (state == State::PLAYING)
		{
			// Handle the pressing and releasing of the WASD keys
			if(event.key.code==Keyboard::W){
					player.moveUp();
				}
			else{
					player.stopUp();
				}
			if(event.key.code==Keyboard::S){
				player.moveDown();
			}
			else{
				player.stopDown();
			}
			if(event.key.code==Keyboard::A){
				player.moveLeft();
			}
			else{
				player.stopLeft();
			}
			if(event.key.code==Keyboard::D){
				player.moveRight();
			}
			else{
				player.stopRight();
			}

		}// End WASD while playing

		 // Handle the levelling up state
		if (state == State::LEVELING_UP)
		{
			// Handle the player levelling up

			if (state == State::PLAYING)
			{
				// Prepare thelevel
				// We will modify the next two lines later
				arena.width = 500;
				arena.height = 500;
				arena.left = 0;
				arena.top = 0;
				 
				//****Call the createBackground function
                int tileSize = createBackground(background,arena);
				// Spawn the player in the middle of the arena
                player.spawn(arena,resolution,tileSize);
				// Reset the clock so there isn't a frame jump
				clock.restart();
			}
		}// End levelling up

		 /*
		 ****************
		 UPDATE THE FRAME
		 ****************
		 */
		if (state == State::PLAYING)
		{
			// Update the delta time
			Time dt=clock.restart();
			// Update the total game time
			gameTimeTotal += dt.asSeconds();
			// Make a decimal fraction of 1 from the delta time
			float dtAsSeconds = dt.asSeconds();
			// Where is the mouse pointer
            mouseScreenPosition=Mouse::getPosition();
			// Convert mouse position to world coordinates of mainView
            mouseWorldPosition = window.mapPixelToCoords(mouseScreenPosition,mainView);
			// Update the player
            player.update(dtAsSeconds,mouseScreenPosition);
			// Make a note of the players new position
            Vector2f playerPosition(player.getCenter());
			// Make the view centre around the player
			mainView.setCenter(playerPosition);				
		}// End updating the scene

		 /*
		 **************
		 Draw the scene
		 **************
		 */

		if (state == State::PLAYING)
		{
			window.clear();

			// set the mainView to be displayed in the window
			// And draw everything related to it
            window.setView(mainView);
			//****Draw the background
              

			// Draw the player
		}

		if (state == State::LEVELING_UP)
		{
		}

		if (state == State::PAUSED)
		{
		}

		if (state == State::GAME_OVER)
		{
		}

		window.display();

	}// End game loop

	return 0;
}

int createBackground(VertexArray& rVA, IntRect arena)
{
	// Anything we do to rVA we are actually doing to background (in the main function)

	// How big is each tile/texture
	const int TILE_SIZE = 50;
	const int TILE_TYPES = 3;
	const int VERTS_IN_QUAD = 4;
	
	//****declare and initialize arena width(worldWidth)
	//****and arena height(worldHeight) in terms of no. of tiles  


	//****What type of primitive are we using?
	

	//****Set the size of the vertex array
	

	//****Start at the beginning of the vertex array
	

	for (int w = 0; w < worldWidth; w++)
	{
		for (int h = 0; h < worldHeight; h++)
		{
			//****Position each vertex in the current quad


			//****Define the position in the Texture to draw for current quad
			//****Either mud, stone, grass or wall
			if (h == 0 || h == worldHeight - 1 || w == 0 || w == worldWidth - 1)
			{
				//****Use the wall texture
				
			}
			else
			{
				//Use a random floor texture
				/*srand((int)time(0) + h * w - h);
				int mOrG = (rand() % TILE_TYPES);
				int verticalOffset = mOrG * TILE_SIZE;
				*/
				
				//****Use the random texture


			}

			//****Position ready for the next for vertices

		}//end of inner for
	}//end of outer for

	return TILE_SIZE;
}
