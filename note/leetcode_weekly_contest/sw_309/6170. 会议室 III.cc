#include<bits/stdc++.h>
#define pb puch_back
#define eb emplace_back
#define inf 0x3f3f3f3f
#define ll long long
#define ull unsigned long long
#define pii pair<int,int>
#define pli pair<ll,int>
using namespace std;
class Solution {
public:
    int cnt[105];//会议室使用的次数
    void init(){
        memset(cnt,0,sizeof(cnt));
    }
    int mostBooked(int n, vector<vector<int>>& meetings) {
        vector<vector<ll>> lm(meetings.size());
        for(int i=0;i<meetings.size();++i){
            lm[i].emplace_back(meetings[i][0]);
            lm[i].emplace_back(meetings[i][1]);
        }
        sort(lm.begin(),lm.end());
        init();
        vector<pli> times(n);
        for(int i=0;i<n;++i){
            times[i]=make_pair(0,i);
        }
        for(int i=0;i<lm.size();++i){
            sort(times.begin(),times.end());
            if(times[0].first>lm[i][0]){
                int delay=times[0].first-lm[i][0];
                // for(int i=0;i<n;++i){
                //     times[i].first-=delay;
                // }
                lm[i][0]+=delay;
                lm[i][1]+=delay;
            }
            auto r=upper_bound(times.begin(),times.end(),pli(lm[i][0],n));
            // int x=r-times.begin();
            int select_id=n;
            int t_id=n;
            for(auto it=times.begin();it<r;++it){
                if(select_id>it->second){
                    select_id=it->second;
                    t_id=it-times.begin();
                }
            }
            cnt[select_id]++;
            times[t_id].first=lm[i][1];
        }
        int res=0;
        int res_id=-1;
        for(int i=0;i<n;++i){
            if(cnt[i]>res){
                res=cnt[i];
                res_id=i;
            }
        }
        return res_id;
    }
};
class Solution {
public:
    int mostBooked(int n, vector<vector<int>>& a) {
        vector<int> cnt(n, 0);
        vector<long long> cur(n, 0);
        sort(a.begin(), a.end(), [](const auto &x, const auto &y){
            return x[0] < y[0];
        });
        for(int i=0; i<a.size(); ++i){
            bool flag = 0;
            for(int j=0; j<n; ++j){
                if(cur[j] <= a[i][0]){
                    flag = 1;
                    ++cnt[j];
                    cur[j] = a[i][1];
                    break;
                }
            }
            if(flag)    continue;
            int k = 0;
            for(int j=1; j<n; ++j){
                if(cur[j] < cur[k]) k = j;
            }
            ++cnt[k];
            cur[k] += (a[i][1] - a[i][0]);
        }
        int ret = 0;
        for(int i=1; i<n; ++i){
            if(cnt[i] > cnt[ret])   ret = i;
        }
        return ret;
    }
};
int main(){
    Solution s;
    FILE *fp=fopen("data.txt","r");
    int n,m;
    fscanf(fp,"%d%d",&n,&m);
    vector<vector<int>> meetings(m,vector<int>(2,0));
    for(int i=0;i<m;++i){
        int x,y;
        fscanf(fp,"%d%d",&x,&y);
        meetings[i][0]=x;
        meetings[i][1]=y;
    }
    printf("%d",s.mostBooked(n,meetings));
}

/*
给你一个整数 n ，共有编号从 0 到 n - 1 的 n 个会议室。

给你一个二维整数数组 meetings ，其中 meetings[i] = [starti, endi] 表示一场会议将会在 半闭 时间区间 [starti, endi) 举办。所有 starti 的值 互不相同 。

会议将会按以下方式分配给会议室：

每场会议都会在未占用且编号 最小 的会议室举办。
如果没有可用的会议室，会议将会延期，直到存在空闲的会议室。延期会议的持续时间和原会议持续时间 相同 。
当会议室处于未占用状态时，将会优先提供给原 开始 时间更早的会议。
返回举办最多次会议的房间 编号 。如果存在多个房间满足此条件，则返回编号 最小 的房间。

半闭区间 [a, b) 是 a 和 b 之间的区间，包括 a 但 不包括 b 。
1 <= n <= 100
1 <= meetings.length <= 105
meetings[i].length == 2
0 <= starti < endi <= 5 * 105
starti 的所有值 互不相同
*/