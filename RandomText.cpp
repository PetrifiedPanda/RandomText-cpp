#include "RandomText.h"

#include <random>
#include <ctime>


namespace random_text {

constexpr size_t VOWELS_SIZE = 5;
constexpr size_t CONSONANTS_SIZE = 21;
constexpr size_t LETTERS_SIZE = 26;

constexpr char VOWELS[VOWELS_SIZE] = {'a', 'e', 'i', 'o', 'u'};
constexpr char CONSONANTS[CONSONANTS_SIZE] = {'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 'n', 'p', 'q', 'r', 's', 't', 'v', 'w', 'x', 'y', 'z'};

constexpr char LETTERS[LETTERS_SIZE] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

std::default_random_engine engine(time(nullptr));

bool is_consonant(char c) {
    for (char cons : CONSONANTS)
        if (c == cons)
            return true;
    return false;
}

bool is_vowel(char c) {
    for (char vowel : VOWELS)
        if (c == vowel)
            return true;
    return false;
}

char get_successor(char prev_char, bool start = false) {
    if (start) {
        std::uniform_int_distribution<size_t> dist(0, LETTERS_SIZE - 1);
        return LETTERS[dist(engine)];
    } else if (is_consonant(prev_char)) {
        std::uniform_int_distribution<size_t> dist(0, VOWELS_SIZE - 1);
        return VOWELS[dist(engine)];
    } else {
        std::uniform_int_distribution<size_t> dist(0, LETTERS_SIZE - 1);
        char next = prev_char;
        while (next == prev_char)
            next = LETTERS[dist(engine)];

        return next;
    }
}

void generate_word_to_string(std::string& str, size_t start, size_t length) {
    str[start] = get_successor('0', true);

    size_t end = start + length;
    for (size_t i = start + 1; i < end; ++i)
        str[i] = get_successor(str[i - 1]);
}

std::string generate_word(size_t length) {
    std::string result(length, '0');
    generate_word_to_string(result, 0, length);
    return result;
}

// Generates the sizes of the words for a sentence and computes the total size of the string to avoid multiple reallocations
std::pair<std::vector<size_t>, size_t> generate_word_sizes(size_t min_words, size_t max_words) {
    std::uniform_int_distribution<size_t> num_words_dist(min_words, max_words);
    std::uniform_int_distribution<size_t> size_dist(3, 10);

    size_t num_words = num_words_dist(engine);
    std::vector<size_t> word_sizes(num_words);
    size_t string_size = 0;
    for (size_t i = 0; i < num_words; ++i) {
        size_t word_size = size_dist(engine);
        string_size += word_size + 1;
        word_sizes[i] = word_size;
    }

    return std::make_pair(std::move(word_sizes), string_size);
}

void generate_sentence_to_string(std::string& string, size_t start, const std::vector<size_t>& word_sizes, size_t result_size) {
    std::uniform_int_distribution<int> percent_dist(1, 100);

    size_t index = start;
    for (size_t i = 0; i < word_sizes.size(); ++i) {
        generate_word_to_string(string, index, word_sizes[i]);
        index += word_sizes[i] + 1;
    }

    string[start] = toupper(string[start]);

    if (percent_dist(engine) > 20)
        string[start + result_size - 1] = '.';
    else
        string[start + result_size - 1] = '!';
}

std::string generate_sentence(size_t min_words, size_t max_words) {
    std::uniform_int_distribution<int> percent_dist(1, 100);

    auto [word_sizes, result_size] = generate_word_sizes(min_words, max_words);
    size_t num_words = word_sizes.size();

    std::string result(result_size, ' ');
    generate_sentence_to_string(result, 0, word_sizes, result_size);

    return result;
}

std::string generate_text(size_t num_sentences, size_t min_words_in_sentence, size_t max_words_in_sentence) {
    // Generate all the sizes before allocating the string
    std::vector<std::pair<std::vector<size_t>, size_t>> sentence_sizes(num_sentences);

    size_t result_length = 0;
    for (size_t i = 0; i < num_sentences; ++i) {
        sentence_sizes[i] = generate_word_sizes(min_words_in_sentence, max_words_in_sentence);
        result_length += sentence_sizes[i].second + 1;
    }

    std::uniform_int_distribution<int> percent_dist(1, 100);
    std::string result(result_length, ' ');

    size_t index = 0;
    for (size_t i = 0; i < num_sentences; ++i) {
        generate_sentence_to_string(result, index, sentence_sizes[i].first, sentence_sizes[i].second);
        index += sentence_sizes[i].second + 1;

        if (percent_dist(engine) > 30)
            result[index - 1] = ' ';
        else
            result[index - 1] = '\n';
    }

    return result;
}

}; // namespace random_text