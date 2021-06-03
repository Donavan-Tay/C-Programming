#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#define Height 20
#define Width 50

void intro();
void Snake_Setup();
void Reset_Screen_Position ();
void Game_Setting();
void Random();
void movement();
int Response();
void Tail_Remove();
void GameOver();
int Snake[Height][Width],x,y,Gy,Head,Body, Game, Food,a,b,Var,Dir,Score,HighScore, Speed, life;
FILE *f;

int main()
{
    intro();
    system ("cls");
    Sleep (100);

    Snake_Setup();
    life = 3;

    while (Game == 0)
    {

       Game_Setting();
       Reset_Screen_Position ();
       Random();
       movement();
       Tail_Remove();
       Sleep(Speed);
    }

    return 0;
}


void Game_Setting ()
{
    for (int i = 0; i<= Width+1; i++)
    {
        if (i==0)
        {   //Top Left Border
            printf("%c",201);
        }   else if (i == Width+1)
            {   //Top Right Border
                printf ("%c", 187);
            }   else
                {   // Line Border
                    printf ("%c",205);
                }
    }
    printf("\n");

    for(int i = 0; i <Height; i++)
    {   //Prints first || for each row
        printf ("%c", 186);
        for(int j = 0; j < Width; j++)
        {
            if(Snake[i][j]==0) printf(" ");
            if(Snake[i][j]>0 && Snake[i][j]!=Head) printf("%c",219);
            if(Snake[i][j]==Head) printf("%c",02);
            if(Snake[i][j] == -1) printf ("%c",64);
            if (j==Width-1) printf ("%c\n",186);

        }
    }

    for (int i = 0; i<= Width+1; i++)
    {
        if (i==0)
        {   //Bottom Left Border
            printf("%c",200);
        }   else if (i == Width+1)
            {   //Bottom Right Border
                printf ("%c", 188);
            }   else
                {   // Line Border
                    printf ("%c",205);
                }

   }
     printf (" \n Current Score: %d      Life: %d      HighScore: %d", Score, life, HighScore);
}

void Snake_Setup()
{
    f=fopen("D:\\HighScore.txt", "r");
    fscanf(f,"%d",&HighScore);
    fclose(f);
    for (int i = 0 ; i < Height ; i++)
    {
        for(int j=0;j<Width;j++)
        {
            Snake[i][j]=0;
        }

    }

    x=Height/2;
    y=Width/2;
    Body = 1;
    Head = 5;
    Gy = y;
    Game = 0;
    Food = 0; //food
    Dir = 'd';
    Score = 0;
    Speed = 120;

    for(int i =0 ; i < Head; i++)
    {
        Gy++;
        Snake[x][Gy-Head] = i+1;
    }

}

//Prints everything at the same position
void Reset_Screen_Position ()
{
    HANDLE hOut;
    COORD Position;
    hOut = GetStdHandle (STD_OUTPUT_HANDLE);
    Position.X = 0;
    Position.Y=0;
    SetConsoleCursorPosition(hOut,Position);
}

void Random()
{
    srand(time(0));
    a = 1+ rand() % (Height-2);
    b = 1 + rand() % (Width-2);

    if(Food == 0 && Snake[a][b] == 0)
    {
        Snake[a][b]= -1;
        Food = 1;
        if(Speed>10 && Score !=0)
        {
            Speed = Speed -5;
        }
    }


}

void movement()
{
    Var = Response();
    Var = tolower(Var);

    if( ( (Var=='w'||Var=='s')||(Var=='a'||Var=='d')) && abs(Dir-Var) >5)
    {
        Dir = Var;
    }
    if(Dir == 'w')
    {
        x--;
        if(Snake[x][y] !=0 && Snake[x][y]!=-1) GameOver();
        if(x==-1) GameOver();
        if(Snake[x][y]==-1)
        {
            Food = 0;
            Score +=1;
            Body -=1;
        }
        Head++;
        Snake[x][y] = Head;
    }

    if(Dir == 'a')
    {
        y--;
        if(Snake[x][y] !=0 && Snake[x][y]!=-1) GameOver();
        if (y==0) GameOver();
        if(Snake[x][y]==-1)
        {
            Food = 0;
            Score +=1;
            Body -=1;
        }
        Head++;
        Snake[x][y] = Head;
    }

    if(Dir == 's')
    {
        x++;
        if(Snake[x][y] !=0 && Snake[x][y]!=-1) GameOver();
        if (x==Height) GameOver();
        if(Snake[x][y]==-1)
        {
            Food = 0;
            Score +=1;
            Body -=1;
        }
        Head++;
        Snake[x][y] = Head;
    }

    if(Dir == 'd')
    {
        y++;
        if(Snake[x][y] !=0 && Snake[x][y]!=-1) GameOver();
        if (y==Width) GameOver();
        if(Snake[x][y]==-1)
        {
            Food = 0;
            Score +=1;
            Body -=1;
        }
        Head++;
        Snake[x][y] = Head;
    }
}

int Response()
{
    if(_kbhit())
    {
        return _getch();
    } else
        {
            return -1;
        }

}
//
void Tail_Remove()
{
    for(int i=0;i<Height;i++)
    {
        for(int j=0;j<Width;j++)
        {
            if(Snake[i][j]==Body)
            {
                Snake[i][j] = 0;
            }
        }
    }
    Body++;
}

void GameOver()
{
    if(life <= 1)
    {
    printf("\a"); //produces a sound
    Sleep(1000); //waits for 1000 milliseconds
    system("Cls");//Clears Screen

    if(Score > HighScore)
    {
        printf("New HighScore %d!!!!!! \n\n",Score);
        system("pause");
        f=fopen("D:\\HighScore.txt","w");
        fprintf(f,"%d",Score);
        fclose(f);
    }
    system ("Cls");
    printf("\n \n          TRY AGAIN NEXT TIME      !!!!! \n");
    printf ("              Score: %d \n\n", Score);
    printf ("              Press ENTER to Try again or ESC to Exit \n\n");



    //Var 13 is ENTER key and Var 27 is ESC key
    while (1)
    {
        Var = Response();
        if(Var ==13)
        {
            Game = 0;
            Snake_Setup();
            life +=2;
            break;
        }   else if (Var == 27)
                {
                    Game = 1;
                    break;
                }
    }
    system("Cls");
    }   else
            {
                life -= 1;
                Snake_Setup();
            }
}

void intro()
{
    printf("WELCOME!!!!     \n\n");
    printf("Game Instructions\n");
    printf("Use w to move up, a to move left, d to move right and s to move down \n");
    printf("To score points guide the snake to the food (@) \n");
    printf("Beware! eating the snake body or touching the borders will result in Game over!!! \n");
    printf ("To start the game press any key to continue!");
    getch();


}
