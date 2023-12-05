#include "pch.h"


#include <iostream>
#include <vector>

using namespace std;

class test
{
public:
    test()
    {
        cout << "생성자 호출" << endl;
    }

    ~test()
    {
        cout << "소멸자 호출" << endl;
    }

  
};


void func(vector<test*> v)
{

    cout << "함수시작" << endl;

    vector<test*> v_copy = v;


    cout << "함수종료" << endl;


}




int main()
{
    test* a = new test();


    vector<test*> v;

    v.push_back(a);

    func(v);

    cout << "메인 종료" << endl;



    return 0;
}