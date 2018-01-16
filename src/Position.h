/* 
 * File:   Position.h
 * Author: Jesse Schwarz
 * 
 * Created on January 15, 2018, 7:22 PM
 */

#ifndef POSITION_H
#define	POSITION_H

#include <iosfwd>// For istream and ostream
#include <string>
#include "PositionAnalyzer.h"

namespace Positions {

    /**
     * The format of output, Currently:
     * Standard --> Flat text w/out lines
     * Fancy --> Formatted text
     * Export --> Export format text(for streams)
     */
    enum OutputFormat {
        Standard, Fancy, FancyNoAnalyzer, Export
    };

    class Position {
    public:
        //%%%%%% Initializers %%%%%%%%%%%//
        Position();
        Position(char* EmpName, char* JobTitle, char* Loc, char* Email, unsigned UJID);
        virtual ~Position();
        bool operator<(Position& Other);
        bool operator==(Position& Other);
        //%%%%%% Exportation and toStream %%%%%%%%%%%//
        bool toStream(std::ostream& output, const OutputFormat FORMAT = Export);
    private:
        virtual void printStandard(std::ostream& output) {
        }

        virtual void printFancy(std::ostream& output, const bool USE_ANALYZER) {
        }
    public:
        //%%%%%% Get Data %%%%%%%%%%%//

        virtual const char* type() = 0;
        // Getters
        virtual const char* GetEmployer() = 0;
        virtual const char* GetJobTitle() = 0;
        virtual const char* GetDescription() = 0;
        virtual const char* GetEmployerEmail() = 0;
        Analyzer::PositionAnalyzer* Analyzer();
    protected:
        Position(const Position& orig); // Restrict copying to nonexistent
        // Data
        unsigned UJobID;
        // Analyzer
        Analyzer::PositionAnalyzer* pAnalyzer;
    };
    const bool sv(std::string); // Sane Value
}// End Namespace
#endif	/* POSITION_H */

