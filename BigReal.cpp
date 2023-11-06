#include <string>
#include "BigReal.h"
using namespace std;

// initialize atributes
BigReal::BigReal(){ 
    integer = "0";
    fraction = "";
    n_sign = '+';
    isNegative = false; 

}
// add double value and convert to string
BigReal :: BigReal (double realNumber){
    string realstr = to_string(realNumber);
    setNum(realstr);
}

BigReal :: BigReal (string realNumber){
    setNum (realNumber);
}
BigReal :: BigReal (const BigReal& other){
    integer = other.integer;
    fraction = other.fraction;
    n_sign = other.n_sign;
    isNegative = other.isNegative;
    decimalPlace = other.decimalPlace;
}
bool BigReal::isValidReal(string realNumber){

    // check if the string is empty
    if (realNumber.empty()){
        return false;
    }
    // check if the string contains alphabet
    for (auto x : realNumber){
        if (isalpha(x))
            return false;
    }

    // check if the first char is not sign or digit
    if (realNumber[0] != '+' && realNumber[0] != '-' && !isdigit(realNumber[0]))
        return false;

    // check if there is more than one decimal point
    int count=0;
    for (int i=0;i<realNumber.size();i++) {
        if (realNumber[i] == '.')
            count++;
        if (count > 1)
            return false;
    }
    return true;
}
BigReal& BigReal :: operator= (BigReal& other){
    if (this != &other){
        integer = other.integer;
        n_sign = other.n_sign;
        isNegative = other.isNegative;
        decimalPlace = other.decimalPlace;
    }
    return *this;
}
void BigReal :: setNum (string realNumber){
    if (!isValidReal(realNumber))
        realNumber = '0.0';

    isNegative = (realNumber[0]=='-');
}
int BigReal::size(){
    return integer.size() + fraction.size();
}
int BigReal::sign(){
    if(integer[0] == '-' or integer.empty()){
        return -1;
    }
    return 1;
}

BigReal BigReal::operator+( const BigReal& other) {
    // Check if signs are different, perform subtraction instead
    if (n_sign != other.n_sign) {
        BigReal negatedOther = other;
        negatedOther.n_sign *= -1;
//        return (*this - negatedOther);
    }

    // Determine the larger integer part
    const BigReal& larger = (integer.size() >= other.integer.size()) ? *this : other;
    const BigReal& smaller = (integer.size() < other.integer.size()) ? *this : other;

    // Add the integer parts
    std::string resultInteger;
    int carry = 0;
    int i = larger.integer.size() - 1;
    int j = smaller.integer.size() - 1;

    while (i >= 0) {
        int largerDigit = larger.integer[i] - '0' + carry;

        if (j >= 0) {
            int smallerDigit = smaller.integer[j] - '0';
            largerDigit += smallerDigit;
            j--;
        }

        if (largerDigit > 9) {
            carry = 1;
            largerDigit -= 10;
        } else {
            carry = 0;
        }

        resultInteger = to_string(largerDigit) + resultInteger;
        i--;
    }

    // Add the fraction parts
    std::string resultFraction;
    int k = larger.fraction.size() - 1;
    int l = smaller.fraction.size() - 1;
    carry = 0;

    while (k >= 0 || l >= 0 || carry > 0) {
        int largerDigit = (k >= 0) ? larger.fraction[k] - '0' : 0;
        int smallerDigit = (l >= 0) ? smaller.fraction[l] - '0' : 0;
        int sum = largerDigit + smallerDigit + carry;

        if (sum > 9) {
            carry = 1;
            sum -= 10;
        } else {
            carry = 0;
        }

        resultFraction = to_string(sum) + resultFraction;

        k--;
        l--;
    }

    // Combine the integer and fraction parts
    string result = resultInteger + "." + resultFraction;

    // Add the sign if necessary
    if (n_sign == -1) {
        result = "-" + result;
    }

    return result;
}

