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
    

    auto translate1 = glm::translate(glm::mat4(1.0f), glm::vec3(+ 0,+ 0,+ 0 ));

    auto rotate = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0, 1.0f, 0));

    auto translate2 = glm::translate(glm::mat4(1.0f), glm::vec3(- 0,- 0,- 0 ));

    auto result = translate2 * rotate * translate1;

   






}

















