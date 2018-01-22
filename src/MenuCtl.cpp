/* 
 * File:   MenuCtl.cpp
 * Author: Jesse Schwarz
 * 
 * Created on January 15, 2018, 7:22 PM
 */
#include <fstream>
#include <iostream>
#include <string.h>
#include <list>
#include <stdlib.h>
#include <sstream>

#include "BitLoader.h" // For Bit Definitions
#include "JobApisLoader.h"
#include "JobAPIPosition.h"

using namespace std;
using namespace Positions;
using namespace BitOpts;

namespace MenuCtl {

    /* A Position Pointer */
    typedef Position* PosPtr;

    void sysInit(int* argc, char** argv) {
        JobApisLoader::pathCheck(); // Sync path with system
        loadFlags(argc, argv); // Load the starting flags
    }

    const char* getInputFileName(const char* PFX = "\\|") {
        list<const char*> datfls;
        JobApisLoader::ListDataFiles(datfls);
        char* rval;

        if (datfls.size() > 0) {
            unsigned short in, ctr = 1;
            list<const char*>::iterator iter = datfls.begin();

            while (iter != datfls.end())
                cout << PFX << ctr++ << " " << *iter++ << endl;

            cout << "Please enter a valid file index(0 = exit):";
            cin >> in;
            cin.clear();
            cin.ignore();

            if (in != 0) {
                iter = datfls.begin();
                std::advance(iter, in - 1);
                rval = new char[strlen(*iter) + 1];
                strncpy(rval, *iter, strlen(*iter) + 1);
            } else rval = 0;
        } else rval = 0;
        return rval;
    }

    //******************************************************************************
    //              Data Initializations
    //******************************************************************************

    void shortenList(list<PosPtr>& Source, list<PosPtr>& Remove) {
        if (Remove.empty() || Source.empty())return;
        for (list<PosPtr>::iterator b = Remove.begin(); b != Remove.end(); b++) {
            for (list<PosPtr>::iterator s = Source.begin(); s != Source.end(); s++)
                if ((**s) == (**b)) {
                    delete (*s);
                    s = Source.erase(s);
                    break;
                }
        }
    }

    void init(list<PosPtr>& lRecords) {
        // Load from individual or all files
        if (getFlag(opChooseFile)) {
            const char* fn = getInputFileName(" ");
            if (fn != 0) JobApisLoader::LoadDataFile(fn, lRecords);
            delete[] fn;
        } else {
            lRecords = JobApisLoader::LoadDataDir();
        }
        if (getFlag(opSort))
            lRecords.sort();
    }
    //******************************************************************************
    //              List Operations
    //******************************************************************************    

    void traverse(list<PosPtr>::iterator& iter, unsigned short& current, const unsigned short& MAX, const bool AZ = true) {
        if (AZ && current + 1 < MAX) {
            iter++;
            current++;
        } else if (!AZ && current - 1 >= 0) {
            iter--;
            current--;
        }
    }

    void removeItem(list<PosPtr>& Haystack, list<PosPtr>::iterator& iter, unsigned short& nMax, unsigned short& nIter) {
        delete (*iter); // Delete the referenced item at the beginning
        if (nIter < nMax - 1) {// Delete record, then set i to next item
            iter = Haystack.erase(iter);
        } else { // Delete record, then reset 'i'

            Haystack.erase(iter);
            iter = Haystack.begin();
            nIter = 0;
        }
        nMax--;
    }

    void listDelete(list<PosPtr>& lRecords) {
        while (!lRecords.empty()) {
            delete *lRecords.begin(); // Delete the referenced item at the beginning
            lRecords.pop_front(); // Delete first item
        }
    }

    void listOutput(list<PosPtr>& lRecords) {
        if (lRecords.empty())return;

        for (list <PosPtr> ::iterator it = lRecords.begin(); it != lRecords.end(); it++) {
            if (getFlag(opVerboseList))(*it)->Analyzer();
            (*it)->toStream(cout, getFlag(opVerboseList) ? Fancy : Standard); // Print toString() equivalent
            cout << "\n";
        }
    }

    void menu(list<PosPtr>& lRecords, ostream* ApplicationOutput = &cout) {
        if (lRecords.empty()) {
            cerr << "Warning: No records found!\n";
            return;
        }
        char inp;
        unsigned short mx = lRecords.size(), cur = 0;
        list<PosPtr>::iterator i = lRecords.begin();
        cout << "There are " << mx << " records!\n";
        while (mx > 0) {
            if (getFlag(opVerboseList)) (*i)->Analyzer(); //initialize analyzer for toStream
            (*i)->toStream(cout, getFlag(opVerboseList) ? Fancy : Standard);
            cout << "Please enter a command(h=help):";
            cin >> inp;
            cin.clear();
            cin.ignore();
            switch (inp) {
                case 'n':case 'N':
                    traverse(i, cur, mx, true);
                    break;
                case 'p':case 'P':
                    traverse(i, cur, mx, false);
                    break;
                case 'a':case 'A':// *Apply then remove item
                    (*i)->Analyzer()->apply(*ApplicationOutput, inp == 'a');
                    removeItem(lRecords, i, mx, cur);
                    break;
                case 'b':case 'B':case 'r':case'R':// *remove item
                    removeItem(lRecords, i, mx, cur);
                    break;
                case 'e':case 'E':// *Erase w/out blacklist
                    removeItem(lRecords, i, mx, cur);
                    break;
                case 'm':case 'M':
                    toggleFlag(opVerboseList); //reverse fancy menu
                    break;
                default:case 'h':case 'H':// *Show help
                    cout << "xX = Exit | nN = Next | pP= Previous | a= Apply | A= Apply(AUTO) | bBrR=Blacklist | eE=Erase | mM=Toggle Menu | hH=Help\n";
                    break;
                case 'x':case 'X':// *Exit function
                    return;
            }
            cout << std::endl; // Tack on newline after command //
        }
    }
    //******************************************************************************
    //           MenuCtl(Entry Point)   
    //******************************************************************************   

    void process() {
        list<PosPtr> lPositions;
        init(lPositions);
        if (getFlag(opNoMenu)) {
            listOutput(lPositions);
        } else {//  #Run menu W/Blacklist#
            
            ostream* pCLOut = (getFlag(opWriteToFile) ? new ofstream(strncat(getenv("home"), "coverletters.txt", strlen(getenv("home")) + strlen("coverletters.txt") + 1), ios::out | ios::app) : &cout);
            menu(lPositions, pCLOut); // Show Menu
            if (getFlag(opWriteToFile))// Close output file/cover letters
                (*(ofstream*) pCLOut).close();
            pCLOut = 0;
        }
        // #Delete Positions#
        listDelete(lPositions);
    }// end FN
}// End Namespace
