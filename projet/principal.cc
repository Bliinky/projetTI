#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <vector>
using namespace std;
#include "other/StringFile.h"
#include "principal.h"
#include "Coding.h"
#include "CodingHuffman.h"
#include "TabCodingHuffman.h"
#include "TabCodingLZW.h"


const char* nameFile ="file.txt";

void huffmanCompress(StringFile& file)
{
  unsigned int n = 1;
  TabCodingHuffman v(file,n);
  CodingHuffman* root=v.createTree();
  string code="";
  root->createCode(code);
  //v.toString();
  StringFile* teste = v.codage(file,n);
  delete root;
  delete teste;
  return;
}
void huffmanDecompress(StringFile& file,char* newNameFile)
{
  unsigned int n = 1;
  TabCodingHuffman a;
  a.decodage(file,1,newNameFile);
  return;
}

void lzwCompress(StringFile& file)
{
  TabCodingLZW a(file);
  a.toString();
    delete a.codage(file);
  return;
}
void lzwDecompress(StringFile& file,char* name)
{
  TabCodingLZW a;
  delete a.decodage(file, name);
}
int main(int argc, char* argv[]){
  //string file = readFile(nameFile);
  if(argc != 3)
    {
      cout<<"Problème du nombre de paramètre"<<endl;
      return -1;
    }
  else
    {
      if(!strcmp(argv[1],"-c"))
	{
	  StringFile file(argv[2]);
	    lzwCompress(file);
	      /*char name[strlen(argv[2]) + 2];
	  strcpy(name,argv[2]);
	  //strcat(name,".l");
	  cout<<"Name "<<name<<endl;
	  StringFile file2(name);
	  huffmanCompress(file2);*/
	  return 1;
	}
      else
	{
	  if(!strcmp(argv[1],"-d"))
	    {
	      bool exit = false;
	      while(!exit)
		{
		  StringFile file(argv[2]);
		  char copie[256];
		  strcpy(copie,argv[2]);
		  copie[strlen(copie) - 2] = '\0';
		  if(!strcmp(argv[2] + strlen(argv[2]) - 2, ".h"))
		    {
		      huffmanDecompress(file,copie);
		    }
		  else{
		    if(!strcmp(argv[2] + strlen(argv[2]) - 2, ".l"))
		      {
			lzwDecompress(file,copie);
		      }
		    exit = true;
		  }
		  argv[2][strlen(argv[2]) - 2] = '\0';
		}  
	    }
	  else
	    {
	      cout<<"Veuillez entrer -d ou -c pour décompressser ou comprésser"<<endl;
	      return -1;
	    }
	}
    }
  //cout<<"taille fichier "<<file.size()<<endl;
  //unsigned int a=2;
  //unsigned int b=4;
  //cout<<file.iToj(a,b)<<endl;
  //lzw(file);
  //cout<<"oh"<<endl;
  return 1;
}

void huffman(const string file){
  //signed int nbChar = 1;
  TabCodingHuffman v(file);
  
  v.toString();
  CodingHuffman* root=v.createTree();
  string code="";
  root->createCode(code);
  //root->toStringTree();
  v.codage(file,1);
  //cout<<decode<<endl;
  //cout<<v.decodage(decode,1)<<endl;
  delete root;
}
void huffman(StringFile& file){
  //file.afficherFichier();
  unsigned int n = 1;
  TabCodingHuffman v(file,n);
  TabCodingHuffman a;
  CodingHuffman* root=v.createTree();
  string code="";
  root->createCode(code);
  //root->toStringTree();
  StringFile* teste = v.codage(file,n);
  v.toString();
  //a.createV(*teste);
  //a.toString();
  //a.toString();
  //teste->afficherFichier();
  //v.codage(file,n);
  //StringFile f("file.txt.h");
  //cout<<"yolo"<<endl;
  //f.afficherFichier();
  //cout<<decode<<endl;
  // cout<<"/////////////"<<endl;
  //  v.decodage(*teste,n);
  delete teste;
  delete root;
}

void lzw(const string file){
  unsigned int n = 3;
  TabCodingLZW v(file,n);
  TabCodingLZW vD(file,n);
  cout<<file<<endl;
  //cout<<v.codage(file)<<endl;
  cout<<vD.decodage(v.codage(file,n))<<endl;
  //v.toString();
  //vD.toString();
  cout<<"ho"<<endl;
}
void lzw(StringFile& file){
  unsigned int n = 2;
  TabCodingLZW v(file);
  TabCodingLZW vD(file);
  cout<<v.codage(file,1)<<endl;
  cout<<v.toString()<<endl;
  // cout<<vD.decodage(v.codage(file,2))<<endl;
  //v.toString();
  //vD.toString();
  
}

string readFile(const char* address){
  ifstream file(address, ios::in); 
  string buffer;
  string line;

  if(!file){
    cerr << "Impossible d'ouvrir le fichier !" 
	 << endl;
  }
  int sizeNotCharEnd=0;
  while(file.good()){buffer+=file.get(); sizeNotCharEnd++;}
  sizeNotCharEnd--;
  buffer.resize(sizeNotCharEnd);
  cout << "Le fichier est: "<<endl<<buffer<<endl;
  return buffer;
} 
