#ifndef SRC_CORE_FILE_IO_H_
#define SRC_CORE_FILE_IO_H_

#include <core/utils.h>
#include <windows.h>

#include <cstdint>
#include <memory>
#include <string>

struct FileResult {
  std::unique_ptr<BYTE[]> content;
  uint32_t file_size;
  bool file_exists;
};

FileResult ReadEntireFile(const char* file_path) noexcept;
bool WriteEntireFile(const char* file_path, uint32_t memory_size,
                     const BYTE* memory) noexcept;
bool WriteFileText(const Path& file_path, std::string text) noexcept;
bool WriteLineToFile(HANDLE file_handle, const char* line) noexcept;
bool CompareFiles(const char* file_path1, const char* file_path2) noexcept;

#endif  // SRC_CORE_FILE_IO_H_
