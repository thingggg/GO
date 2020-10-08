#include <string>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include "historique.cpp"
using namespace std;




int countHisto();
int offsetHistorique();
int ajouterHistorique(pid_t pid,char* arg[]);
int ajouterHistorique(pid_t pid,string arr[]);
int afficherHistorique(int nbrLignes);
