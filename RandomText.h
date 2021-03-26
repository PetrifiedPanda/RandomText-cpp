#include <string>

namespace randomText {
    char getSuccessor(char prevChar, bool start = false);

    std::string getRandomWord(size_t length);

    std::string generateSentence(size_t minWords, size_t maxWords);

    std::string generateText(size_t numSentences, size_t minWordsPerSentence = 3, size_t maxWordsPerSentence = 10);
};
