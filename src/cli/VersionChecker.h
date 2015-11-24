#ifndef MESSMER_CRYFS_SRC_CLI_VERSIONCHECKER_H
#define MESSMER_CRYFS_SRC_CLI_VERSIONCHECKER_H

#include <messmer/cpp-utils/macros.h>
#include <string>
#include <boost/optional.hpp>
#include <boost/property_tree/ptree.hpp>
#include <messmer/cpp-utils/network/HttpClient.h>

namespace cryfs {
    //TODO Test

    class VersionChecker final {
    public:
        VersionChecker();
        //TODO Write a cpputils::shared_ref and use it
        VersionChecker(std::shared_ptr<cpputils::HttpClient> httpClient);

        boost::optional<std::string> newestVersion() const;
        boost::optional<std::string> securityWarningFor(const std::string &version) const;
    private:
        static boost::optional<boost::property_tree::ptree> _getVersionInfo(std::shared_ptr<cpputils::HttpClient> httpClient);
        static boost::optional<boost::property_tree::ptree> _parseJson(const std::string &json);

        boost::optional<boost::property_tree::ptree> _versionInfo;

        DISALLOW_COPY_AND_ASSIGN(VersionChecker);
    };
}

#endif
