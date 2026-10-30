#include <openssl/evp.h>
#include <fstream>
#include <cstdint>

#ifndef HASH_HPP
#define HASH_HPP
namespace Hashing
{

        void createCheckSum(std::fstream &file);
        void binaryToText(const unsigned char* hashed_value, std::string &full_text, int size);
        void hashSegment(uint8_t* segment,  EVP_MD_CTX* ctx,  std::streamsize size);
};

#endif