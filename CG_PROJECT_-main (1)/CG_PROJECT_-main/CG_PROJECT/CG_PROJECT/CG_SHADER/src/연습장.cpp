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
   /*
   

    <이승욱>
    대략 1달정도 프로젝트를 진행하면서 힘들었지만 배운게 정말 많아서 보람차기도 했던 시기였습니다. 
    특히 프로젝트 끝까지 잘 이끌어준 상혁이형 정말 감사합니다. 
    덕분에 c++과 그래픽스 특히 게임개발에 있어서 프로그래밍 방법에 대해서 많이 배웠습니다. 감사합니다

    <김상혁>
    
   
   
   

   
   
   */

}

















