#include "point.hpp"

Point::Point(int x_new, int y_new) {
    x = x_new;
    y = y_new;
}

int Point::getX() {
    return x;
}
int Point::getY() {
    return y;
}

Point Point::boardToArrayKoord(std::string& koord) {
    int x_new, y_new;
    char dummy;
    std::stringstream inputkoord;

    inputkoord << koord;
    inputkoord >> x_new >> dummy >> y_new;
    int x = 2 * x_new;
    int y = y_new;

    return Point(x, y);
}

bool Point::isPointValid() {
    if (x >= 0 && x <= 12 && y >= 0 && y <= 6) {
        return true;
    }
    return false;
}