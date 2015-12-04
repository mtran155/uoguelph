
/* Derived from scene.c in the The OpenGL Programming Guide */
/* Keyboard and mouse rotation taken from Swiftless Tutorials #23 Part 2 */
/* http://www.swiftless.com/tutorials/opengl/camera2.html */

/* Frames per second code taken from : */
/* http://www.lighthouse3d.com/opengl/glut/index.php?fps */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>


#include "graphics.h"

	/* initialize graphics library */
extern void graphicsInit(int *, char **);

/* lighting control */
extern void setLightPosition(GLfloat, GLfloat, GLfloat);
extern GLfloat* getLightPosition();

/* viewpoint control */
extern void setViewPosition(float, float, float);
extern void getViewPosition(float *, float *, float *);
extern void getOldViewPosition(float *, float *, float *);
extern void getViewOrientation(float *, float *, float *);

/* add cube to display list so it will be drawn */
extern int addDisplayList(int, int, int);

/* mob controls */
extern void createMob(int, float, float, float, float);
extern void setMobPosition(int, float, float, float, float);
extern void hideMob(int);
extern void showMob(int);

/* player controls */
extern void createPlayer(int, float, float, float, float);
extern void setPlayerPosition(int, float, float, float, float);
extern void hidePlayer(int);
extern void showPlayer(int);

/* flag which is set to 1 when flying behaviour is desired */
extern int flycontrol;

/* flag used to indicate that the test world should be used */
extern int testWorld;

/* list and count of polygons to be displayed, set during culling */
extern int displayList[MAX_DISPLAY_LIST][3];
extern int displayCount;

/* flag to print out frames per second */
extern int fps;

/* flag to indicate removal of cube the viewer is facing */
extern int dig;

/* flag indicates the program is a client when set = 1 */
extern int netClient;

/* flag indicates the program is a server when set = 1 */
extern int netServer; 

/* frustum corner coordinates, used for visibility determination  */
extern float corners[4][3];

/* determine which cubes are visible e.g. in view frustum */
extern void ExtractFrustum();
extern void tree(float, float, float, float, float, float, int);

/********* end of extern variable declarations **************/

int cloud1 = 50;
int cloud2 = 25;
int cloud3 = 10;

/*** collisionResponse() ***/
/* -performs collision detection and response */
/*  sets new xyz  to position of the viewpoint after collision */
/* -can also be used to implement gravity by updating y position of vp*/
/* note that the world coordinates returned from getViewPosition()
   will be the negative value of the array indices */
void collisionResponse() {
   float x, y, z;

   getViewPosition(&x, &y, &z);

   if (world [(int)(x * -1)][(int)(y * -1)][(int)(z * -1)] != 0){
      if(world [(int)(x * -1)][(int)(y * -1) + 1][(int)(z * -1)] == 0){
         setViewPosition(x, y - 1, z);
      }
      else{
         getOldViewPosition(&x, &y, &z);
         setViewPosition(x, y , z);
      }
   }
	/* your collision code goes here */
}

void gravity(){
   float x, y, z;
   
   getViewPosition(&x,&y,&z);
   
   if (world [(int)(x*-1)][(int)(y*-1) - 1 ][(int)(z*-1)] == 0 || world [(int)(x*-1)][(int)(y*-1) - 1 ][(int)(z*-1)] == 5){
      setViewPosition(x, y + 0.4 ,z );
   }
}

