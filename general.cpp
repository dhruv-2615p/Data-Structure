#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <limits.h>
#include <vector>
using namespace std;

int main(){

    vector<int> v(2);
    
    cout<<v.size()<<endl;
    cout<<v.capacity()<<endl;

    v.pop_back();
    cout<<v.size()<<endl;
    cout<<v.capacity()<<endl;

    return 0;
}
