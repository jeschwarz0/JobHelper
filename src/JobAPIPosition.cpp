/* 
 * File:   JobAPIPosition.cpp
 * Author: Jesse Schwarz
 * 
 * Created on January 15, 2018, 7:22 PM
 */
#include <string.h>// For strcpy and strcmp
#include <iostream>
#include <stdlib.h>

#include "JAPosition.h"
#include "JobAPIPosition.h"// For utility declarations

namespace Positions {

    JobAPIPosition::JobAPIPosition(JAPosition_t* source, const char* sourceFileName) {
        if (source != 0) {
            _data = source;
        }
        if (sourceFileName != 0) {
            const size_t len = strlen(sourceFileName) + 1;
            char* sourceStore = new char(len);
            strncpy(sourceStore, sourceFileName, len);
            _sourceFileName = sourceStore;
        }
    }

    JobAPIPosition::JobAPIPosition(JobAPIPosition& Other) {
    }

    JobAPIPosition::~JobAPIPosition() {
        if (_data != 0) {
            delete _data;
            _data = 0;
        }
        if (_sourceFileName != 0) {
            _sourceFileName = 0;
            delete []_sourceFileName;
        }
    }

    const char* JobAPIPosition::type() {
        return "JobAPIPosition";
    }

    const char* JobAPIPosition::GetDescription() {
        return _data->description.c_str();
    }

    const char* JobAPIPosition::GetEmployer() {
        return _data->company.c_str();
    }

    const char* JobAPIPosition::GetEmployerEmail() {
        return _data->hiringOrganization.email.c_str();
    }

    const char* JobAPIPosition::GetJobTitle() {
        return _data->title.c_str();
    }

    void JobAPIPosition::printStandard(std::ostream& output) {
        if (sv(_data->title))
            output << "\n| :) " << _data->title << "(" << UJobID << ")";
        if (sv(_data->company))
            output << "\n| :) " << _data->company;
        if (sv(_data->location))
            output << "\n| :) " << _data->location;
        if (!sv(_data->hiringOrganization.email))
            output << "\n|  ): NO EMAIL PROVIDED";
        output << std::endl;
    }

    void JobAPIPosition::printFancy(std::ostream& output, const bool USE_ANALYZER) {
        output << "*********** - JobAPI " << (UJobID > 0 ? UJobID : 0) << " - ***************************";
        if (sv(_data->company))
            output << "\nEmployer:" << _data->company;
        if (sv(_data->title))
            output << "\nTitle:" << _data->title;
        if (sv(_data->location))
            output << "\nLocation:" << _data->location;
        if (sv(_data->jobLocation.name))
            output << "\nAddress:" << _data->jobLocation.name;
        if (sv(_data->hiringOrganization.email))
            output << "\nEmail:" << _data->hiringOrganization.email;
        if (sv(_data->url))
            output << "\nLink:" << _data->url;
        if (sv(_data->baseSalary))
            output << "\nSalary:" << _data->baseSalary;
        if (sv(_data->datePosted))
            output << "\nPost Date: " << _data->datePosted;
        if (sv(_data->endDate))
            output << "\nEnd Date: " << _data->endDate;
        if (_sourceFileName != 0)
            output << "\nSource File: " << _sourceFileName;
        if (USE_ANALYZER && pAnalyzer != 0) {
            pAnalyzer->toStream(output, false);
        }// if the user chooses as such
        output << "\n";
    }
}//End Namespace