#include "boggleplayer.h"
#include "boggleutil.h"
#include "baseboggleplayer.h"
#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>
#include <vector>
#include <stack>
#include <fstream>

using namespace std;

//BogglePlayer::BogglePlayer(){
//    num_row=0;
//    num_col=0;
//    boardSet=false;
//    lexiconBuild=false;
//    buildTrie=0;
//}

//BogglePlayer::~BogglePlayer(){
//    if(buildTrie!=0){
 //       delete buildTrie;
 //       buildTrie=0;
 //   }
 //   if(!board.empty()){
 //       vector<BoardPos*>temp=board;
//        board.swap(temp);
//    }
//}

void BogglePlayer::buildLexicon(const set<string>& word_list){
	lexiconBuild=true;
	buildTrie=new Trie();
	buildTrie->build(word_list);
}

void BogglePlayer::setBoard(unsigned int rows, unsigned int cols, string** diceArray) {
	boardSet=true;
	num_row=rows;
	num_col=cols;
        for(unsigned int i=0;i<rows;i++){
                for(unsigned int j=0;j<cols;j++){
			string curr_string=diceArray[i][j];
			transform(curr_string.begin(),curr_string.end(),curr_string.begin(),::tolower);
			BoardPos* curr_pos=new BoardPos(curr_string);
			int temp=cols*i+j;
			curr_pos->setPos(temp);
			board.push_back(curr_pos);
		}
	}
//        cout<<"print setboard: "<<endl;
//        for(unsigned int i=0;i<board.size();i++){
//            cout<<board[i]->getText()<<endl;
//        }
}

bool BogglePlayer::getAllValidWords(unsigned int minimum_word_length, set<string>* words) {
	if((!this->lexiconBuild)||(!this->boardSet))return false;
	int sum=this->board.size();
	for(int i=0;i<sum;i++){
		addOne(board,i,minimum_word_length,words,num_row,num_col);
	}
	return true;
}

bool BogglePlayer::isInLexicon(const string& word_to_check) {
	TrieNode* endnode=0;
	//this->endnode=0;
	if(!this->lexiconBuild)return false;
	//if(!buildTrie->find(word_to_check))return false;
	bool result=false;
	if(buildTrie->find(word_to_check,buildTrie->getRoot(),endnode)){
		if(endnode!=0&&endnode->getEnd()){
			result=true;
		}
	}
	//this->endnode=0;
        //if(endnode!=0)cout<<"whether reach the end: "<<endnode->getEnd()<<endl;
	return result;
}

vector<int> BogglePlayer::isOnBoard(const string& word) {
	vector<int> result;
	if(this->boardSet){
		int sum=this->board.size();
		for(int i=0;i<sum;i++){
			onBoard(board,i,word,result,num_row,num_col);
			if(!result.empty())break;
		}
	}
	return result;
}


void BogglePlayer::getCustomBoard(string** &new_board, unsigned int *rows, unsigned int *cols) {

}

void BogglePlayer::onBoard(vector<BoardPos*> board_1, int start, string word, vector<int> & result, int rows, int cols){
	stack<BoardPos*>s;
        unsigned int pos=0;
        for(unsigned int i=0;i<board_1.size();i++){
                board_1[i]->setVisited(false);
                board_1[i]->setRevisited(false);
	}
        s.push(board_1[start]);
	while(!s.empty()){
                BoardPos* curr=s.top();
                s.pop();
		int curr_length=curr->getText().size();
		if(curr->getRevisited()){
			curr->setRevisited(false);
			curr->setVisited(false);
			pos=pos-curr_length;
			result.pop_back();
		}
		else if(!curr->getVisited()){
                        if((word.size()>=curr_length+pos)&&(curr->getText().compare(0,curr_length,word,pos,curr_length)==0)){
                                //cout<<"print element pass board test: "<<curr->getText()<<endl;
				curr->setVisited(true);
				result.push_back(curr->getPos());
				pos=pos+curr_length;
				if(pos==word.size()){
					return;
				}
				curr->setRevisited(true);
				s.push(curr);
                                vector<int> neigh=neighbour(rows,cols,curr->getPos());
                                for(unsigned int i=0;i<neigh.size();i++){
                                        int temp=neigh[i];
                                        if(!board_1[temp]->getVisited()){
                                                s.push(board_1[temp]);
					}
				}
			}
		}
	}
}

