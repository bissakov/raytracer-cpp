#ifndef SRC_FILE_IO_H_
#define SRC_FILE_IO_H_

#include <windows.h>

#include <cstdint>
#include <string>

struct FileResult {
  bool file_exists;
  uint32_t file_size;
  BYTE *content;
};

void FreeMemory(BYTE *memory);
FileResult ReadEntireFile(std::string file_path);
bool WriteEntireFile(const char *file_path, uint32_t memory_size, BYTE *memory);
bool WriteFileText(std::string file_path, std::string text);
bool CompareFiles(const std::string &filePath1, const std::string &filePath2);

#endif  // SRC_FILE_IO_H_
