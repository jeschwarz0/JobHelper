/* 
 * File:   Position.cpp
 * Author: Jesse Schwarz
 * 
 * Created on January 15, 2018, 7:22 PM
 */
#include <string>
#include <ostream>
#include "Position.h"

namespace Positions {

    //      Constructors

    Position::Position() {
        pAnalyzer = 0;
    }

    Position::Position(char* EmpName, char* JobTitle, char* Loc, char* Email, unsigned UJID)
    : UJobID(UJID) {
        pAnalyzer = 0;
        // do nothing else
    }

    Position::Position(const Position& orig) {
        this->UJobID = orig.UJobID;
        this->pAnalyzer = orig.pAnalyzer != 0 ? orig.pAnalyzer : 0;
    }

    Position::~Position() {
        // Delete Analyzer if exists
        if (pAnalyzer != 0) {
            delete pAnalyzer;
            pAnalyzer = 0;
        }
        //Blank UJobID
        UJobID = 0;
    }

    bool Position::operator<(Position& Other) {
        return this->UJobID < Other.UJobID;
    }

    bool Position::operator==(Position& Other) {
        return
                UJobID == Other.UJobID;
    }

    bool Position::toStream(std::ostream& output, const OutputFormat FORMAT) {
        switch (FORMAT) {
            case Standard:default:
            //#Standard toString#
                printStandard(output);
            
                break;
            case Fancy:case FancyNoAnalyzer:
            // #Fancy toString#
                printFancy(output, FORMAT != FancyNoAnalyzer);
            
                break;
        }// End Switch
        return output.good();
    }


    //      Getters

    Analyzer::PositionAnalyzer* Position::Analyzer() {
        if (pAnalyzer == 0) {
            pAnalyzer = new Analyzer::PositionAnalyzer(
                GetDescription(), GetJobTitle(), GetEmployer(),GetEmployerEmail());
        }
        return pAnalyzer;
    }
    
    const bool sv(std::string value) {// $Sane Value$
        return value.length() > 0 && value.compare("null") != 0;
    }
}// End Namespace