#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype> 

// Function to convert a string to lowercase
std::string toLowerCase(const std::string& str) {
    std::string lowerStr = str;
    for (char& ch : lowerStr) {
        ch = std::tolower(ch);
    }
    return lowerStr;
}

// Function to read spam words from a file and convert them to lowercase
std::vector<std::string> readSpamWords(const std::string& filename) {
    std::vector<std::string> spamWords;
    std::ifstream file(filename);
    std::string word;

    // Read each word from the file, convert it to lowercase, and add it to the spamWords vector
    while (file >> word) {
        spamWords.push_back(toLowerCase(word));
    }

    file.close();
    return spamWords;
}

// Function to check if a message contains any spam words
bool isSpam(const std::string& message, const std::vector<std::string>& spamWords) {
    std::string lowerMessage = toLowerCase(message); // Convert the message to lowercase
    for (const auto& spamWord : spamWords) {
        // Check if the spam word is found in the message
        if (lowerMessage.find(spamWord) != std::string::npos) {
            return true; // Message is spam
        }
    }
    return false; // Message is not spam
}

// Function to check messages from a list of filenames for spam
void checkMessagesForSpam(const std::vector<std::string>& spamWords, const std::vector<std::string>& filenames) {
    for (const auto& filename : filenames) {
        std::ifstream file("messages/" + filename); // Read file from the "messages" folder
        if (!file.is_open()) {
            std::cerr << "Error: Could not open file " << filename << std::endl;
            continue; // Skip to the next file
        }

        std::string message;
        std::getline(file, message, '\0'); // Read the entire file as a single message

        // Check if the message contains any spam words
        if (isSpam(message, spamWords)) {
            std::cout << "Spam detected in file: " << filename << std::endl;
        } else {
            std::cout << "Not spam in file: " << filename << std::endl;
        }

        file.close();
    }
}

int main() {
    // Load spam words from a file
    std::vector<std::string> spamWords = readSpamWords("spam-words-EN.txt");

    // List of filenames in the "messages" folder
    std::vector<std::string> filenames = {
        "message1.txt",
        "message2.txt",
        "message3.txt",
        "message4.txt",
        "message5.txt",
        "longmessage.txt",
        "shortmessage.txt"
    };

    // Check each message file for spam
    checkMessagesForSpam(spamWords, filenames);

    return 0;
}