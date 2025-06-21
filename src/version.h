#ifndef VERSION_H
#define VERSION_H

/**
 * \file version.h
 * \brief Source header file for version routines.
 */

#include <string>

namespace version
{
#define MAJOR_VERSION "000"
#define MINOR_VERSION "001"
#define PATCH_VERSION "002"

// This exists this in this manor so that you may find these strings as human readable strings
// within the resulting executable.  For example, you could use the 'strings' utility on the
// executable and find:
// VERSION=
// 001.000.000
static const char versionPreamble[] = "VERSION=";
static const char version[] = MAJOR_VERSION "." MINOR_VERSION "." PATCH_VERSION;

/**
 * Obtains a string representation of the version.
 * \return The version string.
 */
std::string getVersionString();
/**
 * Obtains a string representation of the major portion of the version.
 * \return The major version string.
 */
std::string getMajorVersionString();
/**
 * Obtains the value of the major portion of the version.
 * \return The major version value.
 */
unsigned int getMajorVersionValue();
/**
 * Obtains a string representation of the minor portion of the version.
 * \return The minor version string.
 */
std::string getMinorVersionString();
/**
 * Obtains the value of the minor portion of the version.
 * \return The minor version value.
 */
unsigned int getMinorVersionValue();
/**
 * Obtains a string representation of the patch portion of the version.
 * \return The patch version string.
 */
std::string getPatchVersionString();
/**
 * Obtains the value of the patch portion of the version.
 * \return The patch version value.
 */
unsigned int getPatchVersionValue();
}

#endif // VERSION_H
