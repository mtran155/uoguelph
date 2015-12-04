all: vcftool vcfextension.o

vcftool: vcftool.o vcutil.o iso3166-2_CountryCodes.o
	gcc vcftool.o vcutil.o iso3166-2_CountryCodes.o -o vcftool -Wall -g -fPIC -std=c99 -DNDEBUG

vcutil.o: vcutil.c vcutil.h
	gcc -c -Wall -g -fPIC -std=c99 -DNDEBUG vcutil.c

vcftool.o: vcftool.c vcftool.h 
	gcc -c -Wall -g -fPIC -std=c99 -DNDEBUG vcftool.c

iso3166-2_CountryCodes.o: iso3166-2_CountryCodes.c iso3166-2_CountryCodes.h
	gcc -c -Wall -g -fPIC -std=c99 iso3166-2_CountryCodes.c

vcfextension.o: vcfextension.c vcutil.c vcutil.h vcftool.c vcftool.h
	gcc -I/usr/include/python3.1 -fPIC -c vcfextension.c
	gcc -shared vcftool.o vcutil.o iso3166-2_CountryCodes.o vcfextension.o -o Vcf.so -DNDEBUG

python:
	python3 xvcf.py

valgrind:
	valgrind --leak-check=full --show-reachable=yes -v ./vcftool -canon < test.txt

clean:
	rm *.o *.so vcftool
