//infint.hpp

#ifndef INFINT_HPP
#define INFINT_HPP

using namespace std;
#include <string>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <math.h>

class Infint{

public:
    Infint();
    Infint(int enter);
    Infint(string enter);
    string pprintf();
    
    friend vector<int> pas_de_zero(vector<int> tab)
    {
        int i = tab.size()-1;
        while(tab[i]==0)
        {
            tab.pop_back();
            i--;
        }
        return tab;
    }
    friend Infint operator-(Infint v1,Infint v2)
    {
        if(v1.enter[0]==0 && v1.enter.size()==1 )
            {

            v2.enter[v2.enter.size()-1]=  -v2.enter[v2.enter.size()-1];
                return v2;
            }
            if(v2.enter[0]==0 && v2.enter.size()==1 )
            {
                return v1;
            }
        vector<int> rslt ;
       // cout<<"av left: ";
      //  v1.pprintf();
    //    cout<<"av right: ";
//v2.pprintf();
        bool is_neg = false;
        if(v1.enter.size()<v2.enter.size() && v2.enter[v2.enter.size()-1]>0)
        {
            Infint tmp = v1;
            v1 = v2;
            v2 = tmp;
            is_neg = true;
       //     cout<<"hola"<<endl;


        }
        if(v1.enter.size()==v2.enter.size())
        {
            
            Infint c_v1=v1;
            Infint c_v2=v2;
            int lenght = v1.enter.size()-1;
            while(v1.enter[lenght]==v2.enter[lenght])
            {
                lenght--;
            }
            if(v2.enter[lenght]>v1.enter[lenght])
            {

                Infint tmp = v1;
                v1 = v2;
                v2 = tmp;
                is_neg = true;
            }
        }
        Infint copy_v1 = v1;
        Infint copy_v2 = v2;
        int v1_rs;
        int v2_rs;
        int retenu = 0;
        int  rs =0;
        bool ok =false;
        unsigned long long i=0;
        

  //   cout<<"SOUSTRACTION"<<endl;
 //       cout<<"left: ";
     //   copy_v1.pprintf();
 //       cout<<"right: ";
  //      copy_v2.pprintf();

        
        if(v1.enter[v1.enter.size()-1]<0 && v2.enter[v2.enter.size()-1]>0)
        {
            if(is_neg)
            {

            v2.enter[v2.enter.size()-1]=  -v2.enter[v2.enter.size()-1];
            }
            else
            {

            v1.enter[v1.enter.size()-1]=  -v1.enter[v1.enter.size()-1];
            v1 = v1 + v2;
            v1.enter[v1.enter.size()-1] =-v1.enter[v1.enter.size()-1];
            return v1;
            }
            return v1 + v2;
            }
        
        if(v1.enter[v1.enter.size()-1]>0 && v2.enter[v2.enter.size()-1]<0)
        {
           // v1.pprintf();
            //v2.pprintf();
           // cout<<"+++++++++++    -     -----------"<<endl;
            if(is_neg==false)
            {
                v2.enter[v2.enter.size()-1]=  -v2.enter[v2.enter.size()-1];
            }
            else
            {

                v1.enter[v1.enter.size()-1]=  -v1.enter[v1.enter.size()-1];
            }
            
            return v1 + v2;
        }
        if(v1.enter[v1.enter.size()-1]<0 && v2.enter[v2.enter.size()-1]<0)
        {
            if(is_neg)
            {
            v2.enter[v2.enter.size()-1]=  -v2.enter[v2.enter.size()-1];
            v1 = v1 +v2;
            v1.enter[v1.enter.size()-1] =-v1.enter[v1.enter.size()-1];
            return v1;
            }
            else
            {
                v2.enter[v2.enter.size()-1]=  -v2.enter[v2.enter.size()-1];
                v1 = v1 +v2;
                return v1; 
            }
        }
        while(copy_v1.enter.empty()!=true || copy_v2.enter.empty()!=true )
        {
            if(copy_v1.enter.empty()!=true)
            {
                v1_rs = v1.enter[i];
                copy_v1.enter.erase(copy_v1.enter.begin());
            }
            else
            {
                v1_rs=0;
            }
            if(copy_v2.enter.empty()!=true)
            {
                v2_rs = v2.enter[i];
                copy_v2.enter.erase(copy_v2.enter.begin());
            }
            else
            {
                v2_rs=0;
            }
       //     cout<<"v1 = "<<v1_rs<<" || v2= "<<v2_rs<<endl;
            if(v1_rs - (v2_rs+retenu) < 0)
            {
                 v1_rs = v1_rs + 10;
                 ok = true;
            }
            
            rs = v1_rs - (v2_rs+retenu) ;
            retenu =0;
            if(ok)
            {
                retenu =1;
                ok = false;
            }
            rs = rs % 10;
            i++;

            rslt.push_back(rs);
    
        } 
    //enlve le zero
    int j = rslt.size()-1;
    if(rslt[0]!=0 && rslt.size()!=1)
    {
        while(rslt[j]==0 )
        {
            rslt.pop_back();
            j--;
        }
    }
    if(is_neg)
    {
    //    cout<<rslt[rslt.size()-1]<<endl;
        rslt[rslt.size()-1] = -rslt[rslt.size()-1];
    }
    v1.enter = rslt;
 //   cout<<"FIN SOUSTRACTION"<<endl;
    return v1;
    }







