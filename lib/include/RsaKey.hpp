#pragma once

#include <cstddef>
#include <functional>
#include <memory>
#include <mutex>
#include <optional>
#include <variant>

#include <OpenSslWrapper.hpp>
#include <Result.hpp>
#include <utils/Deleter.hpp>

// TODO: forward-declare everything and move to .cpp
#include <openssl/rsa.h>
#include <openssl/ssl.h>

#include <experimental/filesystem>

using namespace std::experimental;

namespace MyOpenSslExample {

using RsaKeyPtr = std::unique_ptr<RSA, Deleter<RSA>>;

class BigNumber;

class RsaKey {
  public:
    enum class Exponent { Rsa3 = RSA_3, RsaF4 = RSA_F4 };

    RsaKey(const OpenSslWrapper& ssl, uint16_t keyLength = 1024,
           Exponent exponent = Exponent::Rsa3);

    RsaKey(RsaKey&& other)
        : m_bits(other.m_bits), m_exponent(other.m_exponent),
          m_ssl(std::move(other.m_ssl)), m_rsa(move(other.m_rsa)) {}

    RsaKey(const RsaKey& other) = delete;
    virtual ~RsaKey() = default;

    bool operator==(const RsaKey& other) const;

    virtual Error saveToFiles(const filesystem::path& privPath,
                              const filesystem::path& pubPath);
    virtual Error readFromFile(const filesystem::path& priv);

    Result<RSA*> getKey() const;

    Result<std::pair<std::string, std::string>> asStrings() const;

    virtual Error fromPrivateKeyStr(const std::string& privKey);

    // BigNumber dependency injection
    virtual Error initialize(BigNumber& bne) const;

  protected:
  private:
    Error initialize() const;

    static filesystem::path getAbsolutePath(const filesystem::path& relative);
    const uint16_t m_bits;
    const Exponent m_exponent;
    const OpenSslWrapper& m_ssl;
    mutable std::once_flag m_initOnce;
    mutable RsaKeyPtr m_rsa;
};

} // namespace MyOpenSslExample
