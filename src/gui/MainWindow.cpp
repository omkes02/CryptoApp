#include "MainWindow.h"
#include "ui_mainwindow.h"
#include "utils/file_utils.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDir>
#include <QStandardPaths>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , cryptoManager(new CryptoManager(this))
{
    ui->setupUi(this);
    loadConfig();
    setupConnections();
    onOperationChanged(ui->operationComboBox->currentText()); // Set initial UI state
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadConfig()
{
    QString configPath = "config/config.json";
    if (!FileUtils::FileExists(configPath.toStdString())) {
        QDir().mkpath("config");
        createDefaultConfig(configPath);
    }

    QFile configFile(configPath);
    if (!configFile.open(QIODevice::ReadOnly)) {
        log("Failed to open config file.");
        return;
    }

    QJsonDocument configDoc = QJsonDocument::fromJson(configFile.readAll());
    config = configDoc.object();
    log("Configuration loaded.");

    // Create directories if they don't exist
    QDir().mkpath(QString::fromStdString(config["keys_dir"].toString().toStdString()));
    QDir().mkpath(QString::fromStdString(config["output_dir"].toString().toStdString()));
}

void MainWindow::createDefaultConfig(const QString& path)
{
    QJsonObject defaultConfig;
    defaultConfig["rsa_key_size"] = 2048;
    defaultConfig["dsa_key_size"] = 2048;
    defaultConfig["hash_algorithm"] = "SHA256";
    defaultConfig["keys_dir"] = "keys";
    defaultConfig["output_dir"] = "output";

    QJsonDocument doc(defaultConfig);
    QFile file(path);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(doc.toJson());
        log("Default config file created at " + QDir::current().absoluteFilePath(path));
    } else {
        log("Failed to create default config file.");
    }
}

void MainWindow::setupConnections()
{
    connect(ui->processButton, &QPushButton::clicked, this, &MainWindow::onProcess);
    connect(ui->uploadButton, &QPushButton::clicked, this, &MainWindow::onUploadFile);
    connect(ui->downloadButton, &QPushButton::clicked, this, &MainWindow::onDownloadFile);
    connect(ui->operationComboBox, &QComboBox::currentTextChanged, this, &MainWindow::onOperationChanged);
}

void MainWindow::onOperationChanged(const QString &operation)
{
    ui->inputTextEdit->clear();
    ui->inputPathLineEdit->clear();
    ui->downloadButton->setEnabled(false);

    bool isKeyPairGen = (operation.contains("Key Pair"));
    bool isVerify = (operation.contains("Verify"));

    ui->inputTextEdit->setEnabled(!isKeyPairGen);
    ui->uploadButton->setEnabled(!isKeyPairGen);

    if (isVerify) {
        // Verification needs two inputs: the message and the signature.
        // We'll use the text edit for the message and file upload for the signature.
        ui->inputTextEdit->setEnabled(true);
        ui->uploadButton->setEnabled(true);
        log("For verification: provide message in text input or as a file, and upload the signature file.");
    } else if (isKeyPairGen) {
        log("Click 'Process' to generate new key pair.");
    }
}

