#pragma once

#include "cryptopp/hex.h"
#include "cryptopp/cryptlib.h"
#include "cryptopp/filters.h"
#include "cryptopp/aes.h"
#include "cryptopp/gcm.h"

using CryptoPP::HexEncoder;
using CryptoPP::HexDecoder;

using CryptoPP::BufferedTransformation;
using CryptoPP::AuthenticatedSymmetricCipher;

using CryptoPP::Redirector;
using CryptoPP::StringSink;
using CryptoPP::StringSource;
using CryptoPP::AuthenticatedEncryptionFilter;
using CryptoPP::AuthenticatedDecryptionFilter;

using CryptoPP::AES;
using CryptoPP::GCM;

class Encryptor
{
public:
	static std::string encrypt(std::string text);
	static std::string decrypt(std::string cipher);

private:
	static byte key[AES::DEFAULT_KEYLENGTH];
	static byte iv[AES::BLOCKSIZE];
	static const int TAG_SIZE;
};

