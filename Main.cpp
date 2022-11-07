
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include "BunnyList.cpp"
using namespace std;

// ***** TODO: ******
// Radiation infection rate - play around with two paramenters:
// chance of being born radioactive OR max radioactive age
// radiationInfection function ineffective, but shouldn't affect program


// printing functions
void printList(BunnyList &list, ofstream &file, int turn);
void printStats_Overview(BunnyList &list, ofstream &file, int turn);
void printStats_BunnysBorn(BunnyList &list, ofstream &file, int turn);



// ***MAIN***
int main(){

    cout<<"BUNNY COLONY SIMULATION"<<endl;

    srand(time(NULL));

    // create main object
    BunnyList list;

    // open filestreams
    // (turn events file only written from BunnyList object)
    ofstream listFile;
    ofstream statsOverviewFile;
    ofstream statsBornFile;
    listFile.open("stats_list.txt");
    statsOverviewFile.open("stats_overview.txt");
    statsBornFile.open("stats_born.txt");


    // ***Main part of simulation - take turns until all dead***
    int turn = 0;
    while(true){
        if(list.bunnyNr > 0){
            // turn
            list.takeTurn();
            // print results
            printList(list, listFile, turn);
            printStats_Overview(list, statsOverviewFile, turn);
            printStats_BunnysBorn(list, statsBornFile, turn);

            if(list.bunnyNr > 1000){
                // food shortage event + show in graph
                list.foodShortage();
                printStats_Overview(list, statsOverviewFile, turn);
            }

        }else{
            break;
        }
        turn++;

    }

    cout<<"[Total Bunnys born: "<<list.bunnyID<<"]"<<endl;
    cout<<"[Total radiation infections: "<<list.infected<<"]"<<endl;
    cout<<"[Turns lasted: "<<turn<<"]"<<endl;
    cout<<"See .txt files for more info..."<<endl;

    // close filestreams
    listFile.close();
    statsOverviewFile.close();
    statsBornFile.close();


    return 0;
}

    void printList(BunnyList &list, ofstream &file, int turn){

        file<<"----[turn "<<turn<<"]----\n\n";

        Bunny *index = list.head;

        while(index != NULL){

            file<<" "<<index->idTag;
            file<<"--"<<index->name<<": "<<"\n";
            file<<"[";

            switch(index->color){
                case 0:
                    file<<"white";
                    break;
                case 1:
                    file<<"brown";
                    break;
                case 2:
                    file<<"black";
                    break;
                case 3:
                    file<<"spotted";
                    break;
            }

            file<<", ";

            if(index->sex == 0){
                file<<"male";
            }else if(index->sex == 1){
                file<<"female";
            }

            file<<", ";
            file<<index->age<<" years";

            if(index->radioactive == true){
                file<<", *radioactive*";
            }

            file<<"]\n";

            index = index->next;

        }

        file<<"\n";
        file<<"Total number of Bunnys: "<<list.bunnyNr<<"\n";
        file<<"Radioactive Bunnys: "<<list.bunnyNrRad<<"\n";
        file<<"\n";

    }

    void printStats_Overview(BunnyList &list, ofstream &file, int turn){

        int healthyBunnys = list.bunnyNr - list.bunnyNrRad;

        // display turn
        file<<"turn "<<turn;
        file<<'\n';

        // healthy bunnys
        file<<"Healthy:";
        for(int i=0; i<(healthyBunnys / 5); i++){
            file<<'-';
        }
        file<<':'<<healthyBunnys;
        file<<'\n';

        // radioactive bunnys
        file<<"RadioAc:";
        for(int i=0; i<(list.bunnyNrRad / 5); i++){
            file<<'x';
        }
        file<<':'<<list.bunnyNrRad;
        file<<'\n';

    }

    void printStats_BunnysBorn(BunnyList &list, ofstream &file, int turn){

        // display turn
        file<<"turn "<<turn;
        file<<'\n';

        // sex stats
        file<<"Male:";
        for(int i=0; i<(list.bunnyNrMale / 5); i++){
            file<<'-';
        }
        file<<':'<<list.bunnyNrMale;
        file<<'\n';

        file<<"Female:";
        for(int i=0; i<(list.bunnyNrFemale / 5); i++){
            file<<'-';
        }
        file<<':'<<list.bunnyNrFemale;
        file<<'\n';

        //file<<"--------\n";

        // color stats
        file<<"White:";
        for(int i=0; i<(list.bunnyNrWhite / 5); i++){
            file<<'o';
        }
        file<<':'<<list.bunnyNrWhite;
        file<<'\n';

        file<<"Brown:";
        for(int i=0; i<(list.bunnyNrBrown / 5); i++){
            file<<'.';
        }
        file<<':'<<list.bunnyNrBrown;
        file<<'\n';

        file<<"Black:";
        for(int i=0; i<(list.bunnyNrBlack / 5); i++){
            file<<'*';
        }
        file<<':'<<list.bunnyNrBlack;
        file<<'\n';

        file<<"Spotted:";
        for(int i=0; i<(list.bunnyNrSpotted / 5); i++){
            file<<':';
        }
        file<<':'<<list.bunnyNrSpotted;
        file<<'\n';


        file<<"--------\n";

    }












