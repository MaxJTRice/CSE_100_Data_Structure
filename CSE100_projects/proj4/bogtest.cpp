/******************************************************
 * Tester file to test basic functionality of your code
 * ****************************************************/

#include "baseboggleplayer.h"
#include "boggleplayer.h"
#include "boggleplayer.cpp"     //shan
#include "boggleutil.h"
#include "boggleutil.cpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>

int main (int argc, char* argv[]) {

  BogglePlayer * p = new BogglePlayer();
  //test getAllValid

   set<string> lex;
   string line;
  std::ifstream fword("lex.txt",ios::binary);
  while(fword.good()){
    std::getline(fword,line);
    lex.insert(line);
  }
  fword.close();
   p->buildLexicon(lex);

   std::ifstream f("brd.txt",ios::binary);
   // int row=0;
   // int col=0;
   std::getline(f,line);
   //row=std::stoi(line);
   std::getline(f,line);
   //col=std::stoi(line);

 string brd[20][23];
   for(int i=0;i<20;i++){
     for(int j=0;j<23;j++){
       std::getline(f,line);
       brd[i][j]=line;
     }
   }
   f.close();
   string* bd[20];
   for(int i=0;i<20;i++){
     bd[i]=brd[i];
   }
   p->setBoard(20,23,bd);
//   for(int i=0;i<20;i++){
//     for(int j=0;j<23;j++){
//       cout << p->board[i*23+j].letter<<" ";
//     }
//     cout<<endl;
//   }
//   std::vector<int> v;
//   v= p->isOnBoard("acidified");
//   for(int i=0;i<v.size();i++){
//     cout<<v[i]<<endl;
//   }
  //cout << "size " << p->isOnBoard("acidified").size() <<endl;
  // string wordA("a");
  // string wordX("x");
  // lex.insert(wordA);
  // lex.insert("aba");
//  string row0[] = {"w"};
//  string row1[] = {"e"};
//  string row2[] = {"r"};
//  string row3[] = {"e"};
//  string* board[] = {row0,row1,row2,row3};
//  set<string> words;
//  // vector<int> locations;

//  //p->buildLexicon(lex);
//  //cout << "build" << endl;

//  p->setBoard(4,1,board);
  // // for(int i=0;i<4;i++){
  // //   cout << p->board[i].letter << endl;
  // // }

  // if(p->isOnBoard("aba").size() == 3){
  //   cout << "found" << endl;
  // }

  // if(p->isInLexicon(wordX)) {
  //   std::cerr << "Apparent problem with isInLexicon #1." << std::endl;
  //   return -1;
  // }
  // if(!p->isInLexicon(wordA)) {
  //   std::cerr << "Apparent problem with isInLexicon #2." << std::endl;
  //   return -1;
  // }

  // if(p->isOnBoard(wordA).size() != 1) {
  //   std::cerr << "Apparent problem with isOnBoard #1." << std::endl;
  //   return -1;
  // }

  // locations.clear();
  // locations = p->isOnBoard(wordA);
  // if(locations.size() != 1 || locations[0] != 3) {
  //   std::cerr << "Apparent problem with isOnBoard #2." << std::endl;
  //   return -1;
  // }
  
  
  // if(!p->getAllValidWords(0,&words)) {
  //   std::cerr << "Apparent problem with getAllValidWords #1." << std::endl;
  //   return -1;
  // }
  // if(words.size() != 1 || words.count(wordA) != 1) {
  //   std::cerr << "Apparent problem with getAllValidWords #2." << std::endl;
  //   return -1;
  // }
  set<string> words;
  p->getAllValidWords(2,&words);
  int j=0;
  for (std::set<string>::iterator it = words.begin() ; it != words.end(); ++it){
             j++;
             cout<<j<< " valid words "<<*it<<endl;
           }
  cout<<"total number"<<words.size()<<endl;

  delete p;
  return 0;

}
