// Header Files
#include <graphics.h>
#include <stdio.h>
// Macros
#define LEFT 1
#define RIGHT 2
#define UP 3
#define DOWN 4
//Game Data
int score; //Keeps the count of game score
int gamedelay;//Lower the game delay faster is the game speed.
struct Snake_Data {
int length;
int head_x; // Stores Head X Coordinate
int head_y; // Stores Head Y Coordinate
int head_dir; // Stores Head Direction
int tail_x; // Stores Tail X Coordinat
int tail_y; // Stores Tail Y Coordinat
int tail_dir; // Stores Tail Direction
int bend_x [1000]; //Stores X Bend Coordinate Declare it big enough to accomodate maximum bends
int bend_y [1000];
int bend_dir [1000]; // Stores Bend direction when tail reaches that X Coordinate
} Snake; // Declares a variable of the structure
// User - Defined functions -
int randomvalue (int starting, int ending) // Return a random int value between end and starting parameters
{
static int previous = 0;
int answer;
if (previous <0) previous = 0;
int difference = starting - ending;
time_t t;
srand((unsigned) time(&t));
for (int i = 0; i <previous;i++) rand ();
answer = (rand () % difference);
previous++;
return answer;
} 
void gamephysics ()
{
 static int foodcount = 0;//Keep Count of food
 int futurex, futurey, futurepixel;
 int i;
 char scorestring [100];
 if (foodcount < 500) //Adds a food if no food is present and upto maximum 500 food
   {
     int valid = 0;
     int foodx;
     int foody;
     while (!valid)
       {
         foodx = randomvalue (15,1003);
         foody = randomvalue (15,695);
         if (getpixel (foodx,foody)!= 15)
          {
             putpixel (foodx,foody,2);
             foodcount++; 
             valid = 1; 
          }
   
       } 
   } 
   
//Boundary Collision Check -
   
  if (Snake.head_x <= 10 || Snake.head_x >= 1008 || Snake.head_y <= 10 || Snake.head_y >= 700)
    {
      outtextxy (499,345, "Game Over"); 
      delay (3000);
      exit (1); 
     }

//Get future value of head in int variable futurex and futurey and calculate the logic
   
  futurex = Snake.head_x;
  futurey = Snake.head_y;
  if (Snake.head_dir == LEFT)
    {
      futurex --; 
    }
   if (Snake.head_dir == RIGHT) 
    {
      futurex ++; 
    }
   if (Snake.head_dir == UP) 
     {
      futurey --;
     }
   if (Snake.head_dir == DOWN) 
     {
      futurey ++; 
     }
futurepixel = getpixel(futurex,futurey);
           
   if (futurepixel == 2)//Food Eaten
     {
       foodcount --; //Reduce count
       score++; //Increase Score
       setcolor (0);//Rewrite Score 
       setfillstyle (0,0);
       bar (11,701,1007, 735);
       setcolor (4);
       sprintf (scorestring, "Score : %d", score);
       outtextxy (20,710, scorestring);
 //Increase the size of snake by 100 pixel you can put as much as you want
        if (Snake.tail_dir == UP)
           {
             for (i = 0; i<101;i++) putpixel (Snake.tail_x,Snake.tail_y+i,15); 
             Snake.tail_y +=100;
           }
        if (Snake.tail_dir == DOWN)
          {
            for (i = 0; i<101;i++) putpixel (Snake.tail_x,Snake.tail_y-i,15); 
            Snake.tail_y -=100;
          } 
        if (Snake.tail_dir == LEFT)
          {
            for (i = 0; i<101;i++)
            putpixel (Snake.tail_x+i,Snake.tail_y,15); 
            Snake.tail_x +=100;
            printf ("LEFT");
          }
        if (Snake.tail_dir == RIGHT)
          {
             for (i = 0; i<101;i++)
             putpixel (Snake.tail_x-i,Snake.tail_y,15); 
             Snake.tail_x -=100;
             printf ("RIGHT");
          } 
   
      }
   if (futurepixel == 15)
       {
         outtextxy (499,345, "Game Over"); 
         delay (3000);
         exit (1); 
       }
} 
                 
                 
            
 void userinput () //Process User Input and maps it into game
   {
     static int i = 0;
     if ( i > 1000) i = 0; // Makes the bend array a circular queue
     static int j = 0;
     if ( j > 1000) j = 0;
     char input;
     if (kbhit ())
       {
         input = getch ();
         //Change Respective Return value to our MACRO Direction Code Value 
         if (input == 80) input = DOWN;
   
         if (input == 72) input = UP;
   
         if (input == 75) input = LEFT;
  
         if (input == 77) input = RIGHT;
   
   
   
   
         //Change head direction based on logic
  
         if (input == LEFT && Snake.head_dir != RIGHT && Snake.head_dir != LEFT)
            {
               Snake.head_dir = LEFT; 
               Snake.bend_x [i] = Snake.head_x;
               Snake.bend_y [i] = Snake.head_y;
               Snake.bend_dir [i] = LEFT;
               i++;
             } 
         if (input == RIGHT && Snake.head_dir != LEFT && Snake.head_dir != RIGHT)
             {
               Snake.head_dir = RIGHT;
               Snake.bend_x [i] = Snake.head_x;
               Snake.bend_y [i] = Snake.head_y;
               Snake.bend_dir [i] = RIGHT;
               i++; 
             }
         if (input == UP && Snake.head_dir != DOWN && Snake.head_dir != UP)
             {
               Snake.head_dir = UP;
               Snake.bend_x [i] = Snake.head_x;
               Snake.bend_y [i] = Snake.head_y;
               Snake.bend_dir [i] = UP;
               i++; 
             }
          if (input == DOWN && Snake.head_dir != UP && Snake.head_dir != DOWN)
             {
               Snake.head_dir = DOWN; 
               Snake.bend_x [i] = Snake.head_x;
               Snake.bend_y [i] = Snake.head_y;
               Snake.bend_dir [i] = DOWN;
               i++; 
             } 
   
   
        }
         //Code to change the y direction at respective time
     if (Snake.tail_x == Snake.bend_x [j] && Snake.tail_y == Snake.bend_y [j])
        {
          Snake.tail_dir = Snake.bend_dir [j];
          j++; 
        }
   
 }
