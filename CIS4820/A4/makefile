

INCLUDES = -F/System/Library/Frameworks -framework OpenGL -framework GLUT -lm

a1: a1.c graphics.c visible.c graphics.h projectile.h
	gcc a1.c graphics.c visible.c -o a1 $(INCLUDES)

test: a1
	./a1 -testworld

run: a1
	./a1 

