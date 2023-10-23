//
//  Brettlogik.cpp
//  Muehle
//
//  Created by Phil on 30.05.22.
//

#include "Brettlogik.hpp"



// Funktionen der Spielerklasse

Spieler::Spieler(std::string neuerName) {
    name = neuerName;
    SpielSteineAnzahl = 9;
    aktuellePhase = Setzphase;
}

std::string Spieler::getName() { return name; }
void Spieler::setName(std::string newName) { name = newName; }

void Spieler::setAktullePhase(Spielphase neuePhase) { aktuellePhase = neuePhase; }
Spieler::Spielphase Spieler::getAktuellePhase() { return aktuellePhase; }

void Spieler::setNextSpieler(Spieler& nextSpieler_new) { nextSpieler = &nextSpieler_new; }
Spieler* Spieler::getNextSpieler() { return nextSpieler; }

int Spieler::getSpielSteinAnzahl() { return SpielSteineAnzahl; }
void Spieler::setSpielSteinAnzahl(int newAnzahl) { SpielSteineAnzahl = newAnzahl; }


void Spieler::setSpielsteineMax() { SpielsteineMax-=1; }
int Spieler::getSpielsteineMax() { return SpielsteineMax; }

Spieler::endstatus Spieler:: getEndstatus() { return ergebnis; }
void Spieler:: setEndstatus(Spieler::endstatus erg) { ergebnis = erg; }




// Funktionen f�r den Punkt

punkt::punkt(int x_new, int y_new) {

    x = x_new;
    y = y_new;

}

int punkt::getX() { return x; }
int punkt::getY() { return y; }

void punkt::BrettToArrayKoord(std::string koord) {

    int x_new, y_new;
    char dummy;
    std::stringstream inputkoord;

    inputkoord << koord;
    inputkoord >> x_new >> dummy >> y_new;
    x = 2 * x_new;
    y = y_new;
}

bool punkt::isPointValid()
{

    if (x >= 0 && x <= 12 && y >= 0 && y <= 6) {
        return true;
    }
    return false;

}


// Funktionen des Brettes
Brett::Brett(std::string name_sp1, std::string name_sp2) {

    Sp1.setName(name_sp1);
    Sp2.setName(name_sp2);
    Sp1.setNextSpieler(Sp2);
    Sp2.setNextSpieler(Sp1);


}

void Brett::entferneSteine() {

    loescheBrett();

    punkt arraykoord;
    std::string Koord;
    int gueltigesEntfernen = 0;
    int anzahl = 0;


    std::cout << "Muehle! Bitte entferne einen Stein." << std::endl;
    do {

        std::cin >> Koord;

        arraykoord.BrettToArrayKoord(Koord);
        int x = arraykoord.getX();
        int y = arraykoord.getY();

        if (aktuellerSpieler == &Sp1 && Board[y][x] == BLACK) {

            Board[y][x] = 'o';
            gueltigesEntfernen = 1;
            anzahl = getaktuellerSpieler().getNextSpieler()->getSpielSteinAnzahl();
            getaktuellerSpieler().getNextSpieler()->setSpielSteinAnzahl(anzahl - 1);

            if (getaktuellerSpieler().getNextSpieler()->getSpielSteinAnzahl() == 3) {

                getaktuellerSpieler().getNextSpieler()->setAktullePhase(Spieler::Sprungphase);

            }
            

            if (getaktuellerSpieler().getNextSpieler()->getSpielSteinAnzahl() == 2) {

                getaktuellerSpieler().getNextSpieler()->setAktullePhase(Spieler::Spielende);
                getaktuellerSpieler().getNextSpieler()->setAktullePhase(Spieler::Spielende);

                getaktuellerSpieler().setEndstatus(Spieler::Gewonnen);
                getaktuellerSpieler().getNextSpieler()->setEndstatus(Spieler::Verloren);
            }
        }
        else if (aktuellerSpieler == &Sp2 && Board[y][x] == WHITE) {

            Board[y][x] = 'o';
            gueltigesEntfernen = 1;
            anzahl = getaktuellerSpieler().getNextSpieler()->getSpielSteinAnzahl();
            getaktuellerSpieler().getNextSpieler()->setSpielSteinAnzahl(anzahl - 1);

            if (getaktuellerSpieler().getNextSpieler()->getSpielSteinAnzahl() == 3) {

                getaktuellerSpieler().getNextSpieler()->setAktullePhase(Spieler::Sprungphase);

            }

            if (getaktuellerSpieler().getNextSpieler()->getSpielSteinAnzahl() == 2) {

                getaktuellerSpieler().setAktullePhase(Spieler::Spielende);
                getaktuellerSpieler().getNextSpieler()->setAktullePhase(Spieler::Spielende);

                getaktuellerSpieler().setEndstatus(Spieler::Gewonnen);
                getaktuellerSpieler().getNextSpieler()->setEndstatus(Spieler::Verloren);

            }
        }
        else {
            std::cout << "Ungueltiges entfernen, bitte waehle erneut: ";
            loescheBrett();
        }

    } while (gueltigesEntfernen == 0);

}



