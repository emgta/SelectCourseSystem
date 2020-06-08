#include <iostream>
#include <stdio.h>
#include <limits>

#include "global.hpp"

bool process_error(std::invalid_argument err) {
    using namespace std;

    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cout << err.what() << "\nTry again? Enter y or n" <<endl;
    char c;
    cin >> c;
    if (!cin || c == 'n') return WRONG;
    else return RIGHT;
}