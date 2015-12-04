a.out: myProgram.o StudentImplementation.o HeapImplementation.o
	gcc myProgram.o StudentImplementation.o HeapImplementation.o 

myProgram.o: myProgram.c HeapInterface.h HeapType.h StudentInterface.h StudentType.h 
	gcc -c myProgram.c 

StudentImplementation.o: StudentImplementation.c StudentInterface.h StudentType.h
	gcc -c StudentImplementation.c 

HeapImplementation.o: HeapImplementation.c HeapInterface.h HeapType.h
	gcc -c HeapImplementation.c 


















