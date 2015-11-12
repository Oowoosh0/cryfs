#pragma once
#ifndef MESSMER_CRYFS_SRC_CONFIG_CRYCONFIGLOADER_H_
#define MESSMER_CRYFS_SRC_CONFIG_CRYCONFIGLOADER_H_

#include <messmer/cpp-utils/pointer/unique_ref.h>
#include <boost/filesystem.hpp>
#include "CryConfigFile.h"
#include "CryCipher.h"
#include "CryConfigCreator.h"
#include <messmer/cpp-utils/crypto/kdf/Scrypt.h>

namespace cryfs {

class CryConfigLoader {
public:
  CryConfigLoader(cpputils::unique_ref<cpputils::Console> console, cpputils::RandomGenerator &keyGenerator, const cpputils::SCryptSettings &scryptSettings, std::function<std::string()> askPassword, const boost::optional<std::string> &cipher);
  CryConfigLoader(CryConfigLoader &&rhs) = default;

  boost::optional<CryConfigFile> loadOrCreate(const boost::filesystem::path &filename);

private:
    boost::optional<CryConfigFile> _loadConfig(const boost::filesystem::path &filename);
    CryConfigFile _createConfig(const boost::filesystem::path &filename);

    CryConfigCreator _creator;
    cpputils::SCryptSettings _scryptSettings;
    std::function<std::string()> _askPassword;
    boost::optional<std::string> _cipher;

    DISALLOW_COPY_AND_ASSIGN(CryConfigLoader);
};

}

#endif