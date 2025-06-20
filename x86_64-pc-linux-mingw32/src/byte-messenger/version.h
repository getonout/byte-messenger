#ifndef VERSION_H
#define VERSION_H

#include <string>

namespace version
{
#define MAJOR_VERSION "000"
#define MINOR_VERSION "001"
#define PATCH_VERSION "001"

// This exists this in this manor so that you may find these strings as human readable strings
// within the resulting executable.  For example, you could use the 'strings' utility on the
// executable and find:
// VERSION=
// 001.000.000
static const char versionPreamble[] = "VERSION=";
static const char version[] = MAJOR_VERSION "." MINOR_VERSION "." PATCH_VERSION;

std::string getVersionString();
std::string getMajorVersionString();
unsigned int getMajorVersionValue();
std::string getMinorVersionString();
unsigned int getMinorVersionValue();
std::string getPatchVersionString();
unsigned int getPatchVersionValue();
}

#endif // VERSION_H
