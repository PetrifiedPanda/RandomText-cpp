#include <string>

namespace randomText {
char getSuccessor(char prevChar, bool start = false);

std::string getRandomWord(size_t length);

std::string generateSentence(int minWords, int maxWords);

std::string generateText(int numSentences, int minWordsPerSentence = 3, int maxWordsPerSentence = 10);
};  // namespace randomText
