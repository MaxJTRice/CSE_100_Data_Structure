#include "HCNode.hpp"

bool HCNode::operator<(HCNode const & other){
	if(this->count<other.count)return false;
	else if(this->count>other.count)return true;
	else return this->symbol<other.symbol;
}

bool comp(HCNode* one, HCNode* other){
	return one<other;
}