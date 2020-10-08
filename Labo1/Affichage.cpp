#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include "historique.h" //***
using namespace std;


void executeCommand(char* command, char* argument_list[]);

int main()
{
    string input;
    string commande[3];
    string LaCommande;
    bool quitter = false;
    do {
        //Affichage du terminale et le cin, A remplacer 'Terminal' par nos deux noms pour le rendre
        cout << "DionLoquet< "; 
        getline(cin, input);
        
        //Le caractere separant chaque argument
        char delim = ' ';
        string word;
        stringstream ss(input);
        string arr[3];
        int count = 0;
        while(getline(ss,word, delim))
        { 
            if(count==0 || word != arr[count-1])
            {
                arr[count++]=word;
            }
            else
            {
                count++;
            }
            
        }

        //Traitement de la commande, test par rapport au premier "mot" de la commande
        if(arr[0]== "historique"){
            afficherHistorique(8);  //***
        }
        
        else if(arr[0] == "stop")         //Lancer l'historique ou sortir du programme
        {
            quitter = true;
        }
        else if(arr[0] == "cd")           //Commande "cd"
        {
            vector<char> dir(arr[1].begin(), arr[1].end());
            dir.push_back('\0');        //Conversion du chemin voulu en char*
            char * directory = &dir[0];
            ajouterHistorique(getpid(),arr);
            if(chdir(directory) == 0)
                cout << "Changement de répertoire effectué" << endl;
            else cout << "Répertoire introuvable" << endl;
        }
        else if(arr[0] == "cat")        //Commande "cat"
        {
            if(fork() == 0)             //Nouveau processus
            {
                LaCommande = arr[0] + " " + arr[1]; //Recréation de la commande complète
                ajouterHistorique(getpid(),arr);
                execlp( "/bin/sh", "/bin/sh", "-c", LaCommande.c_str(), (char *)NULL ); //Execution de la commande après conversion de la commande en char*
                //execlp( "/bin/sh", "/bin/sh", "-c", "cat file1.txt", (char *)NULL );
            }
            sleep(1);
        }
        else if(arr[0] == "mv")         //Commande "mv"
        {
            if(fork() == 0)             //Noueau processus
            {
                vector<char> argument0(arr[0].begin(), arr[0].end());   //Les vecteurs me permettent de transformer les strings (obtenus en récupérant l'entrée de l'utilisateur) en char, afin de les passer dans l'execvp
                argument0.push_back('\0');
                char* c = &argument0[0]; //Conversion en char*

                vector<char> argument1(arr[1].begin(), arr[1].end()); //idem
                argument1.push_back('\0');
                char *arg1 = &argument1[0];

                vector<char> argument2(arr[2].begin(), arr[2].end()); //idem
                argument2.push_back('\0');
                char *arg2 = &argument2[0];
                
                char *arg_list[] = {c, arg1, arg2, NULL}; //Liste d'argument à envoyer dans le "execvp"
                executeCommand(c, arg_list);
            }
            arr[0] = ""; //On vide les variables pour une autre utilisation
            arr[1] = "";
            arr[2] = "";
        }
        else{                                                   //Traitement de la commande rentrée
            vector<char> chars(arr[0].begin(), arr[0].end());   //Les vecteurs me permettent de transformer les strings obtenus en récupérant l'entrée de l'utilisateur en char afin de les passer dans l'execvp
            chars.push_back('\0');
            char* c = &chars[0];
            char* command = c;
            char* argument_list[] = {c,NULL,NULL};  //Liste d'argument à envoyer dans le "execvp"

            if(arr[1] != "")
            {
                vector<char> chars2(arr[1].begin(), arr[1].end());
                chars2.push_back('\0');
                char* c2 = &chars2[0];
                char* argument_list2[] = {c,c2,NULL};   //Liste d'argument si 2 options à envoyer dans le "execvp"
                executeCommand(command, argument_list2);
            }
            else
            {
                executeCommand(command, argument_list);
            }
            arr[0] = "";    //On vide les variables pour une autre utilisation
            arr[1] = "";
        }

    } while(!quitter);   //On repete tant que l'utilisateur ne sort pas du programme
}

void executeCommand(char* command, char* argument_list[])
{
    pid_t pid ;                                     //***
    if(fork() == 0){    //Nouveau processus
        
        ajouterHistorique(getpid(), argument_list);     //***
        //int status_code = execvp(command, argument_list);

        if(execvp(command, argument_list) == -1){
            cout<<"Terminated incorrectly\n"<<endl;
        }
        
    }
    sleep(1);
}


