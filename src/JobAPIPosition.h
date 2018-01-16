/* 
 * File:   JobAPIPosition.h
 * Author: Jesse Schwarz
 * 
 * Created on January 15, 2018, 7:22 PM
 */

#ifndef JOBAPIPOSITION_H
#define	JOBAPIPOSITION_H

#include "JAPosition.h"
#include "Position.h"

namespace Positions {

    class JobAPIPosition : public Position {
    public:
        JobAPIPosition(JAPosition_t* source, const char* sourceFileName);
        virtual ~JobAPIPosition();
        
        virtual void printStandard(std::ostream& output);
        virtual void printFancy(std::ostream& output,const bool USE_ANALYZER);
        
        virtual const char* type();
        virtual const char* GetEmployer();
        virtual const char* GetJobTitle();
        virtual const char* GetDescription();
        virtual const char* GetEmployerEmail();
    protected:
        JobAPIPosition(JobAPIPosition& Other);
    private:
        // Data Members
        JAPosition_t* _data;
        const char* _sourceFileName;
    };
}// End Namespace
#endif	/* PETOBJ_H */