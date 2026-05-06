#include "Pipe.cpp"
#include <ctime>
#include <cstdlib>

Pipe* createPipes(int numPipes,float resolutionX,float gapSize)
{
    Pipe* pipes = new Pipe[numPipes];

    for (int i = 0; i < numPipes; i++)
    {
        srand(time(0) * i);

        float gapY = 100 + rand() % 400;

        pipes[i].spawn(resolutionX + (i * 400),gapY,gapSize);
    }

    return pipes;
}