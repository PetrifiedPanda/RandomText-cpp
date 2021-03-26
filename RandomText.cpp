#include "RandomText.h"

#include <random>

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

char randomText::getSuccessor(char prevChar, bool start) {
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

std::string randomText::getRandomWord(size_t length) {
    std::string result(length, '0');
    result[0] = getSuccessor('0', true);

    for (size_t i = 1; i < length; ++i)
        result[i] = getSuccessor(result[i - 1]);

    return result;
}

std::string randomText::generateSentence(size_t minWords, size_t maxWords) {
    std::uniform_int_distribution<size_t> numWordsDist(minWords, maxWords);
    std::uniform_int_distribution<size_t> sizeDist(3, 10);
    std::uniform_int_distribution<int> percentDist(1, 100);
    size_t numWords = numWordsDist(engine);

    std::string result("");
    for (size_t i = 0; i < numWords; ++i) {
        result += getRandomWord(sizeDist(engine));

        if (i != numWords - 1)
            result += " ";
    }

    if (percentDist(engine) > 20)
        result += "!";
    else
        result += ".";

    return result;
}

std::string randomText::generateText(size_t numSentences, size_t minWordsPerSentence, size_t maxWordsPerSentence) {
    std::uniform_int_distribution<int> percentDist(1, 100);

    std::string text("");

    for (size_t i = 0; i < numSentences; ++i) {
        text += generateSentence(minWordsPerSentence, maxWordsPerSentence);

        if (percentDist(engine) > 30)
            text += " ";
        else
            text += "\n";
    }

    return text;
}