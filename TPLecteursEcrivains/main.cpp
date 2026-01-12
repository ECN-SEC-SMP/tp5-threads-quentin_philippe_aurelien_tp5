#include <iostream>           
#include <thread>             
#include "Semaphore.hpp"

int ressourcePartagee;

Semaphore sem1(1);
int nbLecteurs = 0;

void lecteur(int numLecteur){
  for (int i = 0; i < 4; i++){
    sem1.P(1);
    nbLecteurs++;
    sem1.V(1);

    std::cout << "Lecteur n° " << numLecteur << " en cours " << endl;
    this_thread::sleep_for(chrono::milliseconds(rand() % 20000) );
    std::cout << "        Valeur lue = " << ressourcePartagee << "  " << endl;

    sem1.P(1);
    nbLecteurs--;
    sem1.V(1);
  }
}

void ecrivain(int numEcrivain){
  int x;
  for (int i = 0; i < 4; i++){
    sem1.P(1);
    if (nbLecteurs == 0){
      std::cout << "Ecrivain n° " << numEcrivain << " en cours " << endl;
      x = ressourcePartagee;
      this_thread::sleep_for(chrono::milliseconds(rand() % 20000) );
      std::cout << "valeur à incrémenter de la ressourcePartagee = " << x << "  " << endl;
      ressourcePartagee = x+1 ;
    }
    sem1.V(1);
  }
}

int main() {
  const int nbr = 8;
  std::thread r[nbr];
  std::thread w[nbr];
  int ressourcePartagee = 0;

  for (int i = 1; i < nbr; i++){
    r[i] = std::thread(lecteur, -i);
    w[i] = std::thread(ecrivain, i);
  }
// Join des threads 
  for (int i = 1; i < nbr; i++) {
  r[i].join(); 
  w[i].join();   
  }
  return 0;
}
