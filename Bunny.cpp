
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;


const string M_NAMES[6] = {
    "Joe",
    "Pete",
    "Boris",
    "Torkel",
    "Heinmann",
    "Chang-Mei"
};

const string F_NAMES[6] = {
    "Becky",
    "Maria",
    "Lucia",
    "Lana",
    "Adriana",
    "Chang-Maya"
};


class Bunny{

public:

    // data
    int idTag;
    enum Sex {male, female};
    enum Color {white, brown, black, spotted};
    Sex sex;
    Color color;
    int age;
    string name;
    bool radioactive;

    // pointers
    Bunny *next;
    Bunny *prev;

    // constructor
    Bunny(int id, int colorNr){

        idTag = id;

        if(rand() % 2){
            sex = male;
        }else{
            sex = female;
        }

        switch(colorNr){
        case 0:
            color = white;
            break;
        case 1:
            color = brown;
            break;
        case 2:
            color = black;
            break;
        case 3:
            color = spotted;
            break;
        }

        age = 0;

        if(sex == male){
            name = M_NAMES[rand() % 6];
        }else{
            name = F_NAMES[rand() % 6];
        }

        // 0.2% chance of being born radioactive
        if(!(rand() % 500)){
            radioactive = true;
        }else{
            radioactive = false;
        }

        //cout<<"Bunny added"<<endl;

    }

    // destructor
    ~Bunny(){}

};
