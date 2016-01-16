#include "HCTree.hpp"
#include "BitInputStream.hpp"
#include "BitOutputStream.hpp"
#include <vector>
#include <queue>
#include <stdlib.h>
#include <stdio.h>


using namespace std;

HCTree::~HCTree(){
    if(root!=0)clear(root);
}

void HCTree::build(const vector<int>& freqs){
    priority_queue<HCNode,vector<HCNode *>,HCNodePtrComp> q;
    for(int i=0;i<freqs.size();i++){
        HCNode* newNode=new HCNode(freqs[i],(unsigned char)(i));
        this->leaves[i]=newNode;
        if(freqs[i]!=0)q.push(newNode);
    }
    if(q.size()==1){
        HCNode* zeroNode=new HCNode(0,0);
        q.push(zeroNode);
    }

    //least node is c1,second least node is c0
    while(q.size()!=1){
        HCNode* node_1=q.top();
        q.pop();
        HCNode* node_0=q.top();
        q.pop();
        HCNode* mergeNode=new HCNode(node_1->count+node_0->count,0);
        node_1->p=mergeNode;
        node_0->p=mergeNode;
        mergeNode->c1=node_1;
        mergeNode->c0=node_0;
        q.push(mergeNode);
    }
    this->root=q.top();
}

void HCTree::encode(byte symbol, BitOutputStream& out) const{
    HCNode* enNode=this->leaves[symbol];
    this->helper(enNode,out);
}

int HCTree::decode(BitInputStream& in) const{
    HCNode* curr=this->root;
    int currBit;
    while(curr->c1||curr->c0){
        currBit=in.readBit();
        //cout<<currBit<<endl;
        if(currBit==1)curr=curr->c1;
        else if(currBit==0)curr=curr->c0;
    }
    return curr->symbol;
}

void HCTree::helper(HCNode* curr,BitOutputStream& out) const{
    if(curr==0)return;
    helper(curr->p,out);
    if(curr->p!=0){
        if(curr==curr->p->c0){
            out.writeBit(0);
            //cout<<"0"<<endl;
        }
        else if(curr==curr->p->c1){
            out.writeBit(1);
            //cout<<"1"<<endl;
        }
    }
}

void HCTree::clear(HCNode *p){
    if(p!=0){
        if(p->c1!=0)clear(p->c1);
        if(p->c0!=0)clear(p->c0);
        delete p;
    }
}
