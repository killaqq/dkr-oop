#include "Encryptor.h"

using namespace std;

string Encryptor::encrypt(string text)
{
	string cipher;
	try
	{
		GCM<AES>::Encryption e;
		e.SetKeyWithIV(key, sizeof(key), iv, sizeof(iv));
		StringSource(text, true,
			new AuthenticatedEncryptionFilter(e,
				new StringSink(cipher), false, TAG_SIZE
			)
		);
	}
	catch (CryptoPP::InvalidArgument& e)
	{
		cerr << "Caught InvalidArgument..." << "\n";
		cerr << e.what() << "\n\n";
	}
	catch (CryptoPP::Exception& e)
	{
		cerr << "Caught Exception..." << "\n";
		cerr << e.what() << "\n\n";
	}
	return cipher;
}

string Encryptor::decrypt(string cipher)
{
	string text;
	try
	{
		GCM<AES>::Decryption d;
		d.SetKeyWithIV(key, sizeof(key), iv, sizeof(iv));

		AuthenticatedDecryptionFilter df(d,
			new StringSink(text),
			AuthenticatedDecryptionFilter::DEFAULT_FLAGS,
			TAG_SIZE
		);

		StringSource(cipher, true,
			new Redirector(df)
		);

		bool b = df.GetLastResult();
	}
	catch (CryptoPP::HashVerificationFilter::HashVerificationFailed& e)
	{
		cerr << "Caught HashVerificationFailed..." << "\n";
		cerr << e.what() << "\n";
		cerr << "\n";
	}
	catch (CryptoPP::InvalidArgument& e)
	{
		cerr << "Caught InvalidArgument..." << "\n";
		cerr << e.what() << "\n";
		cerr << "\n";
	}
	catch (CryptoPP::Exception& e)
	{
		cerr << "Caught Exception..." << "\n";
		cerr << e.what() << "\n";
		cerr << "\n";
	}
	return text;
}

byte Encryptor::key[AES::DEFAULT_KEYLENGTH] = { 0xC0, 0xF3, 0x69, 0x69, 0x32, 0xAF, 0xEE, 0xCB, 0x1D, 0xA7, 0x23, 0xA6, 0x90, 0x5E, 0x66, 0x5C };
byte Encryptor::iv[AES::BLOCKSIZE] = { 0x9F, 0xF8, 0x9B, 0xB2, 0x0A, 0x0F, 0xAD, 0xDE, 0x38, 0x86, 0xB9, 0xB9, 0x23, 0x4E, 0xE8, 0xC1 };
const int Encryptor::TAG_SIZE = 12;
