vcftool: vcftool.o vcutil.o iso3166-2_CountryCodes.o
	gcc vcftool.o vcutil.o iso3166-2_CountryCodes.o -o vcftool -Wall -g -std=c99 -DNDEBUG

vcutil.o: vcutil.c vcutil.h
	gcc -c -Wall -g -std=c99 -DNDEBUG vcutil.c

vcftool.o: vcftool.c vcftool.h 
	gcc -c -Wall -g -std=c99 -DNDEBUG vcftool.c

iso3166-2_CountryCodes.o: iso3166-2_CountryCodes.c iso3166-2_CountryCodes.h
	gcc -c -Wall -g -std=c99 iso3166-2_CountryCodes.c

clean:
	rm *.o vcftool

