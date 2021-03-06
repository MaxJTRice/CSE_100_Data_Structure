#ifndef BOGGLEUTIL_H
#define BOGGLEUTIL_H
#include <set>
#include <string>
#include <iostream>

//Data structures for lexicon and board should reside in this file.
//All of the operations your data structures support should be declared within your data structures.
using namespace std;

class TrieNode{
public:
        char val;
        bool isEnd;
	TrieNode *leftNode;
	TrieNode *middleNode;
        TrieNode *rightNode;
        TrieNode(char val,
                 bool isEnd,
                TrieNode *leftNode=0,
		TrieNode *middleNode=0,
                TrieNode *rightNode=0)
        : val(val),isEnd(isEnd),leftNode(leftNode), middleNode(middleNode), rightNode(rightNode){ }
	void setEnd(){
		this->isEnd=true;
	}
	bool getEnd(){
		return this->isEnd;
	}
};

class Trie{
private:
	TrieNode *root;
public:
	Trie(){
		root=new TrieNode(0,false);
	}
	~Trie();
	void build(const set<string>& word_list);
        bool find(const string& word, TrieNode* startnode, TrieNode* & endnode);
        void clear(TrieNode *node);
        void InsertLetter(char a, TrieNode* & node, TrieNode* & curr_node);
//        bool findOne(TrieNode* startnode, TrieNode* endnode);
	TrieNode* getRoot(){
		return this->root;
	}
	void setRoot(TrieNode *node){
		this->root=node;
	}
};

class BoardPos{
private:
        const string text;
        bool visited;
        bool revisited;
        int pos;
public:
        BoardPos(const string& text):text(text),visited(false),revisited(false),pos(0){ }
	const string & getText() const{
		return this->text;
	}
	bool getVisited(){
		return this->visited;
	}
	void setVisited(bool visited){
		this->visited=visited;
	}
	void setRevisited(bool revisited){
		this->revisited=revisited;
	}
	bool getRevisited(){
		return this->revisited;
	}
	void setPos(int pos){
		this->pos=pos;
	}
	int getPos(){
		return this->pos;
	}
	// TrieNode* getPrev(){
	// 	return this->prev;
	// }
	// void setPrev(TrieNode* prev){
	// 	this->prev=prev;
	// }
};
#endif
