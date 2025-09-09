#include "file_utils.h"
#include <fstream>
#include <stdexcept>
#include <QDir> // Include QDir for directory creation
#include <QFileInfo> // Include QFileInfo for path manipulation

namespace FileUtils {

std::string ReadFile(const std::string& filePath) {
    std::ifstream file(filePath, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file for reading: " + filePath);
    }
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);
    std::vector<char> buffer(size);
    if (!file.read(buffer.data(), size)) {
        throw std::runtime_error("Could not read file: " + filePath);
    }
    return std::string(buffer.begin(), buffer.end());
}

bool WriteFile(const std::string& filePath, const std::string& content) {
    // Ensure the directory exists before writing the file
    QFileInfo fileInfo(QString::fromStdString(filePath));
    QDir dir(fileInfo.dir().path());
    if (!dir.exists()) {
        if (!dir.mkpath(".")) { // mkpath(".") creates the directory if it doesn't exist
            throw std::runtime_error("Could not create directory for file: " + filePath);
        }
    }

    std::ofstream file(filePath, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file for writing: " + filePath);
    }
    file.write(content.data(), content.size());
    return file.good();
}

bool FileExists(const std::string& filePath) {
    return QFile::exists(QString::fromStdString(filePath));
}

} // namespace FileUtils
