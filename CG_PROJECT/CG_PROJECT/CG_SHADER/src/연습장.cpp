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
   



    KSH : ������ ���� 4���� ���� ���ܳ����ϴ�.

    �������� �̿��Ͽ� ���� ���߰� �Ǹ� ���ڰ� �巯���ϴ�.

    ���ڵ��� ã���� ������������ �����ϸ� �����Դϴ�.

    
   
   
   
   
   
   
   

   
   
   */

}

















