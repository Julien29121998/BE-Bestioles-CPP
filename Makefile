all: main author info

main : main.cpp Aquarium.o DBestiole.o Bestiole.o Milieu.o Membre.o Camouflages.o Nageoire.o Carapace.o Capteur.o Oreilles.o Yeux.o Factory.o Comportement.o
	g++ -Wall -std=c++11 -o main main.cpp Aquarium.o DBestiole.o Bestiole.o Membre.o Camouflages.o Nageoire.o Carapace.o Milieu.o Capteur.o Oreilles.o Yeux.o Factory.o Comportement.o -I . -lX11 -lpthread

Aquarium.o : Aquarium.h DBestiole.h Aquarium.cpp
	g++ -Wall -std=c++11  -c Aquarium.cpp -I .

Bestiole.o : Bestiole.h Milieu.h DBestiole.h Comportement.h Bestiole.cpp
	g++ -Wall -std=c++11  -c Bestiole.cpp -I .

Membre.o : Membre.h DBestiole.h Milieu.h Membre.cpp
	g++ -Wall -std=c++11 -c Membre.cpp -I .

Camouflages.o : Camouflages.h Milieu.h DBestiole.h Membre.h Camouflages.cpp
	g++ -Wall -std=c++11 -c Camouflages.cpp -I .

Nageoire.o : Nageoire.h Milieu.h DBestiole.h Membre.h Nageoire.cpp
	g++ -Wall -std=c++11 -c Nageoire.cpp -I .

Carapace.o : Carapace.h Milieu.h DBestiole.h Membre.h Carapace.cpp
	g++ -Wall -std=c++11 -c Carapace.cpp -I .
	
DBestiole.o : DBestiole.h DBestiole.cpp
	g++ -Wall -std=c++11  -c DBestiole.cpp -I .

Milieu.o : Milieu.h DBestiole.h Milieu.cpp
	g++ -Wall -std=c++11  -c Milieu.cpp -I .

Capteur.o : Capteur.h Milieu.h DBestiole.h Membre.h Capteur.cpp
	g++ -Wall -std=c++11 -c Capteur.cpp -I .

Oreilles.o : Oreilles.h Milieu.h DBestiole.h Membre.h Capteur.h Oreilles.cpp
	g++ -Wall -std=c++11 -c Oreilles.cpp -I .

Yeux.o : Yeux.h Milieu.h DBestiole.h Membre.h Capteur.h Yeux.cpp
	g++ -Wall -std=c++11 -c Yeux.cpp -I .

Factory.o : Factory.h Milieu.h DBestiole.h Membre.h Bestiole.h Capteur.h Yeux.h Oreilles.h Nageoire.h Camouflages.h Carapace.h Comportement.h Factory.cpp
	g++ -Wall -std=c++11 -c Factory.cpp -I .

Comportement.o: Comportement.h Milieu.h DBestiole.h
	g++ -Wall -std=c++11 -c Comportement.cpp -I .
	
author:
	echo "\nAUTHORS: GROUPE 4 (Rouge) - Projet  * Mehdi Hajjam - Wadia Ferjani - Anass Benfathallah - Julien Bénard"

info:
	echo "\n\n\n\nVeuillez lancer le programme avec ./main\n\n\n"

clean:
	rm -rf *.o;

clean-all: clean
	rm -rf main;




