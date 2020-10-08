//Ce fichier contient les fonctions d'historique de ce projet


#pragma once 
#include <string>
#include <iostream>
#include <fstream>
#include <unistd.h>
using namespace std;

// compte le nombre de lignes dans le fichier historique.
// @return cpt
int countHisto(){
    std::ifstream historique;                                   // Variable permettant la lecture du fichier Historique
    std::string ligne;                                          // La fonction getline nécessite une string pour entré le contenu de la ligne
                                                                // je ne m'en sert pas
    int cpt;                                                    // Stocke le nombre de lignes dans le fichier historique.txt

    historique.open("historique.txt");                          //  Ouvre le fichier historique en lecture

    for(cpt = 0; std::getline(historique,ligne); cpt++);        // Lit une ligne jusqu'a ce que la fonction getLine() retourne faux et incremente le compteur.

    historique.close();                                         // Ferme le fichier.

    return cpt;                                                 //retourne le résultat du compteur de lignes
}

// Supprime le première élément du fichier historique.txt
// @return 0
int offsetHistorique(){
    ifstream historique;                                                            // Variable permettant la lecture du fichier Historique
    ofstream temp;                                                                  // Je met le contenu de Historique.txt excluant la première ligne dans ce fichier.
    string ligne;                                                                           

    historique.open("historique.txt");                                              //Ouvre le fichier
    temp.open("tempHistorique.txt", std::ofstream::out | std::ofstream::trunc);
    getline(historique, ligne);
    while(getline(historique, ligne)){
        temp << ligne << endl;
    }
    historique.close();
    temp.close();
     if( remove( "historique.txt" ) != 0 )
        perror( "Erreur lors de la supression de historque.txt" );
    rename("tempHistorique.txt", "historique.txt");
    return 0;
}
//Ajoute la commande spécifié au fichier historique.txt
// @param pid_t pid de la commande
// @param char* arg[] les arguments de la commande 
// @return int
int ajouterHistorique(pid_t pid, char* arg[]){ 
    static int cpt = countHisto();                                                  // compte le nombre de lignes dans le fichier historique. *** à verifier: la variable static est elle compatible avec un fork()?
    string histoText;
    ofstream historique;
    ifstream historiqueLecture;
    if(cpt >= 100){                                                                 //Si le compteur est plus grand que 100 on doit supprimer le plus vieille élément du fichier
        historiqueLecture.open ("historique.txt");                                  //Ouvre le fichier
        while(getline(historiqueLecture, histoText)){
            cpt = 1 + stoi(histoText);                                              //Le compteur deviens la valeur de la première colonne de la dernière ligne.
        }
        historiqueLecture.close();                                                  //ferme le fichier
        offsetHistorique();
    }
    historique.open ("historique.txt", std::ofstream::out | std::ofstream::app);    //  Ouvre le fichier historique en écriture. Met le pointeur d'écriture a la fin du fichier.

    if(!historique){
        cout << "Erreur a l'ouverture du fichier";
        return 0;
    }
    histoText += to_string(cpt++);                                                  // Ajoute le numero de la commande a la fin de la ligne.
    histoText += "\t"; 

    for(int i = 0; arg[i] != NULL; i++){                                            // itère dans le tableau d'arguments
        histoText += arg[i];                                                        // Ajoute à la ligne de l'enregistrement l'argument i dans la string. 
        histoText += " ";                                                          // Ajoute un espace 
    }
    histoText += "\t"; 
    histoText += to_string(pid); 
    historique << histoText << endl ;
    if(!historique){
        cout << "Erreur a l'ecriture du fichier";
        return 0;
    }
    historique.close();                                                             // Ferme le fichier.
    return 1;
}
//Converti string arr[] en char* arr[] et Ajoute la commande spécifié au fichier historique.txt
// @param pid_t pid de la commande
// @param char* arg[] les arguments de la commande 
// @return int
int ajouterHistorique(pid_t pid, string arr[]){ 

    vector<char> argument0(arr[0].begin(), arr[0].end());   //Les vecteurs me permettent de transformer les strings (obtenus en récupérant l'entrée de l'utilisateur) en char, afin de les passer dans l'execvp
    argument0.push_back('\0');
    char* c = &argument0[0]; //Conversion en char*

    vector<char> argument1(arr[1].begin(), arr[1].end()); //idem
    argument1.push_back('\0');
    char *arg1 = &argument1[0];

    vector<char> argument2(arr[2].begin(), arr[2].end()); //idem
    argument2.push_back('\0');
    char *arg2 = &argument2[0];                       // conversion
    char *arg_list[] = {c, arg1, arg2, NULL}; //Liste d'argument à envoyer dans le "execvp"

    return ajouterHistorique(pid, arg_list);
}
// Affiche le contenu du fichier Historique.txt dans le terminal
// @param int nbrLignes combien de lignes vous voulez afficher dans le terminal
int afficherHistorique(int nbrLignes){ 
    int cpt = countHisto(); 
    string histoText;
    ifstream historique;

    historique.open ("historique.txt");    //  Ouvre le fichier historique en écriture. Met le pointeur d'écriture a la fin du fichier.
    if(!historique){
        cout << "Erreur a l'ouverture du fichier";
        return 0;
    }
    for(int i = 0; i < (cpt - nbrLignes); i++)                                            // itère dans l'historique pour placer le pointeur d'écriture à 'nbrLignes' de la fin  
        getline(historique, histoText);
        
    
    while(getline(historique, histoText))
        cout << histoText << endl;
    historique.close();                                                             // Ferme le fichier.
    return 1;
}



