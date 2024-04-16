#include <cstdlib>
#include <cstdint>
#include <string>
#include <windows.h>

#include "procinfo.hpp"

#define CreateProc(args, si, pi) CreateProcess(NULL, args, NULL, NULL, true, 0, NULL, NULL, si, pi)

//constexpr std::string_view TEXT_EDITOR = "npp/notepad++.exe";
constexpr std::string_view TEXT_EDITOR = "../nano.exe";
constexpr char FILENAMES[3][64] = {"file1.txt", "file2.txt", "file3.txt"};

int main() {
    printf("\nProcess (program 1) info:\n");
    printProcInfo(getpid());
    printf("\n");

    for (auto& filename : FILENAMES) {
        STARTUPINFO sInfo;
        PROCESS_INFORMATION pInfo;
        ZeroMemory(&sInfo, sizeof(sInfo));
        sInfo.cb = sizeof(sInfo);
        ZeroMemory(&pInfo, sizeof(pInfo));

        std::string command = std::string(TEXT_EDITOR)+" "+std::string(filename);
        if (!CreateProc(const_cast<char*>(command.c_str()), &sInfo, &pInfo)) {
            printf("CreateProcess failed (%lu).\n", GetLastError());
            return 1;
        }
        WaitForSingleObject(pInfo.hProcess, INFINITE);
        CloseHandle(pInfo.hProcess);
        CloseHandle(pInfo.hThread);

        printf("Editor with %s exited.\n", filename);
    }
}
