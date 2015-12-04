a.out: myProgram.o StudentImplementation.o ListImplementation.o
	gcc myProgram.o StudentImplementation.o ListImplementation.o

myProgram.o: myProgram.c StudentInterface.h StudentType.h ListInterface.h ListType.h
	gcc $(FLAGS)-c myProgram.c

StudentImplementation.o: StudentImplementation.c StudentInterface.h StudentType.h
	gcc $(FLAGS)-c StudentImplementation.c

ListImplementation.o: ListImplementation.c ListInterface.h ListType.h StudentInterface.h StudentType.h
	gcc $(FLAGS)-c ListImplementation.c


