void Brett::SetzeStein(punkt koord) {


    if (aktuellerSpieler == &Sp1) {
        Board[koord.getY()][koord.getX()] = WHITE;
    }
    else {

        Board[koord.getY()][koord.getX()] = BLACK;

    }

    loescheBrett();

    int anzahl = 0;
    anzahl = getaktuellerSpieler().getSpielSteinAnzahl();
    --anzahl;
    getaktuellerSpieler().setSpielSteinAnzahl(anzahl);

    if (anzahl == 0) {

        getaktuellerSpieler().setAktullePhase(Spieler::Zugphase);
        int maxsteine = getaktuellerSpieler().getSpielsteineMax();
        getaktuellerSpieler().setSpielSteinAnzahl(maxsteine);

    }

    

    if (MuehleBesteht(koord)) {

        entferneSteine();
        getaktuellerSpieler().getNextSpieler()->setSpielsteineMax();
    }

    loescheBrett();

}

bool Brett::Zugmoeglich(punkt aktuell, punkt ziel) {

    char stein = WHITE;
    if (aktuellerSpieler == &Sp2) {
        stein = BLACK;
    }

    if (ziel.isPointValid() && aktuell.isPointValid() && (Board[aktuell.getY()][aktuell.getX()] == stein)) {
         
        if (Board[ziel.getY()][ziel.getX()] == 'o') {

            if (ziel.getY() == aktuell.getY()) {
                
                int var = ziel.getX() - aktuell.getX();
                if (aktuell.getY() == 0 || aktuell.getY() == 6) {
                    if (var == -6 || var == 6)
                        return true;
                }
                else if (aktuell.getY() == 1 || aktuell.getY() == 5) {
                    if (var == -4 || var == 4)
                        return true;
                }
                else if (aktuell.getY() == 2 || aktuell.getY() == 4 || aktuell.getY() == 3) {
                    if (var == -2 || var == 2)
                        return true;
                }


            }
            else if (ziel.getX() == aktuell.getX()) {
              
                int var = ziel.getY() - aktuell.getY();
                if (aktuell.getX() == 0 || aktuell.getX() == 12) {
                    if (var == -3 || var == 3)
                        return true;
                }
                else if (aktuell.getX() == 2 || aktuell.getX() == 10) {
                    if (var == -2 || var == 2)
                        return true;
                }
                else if (aktuell.getX() == 4 || aktuell.getX() == 8 || aktuell.getX() == 6) {
                    if (var == -1 || var == 1)
                        return true;
                }
            }
            else
                return false;
        }
        else
            return false;
    }


    return false;

}

bool Brett::Zugmoeglich(punkt aktuell, punkt ziel, int i)
{
    if (ziel.isPointValid() && aktuell.isPointValid()) {

        if (Board[ziel.getY()][ziel.getX()] == 'o') {

            return true;
        }

    }
    return false;
}


punkt Brett::SteinSetzbar() {

    bool SteinSetzbar = false;
    
    punkt arraykoord;
    do {
        std::cout << "Bitte Setzposition wie folgend eingeben: x,y:" << std::endl;
        std::cout << "Setzposition: ";
        std::string Koord;
        std::cin >> Koord;

        arraykoord.BrettToArrayKoord(Koord);

        int x = arraykoord.getX();
        int y = arraykoord.getY();

        if ((x >= 0) && (x <= 12) && (y >= 0) && (y <= 6)) {
            if (Board[y][x] == 'o') {
                SteinSetzbar = true;

            }
            else {
                std::cout << "Der Spielstein kann nicht auf die angegebene Position gesetzt werden. Bitte neu eingeben" << std::endl;
                loescheBrett();
            }
        }

    } while (SteinSetzbar == false);

    return arraykoord;

}


