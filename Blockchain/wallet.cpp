#include "wallet.h"

#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>
#include <memory>
#include <sstream>
#include <iomanip>

static string bytes_to_hex(const unsigned char* data, size_t len) {
    std::ostringstream oss;
    oss << std::hex << std::setfill('0');
    for (size_t i = 0; i < len; ++i) {
        oss << std::setw(2) << (int)(data[i] & 0xFF);
    }
    return oss.str();
}

static string bio_to_string(BIO* bio) {
    BUF_MEM* bptr = nullptr;
    BIO_get_mem_ptr(bio, &bptr);
    if (!bptr || !bptr->data) return string();
    return string(bptr->data, bptr->length);
}

Wallet::Wallet() {
    EVP_PKEY_CTX* pctx = EVP_PKEY_CTX_new_id(EVP_PKEY_EC, nullptr);
    if (!pctx) {
        address.clear();
        return;
    }

    if (EVP_PKEY_keygen_init(pctx) <= 0) {
        EVP_PKEY_CTX_free(pctx);
        address.clear();
        return;
    }

    if (EVP_PKEY_CTX_set_ec_paramgen_curve_nid(pctx, NID_secp256k1) <= 0) {
        EVP_PKEY_CTX_free(pctx);
        address.clear();
        return;
    }

    EVP_PKEY* pkey = nullptr;
    if (EVP_PKEY_keygen(pctx, &pkey) <= 0 || !pkey) {
        EVP_PKEY_CTX_free(pctx);
        address.clear();
        return;
    }

    EVP_PKEY_CTX_free(pctx);

    BIO* pri_bio = BIO_new(BIO_s_mem());
    if (pri_bio) {
        if (PEM_write_bio_PrivateKey(pri_bio, pkey, nullptr, nullptr, 0, nullptr, nullptr)) {
            privateKeyPEM = bio_to_string(pri_bio);
        }
        BIO_free(pri_bio);
    }

    BIO* pub_bio = BIO_new(BIO_s_mem());
    if (pub_bio) {
        if (PEM_write_bio_PUBKEY(pub_bio, pkey)) {
            publicKeyPEM = bio_to_string(pub_bio);
        }
        BIO_free(pub_bio);
    }

    if (!publicKeyPEM.empty()) {
        address = sha256_string(publicKeyPEM);
    } else {
        address.clear();
    }

    EVP_PKEY_free(pkey);
}

string Wallet::getAddress() {
    return address;
}

string Wallet::getPublicKeyPEM() {
    return publicKeyPEM;
}

string Wallet::getPrivateKeyPEM() {
    return privateKeyPEM;
}

string Wallet::sign(const string& message) {
    BIO* pri_bio = BIO_new_mem_buf(privateKeyPEM.data(), static_cast<int>(privateKeyPEM.size()));
    if (!pri_bio) return string();

    EVP_PKEY* pkey = PEM_read_bio_PrivateKey(pri_bio, nullptr, nullptr, nullptr);
    BIO_free(pri_bio);
    if (!pkey) return string();

    EVP_MD_CTX* mdctx = EVP_MD_CTX_new();
    if (!mdctx) {
        EVP_PKEY_free(pkey);
        return string();
    }

    if (EVP_DigestSignInit(mdctx, nullptr, EVP_sha256(), nullptr, pkey) <= 0) {
        EVP_MD_CTX_free(mdctx);
        EVP_PKEY_free(pkey);
        return string();
    }

    if (EVP_DigestSignUpdate(mdctx, message.data(), message.size()) <= 0) {
        EVP_MD_CTX_free(mdctx);
        EVP_PKEY_free(pkey);
        return string();
    }

    size_t siglen = 0;
    if (EVP_DigestSignFinal(mdctx, nullptr, &siglen) <= 0) {
        EVP_MD_CTX_free(mdctx);
        EVP_PKEY_free(pkey);
        return string();
    }

    std::unique_ptr<unsigned char[]> sig_buf(new unsigned char[siglen]);
    if (EVP_DigestSignFinal(mdctx, sig_buf.get(), &siglen) <= 0) {
        EVP_MD_CTX_free(mdctx);
        EVP_PKEY_free(pkey);
        return string();
    }

    string sig_hex = bytes_to_hex(sig_buf.get(), siglen);

    EVP_MD_CTX_free(mdctx);
    EVP_PKEY_free(pkey);

    return sig_hex;
}