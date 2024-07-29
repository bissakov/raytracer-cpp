
#include <src/file_io.h>
#include <src/utils.h>
#include <strsafe.h>
#include <windows.h>

#include <cassert>
#include <string>

// TODO(bissakov): Implement platform-independent file IO.
void FreeMemory(BYTE* memory) {
  if (memory == nullptr) {
    return;
  }

  delete[] memory;
  memory = nullptr;

  assert(!memory);
}

FileResult ReadEntireFile(std::string file_path) {
  FileResult result = {};

  HANDLE file_handle = CreateFile(file_path.c_str(), GENERIC_READ,
                                  FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);
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

  result.content = new BYTE[result.file_size];

  if (!result.content) {
    FreeMemory(result.content);
    CloseHandle(file_handle);
    return result;
  }

  DWORD bytes_read = 0;
  if (!(ReadFile(file_handle, result.content, result.file_size, &bytes_read,
                 0) &&
        result.file_size == bytes_read)) {
    FreeMemory(result.content);
    CloseHandle(file_handle);
    return result;
  }

  CloseHandle(file_handle);

  return result;
}

bool WriteEntireFile(const char* file_path, uint32_t memory_size,
                     BYTE* memory) {
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

bool WriteFileText(std::string file_path, std::string text) {
  HANDLE file_handle =
      CreateFile(file_path.c_str(), GENERIC_WRITE, 0, 0, CREATE_ALWAYS, 0, 0);
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

bool CompareFiles(const std::string& file_path1,
                  const std::string& file_path2) {
  HANDLE h_file1 = CreateFile(file_path1.c_str(), GENERIC_READ, 0, NULL,
                              OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
  HANDLE h_file2 = CreateFile(file_path2.c_str(), GENERIC_READ, 0, NULL,
                              OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

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

  BYTE* buffer1 = new BYTE[file_size1];
  BYTE* buffer2 = new BYTE[file_size2];

  DWORD bytes_read1, bytes_read2;
  BOOL read1 = ReadFile(h_file1, buffer1, file_size1, &bytes_read1, NULL);
  BOOL read2 = ReadFile(h_file2, buffer2, file_size2, &bytes_read2, NULL);

  if (!read1 || !read2 || bytes_read1 != file_size1 ||
      bytes_read2 != file_size2) {
    delete[] buffer1;
    delete[] buffer2;
    CloseHandle(h_file1);
    CloseHandle(h_file2);
    return false;
  }

  bool result = (memcmp(buffer1, buffer2, file_size1) == 0);

  delete[] buffer1;
  delete[] buffer2;
  CloseHandle(h_file1);
  CloseHandle(h_file2);

  return result;
}
