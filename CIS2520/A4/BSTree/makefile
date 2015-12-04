a.out: myProgram.o StudentImplementation.o TreeImplementation.o
	gcc myProgram.o StudentImplementation.o TreeImplementation.o

myProgram.o: myProgram.c TreeInterface.h TreeType.h StudentInterface.h StudentType.h 
	gcc -c myProgram.c

StudentImplementation.o: StudentImplementation.c StudentInterface.h StudentType.h
	gcc -c StudentImplementation.c

TreeImplementation.o: TreeImplementation.c TreeInterface.h TreeType.h
	gcc -c TreeImplementation.c


