bool Brett:: MuehleBesteht(punkt neuPlatzierterStein) const{

    char stein = WHITE;
    if (aktuellerSpieler == &Sp2) {
        stein = BLACK;
    }

    int y = neuPlatzierterStein.getY();


    if (y == 0 || y == 6) {
        if (Board[y][0] == stein && Board[y][2 * 3] == stein && Board[y][2 * 6] == stein)
            return true;
    }
    else if (y == 1 || y == 5) {
        if (Board[y][2 * 1] == stein && Board[y][2 * 3] == stein && Board[y][2 * 5] == stein)
            return true;
    }
    else if (y == 2 || y == 4) {
        if (Board[y][2 * 2] == stein && Board[y][2 * 3] == stein && Board[y][2 * 4] == stein)
            return true;
    }
    else if (y == 3) {
        if ((Board[y][0] == stein && Board[y][2 * 1] == stein && Board[y][2 * 2] == stein) ||
            (Board[y][2 * 4] == stein && Board[y][2 * 5] == stein && Board[y][2 * 6] == stein))
            return true;
    }
  
    int x = neuPlatzierterStein.getX();

    if (x == 0 || x == 2 * 6) {
        if (Board[0][x] == stein && Board[3][x] == stein && Board[6][x] == stein)
            return true;
    }
    else if (x == 2 * 1 || x == 2 * 5) {
        if (Board[1][x] == stein && Board[3][x] == stein && Board[5][x] == stein)
            return true;
    }
    else if (x == 2 * 2 || x == 2 * 4) {
        if (Board[2][x] == stein && Board[3][x] == stein && Board[4][x] == stein)
            return true;
    }
    else if (x == 2 * 3) {
        if ((Board[0][x] == stein && Board[1][x] == stein && Board[2][x] == stein) ||
            (Board[4][x] == stein && Board[5][x] == stein && Board[6][x] == stein))
            return true;
    }

    return false;

}

void Brett::verschiebeStein() {

    punkt ziel, aktuell;
    do {

        loescheBrett();
        std::cout << "Bitte Zugposition wie folgend eingeben: aktuell: x,y ziel: x,y" << std::endl;
        std::cout << "aktuell: ";
        std::string Koord_aktuell;
        std::cin >> Koord_aktuell;
        std::cout << "ziel: ";
        std::string Koord_ziel;
        std::cin >> Koord_ziel;


        aktuell.BrettToArrayKoord(Koord_aktuell);
        ziel.BrettToArrayKoord(Koord_ziel);



    } while (!Zugmoeglich(aktuell, ziel));

    char stein = WHITE;

    Board[aktuell.getY()][aktuell.getX()] = 'o';
    if (aktuellerSpieler == &Sp2)
        stein = BLACK;

    Board[ziel.getY()][ziel.getX()] = stein;

    if (MuehleBesteht(ziel)) {

        entferneSteine();

    }

    loescheBrett();

}

void Brett::springeStein() {

    punkt ziel, aktuell;
    do {
        std::cout << "Bitte Sprungposition wie folgend eingeben: aktuell: x,y ziel: x,y" << std::endl;
        std::cout << "aktuell: ";
        std::string Koord_aktuell;
        std::cin >> Koord_aktuell;
        std::cout << "ziel: ";
        std::string Koord_ziel;
        std::cin >> Koord_ziel;


        aktuell.BrettToArrayKoord(Koord_aktuell);
        ziel.BrettToArrayKoord(Koord_ziel);



    } while (!Zugmoeglich(aktuell, ziel, 42));


    char stein = WHITE;

    if (Board[ziel.getY()][ziel.getX()] == 'o') {

        Board[aktuell.getY()][aktuell.getX()] = 'o';

        if (aktuellerSpieler == &Sp2) {
            stein = BLACK;
        }


        Board[ziel.getY()][ziel.getX()] = stein;
    }

    if (MuehleBesteht(ziel)) {

        entferneSteine();

    }

    loescheBrett();
}

