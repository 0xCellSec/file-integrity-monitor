#include <openssl/evp.h>
#include <fstream>
#include <cstdint>

#ifndef HASH_HPP
#define HASH_HPP
namespace Hashing
{

    void createCheckSum(std::fstream &file);
    void hashFile(EVP_MD_CTX *ctx, std::fstream &infile);
    void binaryToText(const unsigned char* hashed_value, std::string &full_text, int size);
};

#endif