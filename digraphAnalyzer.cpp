#include <iostream>
#include <fstream>
#include "digraph.h"
#include <string>
#include <cstring>
#include <cctype>
#include <map>
#include <vector>
//#include <sstream>

using std::cout;   using std::endl;
using std::cerr;   using std::cin;
//using std::ifstream;
using std::stringstream;
using std::string;
using std::vector;
using std::map;
using std::ifstream;

/* This function outputs the digraphs and the words containing them in the desired order.
 * param - words: the map of digraph (keys), and the words containing it (values)
 *         counter: the map of number of appearances of digraphs(keys) with the digraphs(values)
 *         sequence: the order digraphs to be outputted, 'a' = normal, 'r' = reverse, 'c' = by count
 */

int main (int argc, char* argv[]) {
  //check the std inputs for validity
  //TODO: think of other possible invalidity, eg argv[1] is a num??
  string order = argv[2];
  if (argc != 3 || ((strcmp(argv[2], "r") != 0 && strcmp(argv[2], "c") != 0 && strcmp(argv[2], "a") != 0))) {
      cout << "invalid arguments." << endl;
      return 1;
  }
  ifstream inf(argv[1]);
  if(!inf.is_open()) {
    cout << "Invalid file." << endl;
    return 2;
  }

  //open file           //HOW TO OPEN inf if it is initialized??
  ifstream infile;
  infile.open(argv[1]);
  // to generate a list of digraphs to be searched from the first part of infile
  vector<string> digraphs;
  digraphs = generate_digraph_list(infile);
  
  //to generate a map of strings and their appearace #s and initialize the latter to 0 for all
  map<string, int> d_freq_init;
  d_freq_init = d_appearance(digraphs);
  // This func is checked, and works well
  
  // to search through the rest of the infile and extract all words containing
  // the digraphs, with punctuations removed.

  map<string, vector<string>> digraph_words;
  digraph_words = search_para(digraphs, d_freq_init, infile);
    // The following is to test print outcome
  
  
  // to generate a map of # of appearances with corresponding digraphs
  map<int, vector<string>> counter;
  counter = word_count(digraph_words);
  // another test
  
  
  //output digraphs with the words containing them, and ask for use input
  output_digraph(digraph_words, counter, order);
  cout << "q?>";
  
  // to extract command line input from user and generate menu
  string choice;
  cin >> choice;  
  do {
    // choice is "quit"
    if (choice.compare("quit") == 0) {
      return 0;      //TODO
    }
    // choice is an int
    else if (isdigit(choice.at(0))) {
      int num_search = (int)stoi(choice);
      if (counter.find(num_search) != counter.end()) {
	for (size_t i = 0; i < counter[num_search].size(); i++) {
	  vector<string> temp = counter[num_search];
	  cout << temp[i] << endl;
	  for (vector<string>::iterator it = digraph_words[temp[i]].begin();
	       it != digraph_words[temp[i]].end();
	       it++)
	    cout << *it << endl; 
	}
      }      	     
      else {
	cout << "None" << endl;
      }
    }
    // choice is a string ie a digraph
    else {
      for(size_t i = 0; i < choice.length(); i++) {
	choice[i] = tolower(choice[i]);	
      }
      if (digraph_words.find(choice) != digraph_words.end()) {
	cout << digraph_words[choice].size() << endl;
	vector<string> temp = digraph_words[choice];
	for (size_t j = 0; j < digraph_words[choice].size(); j++) {
	  cout << temp[j] << endl;
	}
      } 
      else {
	cout << "No such digraph" << endl;
      }
    }
    
    cout << "q?>";
  } while (cin >> choice);

  infile.close();
  return 0;
}
