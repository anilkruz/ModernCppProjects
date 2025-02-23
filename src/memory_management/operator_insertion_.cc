#include<iostream>

using namespace std;

class Points{
    public:
        int a;
        int b;
     friend ostream& operator<<(ostream& os,const Points& oth){
            os<<'('<<oth.a<<','<<oth.b<<')'<<endl;
            return os;
        }
    public:
        Points(int a, int b):a(a),b(b){}

};

int main(){

    Points p1(2,4);
        
    cout<<p1;

}
