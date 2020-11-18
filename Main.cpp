#include <fstream>
#include <iostream>

#include "RandomText.h"

void generateTextToFile(const std::string& filename, int numSentences, int minWordsPerSentence = 3, int maxWordsPerSentence = 10);

int main() {
    generateTextToFile("Gibberish.txt", 100000);
}

void generateTextToFile(const std::string& filename, int numSentences, int minWordsPerSentence, int maxWordsPerSentence) {
    std::string text = randomText::generateText(numSentences, minWordsPerSentence, maxWordsPerSentence);
    std::ofstream file(filename, std::fstream::app);

    file << text;
}