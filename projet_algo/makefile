algo: main.o voiture.o historique.o utils.o
	gcc -Wall -o projet_algo main.o voiture.o historique.o utils.o

main.o: main.c voiture.h historique.h utils.h
	gcc -Wall -c -g main.c

voiture.o: voiture.c voiture.h utils.h
	gcc -Wall -c -g voiture.c

historique.o: historique.c historique.h utils.h
	gcc -Wall -c -g historique.c

utils.o: utils.c utils.h
	gcc -Wall -c -g utils.c

clean:
	rm -f *.o projet_algo


	
