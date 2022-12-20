/*
 * File: main.cpp
 * --------------
 * Blank C++ project configured to use Stanford cslib and Qt
 */

#include "console.h"
#include "simpio.h"
//#include "vector.h"
#include "OurMap.h"
using namespace std;



int main()
{
    OurMap<int,string> map1;
    map1.put(1,"ab");
    map1.put(2,"rs");
    map1.put(3,"tt");

    cout<<"map1.firstKey():"<<map1.firstKey()<<endl;
    cout<<"map1.lastKey():"<<map1.lastKey()<<endl;
    cout<<"map1.size():"<<map1.size()<<endl;
    cout<<"map1.Keys():"<<map1.Keys()<<endl;
    cout<<"map1.values():"<<map1.values()<<endl;
    map1.remove(2);
    cout<<"map1.Keys() after map1.remove(2):"<<map1.Keys()<<endl;
    cout<<"map1.values()after map1.remove(2):"<<map1.values()<<endl;
    cout<<"map1.containsKey(2):"<<map1.containsKey(2)<<endl;
    cout<<"map1.containsKey(3):"<<map1.containsKey(3)<<endl;
    cout<<"map1[3]:"<<map1[3]<<endl;
    map1[3] = "ff";
    cout<<"map1[3] after map1[3] = ff:"<<map1[3]<<endl;
    cout<<"map1.isEmpty():"<<map1.isEmpty()<<endl;

    OurMap<int,string> map2(map1);
    cout<<"map2.Keys():"<<map2.Keys()<<endl;
    cout<<"map2.values():"<<map2.values()<<endl;
    cout<<"map2.isEmpty():"<<map2.isEmpty()<<endl;
    map2.clear();
    cout<<"map2.isEmpty() after map2.clear():"<<map2.isEmpty()<<endl;


    return 0;
}
