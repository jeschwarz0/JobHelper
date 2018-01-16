/* 
 * File:   autoCL.h
 * Author: Jesse Schwarz
 * 
 * Created on January 15, 2018, 7:22 PM
 */

#ifndef AUTOCL_H
#define	AUTOCL_H

namespace autoCL {
    enum cltype {
        none, Default
    };
    std::string getString(const char* IDENTIFIER, const std::string& REC);
    cltype manualGetType(cltype rec);
    std::string getCoverLetter(cltype t, const std::string POSITION, const std::string COMPANY);
}
#endif	/* AUTOCL_H */

