//
//  main.cpp
//  Muehle
//
//  Created by Phil on 30.05.22.
//

#include <iostream>
#include "Brettlogik.hpp"



int main()
{

    Brett Spielbrett("Heinz", "Karl");
    Spielbrett.printBrett();
    int ende = 0;
    while (ende != 1) {
        switch (Spielbrett.getaktuellerSpieler().getAktuellePhase()) {

            case Spieler::Setzphase:
            {
                Spielbrett.loescheBrett();
                Spielbrett.SetzeStein(Spielbrett.SteinSetzbar());
            
            }break;
            case Spieler::Zugphase:
            {
                if (!Spielbrett.zugunfaehig()) {

                    Spielbrett.loescheBrett();


                    int aktuelleAnzahlSteine = Spielbrett.getaktuellerSpieler().getSpielSteinAnzahl();
                    if (aktuelleAnzahlSteine == 3) {

                        Spielbrett.getaktuellerSpieler().setAktullePhase(Spieler::Sprungphase);
                        Spielbrett.loescheBrett();
                        Spielbrett.springeStein();

                    }
                    else {
                        Spielbrett.verschiebeStein();
                    }
                }
            } break;
            case Spieler::Sprungphase:
            {
                Spielbrett.loescheBrett();

                if (Spielbrett.unentschieden()) {
                    Spielbrett.getaktuellerSpieler().setAktullePhase(Spieler::Spielende);
                    Spielbrett.getaktuellerSpieler().getNextSpieler()->setAktullePhase(Spieler::Spielende);

                    std::cout << "unentschieden" << std::endl;


                }
                else if (Spielbrett.zugunfaehig()) {    // ! entfernt

                    std::cout << "zugunfaehig" << std::endl;

                

                    Spielbrett.getaktuellerSpieler().setAktullePhase(Spieler::Spielende);
                    Spielbrett.getaktuellerSpieler().getNextSpieler()->setAktullePhase(Spieler::Spielende);

                    Spielbrett.getaktuellerSpieler().setEndstatus(Spieler::Verloren);
                    Spielbrett.getaktuellerSpieler().getNextSpieler()->setEndstatus(Spieler::Gewonnen);



                }
                else { Spielbrett.springeStein(); }


            } break;
            case Spieler::Spielende:
            {


                int erg= Spielbrett.getaktuellerSpieler().getEndstatus();

                switch (erg) {

                    case Spieler::Gewonnen: {
                        std::cout << "Spieler: " << Spielbrett.getaktuellerSpieler().getName() << " hat gewonnen!!!!!!!!!"<<std::endl;
                        std::cout << "Spieler: " << Spielbrett.getaktuellerSpieler().getNextSpieler()->getName() << " hat verloren" << std::endl;

                    }break;
                    case Spieler::Verloren: {
                        std::cout << "Spieler: " << Spielbrett.getaktuellerSpieler().getNextSpieler()->getName() << " hat gewonnen!!!!!!!!!"<< std::endl;
                        std::cout << "Spieler: " << Spielbrett.getaktuellerSpieler().getName() << " hat verloren" << std::endl;

                    }break;
                    case Spieler::Unentschieden: {

                        std::cout << "Spieler: " << Spielbrett.getaktuellerSpieler().getName()<< " und "<<Spielbrett.getaktuellerSpieler().getNextSpieler()->getName();
                        std::cout << " haben unentschieden gespielt!" << std::endl;

                    }break;
                    default: {
                        exit(-121);
                    }break;

                }

                ende = 1;

            } break;
            default:
            {
                exit(-12321);
            }break;

        }

        Spielbrett.setnextaktuellerSpieler();
        

    }


}






