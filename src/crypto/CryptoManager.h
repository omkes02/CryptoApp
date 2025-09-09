#ifndef CRYPTOMANAGER_H
#define CRYPTOMANAGER_H

#include <QObject>
#include <string>

class CryptoManager : public QObject
{
    Q_OBJECT
public:
    explicit CryptoManager(QObject *parent = nullptr);

    void generateRsaKeyPair(int keySize, const std::string& keysDir);
    std::string rsaEncrypt(const std::string& publicKeyPath, const std::string& plaintext);
    std::string rsaDecrypt(const std::string& privateKeyPath, const std::string& ciphertext);

    void generateDsaKeyPair(int keySize, const std::string& keysDir);
    std::string dsaSign(const std::string& privateKeyPath, const std::string& message);
    bool dsaVerify(const std::string& publicKeyPath, const std::string& message, const std::string& signature);
};

#endif // CRYPTOMANAGER_H