//
// Created by ea033805 on 12/14/2023.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <utility>
#include "List\Graph\Graph.h"

typedef std::pair<std::string, int> WordPair;

int main(int argc, char** argv) {
    std::vector<std::pair<std::string, int>> dictionary3;
    std::vector<std::pair<std::string, int>> dictionary4;
    std::vector<std::pair<std::string, int>> dictionary5;

    /* Read lines and add words to the vector. */
    std::ifstream dict_file;
    dict_file.open("dictionary.txt");
    if (dict_file.is_open()) {
        while (true) {
            std::string word;
            std::getline(dict_file, word);
            switch (word.length()) {
                case 3:
                    dictionary3.push_back(std::move(WordPair(word, word.length())));
                    break;
                case 4:
                    dictionary4.push_back(std::move(WordPair(word, word.length())));
                    break;
                case 5:
                    dictionary5.push_back(std::move(WordPair(word, word.length())));
                    break;
            }
        }
    }
    dict_file.close();

    /* Create the graphs for three cases. */
    list::Graph threeGraph(dictionary3.size());
    list::Graph fourGraph(dictionary3.size());
    list::Graph fiveGraph(dictionary3.size());

    /* Correspond edges between elements in dictionary and store them in the corresponding graph. */

    return 0;
}