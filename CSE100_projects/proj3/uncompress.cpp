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

HCNode* readNode(BitInputStream & in);
int main(int argc,char **argv){
        if(argc!=3){
            cerr<<"Error:invalid argument"<<endl;
            return -1;
        }
        if(strcmp(argv[1],argv[2])==0){
            cerr<<"Error:input and output files have the same name"<<endl;
            return -1;
        }
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
	BitInputStream* is=new BitInputStream(in);
	BitOutputStream* os=new BitOutputStream(out);
        int numAll=is->readInt();
        if(numAll==-1){
            cerr<<"Error:empty file"<<endl;
            return -1;
        }
	HCTree* decodeTree=new HCTree();
        decodeTree->setRoot(readNode(*is));
//	int flag=is->readBit();
//        cout<<flag<<endl;
//	if(flag==0){
//		HCNode* node=new HCNode(0,is->readByte());
//		HCNode* rootNode=new HCNode(0,0);
//                rootNode->c0=node;
//		decodeTree->setRoot(rootNode);
//	}
//	else{
//		decodeTree->setRoot(readNode(*is));
//	}
//        cout<<decodeTree->getRoot()->c1->c1->symbol<<endl;
//        cout<<decodeTree->getRoot()->c1->c0->symbol<<endl;
//        cout<<decodeTree->getRoot()->c0->c1->symbol<<endl;
//        cout<<decodeTree->getRoot()->c0->c0->symbol<<endl;
//        for(int i=0;i<8;i++){
//            cout<<is->readBit()<<endl;
//        }
        for(int i=0;i<numAll;i++){
                os->writeByte(decodeTree->decode(*is));
        }
	in.close();
	out.close();
	return 0;
}

HCNode* readNode(BitInputStream & in){
	if(in.readBit()==1){
		HCNode* node=new HCNode(0,in.readByte());
		return node;
	}
	else{
		HCNode* child1=readNode(in);
		HCNode* child0=readNode(in);
		HCNode* node=new HCNode(0,0);
		node->c1=child1;
		node->c0=child0;
		return node;
	}
}
