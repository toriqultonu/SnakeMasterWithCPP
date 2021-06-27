#include<iostream>
#include<vector>
#include<conio.h>
#include<time.h>
#include<synchapi.h>
#include<algorithm>
#include <windows.h>
using namespace std;
namespace consoleforeground //for text colour, colours made using 4 attributes
{
    enum {
        BLACK             = 0,
        WHITE             = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
    };
}
namespace consolebackground//for background colour,  colours made using 4 attributes
{
    enum {
        BLACK             = 0,
        GREEN             = BACKGROUND_INTENSITY | BACKGROUND_GREEN,
        CYAN              = BACKGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_BLUE,
        RED               = BACKGROUND_INTENSITY | BACKGROUND_RED,
        WHITE             = BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE,
    };
}

vector<int> snake;
bool kids=0,self_hit=1,reverse_snake=0;
int width=27,lenght=118,food_x=-1,food_y=-2,hsc,time1=50;// hsc- high score

class Board{
public:
    void setConsoleColour(unsigned short colour)//function to set colour
    {
        static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        cout.flush();
        SetConsoleTextAttribute(hOut, colour);
    }

    void setcursor(int x, int y)//function  to set the position of cursor in console(0 indexing)
    {
        static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        cout.flush();
        COORD coord = { (SHORT)x, (SHORT)y };
        SetConsoleCursorPosition(hOut, coord);
    }

    void print_title(){	//printing lelments that do not change with time on screen
        setcursor(0,0);
        setConsoleColour(consoleforeground::WHITE);
        cout<<"YOUR SCORE:                     ";
        cout<<"\n";
        //printing walls
            setConsoleColour(consolebackground::CYAN);
            for(int i=0;i<lenght+2;i++)
                cout<<" ";
            cout<<"\n";
            for(int i=0;i<width;i++){
                for(int j=0;j<lenght+2;j++){
                    if(j==0  || j==lenght+1)	setConsoleColour(consolebackground::CYAN);
                    else	 					setConsoleColour(consolebackground::BLACK);
                    cout<<" ";
                }
                cout<<"\n";
            }
            setConsoleColour(consolebackground::CYAN);
            for(int i=0;i<lenght+2;i++)
                cout<<" ";

    }

    void print_highscore(){//printing high score(changes with time
        int i,j;
        setcursor(11,0);
        setConsoleColour(consoleforeground::WHITE);
        cout<<snake.size()/2-3<<"  ";//-3 because the initial size of snake is 3
    }

    void welcome_to(){//printing welcome screen
        system("cls");//clearing screen
        setConsoleColour(consoleforeground::WHITE);
        int a;
        bool t=1;
        cout<<"\n\n\n\n\n\n\n\n\n                                       WELCOME TO THE SNAKE GAME\n\n";
        cout<<"                               		     press any key to start the game..";
        a=getch();

    }


    int print_final_message(){//printing final message screen
        setConsoleColour(consoleforeground::BLACK);
        system("cls");
        setConsoleColour(consoleforeground::WHITE);
        int a=snake.size()/2-3,k;
        if(a>hsc)
            hsc=a;
        cout<<"\n\n\n\n\n               GAME OVER\n";
        cout<<"               YOUR SCORE: "<<snake.size()/2-3<<endl;
        cout<<"               HIGH SCORE: "<<hsc;
        cout<<endl<<endl<<endl;
        cout<<"               PRESS ANY KEY TO RESTART\n";
        cout<<"               esc to EXIT\n\n\n\n\n\n";
        setConsoleColour(consoleforeground::WHITE);

        a=getch();
        return a;
    }

};


class Snake:public Board{

public:

    void initialise_snake(){//making my starting snake
        snake.clear();
        for(int i=0;i<2;i++){//loop to initialse snake,
            snake.push_back(0);//x cordinate
            snake.push_back(i);//y cordinate
        }
    }


