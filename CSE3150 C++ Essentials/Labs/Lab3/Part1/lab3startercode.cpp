#include <iostream>
#include <string>

// Function to reverse a string using pointers
void reverseString(char* str) {
    // Pointers to the beginning and end of the string
    char* start = str;
    char* end = str;

    // Move "end" to the last character of the string
    while (*end != '\0') {
        end++;
    }
    end--; // Move back from the null terminator to the last character

    // Swap characters until start and end meet
    while (start < end) {
        // Store the last character in a temporary variable
        char temp = *end;
        *end = *start;
        *start = temp;

        // Move the pointers
        start++;
        end--;
    }
}

int main() {
    char str[] = "maman";

    std::cout << "Original string: " << str << std::endl;

    // Reverse the string
    reverseString(str);
    std::cout << "Reversed string: " << str << std::endl;

    return 0;
}