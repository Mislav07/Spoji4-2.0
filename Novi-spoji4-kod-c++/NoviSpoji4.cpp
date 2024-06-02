#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int RED = 6;
const int STUPAC = 7;

void printanje_ploce(const vector<vector<char>> &ploca) // https://stackoverflow.com/questions/22290174/connect-four-game-board-in-c
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

bool provjera(const vector<vector<char>> &ploca, char zeton)
{
    // horizontalno
    for (int i = 0; i < RED; i++)
    {
        for (int j = 0; j < STUPAC - 3; j++)
        {
            if (ploca[i][j] == zeton && ploca[i][j + 1] == zeton && ploca[i][j + 2] == zeton && ploca[i][j + 3] == zeton)
            {
                return true;
            }
        }
    }
    // vertikalno
    for (int i = 0; i < RED - 3; i++)
    {
        for (int j = 0; j < STUPAC; j++)
        {
            if (ploca[i][j] == zeton && ploca[i + 1][j] == zeton && ploca[i + 2][j] == zeton && ploca[i + 3][j] == zeton)
            {
                return true;
            }
        }
    }
    // dijagonalno od lijevo dolje do desno gore
    for (int i = 3; i < RED; i++)
    {
        for (int j = 0; j < STUPAC - 3; j++)
        {
            if (ploca[i][j] == zeton && ploca[i - 1][j + 1] == zeton && ploca[i - 2][j + 2] == zeton && ploca[i - 3][j + 3] == zeton)
            {
                return true;
            }
        }
    }
    // dijagonalno od lijevo gore do desno dolje
    for (int i = 0; i < RED - 3; i++)
    {
        for (int j = 3; j < STUPAC; j++)
        {
            if (ploca[i][j] == zeton && ploca[i + 1][j + 1] == zeton && ploca[i + 2][j + 2] == zeton && ploca[i + 3][j + 3] == zeton)
            {
                return true;
            }
        }
    }
    return false;
}

bool punaPloca(const vector<vector<char>> &ploca)
{
    for (int i = 0; i < RED; i++)
    {
        for (int j = 0; j < STUPAC; j++)
        {
            if (ploca[i][j] == ' ')
            {
                return false;
            }
        }
    }
    return true;
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
        cout << "1. Zapocnite igru: igrac protiv igraca! " << endl;
        cout << "2. Ispis pobjeda po igracima. " << endl;
        cout << "3. Izadite iz igrice! " << endl;
        cin >> izbor;
        cin.ignore();

        if (izbor == 1)
        {
            vector<vector<char>> ploca(RED, vector<char>(STUPAC, ' '));
            string igrac1, igrac2;

            cout << "Unesite ime prvog igraca: ";
            getline(cin, igrac1);

            cout << "Unesite ime drugog igraca: ";
            getline(cin, igrac2);

            char trenutniIgrac = 'X';
            bool igraTraje = true;

            while (igraTraje)
            {
                printanje_ploce(ploca);
                int odabraniStupac;
                cout << "Na potezu je igrac " << (trenutniIgrac == 'X' ? igrac1 : igrac2) << ", unesite broj stupca od 0-6! "; //
                cin >> odabraniStupac;

                if (odabraniStupac < 0 || odabraniStupac >= STUPAC)
                {
                    cout << "Neispravan unos! Pokusajte ponovno. Molim unesite stupac od 0 - 6! " << endl;
                }

                bool dobarPotez = false;
                for (int i = RED - 1; i >= 0; i--)
                {
                    if(ploca[i][odabraniStupac] == ' ')
                    {
                        ploca[i][odabraniStupac] = trenutniIgrac;
                        dobarPotez = true;
                        break;
                    }
                }
                if(!dobarPotez)
                {
                    cout << "Stupac je pun! Molim unesite drugi stupac.";

                }
                if(provjera(ploca, trenutniIgrac))
                {
                    printanje_ploce(ploca);
                    cout << "Pobjednik je " << (trenutniIgrac == 'X' ? igrac1 : igrac2) << "!" << endl;
                    igraTraje = false;
                }
                else if(punaPloca(ploca))
                {
                    printanje_ploce(ploca);
                    cout << "Ploca je puna, nema vise slobodnih mjesta. Nerijeseno! " << endl;
                    igraTraje = false;
                }
                trenutniIgrac = (trenutniIgrac == 'X' ? 'O' : 'X');
            }
        }
        else if(izbor == 2)
        {
            cout << "Odabrali ste leaderboard. Trenutno nije dostupno!";
        }
        else if(izbor == 3)
        {
            cout << "Izlazak iz igre!" << endl;
            break;
        }
        else
        {
            cout << "Unijeli ste izbor koji nije ponuden! Molim odaberite od 1-3. ";
        }
        
    }
    return 0;
}
