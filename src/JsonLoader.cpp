/* 
 * File:   JsonLoader.cpp
 * Author: Jesse Schwarz
 * 
 * Created on January 15, 2018, 7:22 PM
 */
#include <sstream>
#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem.hpp>
#include <dirent.h>
#include "JAPosition.h"
#include "JobAPIPosition.h"

using boost::property_tree::ptree;
using std::string;
using std::list;
using Positions::JobAPIPosition;
using Positions::Position;

namespace JsonLoader {
    const std::string DATA_DIR = std::string(getenv("HOME")) + "/.cache/jobhelper/";
    const std::string EMPTY_STRING = "";

    JAPosition_t* loadPositionFromNode(ptree tree);
    void processDataDir(std::list<Position*>& collection);

    void pathCheck() {
        boost::filesystem::create_directories(
                boost::filesystem::path(DATA_DIR));
    }

    void ListDataFiles(list<const char*>& target) {
        struct dirent** files;
        short count =
                scandir(DATA_DIR.c_str(), &files, NULL, alphasort);

        for (unsigned short int i = 0; i < count; i++) {
            if (!strstr(files[i]->d_name, ".json") == 0){
                target.push_back(files[i]->d_name);
            }
            free(files[i]);
        }
        free(files);
    }

    std::list<Position*> LoadDataDir() {
        std::list<Position*> collection = std::list<Position*>();
        processDataDir(collection);
        return collection;
    }

    void LoadDataFile(const char* filename, std::list<Position*>& collection) {
        ptree result;
        string fullpath (DATA_DIR.c_str());
        fullpath.append(filename);
        read_json(fullpath.c_str(), result);
        try {
            for (boost::property_tree::ptree::value_type& posting : result.get_child("")) {
                JAPosition_t* pSource = loadPositionFromNode(posting.second);
                if (pSource != 0) {
                    JobAPIPosition* pRecord = new JobAPIPosition(pSource, filename);
                    if (pRecord != 0)
                        collection.push_back(pRecord);
                }
            }
        } catch (std::exception ex) {
            std::cerr << "Failed to load " << filename << " | " << ex.what() << std::endl;
        }
    }

    void processDataDir(std::list<Position*>& collection) {
        struct dirent** files;
        short count =
                scandir(DATA_DIR.c_str(), &files, NULL, alphasort);

        for (unsigned short int i = 0; i < count; i++) {
            if (!strstr(files[i]->d_name, ".json") == 0)
                LoadDataFile(files[i]->d_name, collection);
            free(files[i]);
        }
        free(files);
    }

