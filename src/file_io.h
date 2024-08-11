#ifndef SRC_FILE_IO_H_
#define SRC_FILE_IO_H_

#include <src/utils.h>
#include <windows.h>

#include <cstdint>
#include <memory>
#include <string>

struct FileResult {
  std::unique_ptr<BYTE[]> content;
  uint32_t file_size;
  bool file_exists;
};

FileResult ReadEntireFile(const std::string file_path) noexcept;
bool WriteEntireFile(const char* file_path, const uint32_t memory_size,
                     const BYTE* memory) noexcept;
bool WriteFileText(const Path& file_path, const std::string text) noexcept;
bool CompareFiles(const char* file_path1, const char* file_path2) noexcept;

#endif  // SRC_FILE_IO_H_
