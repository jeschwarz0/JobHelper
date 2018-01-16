/* 
 * File:   autoCL.cpp
 * Author: Jesse Schwarz
 * 
 * Created on January 15, 2018, 7:22 PM
 */

#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include "autoCL.h"
using namespace std;

namespace autoCL {

    cltype manualGetType(cltype rec) {
        cout << "What type would you like:\n"
                << none << "='EXIT'\n" <<
                (rec == 1 ? "(R)" : "") << Default << "=Default\n";
        char c;
        cin >> c;
        cin.clear();
        cin.ignore();
        return (c == 'r' || c == 'R') ? rec : (cltype) atoi(&c);
    }
    //TODO: Fix this

    string getString(const char* IDENTIFIER, const string& REC) {
        const bool USEREC = REC != "NA" && REC != "NYI";
        cout << "Please enter the " << IDENTIFIER <<
                (USEREC ? ",[r]" : "") << (USEREC ? REC : "") << ": ";
        string rv;
        getline(cin, rv);
        return !rv.empty()&&(rv.at(0) == 'r' || rv.at(0) == 'R') && REC != "NA" ? REC : rv;
    }

    void strReplace(string& haystack, const string find, const string replace) {
        for (size_t offset = haystack.find(find); offset != string::npos; offset = haystack.find(find)) {
            haystack.erase(offset, find.size());
            haystack.insert(offset, replace);
        }
    }

    std::string getCoverLetter(cltype t, const string POSITION, const string COMPANY) {
        string rawrval = "!!!Not Implemented!!!";//TODO: Implement from file system
        strReplace(rawrval, "<position>", POSITION);
        strReplace(rawrval, "<employer>", COMPANY);
        return rawrval;
    }
}