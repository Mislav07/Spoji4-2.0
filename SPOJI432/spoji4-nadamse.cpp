#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

using namespace std;

const int RED = 6;
const int STUPAC = 7;
int ploca[RED][STUPAC];

void ocistiTerminal()
{
    cout << "\033[2J\033[1;1H";
}


void printanje_ploce() // https://stackoverflow.com/questions/22290174/connect-four-game-board-in-c
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
            if(ploca[i][j] == 0)
                cout << "   |";
            else if (ploca [i][j] == 1)
                cout << " X |";
            else
                cout << " 0 |";
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

bool provjera_PunaPloca(int ploca[RED][STUPAC])
{
    for (int j = 0; j < STUPAC; j++)
    {
        if (ploca[0][j] == 0)
        {
            return false; // ako ima prostora ploca nije puna
        }
    }
    return true; // ako nema prostora ploca je puna
}

bool provjera_Pobjednik(int ploca[RED][STUPAC], char zeton)
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
    // dijagonalno od lijevo dole prema desno gore
    for (int i = 0; i < RED - 3; i++)
    {
        for (int j = 0; j < STUPAC - 3; j++)
        {
            if (ploca[i][j] == zeton && ploca[i + 1][j + 1] == zeton && ploca[i + 2][j + 2] == zeton && ploca[i + 3][j + 3] == zeton)
            {
                return true;
            }
        }
    }
    // dijagonalno od lijevo gore prema desno dole
    for (int i = 0; i < RED; i++)
    {
        for (int j = 0; j < STUPAC - 3; j++)
        {
            if (ploca[i][j] == zeton && ploca[i - 1][j + 1] == zeton && ploca[i - 2][j + 2] == zeton && ploca[i - 3][j + 3] == zeton)
            {
                return true;
            }
        }
    }
    return false;
}

void upisImena(string &igrac1, string &igrac2)
{
    cout << "Unesite ime 1. igraca: ";
    getline(cin, igrac1);

    cout << "Unesite ime 2. igraca: ";
    getline(cin, igrac2);
}

int odabirStupca(int ploca[RED][STUPAC])
{
    int stupac;
    while (true)
    {
        cout << "Odaberite stupac od 0-6 gdje zelite ubaciti zeton!" << endl;
        cin >> stupac;

        if (stupac >= 0 && stupac < STUPAC && ploca[0][stupac] == 0)
        {
            return stupac;
        }
        cout << "Odabrali ste stupac koji se ne nalazi na ploci ili je stupac pun. Molim pokusajte ponovno!" << endl;
    }
}

bool ubaciZeton(int ploca[RED][STUPAC], char zeton, int stupac)
{
    for (int i = RED - 1; i >= 0; i--) // krece od najnizeg reda , zeton pada pa trebamo prvo slobodno mjesto
    {
        if (ploca[i][stupac] == 0) // je li stupac prazan?
        {
            ploca[i][stupac] = zeton; // ako je prazan se ubacuje zeton
            return true;
        }
    }
    return false; // ako je stupac pun vraca false
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
            string igrac1, igrac2;
            upisImena(igrac1, igrac2);

            for (int i = 0; i < RED; i++)
            {
                for (int j = 0; j < STUPAC; j++)
                {
                    ploca[i][j] = 0;
                }
            }
            int trenutniIgrac = 1;
            char zeton;

            while (true)
            {
                //clearScreen();
                ocistiTerminal();
                printanje_ploce();

                zeton = (trenutniIgrac == 1) ? 1 : 2;
                cout << (trenutniIgrac == 1 ? igrac1 : igrac2) << " je na potezu. Njegov zeton je: " << (zeton == 1 ? 'X' : 'O') << endl;

                int stupac = odabirStupca(ploca);
                ubaciZeton(ploca, zeton, stupac);

                if (provjera_Pobjednik(ploca, zeton))
                {
                    //clearScreen();
                    ocistiTerminal();
                    printanje_ploce();
                    cout << (trenutniIgrac == 1 ? igrac1 : igrac2) << " je pobjedio!" << endl;
                    break;
                }
                if (provjera_PunaPloca(ploca))
                {
                    //clearScreen();
                    ocistiTerminal();
                    printanje_ploce();
                    cout << "Ploca je popunjena! Nerjeseno!! " << endl;
                    break;
                }
                trenutniIgrac = (trenutniIgrac == 1) ? 2 : 1;
            }

            string odgovor;
            cout << "Zelite li igrati ponovo? (da/ne): ";
            cin >> odgovor;
            if(odgovor != "da" && odgovor != "Da" && odgovor != "DA")
            {
                break;
            }
        }

        if (izbor == 2)
        {
            cout << "Leaderboard jos nije gotov!"; // uzima imena i bodove iz tekstualne datoteke/binarne
        }
        if (izbor == 3)
        {
            break;
        }
        else 
        {
            cout << "Odabrali ste izbor koji ne postoji! Molim unesite validan izbor! " << endl;
        }
    }
    return 0;
}