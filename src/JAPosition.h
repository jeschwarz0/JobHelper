/* 
 * File:   JAPosition.h
 * Author: Jesse Schwarz
 * 
 * Created on January 15, 2018, 7:22 PM
 */

#ifndef JAPOSITION_H
#define JAPOSITION_H

#include<string>
using std::string;

struct JAGeo_t{
    float latitude;
    float longitude;
    string alternateName;
    string description;
    string name;
    string url;
};

struct JAAddress_t{
    string addressCountry;
    string addressLocality;
    string addressRegion;
    string postalCode;
    string postOfficeBoxNumber;
    string streetAddress;
};

struct JALocation_t{
    JAAddress_t address;
    JAGeo_t geo;
    string telephone;
    string alternateName;
    string description;
    string name;
    string url;
};

struct JAHiringOrg_t{
    JAAddress_t address;
    string email;
    string logo;
    string telephone;
    string alternateName;
    string description;
    string name;
    string url;
};

struct JAPosition_t{
    string alternateName;
    string baseSalary;
    string company;
    string datePosted;
    string description;
    string educationRequirements;
    string employmentType;
    string endDate;
    string experienceRequirements;
    JAHiringOrg_t hiringOrganization;
    string incentiveCompensation;
    string industry;
    string javascriptAction;
    string javascriptFunction;
    string jobBenefits;
    JALocation_t jobLocation;
    string location;
    string maximumSalary;
    string minimumSalary;
    string name;
    string occupationalCategory;
    string qualifications;
    string query;
    string responsibilities;
    string salaryCurrency;
    string skills;
    string source;
    string sourceId;
    string specialCommitments;
    string startDate;
    string title;
    string url;
    string workHours;
    //int[] _terms;
    long lastObservedAt;
    long firstObservedAt;
    long objectID;
};

#endif /* JAPOSITION_H */

