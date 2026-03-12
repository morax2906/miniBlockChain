#include "lib.h"
string time_now() {
    time_t now = time(0);
    tm* ltm = localtime(&now);

    stringstream ss;
    ss << 1900 + ltm->tm_year << "-"
        << 1 + ltm->tm_mon << "-"
        << ltm->tm_mday;

    string result = ss.str();
    return result;
}
string sha256_string(const std::string& data) {
    EVP_MD_CTX* context = EVP_MD_CTX_new();
    if (context == nullptr) return "error Context!";

    if (EVP_DigestInit_ex(context, EVP_sha256(), nullptr) != 1) {
        EVP_MD_CTX_free(context);
        return "error!";
    }

    if (EVP_DigestUpdate(context, data.c_str(), data.length()) != 1) {
        EVP_MD_CTX_free(context);
        return "error!";
    }

    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int lengthOfHash = 0;

    if (EVP_DigestFinal_ex(context, hash, &lengthOfHash) != 1) {
        EVP_MD_CTX_free(context);
        return "error!";
    }

    EVP_MD_CTX_free(context);

    std::stringstream ss;
    for (unsigned int i = 0; i < lengthOfHash; ++i) {
        ss << std::hex << setw(2) << setfill('0') << static_cast<int>(hash[i]);
    }

    return ss.str();
}
