#ifndef SRC_FILE_IO_H_
#define SRC_FILE_IO_H_

#include <windows.h>

#include <cstdint>
#include <string>

struct FileResult {
  BYTE *content;
  uint32_t file_size;
  bool file_exists;
};

void FreeMemory(const BYTE *memory);
FileResult ReadEntireFile(const std::string file_path);
bool WriteEntireFile(const char *file_path, const uint32_t memory_size,
                     const BYTE *memory);
bool WriteFileText(const std::string file_path, const std::string text);
bool CompareFiles(const std::string &filePath1, const std::string &filePath2);

#endif  // SRC_FILE_IO_H_
