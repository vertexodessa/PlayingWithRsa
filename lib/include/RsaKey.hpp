#pragma once

#include <cstddef>
#include <functional>
#include <memory>
#include <optional>

#include <utils/Deleter.hpp>

// TODO: forward-declare everything and move to .cpp
#include <openssl/rsa.h>
#include <openssl/ssl.h>

namespace MyOpenSslExample {

using RsaKeyPtr = std::unique_ptr<RSA, Deleter<RSA>>;
class BigNumber;

class RsaKey {
  public:
    enum class Exponent { Rsa3 = RSA_3, RsaF4 = RSA_F4 };

    RsaKey(uint16_t keyLength = 1024, Exponent exponent = Exponent::Rsa3);
    RsaKey(RsaKey&& other)
        : m_bits(other.m_bits), m_exponent(other.m_exponent),
          m_initialized(other.m_initialized), m_rsa(move(other.m_rsa)) {}

    RsaKey(const RsaKey& other) = delete;
    virtual ~RsaKey() = default;

    virtual bool initialize();
    virtual bool initialize(BigNumber& bne);

  protected:
    virtual RsaKeyPtr newKey();
    virtual bool generateKey(const BigNumber& bne);
    auto* getKey() const;

  private:
    const uint16_t m_bits;
    const Exponent m_exponent;
    bool m_initialized;
    RsaKeyPtr m_rsa;
};

std::optional<RsaKey>
make_rsa_key(uint16_t keyLength = 1024,
             RsaKey::Exponent exponent = RsaKey::Exponent::Rsa3);;

} // namespace MyOpenSslExample