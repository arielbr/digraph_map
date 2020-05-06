#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include "digraph.h"

using std::cout; using std::cin; using std::endl;
using std::string;
using std::vector;
using std::cerr;
using std::stringstream;
using std::map;
using std::ifstream;

/* This function reads the first int from a file and then reads that number
 * of strings that follow and stores them in a vector of digraphs.
 * param - file: file pointer
 */
vector<string> generate_digraph_list(ifstream& file) {
  //open and close in the main
  vector<string> digraphs;
  int num_dig;
  string next; //can i avoid this
  file >> num_dig;
  for (int i = 0; i < num_dig; i++) {
    file >> next;
    for (size_t j = 0; j < next.length(); j++) {
      next[j] = tolower(next[j]);
    }
    digraphs.push_back(next);
  }
  //cout << "reached gene...";
  return digraphs;
}

/* This function takes a string and initialize each digraph's appearances to
 * be zero, which will be updated later.
 * params - d: a list of digraphs to be searched
 */
map<string, int> d_appearance(vector<string> d) {
  map<string, int> d_freq_init;
  for(vector<string>::iterator it = d.begin();
      it != d.end();
      it++) {
    d_freq_init[*it] = 0;
  }
  return d_freq_init;
}

/* This function search the paragraph in the .txt file, and checks whether
 * each word contains any of the digraphs. If so it increments the counts
 * for appearances of digraphs. It returns a map whose key is the digraphs,
 * and values are all words containing the digraphs.
 * params - digraphs: the vector of digraphs to be ssearched from
 *          d_freq: a map of digraphs with initialized 0 freq
 *          file: file pointer
 */
map<string, vector<string>> search_para(vector<string> digraphs, map<string, int> d_freq, ifstream& file) {
  string word;
  map<string, vector<string>> words_with_d;
  size_t found_comma, found_excl, found_qnmark, found_period;
  //initialize the values of the map created with empty string vectors!!!! OK THIS IS IMPT WEW
  /*  for(vector<string>::iterator init_itr = digraphs.begin();
      init_itr != digraphs.end();
      init_itr++) {
    words_with_d[*init_itr] = vector<string>();
    }*/
  
  while(file >> word){
    //change to lower case
    for (size_t i = 0; i < word.length(); i++) {
      word[i] = tolower(word[i]);
    }
    //check if there is punctuation mark at the end
    found_comma = word.find(',');
    found_excl = word.find('!');
    found_qnmark = word.find('?');
    found_period = word.find('.');
    if (found_comma != string::npos || found_excl != string::npos || found_qnmark != string::npos || found_period != string::npos) {
      word = word.substr(0, word.length() - 1);
    }
    for (vector<string>::iterator it = digraphs.begin();
	 it != digraphs.end();
	 it++) {
      if (word.find(*it) != string::npos) {
	words_with_d[*it].push_back(word);
	d_freq[*it] += 1;
      }
    }
  }
  //check to make sure digraphs with zero appeearances are pushed in
  /*
  for (vector<string>::iterator itr = digraphs.begin();
       itr != digraphs.end();
       itr++) {
    if(words_with_d.find(*itr) == words_with_d.end()) {
      words_with_d[*itr].push_back("");
    }
  }
  */
  vector<string> empty;
  for (map<string, int>::iterator it = d_freq.begin();
       it != d_freq.end();
       it++) {
    if (it->second == 0) {
      words_with_d[it->first] = empty;
    }
  }
  
  return words_with_d;
}

/* This function takes a map of all digraphs with the words containing them,
 * and output a map whose key is the total number of appearances (int), and 
 * whose values are all digraphs with that number of appearances.
 * params - words_with_d: a map of all words in which digraphs appear
 */
map<int, vector<string>> word_count(map<string, vector<string>> words_with_d) {  //WRONG HERE
  map<int, vector<string>> d_by_count;
  int num_appearance;
  vector<string> empty;
  for (map<string, vector<string>>::iterator it = words_with_d.begin();
       it != words_with_d.end();
       it++) {
    if (it->second == empty) {
      d_by_count[0].push_back(it->first);
    }
    else {
      num_appearance = (int)it->second.size();
      d_by_count[num_appearance].push_back(it->first);
    }
  }
  return d_by_count;
}

/* This function outputs the digraphs and the words containing them in the desired order.
 * param - words: the map of digraph (keys), and the words containing it (values)
 *         counter: the map of number of appearances of digraphs(keys) with the digraphs(values)
 *         sequence: the order digraphs to be outputted, 'a' = normal, 'r' = reverse, 'c' = by count
 */
void output_digraph (map<string, vector<string>> words, map<int, vector<string>> counter, string seq) {
  //cout << "reached 1" << endl;
  string temp;
  vector<string> empty;
  if (seq == "a") {
    for (map<string, vector<string>>::iterator it_a = words.begin();
	 it_a != words.end();
	 it_a++) {
      cout << it_a->first << ": ["; // this statement went wrong
      if (!(words[it_a->first] == empty)) {
	for (vector<string>::iterator inner = it_a->second.begin();
	     inner != (it_a->second.end() - 1); //dk if right
	     inner++) {
	  cout << *inner << ", ";
	}
	cout << (it_a->second).back();
      }
      cout << "]" << endl;
      //cout << "reached." << endl;
    }
  } //This part is correct!!!!
  else if (seq == "r") {
    for (map<string, vector<string>>::reverse_iterator it_r = words.rbegin();
	 it_r != words.rend();
	 it_r++) {
      cout << it_r->first << ": [";
      if (!(words[it_r->first] == empty)) {
	for (vector<string>::iterator inner = it_r->second.begin();
	     inner != (it_r->second.end() - 1);
	     inner++) {
	  cout << *inner << ", ";
	}
	cout << (it_r->second).back();
      }
      cout << "]" << endl;
    }
    //cout << "check" << endl;
  }
  
  /*  else if (seq == "r") {
    for (map<string, vector<string>>::reverse_iterator it_r = words.rbegin();
	 it_r != words.rend();
	 it_r++) {
      cout << it_r->first << ": [";
      if (!(words[it_r->first] == empty)) {
	for (vector<string>::iterator inner = it_r->second.begin();
	     inner != (it_r->second.end() - 1);
	     inner++) {
	  cout << *inner << ", ";
	}
      }
      cout << (it_r->second).back();
    }
    cout << "]" << endl;
  }
  //cout << "check" << endl;
  */
 else if (seq == "c") {
   for (map<int, vector<string>>::reverse_iterator it_c = counter.rbegin();
	it_c != counter.rend();
	it_c++) {
     for(size_t i = 0; i < (it_c->second).size(); i++) {
       temp = (it_c->second)[i];
       cout << temp << ": [";
       if (!(words[temp] == empty)) {
	 for (vector<string>::iterator itr_words = words[temp].begin();
	      itr_words != (words[temp].end() - 1);
	      itr_words++) {
	   cout << *itr_words << ", ";
	 }
	 cout << words[temp].back();
       }
       cout <<  "]" << endl;
     }
   }
 }
}





/*
{
  map<int, vector<string>> word_freq;
  for(vector<string>::iterator it = counter.cbegin();
      it != counter.cend();
      it++) {
    word_freq[it->second].push_back(it->first);    
  }
  return word_freq;
}
*/





/* This is only for testing.
int main() {
  ifstream infile;
  infile.open("test.txt");
  vector<string> diags = generate_digraph_list(infile);
  for (vector<string>::iterator it = diags.begin();
       it != diags.end();
       it++) {
    cout << *it << endl;
  }
}
*/
