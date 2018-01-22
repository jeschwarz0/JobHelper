/* 
 * File:   JobApisLoader.h
 * Author: Jesse Schwarz
 * 
 * Created on January 15, 2018, 7:22 PM
 */
#ifndef JOBAPISL_H
#define JOBAPISL_H

#include <list>
#include "Position.h"

namespace JobApisLoader {
    void pathCheck();
    void ListDataFiles(std::list<const char*>& target);
    std::list<Positions::Position*> LoadDataDir();
    void LoadDataFile(const char* filename, std::list<Positions::Position*>& collection);
}// end namespace
#endif