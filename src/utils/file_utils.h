#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <string>
#include <vector>

namespace FileUtils {

// Reads the entire content of a file into a string
std::string ReadFile(const std::string& filePath);

// Writes the given content to a file
bool WriteFile(const std::string& filePath, const std::string& content);

// Checks if a file exists
bool FileExists(const std::string& filePath);

} // namespace FileUtils

#endif // FILE_UTILS_H
