algo: main.o voiture.o historique.o
	gcc -Wall -o projet_algo main.o voiture.o historique.o

main.o: main.c voiture.h historique.h
	gcc -Wall -c -g main.c

voiture.o: voiture.c voiture.h
	gcc -Wall -c -g voiture.c

historique.o: historique.c historique.h
	gcc -Wall -c -g historique.c


clean:
	rm -f *.o projet_algo


	
