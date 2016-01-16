#include "HCTree.hpp"
#include "BitInputStream.hpp"
#include "BitOutputStream.hpp"
#include <fstream>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

void encodeTree(HCNode* node,BitOutputStream & out);

int main(int argc,char **argv){
        if(argc!=3){
            cerr<<"Error:invalid argument"<<endl;
            return -1;
        }
        if(strcmp(argv[1],argv[2])==0){
            cerr<<"Error:input and output files have the same name"<<endl;
            return -1;
        }
        int emptyFlag=1;
	ifstream in;
	in.open(argv[1],ios::binary);
	ofstream out;
	out.open(argv[2],ios::binary);
        if(!in.good()){
            cerr<<"Error:input file has some problems"<<endl;
            return -1;
        }
        if(!out.good()){
            cerr<<"Error:output file has some problems"<<endl;
            return -1;
        }
	//BitInputStream is=new BitInputStream(in);
	vector<int>counter(256,0);
	unsigned char ch;
        //int numLeaves=0;
	int numAll=0;
	while(1){
		ch=in.get();
		if(!in.good())break;
                emptyFlag=0;
		counter[ch]++;
		numAll++;
	}
	if(!in.eof()){
		cerr<<"There was a problem!"<<endl;
		return -1;
	}
        if(emptyFlag==1){
                cerr<<"Error:empty file"<<endl;
                return -1;
        }
	in.close();
	cout<<"Successfully read a file"<<endl;
	for(int i=0;i<counter.size();i++){
		if(counter[(unsigned char)(i)]!=0){
                        //numLeaves++;
                        cout<<i<<":"<<counter[i]<<endl;
		}
	}
	cout<<"End of reading bytes"<<endl;

	HCTree* newTree=new HCTree();
	newTree->build(counter);
	BitOutputStream* os=new BitOutputStream(out);
	//os->writeByte(numLeaves);
	os->writeInt(numAll);
        encodeTree(newTree->getRoot(),*os);
//	if(numLeaves==1){
//		os->writeBit(0);
//		os->writeByte(ch);
//	}
//	else{
//		os->writeBit(1);
//		encodeTree(newTree->getRoot(),*os);
//	}
	in.open(argv[1],ios::binary);
	while(1){
		ch=in.get();
		if(!in.good())break;
		newTree->encode(ch,*os);
	}
	if(!in.eof()){
		cerr<<"There was a problem!"<<endl;
		return -1;
	}
        os->writeByte(0);
	in.close();
	out.close();
        cout<<numAll<<endl;
	return 0;
}

void encodeTree(HCNode* node,BitOutputStream & out){
	if(node->c1==0){
		out.writeBit(1);
		out.writeByte(node->symbol);
	}
	else{
		out.writeBit(0);
		encodeTree(node->c1,out);
		encodeTree(node->c0,out);
	}
}
