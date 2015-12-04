#define GRAVITY 9.8
#define MAX_VELOCITY 30
#define MAX_ANGLE 90

typedef struct{
	float velocity;
	float angle;
	float mobX;
	float mobY;
	float mobZ;
	float yRotation;
	int active;
	int mobNum;
	float distanceX;
	float distanceY;
} Projectile;