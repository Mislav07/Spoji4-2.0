#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

const int RED = 6;
const int STUPAC = 7;
int ploca[RED][STUPAC];

void ocistiTerminal()
{
    cout << "\033[2J\033[1;1H";
}

bool imePostoji(const vector<string> &imena, const string &ime) // chatgpt
{
    return find(imena.begin(), imena.end(), ime) != imena.end();
}

void BrojPokretaBrojac(int brojPokretanja)
{
    ofstream datoteka("broj_pokretanja.bin", ios::binary);
    if (datoteka.is_open())
    {
        datoteka.write(reinterpret_cast<char *>(&brojPokretanja), sizeof(brojPokretanja));
        datoteka.close();
    }
    else
    {
        cout << "Nije moguce otvoriti datoteku za pisanje!" << endl;
    }
}

int procitajBrojPokretanja()
{
    ifstream datoteka("broj_pokretanja.bin", ios::binary);
    int brojPokretanja = 0;
    if (datoteka.is_open())
    {
        datoteka.read(reinterpret_cast<char *>(&brojPokretanja), sizeof(brojPokretanja));
        datoteka.close();
    }
    else
    {
        cout << "Nije moguce otvoriti datoteku za citanje!" << endl;
    }
    return brojPokretanja;
}

void upisImena(string &igrac1, string &igrac2)
{
    fstream datoteka;
    datoteka.open("igraci.txt", ios::in);
    vector<string> imena;
    string ime;
    int bodovi;

    if (datoteka.is_open())
    {
        while (datoteka >> ime >> bodovi)
        {
            imena.push_back(ime);
        }
        datoteka.close();
    }
    else
    {
        cout << "Datoteka se ne moze otvoriti! " << endl;
    }

    // provjera imena prvog igraca
    while (true)
    {
        cout << "Unesite ime 1. igraca: " << endl;
        getline(cin, igrac1);
        if (!imePostoji(imena, igrac1))
        {
            break;
        }
        cout << "Ovo ime vec postoji. Molim unesite drugo ili ga malo promijenite! " << endl;
    }

    // drugi igrac
    while (true)
    {
        cout << "Unesite ime 2. igraca: " << endl;
        getline(cin, igrac2);
        if (!imePostoji(imena, igrac2))
        {
            break;
        }
        cout << "Ovo ime vec postoji. Molim unesite drugo ili ga malo promijenite! " << endl;
    }

    datoteka.open("igraci.txt", ios::app);
    if (datoteka.is_open())
    {
        datoteka << igrac1 << " 0" << endl;
        datoteka << igrac2 << " 0" << endl;
        datoteka.close();
    }
    else
    {
        cout << "Datoteka se ne moze otvoriti! " << endl;
    }
}

void ispisIgraca()
{
    fstream datoteka("igraci.txt");
    string ime;
    int bodovi;

    if (datoteka.is_open())
    {
        cout << "Imena igraca koji su igrali Spoji4 2.0: " << endl;
        while (datoteka >> ime >> bodovi)
        {
            cout << "Ime igraca: " << ime << " bodovi igraca: " << bodovi << endl;
        }
        datoteka.close();
    }
    else
    {
        cout << "Datoteka se ne moze otvoriti! ";
    }
}

void updateScore(const string &ime) // chatgpt
{
    fstream datoteka("igraci.txt");
    vector<pair<string, int>> igraci;
    string imeTemp;
    int bodovi;

    if (datoteka.is_open())
    {
        while (datoteka >> imeTemp >> bodovi)
        {
            if (imeTemp == ime)
            {
                bodovi++;
            }
            igraci.push_back(make_pair(imeTemp, bodovi));
        }
        datoteka.close();
    }
    else
    {
        cout << "Datoteka se ne moze otvoriti! " << endl;
    }

    datoteka.open("igraci.txt", ios::out | ios::trunc);
    if (datoteka.is_open())
    {
        for (const auto &igrac : igraci)
        {
            datoteka << igrac.first << " " << igrac.second << endl;
        }
        datoteka.close();
    }
    else
    {
        cout << "Datoteka se ne moze otvoriti! " << endl;
    }
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
            if (ploca[i][j] == 0)
                cout << "   |";
            else if (ploca[i][j] == 1)
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

int odabirStupca(int ploca[RED][STUPAC])
{
    int stupac;
    while (true)
    {
        cout << "Odaberite stupac od 1-7 gdje zelite ubaciti zeton!" << endl;
        cin >> stupac;
        stupac -= 1;
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

void igra()
{
    int brojPokretanja = procitajBrojPokretanja();
    brojPokretanja++;
    BrojPokretaBrojac(brojPokretanja);

    string igrac1, igrac2;
    upisImena(igrac1, igrac2);

    while (true)
    {
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
            // clearScreen();
            ocistiTerminal();
            printanje_ploce();

            zeton = (trenutniIgrac == 1) ? 1 : 2;
            cout << (trenutniIgrac == 1 ? igrac1 : igrac2) << " je na potezu. Njegov zeton je: " << (zeton == 1 ? 'X' : 'O') << endl;

            int stupac = odabirStupca(ploca);
            ubaciZeton(ploca, zeton, stupac);

            if (provjera_Pobjednik(ploca, zeton))
            {
                // clearScreen();
                ocistiTerminal();
                printanje_ploce();
                cout << (trenutniIgrac == 1 ? igrac1 : igrac2) << " je pobjedio! Osvojili ste 1 bod!" << endl;
                updateScore(trenutniIgrac == 1 ? igrac1 : igrac2);
                break;
            }
            if (provjera_PunaPloca(ploca))
            {
                // clearScreen();
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
        cin.ignore();
        if (odgovor != "da" && odgovor != "Da" && odgovor != "DA")
        {
            // igra();
            ocistiTerminal();
            break;
        }
    }
}

int main()
{
    ocistiTerminal();
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
        cout << "3. Ispis broja pokretanja igre. " << endl;
        cout << "4. Izadite iz igrice! " << endl;
        cin >> izbor;
        cin.ignore();

        if (izbor == 1)
        {
            cout << "Zapoceli ste igru!" << endl;
            igra();
        }

        else if (izbor == 2)
        {
            ocistiTerminal();
            ispisIgraca();
        }
        else if (izbor == 3)
        {
            ocistiTerminal();
            int brojPokretanja = procitajBrojPokretanja();
            cout << "Igra je pokrenuta ukupno " << brojPokretanja << " puta." << endl;
        }
        else if (izbor == 4)
        {
            cout << "Odabrali ste izlazak iz igrice! Doviđenja! " << endl;
            break;
        }
        else
        {
            cout << "Odabrali ste izbor koji ne postoji! Molim unesite validan izbor! " << endl;
        }
    }
    return 0;
}