void movesnake ()
 {
  //Move the Head
  if (Snake.head_dir == LEFT)
    {
      Snake.head_x --; 
    }
  if (Snake.head_dir == RIGHT) 
    {
      Snake.head_x ++; 
    }
  if (Snake.head_dir == UP) 
    {
      Snake.head_y --;
    }
  if (Snake.head_dir == DOWN) 
    {
      Snake.head_y ++; 
    } 
  putpixel (Snake.head_x, Snake.head_y,15);
  //Move the Tail
  putpixel (Snake.tail_x, Snake.tail_y,0);
  if (Snake.tail_dir == LEFT)
    {
      Snake.tail_x --; 
    }
  if (Snake.tail_dir == RIGHT) 
     {
       Snake.tail_x ++; 
     }
  if (Snake.tail_dir == UP) 
     {
       Snake.tail_y --;
     }
  if (Snake.tail_dir == DOWN) 
     {
       Snake.tail_y ++; 
     } 
             
 }
             
void gameengine ()//Soul of our game.
 {
  while (1) 
    {
      movesnake ();
      userinput ();
      gamephysics ();
      delay (5);
     }
}

void initscreen ( ) //Draws Intial Screen.
 {
   int i;
   char scorestring [100];
   //Draw Boundary
   setcolor (4);
   line (10,10,10,700);
   line (1008,10,1008,700);
   line (10,700,1008,700);
   line (10,10,1008,10);
   //Write Score on scree
   sprintf (scorestring, "Score : %d", score);
   outtextxy (20,710, scorestring);
   //Draw Intial Snake Body 
   for (int i = Snake.length; i>0;i--) //This part should be redesigned for change of code of intial values 
      {
        putpixel (Snake.head_x-i,Snake.head_y,15); 
      }
 }
void initgamedata ( ) //Snakes starting coordinate if you modify any one make sure also modify dependent values
 {
   int i;
   Snake.length = 100;
   Snake.head_x = 200;
   Snake.head_y = 200;
   Snake.head_dir = RIGHT;
   Snake.tail_x = Snake.head_x- Snake.length;
   Snake.tail_y = Snake.head_y;
   Snake.tail_dir = Snake.head_dir;
   for (int i = 0; i <1000;i++) // There is no bend initally
     {
      Snake.bend_x[i] = 0;
      Snake.bend_dir[i] = 0; 
     }
    score = 0;
    gamedelay = 1000; // Should be change according to game speed need. 
   
}
// Main Function
int main ()
{
  initwindow(1018, 736,"Snake 1.0"); // Create the Snake Window with value is optimize for mode 1024 * 768 
  initgamedata ();
  initscreen ();
  gameengine (); 
  return 0;
}