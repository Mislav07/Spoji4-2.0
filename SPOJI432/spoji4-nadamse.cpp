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

void ocistiTerminal() // link stackoverflow
{
    cout << "\033[2J\033[1;1H";
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

bool ulogirajIgraca(string &ime)
{
    fstream datoteka;
    datoteka.open("C:\\Users\\Mislav\\OneDrive\\Dokumenti\\GitHub\\Spoji4-2.0\\SPOJI432\\igraci.txt", ios::in);
    vector<string> imena;
    string imeTemp;
    int bodovi;
    bool found = false;

    if (datoteka.is_open())
    {
        while (datoteka >> imeTemp >> bodovi)
        {
            imena.push_back(imeTemp);
            if (imeTemp == ime)
            {
                found = true;
            }
        }
        datoteka.close();
    }
    else
    {
        cout << "Datoteka se ne moze otvoriti!" << endl;
    }

    if (!found)
    {
        datoteka.open("C:\\Users\\Mislav\\OneDrive\\Dokumenti\\GitHub\\Spoji4-2.0\\SPOJI432\\igraci.txt", ios::app);
        if (datoteka.is_open())
        {
            datoteka << ime << " 0" << endl;
            datoteka.close();
        }
        else
        {
            cout << "Datoteka se ne moze otvoriti!" << endl;
        }
    }
    return found;
}

void ispisIgraca()
{
    fstream datoteka("C:\\Users\\Mislav\\OneDrive\\Dokumenti\\GitHub\\Spoji4-2.0\\SPOJI432\\igraci.txt");
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
    fstream datoteka("C:\\Users\\Mislav\\OneDrive\\Dokumenti\\GitHub\\Spoji4-2.0\\SPOJI432\\igraci.txt");
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

    datoteka.open("C:\\Users\\Mislav\\OneDrive\\Dokumenti\\GitHub\\Spoji4-2.0\\SPOJI432\\igraci.txt", ios::out | ios::trunc);
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

void ubaciPotez(int ploca[RED][STUPAC], char zeton, int stupac)
{
    for (int i = RED - 1; i >= 0; i--)
    {
        if (ploca[i][stupac] == 0)
        {
            ploca[i][stupac] = zeton;
            break;
        }
    }
}

void spremiIgru()
{
    fstream datoteka("saveIgrice.bin", ios::binary | ios::out);
    datoteka.write(reinterpret_cast<char *>(ploca), sizeof(ploca));
    datoteka.close();
    cout << "Igra je spremljena! " << endl;
}

void ucitajIgru()
{
    fstream datoteka("saveIgrice.bin", ios::binary | ios::in);
    datoteka.read(reinterpret_cast<char *>(ploca), sizeof(ploca));
    datoteka.close();
    cout << "Igra je ucitana! " << endl;
}

void igra(bool ucitaj_ime = true)
{
    int brojPokretanja = procitajBrojPokretanja();
    brojPokretanja++;
    BrojPokretaBrojac(brojPokretanja);

    string igrac1, igrac2;

    if(ucitaj_ime)
    {
    cout << "Unesite ime prvog igraca: " << endl;
    cin >> igrac1;
    cout << "Unesite ime drugog igraca: " << endl;
    cin >> igrac2;

    ulogirajIgraca(igrac1);
    ulogirajIgraca(igrac2);
    }

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
            ocistiTerminal();
            printanje_ploce();

            zeton = (trenutniIgrac == 1) ? 1 : 2;
            cout << (trenutniIgrac == 1 ? igrac1 : igrac2) << " je na potezu. Njegov zeton je: " << (zeton == 1 ? 'X' : 'O') << endl;

            int stupac = odabirStupca(ploca);
            ubaciZeton(ploca, zeton, stupac);

            if (provjera_Pobjednik(ploca, zeton))
            {
                ocistiTerminal();
                printanje_ploce();
                cout << (trenutniIgrac == 1 ? igrac1 : igrac2) << " je pobjedio! Osvojili ste 1 bod!" << endl;
                updateScore(trenutniIgrac == 1 ? igrac1 : igrac2);
                break;
            }
            if (provjera_PunaPloca(ploca))
            {
                ocistiTerminal();
                printanje_ploce();
                cout << "Ploca je popunjena! Nerjeseno!! " << endl;
                break;
            }
            trenutniIgrac = (trenutniIgrac == 1) ? 2 : 1;

            string odgovor;
            cout << "Zelite li spremiti igru (da/ne)? " << endl;
            cin >> odgovor;
            if (odgovor == "da" || odgovor == "Da" || odgovor == "DA")
            {
                spremiIgru();
                break;
            }
        }

        string odgovor;
        cout << "Zelite li igrati ponovo? (da/ne): ";
        cin >> odgovor;
        cin.ignore();
        if (odgovor != "da" && odgovor != "Da" && odgovor != "DA")
        {
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
        cout << "4. Spremite igricu! " << endl;
        cout << "5. Ucitajte igricu! " << endl;
        cout << "6. Izadite iz igrice! " << endl;
        cin >> izbor;
        cin.ignore();

        if (izbor == 1)
        {
            cout << "Zapoceli ste igru!" << endl;
            label:
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
            ocistiTerminal();
            spremiIgru();
        }
        else if (izbor == 5)
        {
            ocistiTerminal();
            ucitajIgru();
            printanje_ploce();
            igra(false);
            //goto label;
        }
        else if (izbor == 6)
        {
            cout << "Odabrali ste izlazak iz igrice! Doviđenja! " << endl;
            break;
        }
        else
            cout << "Odabrali ste izbor koji ne postoji! Molim unesite validan izbor! " << endl;
    }
    return 0;
}