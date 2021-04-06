#include "RandomText.h"

#include <random>
#include <ctime>

constexpr size_t c_vowelsSize = 5;
constexpr size_t c_consonantsSize = 21;
constexpr size_t c_lettersSize = 26;

constexpr char c_vowels[c_vowelsSize] = {'a', 'e', 'i', 'o', 'u'};
constexpr char c_consonants[c_consonantsSize] = {'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 'n', 'p', 'q', 'r', 's', 't', 'v', 'w', 'x', 'y', 'z'};

constexpr char c_letters[c_lettersSize] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

std::default_random_engine engine(time(nullptr));

bool isConsonant(char c) {
    for (char cons : c_consonants)
        if (c == cons)
            return true;
    return false;
}

bool isVowel(char c) {
    for (char vowel : c_vowels)
        if (c == vowel)
            return true;
    return false;
}

char getSuccessor(char prevChar, bool start = false) {
    if (start) {
        std::uniform_int_distribution<size_t> dist(0, c_lettersSize - 1);
        return c_letters[dist(engine)];
    } else if (isConsonant(prevChar)) {
        std::uniform_int_distribution<size_t> dist(0, c_vowelsSize - 1);
        return c_vowels[dist(engine)];
    } else {
        std::uniform_int_distribution<size_t> dist(0, c_lettersSize - 1);
        char next = prevChar;
        while (next == prevChar)
            next = c_letters[dist(engine)];

        return next;
    }
}

void generateWordToString(std::string& str, size_t start, size_t length) {
    str[start] = getSuccessor('0', true);

    size_t end = start + length;
    for (size_t i = start + 1; i < end; ++i)
        str[i] = getSuccessor(str[i - 1]);
}

std::string randomText::generateWord(size_t length) {
    std::string result(length, '0');
    generateWordToString(result, 0, length);
    return result;
}

// Generates the sizes of the words for a sentence and computes the total size of the string to avoid multiple reallocations
std::pair<std::vector<size_t>, size_t> generateWordSizes(size_t minWords, size_t maxWords) {
    std::uniform_int_distribution<size_t> numWordsDist(minWords, maxWords);
    std::uniform_int_distribution<size_t> sizeDist(3, 10);

    size_t numWords = numWordsDist(engine);
    std::vector<size_t> wordSizes(numWords);
    size_t stringSize = 0;
    for (size_t i = 0; i < numWords; ++i) {
        size_t wordSize = sizeDist(engine);
        stringSize += wordSize + 1;
        wordSizes[i] = wordSize;
    }

    return std::make_pair(std::move(wordSizes), stringSize);
}

void generateSentenceToString(std::string& string, size_t start, const std::vector<size_t>& wordSizes, size_t resultSize) {
    std::uniform_int_distribution<int> percentDist(1, 100);

    size_t index = start;
    for (size_t i = 0; i < wordSizes.size(); ++i) {
        generateWordToString(string, index, wordSizes[i]);
        index += wordSizes[i] + 1;
    }

    string[start] = toupper(string[start]);

    if (percentDist(engine) > 20)
        string[start + resultSize - 1] = '.';
    else
        string[start + resultSize - 1] = '!';
}

std::string randomText::generateSentence(size_t minWords, size_t maxWords) {
    std::uniform_int_distribution<int> percentDist(1, 100);

    auto [wordSizes, resultSize] = generateWordSizes(minWords, maxWords);
    size_t numWords = wordSizes.size();

    std::string result(resultSize, ' ');
    generateSentenceToString(result, 0, wordSizes, resultSize);

    return result;
}

std::string randomText::generateText(size_t numSentences, size_t minWordsPerSentence, size_t maxWordsPerSentence) {
    // Generate all the sizes before allocating the string
    std::vector<std::pair<std::vector<size_t>, size_t>> sentenceSizes(numSentences);

    size_t resultLength = 0;
    for (size_t i = 0; i < numSentences; ++i) {
        sentenceSizes[i] = generateWordSizes(minWordsPerSentence, maxWordsPerSentence);
        resultLength += sentenceSizes[i].second + 1;
    }

    std::uniform_int_distribution<int> percentDist(1, 100);
    std::string result(resultLength, ' ');

    size_t index = 0;
    for (size_t i = 0; i < numSentences; ++i) {
        generateSentenceToString(result, index, sentenceSizes[i].first, sentenceSizes[i].second);
        index += sentenceSizes[i].second + 1;

        if (percentDist(engine) > 30)
            result[index - 1] = ' ';
        else
            result[index - 1] = '\n';
    }

    return result;
}