#include <iostream>
#include "BigReal.h"
using namespace std;
int main (){
    BigReal num1 ("1111111111111111111111111111111111");
    BigReal num2 ("-33333333333333333333333333333333333333");
    BigReal sum = num1 + num2;
//    BigReal diff = num1 - num2;
//    cout << num1 << " " << num2 << endl;
    cout << sum;

    if (num1 < num2)
        cout << "num1 is less than num2" << endl;
    else if (num2 > num1)
        cout << "num1 is greater than num2" << endl;
    else
        cout << "They are equal" << endl;
}

