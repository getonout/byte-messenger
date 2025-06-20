#include "version.h"

#include <cstdlib>
#include <string>

std::string version::getVersionString()
{
    return version;
}

std::string version::getMajorVersionString()
{
    return MAJOR_VERSION;
}

unsigned int version::getMajorVersionValue()
{
    return std::strtoul(MAJOR_VERSION, nullptr, 10);
}

std::string version::getMinorVersionString()
{
    return MINOR_VERSION;
}

unsigned int version::getMinorVersionValue()
{
    return std::strtoul(MINOR_VERSION, nullptr, 10);
}

std::string version::getPatchVersionString()
{
    return PATCH_VERSION;
}

unsigned int version::getPatchVersionValue()
{
    return std::strtoul(PATCH_VERSION, nullptr, 10);
}
