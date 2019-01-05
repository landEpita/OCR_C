
//infint.cpp
#include <iostream>
#include "infint.hpp"
#include <string>
#include <stdlib.h>

using namespace std;

/*string tostring (int nb)
{
    string rslt="";
    int i=0;
    while(nb!=0)
    {
        rslt =    
    }
}*/
Infint::Infint()
{

    this->moins = false;
    this->enter.push_back(0);
}
Infint::Infint(int enter)
{
    this->moins = false;
    int digit;
  //  cout<<"build integer =   "<<  enter  <<endl;
    if(enter!=0)
    {
        while(enter != 0)
        {
            digit = enter%10;
            if(digit<0 && enter/10!=0)
            {
                digit = abs(digit);
            }
            else
            {
                this->moins= true;
            }
            this->enter.push_back(digit);
            enter = enter/10;
        }
    }
    else
    {
        this->enter.push_back(0);
    }
}
    
    

Infint::Infint(string enter)
{

    this->moins = false;
    bool bit = false;
//    cout<<"string build"<<endl;
    if(enter[0]=='-')
    {
        enter = enter.substr(1,enter.size());
        bit =true;

    }
    while(enter != "")
    {
        this->enter.push_back(enter[enter.size()-1] -'0');
//        cout<<enter[enter.size()-1]-48<<endl;
        enter = enter.substr(0,enter.size()-1);
    }
    if(bit)
    {
        this->enter[this->enter.size()-1] = -this->enter[this->enter.size()-1];
    }
}
string plus(string v1,string v2)
{
    string rslt ="";
    int i=0;
    int retenu=0;
    int r;
    while(v1 != "" && v2 != "")
    {
        r = (int)(v1[i]) + (int)(v2[i]) + retenu;
        retenu = r / 10;
        r =r % 10;
        rslt[i] = r;
    }
 //   cout<<"string "<<rslt<<endl;
    return rslt;

}
string Infint::pprintf()
{
    int i =this->enter.size()-1;
    string rslt = "";
    vector<int> copy = this->enter;
 //   copy.pop_back();
    
    if(copy.empty() == true)
    {
         cout << "empty tab";
    }
    while(copy.empty()!=true)
    {
        cout<<this->enter[i];
        rslt+=char(this->enter[i]);
        i--;
        copy.pop_back();
    }
    cout<<endl;
    return rslt;
}


