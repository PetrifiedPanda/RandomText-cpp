#include <string>

namespace random_text {
    std::string generate_word(size_t length);

    std::string generate_sentence(size_t min_words, size_t max_words);

    std::string generate_text(size_t num_sentences, size_t min_words_in_sentence = 3, size_t max_words_in_sentence = 10);
};
