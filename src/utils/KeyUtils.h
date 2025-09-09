#ifndef KEYUTILS_H
#define KEYUTILS_H

#include <string>
#include <cryptlib.h>
#include <rsa.h>
#include <dsa.h>

namespace KeyUtils {

bool SavePrivateKey(const std::string& filename, const CryptoPP::PrivateKey& key);
bool SavePublicKey(const std::string& filename, const CryptoPP::PublicKey& key);
bool LoadPrivateKey(const std::string& filename, CryptoPP::PrivateKey& key);
bool LoadPublicKey(const std::string& filename, CryptoPP::PublicKey& key);

// Overloads for specific key types
bool SavePrivateKey(const std::string& filename, const CryptoPP::RSA::PrivateKey& key);
bool SavePublicKey(const std::string& filename, const CryptoPP::RSA::PublicKey& key);
bool LoadPrivateKey(const std::string& filename, CryptoPP::RSA::PrivateKey& key);
bool LoadPublicKey(const std::string& filename, CryptoPP::RSA::PublicKey& key);

bool SavePrivateKey(const std::string& filename, const CryptoPP::DSA::PrivateKey& key);
bool SavePublicKey(const std::string& filename, const CryptoPP::DSA::PublicKey& key);
bool LoadPrivateKey(const std::string& filename, CryptoPP::DSA::PrivateKey& key);
bool LoadPublicKey(const std::string& filename, CryptoPP::DSA::PublicKey& key);

std::string ToHex(const std::string& data);

} // namespace KeyUtils

#endif // KEYUTILS_H