
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include "Bunny.cpp"
using namespace std;

// Double Linked List for storing Bunny objects
class BunnyList{

public:

    // data
    Bunny *head, *tail;
    int bunnyID; // number assigned to one bunny
    int bunnyNr; // total number of bunnys
    int bunnyNrRad; // radioactive bunnys
    int infected; // total number of infections

    // sex and color stats
    int bunnyNrMale;
    int bunnyNrFemale;

    int bunnyNrWhite;
    int bunnyNrBrown;
    int bunnyNrBlack;
    int bunnyNrSpotted;

    ofstream file;

    // constructor
    BunnyList(){

        head = NULL;
        tail = NULL;
        bunnyID = 1;
        bunnyNr = 0;
        bunnyNrRad = 0;
        infected = 0;

        bunnyNrMale = 0;
        bunnyNrFemale = 0;

        bunnyNrWhite = 0;
        bunnyNrBrown = 0;
        bunnyNrBlack = 0;
        bunnyNrSpotted = 0;


        file.open("stats_turn_events.txt");

        // create first 5 Bunnys
        for(int i=0; i<5; i++){
            addBunny(rand() % 4);
        }

    }

    // destructor
    ~BunnyList(){
        file.close();
    }


    void addBunny(int colorNr){

        // create Bunny object + report to stats
        Bunny *tmp = new Bunny(bunnyID, colorNr);
        file<<"Bunny "<<tmp->name<<" was born\n";

        bunnyID++;
        bunnyNr++;

        if(tmp->sex){
            bunnyNrMale++;
        }else{
            bunnyNrFemale++;
        }

        switch(colorNr){
        case 0:
            bunnyNrWhite++;
            break;
        case 1:
            bunnyNrBrown++;
            break;
        case 2:
            bunnyNrBlack++;
            break;
        case 3:
            bunnyNrSpotted++;
            break;
        }

        if(tmp->radioactive == true){
            bunnyNrRad++;
        }

        // add to linked list
        tmp->next = NULL;
        tmp->prev = tail;

        if(head == NULL){
            head = tmp;
            tail = tmp;
        }else{
            tail->next = tmp;
            tail = tmp;
        }

    }

    void deleteBunny(Bunny *index){

        // report to stats
        file<<"Bunny "<<index->name<<" died\n";
        bunnyNr--;

        if(index->radioactive == true)
            bunnyNrRad--;

        if(index->sex){
            bunnyNrMale--;
        }else{
            bunnyNrFemale--;
        }

        switch(index->color){
        case 0:
            bunnyNrWhite--;
            break;
        case 1:
            bunnyNrBrown--;
            break;
        case 2:
            bunnyNrBlack--;
            break;
        case 3:
            bunnyNrSpotted--;
            break;
        }

        // delete from linked list
        if(index == head){
            head = index->next;
            index->~Bunny();

        }else if(index == tail){
            tail = index->prev;
            tail->next = NULL;
            index->~Bunny();

        }else{
            index->prev->next = index->next;
            index->next->prev = index->prev;
            index->~Bunny();
        }

    }


    void takeTurn(){

        // age one year
        Bunny *index = head;
        while(index != NULL){
            index->age++;
            index = index->next;
        }

        // breed new Bunnys
        index = head;
        while(index != NULL){
            // check for male 2+ years old
            if(index->sex == 0 && index->age > 2 && index->radioactive == false){
                // reset index pointer, check for females 2+ years and their color
                index = head;
                while(index != NULL){
                    if(index->sex == 1 && index->age > 2 && index->radioactive == false){
                        // add new Bunny with same color as mother
                        addBunny(index->color);
                    }
                    index = index->next;
                }
                break;
            }
            index = index->next;
        }

        checkAge();

        if(bunnyNr - bunnyNrRad > 0){
            radiationInfection();
        }

    }

    void checkAge(){
        // loop through list and delete Bunnies with 10+ years
        // radioactive Bunnies die at age 5
        Bunny *index = head;
        while(index != NULL){

            if(index->age > 10 && index->radioactive == false)
                deleteBunny(index);

            if(index->age > 5 && index->radioactive == true)
                deleteBunny(index);

            index = index->next;

        }

    }

    void radiationInfection(){
        // number of radioactive Bunnys create number of (possible) infections
        // NOTE: the more infected Bunnys in the colony, the less chance of a healthy Bunny being infected
        int infections = bunnyNrRad;
        int n;
        int rnd;
        Bunny *index;

        for(int i=0; i<infections; i++){
            // reset and repeat process
            index = head;
            n = 0;
            rnd = rand() % bunnyNr;

            // find random Bunny to infect
            while(index != NULL){
                if(n == rnd){
                    if(index->radioactive == false){
                        index->radioactive = true;
                        bunnyNrRad++;
                        infected++;
                        file<<"Bunny "<<index->name<<" irradiated!\n";
                        break;
                    }else{
                        rnd++;
                    }
                }
                n++;
                index = index->next;
            }
        }
    }

    void foodShortage(){
        // kill half the population randomly
        file<<"FOOD SHORTAGE!\n";

        int casualties = bunnyNr/2;
        int rnd;
        int dead = 0;
        Bunny *index;
        // pick random bunny to kill each time for half the population
        for(int i=0; i<casualties; i++){
            rnd = rand() % bunnyNr;
            index = head;
            for(int j=0; j<rnd; j++)
                index = index->next;

            deleteBunny(index);
            dead++;
        }

        file<<"["<<dead<<" bunnies dead in food shortage]\n";
    }





};


