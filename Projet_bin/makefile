algo: main.o voiture.o initfile.o
	gcc -Wall -o Projet_bin main.o voiture.o initfile.o

main.o: main.c voiture.h initfile.h
	gcc -Wall -c -g main.c

voiture.o: voiture.c voiture.h 
	gcc -Wall -c -g voiture.c

initfile.o: initfile.c initfile.h
	gcc -Wall -c -g initfile.c


clean:
	rm -f *.o Projet_bin
