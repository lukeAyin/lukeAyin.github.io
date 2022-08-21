剑指offer12 矩阵中的路径

# question
>给定一个 m x n 二维字符网格 board 和一个字符串单词 word 。如果 word 存在于网格中，返回 true ；否则，返回 false 。
单词必须按照字母顺序，通过相邻的单元格内的字母构成，其中“相邻”单元格是那些水平相邻或垂直相邻的单元格。同一个单元格内的字母不允许被重复使用。
>- 示例 1：
> 输入：board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCCED"
输出：true
>- 示例 2：
输入：board = [["a","b"],["c","d"]], word = "abcd"
输出：false

>链接：https://leetcode-cn.com/problems/ju-zhen-zhong-de-lu-jing-lcof

- 深度优先搜索加剪枝
~~~
class Solution {
public:
    
    bool exist(vector<vector<char>>& board, string word) {
        int m=board.size();
        int n=board[0].size();
        vector<vector<bool>> flag(m,vector<bool>(n,false));
        for(int i=0;i<m;++i){
            for(int j=0;j<n;++j){
                if(board[i][j]==word[0]&&dfs(board,word,0,i,j,flag)){
                    return true;
                }
            }
        }
        return false;
    }
    bool dfs(vector<vector<char>>& board,string word,int index,int x,int y,vector<vector<bool>>& flag){
        if(index>=word.size()){
            return true;
        }
        int m=board.size();
        int n=board[0].size();
        if(x<0||x>=m||y<0||y>=n||flag[x][y]||board[x][y]!=word[index]){
            return false;
        }
        flag[x][y]=true;
        bool ans=dfs(board,word,index+1,x+1,y,flag)||dfs(board,word,index+1,x-1,y,flag)||dfs(board,word,index+1,x,y+1,flag)||dfs(board,word,index+1,x,y-1,flag);
        flag[x][y]=false;
        return ans;
    }
};
~~~
- 不使用flag数组，讲board中的字符临时替换成'\0'来表示已经访问过了
~~~
class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        rows = board.size();
        cols = board[0].size();
        for(int i = 0; i < rows; i++) {
            for(int j = 0; j < cols; j++) {
                if(dfs(board, word, i, j, 0)) return true;
            }
        }
        return false;
    }
private:
    int rows, cols;
    bool dfs(vector<vector<char>>& board, string word, int i, int j, int k) {
        if(i >= rows || i < 0 || j >= cols || j < 0 || board[i][j] != word[k]) return false;
        if(k == word.size() - 1) return true;
        board[i][j] = '\0';
        bool res = dfs(board, word, i + 1, j, k + 1) || dfs(board, word, i - 1, j, k + 1) || 
                      dfs(board, word, i, j + 1, k + 1) || dfs(board, word, i , j - 1, k + 1);
        board[i][j] = word[k];
        return res;
    }
};
~~~