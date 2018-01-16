/* 
 * File:   PositionAnalyzer.h
 * Author: Jesse Schwarz
 * 
 * Created on January 15, 2018, 7:22 PM
 */

#ifndef POSITIONANALYZER_H
#define	POSITIONANALYZER_H

#include <string>
#include "autoCL.h"

namespace Analyzer {

    class PositionAnalyzer {
    public:
        PositionAnalyzer(const std::string FULL_DESCRIPTION);
        PositionAnalyzer(const std::string FULL_DESCRIPTION, const std::string TITLE, 
        const std::string EMPLOYER,const std::string EMAIL);
        ~PositionAnalyzer();
        // * Check for position data requirements * //
        bool req(std::string KEYWORD);
        void toStream(std::ostream& out,const bool VERBOSE=true);
        void apply(std::ostream& out,const bool NO_OVERRIDE=true);
    private:
        PositionAnalyzer(const PositionAnalyzer& orig);
        const std::string strDESC, strTITLE,strEMP,strEML;
    };
}// End Namespace
#endif	/* POSITIONANALYZER_H */

