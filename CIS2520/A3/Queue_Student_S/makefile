a.out: myProgram.o StudentImplementation.o QueueImplementation.o
	gcc myProgram.o StudentImplementation.o QueueImplementation.o

myProgram.o: myProgram.c StudentInterface.h StudentType.h QueueInterface.h QueueType.h
	gcc -c myProgram.c

StudentImplementation.o: StudentImplementation.c StudentInterface.h StudentType.h
	gcc $(FLAG) -c StudentImplementation.c

QueueImplementation.o: QueueImplementation.c QueueInterface.h QueueType.h StudentInterface.h StudentType.h
	gcc $(FLAG) -c QueueImplementation.c


















