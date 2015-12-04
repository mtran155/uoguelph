all: n1 n2 n3 n4 n5 n6 n7

n1: n1.c protocols.c protocols.h
	gcc -Wall -g n1.c protocols.c -o n1

n2: n2.c protocols.c protocols.h
	gcc -Wall -g n2.c protocols.c -o n2

n3: n3.c protocols.c protocols.h
	gcc -Wall -g n3.c protocols.c -o n3

n4: n4.c protocols.c protocols.h
	gcc -Wall -g n4.c protocols.c -o n4

n5: n5.c protocols.c protocols.h
	gcc -Wall -g n5.c protocols.c -o n5

n6: n6.c protocols.c protocols.h
	gcc -Wall -g n6.c protocols.c -o n6

n7: n7.c protocols.c protocols.h
	gcc -Wall -g n7.c protocols.c -o n7

run: n1 n2 n3 n4 n5 n6 n7 
	./n2 &
	./n3 &
	./n4 &
	./n5 &
	./n6 &
	./n7 &
	./n1 

valgrind:
	valgrind --leak-check=full --show-reachable=yes -v  ./n2 &
	./n3 &
	./n4 &
	./n5 &
	./n6 &
	./n7 &
	./n1

clean:
	rm n1 n2 n3 n4 n5 n6 n7

