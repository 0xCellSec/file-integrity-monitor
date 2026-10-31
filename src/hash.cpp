#include "hash.hpp"

#include <openssl/evp.h>
#include <iostream> 
#include <fstream>
#include <algorithm>


struct Nibble  
{
    uint8_t lower_nible : 4;
    uint8_t upper_nibble : 4;
};

std::string Hashing::createCheckSum(std::fstream& infile)
{
    unsigned char hashed_binary_value[32];

    EVP_MD_CTX* ctx = EVP_MD_CTX_new();
    hashFile(ctx, infile);

    // moved the data fom ctx into hashed_value
    EVP_DigestFinal_ex(ctx, hashed_binary_value, NULL);

    std::string full_text;
    binaryToText(hashed_binary_value, full_text, sizeof(hashed_binary_value));
    std::cout << "Hash: " << full_text << std::endl;
    EVP_MD_CTX_free(ctx);

    return (full_text);
}

void Hashing::hashFile(EVP_MD_CTX *ctx, std::fstream &infile)
{
    uint8_t segment[32];

    EVP_DigestInit_ex(ctx, EVP_sha256(), NULL);
    while (infile)
    {
        // zeroing out an uint8_t array to erase any retained previous data
        std::fill(std::begin(segment), std::end(segment), 0);
        infile.read(reinterpret_cast<char *>(segment), 32);
        if (infile.gcount() > 0)
        {
            EVP_DigestUpdate(ctx, segment, infile.gcount());
        }
        else
        {
            break;
        }
    }
}

void Hashing::binaryToText(const unsigned char* hashed_value, std::string &full_text, int size)
{   
    Nibble nib;
    const char *hex_data = "0123456789abcdef";
    for (int i = 0; i < size; i++)
    {
        nib.upper_nibble = (hashed_value[i] >> 4) & 0x0F;
        nib.lower_nible = hashed_value[i] & 0x0F;
        full_text += hex_data[nib.upper_nibble];
        full_text += hex_data[nib.lower_nible];
    }
}
