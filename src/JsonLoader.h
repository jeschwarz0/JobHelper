/* 
 * File:   JsonLoader.h
 * Author: Jesse Schwarz
 * 
 * Created on January 15, 2018, 7:22 PM
 */
#ifndef PARSEUTILS_H
#define PARSEUTILS_H

#include <list>
#include "Position.h"

namespace JsonLoader {
    void pathCheck();
    void ListDataFiles(std::list<const char*>& target);
    std::list<Positions::Position*> LoadDataDir();
    void LoadDataFile(const char* filename, std::list<Positions::Position*>& collection);
}// end namespace
#endif