    friend Infint operator+(Infint v1,Infint v2)
    {
        if(v1.enter[0]==0 && v1.enter.size()==1)
        {
            return v2;
        }
        if(v2.enter[0]==0 && v2.enter.size()==1)
        {
            return v1;
        }
        vector<int> rslt ;
        Infint copy_v1 = v1;
        Infint copy_v2 = v2;
        int v1_rs;
        int v2_rs;
        int retenu = 0;
        int  rs =0;
        unsigned long long i=0;
        bool negative2 = false;
        
        if(v1.enter[v1.enter.size()-1]<0 && v2.enter[v2.enter.size()-1]<0)
        {
            v1.enter[v1.enter.size()-1] = abs(v1.enter[v1.enter.size()-1]);
            v2.enter[v2.enter.size()-1] = abs(v2.enter[v2.enter.size()-1]);
            negative2 = true;
        }
        if(v1.enter[v1.enter.size()-1]<0 && v2.enter[v2.enter.size()-1]>0)
        {
            v1.enter[v1.enter.size()-1] = abs(v1.enter[v1.enter.size()-1]);
            return v2 - v1;
        }
        

        if(v2.enter[v2.enter.size()-1]<0 && v1.enter[v1.enter.size()-1]>0)
        {
            v2.enter[v2.enter.size()-1] = abs(v2.enter[v2.enter.size()-1]);
            return v1 - v2;
        }


    //    cout<<"ADDITION"<<endl;
//        cout<<"left: ";
    //    copy_v1.pprintf();
      //  cout<<"right: ";
        //copy_v2.pprintf();

        

        while(copy_v1.enter.empty()!=true || copy_v2.enter.empty()!=true )
        {
            if(copy_v1.enter.empty()!=true)
            {
                v1_rs = v1.enter[i];
                copy_v1.enter.erase(copy_v1.enter.begin());
            }
            else
            {
                v1_rs=0;
            }
            if(copy_v2.enter.empty()!=true)
            {
                v2_rs = v2.enter[i];
                copy_v2.enter.erase(copy_v2.enter.begin());
            }
            else
            {
                v2_rs=0;
            }
          //  cout<<"v1 = "<<v1_rs<<" || v2= "<<v2_rs<<endl;
            rs = v1_rs + v2_rs + retenu;
            retenu = rs / 10;
            rs = rs % 10;
            i++;
            rslt.push_back(rs);
    
        }
        if(retenu !=0)
        {
            rslt.push_back(retenu);
        }
    if(negative2)
    {
        rslt[rslt.size()-1] = -rslt[rslt.size()-1];
    }
    v1.enter = rslt;
 //   cout<<"FIN ADDITION"<<endl;
    return v1;
    }
    friend Infint operator+(Infint v1,string v2)
    {
        Infint str = v2;
        return v1 + str;
    }
    friend Infint operator+(Infint v1,long long v2)
    {
        Infint str = v2;
        return v1 + str;
    }
////////
    friend Infint operator+=(Infint &v1,Infint v2)
    {
        v1 = v1 + v2;
        return v1;
    }
    friend Infint operator+=(Infint &v1,string v2)
    {
        Infint str = v2;
        v1 = v1 + v2;
        return v1;
    }
    friend Infint operator+=(Infint &v1,long long v2)
    {
        Infint str = v2;
        v1 = v1 + v2;
        return v1;
    }
////////
    friend Infint operator++(Infint &v1,int)
    {
        v1 = v1 + 1;
        return v1;
    }

