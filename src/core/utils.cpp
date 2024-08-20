#include <core/utils.h>
#include <windows.h>

#include <cstdio>

void ErrorExit(const LPCTSTR function) {
  LPVOID message_buffer;
  DWORD last_error_code = GetLastError();

  FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |
                    FORMAT_MESSAGE_IGNORE_INSERTS,
                NULL, last_error_code,
                MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                reinterpret_cast<LPTSTR>(&message_buffer), 0, NULL);

  printf("\33[0;31m%s failed with error %lu:\033[0m %s", function,
         last_error_code, static_cast<LPCTSTR>(message_buffer));

  LocalFree(message_buffer);
  ExitProcess(last_error_code);
}

Path Join(const char* left, const char* right) noexcept {
  assert(left != nullptr && "left string is nullptr");
  assert(right != nullptr && "right string is nullptr");

  size_t length1 = strlen(left);
  size_t length2 = strlen(right);

  bool leftHasSeparator = (length1 > 0 && left[length1 - 1] == '/');
  bool rightHasSeparator = (length2 > 0 && right[0] == '/');
  assert(leftHasSeparator || rightHasSeparator || "No separator specified");

  size_t length = length1 + length2 + 1;
  assert(length <= MAX_PATH);

  Path path;

  memcpy(path.value, left, length1);
  memcpy(path.value + length1, right, length2);
  path.value[length - 1] = '\0';

  path.length = length;
  return path;
}
