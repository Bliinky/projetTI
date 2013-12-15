#include <iostream>
#include <string>
using namespace std;
#include "Coding.h"
#include "CodingHuffman.h"

CodingHuffman::CodingHuffman(): Coding() {p=0;left=NULL;right=NULL;}

CodingHuffman::CodingHuffman(const char c): Coding(c) {p=0;
  left=NULL; right=NULL;}

CodingHuffman::CodingHuffman(const string n): Coding(n) {
  p=0;left=NULL; right=NULL;}
CodingHuffman::CodingHuffman(char c,string s): Coding(c,s)
{
  p = 0; left=NULL; right = NULL;
}
CodingHuffman::CodingHuffman(CodingHuffman* l, CodingHuffman* r) 
{
  name=l->getName()+r->getName();
  quantity=l->getQuantity()+r->getQuantity();
  p=l->getP()+r->getP();
  left=l;
  right=r;
  code="";
}

CodingHuffman::~CodingHuffman()
{
  if(left!=NULL)
    delete left;
  if(right!=NULL){
    delete right;
  }
}


//Get and Set
float CodingHuffman::getP()const{return p;}
CodingHuffman* CodingHuffman::getLeft()const{return left;}
CodingHuffman* CodingHuffman::getRight()const{return right;}

void CodingHuffman::setP(const float prob){p=prob;}


//Methode d'ajout d'occurence
void CodingHuffman::calculP(const int quantityElt){p=(float)quantity/(float)quantityElt;}

//Creation codage
//Creation codage
CodingHuffman* CodingHuffman::createCode(string code){
  //Crée le noeud gauche 
  if(left!=NULL)
    {
      string c(code);
      c=c+"0";
      left->createCode(c);
    }
  //Crée le noeud droit
  if(right!=NULL)
    {
      string c(code);
      c=c+"1";
      right->createCode(c);
    }
  if(left==NULL && right==NULL)
    {
      this->code=code;
      return this;
    }
}

void CodingHuffman::toStringTree()const
{
  cout << this->toString() << endl;
  if(left!=NULL)
    left->toStringTree();
  if(right!=NULL)
    right->toStringTree();
}
