#pragma once

#include <OpenSslWrapper.hpp>
#include <Result.hpp>
#include <RsaKey.hpp>
#include <utils/Deleter.hpp>

#include <string>

namespace MyOpenSslExample {

class RsaEngine {
  public:
    explicit RsaEngine(const OpenSslWrapper& rsa);

    Result<std::vector<unsigned char>>
    encrypt(const RsaKey& key, const std::vector<unsigned char>& data);

    Result<std::vector<unsigned char>>
    decrypt(const RsaKey& key, const std::vector<unsigned char>& data);

  private:
    const OpenSslWrapper& m_ssl;
};
} // namespace MyOpenSslExample