void MainWindow::onProcess()
{
    QString operation = ui->operationComboBox->currentText();
    log("Processing operation: " + operation);
    setUiEnabled(false);
    ui->progressBar->setValue(0);
    outputData.clear();
    outputFileName.clear();
    ui->downloadButton->setEnabled(false);

    try {
        if (operation == "Generate RSA Key Pair") {
            cryptoManager->generateRsaKeyPair(config["rsa_key_size"].toInt(), config["keys_dir"].toString().toStdString());
            log("RSA key pair generated successfully in '" + config["keys_dir"].toString() + "' directory.");
        } else if (operation == "Generate DSA Key Pair") {
            cryptoManager->generateDsaKeyPair(config["dsa_key_size"].toInt(), config["keys_dir"].toString().toStdString());
            log("DSA key pair generated successfully in '" + config["keys_dir"].toString() + "' directory.");
        } else {
            // Operations requiring input
            std::string inputDataStr;
            if (!ui->inputTextEdit->toPlainText().isEmpty()) {
                inputDataStr = ui->inputTextEdit->toPlainText().toStdString();
            } else if (!ui->inputPathLineEdit->text().isEmpty()) {
                                inputDataStr = FileUtils::ReadFile(ui->inputPathLineEdit->text().toStdString());
            } else {
                throw std::runtime_error("No input provided. Use the text field or upload a file.");
            }

            if (operation == "RSA Encrypt") {
                std::string publicKeyPath = (config["keys_dir"].toString() + "/rsa_public.key").toStdString();
                std::string result = cryptoManager->rsaEncrypt(publicKeyPath, inputDataStr);
                outputData = QByteArray::fromStdString(result);
                outputFileName = "encrypted.bin";
                log("Encryption successful. Click 'Download Output' to save.");
            } else if (operation == "RSA Decrypt") {
                std::string privateKeyPath = (config["keys_dir"].toString() + "/rsa_private.key").toStdString();
                std::string result = cryptoManager->rsaDecrypt(privateKeyPath, inputDataStr);
                outputData = QByteArray::fromStdString(result);
                outputFileName = "decrypted.txt";
                log("Decryption successful. Click 'Download Output' to save.");
            } else if (operation == "DSA Sign") {
                std::string privateKeyPath = (config["keys_dir"].toString() + "/dsa_private.key").toStdString();
                std::string result = cryptoManager->dsaSign(privateKeyPath, inputDataStr);
                outputData = QByteArray::fromStdString(result);
                outputFileName = "signature.sig";
                log("Signing successful. Click 'Download Output' to save.");
            } else if (operation == "DSA Verify") {
                // For verification, the signature must be from a file.
                if (ui->inputPathLineEdit->text().isEmpty()) {
                    throw std::runtime_error("Signature file not provided. Please upload a signature file.");
                }
                                std::string signature = FileUtils::ReadFile(ui->inputPathLineEdit->text().toStdString());
                std::string publicKeyPath = (config["keys_dir"].toString() + "/dsa_public.key").toStdString();
                bool success = cryptoManager->dsaVerify(publicKeyPath, inputDataStr, signature);
                if (success) {
                    log("Signature verified successfully.");
                    QMessageBox::information(this, "Success", "Signature is valid.");
                } else {
                    throw std::runtime_error("Signature verification failed.");
                }
            }
        }

        if (!outputData.isEmpty()) {
            ui->downloadButton->setEnabled(true);
        }
        ui->progressBar->setValue(100);

    } catch (const std::exception& e) {
        log("Error: " + QString(e.what()));
        QMessageBox::critical(this, "Error", e.what());
        ui->progressBar->setValue(0);
    }
    setUiEnabled(true);
}

void MainWindow::onUploadFile()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Select Input File", QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation));
    if (!filePath.isEmpty()) {
        ui->inputPathLineEdit->setText(filePath);
        log("Selected input file: " + filePath);
    }
}

void MainWindow::onDownloadFile()
{
    if (outputData.isEmpty()) {
        log("No output data to save.");
        return;
    }
    QString outputPath = QDir(config["output_dir"].toString()).filePath(outputFileName);
    QString savePath = QFileDialog::getSaveFileName(this, "Save Output File", outputPath);

    if (!savePath.isEmpty()) {
        QFile file(savePath);
        if (file.open(QIODevice::WriteOnly)) {
            file.write(outputData);
            log("Output saved to: " + savePath);
        } else {
            log("Failed to save output file: " + file.errorString());
            QMessageBox::critical(this, "Error", "Could not save file: " + file.errorString());
        }
    }
}

void MainWindow::log(const QString& message)
{
    ui->logTextEdit->append(message);
}

void MainWindow::setUiEnabled(bool enabled)
{
    ui->operationComboBox->setEnabled(enabled);
    ui->processButton->setEnabled(enabled);
    ui->uploadButton->setEnabled(enabled);
    ui->inputTextEdit->setEnabled(enabled);
    // download button is handled separately
}
