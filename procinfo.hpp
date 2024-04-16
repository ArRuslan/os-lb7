#pragma once

#include <cstdint>
#include <iostream>
#include <windows.h>
#include <tlhelp32.h>

void printModsInfo(const uint64_t pid) {
    MODULEENTRY32 entry;
    ZeroMemory(&entry, sizeof(entry));
    entry.dwSize = sizeof(MODULEENTRY32);

    void* snap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid);
    if(snap == INVALID_HANDLE_VALUE) {
        printf("    Failed to get snapshot of modules: %lu.\n", GetLastError());
        CloseHandle(snap);
        return;
    }

    if(!Module32First(snap, &entry)) {
        printf("    Failed to get first module %lu.\n", GetLastError());
        CloseHandle(snap);
        return;
    }

    printf("    Dlls:\n");
    do {
        printf("      - %s\n", entry.szModule);
    } while(Module32Next(snap, &entry));

    CloseHandle(snap);
}

void printProcInfo(const uint64_t pid) {
    PROCESSENTRY32 entry;
    ZeroMemory(&entry, sizeof(entry));
    entry.dwSize = sizeof(PROCESSENTRY32);

    void* snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, pid);
    if(snap == INVALID_HANDLE_VALUE) {
        printf("  Failed to get snapshot: %lu.\n", GetLastError());
        CloseHandle(snap);
        return;
    }

    if(!Process32First(snap, &entry)) {
        printf("  Failed to get first process %lu.\n", GetLastError());
        CloseHandle(snap);
        return;
    }

    do {
        if(entry.th32ProcessID != pid && pid != 0)
            continue;
        printf("    Exe: %s\n", entry.szExeFile);
        printf("    Thread count: %lu\n", entry.cntThreads);
        printModsInfo(entry.th32ProcessID);
    } while(Process32Next(snap, &entry));

    CloseHandle(snap);
}

void printProcInfo() {
    printProcInfo(0);
}