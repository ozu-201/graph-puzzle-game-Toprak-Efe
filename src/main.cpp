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

int get_difference(std::string str1_in, std::string str2_in) {
    int difference = 0;
    for (int i = 0; i < str1_in.length(); i++) {
        difference += (str1_in[i] == str2_in[i] ? 0 : 1);
    }
    return difference;
}

int main(int argc, char** argv) {
    std::vector<std::string> dictionary3;
    std::vector<std::string> dictionary4;
    std::vector<std::string> dictionary5;

    /* Read lines and add words to the vector. */
    std::ifstream dict_file;
    dict_file.open("C:\\Users\\ea033805\\CLionProjects\\graph-puzzle-game-Toprak-Efe\\dictionary.txt");
    if (dict_file.is_open()) {
        std::string word;
        while (std::getline(dict_file, word)) {
            switch (word.length()) {
                case 3:
                    dictionary3.push_back(word);
                    break;
                case 4:
                    dictionary4.push_back(word);
                    break;
                case 5:
                    dictionary5.push_back(word);
                    break;
            }
        }
    }
    dict_file.close();

    int dict3_len = dictionary3.size();
    int dict4_len = dictionary4.size();
    int dict5_len = dictionary5.size();

    /* Create the graphs for three cases. */
    list::Graph threeGraph(dictionary3.size());
    list::Graph fourGraph(dictionary4.size());
    list::Graph fiveGraph(dictionary5.size());

    /* Correspond edges between elements in dictionary and store them in the corresponding graph. */
    for (int i = 0; i < dict3_len; i++) {
        for (int j = i + 1; j < dict3_len; j++) {
            if (get_difference(dictionary3[i], dictionary3[j]) == 1) {
                threeGraph.addEdge(i, j);
                threeGraph.addEdge(j, i);
            }
        }
    }
    for (int i = 0; i < dict4_len; i++) {
        for (int j = i + 1; j < dict4_len; j++) {
            if (get_difference(dictionary4[i], dictionary4[j]) == 1) {
                fourGraph.addEdge(i, j);
                fourGraph.addEdge(j, i);
            }
        }
    }
    for (int i = 0; i < dict5_len; i++) {
        for (int j = i + 1; j < dict5_len; j++) {
            if (get_difference(dictionary5[i], dictionary5[j]) == 1) {
                fiveGraph.addEdge(i, j);
                fiveGraph.addEdge(j, i);
            }
        }
    }

    // Generate two indices for dictionary 4.
    srand(123);
    int start = 1; //rand() % dict3_len;
    int goal = 10; //rand() % dict3_len;

    std::cout << "Starting Word: " << dictionary3[start] << std::endl;
    std::cout << "Ending Word: " << dictionary3[goal] << std::endl;
    threeGraph.getPathBreadth(dictionary3, start, goal);
    threeGraph.getPathDijkstra(dictionary3, start, goal);

    return 0;
}