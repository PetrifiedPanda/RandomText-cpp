#include <fstream>
#include <iostream>

#include <RandomText.h>

void generateTextToFile(const std::string& filename, int num_sentences, int min_words_in_sentence = 3, int max_words_in_sentence = 10);

int main() {
    generateTextToFile("Gibberish.txt", 100000);
}

void generateTextToFile(const std::string& filename, int num_sentences, int min_words_in_sentence, int max_words_in_sentence) {
    std::string text = random_text::generate_text(num_sentences, min_words_in_sentence, max_words_in_sentence);
    std::ofstream file(filename, std::fstream::app);

    file << text;
}