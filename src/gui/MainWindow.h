#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QJsonObject>
#include <QByteArray>
#include "crypto/CryptoManager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onProcess();
    void onUploadFile();
    void onDownloadFile();
    void onOperationChanged(const QString &operation);

private:
    void loadConfig();
    void createDefaultConfig(const QString& path);
    void setupConnections();
    void log(const QString& message);
    void setUiEnabled(bool enabled);

    Ui::MainWindow *ui;
    CryptoManager *cryptoManager;
    QJsonObject config;
    QByteArray outputData;
    QString outputFileName;
};
#endif // MAINWINDOW_H
