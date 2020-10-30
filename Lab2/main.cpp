#include <iostream>
#include <string>
#include <thread>
#include <unistd.h>
#include <mutex>
#include <semaphore.h>
using namespace std;

void creerCoupe();
void creerPorte();
void creerTable();
void creerBague();
void creerChandelier();

bool Or = false, Fer = false, Bois = false, Metal = false, Diamants = false;
int CoupeDeVin, Porte, Table, Bague, Chandelier;

int main()
{
    bool quitter = false;
    int choix;
    
    do {
		thread t1(creerCoupe);
        thread t2(creerPorte);
        thread t3(creerTable);
        thread t4(creerBague);
        thread t5(creerChandelier);

        t1.join();
        t2.join();
        t3.join();
        t4.join();
        t5.join();

        if(CoupeDeVin >= 300 && Porte >= 300 && Table >= 300 && Bague >= 300 && Chandelier >= 300)
            quitter = true;
	} while (!quitter);
    cout << "Programme terminé sans accroc";
    
}

void creerCoupe()
{
    sem_t semOr;
    sem_init(&semOr, 0, Or);
    sem_wait(&semOr);
    sem_t semFer;
    sem_init(&semFer, 0, Fer);
    sem_wait(&semFer);

    sleep(0.25);
    sem_post(&semOr);
    sleep(0.25);
    sem_post(&semFer);
    CoupeDeVin++;
}
void creerPorte()
{
    sem_t semBois;
    sem_init(&semBois, 0, Bois);
    sem_wait(&semBois);
    sem_t semOr;
    sem_init(&semOr, 0, Or);
    sem_wait(&semOr);

    sleep(1.2);
    sem_post(&semBois);
    sleep(1.2);
    sem_post(&semOr);
    Porte++;
}
void creerTable()
{
    sem_t semMetal;
    sem_init(&semMetal, 0, Metal);
    sem_wait(&semMetal);
    sem_t semBois;
    sem_init(&semBois, 0, Bois);
    sem_wait(&semBois);

    sleep(1);
    sem_post(&semMetal);
    sleep(1);
    sem_post(&semBois);
    Table++;
}
void creerBague()
{
    sem_t semDiamants;
    sem_init(&semDiamants, 0, Diamants);
    sem_wait(&semDiamants);
    sem_t semMetal;
    sem_init(&semMetal, 0, Metal);
    sem_wait(&semMetal);

    sleep(0.75);
    sem_post(&semDiamants);
    sleep(0.75);
    sem_post(&semMetal);
    Bague++;
}
void creerChandelier()
{
    sem_t semFer;
    sem_init(&semFer, 0, Fer);
    sem_wait(&semFer);
    sem_t semDiamants;
    sem_init(&semDiamants, 0, Diamants);
    sem_wait(&semDiamants);

    sleep(0.5);
    sem_post(&semFer);
    sleep(0.5);
    sem_post(&semDiamants);
    Chandelier++;
}