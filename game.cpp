#include <iostream>
#include <string>
using namespace std;

char bord[9] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
char pieces[2] = {'O', 'X'};
int beurt = 1;

void drawBord();
void invoerhandel(int plaatsindex);
void beurtStart();
typedef struct
{
    bool einde;
    char PieceIsWinnaar;
} uitkomst;
uitkomst checkField();

int main()
{
    beurtStart();
    return 0;
}

// functie om het bord te tekenen
void drawBord()
{
    cout << bord[0] << " | " << bord[1] << " | " << bord[2] << endl;
    cout << "---------" << endl;
    cout << bord[3] << " | " << bord[4] << " | " << bord[5] << endl;
    cout << "---------" << endl;
    cout << bord[6] << " | " << bord[7] << " | " << bord[8] << endl;
    cout << endl;
}

void beurtStart()
{
    // Teken het bord
    drawBord();
    cout << "Speler " << pieces[beurt % 2] << " is nu aan de beurt" << endl;
    cout << "Op welke plek wil je een \"" << pieces[beurt % 2] << "\" plaatsen? (Voer een getal van 1 - 9 in.)" << endl;

    int invoer = 0;
    cin >> invoer;
    cin.get();
    invoerhandel(invoer);
}

void invoerhandel(int plaatsindex)
{
    // zorg dat de plaatsindex binnen het domein [1, 9] blijft
    if (plaatsindex < 1 || plaatsindex > 9)
    {
        cout << plaatsindex << " is geen geldige invoer. Voer een andere plek in tussen 1 en 9" << endl;
        int invoer = 1;
        cin >> invoer;
        cin.get();
        invoerhandel(invoer);

        return;
    }

    // zorg dat je niet op een plek kan plaatsen waar al iets staat
    if (bord[plaatsindex - 1] != ' ')
    {
        cout << "Deze plek is al bezet door " << bord[plaatsindex - 1] << ". Voer een andere plek in tussen 1 en 9:" << endl;

        int invoer = 1;
        cin >> invoer;
        cin.get();
        invoerhandel(invoer);

        return;
    }

    // zet de keuze van de speler
    bord[plaatsindex - 1] = pieces[beurt % 2];

    // check na iedere beurt het speelveld;
    uitkomst check = checkField();
    if (check.einde)
    {
        if ((bool)(int)check.PieceIsWinnaar)
            cout << check.PieceIsWinnaar << " is de winnaar!" << endl;
        else
            cout << "Er is geen winnaar, het spel is afgelopen" << endl;
        drawBord();
        return;
    }

    // ga door naar de volgende beurt
    beurt++;
    beurtStart();
}

uitkomst checkField()
{
    bool winnaar = false;
    char speler = 0;

    // check horizontaal
    for (int column = 0; column < 3; column++)
    {
        string columnString = "";
        columnString += bord[3 * column];
        columnString += bord[3 * column + 1];
        columnString += bord[3 * column + 2];

        if (columnString == "OOO") // O wint
        {
            winnaar = true;
            speler = 'O';
            return uitkomst{
                winnaar,
                speler,
            };
        }
        else if (columnString == "XXX")
        {
            winnaar = true;
            speler = 'X';
            return uitkomst{
                winnaar,
                speler,
            };
        }
    }

    // check verticaal
    for (int row = 0; row < 3; row++)
    {
        string rowString = "";
        rowString += bord[0 + row];
        rowString += bord[3 + row];
        rowString += bord[6 + row];

        if (rowString == "OOO")
        {
            winnaar = true;
            speler = 'O';
            return uitkomst{
                winnaar,
                speler,
            };
        }
        else if (rowString == "XXX")
        {
            winnaar = true;
            speler = 'X';
            return uitkomst{
                winnaar,
                speler,
            };
        }
    }

    // check diagonaal (linksboven naar rechtsonder)
    if (bord[0] == bord[4] && bord[0] == bord[8] && (bord[0] != ' ' && bord[4] != ' ' && bord[8] != ' '))
    {
        winnaar = true;
        speler = bord[0];
        return uitkomst{
            winnaar,
            speler,
        };
    }

    // check diagonaal (rechtsboven naar linksonder)
    if (bord[2] == bord[4] && bord[2] == bord[6] && (bord[2] != ' ' && bord[4] != ' ' && bord[6] != ' '))
    {
        winnaar = true;
        speler = bord[2];
        return uitkomst{
            winnaar,
            speler,
        };
    }

    // check op welke index er een lege plek zit
    int i = 0;
    while (i < 9)
    {
        if (bord[i] == ' ')
            break;
        i++;
    }

    // 9 valt buiten de matrix, dus dan is het hele bord vol
    if (i > 8)
    {
        return uitkomst{
            true,
            0,
        };
    }

    // standaard uitkomst
    uitkomst stand = uitkomst{
        false,
        0,
    };
    return stand;
}