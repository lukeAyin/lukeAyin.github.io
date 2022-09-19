#include<bits/stdc++.h>
#define pb puch_back
#define eb emplace_back
#define inf 0x3f3f3f3f
#define ll long long
#define ull unsigned long long
#define pii pair<int,int>
using namespace std;

class Solution {
public:
    int maximalRectangle(vector<string>& matrix) {
        int m=matrix.size();
        if(m==0){
            return 0;
        }
        int n=matrix[0].size();
        vector<int> h(n,0);
        int res=0;
        // vector<int> left(n,-1);
        // vector<int> right(n,n);
        for(int i=0;i<m;i++){
            stack<int> stk;
            vector<int> left(n,-1);
            vector<int> right(n,n);
            // left.resize(n,-1);
            // right.resize(n,n);//vector的resize函数只会在新插入的数中赋值新的值，原来数组中存在的不会更改
            for(int j=0;j<n;j++){
                if(matrix[i][j]=='1'){
                    h[j]++;
                }else{
                    h[j]=0;
                }
                while(!stk.empty()&&h[stk.top()]>h[j]){
                    right[stk.top()]=j;
                    stk.pop();
                }
                if(!stk.empty()){
                    left[j]=stk.top();
                }
                stk.push(j);
            }
            for(int j=0;j<n;j++){
                res=max(h[j]*(right[j]-left[j]-1),res);
            }
        }
        return res;
    }
};
int main(){
    Solution s;
    // vector<string> vec{"10100","10111","11111","10010"};
    // cout<<s.maximalRectangle(vec);
    vector<string> vec={"10001","11011","11111"};
    cout<<s.maximalRectangle(vec);
}
/*
给定一个由 0 和 1 组成的矩阵 matrix ，找出只包含 1 的最大矩形，并返回其面积。

注意：此题 matrix 输入格式为一维 01 字符串数组。

rows == matrix.length
cols == matrix[0].length
0 <= row, cols <= 200
matrix[i][j] 为 '0' 或 '1'

*/