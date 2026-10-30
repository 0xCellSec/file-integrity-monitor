#include "hash.hpp"

#include <openssl/evp.h>
#include <iostream> 
#include <fstream>


struct Nibble  
{
    uint8_t lower_nible : 4;
    uint8_t upper_nibble : 4;
};

void Hashing::hashSegment(uint8_t* segment,  EVP_MD_CTX* ctx, std::streamsize size)
{
    EVP_DigestInit_ex(ctx, EVP_sha256(), NULL);
    EVP_DigestUpdate(ctx, segment, size);
}

void Hashing::createCheckSum(std::fstream& infile)
{

    unsigned char hashed_binary_value[32];

    EVP_MD_CTX* ctx = EVP_MD_CTX_new();
   
    uint8_t segment[32];

    while (infile)
    {
    infile.read(reinterpret_cast<char *> (segment), 32);
        if (infile.gcount() > 0)
        {
            std::cout << "Segment: " << segment << std::endl;
    hashSegment(segment, ctx, infile.gcount());
        }
           
        else
        {
            std::cout << "END FILE REACHED" << std::endl;
            break;
        }


    // moved the data fom ctx into hashed_value
    EVP_DigestFinal_ex(ctx, hashed_binary_value, NULL);

   
    std::string full_text;
    binaryToText(hashed_binary_value, full_text, sizeof(hashed_binary_value));
    std::cout << full_text << std::endl;
    EVP_MD_CTX_free(ctx);
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
