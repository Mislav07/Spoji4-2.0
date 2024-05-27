#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int izbor;
#define RED 6
#define STUPAC 7

int ploca[RED][STUPAC];
int igrac = 0;
int zavrsetak_igre = 0;

void printanje_ploce2(int ploca[][RED]) // https://stackoverflow.com/questions/22290174/connect-four-game-board-in-c
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

int unesi_potez(int stupac, int vrijednost)
{
    if(stupac < 0 ||stupac > STUPAC)
    {
        cout << "Netocan stupac, unesite stupac izmedu 1-7";
        return 0;
    }
    for (int i = RED - 1; i >= 0; i--)
    {
        if(ploca[i][stupac-1]==0)
        {
            ploca[i][stupac - 1] = vrijednost;
            return 1;
        }
    }
    cout << "Red je popunjen, odaberite neki drugi! " << endl;
    return 0;
}
bool provjera()
{
    // horizontalno
    for (int i = 0; i < RED; i++)
    {
        for (int j = 0; j < STUPAC - 3; j++)
        {
            if (ploca[i][j] == igrac && ploca[i][j + 1] == igrac && ploca[i][j + 2] == igrac && ploca[i][j + 3] == igrac)
            {
                return true;
            }
        }
    }
    // vertikalno
    for (int i = 0; i < RED; i++)
    {
        for (int j = 0; j < STUPAC - 3; j++)
        {
            if (ploca[i][j] == igrac && ploca[i + 1][j] == igrac && ploca[i + 2][j] == igrac && ploca[i + 3][j] == igrac)
            {
                return true;
            }
        }
    }
    // dijagonalno lijevo na desno (\)
    for (int i = 0; i < RED - 3; i++)
    {
        for (int j = 0; j < STUPAC - 3; j++)
        {
            if (ploca[i][j] == igrac && ploca[i + 1][j + 1] == igrac && ploca[i + 2][j + 2] == igrac && ploca[i + 3][j + 3] == igrac)
            {
                return true;
            }
        }
    }
    // dijagonalno desno na lijevo (/)
    for (int i = 3; i < RED; i++)
    {
        for (int j = 3; j < STUPAC; j++)
        {
            if (ploca[i][j] == igrac && ploca[i - 1][j - 1] == igrac && ploca[i - 2][j - 2] == igrac && ploca[i - 3][j - 3] == igrac)
            {
                return true;
            }
        }
    }
    return false;
}

int main()
{
    int ploca[STUPAC][RED] = {{0}};
    int izbor; // https://www.asciiart.eu/text-to-ascii-art
    cout << "███████╗██████╗  ██████╗      ██╗██╗    ██╗  ██╗    ██████╗     ██████╗ " << endl;
    cout << "██╔════╝██╔══██╗██╔═══██╗     ██║██║    ██║  ██║    ╚════██╗   ██╔═████╗" << endl;
    cout << "███████╗██████╔╝██║   ██║     ██║██║    ███████║     █████╔╝   ██║██╔██║ " << endl;
    cout << "╚════██║██╔═══╝ ██║   ██║██   ██║██║    ╚════██║    ██╔═══╝    ████╔╝██║" << endl;
    cout << "███████║██║     ╚██████╔╝╚█████╔╝██║         ██║    ███████╗██╗╚██████╔" << endl;
    cout << "╚══════╝╚═╝      ╚═════╝  ╚════╝ ╚═╝         ╚═╝    ╚══════╝╚═╝ ╚═════╝" << endl;

    while (1)
    {
        cout << "1. Zapocnite igru! " << endl;
        cout << "2. Ispis pobijeda. " << endl;
        cout << "3. Izlazak iz igre! " << endl;
        cout << "Molimo unesite broj iz izbornika! " << endl;
        cin >> izbor;

        if (izbor == 1)
        {
            for (int i = 0; i < RED; i++)
            {
                for (int j = 0; j < STUPAC; j++)
                {
                    ploca[i][j] = 0;
                }
            }
            printanje_ploce2(ploca);
            igrac = 1;
            zavrsetak_igre = 0;
            while (!zavrsetak_igre)
            {
                int stupac;
                cout << "Igrac " << igrac << " unesite red 1-7 " << endl;
                cin >> stupac;
                if(unesi_potez(stupac, igrac))
                {
                    system("cls");
                    printanje_ploce2;
                    int pobjednik = provjera();
                    if(pobjednik != false)
                    {
                        cout << "Pobjednik je igrac " << igrac << endl, (pobjednik == true) ? '1' : '2';
                        zavrsetak_igre = true;
                    }
                    else if(igrac == 1)
                    {
                        igrac = 2;
                    }
                    else
                    {
                        igrac = 1;
                    }
                }
                
            }
        }
    }
}