    JAPosition_t* loadPositionFromNode(ptree tree) {
        JAPosition_t* result = new JAPosition_t();
        try {
            // # / # //
            result->alternateName = tree.get_optional<string>("alternateName").get_value_or(EMPTY_STRING);
            result->baseSalary = tree.get_optional<string>("baseSalary").get_value_or(EMPTY_STRING);
            result->company = tree.get<string>("company");
            result->datePosted = tree.get_optional<string>("datePosted").get_value_or(EMPTY_STRING);
            result->description = tree.get<string>("description");
            result->educationRequirements = tree.get_optional<string>("educationRequirements").get_value_or(EMPTY_STRING);
            result->employmentType = tree.get_optional<string>("employmentType").get_value_or(EMPTY_STRING);
            result->endDate = tree.get_optional<string>("endDate").get_value_or(EMPTY_STRING);
            result->experienceRequirements = tree.get_optional<string>("experienceRequirements").get_value_or(EMPTY_STRING);
            // # HiringOrganization # //
            result->hiringOrganization = JAHiringOrg_t();
            result->hiringOrganization.address = JAAddress_t();
            result->hiringOrganization.alternateName = tree.get_optional<string>("hiringOrganization.alternateName").get_value_or(EMPTY_STRING);
            result->hiringOrganization.description = tree.get_optional<string>("hiringOrganization.description").get_value_or(EMPTY_STRING);
            result->hiringOrganization.email = tree.get_optional<string>("hiringOrganization.email").get_value_or(EMPTY_STRING);
            result->hiringOrganization.logo = tree.get_optional<string>("hiringOrganization.logo").get_value_or(EMPTY_STRING);
            result->hiringOrganization.name = tree.get_optional<string>("hiringOrganization.name").get_value_or(EMPTY_STRING);
            result->hiringOrganization.telephone = tree.get_optional<string>("hiringOrganization.telephone").get_value_or(EMPTY_STRING);
            result->hiringOrganization.url = tree.get_optional<string>("hiringOrganization.url").get_value_or(EMPTY_STRING);
            // # hiringOrganization.address # //
            result->hiringOrganization.address = JAAddress_t();
            result->hiringOrganization.address.addressCountry = tree.get_optional<string>("hiringOrganization.address.addressCountry").get_value_or(EMPTY_STRING);
            result->hiringOrganization.address.addressLocality = tree.get_optional<string>("hiringOrganization.address.addressLocality").get_value_or(EMPTY_STRING);
            result->hiringOrganization.address.addressRegion = tree.get_optional<string>("hiringOrganization.address.addressRegion").get_value_or(EMPTY_STRING);
            result->hiringOrganization.address.postOfficeBoxNumber = tree.get_optional<string>("hiringOrganization.address.postOfficeBoxNumber").get_value_or(EMPTY_STRING);
            result->hiringOrganization.address.postalCode = tree.get_optional<string>("hiringOrganization.address.postalCode").get_value_or(EMPTY_STRING);
            result->hiringOrganization.address.streetAddress = tree.get_optional<string>("hiringOrganization.address.streetAddress").get_value_or(EMPTY_STRING);
            // # / # //
            result->incentiveCompensation = tree.get_optional<string>("incentiveCompensation").get_value_or(EMPTY_STRING);
            result->industry = tree.get_optional<string>("industry").get_value_or(EMPTY_STRING);
            result->javascriptAction = tree.get_optional<string>("javascriptAction").get_value_or(EMPTY_STRING);
            result->javascriptFunction = tree.get_optional<string>("javascriptFunction").get_value_or(EMPTY_STRING);
            result->jobBenefits = tree.get_optional<string>("jobBenefits").get_value_or(EMPTY_STRING);
            // # jobLocation # //
            result->jobLocation = JALocation_t();
            // # jobLocation.address # //
            result->jobLocation.address = JAAddress_t();
            result->jobLocation.address.addressCountry = tree.get_optional<string>("jobLocation.address.addressCountry").get_value_or(EMPTY_STRING);
            result->jobLocation.address.addressLocality = tree.get_optional<string>("jobLocation.address.addressLocality").get_value_or(EMPTY_STRING);
            result->jobLocation.address.addressRegion = tree.get_optional<string>("jobLocation.address.addressRegion").get_value_or(EMPTY_STRING);
            result->jobLocation.address.postOfficeBoxNumber = tree.get_optional<string>("jobLocation.address.postOfficeBoxNumber").get_value_or(EMPTY_STRING);
            result->jobLocation.address.postalCode = tree.get_optional<string>("jobLocation.address.postalCode").get_value_or(EMPTY_STRING);
            result->jobLocation.address.streetAddress = tree.get_optional<string>("jobLocation.address.streetAddress").get_value_or(EMPTY_STRING);
            // # jobLocation.geo # //
            result->jobLocation.geo = JAGeo_t();
            result->jobLocation.geo.alternateName = tree.get_optional<string>("jobLocation.geo.alternateName").get_value_or(EMPTY_STRING);
            result->jobLocation.geo.description = tree.get_optional<string>("jobLocation.geo.description").get_value_or(EMPTY_STRING);
            result->jobLocation.geo.latitude = tree.get_optional<float>("jobLocation.geo.latitude").get_value_or(0);
            result->jobLocation.geo.longitude = tree.get_optional<float>("jobLocation.geo.longitude").get_value_or(0);
            result->jobLocation.geo.name = tree.get_optional<string>("jobLocation.geo.name").get_value_or(EMPTY_STRING);
            result->jobLocation.geo.url = tree.get_optional<string>("jobLocation.geo.url").get_value_or(EMPTY_STRING);
            // # jobLocation # //
            result->jobLocation.telephone = tree.get_optional<string>("jobLocation.telephone").get_value_or(EMPTY_STRING);
            result->jobLocation.alternateName = tree.get_optional<string>("jobLocation.alternateName").get_value_or(EMPTY_STRING);
            result->jobLocation.description = tree.get_optional<string>("jobLocation.description").get_value_or(EMPTY_STRING);
            result->jobLocation.name = tree.get_optional<string>("jobLocation.name").get_value_or(EMPTY_STRING);
            result->jobLocation.url = tree.get_optional<string>("jobLocation.url").get_value_or(EMPTY_STRING);
            // # / # //
            result->location = tree.get<string>("location");
            result->maximumSalary = tree.get_optional<string>("maximumSalary").get_value_or(EMPTY_STRING);
            result->minimumSalary = tree.get_optional<string>("minimumSalary").get_value_or(EMPTY_STRING);
            result->name = tree.get<string>("name");
            result->occupationalCategory = tree.get_optional<string>("occupationalCategory").get_value_or(EMPTY_STRING);
            result->qualifications = tree.get_optional<string>("qualifications").get_value_or(EMPTY_STRING);
            result->query = tree.get_optional<string>("query").get_value_or(EMPTY_STRING);
            result->responsibilities = tree.get_optional<string>("responsibilities").get_value_or(EMPTY_STRING);
            result->salaryCurrency = tree.get_optional<string>("salaryCurrency").get_value_or(EMPTY_STRING);
            result->skills = tree.get_optional<string>("skills").get_value_or(EMPTY_STRING);
            result->source = tree.get_optional<string>("source").get_value_or(EMPTY_STRING);
            result->sourceId = tree.get_optional<string>("sourceId").get_value_or(EMPTY_STRING);
            result->specialCommitments = tree.get_optional<string>("specialCommitments").get_value_or(EMPTY_STRING);
            result->startDate = tree.get_optional<string>("startDate").get_value_or(EMPTY_STRING);
            result->title = tree.get<string>("title");
            result->url = tree.get_optional<string>("url").get_value_or(EMPTY_STRING);
            result->workHours = tree.get_optional<string>("workHours").get_value_or(EMPTY_STRING);
            result->lastObservedAt = tree.get_optional<long>("lastObservedAt").get_value_or(0l);
            result->firstObservedAt = tree.get_optional<long>("firstObservedAt").get_value_or(0l);
            result->objectID = tree.get_optional<long>("objectID").get_value_or(0l);
        } catch (boost::property_tree::ptree_error ex) {
            std::cerr << "Failed to parse record | " << ex.what() << std::endl;
        } catch (std::exception ex) {
            std::cerr << "An unknown exception has occurred!" << std::endl;
        }
        return result;
    }
}