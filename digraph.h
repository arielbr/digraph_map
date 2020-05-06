#ifndef DIGRAPH_H
#define DIGRAPH_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <cstring>
#include <cctype>

std::vector<std::string> generate_digraph_list(std::ifstream& file);
std::map<std::string, int> d_appearance(std::vector<std::string> d);
std::map<std::string, std::vector<std::string>> search_para(std::vector<std::string> digraphs, std::map<std::string, int> d_freq, std::ifstream& file);
std::map<int, std::vector<std::string>> word_count(std::map<std::string, std::vector<std::string>> words_with_d);
void output_digraph (std::map<std::string, std::vector<std::string>> words, std::map<int, std::vector<std::string>> counter, std::string seq);
	
#endif /* DIGRAPH_H */
