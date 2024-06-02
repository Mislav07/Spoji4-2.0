#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

const int RED = 6;
const int STUPAC = 7;

int igrac = 0;
int gotova_igra = 0;
int ploca[RED][STUPAC];

void printanje_ploce2(int ploca[RED][STUPAC]) // https://stackoverflow.com/questions/22290174/connect-four-game-board-in-c
{
    for (int i = 0; i < RED; i++)
    {
        cout << "+";
        for (int j = 0; j < STUPAC; j++)
        {
            cout << "---+";
        }
        cout << endl;
        cout << "|";
        for (int j = 0; j < STUPAC; j++)
        {
            cout << "   |";
        }
        cout << endl;
    }
    cout << "+";
    for (int j = 0; j < STUPAC; j++)
    {
        cout << "---+";
    }
    cout << endl;
}

bool provjera_PuniStupac(int ploca[RED][STUPAC], int stupac) //gleda prvo polje stupca, ako nije 0 onda je pun
{
    return ploca[0][stupac] != 0;
}

bool postaviKruzic(int ploca[RED][STUPAC], int stupac, int kruzic)
{
    for (int i = RED - 1; i >= 0; i++)
    {
        if(ploca [i][stupac] == 0)
        {
            ploca[i][stupac] = kruzic;
            return true;
        }
    }
    return false;
}

int main()
{
    int izbor;
    cout << "███████╗██████╗  ██████╗      ██╗██╗    ██╗  ██╗    ██████╗     ██████╗ " << endl;
    cout << "██╔════╝██╔══██╗██╔═══██╗     ██║██║    ██║  ██║    ╚════██╗   ██╔═████╗" << endl;
    cout << "███████╗██████╔╝██║   ██║     ██║██║    ███████║     █████╔╝   ██║██╔██║ " << endl;
    cout << "╚════██║██╔═══╝ ██║   ██║██   ██║██║    ╚════██║    ██╔═══╝    ████╔╝██║" << endl;
    cout << "███████║██║     ╚██████╔╝╚█████╔╝██║         ██║    ███████╗██╗╚██████╔" << endl;
    cout << "╚══════╝╚═╝      ╚═════╝  ╚════╝ ╚═╝         ╚═╝    ╚══════╝╚═╝ ╚═════╝" << endl;

    while (1)
    {
        cout << "1. Zapocnite igru! " << endl;
        cout << "2. Ispis pobijeda (leaderboard) " << endl;
        cout << "3. Izadite iz igre! " << endl;
        cin >> izbor;
        cin.ignore();

        if (izbor == 1)
        {
            for (int i = 0; i < RED; i++)
            {
                for (int j = 0; j < STUPAC; j++)
                {
                }
            }
        }
        return 0;
    }
}