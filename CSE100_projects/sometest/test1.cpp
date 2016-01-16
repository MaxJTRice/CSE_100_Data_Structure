#include <stdio.h>
#include <vector>
#include <iostream>
using namespace std;

vector<int>neighbour(int rows, int cols, int curr){
        vector<int> result;
        int temp=0;
        int sum=rows*cols;
        int curr_row=curr/cols;
        int curr_col=curr%cols;
        int pos[8][2]={-1,-1,-1,0,-1,1,0,-1,0,1,1,-1,1,0,1,1};
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

int main(){
        vector<int>result=neighbour(5,6,7);
	for(int i=0;i<result.size();i++){
		cout<<result[i]<<endl;
	}
        return 0;
}

