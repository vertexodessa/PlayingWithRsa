#pragma once

#include <openssl/ssl.h>

namespace MyOpenSslExample {
class OpenSslWrapper {
  public:
    virtual RSA* RSA_new() const;
    virtual void RSA_free(RSA*) const;

    virtual int RSA_generate_key_ex(RSA* rsa, int bits, BIGNUM* e,
                                    BN_GENCB* cb) const;

    virtual BIGNUM* BN_new() const;
    virtual void BN_clear_free(BIGNUM*) const;
    virtual int BN_set_word(BIGNUM* a, BN_ULONG w) const;
    virtual int BN_cmp(const BIGNUM* a, const BIGNUM* b) const;

    virtual const BIO_METHOD* BIO_s_mem(void) const;
    virtual BIO* BIO_new(const BIO_METHOD* type) const;
    virtual void BIO_vfree(BIO* p) const;
    virtual int BIO_read(BIO* b, void* buf, int len) const;
    virtual int BIO_write(BIO* b, const void* buf, int len) const;
    virtual long BIO_ctrl(BIO* bp, int cmd, long larg, void* parg) const;

    virtual int PEM_write_bio_RSAPublicKey(BIO* bp, RSA* x) const;
    virtual int PEM_write_bio_RSAPrivateKey(BIO* bp, RSA* x,
                                            const EVP_CIPHER* enc,
                                            unsigned char* kstr, int klen,
                                            pem_password_cb* cb, void* u) const;
    virtual RSA* PEM_read_bio_RSAPrivateKey(BIO* bp, RSA** x,
                                            pem_password_cb* cb, void* u) const;

    virtual void RSA_get0_key(const RSA* r, const BIGNUM** n, const BIGNUM** e,
                              const BIGNUM** d) const;
    virtual int RSA_public_encrypt(int flen, const unsigned char* from,
                                   unsigned char* to, RSA* rsa,
                                   int padding) const;
    virtual int RSA_private_decrypt(int flen, const unsigned char* from,
                                    unsigned char* to, RSA* rsa,
                                    int padding) const;
    virtual RSA* PEM_read_bio_RSAPublicKey(BIO* bp, RSA** x,
                                           pem_password_cb* cb, void* u) const;

    virtual RSA* EVP_PKEY_get1_RSA(EVP_PKEY* pkey) const;

    virtual void ERR_error_string_n(unsigned long e, char* buf,
                                    size_t len) const;
    virtual unsigned long ERR_get_error(void) const;
};
} // namespace MyOpenSslExample