void moveCloud(int x, int y){
	int i, j;
	int counter;
	int copyX;
	 
	counter = 1;
	 
	 
	while(1){
      if (counter == 5){
         break;
      }

		if(counter == 1){
			world[x + 2][49][(x + y) - 3] = 0;
			world[x + 2][49][(x + y) + 3] = 0;
		}
		 
		if(counter == 2){
			copyX = x;
			for(i = 0; i < 3; i++){
				copyX++;
				world[copyX][49][(x + y) - 2] = 0;
				world[copyX][49][(x + y) + 2] = 0;
			}
		}

		if(counter == 3){
			copyX = x;
			for(i = 0; i < 5; i++){
				world[copyX][49][(x + y) - 1] = 0;
				world[copyX][49][(x + y) + 1] = 0;
				copyX++;
			}
		}

		if(counter == 4){
			copyX = x - 1;
			for(i = 0; i < 7; i++){
				world[copyX][49][(x + y)] = 0;
				copyX++;
			}
		}

		counter++;
	}
	
	x++;
    counter = 1;

   while(1){
      if (counter == 5){
         break;
      }

      if(counter == 1){
         world[x + 2][49][(x + y) - 3] = 5;
         world[x + 2][49][(x + y) + 3] = 5;
      }
       
	  if(counter == 2){
         copyX = x;
         for(i = 0; i < 3; i++){
            copyX++;
            world[copyX][49][(x + y) - 2] = 5;
            world[copyX][49][(x + y) + 2] = 5;
         }
      }

      if(counter == 3){
         copyX = x;
         for(i = 0; i < 5; i++){
            world[copyX][49][(x + y) - 1] = 5;
            world[copyX][49][(x + y) + 1] = 5;
            copyX++;
         }
      }

      if(counter == 4){
         copyX = x - 1;
         for(i = 0; i < 7; i++){
            world[copyX][49][(x + y)] = 5;
            copyX++;
         }
      }

      counter++;
   }

   if(x == cloud1 + 1){
      cloud1++;
	   if(cloud1 == 90){
		   cloud1 = 10;
	   }	   
   }
   if(x == cloud2 + 1){
      cloud2++;
	   if(cloud2 == 90){
		   cloud2 = 10;
	   }
   }
   if(x == cloud3 + 1){
      cloud3++;
	   if(cloud3 == 90){
		   cloud3 = 10;
	   }
   }
}

/*** update() ***/
/* background process, it is called when there are no other events */
/* -used to control animations and perform calculations while the  */
/*  system is running */
/* -gravity must also implemented here, duplicate collisionResponse */
void update() {
int i, j, k;
float *la;

	/* sample animation for the test world, don't remove this code */
	/* -demo of animating mobs */
   if (testWorld) {
	   gravity();
	/* sample of rotation and positioning of mob */
	/* coordinates for mob 0 */
      static float mob0x = 50.0, mob0y = 25.0, mob0z = 52.0;
      static float mob0ry = 0.0;
      static int increasingmob0 = 1;
	/* coordinates for mob 1 */
      static float mob1x = 50.0, mob1y = 25.0, mob1z = 52.0;
      static float mob1ry = 0.0;
      static int increasingmob1 = 1;

	/* move mob 0 and rotate */
	/* set mob 0 position */
      setMobPosition(0, mob0x, mob0y, mob0z, mob0ry);

	/* move mob 0 in the x axis */
      if (increasingmob0 == 1)
         mob0x += 0.2;
      else 
         mob0x -= 0.2;
      if (mob0x > 50) increasingmob0 = 0;
      if (mob0x < 30) increasingmob0 = 1;

	/* rotate mob 0 around the y axis */
      mob0ry += 1.0;
      if (mob0ry > 360.0) mob0ry -= 360.0;

	/* move mob 1 and rotate */
      setMobPosition(1, mob1x, mob1y, mob1z, mob1ry);

	/* move mob 1 in the z axis */
	/* when mob is moving away it is visible, when moving back it */
	/* is hidden */
      if (increasingmob1 == 1) {
         mob1z += 0.2;
         showMob(1);
      } else {
         mob1z -= 0.2;
         hideMob(1);
      }
      if (mob1z > 72) increasingmob1 = 0;
      if (mob1z < 52) increasingmob1 = 1;

	/* rotate mob 1 around the y axis */
      mob1ry += 1.0;
      if (mob1ry > 360.0) mob1ry -= 360.0;
    /* end testworld animation */

      moveCloud(cloud1, 55);
      moveCloud(cloud2, 30);
      moveCloud(cloud3, 70);

   } else {
      gravity();
      moveCloud(cloud1, 55);
      moveCloud(cloud2, 30);
      moveCloud(cloud3, 70);
	/* your code goes here */

   }
}

/*For the perlin noise I used the website
http://freespace.virgin.net/hugo.elias/models/m_perlin.htm
that was provided by the professer in the assignment.txt*/

double Interpolate(double a, double b, double x){
	double ft, f;
	 
	ft = x * 3.1415927;
	f = (1.0 - cos(ft)) * 0.5;
	 
	return a * (1.0-f) + b * f;
}

