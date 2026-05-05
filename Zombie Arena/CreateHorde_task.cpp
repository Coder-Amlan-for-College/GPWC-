#include "Zombie_task.cpp"
//createHorde() function
Zombie* createHorde(int numZombies, IntRect arena)
{
	//array of objects of type Zombie
	Zombie *zombies = new Zombie[numZombies];
	//arena wall-boundary to spawn zombies minX,maxX,minY,maxY
	int minX = arena.left+20;
	int maxX = arena.width-20;
	int minY = arena.top+20;
	int maxY = arena.height-20;
	//place each zombie in the arena
	for (int i = 0; i < numZombies; i++)
	{

		// Which side should the zombie spawn
		srand((int)time(0) * i);
		int side = rand()%4; 
		float x, y;

		switch (side)
		{
		case 0:
			// left
			x = minX;
			y = minY+rand()%maxY;
			break;

		case 1:
			// right
			x = maxX;
			y = minY+rand()%maxY;
			break;

		case 2:
			// top
			x = minX+rand()%maxX;
			y = minY;
			break;

		case 3:
			// bottom
			x = minX+rand()%maxX;
			y = maxY;
			break;
		}

		// Bloater, crawler or runner
		srand((int)time(0) * i * 2);
		int type = rand()%3;

		// Spawn the new zombie into the array
		zombies[i].spawn(x,y,type,i);

	}
	return zombies;
}
