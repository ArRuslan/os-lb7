#include <cstdint>
#include <iostream>
#include <windows.h>
#include "procinfo.hpp"

#define CreateProc(name, prio, si, pi) CreateProcess(name, NULL, NULL, NULL, true, prio, NULL, NULL, si, pi)

int main() {
    STARTUPINFO sInfo, sInfo2;
    PROCESS_INFORMATION pInfo, pInfo2;

    ZeroMemory(&sInfo, sizeof(sInfo));
    ZeroMemory(&sInfo2, sizeof(sInfo2));
    sInfo.cb = sizeof(sInfo);
    sInfo2.cb = sizeof(sInfo2);
    ZeroMemory(&pInfo, sizeof(pInfo));
    ZeroMemory(&pInfo2, sizeof(pInfo2));

    if (!CreateProc("./lb7t2p1.exe", NORMAL_PRIORITY_CLASS, &sInfo, &pInfo)) {
        printf("CreateProcess failed (%lu).\n", GetLastError());
        return 1;
    }

    WaitForSingleObject(pInfo.hProcess, INFINITE);
    CloseHandle(pInfo.hProcess);
    CloseHandle(pInfo.hThread);

    // Prog 2

    if (!CreateProc("./lb7t2p2.exe", BELOW_NORMAL_PRIORITY_CLASS, &sInfo2, &pInfo2)) {
        printf("CreateProcess failed (%lu).\n", GetLastError());
        return 1;
    }

    WaitForSingleObject(pInfo2.hProcess, INFINITE);
    CloseHandle(pInfo2.hProcess);
    CloseHandle(pInfo2.hThread);

    printf("\nProcess (main) info:\n");
    printProcInfo(getpid());
    printf("\n");

    return 0;
}
