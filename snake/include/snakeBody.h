#ifndef SNAKEBODY_H
#define SNAKEBODY_H
#include "food.h"
#include <graphics.h>
#include<time.h>

enum DIR {LEFT , UP , RIGHT , DOWN};

class snakeBody
{
    private:
        POS arr[31];            // THIHS ARRAY IS GOING TO CONTAIN THE POSITIONS OF WHOLE SNAKE
        int direction;          // WORKING WITH ENUM !!!
        int length;
    public:
        snakeBody();
        void drawSnake();
        void appendSnake();         // IT IS RESPONSIBLE FOR INCREMENT IN SNAKE'S LENGTH
        void changeDirTo(int);
        int update();
        int getPosx();              // THESE FUNCTIONS ARE FOR OBVIOUS PURPOSES
        int getPosy();              // THESE FUNCTIONS ARE FOR OBVIOUS PURPOSES
        int getlength();

    protected:
};

#endif // SNAKEBODY_H
