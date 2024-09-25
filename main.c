#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include "life.h"

char grids[2][24][80] = {
    {"                                                                                ",
     "                                                                                ",
     "                                                                                ",
     "                                                                                ",
     "                                                                                ",
     "                                                                                ",
     "                                                                                ",
     "                                                                                ",
     "                                                                                ",
     "                                                                                ",
     "                                                                                ",
     "                                                                                ",
     "                                                                                ",
     "                                                                                ",
     "                                                                                ",
     "                                                                                ",
     "                                                                                ",
     "                                                                                ",
     "                                                                                ",
     "                                                                                ",
     "                                                                                ",
     "                                                                                ",
     "                                                                                ",
     "                                                                                "},
    {"                                                                                ",
     "                                                                                ",
     "                                                                                ",
     "                                                                                ",
     "                                                                                ",
     "                                                                                ",
     "                                                                                ",
     "                                                                                ",
     "                                                                                ",
     "                                                                                ",
     "                                                                                ",
     "                                                                                ",
     "                                                                                ",
     "                                                                                ",
     "                                                                                ",
     "                                                                                ",
     "                                                                                ",
     "                                                                                ",
     "                                                                                ",
     "                                                                                ",
     "                                                                                ",
     "                                                                                ",
     "                                                                                ",
     "                                                                                "}};

int current = 0;

int high(int val1, int val2)
{
    return (val1 > val2) ? val1 : val2;
}

int low(int val1, int val2)
{
    return (val1 > val2) ? val2 : val1;
}

int countNeighbors(int i, int j)
{
    int count = 0;

    for (int x = high(0, i - 1); x <= low(GRIDY - 1, i + 1); x++)
    {
        for (int y = high(0, j - 1); y <= low(GRIDX - 1, j + 1); y++)
        {
            if (x == i && y == j)
                continue;

            if (grids[current][x][y] == 'X')
            {
                count++;
            }
        }
    }

    return count;
}

void copyMatrix(char **grid)
{
    for (int i = 0; i < GRIDY; i++)
    {
        for (int j = 0; j < GRIDX; j++)
        {
            grids[current][i][j] = grid[i][j];
        }
    }
}

void updateCells()
{
    int count;

    for (int i = 0; i < GRIDY; i++)
    {
        for (int j = 0; j < GRIDX; j++)
        {
            count = countNeighbors(i, j);

            if (grids[current][i][j] == 'X')
            {
                if (count < 2 || count > 3)
                {
                    grids[(current + 1) % 2][i][j] = ' ';
                }
                else
                {
                    grids[(current + 1) % 2][i][j] = 'X';
                }
            }
            else
            {
                if (count == 3)
                {
                    grids[(current + 1) % 2][i][j] = 'X';
                }
                else
                {
                    grids[(current + 1) % 2][i][j] = ' ';
                }
            }
        }
    }

    current = (current + 1) % 2;
}

void printCells()
{
    for (int i = 0; i < GRIDY; i++)
    {
        for (int j = 0; j < GRIDX; j++)
        {
            printf("%c", grids[current][i][j]);
        }
        printf("\n");
    }
}

void conway(int iterations)
{
    for (int i = 0; i < iterations; i++)
    {
        updateCells();
    }
}

void copyToGrid(char **grid)
{
    for (int i = 0; i < GRIDY; i++)
    {
        for (int j = 0; j < GRIDX; j++)
        {
            grid[i][j] = grids[current][i][j];
        }
    }
}

void printGrid(char **grid)
{
    for (int i = 0; i < GRIDY; i++)
    {
        for (int j = 0; j < GRIDX; j++)
        {
            printf("%c", grid[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char *argv[])
{
    if (argc > 3 || argc < 1)
    {
        return -1;
    }
    int a;
    if (argc == 3)
    {
        a = atoi(argv[2]);
    }
    else
    {
        a = 0;
    }
    char **grid = parse_life(argv[1]);
    copyMatrix(grid);
    conway(a);
    copyToGrid(grid);
    printGrid(grid);
    free_grid(grid);
    return 0;
}
