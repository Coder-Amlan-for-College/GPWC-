#include "Pipe.cpp"
#include <ctime>
#include <cstdlib>

Pipe* createPipes(int numPipes,float resolutionX,float gapSize)
{
    Pipe* pipes = new Pipe[numPipes];

    for (int i = 0; i < numPipes; i++)
    {
        srand(time(0) * i);

        float gapY = 250+rand()%350;

        pipes[i].spawn(resolutionX + (i * 500),gapY,gapSize);
    }

    return pipes;
}