bool Brett::unentschieden()
{
    if (Sp1.getAktuellePhase() == Sp2.getAktuellePhase() && Sp1.getAktuellePhase()==Spieler::Sprungphase) {
        return true;
    }
    return false;
}


bool Brett::zugunfaehig() {

    char stein = WHITE;

    int schrittweite = 1;
    int anzahlfreiernachbarplaetze = 0;
    

    if (aktuellerSpieler == &Sp2) {
        stein = BLACK;
    }

    for (int zeilen = 0; zeilen < ROW; zeilen++) {

        for (int spalten = 0; spalten < COLUMN; spalten += 2) {

            if (Board[zeilen][spalten] == stein) {


                // Norden
                do {

                    if ((zeilen-schrittweite)>=0 && Board[zeilen-schrittweite][spalten] == 'o') {

                        anzahlfreiernachbarplaetze++;
                        break;

                    }
                    else if (Board[zeilen - schrittweite][spalten] == '|') {
                        schrittweite++;
                        continue;

                    }
                    else { break; }

                } while (true);

                schrittweite = 1;

                //Sueden
                do {

                    if ((zeilen + schrittweite)<= 6 && Board[zeilen + schrittweite][spalten] == 'o') {

                        anzahlfreiernachbarplaetze++;
                        break;

                    }
                    else if (Board[zeilen + schrittweite][spalten] == '|') {
                        schrittweite++;
                        continue;

                    }
                    else { break; }

                } while (true);

                schrittweite = 1;
                
                //Westen
                do {

                    if ((spalten - schrittweite) >=0  && Board[zeilen][spalten - schrittweite] == 'o') {

                        anzahlfreiernachbarplaetze++;
                        break;

                    }
                    else if (Board[zeilen][spalten - schrittweite] == '-') {
                        schrittweite++;
                        continue;

                    }
                    else { break; }

                } while (true);

                schrittweite = 1;
                
                //Osten
                do {

                    if ((spalten + schrittweite)<= 12 && Board[zeilen ][spalten + schrittweite] == 'o') {

                        anzahlfreiernachbarplaetze++;
                        break;

                    }
                    else if (Board[zeilen][spalten + schrittweite] == '-') {
                        schrittweite++;
                        continue;

                    }
                    else { break; }

                } while (true);


            }
        }
    }

    if (anzahlfreiernachbarplaetze==0) {
        return true;            // auf true geaendert
    }
    else { return false; }        // auf false geaendert


}




//getter und setter

Spieler& Brett::getaktuellerSpieler() { return *aktuellerSpieler; }

void Brett::setnextaktuellerSpieler() {


    aktuellerSpieler = aktuellerSpieler->getNextSpieler();


}



//Funktionen zum funktionalen Testen auf Shell

void Brett::printBrett()  {

    std::cout << "Spielelogik fuer das Muehle Spiel!"<<std::endl;
    if (getaktuellerSpieler().getAktuellePhase() == Spieler::Setzphase) {
        std::cout << "Setzphase " << std::endl;
    }
    else if (getaktuellerSpieler().getAktuellePhase() == Spieler::Sprungphase) {
        std::cout << "Sprungphase " << std::endl;
    }
    else if (getaktuellerSpieler().getAktuellePhase() == Spieler::Zugphase) {
        std::cout << "Zugphase " << std::endl;
    }

    std::cout << "Spieler1: " << Sp1.getName()<<" Anzahl Steine: "<<Sp1.getSpielSteinAnzahl()<<" Max Anzahl Steine: "<<Sp1.getSpielsteineMax()<<std::endl;
    std::cout << "Spieler2: " << Sp2.getName() << " Anzahl Steine: " << Sp2.getSpielSteinAnzahl() << " Max Anzahl Steine: " << Sp2.getSpielsteineMax() << std::endl;
    std::cout << std::endl;

    std::cout << getaktuellerSpieler().getName() << " ist am Zug" << std::endl << std::endl;
    std::cout << "  0 1 2 3 4 5 6" << std::endl;
    for (int i = 0; i < ROW; ++i)
    {
        std::cout << i << " ";
        for (int j = 0; j < COLUMN; ++j)
        {
            std::cout << Board[i][j];

        }

        std::cout << std::endl;
    }


}


void Brett::loescheBrett() {

    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    system("clear");
    printBrett();

}
