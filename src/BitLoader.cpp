/* 
 * File:   BitLoader.cpp
 * Author: Jesse Schwarz
 * 
 * Created on January 15, 2018, 7:22 PM
 */
#include <stdio.h>//  For printf();)
#include <string.h>// For char* comparisons
#include <stdlib.h>// For exit(0))

#include "BitLoader.h"

namespace BitOpts {
    unsigned int cFlags = opUseBlacklist; // Defaulted flags

    //******************************************************************************
    //              Helper function for storing bitwise booleans
    //******************************************************************************

    void setFlag(JPOptions opt, const bool rep) {
        if (((cFlags & opt) > 0) != rep)
            cFlags ^= opt; // Swap bit
    }

    void toggleFlag(JPOptions opt) {
        cFlags ^= opt;
    }

    /**
     * Get a flag item
     * @param what
     * @return 
     */
    const bool getFlag(JPOptions what) {
        return (cFlags & what) > 0;
    }

    void printVersion();
    void printHelp();

    void bind(const char* source, const char& find, const JPOptions opt, const bool value) {
        if (strchr(source, find))
            setFlag(opt, value);
    }

    bool bind(const char* source, const char* find, const JPOptions opt, const bool value) {
        if (strcasecmp(source, find) == 0) {
            setFlag(opt, value);
            return true;
        }
        return false;
    }

    void loadFlags(int* argc, char** argv) {
        for (unsigned short u = 1; u < *argc; u++) {
            if (u == 1 && argv[1][0] == '-' && argv[1][1] != '-') {// SHORTHAND
                const char* b_chars = "fwdbBvmr";
                const JPOptions b_opts[] = {opChooseFile, opWriteToFile, opDebugMode, opUseBlacklist, opUseBlacklist, opVerboseList, opNoMenu, opSort};
                bool b_res[] = {true, true, true, true, false, true, true, true};
                // Print the menu
                for (unsigned short idx = 0; idx < strlen(b_chars); idx++) {
                    bind(argv[1], b_chars[idx], b_opts[idx], b_res[idx]);
                }
                // END SHORTHAND
            } else if (strcmp(argv[u], "--version") == 0) {
                printVersion();
                exit(0);
            } else if (strcmp(argv[u], "--help") == 0) {
                printHelp();
                exit(0);
            } else {
                const char* b_chars[] = {"--choose-file", "--to-file",
                    "--debug-mode", "--blacklist", "--no-blacklist",
                    "--verbose-menu", "--no-menu", "--sort"};
                const JPOptions b_opts[] = {opChooseFile, opWriteToFile, opDebugMode, opUseBlacklist, opUseBlacklist, opVerboseList, opNoMenu, opSort};
                const bool b_res[] = {true, true, true, true, false, true, true, true};
                unsigned short idx = 0;
                while ((idx++ < 12) && bind(argv[u], b_chars[idx], b_opts[idx], b_res[idx])); // Process each other record
            }
        }// End for
        if (getFlag(opDebugMode))
            printFlags();

    }

    void printFlags() {
        //printf("ARGV[%d]=%s | %p\n\n", u, argv[u], *argv[u]);
        printf(
                "opUseBlacklist = %d,opDebugMode = %d,opChooseFile = %d,opVerboseList = %d,opWriteToFile = %d,opNoMenu= %d, opSort = %d\n"
                , getFlag(opUseBlacklist), getFlag(opDebugMode), getFlag(opChooseFile), getFlag(opVerboseList), getFlag(opWriteToFile), getFlag(opNoMenu), getFlag(opSort));

    }

    void printHelp() {

        printf("Usage: JobHelper [OPTION]\nView and analyze data from JSON data sources.\n"
                "-f, --choose-file\t Only load a single file\n"
                "-w, --to-file\tWrite the cover letter to \"coverletters.txt\"\n"
                "-d, --debug-mode\tPrint data to screen, including debugging output\n"
                "-m, --no-menu\tOnly list records and do not open interactive menu\n"
                "-b, --blacklist\tUse the default blacklist file(Default)\n"
                "-B, --no-blacklist\tDo not use the default blacklist file\n"
                "-r, --sort\tSort records by ID\n"
                "-v, --verbose-menu\tShow analyzer summary in menu\n"
                "--help\t Print this message\n"
                "--version\t output version information and exit\n");
    }

    void printVersion() {
        printf("JobHelper Version 1.0\nAuthor: Jesse Schwarz\n");
    }
}// End Namespace

