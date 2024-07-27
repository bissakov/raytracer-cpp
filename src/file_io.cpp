
#include <src/file_io.h>
#include <windows.h>

#include <cassert>

// TODO(bissakov): Implement platform-independent file IO.
void FreeMemory(void **memory) {
  if (!memory || !*memory) {
    return;
  }

  VirtualFree(*memory, 0, MEM_RELEASE);
  *memory = 0;

  assert(!*memory);
}

FileResult ReadEntireFile(wchar_t *file_path) {
  FileResult result = {};

  HANDLE file_handle = CreateFileW(file_path, GENERIC_READ, FILE_SHARE_READ, 0,
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

  result.content = VirtualAlloc(0, result.file_size, MEM_RESERVE | MEM_COMMIT,
                                PAGE_READWRITE);
  if (!result.content) {
    FreeMemory(&result.content);
    CloseHandle(file_handle);
    return result;
  }

  DWORD bytes_read = 0;
  if (!(ReadFile(file_handle, result.content, result.file_size, &bytes_read,
                 0) &&
        result.file_size == bytes_read)) {
    FreeMemory(&result.content);
    CloseHandle(file_handle);
    return result;
  }

  CloseHandle(file_handle);

  return result;
}

bool WriteEntireFile(const wchar_t *file_path, uint32_t memory_size,
                     void *memory) {
  HANDLE file_handle =
      CreateFileW(file_path, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, 0, 0);
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

bool WriteFileText(const wchar_t *file_path, const wchar_t *text) {
  HANDLE file_handle =
      CreateFileW(file_path, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, 0, 0);
  if (file_handle == INVALID_HANDLE_VALUE) {
    CloseHandle(file_handle);
    return false;
  }

  DWORD bytes_to_write = static_cast<DWORD>(wcslen(text)) * sizeof(wchar_t);
  DWORD bytes_written = 0;

  if (!WriteFile(file_handle, text, bytes_to_write, &bytes_written, 0)) {
    CloseHandle(file_handle);
    return false;
  }

  CloseHandle(file_handle);

  bool res = bytes_written == bytes_to_write;
  return res;
}
