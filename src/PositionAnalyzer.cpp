/* 
 * File:   PositionAnalyzer.cpp
 * Author: Jesse Schwarz
 * 
 * Created on January 15, 2018, 7:22 PM
 */
#include <iostream>
#include "PositionAnalyzer.h"
//      Constructors
namespace Analyzer {

    PositionAnalyzer::PositionAnalyzer(const std::string FULL_DESCRIPTION) :
    strDESC(FULL_DESCRIPTION), strTITLE(""), strEMP(""), strEML("") {
        //DO NOTHING MORE;
    }

    PositionAnalyzer::PositionAnalyzer(
            const std::string FULL_DESCRIPTION, const std::string TITLE,
            const std::string EMPLOYER, const std::string EMAIL) :
    strDESC(FULL_DESCRIPTION), strTITLE(TITLE), strEMP(EMPLOYER), strEML(EMAIL) {
        //DO NOTHING MORE;
    }

    PositionAnalyzer::~PositionAnalyzer() {
        // DO NOTHING ELSE...
    }

    //  Analyzer

    bool PositionAnalyzer::req(const std::string KEYWORD) {
        return strDESC.find(KEYWORD);
    }
   
    void PositionAnalyzer::toStream(std::ostream& out, const bool VERBOSE) {
        if (VERBOSE) {
            out << "\t^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n" <<
                    "\tPositionAnalyzer{string[" << strDESC.length() << "]," << strTITLE << "," << strEMP << "," << strEML << "}\n";
        }
        out << "\n\t___________________________\n" << // Output the analyzer
                "\tNot Implemented!\n\t" <<
                (VERBOSE ? "\t^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n" : "");
    }

    void PositionAnalyzer::apply(std::ostream& out, const bool MANUAL_MODE) {
        if (MANUAL_MODE) {
            toStream(std::cout, false);
        }//TODO: Implement dynamically from configuration file
        std::string cl = autoCL::getCoverLetter(// Generate cover letter
                MANUAL_MODE ? autoCL::manualGetType(autoCL::cltype::Default) : autoCL::cltype::Default,
                MANUAL_MODE || strTITLE == "NA" ? autoCL::getString("Job Title", strTITLE) : strTITLE,
                (MANUAL_MODE || strEMP== "NA" || strEMP == "NYI") ?
                autoCL::getString("Employer's Name", (std::string)strEMP) : strEMP);
        if (!cl.empty())
            out <<
                "\n$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n" <<
                "<|  Email:  " << strEML << "  |>\n\n" << cl <<
                "\n$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n";
    }
}// End Namespace