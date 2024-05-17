#include <iostream>
#include <string>
#include <fstream>

using namespace std;

#define STUPAC 6
#define RED 7

int ploca[STUPAC][RED];
int igrac;
int gotova_igra = 0;

void printanje_ploce()
{
    cout << "\n";
    for (int i = 0; i < STUPAC; i++)
    {
        cout << " | ";
        for (int j = 0; j < RED; j++)
        {
            if (ploca[i][j] == 0)
            {
                cout << " ";
            }
            else if (ploca[i][j] == 1)
            {
                cout << "x ";
            }
            else if (ploca[i][j] == 2)
            {
                cout << "O ";
            }
        }
        cout << " |" << endl;
    }
    cout << "----------------\n";
    cout << "1 2 3 4 5 6 7\n";
}

int unesi_potez(int red, int vrijednost)
{
    if (red < 0 || red > RED)
    {
        cout << "Red nije tocan, unesite red izmedu 1 i 7!" << endl;
        return 0;
    }
    for (int i = STUPAC - 1; i >= 0; i--)
    {
        if (ploca[i][red - 1] == 0)
        {
            ploca[i][red - 1] = vrijednost;
            return 1;
        }
    }
    cout << "Stupac je popunjen, odaberite drugi!" << endl;
    return 0;
}

int provjera()
// po horizontali
{
    for (int i = 0; i < STUPAC; i++)
    {
        for (int j = 0; j < RED - 3; j++)
        {
            if (ploca[i][j] != 0 && ploca[i][j] == ploca[i][j + 1] && ploca[i][j + 2] && ploca[i][j + 3])
            {
                return ploca[i][j];
            }
        }
    }
    // po vertikali
    for (int i = 0; i < STUPAC - 3; i++)
    {
        for (int j = 0; j < RED; j++)
        {
            if (ploca[i][j] != 0 && ploca[i][j] == ploca[i + 1][j] && ploca[i][j] == ploca[i + 2][j] && ploca[i][j] == ploca[i + 3][j])
            {
                return ploca[i][j];
            }
        }
    }
    // po dijagonali (od lijevo prema desno)
    for (int i = 0; i < STUPAC - 3; i++)
    {
        for (int j = 3; i < RED; j++)
        {
            if (ploca[i][j] != 0 && ploca[i][j] == ploca[i + 1][j - 1] && ploca[i][j] == ploca[i + 2][j + 2] && ploca[i][j] == ploca[i + 3][j + 3])
            {
                return ploca[i][j];
            }
        }
    }
    // po dijagonali (od desno prema lijevo)
    for (int i = 0; i < STUPAC - 3; i++)
    {
        for (int j = 3; j < RED; j++)
        {
            if (ploca[i][j] != 0 && ploca[i][j] == ploca[i + 1][j - 1] && ploca[i][j] == ploca[i + 2][j - 2] && ploca[i][j] == ploca[i + 3][j - 3])
            {
                return ploca[i][j];
            }
        }
    }
    return 0;
}
// napraviti sort za leaderboard
int main()
{
    int izbor;
    cout << "███████ ██████   ██████       ██ ██     ██   ██ " << endl;
    cout << "██      ██   ██ ██    ██      ██ ██     ██   ██ " << endl;
    cout << "███████ ██████  ██    ██      ██ ██     ███████ " << endl;
    cout << "     ██ ██      ██    ██ ██   ██ ██          ██ " << endl;
    cout << "███████ ██       ██████   █████  ██          ██ " << endl;

    while (1)
    {
        cout << endl;
        cout << "1. Zapocni igru: igrac protiv igraca! " << endl;
        cout << endl;
        cout << "2. Zapocni igru: igrac protiv racunala! " << endl;
        cout << endl;
        cout << "3. Izlaz iz igre! " << endl;
        cout << endl;
        cout << "Molim unesite broj iz izbornika: " << endl;
        cin >> izbor;

        if (izbor == 1)
        {
            for (int i = 0; i < STUPAC; i++)
            {
                for (int j = 0; j < RED; j++)
                {
                    ploca[i][j] = 0;
                }
            }
            printanje_ploce();
            igrac = 1;
            gotova_igra = 0;
            int n_igrac = 0;

            while (!gotova_igra)
            {
                int red;
                cin >> n_igrac;
                cout << "Igrac" << n_igrac << "unesite redak (1-7): " << igrac;
                cin >> red;

                if (unesi_potez(red, igrac))
                {
                    system("clear");
                    printanje_ploce();
                    int pobjednik = provjera();
                    if (pobjednik != 0)
                    {
                        cout << "Pobjednik je igrac " << n_igrac << endl;
                        gotova_igra = 1;
                    }
                    // provjeri kako unosimo igrace i kako ih ispisat
                }
            }
        }
        else if (izbor == 2)
        {
            cout << "Trenutno nije moguce igrati protiv racunala!" << endl;
        }
        else if (izbor == 3)
        {
            cout << "Izlazak iz igre!";
            break;
        }
        else
        {
            cout << "Molim unesite broj izmedu 1 i 3";
        }
    }
    return 0;
}