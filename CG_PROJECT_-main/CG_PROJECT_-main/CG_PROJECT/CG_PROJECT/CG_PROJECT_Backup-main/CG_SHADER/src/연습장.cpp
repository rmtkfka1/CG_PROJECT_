#include "pch.h"


#include <iostream>
#include <vector>

using namespace std;

class test
{
public:
    test()
    {
        cout << "������ ȣ��" << endl;
    }

    ~test()
    {
        cout << "�Ҹ��� ȣ��" << endl;
    }

  
};


void func(vector<test*> v)
{

    cout << "�Լ�����" << endl;

    vector<test*> v_copy = v;


    cout << "�Լ�����" << endl;


}




int main()
{
    test* a = new test();


    vector<test*> v;

    v.push_back(a);

    func(v);

    cout << "���� ����" << endl;



    return 0;
}