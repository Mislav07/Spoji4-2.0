#include <stdio.h>

#define STUPAC 6
#define RED 7

int ploca[STUPAC][RED];
int igrac;
int gotova_igra = 0;

void printanje_ploce()
{
    printf("\n");
    for (int i = 0; i < STUPAC; i++)
    {
        printf("|");
        for (int j = 0; j < RED; j++)
        {
            if (ploca[i][j] == 0)
                printf("  ");
            else if (ploca[i][j] == 1)
                printf("X ");
            else if (ploca[i][j] == 2)
                printf("O ");
        }
        printf("|\n");
    }
    printf("----------------\n");
    printf(" 1 2 3 4 5 6 7\n");
}

int unesi_potez(int red, int vrijednost)
{
    if (red < 0 || red > RED)
    {
        printf("Red nije tocan, unesit red izmedu 1 i 7!\n");
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
    printf("Stupac je popunjen, odaberite drugi!\n");
    return 0;
}
int provjera()
// po horizontali
{
    for (int i = 0; i < STUPAC; i++)
    {
        for (int j = 0; j < RED - 3; j++) //-3 zbog toga jer provjeravamo za 4
            if (ploca[i][j] != 0 && ploca[i][j] == ploca[i][j + 1] && ploca[i][j] == ploca[i][j + 2] && ploca[i][j] == ploca[i][j + 3])
            {
                return ploca[i][j];
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

    // po dijagonali(od lijevo prema desno)
    for (int i = 0; i < STUPAC - 3; i++)
    {
        for (int j = 0; j < RED - 3; j++)
        {
            if (ploca[i][j] != 0 && ploca[i][j] == ploca[i + 1][j + 1] && ploca[i][j] == ploca[i + 2][j + 2] && ploca[i][j] == ploca[i + 3][j + 3])
            {
                return ploca[i][j];
            }
        }
    }

    // po dijagonali(od desno prema lijevo)
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

int main()
{
    int izbor;

    printf("███████ ██████   ██████       ██ ██     ██   ██ \n");
    printf("██      ██   ██ ██    ██      ██ ██     ██   ██ \n");
    printf("███████ ██████  ██    ██      ██ ██     ███████ \n");
    printf("     ██ ██      ██    ██ ██   ██ ██          ██ \n");
    printf("███████ ██       ██████   █████  ██          ██ \n");
    while (1)
    {
        printf("\n");
        printf("1. Zapocni igru: igrac protiv igraca!\n");
        printf("\n");
        printf("2. Zapocni igru: igrac protiv racunala!\n");
        printf("\n");
        printf("3. Izlaz iz igre!\n");
        printf("\n");
        printf("Molim unesite broj izbornika:\n");
        scanf("%d", &izbor);

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

            while (!gotova_igra)
            {
                int red;
                printf("Igrac %d, unesite redak(1-7):", igrac);
                scanf("%d", &red);

                if (unesi_potez(red, igrac))
                {
                    // system clr
                    system("clear");
                    printanje_ploce();
                    int pobjednik = provjera();
                    if (pobjednik != 0)
                    {
                        printf("Pobjednik je igrac %c!\n", (pobjednik == 1) ? '1' : '2');
                        gotova_igra = 1;
                    }
                    else if (igrac == 1)
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
        else if (izbor == 2)
            printf("Trenutno nije moguce igrati igrac protiv racunala!\n");
        else if (izbor == 3)
        {
            printf("Izlazak iz igre");
            break;
        }
        else
        {
            printf("Molim unesite broj izmedu 1 i 3");
        }
    }
    return 0;
}