void BogglePlayer::addOne(vector<BoardPos*> board_1, int start, unsigned int min_length, set<string>* & words, int rows, int cols){
	stack<BoardPos*>s;
	TrieNode* endnode=buildTrie->getRoot();
        for(unsigned int i=0;i<board_1.size();i++){
                board_1[i]->setVisited(false);
                board_1[i]->setRevisited(false);
	}
        s.push(board_1[start]);
	string toAdd;
	while(!s.empty()){
                BoardPos* curr=s.top();
                s.pop();
		int curr_length=curr->getText().size();
		if(curr->getRevisited()){
			curr->setRevisited(false);
			curr->setVisited(false);
                        toAdd.erase(toAdd.end()-curr_length,toAdd.end());
		}
		else if(!curr->getVisited()){
			toAdd.append(curr->getText());
                        //cout<<"print toadd: "<<toAdd<<endl;
			if(buildTrie->find(toAdd,buildTrie->getRoot(),endnode)){
                                //cout<<"In add all succesfully find: "<<curr->getText()<<endl;
				if(endnode->getEnd()&&(toAdd.size()>=min_length)){
					(*words).insert(toAdd);
                                        //cout<<"Insert a word to the set!"<<endl;
				}
				curr->setVisited(true);
				curr->setRevisited(true);
				s.push(curr);
                                vector<int> neigh=neighbour(rows,cols,curr->getPos());
                                for(unsigned int i=0;i<neigh.size();i++){
                                        int temp=neigh[i];
                                        if(!board_1[temp]->getVisited()){
                                                s.push(board_1[temp]);
//                                                if(temp==9){
//                                                    cout<<"find a of 'canibal'!"<<endl;
//                                                    cout<<board_1[temp]->getVisited()<<endl;
//                                                }
					}
				}
			}
			else{
                                toAdd.erase(toAdd.end()-curr_length,toAdd.end());
			}
		}
	}
}

// void addOne(vector<BoardPos*> board, int start, unsigned int min_length, set<string>* words, int rows, int cols){
// 	TrieNode* endnode=buildTrie->getRoot();
// 	stack<BoardPos*>s;
// 	for(int i=0;i<board.size();i++){
// 		board[i]->setVisited(false);
// 		board[i]->setRevisited(false);
// 	}
// 	s.push(board[start]);
// 	while(!s.empty()){
// 		BoardPos* curr=s.pop();
// 		if(curr->getRevisited()){
// 			curr->setRevisited(false);
// 			curr->setVisited(false);
// 			endnode=curr->getPrev();
// 		}
// 		else if(!curr->getVisited()){
// 			TrieNode* temp_node=endnode;
// 			string temp_text=curr->getText();
// 			if(buildTrie->find(temp_text,temp_node,endnode)){
// 				cur
// 				curr->setVisited(true);
// 				curr->setRevisited(true);
// 				s.push(curr);
// 				vector<int> neighbour=neighbour(rows,cols,curr->getPos());
// 				for(int i=0;i<neighbour.size();i++){
// 					int temp=neighbour[i];
// 					if(!board[temp]->getVisited()){
// 						s.push(board[temp]);
// 					}
// 				}
// 			}
// 		}
// 	}
// }

vector<int> BogglePlayer::neighbour(int rows, int cols, int curr){
	vector<int> result;
	int temp=0;
	int sum=rows*cols;
	int curr_row=curr/cols;
	int curr_col=curr%cols;
        int pos[8][2]={{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};
	if(curr>=0&&(curr<sum)){
		for(int k=0;k<8;k++){
			if(curr_row+pos[k][0]<0||curr_row+pos[k][0]>=rows||curr_col+pos[k][1]<0||curr_col+pos[k][1]>=cols)continue;
			else{
				temp=cols*(curr_row+pos[k][0])+curr_col+pos[k][1];
				result.push_back(temp);
			}
		}
	}
	return result;
}
