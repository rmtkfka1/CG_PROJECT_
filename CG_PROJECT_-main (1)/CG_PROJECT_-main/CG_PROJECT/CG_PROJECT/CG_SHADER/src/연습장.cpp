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
   /*
   

    <�̽¿�>
    �뷫 1������ ������Ʈ�� �����ϸ鼭 ��������� ���� ���� ���Ƽ� �������⵵ �ߴ� �ñ⿴���ϴ�. 
    Ư�� ������Ʈ ������ �� �̲����� �������� ���� �����մϴ�. 
    ���п� c++�� �׷��Ƚ� Ư�� ���Ӱ��߿� �־ ���α׷��� ����� ���ؼ� ���� ������ϴ�. �����մϴ�

    <�����>
    
   
   
   

   
   
   */

}

















