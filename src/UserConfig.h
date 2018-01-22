/* 
 * File:   UserConfig.h
 * Author: Jesse Schwarz
 *
 * Created on January 16, 2018, 2:36 PM
 */

#ifndef CONFIG_T_H
#define CONFIG_T_H

#include <string>
#include <vector>

using std::string;
using std::vector;

namespace Analyzer {

    struct CategoryValue_t {
        string EntryName;
        signed int MatchValue;
        signed int NonMatchValue;
    };

    struct SearchCategory_t {
        string Name;
        string CoverLetterPath;
        vector<CategoryValue_t> CategoryValues;
    };

    struct SearchEntry_t {
        string Name;
        vector<string> SearchTerms;
    };

    struct UserConfig_t {
        uint ConfigVersion;
        vector<SearchEntry_t> Entries;
        vector<SearchCategory_t> Categories;
    };
}
#endif /* CONFIG_T_H */

