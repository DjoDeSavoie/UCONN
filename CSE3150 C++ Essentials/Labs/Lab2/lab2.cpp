#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

void sortIntegersInFile(const std::string& inputFile, const std::string& outputFile) {
    std::vector<int> data;
    std::ifstream fileIn(inputFile);
    if (!fileIn) {
        std::cerr << "File error: " << inputFile << std::endl;
        return;
    }

    int value;
    while (fileIn >> value) {
        data.push_back(value);
    }
    fileIn.close();

    std::sort(data.begin(), data.end());

    std::ofstream fileOut(outputFile);
    if (!fileOut) {
        std::cerr << "File error: " << outputFile << std::endl;
        return;
    }

    for (const int& elem : data) {
        fileOut << elem << "\n";
    }
    fileOut.close();
    std::cout << "Done: " << outputFile << std::endl;
}

int main() {
    sortIntegersInFile("input.txt", "output.txt");
    return 0;
}
