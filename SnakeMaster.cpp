#include<iostream>
#include<graphics.h>
#include<conio.h>
#include<stdlib.h>
using namespace std;
int main()
{
 int gdriver=DETECT,gmode;
 initgraph(&gdriver,&gmode,"");
 cleardevice();
 //x and y are for the circle
 int x=300,y=250;
 //x1 and y1 are fo generating foot at random place
 int x1=200,y1=230,food=0;
 // key is used to take input from KEYBOARD
 char key;
 // a boundry line
 rectangle(100,100,500,400);

// if x or y exceeds the boundry limit game is out
 while(x>100 && x<500 && y>100 && y<400)
 {
 //these are for generating food at randm pleaces..
 // these 4 conditions are if the circle that is in your ccontrol reaches the food then
 // generate new foot at new place within the boundry
 if(x+1==x1 && y+1==y1 || x-1==x1 && y+1==y1 || x+1==x1 && y-1==y1 || x-1==x1 &&
y-1==y1)
 {
 // food counts number of dots accessed
 food++;
 againx:
 x1=rand();
 // these conditions are for generating food within the boundry
 if(x1<100 || x1>500)
 goto againx;
 againy:
 y1=rand();
 if(y1<100 || y1>400)
 goto againy;
 // this draws a dot for food

circle(x1,y1,3);
 }
 // KEYS INFORMATION
 key=getch();
 if(key=='A' || key=='a')//move up
 y--;
 else if(key=='Z'||key=='z')//move right
 x++;
 else if(key=='L' || key=='l')//for left
 x--;
 else if(key=='.')//for downward
 y++;
 cleardevice();
 outtextxy(100,0,"SNAKE GAME BY JAVERIA");
 outtextxy(100,20,"Z to move right");
 outtextxy(100,40,"L to move left");
 outtextxy(100,60,". to move down");
 outtextxy(100,80,"A to move up");
 // boundry line and the circle

rectangle(100,100,500,400);
 circle(x1,y1,3);
 // you can control the circle of green color to reach to food
 setcolor(2);
 circle(x,y,4);
 setcolor(WHITE);
 }
 outtextxy(100,420,"You are out");
 cout<<"\n\n\n\tYOUR TOTAL SCORES ARE "<<food<<endl<<endl;
//conditions so that the game exit when you press space
 char exitt;
 again:
 exitt=getch();
 if(exitt==32)
 closegraph();
 else
 goto again;

return 0;
}

