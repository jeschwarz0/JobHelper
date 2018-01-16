/* 
 * File:   BitLoader.h
 * Author: Jesse Schwarz
 * 
 * Created on January 15, 2018, 7:22 PM
 */

#ifndef BITLOADER_H
#define	BITLOADER_H

namespace BitOpts {

    enum JPOptions {
        opUseBlacklist = 0x01,
        opDebugMode = 0x02,
        opChooseFile = 0x4,
        opVerboseList = 0x8,
        opWriteToFile = 0x10,
        opNoMenu = 0x20,
        opSort = 0x40,
    };
    void loadFlags(int* argc, char** argv);
    const bool getFlag(JPOptions what);
    void setFlag(JPOptions opt, const bool rep);
    void toggleFlag(JPOptions opt);
    void printFlags();
}
/*-Wl,--allow-multiple-definition  A quick fix*/
#endif	/* BITLOADER_H */