//BigReal BigReal::operator-(BigReal& other){
//    // Check if signs are different, perform addition instead
//    if (n_sign != other.n_sign) {
//        BigReal negatedOther = other;
//        negatedOther.n_sign *= -1;
//        return *this + negatedOther;
//    }
//
//    // Determine the larger integer part
//    const std::string& larger = (num1.size() >= num2.size()) ? num1 : num2;
//    const std::string& smaller = (num1.size() < num2.size()) ? num1 : num2;
//
//    // Subtract the integer parts
//    string resultIntegerPart;
//    int carry = 0;
//    int i = larger.size() - 1;
//    int j = smaller.size() - 1;
//
//    while (i >= 0) {
//        int largerDigit = larger[i] - '0' - carry;
//
//        if (j >= 0) {
//            int smallerDigit = smaller[j] - '0';
//
//            if (largerDigit < smallerDigit) {
//                largerDigit += 10;
//                carry = 1;
//            } else {
//                carry = 0;
//            }
//
//            largerDigit -= smallerDigit;
//            j--;
//        } else if (largerDigit < 0) {
//            largerDigit += 10;
//            carry = 1;
//        } else {
//            carry = 0;
//        }
//
//        resultIntegerPart = to_string(largerDigit) + resultIntegerPart;
//        i--;
//    }
//
//    // Create the result string
//    string result = resultIntegerPart;
//
//    // Subtract the fraction parts
//    int k = larger.size();
//    int l = smaller.size();
//
//    while (k > 0 || l > 0) {
//        int largerDigit = (k > 0) ? larger[k - 1] - '0' : 0;
//        int smallerDigit = (l > 0) ? smaller[l - 1] - '0' : 0;
//
//        if (largerDigit < smallerDigit) {
//            largerDigit += 10;
//            carry = 1;
//        } else {
//            carry = 0;
//        }
//
//        largerDigit -= smallerDigit;
//        result = std::to_string(largerDigit) + result;
//
//        k--;
//        l--;
//    }
//
//    // Add the decimal point if necessary
//    if (result.size() > 1) {
//        result.insert(result.size() - 1, ".");
//    }
//
//    return result;
//}
bool BigReal :: operator==(BigReal other)
{
    if (integer == other.integer && fraction == other.fraction)
        return true;
    else
        return false;
}

bool BigReal :: operator>(BigReal other)
{
    string n2 = other.integer;
    string d2 = other.fraction;
    string n1 = this->integer;
    string d1 = this->fraction;
    int y = max(n1.size(), n2.size());
    if (y == n2.size())
    {
        int difference = n2.size() - n1.size();
        string zeros(difference, '0');
        n1 = zeros + n1 ;
    }
    if (y == n1.size())
    {
        int difference = n1.size() - n2.size();
        string zeros(difference, '0');
        n2 =   zeros+n2;
    }
    y = max(d1.size(), d2.size());
    if (y == d2.size())
    {
        int difference = d2.size() - d1.size();
        string zeros(difference, '0');
        d1 = d1+zeros ;
    }
    if (y == d1.size())
    {
        int difference = d1.size() - d2.size();
        string zeros(difference, '0');
        d2 = d2 + zeros;
    }
    string num1 = n1+d1;//822>823
    string num2 = n2+d2;
    for(int i =0; i<num1.size();i++){
        if(num2[i]<num1[i]){
            return true;
        }
        else if(num2[i]>num1[i])
        {
            return false;
        }
        else if(num2[i]==num1[i])
        {
            continue;
        }
    }
    return false;

}

bool  BigReal :: operator<(BigReal other)
{ 
    string n2 = other.integer;
    string d2 = other.fraction;
    string n1 = this->integer;
    string d1 = this->fraction;
    int y = max(n1.size(), n2.size());
    if (y == n2.size())
    {
        int difference = n2.size() - n1.size();
        string zeros(difference, '0');
        n1 = zeros + n1 ;
    }
    if (y == n1.size())
    {
        int difference = n1.size() - n2.size();
        string zeros(difference, '0');
        n2 =   zeros+n2;
    }
    y = max(d1.size(), d2.size());
    if (y == d2.size())
    {
        int difference = d2.size() - d1.size();
        string zeros(difference, '0');
        d1 = d1+zeros ;
    }
    if (y == d1.size())
    {
        int difference = d1.size() - d2.size();
        string zeros(difference, '0');
        d2 = d2 + zeros;
    }
    string num1 = n1+d1;
    string num2 = n2+d2;
    for(int i =0; i<num1.size();i++){
        if(num2[i]>num1[i]){
            return true;
        }
        else if(num2[i]<num1[i])
        {
            return false;
        }
        else if(num2[i]==num1[i])
        {
            continue;
        }
    }
    return false;
}


ostream& operator << (ostream& out, BigReal num){
    if (num.isNegative)
        out << '-';
    out << num.integer;
    if (!num.fraction.empty())
        out << '.' << num.fraction;

    return out;

}

