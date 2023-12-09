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
   



    스네이프 교수 : 복도에 숫자 4개를 숨겨 맵핑해놨습니다.

    손전등을 이용하지 않으면 찾지 못합니다.

    숫자들을 찾은후 오름차순으로 정렬하면 정답입니다.

    
   
   
   
   
   
   
   

   
   
   */

}

















