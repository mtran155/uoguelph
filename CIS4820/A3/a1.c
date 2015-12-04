
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
#include <time.h>

// Networking libraries
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


#include "projectile.h"
#include "graphics.h"

/* mouse function called by GLUT when a button is pressed or released */
void mouse(int, int, int, int);

/* initialize graphics library */
extern void graphicsInit(int *, char **);

/* lighting control */
extern void setLightPosition(GLfloat, GLfloat, GLfloat);
extern GLfloat* getLightPosition();

/* viewpoint control */
extern void setViewPosition(float, float, float);
extern void getViewPosition(float *, float *, float *);
extern void getOldViewPosition(float *, float *, float *);
extern void setViewOrientation(float, float, float);
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

/* 2D drawing functions */
extern void  draw2Dline(int, int, int, int, int);
extern void  draw2Dbox(int, int, int, int);
extern void  draw2Dtriangle(int, int, int, int, int, int);
extern void  set2Dcolour(float []);


/* flag which is set to 1 when flying behaviour is desired */
extern int flycontrol;
/* flag used to indicate that the test world should be used */
extern int testWorld;
/* flag to print out frames per second */
extern int fps;
/* flag to indicate removal of cube the viewer is facing */
extern int dig;
/* flag indicates the program is a client when set = 1 */
extern int netClient;
/* flag indicates the program is a server when set = 1 */
extern int netServer; 
/* size of the window in pixels */
extern int screenWidth, screenHeight;
/* flag indicates if map is to be printed */
extern int displayMap;

/* frustum corner coordinates, used for visibility determination  */
extern float corners[4][3];

/* determine which cubes are visible e.g. in view frustum */
extern void ExtractFrustum();
extern void tree(float, float, float, float, float, float, int);

/********* end of extern variable declarations **************/

int cloud1 = 50;
int cloud2 = 25;
int cloud3 = 10;
int x = 0;
double currentTime;
double oldTime;
double deltaTime = 0;
Projectile ammo[10];
float gunAngle;

/*Networking Variables*/
// Server Side
int server_sockfd, client_sockfd;
int server_len, client_len;
struct sockaddr_in server_address;
struct sockaddr_in client_address;

// Client Side
int sockfd;
int len;
struct sockaddr_in address;
int result;
/**************************/

/*** collisionResponse() ***/
/* -performs collision detection and response */
/*  sets new xyz  to position of the viewpoint after collision */
/* -can also be used to implement gravity by updating y position of vp*/
/* note that the world coordinates returned from getViewPosition() will be the negative value of the array indices */
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
   
   //keep player within the world
   if( (x * - 1) < 0 || (x * - 1) > 100 || (z * - 1) < 0 || (z * - 1) > 100 || (y * -1) == 0){
      getOldViewPosition(&x, &y, &z);
      setViewPosition(x,y,z);
   }
	/* your collision code goes here */
}

