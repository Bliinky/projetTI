#include <iostream>
#include <string>
#include <sstream>
using namespace std;
#include "Coding.h"

//Constructor
Coding::Coding(){quantity=0;code="";}
Coding::Coding(const char c)
{
  name=c;
  quantity=1;
  code="";
}
Coding::Coding(const char c,int codeInt)
{
  name=c;
  quantity=1;
  ostringstream os;
  os << codeInt;
  code=os.str();
}
Coding::Coding(const string n)
{
  name=n; 
  quantity=1;
  code="";
}
Coding::Coding(char c, const string s)
{
  ostringstream os;
  os << c;
  name = string();
  name = os.str();
  code = s;
}
Coding::Coding(const string s,const char c,int encoding)
{
  name=s+c;
  quantity=0;
  ostringstream os;
  os << encoding;
  code= os.str();
}
Coding::Coding(const string s1,const string s2,int encoding){
  name=s1+s2;
  quantity=0;
  ostringstream os;
  os << encoding;
  code = os.str();
}
Coding::Coding(string word , unsigned int encoding)
{
  name=word;
  quantity=0;
  ostringstream os;
  os << encoding;
  code = os.str();
}
Coding::~Coding(){
  
}

//Get and Set 
string Coding::getName()const{return name;}
char Coding::getNameRang(const int rang)const{return name[rang];}
int Coding::getNameSize()const{return name.size();}
int Coding::getQuantity()const{return quantity;}
string Coding::getCode()const{return code;}
char Coding::getCodeRang(const int rang)const{return code[rang];}
int Coding::getCodeSize()const{return code.size();}

void Coding::setName(const string n){name=n;}
void Coding::setQuantity(const int q){quantity=q;}
void Coding::setCode(const string c){code=c;}

//Methode d'ajout d'occurence
void Coding::upQuantity(){quantity++;}




//Affichage
string Coding::toString()const
{
  cout << "Le nom est " 
       << name 
       << " de quantité "
       << quantity
       << " avec le code "
       << code
       << endl;
  return "";
}
 

