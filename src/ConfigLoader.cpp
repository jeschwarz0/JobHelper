/* 
 * File:   ConfigLoader.cpp
 * Author: Jesse Schwarz
 *
 * Created on January 16, 2018, 2:36 PM
 */

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem.hpp>
#include <iostream>
#include <string>
#include "ConfigLoader.h"

using boost::property_tree::ptree;
using std::vector;

namespace Analyzer {
    std::string CONFIG_FILE = std::string(getenv("HOME")) + "/.config/JobHelper/preferences.xml";

    void loadV1(ptree& rootElement, UserConfig_t* result) {
        for (ptree::value_type& node : rootElement.get_child("UserPreference")) {
            try {// Loop through UserPreference for SearchCategories
                if (node.first == "SearchCategory") {
                    SearchCategory_t category = SearchCategory_t();
                    category.Name = node.second.get<string>("Name");
                    category.CoverLetterPath = node.second.get<string>("CoverLetterPath", "");
                    // Loop through SearchCategories for CategoryValues
                    for (ptree::value_type& catValRoot : node.second.get_child("")) {
                        if (catValRoot.first == "CategoryValue") {
                            CategoryValue_t catVal;
                            catVal.EntryName = catValRoot.second.get<string>("EntryName");
                            catVal.MatchValue = catValRoot.second.get<signed int>("MatchValue");
                            catVal.NonMatchValue = catValRoot.second.get<signed int>("NonMatchValue");
                            category.CategoryValues.push_back(catVal);
                        }
                    }
                    result->Categories.push_back(category);
                } else if (node.first == "SearchEntry") {
                    // Process search entry
                    SearchEntry_t entry = SearchEntry_t();
                    entry.Name = node.second.get<string>("Name");
                    for (ptree::value_type& termRoot : node.second.get_child("SearchTerms")) {
                        string term = termRoot.second.get_value<string>("Term");
                        entry.SearchTerms.push_back(term);
                    }
                    result->Entries.push_back(entry);
                }
            } catch (boost::property_tree::ptree_error ex) {
                std::cerr << "Failed to parse element " << ex.what() << std::endl;
            }
        }
    }

    UserConfig_t* LoadUserConfig() {
        UserConfig_t* result = new UserConfig_t;
        ptree input;
        try {
            read_xml(CONFIG_FILE.c_str(), input);
            result->ConfigVersion = input.get<uint>("UserPreference.ConfigVersion");
            if (result->ConfigVersion == 1) loadV1(input, result);
        } catch (boost::property_tree::ptree_error ex) {
            std::cerr << ex.what() << std::endl;
        } catch (std::exception ex) {
            std::cerr << "Failed to load " << CONFIG_FILE.c_str() << " | " << ex.what() << std::endl;
        }
        return result;
    }
}