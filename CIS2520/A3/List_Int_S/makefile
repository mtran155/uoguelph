all: test.out sort.out
test.out: test.o ListImplementation.o
	gcc test.o ListImplementation.o -o test.out
	
sort.out: sort.o ListImplementation.o
	gcc sort.o ListImplementation.o -o sort.out
	
sort.o: sort.c ListInterface.h ListType.h
	gcc -c sort.c

test.o: test.c ListInterface.h ListType.h
	gcc -c test.c

ListImplementation.o: ListImplementation.c ListInterface.h ListType.h 
	gcc -c ListImplementation.c
