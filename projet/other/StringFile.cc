#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
#include "string.h"
#include "StringFile.h"

//Constructor
StringFile::StringFile(const char* file): rang(0),sizeClass(0)
{
  unsigned int sizeNameFile = strlen(file);
  name = new char[sizeNameFile];
  strcpy(name,file);
  //Ouvre un fichier de nom file
  this->file = new fstream(file,std::fstream::in | std::fstream::out);
  
  if(!(*file))
    {
      cerr << "Impossible d'ouvrir le fichier !" 
	   << endl;
    }
  //Compte le nombre de char
  while(this->file->good())
    {
      this->file->get();
      sizeClass++;
    }
  //
  sizeClass=sizeClass-1;
  this->file->clear();
  this->file->seekg(0,this->file->beg);
}
StringFile::StringFile(const char* file,unsigned int n): rang(0),sizeClass(0)
{
  unsigned int sizeNameFile = strlen(file);
  name = new char[sizeNameFile];
  for(unsigned int i = 0 ; i < sizeNameFile ; i++)
    {
      name[i] = file[i];
    }
  //Creation de fichier
  if(n == 0)
    {
      this->file = new fstream(file,ios::in|ios::out|ios::trunc|ios::ate);
      //*(this->file) << "hello"<<endl;
    }
  //Ouvre un fichier de nom file
  if(n == 1)
    {
      this->file = new fstream(file,ios::in|ios::out);
      
      if(!(*file))
	{
	  cerr << "Impossible d'ouvrir le fichier !" 
	       << endl;
	}
      //Compte le nombre de char
      while(this->file->good())
	{
	  this->file->get();
	  sizeClass++;
	}
      //
      sizeClass=sizeClass-1;
      this->file->clear();
      this->file->seekg(0,this->file->beg);
    }
}

StringFile::~StringFile(){
  if(file != NULL)
    {
      file->clear();
      delete file;
      delete name;
    }
}

//Get and Set
char * StringFile::getName()const{return name;}
fstream* StringFile::getFile()const{return file;}


/*string StringFile::iToj(unsigned int rang , unsigned int n)
{
  file->clear();
  this->file->seekg(0,this->file->beg);
  unsigned int copyRang=rang;
  unsigned int copyN=n;
  //Parcours les elt qui nous interesse pas
  while(copyRang!=0)
    {
      this->file->get();
      copyRang--;
    }
  ///////////////////////////////////////
  string result="";
  //Ajoute les elts qui nous interesse
  while(copyN!=0){
    copyN--;
    result = result + (char)this->file->get();
  }
  ////////////////////////////////////
  return result;
}*/

string StringFile::iToj(unsigned int rang , unsigned int n)
{
  file->clear();
  this->rang = rang;
  unsigned int copyRang = rang;
  unsigned int copyN=n;
  while(file->tellg()!=rang)
    {
      if(file->tellg() < rang)
	{
	  this->file->get();
	  this->rang= this->rang + 1;
	}
      else
	{
	  this->file->unget();
	  this->rang= this->rang - 1;
	}
    }
  //////
  ///////////////////////////////////////
  string result="";
  //Ajoute les elts qui nous interesse
  while(copyN!=0){
    copyN--;
    result = result + (char)this->file->get();
  }
  ////////////////////////////////////
  cout<<"result "<<result<<endl;
  return result;
}

int StringFile::size()const{
  return sizeClass;
  }

/*char StringFile::operator[](const unsigned int rang){
  /*int move = rang - this->rang ;
  cout<<"this rang "<<this->rang<<endl;
  cout<<"rang "<<rang<<endl;
  cout<<"move "<<move<<endl;
  cout<<"file->cur "<<this->file->cur<<endl;
  /*if(this->rang + move > sizeClass || 
     this->rang + move < -10 )
    {
      cout<<"Exception, sorti de tableau A faire"<<endl;
      return ' ';
      }
  
  file->clear();
  this->file->seekg(3,this->file->cur);
  cout<<"file->cur "<<this->file->cur<<endl;
  if(this->file->good())
    {
      this->rang=rang;
      return this->file->get();
    }
  else
    {
      
      cout<<"Erreur mais pourquoi?"<<endl;
      return ' ';
      }
*//*
  file->clear();
  this->file->seekg(0,this->file->beg);
  unsigned int copieRang=rang;
  
  //Parcours les élts inutile
  while(copieRang!=0)
    {
      this->file->get();
      copieRang--;
    }
  /////////////////////////////
  if(!file->good())
    {
      cout<<"erreur"<<endl;
    }
  return this->file->get();

  }*/
char StringFile::operator[](const unsigned int rang){
  /*int move = rang - this->rang ;
  cout<<"this rang "<<this->rang<<endl;
  cout<<"rang "<<rang<<endl;
  cout<<"move "<<move<<endl;
  cout<<"file->cur "<<this->file->cur<<endl;
  /*if(this->rang + move > sizeClass || 
     this->rang + move < -10 )
    {
      cout<<"Exception, sorti de tableau A faire"<<endl;
      return ' ';
      }
  
  file->clear();
  this->file->seekg(3,this->file->cur);
  cout<<"file->cur "<<this->file->cur<<endl;
  if(this->file->good())
    {
      this->rang=rang;
      return this->file->get();
    }
  else
    {
      
      cout<<"Erreur mais pourquoi?"<<endl;
      return ' ';
      }
*/
  file->clear();
  while(rang != file->tellg())
    {
      if(rang > file->tellg())
	{
	  this->file->get();
	  this->rang= this->rang + 1;
	}
      else
	{
	  this->file->unget();
	  this->rang= this->rang - 1;
	}
    }
  return this->file->get();

}

void StringFile::addOctet(bool* isCoding)
{
  unsigned int newChar = 0;
  unsigned int val = 128;
  for(int i = 0 ; i < 8 ; i++)
    {
      if(isCoding[i])
	{
	  newChar = newChar + val;

	}
      val = val / 2;
    }
  char addFile = (char)newChar;
  //file->put(addFile);
  //*(this->file) << "hello" << endl;
  stringstream ss;
  string s;
  ss << addFile;
  ss >> s;
  *(this->file) << addFile;
  sizeClass++;
}

void StringFile::addString(string isDecoding)
{
  *(file) << isDecoding;
  sizeClass++;
}
void StringFile::addNewLine()
{
  *(file)<<flush;
}

void StringFile::afficherFichier()
{
  for(int i = 0 ; i < this->size() ; i++)
    {
      file->clear();
      this->file->seekg(0,this->file->beg);
      unsigned int copieRang=i;
      
      //Parcours les élts inutile
      while(copieRang!=0)
	{
	  this->file->get();
	  copieRang--;
	}
      /////////////////////////////
      if(!file->good())
	{
	  cout<<"erreur"<<endl;
	}
      
    }
}

void StringFile::cp(StringFile* copy)
{
  copy->getFile()->seekg(0,this->file->beg);
  for(int i = 0 ; i < copy->size() ; i ++)
    {
      (*file) << (*(copy))[i];
    }
  /*  while(copy->getFile()->good())
    {
      
      *(file) << copy->getFile()->get();
      }*/
  return;
}

