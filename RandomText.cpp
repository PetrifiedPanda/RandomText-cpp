#include "RandomText.h"

#include <random>

constexpr size_t vowelsSize = 5;
constexpr size_t consonantsSize = 21;
constexpr size_t lettersSize = 26;

constexpr char vowels[vowelsSize] = {'a', 'e', 'i', 'o', 'u'};
constexpr char consonants[consonantsSize] = {'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 'n', 'p', 'q', 'r', 's', 't', 'v', 'w', 'x', 'y', 'z'};

constexpr char letters[lettersSize] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

std::default_random_engine engine(time(nullptr));

bool isConsonant(char c) {
    for (char cons : consonants)
        if (c == cons)
            return true;
    return false;
}

bool isVowel(char c) {
    for (char vowel : vowels)
        if (c == vowel)
            return true;
    return false;
}

char randomText::getSuccessor(char prevChar, bool start) {
    if (start) {
        std::uniform_int_distribution<size_t> dist(0, lettersSize - 1);
        return letters[dist(engine)];
    } else if (isConsonant(prevChar)) {
        std::uniform_int_distribution<size_t> dist(0, vowelsSize - 1);
        return vowels[dist(engine)];
    } else {
        std::uniform_int_distribution<size_t> dist(0, lettersSize - 1);
        char next = prevChar;
        while (next == prevChar)
            next = letters[dist(engine)];

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

std::string randomText::generateSentence(int minWords, int maxWords) {
    std::uniform_int_distribution<int> numWordsDist(minWords, maxWords);
    std::uniform_int_distribution<size_t> sizeDist(3, 10);
    std::uniform_int_distribution<int> percentDist(1, 100);
    size_t numWords = numWordsDist(engine);

    std::string result("");
    for (int i = 0; i < numWords; ++i) {
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

std::string randomText::generateText(int numSentences, int minWordsPerSentence, int maxWordsPerSentence) {
    std::uniform_int_distribution<int> percentDist(1, 100);

    std::string text("");

    for (int i = 0; i < numSentences; ++i) {
        text += generateSentence(minWordsPerSentence, maxWordsPerSentence);

        if (percentDist(engine) > 30)
            text += " ";
        else
            text += "\n";
    }

    return text;
}