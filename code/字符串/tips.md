### 剑指 Offer II 002. 二进制加法
可以使用^和&和<<运算符来模仿二进制加法

0101+0101=1010

0101^0101=0000//新的A
0101&0101=0101///新的B
0101<<1=1010//B左移模仿进位
1010^0000=1010//新的A
1010&0000=0000//B==0为停止条件
so answer is 1010

~~~ cpp
        while(1){
            res=A^B;
            B=A&B;
            A=res;
            B<<=1;
            if(B==0){
                break;
            }
        }
~~~

> 二进制减法可以先将被减数取补码再进行加法计算
