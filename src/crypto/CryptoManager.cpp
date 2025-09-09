#include "CryptoManager.h"
#include "utils/KeyUtils.h"
#include <rsa.h>
#include <osrng.h>
#include <base64.h>
#include <files.h>
#include <dsa.h>
#include <sha.h>
#include <pssr.h>
#include <stdexcept>

CryptoManager::CryptoManager(QObject *parent) : QObject(parent) {}

void CryptoManager::generateRsaKeyPair(int keySize, const std::string& keysDir) {
    CryptoPP::AutoSeededRandomPool rng;

    CryptoPP::RSA::PrivateKey privateKey;
    privateKey.GenerateRandomWithKeySize(rng, keySize);
    CryptoPP::RSA::PublicKey publicKey(privateKey);

    KeyUtils::SavePrivateKey(keysDir + "/rsa_private.key", privateKey);
    KeyUtils::SavePublicKey(keysDir + "/rsa_public.key", publicKey);
}

std::string CryptoManager::rsaEncrypt(const std::string& publicKeyPath, const std::string& plaintext) {
    CryptoPP::AutoSeededRandomPool rng;
    CryptoPP::RSA::PublicKey publicKey;
    KeyUtils::LoadPublicKey(publicKeyPath, publicKey);

    CryptoPP::RSAES_OAEP_SHA_Encryptor e(publicKey);
    std::string ciphertext;

    CryptoPP::StringSource ss(plaintext, true,
        new CryptoPP::PK_EncryptorFilter(rng, e,
            new CryptoPP::StringSink(ciphertext)
        )
    );

    return ciphertext;
}

std::string CryptoManager::rsaDecrypt(const std::string& privateKeyPath, const std::string& ciphertext) {
    CryptoPP::AutoSeededRandomPool rng;
    CryptoPP::RSA::PrivateKey privateKey;
    KeyUtils::LoadPrivateKey(privateKeyPath, privateKey);

    CryptoPP::RSAES_OAEP_SHA_Decryptor d(privateKey);
    std::string recovered;

    CryptoPP::StringSource ss(ciphertext, true,
        new CryptoPP::PK_DecryptorFilter(rng, d,
            new CryptoPP::StringSink(recovered)
        )
    );

    return recovered;
}

void CryptoManager::generateDsaKeyPair(int keySize, const std::string& keysDir) {
    CryptoPP::AutoSeededRandomPool rng;

    CryptoPP::DSA::PrivateKey privateKey;
    privateKey.GenerateRandomWithKeySize(rng, keySize);
    CryptoPP::DSA::PublicKey publicKey;
    publicKey.AssignFrom(privateKey);

    KeyUtils::SavePrivateKey(keysDir + "/dsa_private.key", privateKey);
    KeyUtils::SavePublicKey(keysDir + "/dsa_public.key", publicKey);
}

std::string CryptoManager::dsaSign(const std::string& privateKeyPath, const std::string& message) {
    CryptoPP::AutoSeededRandomPool rng;
    CryptoPP::DSA::PrivateKey privateKey;
    KeyUtils::LoadPrivateKey(privateKeyPath, privateKey);

    CryptoPP::DSA::Signer signer(privateKey);
    std::string signature;

    CryptoPP::StringSource ss(message, true,
        new CryptoPP::SignerFilter(rng, signer,
            new CryptoPP::StringSink(signature)
        )
    );

    return signature;
}

bool CryptoManager::dsaVerify(const std::string& publicKeyPath, const std::string& message, const std::string& signature) {
    CryptoPP::DSA::PublicKey publicKey;
    KeyUtils::LoadPublicKey(publicKeyPath, publicKey);

    CryptoPP::DSA::Verifier verifier(publicKey);

    bool result = false;
    CryptoPP::StringSource ss(signature + message, true,
        new CryptoPP::SignatureVerificationFilter(
            verifier,
            new CryptoPP::ArraySink((CryptoPP::byte*)&result, sizeof(result))
        )
    );

    return result;
}
