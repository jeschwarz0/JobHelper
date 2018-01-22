/* 
 * File:   ConfigLoader.h
 * Author: Jesse Schwarz
 *
 * Created on January 16, 2018, 9:15 PM
 */

#ifndef CONFIGLOADER_H
#define CONFIGLOADER_H

#include "UserConfig.h"
#include <vector>

using std::vector;
namespace Analyzer{
    UserConfig_t* LoadUserConfig();
}
#endif /* CONFIGLOADER_H */