    /*friend bool operator!=(Infint &v1,Infint v2)
    {
        Infint copy_v1 = v1;
        Infint copy_v2 = v2;
        unsigned long long i =0;
        while(copy_v1.enter.empty()!=true && copy_v2.enter.empty()!=true)
        {
            if(copy_v1.enter[i] != copy_v2.enter[i])
            {
                return true;
            }
        }
        return false;

    }*/





///////
    friend Infint operator--(Infint &v1,int)
    {
        v1 = v1 + -1;
        return v1;
    }
////////
    friend Infint operator*(Infint v1,Infint v2)
    {
     //   cout<<"MULTIPLICATION"<<endl;
       // cout<<"left: "<<v1<<endl;
        //cout<<"right: "<<v2<<endl;
        Infint rslt = Infint();
        bool is_neg =false;
        if((v1.enter[0]==0 && v1.enter.size()==1 )||(v2.enter[0]==0 && v2.enter.size()==1 ))
        {
            return 0;
        }
        /*if(v1.enter.size()<v2.enter.size())
        {
            Infint tmp = v1;
            v1 = v2;
            v2 = v1;
        }*/
      /*  if(v2.enter[v2.enter.size()-1]<0)
        {
            v2.enter[v2.enter.size()-1]= abs(v2.enter[v2.enter.size()-1]);
        }*/
        if(v1.enter[v1.enter.size()-1]<0 && v2.enter[v2.enter.size()-1]<0)
        {
            v1.enter[v1.enter.size()-1] = -v1.enter[v1.enter.size()-1];
            v2.enter[v2.enter.size()-1] = -v2.enter[v2.enter.size()-1];
        }
        else
        {
            if(v1.enter[v1.enter.size()-1]>0 && v2.enter[v2.enter.size()-1]<0)
            {

            v2.enter[v2.enter.size()-1] = -v2.enter[v2.enter.size()-1];
                is_neg = true;
            }
            if(v1.enter[v1.enter.size()-1]<0 && v2.enter[v2.enter.size()-1]>0)
            {

            v1.enter[v1.enter.size()-1] = -v1.enter[v1.enter.size()-1];
                is_neg = true;
            }
        }
        vector<Infint> fin ;
        unsigned int i=0;
        while(i!=v1.enter.size())
        {
            rslt =0;
            
            while(v1.enter[i] !=0)
            {
//                cout<<"v1 = "<<v1.enter[i]<<endl;
                rslt = rslt + v2;
  //              cout<<"================= rslt = "<<rslt<<endl;
                v1.enter[i]--;
            }
            for(unsigned int zero=0;zero!=i;zero++)
            {
    //            cout<<"je met un zero"<<endl;
                rslt.enter.insert(rslt.enter.begin(),0);
            }
            fin.push_back(rslt);
            
  //          cout<<"----------------->>>>>"<<fin[i]<<endl;
            i++;
        }
  //      cout<<"fini"<<endl;
        rslt =0;
        for(unsigned int add=0;add!=fin.size();add++)
        {
            rslt = rslt + fin[add];
        }
        if(is_neg)
        {
            rslt.enter[rslt.enter.size()-1] = -rslt.enter[rslt.enter.size()-1];
        }
        v1 =rslt;
   //     cout<<"FIN MULTIPLICATION"<<endl;
        return v1;
    }
    friend Infint operator*(Infint v1,string v2)
    {
        Infint str = v2;
        return v1 * str;
    }
    friend Infint operator*(Infint v1,long long v2)
    {
        Infint str = v2;
        return v1 * str;
    }


///////////
    friend Infint operator*=(Infint &v1,Infint v2)
    {
        v1 = v1 * v2;
        return v1;
    }
    friend Infint operator*=(Infint &v1,string v2)
    {
        v1 = v1 * v2;
        return v1;
    }
    friend Infint operator*=(Infint &v1,long long v2)
    {
        Infint str = v2;
        v1 = v1 * str;
        return v1;
    }
/////////
    friend Infint operator-(Infint v1,string v2)
    {
        Infint str = v2;
        return v1 - str;
    }
    friend Infint operator-(Infint v1,long long v2)
    {
        Infint str = v2;
        return v1 - str;
    }
/////////
    friend Infint operator-=(Infint &v1,Infint v2)
    {
        Infint str = v2;
        v1 = v1 - str;
        return v1;
    }
    friend Infint operator-=(Infint &v1,string v2)
    {
        Infint str = v2;
        v1 = v1 - str;
        return v1;
    }
    friend Infint operator-=(Infint &v1,long long v2)
    {
        Infint str = v2;
        v1 = v1 - str;
        return v1;
    }
////////
    friend ostream &operator<<(ostream &flux,Infint const &a)
    {
        vector<int> copy = a.enter;
        
        int i = a.enter.size()-1;
        while(copy.empty()!=true)
        {
            flux<<a.enter[i];
            i--;
            copy.pop_back();
        }
        
      //  flux << num.enter;
        return flux;
    }
    vector<int> enter;
    string num;
    bool moins ;
    

};





#endif