    void move_snake(int move,char direction){//moviing my snake //v-vertical, 1=up,-1=down
        int i,j;
        if(direction=='v'){
            snake.push_back(snake[snake.end()-2-snake.begin()]+move);
            snake.push_back(snake[snake.end()-2-snake.begin()]);
        }
        else{
            snake.push_back(snake[snake.end()-2-snake.begin()]);
            snake.push_back(snake[snake.end()-2-snake.begin()]+move);
        }
        setcursor(snake[1]+1,snake[0]+2);
            setConsoleColour(consolebackground::BLACK);
        cout<<" ";
        snake.erase(snake.begin());//deleting snake back, yeah vector begin indicates back of snake
        snake.erase(snake.begin());
        //if want to pass through walls-mode-kids
        if(snake.back()==lenght && kids)										snake.back()-=lenght;
        else if(snake.back()==-1 && kids)										snake.back()+=lenght;
        else if(snake[snake.end()-snake.begin()-2]==-1 && kids)					snake[snake.end()-snake.begin()-2]+=width;
        else if(snake[snake.end()-snake.begin()-2]==width && kids)				snake[snake.end()-snake.begin()-2]-=width;
        //4 lines above for kids mode
        setcursor(snake.back()+1,snake[snake.end()-snake.begin()-2]+2);//printing snake
        //head of snake
            setConsoleColour(consolebackground::RED);
            cout<<" ";

        setcursor(snake[snake.end()-snake.begin()-3]+1,snake[snake.end()-snake.begin()-4]+2); //body of snake
            setConsoleColour(consolebackground::GREEN);
            cout<<" ";


    }
    void eat_food(){//eating food and generating new food
        food_x=rand()%(width);
        food_y=rand()%(lenght);
        setcursor(food_y+1,food_x+2);
            setConsoleColour(consolebackground::WHITE);
            cout<<" ";


        snake.insert(snake.begin(),snake[1]);//incresing length of snake if food is eaten
        snake.insert(snake.begin(),snake[1]);
    }

    bool check_interbody_death(){//to check if snake died by touching its own body or not
        int x,y,i;
        bool j=0;
        x=snake[snake.end()-snake.begin()-2];//x cordinate of snake mouth
        y=snake.back();						 //y cordinate of snake mouth
        for(i=0;i<snake.size()-2;i=i+2){	 //checking with body array
            if(x==snake[i] && y==snake[i+1]){
                j=1;
                break;
            }
        }
        return j;
    }

};




int main(){
    cin.tie(NULL);//to gain mannual flush control
    cout.tie(NULL);//to gain mannual flush control
    srand(time(0));//to generate random numbers, diiferent every time

    Board brd;
    Snake snk;

    brd.welcome_to();
    restart_game://goto statement, came from last

    system("cls");//to clean the screen
    brd.print_title();
    snk.initialise_snake();
    snk.eat_food();
    int i1=80,i2=80;//key press
    while(i1!=99){
        if(kbhit()){//if a key press is detected
            i1=getch();//take the buffer of keyboard
            if(i1==72 && (i2!=80 || reverse_snake))				i2=i1,snk.move_snake(-1,'v');
            else if(i1==80 && (i2!=72 || reverse_snake))			i2=i1,snk.move_snake(1,'v');
            else if(i1==75 && (i2!=77 || reverse_snake))			i2=i1,snk.move_snake(-1,'h');
            else if(i1==77 && (i2!=75 || reverse_snake))			i2=i1,snk.move_snake(1,'h');
            else if(i1==112){//112- p

                while(1){//to not remove pause menu untill p is pressed again
                    i1=getch();
                    if(i1==112)
                        break;
                }

            }
            else 								goto congo;//if other than arrow key are pressed
        }
        else{												//if no key is pressed
            congo:
            if(i2==72 )							snk.move_snake(-1,'v');
            else if(i2==80)						snk.move_snake(1,'v');
            else if(i2==75)						snk.move_snake(-1,'h');
            else if(i2==77)						snk.move_snake(1,'h');
        }
        if(snk.check_interbody_death() && !reverse_snake && self_hit)																				break;//body collision
        if(snake.back()>lenght-1 || snake.back()<0 || snake[snake.end()-snake.begin()-2]<0 || snake[snake.end()-snake.begin()-2]>width-1)		break;//wall collision
        if(food_y==snake.back() && food_x==snake[snake.end()-2-snake.begin()])																	snk.eat_food();
        brd.print_highscore();
        Sleep(time1);//for defficulty
    }
    int result;//keypress at last screen
    print_final:
    result=brd.print_final_message();//bringing keyoress from function

    if(result!=27)//if any key is pressed other than esc
        goto restart_game;
}
