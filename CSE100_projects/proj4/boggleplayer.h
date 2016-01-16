#ifndef BOGGLEPLAYER_H
#define BOGGLEPLAYER_H
#include "baseboggleplayer.h"
#include "boggleutil.h"
#include <vector>
#include <string>
#include <set>
using namespace std;

class BogglePlayer : public BaseBogglePlayer {
private:
  unsigned int num_row;
  unsigned int num_col;
  bool boardSet;
  bool lexiconBuild;
  Trie *buildTrie;
  vector<BoardPos*> board;
  void onBoard(vector<BoardPos*> board_1, int start, string word, vector<int> & result, int rows, int cols);
  void addOne(vector<BoardPos*> board_1, int start, unsigned int min_length, set<string>* & words, int rows, int cols);
  vector<int> neighbour(int rows, int cols, int curr);
public:
    BogglePlayer(){
      num_row=0;
      num_col=0;
      boardSet=false;
      lexiconBuild=false;
      buildTrie=0;
  }

  //~BogglePlayer();

  void buildLexicon(const set<string>& word_list);
  
  void setBoard(unsigned int rows, unsigned int cols, string** diceArray); 

  bool getAllValidWords(unsigned int minimum_word_length, set<string>* words);
  
  bool isInLexicon(const string& word_to_check); 

  vector<int> isOnBoard(const string& word);

  void getCustomBoard(string** &new_board, unsigned int *rows, unsigned int *cols);



  ~BogglePlayer(){
      if(buildTrie!=0){
          delete buildTrie;
          buildTrie=0;
      }
      if(!board.empty()){
          vector<BoardPos*>temp=board;
          board.swap(temp);
      }
  }

//  void onBoard(vector<BoardPos*> board_1, int start, string word, vector<int> result, int rows, int cols);

//  void addOne(vector<BoardPos*> board_1, int start, unsigned int min_length, set<string>* words, int rows, int cols);

//  vector<int> neighbour(int rows, int cols, int curr);

};

#endif
