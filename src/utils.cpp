#include <src/utils.h>
#include <windows.h>

#include <cstdio>

void ErrorExit(const LPCTSTR function) {
  LPVOID message_buffer;
  DWORD last_error_code = GetLastError();

  FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |
                    FORMAT_MESSAGE_IGNORE_INSERTS,
                NULL, last_error_code,
                MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                (LPTSTR)&message_buffer, 0, NULL);

  printf("\33[0;31m%s failed with error %lu:\033[0m %s", function,
         last_error_code, (LPCTSTR)message_buffer);

  LocalFree(message_buffer);
  ExitProcess(last_error_code);
}
