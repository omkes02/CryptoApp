#include "KeyUtils.h"
#include <files.h>
#include <osrng.h>
#include <hex.h>
#include <rsa.h>
#include <dsa.h>
#include <oids.h>

#include <stdexcept>
#include <iostream>

namespace KeyUtils {

// Generic Save/Load for PrivateKey and PublicKey (base classes)
bool SavePrivateKey(const std::string& filename, const CryptoPP::PrivateKey& key) {
    try {
        CryptoPP::FileSink file(filename.c_str(), true); // true for binary
        key.Save(file);
        return true;
    } catch (const CryptoPP::Exception& e) {
        std::cerr << "Error saving private key to " << filename << ": " << e.what() << std::endl;
        return false;
    }
}

bool SavePublicKey(const std::string& filename, const CryptoPP::PublicKey& key) {
    try {
        CryptoPP::FileSink file(filename.c_str(), true); // true for binary
        key.Save(file);
        return true;
    } catch (const CryptoPP::Exception& e) {
        std::cerr << "Error saving public key to " << filename << ": " << e.what() << std::endl;
        return false;
    }
}

bool LoadPrivateKey(const std::string& filename, CryptoPP::PrivateKey& key) {
    try {
        CryptoPP::FileSource file(filename.c_str(), true); // true for pumpAll
        key.Load(file);
        return true;
    } catch (const CryptoPP::Exception& e) {
        std::cerr << "Error loading private key from " << filename << ": " << e.what() << std::endl;
        return false;
    }
}

bool LoadPublicKey(const std::string& filename, CryptoPP::PublicKey& key) {
    try {
        CryptoPP::FileSource file(filename.c_str(), true); // true for pumpAll
        key.Load(file);
        return true;
    } catch (const CryptoPP::Exception& e) {
        std::cerr << "Error loading public key from " << filename << ": " << e.what() << std::endl;
        return false;
    }
}

// Specific Save/Load for RSA keys
bool SavePrivateKey(const std::string& filename, const CryptoPP::RSA::PrivateKey& key) {
    return SavePrivateKey(filename, static_cast<const CryptoPP::PrivateKey&>(key));
}

bool SavePublicKey(const std::string& filename, const CryptoPP::RSA::PublicKey& key) {
    return SavePublicKey(filename, static_cast<const CryptoPP::PublicKey&>(key));
}

bool LoadPrivateKey(const std::string& filename, CryptoPP::RSA::PrivateKey& key) {
    return LoadPrivateKey(filename, static_cast<CryptoPP::PrivateKey&>(key));
}

bool LoadPublicKey(const std::string& filename, CryptoPP::RSA::PublicKey& key) {
    return LoadPublicKey(filename, static_cast<CryptoPP::PublicKey&>(key));
}

// Specific Save/Load for DSA keys
bool SavePrivateKey(const std::string& filename, const CryptoPP::DSA::PrivateKey& key) {
    return SavePrivateKey(filename, static_cast<const CryptoPP::PrivateKey&>(key));
}

bool SavePublicKey(const std::string& filename, const CryptoPP::DSA::PublicKey& key) {
    return SavePublicKey(filename, static_cast<const CryptoPP::PublicKey&>(key));
}

bool LoadPrivateKey(const std::string& filename, CryptoPP::DSA::PrivateKey& key) {
    return LoadPrivateKey(filename, static_cast<CryptoPP::PrivateKey&>(key));
}

bool LoadPublicKey(const std::string& filename, CryptoPP::DSA::PublicKey& key) {
    return LoadPublicKey(filename, static_cast<CryptoPP::PublicKey&>(key));
}

std::string ToHex(const std::string& data) {
    std::string hex;
    CryptoPP::StringSource(data, true, new CryptoPP::HexEncoder(new CryptoPP::StringSink(hex)));
    return hex;
}

} // namespace KeyUtils