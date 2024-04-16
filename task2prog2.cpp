#include <cstdint>
#include <fstream>
#include <unistd.h>

#include "procinfo.hpp"

constexpr char FILENAMES[3][64] = {"file1.txt", "file2.txt", "file3.txt"};

void printStatsForFile(const char* filename) {
    printf("File: %s\n", filename);

    uint32_t lines = 1;
    uint32_t currentLength = 0;

    std::ifstream file(filename, std::ios::binary);
    file.seekg(0, std::ios::end);
    printf("  File size: %lld\n", static_cast<long long>(file.tellg()));
    file.seekg(0);
    file.clear();

    char curChar;
    while (file.read(&curChar, 1)) {
        if(curChar == 0x0a) {
            printf("    Line #%d length: %d\n", lines, currentLength);
            lines++;
            currentLength = 0;
            continue;
        }

        if ((curChar & 0b11000000) == 0b11000000) {
            int numBytes;
            for (numBytes = 1; numBytes <= 4; ++numBytes)
                if (!(curChar & 0b10000000 >> numBytes))
                    break;

            for (int i = 1; i < numBytes && file.read(&curChar, 1); ++i) {}
        }

        currentLength++;
    }

    printf("    Line #%d length: %d\n", lines, currentLength);
    printf("  Number of lines: %d\n", lines);

    file.close();
}

int main() {
    printf("\nProcess (program 2) info:\n");
    printProcInfo(getpid());
    printf("\n");

    for(auto& filename : FILENAMES) {
        printStatsForFile(filename);
    }
}
