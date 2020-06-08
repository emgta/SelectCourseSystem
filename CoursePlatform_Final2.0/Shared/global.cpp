//
//  global.cpp
//  Results Management System
//
//

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <limits>

#include "global.hpp"

void process_error(std::invalid_argument err, char *err_info) {
    using namespace std;

    strcpy(err_info, err.what());
}
