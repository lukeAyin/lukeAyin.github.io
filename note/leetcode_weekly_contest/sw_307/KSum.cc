class Solution {
    typedef pair<long long,int> pli;
    typedef long long ll;
public:
    long long kSum(vector<int>& nums, int k) {
        int n=nums.size();
        ll neg=0;
        ll sm=0;
        for(int i=0;i<n;++i){
            sm+=nums[i];
            if(nums[i]<0){
                neg+=nums[i];
                nums[i]=-nums[i];
            }
        }
        sort(nums.begin(),nums.end());
        priority_queue<pli,vector<pli>,greater<pli>> pq;
        pq.push(make_pair(nums[0],0));
        ll ans=0;
        for(int i=2;i<=k;++i){
            auto tmp=pq.top();
            pq.pop();
            ans=tmp.first;
            if(tmp.second==n-1){
                continue;
            }
            pq.push(make_pair(tmp.first+nums[tmp.second+1],tmp.second+1));
            pq.push(make_pair(tmp.first+nums[tmp.second+1]-nums[tmp.second],tmp.second+1));
        }
        return sm-(ans+neg);
    }
};