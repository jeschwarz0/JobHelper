/* 
 * File:   main.cpp
 * Author: Jesse Schwarz
 * 
 * Created on January 15, 2018, 7:22 PM
 */

#define PROGRAM_NAME "jobhelper"

#include "MenuCtl.h"

int main(int argc, char** argv) {
    MenuCtl::sysInit(&argc, argv);
    MenuCtl::process(); // Initialize MenuCtl
    return 0;
}