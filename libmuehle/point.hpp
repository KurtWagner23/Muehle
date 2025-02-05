#pragma once

#include <iostream>
#include <sstream>
#include <string>

class Point {
private:
    int x;
    int y;

public:
    Point(int x_new = -1, int y_new = -1);
    int getX(void);
    int getY(void);
    static Point boardToArrayKoord(std::string&);
    bool isPointValid(void);
};