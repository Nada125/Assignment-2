#ifndef ASSIGNMENT_2_BIGREAL_H
#define ASSIGNMENT_2_BIGREAL_H

#include <iostream>
#include <string>
using namespace std;

class BigReal {
private:
    string integer, fraction;
    char n_sign;
    bool isNegative;
    int decimalPlace;
    bool isValidReal (string realNumber);
public:
    BigReal();
    BigReal (double realNumber = 0.0); // constructor add double value
    BigReal (string realNumber); // constructor add string value
    BigReal (const BigReal& other); // Copy constructor
    BigReal& operator= (BigReal& other); // Assignment operator
// Depending on how you store data, default can be enough
    void setNum (string realNumber);
    int size();
    int sign();
    BigReal operator+ (BigReal other); // + operator for summation
    BigReal operator- (BigReal& other); // - operator for subtraction
    bool operator< (BigReal anotherReal);
    bool operator> (BigReal anotherReal);
    bool operator== (BigReal anotherReal);
    friend ostream& operator << (ostream& out, BigReal num); // friend function to print
};


#endif //ASSIGNMENT_2_BIGREAL_H
