#ifndef SRC_FILE_IO_H_
#define SRC_FILE_IO_H_

#include <cstdint>

struct FileResult {
  bool file_exists;
  uint32_t file_size;
  void *content;
};

void FreeMemory(void **memory);
FileResult ReadEntireFile(wchar_t *file_path);
bool WriteEntireFile(const wchar_t *file_path, uint32_t memory_size,
                     void *memory);
bool WriteFileText(const wchar_t *file_path, const wchar_t *text);

#endif  // SRC_FILE_IO_H_
