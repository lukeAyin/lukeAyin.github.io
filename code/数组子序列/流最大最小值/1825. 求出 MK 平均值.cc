#include<bits/stdc++.h>
using namespace std;
class MKAverage {
public:
    int m,k;
    queue<int> q;
    multiset<int> ms_max,ms_min,ms;
    long long sum;
    MKAverage(int m, int k) {
        this->m=m;
        this->k=k;
        sum=0;
    }
    
    void addElement(int num) {
        q.push(num);
        if(q.size()<m){
            ms.insert(num);
            sum+=num;
        }else if(q.size()==m){
            ms.insert(num);
            sum+=num;
            for(int i=0;i<k;i++){
                int t=*ms.begin();
                sum-=t;
                ms_min.insert(t);
                ms.erase(ms.begin());
            }
            for(int i=0;i<k;i++){
                int t=*ms.rbegin();
                sum-=t;
                ms_max.insert(t);
                ms.erase(prev(ms.end()));
            }
        }else{
            int t=*ms_max.begin();
            int y=*ms_min.rbegin();
            if(num>t){
                ms_max.insert(num);
                ms.insert(t);
                sum+=t;
                ms_max.erase(ms_max.begin());
            }else if(num<y){
                ms_min.insert(num);
                ms.insert(y);
                sum+=y;
                ms_min.erase(prev(ms_min.end()));
            }else{
                ms.insert(num);
                sum+=num;
            }
            int x=q.front();
            q.pop();
            if(ms_max.count(x)>0){
                ms_max.erase(ms_max.find(x));
                ms_max.insert(*ms.rbegin());
                sum-=*ms.rbegin();
                ms.erase(prev(ms.end()));
            }else if(ms_min.count(x)>0){
                ms_min.erase(ms_min.find(x));
                ms_min.insert(*ms.begin());
                sum-=*ms.begin();
                ms.erase(ms.begin());
            }else{
                ms.erase(ms.find(x));
                sum-=x;
            }

        }
            // cout<<sum<<endl;
    }
    
    int calculateMKAverage() {
        if(q.size()<m){
            return -1;
        }else{
            return sum/(m-2*k);
        }
    }
};

/**
 * Your MKAverage object will be instantiated and called as such:
 * MKAverage* obj = new MKAverage(m, k);
 * obj->addElement(num);
 * int param_2 = obj->calculateMKAverage();
 */
int main(){
    
}