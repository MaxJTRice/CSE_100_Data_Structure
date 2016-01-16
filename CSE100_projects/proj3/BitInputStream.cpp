#include <iostream>
#include <fstream>
#include "BitInputStream.hpp"

using namespace std;

int BitInputStream::readBit(){
	if(this->buf_index==8)this->fill();
	int v=bitVal(this->buf,7-(this->buf_index));
	this->buf_index++;
	return v;
}

int BitInputStream::readByte(){
	int result=0;
	for(int i=0;i<8;i++){
		result=result|((this->readBit())<<(7-i));
	}
	return result;
}

int BitInputStream::readInt(){
	int result=0;
	for(int i=0;i<32;i++){
		result=result|((this->readBit())<<(31-i));
	}
	return result;
}

int BitInputStream::bitVal(char b,int n){
	char c;
	c=b>>n&1;
	return (int)c;
}

void BitInputStream::fill(){
	this->buf=this->in.get();
	this->buf_index=0;
}