double Noise(double x, double y){
	int n;
	 
   n = x + y * 57;
   n = (n<<13) ^ n;

   return (1.0 - ((n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0);     
}

double SmoothNoise(double x, double y ){
   double corners, sides, center;
   
	corners = (Noise(x-1.0, y-1.0) + Noise(x+1.0, y-1.0) + Noise(x-1.0, y+1.0) + Noise(x+1.0, y+1.0)) / 16.0;
	sides   = (Noise(x-1.0, y)  + Noise(x+1.0, y)  + Noise(x, y-1.0)  + Noise(x, y+1.0) ) /  8.0;
	center  =  Noise(x, y) / 4.0;	 
   
	return corners + sides + center;
}

double InterpolatedNoise(double x, double y){
   int integer_X, integer_Y;;
   double fractional_X, fractional_Y;
   double v1, v2, v3, v4;
   double i1, i2;
   
   integer_X = (int)x;
   fractional_X = x - integer_X; 

   integer_Y = (int)y;
   fractional_Y = y - integer_Y;   
   
   v1 = SmoothNoise(integer_X, integer_Y);
   v2 = SmoothNoise(integer_X + 1.0, integer_Y);   
   v3 = SmoothNoise(integer_X, integer_Y + 1.0);
   v4 = SmoothNoise(integer_X + 1.0, integer_Y + 1.0);  
   
   i1 = Interpolate(v1, v2, fractional_X);
   i2 = Interpolate(v3, v4, fractional_X);
   
   return Interpolate(i1, i2, fractional_Y);
}

double PerlinNoise_2D(double x, double y){
   double total, persistence;
   int numOctave, i;

   total = 0;
   persistence = 0.6;
   numOctave = 2 - 1;
   
   double freqeuncy = 0;
   double amplitude = 0;
   
   
   for(i = 0; i < numOctave; i++){
      freqeuncy = pow(2,i);
      amplitude = pow(persistence,i);
      total = total + InterpolatedNoise(x * freqeuncy, y * freqeuncy) * amplitude;
   }   
   
   return total;
}

int main(int argc, char** argv)
{
int i, j, k;
	/* initialize the graphics system */
   graphicsInit(&argc, argv);

	/* the first part of this if statement builds a sample */
	/* world which will be used for testing */
	/* DO NOT remove this code. */
	/* Put your code in the else statment below */
	/* The testworld is only guaranteed to work with a world of
		with dimensions of 100,50,100. */
   if (testWorld == 1) {
	/* initialize world to empty */
      for(i=0; i<WORLDX; i++)
         for(j=0; j<WORLDY; j++)
            for(k=0; k<WORLDZ; k++)
               world[i][j][k] = 0;
	
	/* some sample objects */
	/* build a red platform */
      for(i=0; i<WORLDX; i++) {
         for(j=0; j<WORLDZ; j++) {
            world[i][24][j] = 3;
         }
      }
	/* create some green and blue cubes */
      world[50][25][50] = 1;
      world[49][25][50] = 1;
      world[49][26][50] = 1;
      world[52][25][52] = 2;
      world[52][26][52] = 2;

	/* blue box shows xy bounds of the world */
      for(i=0; i<WORLDX-1; i++) {
         world[i][25][0] = 2;
         world[i][25][WORLDZ-1] = 2;
      }
      for(i=0; i<WORLDZ-1; i++) {
         world[0][25][i] = 2;
         world[WORLDX-1][25][i] = 2;
      }

	/* create two sample mobs */
	/* these are animated in the update() function */
      createMob(0, 50.0, 25.0, 52.0, 0.0);
      createMob(1, 50.0, 25.0, 52.0, 0.0);

	/* create sample player */
      createPlayer(0, 52.0, 27.0, 52.0, 0.0);

   } else {
	   double perlinValue;
	   double newValue, oldValue, oldMin, newMax, newMin, oldMax;
	   
	   oldMin = -1;
	   oldMax = 1;
	   newMin = 10;
	   newMax = 18;
	   
	   /*I used this website to help with range conversion
		http://stackoverflow.com/questions/929103/convert-a-number-range-to-another-range-maintaining-ratio*/
	   
	   double oldRange = (oldMax - oldMin);
	   double newRange = (newMax - newMin);	   
	   
	   for(i = 0; i < WORLDX; i++){         
		   for(j = 0; j < WORLDZ; j++){
			   perlinValue = PerlinNoise_2D((double)i,(double)j);			   
			   newValue = (((perlinValue - oldMin) * newRange) / oldRange) + newMin;
			   for(k = 0; k < (int)newValue;k++){
               world[i][k][j] = 3;
            }			   
		   }
      }
	/* your code to build the world goes here */

   }


	/* starts the graphics processing loop */
	/* code after this will not run until the program exits */
   glutMainLoop();
   return 0; 
}