void gravity(){
   float x, y, z;
   
   getViewPosition(&x,&y,&z);

   if(y * -1 <= 0)
      return;
   
   if (world [(int)(x*-1)][(int)(y*-1) - 1 ][(int)(z*-1)] == 0 || world [(int)(x*-1)][(int)(y*-1) - 1 ][(int)(z*-1)] == 5){
      setViewPosition(x, y + 0.2 ,z );
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

float convertToRadian(float x){
   return x * (M_PI/180);
}

/* I used this website to help with range conversion
   http://stackoverflow.com/questions/929103/convert-a-number-range-to-another-range-maintaining-ratio
*/
double rangeConverter(double value, double oldMin, double oldMax, double newMin, double newMax){
   double oldRange = (oldMax - oldMin);
   double newRange = (newMax - newMin);
   
   return (((value - oldMin) * newRange) / oldRange) + newMin;
}

int craterBoundary(int x){
   if(x >= 99)
      return 99;
   else if (x <= 0)
      return 0;
   else
      return x;
}

void createCrater(int x,int y, int z){
   int i, j, k;
   int copyX, copyZ;

   copyX = copyZ = 0;

   for(i = 0; i < 3; i++){
      if(i == 0){
         // 5x5 layer
         copyX = x-2;
         copyZ = z-2;
         for(j = 0; j < 5; j++){
            for(k = 0; k < 5; k++){
               world[craterBoundary(copyX+j)][craterBoundary(y)][craterBoundary(k+copyZ)] = 0;
            }
         }
      }
      else if(i == 1){
         // 3x3 layer
         copyX = x-1;
         copyZ = z-1;
         for(j = 0; j < 3; j++){
            for(k = 0; k < 3; k++){
               world[craterBoundary(copyX+j)][craterBoundary(y-1)][craterBoundary(k+copyZ)] = 0;
            }
         }
      }
      else // 1x1 layer
         world[craterBoundary(x)][craterBoundary(y-2)][craterBoundary(z)] = 0;
   }
}

float maxHeight(float velocity, float angle){
   return ((pow(velocity * sin(convertToRadian(angle)), 2)) / (2 * GRAVITY));
}

float trajectoryDistance(float x, float velocity, float angle){
   return (x * (tan(convertToRadian(angle))) - ((GRAVITY * pow(x,2)) / (2 * (pow(velocity * cos(convertToRadian(angle)),2)))));
}

int * launchProjectile(Projectile * X){
   float y, mobX, mobY, mobZ;
   static int values[2];
   int flag;

   // animate mob with angle and no velocity -- falls straight down
   if(X->angle >= 0 && X->velocity == 0){
      mobX = X->mobX;
      mobY = (X->mobY - X->distanceY);
      mobZ = X->mobZ;
      setMobPosition(X->mobNum, X->mobX, mobY, X->mobZ, 0.0);

      // hit terrain make a hole and deactivate mob
      if (world [(int)X->mobX][(int)mobY][(int)X->mobZ] != 0){
         createCrater((int)X->mobX,(int)mobY,(int)X->mobZ);
         hideMob(X->mobNum);
         X->active = 0;
         X->distanceY = 0;
         X->distanceX = 0;
      }
      X->distanceY += 0.1;
   }

   // animate mob when user wants to use 90 degree angle
   else if(X->angle == 90){
      y = maxHeight(X->velocity, X->angle);
      mobX = X->mobX;
      mobZ = X->mobZ;

      if(y > X->distanceY){
         mobY = X->mobY + X->distanceY;
         setMobPosition(X->mobNum, X->mobX, mobY, X->mobZ, 0.0);
         X->distanceY += 0.3;
      }

      else{
         mobY = (X->mobY + X->distanceY - 0.3) - X->distanceX;

         if ((int)mobY > 48){
            flag = 1;
         }
         else
            flag = 0;

         if (world [(int)X->mobX][(int)mobY][(int)X->mobZ] != 0 && flag == 0){
            createCrater((int)X->mobX,(int)mobY,(int)X->mobZ);
            hideMob(X->mobNum);
            X->active = 0;
            X->distanceY = 0;
            X->distanceX = 0;
         }
         else{
            setMobPosition(X->mobNum, X->mobX, mobY, X->mobZ, 0.0);
            X->distanceX += 0.3;
         }
      }
   }

   // animate mob when 0 <= angle >= 90
   else{
      y = trajectoryDistance(X->distanceX, X->velocity, X->angle);

      mobX = X->mobX + X->distanceX * (cos(X->yRotation));
      mobY = X->mobY + y;
      mobZ = X->mobZ + X->distanceX * (sin(X->yRotation));

      if ((int)mobY > 48)
         flag = 1;
      else
         flag = 0;

      if((int)mobX < 0 || (int)mobX > 100 ||(int)mobZ < 0 || (int)mobZ > 100 ||(int)mobY < 0){
         hideMob(X->mobNum);
         X->active = 0;
         X->distanceX = 0;
         flag = 0;
      }
      else if (world [(int)mobX][(int)mobY][(int)mobZ] != 0 && flag == 0){
         createCrater((int)mobX,(int)mobY,(int)mobZ);
         hideMob(X->mobNum);
         X->active = 0;
         X->distanceX = 0;
      }
      else{
         setMobPosition(X->mobNum, mobX, mobY, mobZ, 0.0);
         if(X->angle < 70)
            X->distanceX += 0.4;
         else
            X->distanceX += 0.1;
      }
   }

   values[0] = mobX;
   values[1] = mobZ;
   return values; 
}

float projectileVelocity(float x, float y){
   float value;

   value = rangeConverter((x - y), 0, 450, 0, MAX_VELOCITY);

   if( value > MAX_VELOCITY)
      value = MAX_VELOCITY;

   return value;
}

float projectileAngle(float x, float y){
   float value;

   value = rangeConverter((x - y), 0, 350, 0, MAX_ANGLE);

   if( value > MAX_ANGLE)
      value = MAX_ANGLE;

   return value;
}

void initializeProjectile(Projectile * X){
   X->active = 0;
   X->velocity = 0.0;
   X->angle = 0.0;
   X->mobX = 0.0;
   X->mobY = 0.0;
   X->mobZ = 0.0;
   X->yRotation = 0.0;
   X->mobNum = 0;
   X->distanceX = 0.0;
   X->distanceY = 0.0;
}

void projectileParams(Projectile * X, float velocity, float angle, float mobX, float mobY, float mobZ, float yRotation, int mobNum){
   X->velocity = velocity;
   X->angle = angle;
   X->mobX = mobX;
   X->mobY = mobY;
   X->mobZ = mobZ;
   X->yRotation = yRotation;
   X->active = 1;
   X->mobNum = mobNum;
   X->distanceX = 0.0;
   X->distanceY = 0.0;
}

void displayStruct(Projectile * X){
   printf("active = %d velocity = %f angle = %f mobX = %f mobY = %f mobZ = %f\n", X->active, X->velocity, X->angle,
      X->mobX, X->mobY, X->mobZ);
}

	/******* draw2D() *******/
	/* draws 2D shapes on screen */
	/* use the following functions: 			*/
	/*	draw2Dline(int, int, int, int, int);		*/
	/*	draw2Dbox(int, int, int, int);			*/
	/*	draw2Dtriangle(int, int, int, int, int, int);	*/
	/*	set2Dcolour(float []); 				*/
	/* colour must be set before other functions are called	*/

void draw2D() {

   float x, y, z;
   int newX, newZ, i;
   int *coordinates;

   getViewPosition(&x, &y, &z);

   x *= -1; 
   z *= -1;

   // printf("x = %d\n z = %d\n", (int)x, (int)z);

   if (testWorld) {
		/* draw some sample 2d shapes */
      // GLfloat green[] = {0.0, 0.5, 0.0, 1};
      // set2Dcolour(green);
      // draw2Dline(0, 0, 500, 500, 15);
      // draw2Dtriangle(0, 0, 200, 200, 0, 200);

      if (displayMap == 1){
         GLfloat black[] = {0.0, 0.0, 0.0, 0.5};
         set2Dcolour(black);
         draw2Dbox(screenWidth/1.35, screenHeight/1.35, screenWidth, screenHeight);
      }

      else if (displayMap == 2){  
         GLfloat black[] = {0.0, 0.0, 0.0, 0.5};
         set2Dcolour(black);
         draw2Dbox(screenWidth/5, screenHeight/5, screenWidth/1.25, screenHeight/1.25);
      }
   }

   else {
      if (displayMap == 1){

         // Boundary of map
         GLfloat red[] = {1.0, 0.0, 0.0, 1};
         set2Dcolour(red);
         draw2Dline((screenWidth/1.35), (screenHeight-1), (screenWidth), (screenHeight-1), 1); // top line
         draw2Dline((screenWidth/1.35), (screenHeight), (screenWidth/1.35), (screenHeight/1.35), 1); // left line
         draw2Dline((screenWidth-1), (screenHeight), (screenWidth-1), (screenHeight/1.35), 1); // right line
         draw2Dline((screenWidth/1.35), (screenHeight/1.35), (screenWidth), (screenHeight/1.35), 1); // bottom line

         // Get position of player and draw on mini map
         newX = rangeConverter(x, 0, 100, screenWidth/1.35, screenWidth - 5);
         newZ = rangeConverter(z, 0, 100, screenHeight/1.35, screenHeight - 5);
         GLfloat white[] = {1.0, 1.0, 1.0 , 1};
         set2Dcolour(white);
         draw2Dbox(newX,newZ,newX+5,newZ+5);

         // Draw ammo on minimap
         for(i = 0; i < 10; i++){
            if(ammo[i].active == 1){
               coordinates = launchProjectile(&ammo[i]);
               newX = rangeConverter(coordinates[0], 0, 100, screenWidth/1.35, screenWidth);
               newZ = rangeConverter(coordinates[1], 0, 100, screenHeight/1.35, screenHeight);

               GLfloat pink[] = {1.0, 0.08, 0.58, 1};
               set2Dcolour(pink);
               draw2Dtriangle(newX + 5, newZ + 5, newX - 5, newZ - 5, newX - 5, newZ + 5);
            }
            else{
               GLfloat pink[] = {1.0, 0.08, 0.58,0};
               set2Dcolour(pink);
            }
         }

         // Draw top right minimap
         GLfloat black[] = {0.0, 0.0, 0.0, 0.5};
         set2Dcolour(black);
         draw2Dbox(screenWidth/1.35, screenHeight/1.35, screenWidth, screenHeight);
      }

      else if (displayMap == 2){

         GLfloat red[] = {1.0, 0.0, 0.0, 1};
         set2Dcolour(red);
         draw2Dline((screenWidth/5 - 1), (screenHeight/1.25), (screenWidth/1.25 + 2), (screenHeight/1.25), 3);
         draw2Dline((screenWidth/5), (screenHeight/1.25), (screenWidth/5), (screenHeight/5), 3);
         draw2Dline((screenWidth/1.25), (screenHeight/1.25), (screenWidth/1.25), (screenHeight/5), 3);
         draw2Dline((screenWidth/5 - 1), (screenHeight/5), (screenWidth/1.25 + 2), (screenHeight/5), 3);

         newX = rangeConverter(x, 0, 100, screenWidth/5, screenWidth/1.25 - 10);
         newZ = rangeConverter(z, 0, 100, screenHeight/5, screenHeight/1.25 - 10);
         GLfloat white[] = {1.0, 1.0, 1.0 , 1};
         set2Dcolour(white);
         draw2Dbox(newX,newZ,newX+10,newZ+10);

         // Draw ammo on minimap
         for(i = 0; i < 10; i++){
            if(ammo[i].active == 1){
               coordinates = launchProjectile(&ammo[i]);
               newX = rangeConverter(coordinates[0], 0, 100, screenWidth/5, screenWidth/1.25);
               newZ = rangeConverter(coordinates[1], 0, 100, screenHeight/5, screenHeight/1.25);

               GLfloat pink[] = {1.0, 0.08, 0.58, 1};
               set2Dcolour(pink);
               draw2Dtriangle(newX + 10, newZ + 10, newX - 5, newZ - 5, newX - 5, newZ + 15);
            }
            else{
               GLfloat pink[] = {1.0, 0.08, 0.58,0};
               set2Dcolour(pink);
            }
         }

         // Draw large minimap in the middle
         GLfloat black[] = {0.0, 0.0, 0.0, 0.5};
         set2Dcolour(black);
         draw2Dbox(screenWidth/5, screenHeight/5, screenWidth/1.25, screenHeight/1.25);
         
      }
	/* your code goes here */
   }
}

/* called by GLUT when a mouse button is pressed or released */
/* -button indicates which button was pressed or released */
/* -state indicates a button down or button up event */
/* -x,y are the screen coordinates when the mouse is pressed or */
/*  released */ 
void mouse(int button, int state, int x, int y) {

   float viewX, viewY, viewZ;
   float mobX, mobY, mobZ;
   float posX, posY, posZ;
   float radian;
   double newVelocity, newAngle; 
   static double velocity, angle; 
   static int up_X, down_X, up_Y, down_Y, flag, click;
   int i;

   viewX = viewY = viewZ = 0.0;
   mobX = mobY = mobZ = 0.0;
   posX = posY = posZ = 0.0;
   radian = 0.0;
   newVelocity = newAngle = 0.0;

   if(netServer){
      return;
   }

   if (button == GLUT_LEFT_BUTTON){
      flag = 1;
   }      
   else if (button == GLUT_MIDDLE_BUTTON){
   }      
   else{
      flag = 2;
   }

   if (state == GLUT_UP){
      // left click up
      if (flag == 1){
         getViewOrientation(&viewX, &viewY, &viewZ);
         getViewPosition(&posX, &posY, &posZ);

         radian = convertToRadian(viewY + 270);
         mobX = (cos(radian) * 3) + (posX * -1);
         mobY = (posY * -1);
         mobZ = (sin(radian) * 3) + (posZ * -1);

         for(i = 0; i < 10; i++){
            if(ammo[i].active == 0){
               createMob(i, mobX, mobY, mobZ, 0.0);
               projectileParams(&ammo[i], velocity, angle, mobX, mobY, mobZ, radian, i);
               break;
            }
         }
      }
      // right click up -- get user velocity and angle
      if(flag == 2){
         up_X  = x;
         up_Y = y;

         if(click == 1){
            newVelocity = up_X - down_X;
            newAngle = down_Y - up_Y;

            // want to increase velocity
            if(newVelocity > 0){
               newVelocity = projectileVelocity(up_X, down_X);
               velocity += newVelocity;
   
               if(velocity > MAX_VELOCITY){
                  velocity = MAX_VELOCITY;
               }
            }

            // decrease velocity
            else{
               newVelocity = projectileVelocity(down_X, up_X);
               velocity -= newVelocity;
               
               if(velocity < 0){
                  velocity = 0;
               }
            }

            // increase angle
            if(newAngle > 0){
               newAngle = projectileAngle(down_Y,up_Y);
               angle += newAngle;
               gunAngle = angle;
               
               if(angle > MAX_ANGLE){
                  angle = MAX_ANGLE;
                  gunAngle = MAX_ANGLE;
               }         
            }

            // decrease angle
            else{
               newAngle = projectileAngle(up_Y,down_Y);
               angle -= newAngle;
               gunAngle = angle;
               
               if(angle < 0){
                  angle = 0;
                  gunAngle = 0;
               }
            }
         }

         else{
            velocity = projectileVelocity(up_X, down_X);

            if(velocity < 0){
               velocity = 0;
            }

            angle = projectileAngle(down_Y,up_Y);
            gunAngle = angle;

            if(angle < 0){
               angle = 0;
               gunAngle = 0;
            }
         }

         click = 1;
         printf("velocity = %d%%\nangle = %d degrees\n", (int)(velocity/MAX_VELOCITY * 100), (int)angle);
      }
   }
      
   else{
      //right click down
      if(flag == 2){
         down_X = x;
         down_Y = y;
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
   int *values;

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
      // setMobPosition(0, mob0x, mob0y, mob0z, mob0ry);

   /* move mob 0 in the x axis */
      if (increasingmob0 == 1){
         mob0x += 0.1;
         // mob0z += 0.2;
      }         
      else{
         mob0x -= 0.1;
         // mob0z -= 0.2;
      }         
      if (mob0x > 50 ) increasingmob0 = 0;
      if (mob0x < 30 ) increasingmob0 = 1;

   /* rotate mob 0 around the y axis */
      mob0ry += 1.0;
      if (mob0ry > 360.0) mob0ry -= 360.0;

   /* move mob 1 and rotate */
      // setMobPosition(1, mob1x, mob1y, mob1z, mob1ry);

   /* move mob 1 in the z axis */
   /* when mob is moving away it is visible, when moving back it */
   /* is hidden */
      if (increasingmob1 == 1) {
         mob1z += 0.2;
         // showMob(1);
      } else {
         mob1z -= 0.2;
         // hideMob(1);
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

      for(i = 0; i < 10; i++){
         if(ammo[i].active == 1){
            // displayStruct(&ammo[i]);
            launchProjectile(&ammo[i]);
         }
      }

   } else {

      float x, y, z;
      float serverX, serverY, serverZ;
      float viewX, viewY, viewZ;
      float serverViewX, serverViewY;
      float serverAngle;
      char server[256];
      char client[256];

      if(netServer){
         char * token;
         int counter = 0;

         read(client_sockfd, &server , 35);

         token = strtok(server, " ");

         if(token != NULL)
            serverX = atof(token);

         while( token != NULL){

            token = strtok(NULL, " ");

            if (counter == 0){
               if(token != NULL)
                  serverY = atof(token);
            }
            if (counter == 1){
               if(token != NULL)
                  serverZ = atof(token);
            }

            counter++;
         }

         setViewPosition(serverX, serverY, serverZ);

         server[0] = '\0';

         read(client_sockfd, &server , 20);

         serverViewY = atof(server);

         server[0] = '\0';

         read(client_sockfd, &server , 20);
         serverAngle = atof(server);

         setViewOrientation(360.0 - serverAngle, serverViewY, 0.0);

      }

      else if (netClient){
         getViewPosition(&x, &y, &z);
         sprintf(client, "%f %f %f", x, y, z);

         write(sockfd, &client, 35);

         client[0] = '\0';

         getViewOrientation(&viewX, &viewY, &viewZ);
         sprintf(client, "%f", viewY);

         write(sockfd, &client, 20);

         client[0] = '\0';

         sprintf(client, "%f", gunAngle);
         write(sockfd, &client, 20);

      }

      gravity();
      currentTime = clock();

      if(x == 0){
         oldTime = currentTime;
         x++;
      }

      deltaTime += (currentTime - oldTime)/CLOCKS_PER_SEC;

      if( deltaTime > 0.4){         
         moveCloud(cloud1, 55);
         moveCloud(cloud2, 30);
         moveCloud(cloud3, 70);
         deltaTime = 0;
         oldTime = currentTime;
      }

      for(i = 0; i < 10; i++){
         if(ammo[i].active == 1){
            // displayStruct(&ammo[i]);
            values = launchProjectile(&ammo[i]);
         }
      }
   /* your code goes here */

   }
}

void createClient(){
   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   address.sin_family = AF_INET;
   address.sin_addr.s_addr = inet_addr("127.0.0.1");
   address.sin_port = htons(9734);
   len = sizeof(address);

   result = connect(sockfd, (struct sockaddr *)&address, len);

   if(result == -1) {
       perror("Connection Failed");
       exit(1);
   }
}

void createServer(){
   /*  Remove any old socket and create an unnamed socket for the server.  */
   server_sockfd = socket(AF_INET, SOCK_STREAM, 0);

   /*  Name the socket.  */

   server_address.sin_family = AF_INET;
   server_address.sin_addr.s_addr = htonl(INADDR_ANY);
   server_address.sin_port = htons(9734);
   server_len = sizeof(server_address);
   bind(server_sockfd, (struct sockaddr *)&server_address, server_len);

   listen(server_sockfd, 5);
   
   client_len = sizeof(client_address);
   client_sockfd = accept(server_sockfd,(struct sockaddr *)&client_address, &client_len);
}

void createSand(){
   int i, j, k;

   for(i=0; i<WORLDX; i++) {
      for(j=0; j<WORLDZ; j++) {
         for(k = 0; k < 17; k++){
            world[i][k][j] = 8;
         }            
      }
   }
}

int main(int argc, char** argv){
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
      // for(i=0; i<WORLDX; i++) {
      //    for(j=0; j<WORLDZ; j++) {
      //       world[i][24][j] = 3;
      //    }
      // }
      for(i=0; i<WORLDX; i++) {
         for(j=0; j<WORLDZ; j++) {
            for(k = 0; k < 25; k++){
               world[i][k][j] = 3;
            }            
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
      // createMob(0, 50.0, 25.0, 52.0, 0.0);
      // createMob(1, 50.0, 25.0, 52.0, 0.0);
      // createMob(2, 50.0, 90.0, 52.0, 0.0);

   /* create sample player */
      createPlayer(0, 52.0, 27.0, 52.0, 0.0);

   } else {
      srand(time(NULL));
      double perlinValue, newValue;
      char serverBlock[10];
      char serverColour[10];
      char clientBlock[10];
      char clientColour[10];

      for (i = 0; i < 10; ++i){
            initializeProjectile(&ammo[i]);
      }

      // Networking
      if (netServer){
         createServer();

         for(i = 0; i < WORLDX; i++){
            for(j = 0; j < WORLDZ; j++){
               perlinValue = PerlinNoise_2D((double)i/7,(double)j/7);
               newValue = rangeConverter(perlinValue, -1, 1, 10, 30);

               sprintf(serverBlock, "%d", (int)newValue);
               write(client_sockfd, &serverBlock, 10);

               for(k = 0; k < (int)newValue; k++){
                  world[i][k][j] = (rand() % 2) + 1;
                  sprintf(serverColour, "%d", world[i][k][j]);
                  write(client_sockfd, &serverColour, 10);
               }
            }
         }

         createSand();
      }

      else if (netClient){
         createClient();
         int height;
         int colour;

         for(i = 0; i < WORLDX; i++){         
            for(j = 0; j < WORLDZ; j++){
               read(sockfd, &clientBlock, 10);
               height = atoi(clientBlock);

               for(k = 0; k < height; k++){
                  read(sockfd, &clientColour, 10);
                  colour = atoi(clientColour);
                  world[i][k][j] = colour;
               }           
            }
         }

         createSand();
      }

      // Single player
      else{

         for(i = 0; i < WORLDX; i++){         
            for(j = 0; j < WORLDZ; j++){
               perlinValue = PerlinNoise_2D((double)i/7,(double)j/7);
               newValue = rangeConverter(perlinValue, -1, 1, 10, 30);          
               for(k = 0; k < (int)newValue;k++){
                  world[i][k][j] = (rand() % 2) + 1;
               }           
            }
         }

         createSand();
      }
   /* your code to build the world goes here */

   }

   /* starts the graphics processing loop */
   /* code after this will not run until the program exits */
   glutMainLoop();

   if(netServer){
      close(client_sockfd);
   }
   if(netClient){
      close(sockfd);
   }
   
   return 0; 
}