//
//  Brettlogik.hpp
//  Muehle
//
//  Created by Phil on 30.05.22.
//

#ifndef Brettlogik_hpp
#define Brettlogik_hpp
#include<string>
#include<sstream>
#include<iostream>
#include <thread>
#include <chrono>

#define SPACE ' '
#define ROW 7
#define COLUMN 13
#define BLACK 'B'
#define WHITE 'W'

class Spieler {
public:
    enum Spielphase { Setzphase = 0, Zugphase, Sprungphase, Spielende };
    enum endstatus{Gewonnen=0,Verloren,Unentschieden};


    private:
    int SpielSteineAnzahl;
    int SpielsteineMax=9;
    
    Spielphase aktuellePhase;
    endstatus ergebnis=Unentschieden;
    std::string name;
    Spieler* nextSpieler;
public:
    Spieler(std::string neuerName = "defaultName");
    
    std::string getName();
    void setName(std::string);

    void setAktullePhase(Spielphase);
    Spielphase getAktuellePhase();

    void setNextSpieler(Spieler&);
    Spieler* getNextSpieler();

    void setSpielsteineMax();
    int getSpielsteineMax();

    endstatus getEndstatus();
    void setEndstatus(Spieler::endstatus);

    int  getSpielSteinAnzahl();
    void setSpielSteinAnzahl(int);
    

};


class punkt {
private:
    int x;
    int y;
public:
    punkt(int x_new = -1, int y_new = -1);
    int getX();
    int getY();
    void BrettToArrayKoord(std::string);
    bool isPointValid();
};


class Brett {
private:
    Spieler Sp1;
    Spieler Sp2;
    Spieler* aktuellerSpieler = &Sp1;
    
    
     char Board[ROW][COLUMN] = {
    {'o','-','-','-','-','-','o','-','-','-','-','-','o'},
    {'|',SPACE,'o','-','-','-','o','-','-','-','o',SPACE,'|'},
    {'|',SPACE,'|',SPACE,'o','-','o','-','o',SPACE,'|',SPACE,'|'},
    {'o','-','o','-','o',SPACE,SPACE,SPACE,'o','-','o','-','o'},
    {'|',SPACE,'|',SPACE,'o','-','o','-','o',SPACE,'|',SPACE,'|'},
    {'|',SPACE,'o','-','-','-','o','-','-','-','o',SPACE,'|'},
    {'o','-','-','-','-','-','o','-','-','-','-','-','o'}
    };

public:
    Brett(std::string,std::string);
    void entferneSteine();
    void SetzeStein(punkt);
    bool Zugmoeglich(punkt, punkt);// �bergabeparameter auf Punkt ge�ndert
    bool Zugmoeglich(punkt, punkt, int);
    punkt SteinSetzbar();
    bool MuehleBesteht(punkt)const;
    void verschiebeStein();
    void springeStein();
    bool unentschieden();
    bool zugunfaehig();

    //getter und setter

    Spieler& getaktuellerSpieler();
    void setnextaktuellerSpieler();

    // um die Funktionalit�t zupr�fen

    void printBrett() ;

    void loescheBrett();

};

#endif /* Brettlogik_hpp */
