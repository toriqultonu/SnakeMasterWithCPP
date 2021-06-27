#ifndef FOOD_H
#define FOOD_H
#include <graphics.h>
#include<time.h>
struct POS
{
       int x,y;
       POS()
       {
            x = -50;
            y = 0;
       }
};

class food
{

    private:
        POS foodPos;
    public:
         void draw();                    // functtion to draw the food on the graphics window
        void generate(int, int);        // function to generate food everytime snake eats it
        bool update(int, int);

    protected:


};

#endif // FOOD_H
