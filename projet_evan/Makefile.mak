algo: mainprinc.o voiture.o historique.o utilisateur.o
	gcc -Wall -o projet_algo mainprinc.o voiture.o historique.o utilisateur.o

main.o: mainprinc.c voiture.h historique.h utilisateur.h 
	gcc -Wall -c -g mainprinc.c

voiture.o: voiture.c voiture.h 
	gcc -Wall -c -g voiture.c

historique.o: historique.c historique.h 
	gcc -Wall -c -g historique.c

utilisateur.o: utilisateur.c utilisateur.h
	gcc -Wall -c -g utilisateur.c

clean:
	rm -f *.o projet_algo
