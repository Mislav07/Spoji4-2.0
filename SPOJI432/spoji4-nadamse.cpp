#include <iostream>
#include <string>
#include <fstream>

using namespace std;

const int RED = 6;
const int STUPAC = 7;

void printanje_ploce(int ploca[RED][STUPAC]) // https://stackoverflow.com/questions/22290174/connect-four-game-board-in-c
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

bool provjera_PunaPloca(char ploca[RED][STUPAC])
{
    for (int j = 0; j < STUPAC; j++)
    {
        if (ploca[0][j] = ' ')
        {
            return false; // ako ima prostora ploca nije puna
        }
    }
    return true; // ako nema prostora ploca je puna
}

bool provjera_Pobjednik(char ploca[RED][STUPAC], char zeton)
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
    for (int i = 0; i < RED - 3; i++)
    {
        for (int j = 0; j < STUPAC; j++)
        {
            if (ploca[i][j] == zeton && ploca[i + 1][j - 1] == zeton && ploca[i + 2][j - 2] == zeton && ploca[i + 3][j - 3] == zeton)
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

int odabirStupca(char ploca[RED][STUPAC])
{
    int stupac;
    while (true)
    {
        cout << "Odaberite stupac od 0-6 gdje zelite ubaciti zeton!" << endl;
        cin >> stupac;

        if (stupac >= 0 && stupac < STUPAC && ploca[0][stupac] == ' ')
        {
            return stupac;
        }
        cout << "Odabrali ste stupac koji se ne nalazi na ploci ili je stupac pun. Molim pokusajte ponovno!";
    }
}

bool ubaciZeton(char ploca[RED][STUPAC], char zeton, int stupac)
{
    for (int i = RED - 1; i >= 0; i--) // krece od najnizeg reda , zeton pada pa trebamo prvo slobodno mjesto
    {
        if (ploca[i][stupac] == ' ') // je li stupac prazan?
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
            while (true)
            {
                printanje_ploce(ploca);

                cout << "Na potezu je " << trenutniIgrac << ". Vas zeton je: " << trenutniZeton << endl;

                int stupac = odabir_stupca;
            }

        if (izbor == 2)
        {
            cout << "Leaderboard jos nije gotov!";
        }
        if (izbor == 3)
        {
            break;
        }
        else
        {
            cout << "Odabrali se izbor koji ne postoji! Molim unesite validan izbor! ";
        }
    }
    return 0;
    }
}