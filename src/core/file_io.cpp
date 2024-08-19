#include <core/file_io.h>
#include <core/utils.h>
#include <strsafe.h>
#include <windows.h>

#include <cassert>
#include <memory>
#include <string>

// TODO(bissakov): Implement platform-independent file IO.
FileResult ReadEntireFile(const char* file_path) noexcept {
  FileResult result = {};

  HANDLE file_handle = CreateFile(file_path, GENERIC_READ, FILE_SHARE_READ, 0,
                                  OPEN_EXISTING, 0, 0);
  if (file_handle == INVALID_HANDLE_VALUE) {
    CloseHandle(file_handle);
    result.file_exists = false;
    return result;
  }

  result.file_exists = true;

  LARGE_INTEGER file_size;

  if (!GetFileSizeEx(file_handle, &file_size)) {
    CloseHandle(file_handle);
    return result;
  }

  assert(file_size.QuadPart <= 0xFF'FF'FF'FF);
  result.file_size = (uint32_t)(file_size.QuadPart);

  result.content = std::make_unique<BYTE[]>(result.file_size);

  if (!result.content) {
    CloseHandle(file_handle);
    return result;
  }

  DWORD bytes_read = 0;
  if (!(ReadFile(file_handle, result.content.get(), result.file_size,
                 &bytes_read, 0) &&
        result.file_size == bytes_read)) {
    CloseHandle(file_handle);
    return result;
  }

  CloseHandle(file_handle);

  return result;
}

bool WriteEntireFile(const char* file_path, const uint32_t memory_size,
                     const BYTE* memory) noexcept {
  HANDLE file_handle =
      CreateFile(file_path, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, 0, 0);
  if (file_handle == INVALID_HANDLE_VALUE) {
    CloseHandle(file_handle);
    return false;
  }

  DWORD bytes_written = 0;
  if (!WriteFile(file_handle, memory, memory_size, &bytes_written, 0)) {
    CloseHandle(file_handle);
    return false;
  }

  CloseHandle(file_handle);

  bool res = bytes_written == memory_size;
  return res;
}

bool WriteFileText(const Path& file_path, const std::string text) noexcept {
  HANDLE file_handle =
      CreateFile(file_path.value, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, 0, 0);
  if (file_handle == INVALID_HANDLE_VALUE) {
    CloseHandle(file_handle);
    return false;
  }

  DWORD bytes_to_write = (DWORD)text.size();
  DWORD bytes_written = 0;

  if (!WriteFile(file_handle, text.c_str(), bytes_to_write, &bytes_written,
                 0)) {
    CloseHandle(file_handle);
    ErrorExit(TEXT("WriteFile"));
    return false;
  }

  CloseHandle(file_handle);

  bool res = bytes_written == bytes_to_write;
  return res;
}

bool WriteLineToFile(HANDLE file_handle, const char* line) noexcept {
  DWORD bytes_to_write = (DWORD)strlen(line);
  DWORD bytes_written;

  if (!WriteFile(file_handle, line, bytes_to_write, &bytes_written, 0)) {
    ErrorExit(TEXT("WriteFile"));
    return false;
  }

  return bytes_to_write == bytes_written;
}

bool CompareFiles(const char* file_path1, const char* file_path2) noexcept {
  HANDLE h_file1 = CreateFile(file_path1, GENERIC_READ, 0, NULL, OPEN_EXISTING,
                              FILE_ATTRIBUTE_NORMAL, NULL);
  HANDLE h_file2 = CreateFile(file_path2, GENERIC_READ, 0, NULL, OPEN_EXISTING,
                              FILE_ATTRIBUTE_NORMAL, NULL);

  if (h_file1 == INVALID_HANDLE_VALUE) {
    CloseHandle(h_file1);
    return false;
  }

  if (h_file2 == INVALID_HANDLE_VALUE) {
    CloseHandle(h_file2);
    return false;
  }

  DWORD file_size1 = GetFileSize(h_file1, NULL);
  DWORD file_size2 = GetFileSize(h_file2, NULL);

  if (file_size1 != file_size2) {
    CloseHandle(h_file1);
    CloseHandle(h_file2);
    return false;
  }

  std::unique_ptr<BYTE[]> buffer1 = std::make_unique<BYTE[]>(file_size1);
  std::unique_ptr<BYTE[]> buffer2 = std::make_unique<BYTE[]>(file_size2);

  DWORD bytes_read1, bytes_read2;
  BOOL read1 = ReadFile(h_file1, buffer1.get(), file_size1, &bytes_read1, NULL);
  BOOL read2 = ReadFile(h_file2, buffer2.get(), file_size2, &bytes_read2, NULL);

  if (!read1 || !read2 || bytes_read1 != file_size1 ||
      bytes_read2 != file_size2) {
    CloseHandle(h_file1);
    CloseHandle(h_file2);
    return false;
  }

  bool result = (memcmp(buffer1.get(), buffer2.get(), file_size1) == 0);

  CloseHandle(h_file1);
  CloseHandle(h_file2);

  return result;
}
