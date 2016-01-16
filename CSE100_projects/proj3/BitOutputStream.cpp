#include <iostream>
#include "BitOutputStream.hpp"

using namespace std;

void BitOutputStream::writeBit(int bit){
        //if(this->buf_index==8)flush();
	this->buf=setBit(this->buf,bit,this->buf_index);
	this->buf_index++;
        if(this->buf_index==8)flush();
}

void BitOutputStream::writeByte(int i){
	for(int m=0;m<8;m++){
		int temp=(i>>(7-m))&1;
		this->writeBit(temp);
	}
}

void BitOutputStream::writeInt(int i){
	for(int m=0;m<32;m++){
		int temp=(i>>(31-m))&1;
		this->writeBit(temp);
	}
}

void BitOutputStream::flush(){
	out.put(this->buf);
	out.flush();
	this->buf=0;
	this->buf_index=0;
}

char BitOutputStream::setBit(char buffer,int i,int num){
	char c;
	if(i==1){
		c=buffer|(1<<(7-num));
	}
	else c=buffer&~(1<<(7-num));
	return c;
}
