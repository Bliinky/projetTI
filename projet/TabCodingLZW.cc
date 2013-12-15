#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <string.h>
using namespace std;

#include "Coding.h"
#include "other/StringFile.h"
#include "TabCodingLZW.h"
unsigned int valCodeInt = 0;

//Constructeur et initialise le dictionnaire


TabCodingLZW::TabCodingLZW(){}



//Pour les string

TabCodingLZW::TabCodingLZW(const string file)
{
  int quantityElt=file.size(); //Quantité d'élément dans un stirng 
  int codeInt=0;
  //Parcours tous les éléments du fichier
  for(int i=0;i<quantityElt;i++)
    {
      bool isPresent=false;
      //Parcours la table de codage 
      for(int j=0;j<v.size();j++)
	{
	  if(file[i]==v[j]->getName()[0])
	    {
	      isPresent=true;
	      v[j]->upQuantity();
	      //sortElt(j);
	    }
	}
      ////////////////////////////////////////
      //Ajoute dans la table de codage un elt
      if(!isPresent)
	{
	  Coding* newElt=new Coding(file[i],codeInt);
	  codeInt++;
	  v.push_back(newElt);
	}
      //////////////////////////////////////
    }
  ///////////////////////////////////////////
}
TabCodingLZW::TabCodingLZW(const string file,unsigned int n )
{
  int quantityElt=file.size(); //Taille du fichier 
  int codeInt=0;
  vector<char> allChar;
  //Parcours le fichier 
  for(int i=0;i<quantityElt;i++)
    {
      bool isPresent=false;
      char compare=file[i];
      //Parcours l'ensemble des char deja présents
      for(int j=0;j<allChar.size();j++)
	{
	  if(compare==allChar[j])
	    {
	      isPresent=true;
	    }
	}
      //////////////////////////////////////////
      //Ajoute un élement non present
      if(!isPresent)
	{
	  allChar.push_back(compare);
	}
      //////////////////////////////////
    }
  /////////////////////////////////////////////
  string word="";
  valCodeInt=0;
  createDictionary(allChar,word,n); //Création dico
}

string TabCodingLZW::codage(const string file , unsigned int n)
{
  int sizeFile = file.size() -  (file.size() % n); //Taille du file moins le surplus non éxpoitable
  int intCode=v.size();
  Coding* encoding=NULL;
  string result="";
  int tripFile=0;
  //Parcours le fichier
  while(tripFile < sizeFile)
    {
      //Parcours la table de codage
      for(int i=0;i<v.size();i++)
	{
	  bool isEncoding=true;
	  //Parcours le nom de l'élt i de la table
	  for(int j=0;j<v[i]->getNameSize();j++)
	    {
	      //Si on ne dépasse pas la taille du fichier
	      if(tripFile+j<sizeFile)
		{
		  //Si les deux char sont différents alors l'élément i dans la table de codage ne correspond pas
		  if(file[tripFile+j]!=v[i]->getNameRang(j))
		    {
		      isEncoding=false;
		      j=v[i]->getNameSize();
		    }
		  //////////////////////////////////
		}
	      /////////////////////////////////////
	      //L'élément ne corresponds pas dans la table de codage 
	      else
		{
		  j=v[i]->getNameSize();
		  isEncoding=false;
		}
	      ////////////////////////////////
	    }
	  ////////////////////////////////////////
	  //Si on peux encoder avec l'elt trouvé
	  if(isEncoding)
	    {
	      //Si l'elt trouvé est plus grand que l'ancien alors on le garde en mémoire 
	      if(encoding!=NULL && 
		 encoding->getNameSize()<v[i]->getNameSize())
		{
		  encoding=v[i];
		} 
	      //////////////////////////////////////////////
	      else
		{
		  //Si il n'y pas d'ancien alors on garde l'élt trouvé 
		  if(encoding==NULL)
		    {
		      encoding=v[i];
		    }
		  ////////////////////////////////////////
		}
	    }
	}
	  //////////////////////////////////////////////
	  //On se place au nouveau endroit dans le fichier 
	  tripFile=tripFile+encoding->getNameSize();
	  //On ajoute l'encodage dans le résultat
	  result=result + encoding->getCode()+" ";
	  //Fais attention de pas faire une error de seg dans le fichier et ajoute un elt dans la table de codage
	  if(tripFile < sizeFile)
	    {
	      string iToj="";
	      if(tripFile + n < sizeFile){
		for(int k = tripFile ; k < tripFile + n ; k++)
		  {
		    iToj = iToj + file[k];
		  }
	      }
	      if(iToj != "")
		{
		  Coding* newEltDic=new Coding(encoding->getName(),iToj,intCode);
		  intCode++;
		  v.push_back(newEltDic);
		}
	    }
	  ///////////////////////////////////////////////
	  encoding=NULL;
    }
      /////////////////////////////////////////
  return result;
}

string TabCodingLZW::decodage(const string decoding){
  cout<<"Voici un code de lZW "<<decoding<<endl;
  string puzzleOut=""; //Mot decoder à un instant t
  string s="";
  int intCode=v.size();
  //Parcours le mot à decoder
  for(int i=0;i<decoding.size();i++)
    {
      bool b=false; //b permet de savoir quand on a trouvé le codage
      //Si il y a un espace alors on a recup le codage
      if(decoding[i]==' ')
	{
	  cout<<"Mot à decoder LZW "<<s<<endl;
	  b=true;
	}
      ////////////////////////////////////////////////
      //Sinon on ajoute, le char dans le codage
      else
	{
	  s = s + decoding[i];
	}
    int eltV=-1;
    //Si on a trouvé le codage correspondant
    if(b)
      {
	//On cherche dans la table de codage le correspodant
	for(int j=0;j<v.size();j++)
	  {
	    //Quand on l'a trouvé, on le rajoute dans le mot decoder
	    if(v[j]->getCode()==s)
	      {
		eltV=j;
		puzzleOut+=v[j]->getName();
	      }
	    ///////////////////////////////////////////////
	  }
	//////////////////////////////////////////////////
	//On chrche ici l'élément suivant à decoder pour le rajouter dans la table de codage. On utilise excactement le même principe que précédament
	string nextCoding="";
	bool nextB=false;
	for(int j=i+1;j<decoding.size();j++)
	  {
	    if(decoding[j]==' ')
	      {
		nextB=true;
	      }
	    else
	      {
		nextCoding+=decoding[j];
	      }
	    if(nextB)
	      {
		for(int k=0;k<v.size();k++)
		  {
		    //Ajoute un element dans la table de codage
		    if(v[k]->getCode()==nextCoding)
		      {
			Coding* newElt=new Coding(v[eltV]->getName(),v[k]->getName(),intCode);
			intCode++;
			v.push_back(newElt);
		      }
		    //////////////////////////////////
		  }
	      }
	  }
	s = "";
      }
    }
  return puzzleOut;
}

int TabCodingLZW::createV(StringFile& decoding)
{
  int sizeDico = decoding[1];
  for(int i = 2 ; i < sizeDico + 2 ; i++)
    {
      Coding* c = new Coding(decoding[i], i - 2);
      v.push_back(c);
    }

  return sizeDico + 2;
}

StringFile* TabCodingLZW::decodage(StringFile& decoding,char* nameFile){
  cout<<"hello"<<endl;
  int firstOctet = decoding[0];
  int sizeFirstOctet = 0;
  bool boolFirstOctet[8];
  int val = 128;
  int f = 8;
  cout<<val<<endl;
  if((int)firstOctet < 0)
    firstOctet = (int)firstOctet + 256;
  cout<<(int)firstOctet<<endl;
  while(firstOctet < val)
    {
      val = val / 2;
      f--;
    }
  cout<<f<<endl;
  f--;
  firstOctet = firstOctet - val;
  val = val / 2;
  for(int k = 0; k < f ; k++)
    {
      if(firstOctet >= val)
	{
	  boolFirstOctet[k] = true;
	  firstOctet = firstOctet - val;
	}
      else
	{
	  boolFirstOctet[k] = false;
	}
      val = val / 2;
    }
  StringFile* isDecoding = new StringFile(nameFile,0);

  string puzzleOut=""; //Mot decoder à un instant t
  string s="";
  int intCode=v.size();
  int i = createV(decoding);
  int quantityEltDicoInitial = i - 2 ;
  int powerTwo = 2;
  int readNext = 0;
  bool aDechiffrerDebut[8];
  bool aDechiffrerFin[100];
  int bitsRead = 1;
  while(quantityEltDicoInitial > powerTwo)
    {
      bitsRead++;
      powerTwo = powerTwo * 2;
    }
  int finalyDico = quantityEltDicoInitial;
  //Parcours le mot à decoder
  for(i;i<decoding.size();i++)
    {
      unsigned int valDecoder=128;
      unsigned int deb = 0;
      char addChar = decoding[i];
      //Permet de récuperer l'octet à decoder
      while(deb != 8)
	{
	  if(addChar >= valDecoder)
	    {
	      aDechiffrerDebut[deb] = true;
	      addChar = addChar - valDecoder;
	    } 
	  else
	    {
	      aDechiffrerDebut[deb] = false;
	    }
	  deb++;
	  valDecoder = valDecoder / 2;
	  
	}
      for(int g = 0 ; g < 8 ; g++)
	{
	  cout<<aDechiffrerDebut[g];
	}
      cout<<endl;
      //Recup au max 4 octet suivant
      int quantityOctetNext = 0;
      for(int k = 0 ; k < 4 ; k++)
	{
	  if(i + k + 1 < decoding.size())
	    {
	      valDecoder = 128;
	      deb = 0;
	      addChar = decoding[(i + k + 1)];
	      
	      
	      while(deb != 8)
		{
		  if(addChar >= valDecoder)
		    {
		      aDechiffrerFin[deb + (quantityOctetNext * 8)] = true;
		      cout<<true;
		      addChar = addChar - valDecoder;
		    } 
		  else
		    {
		      cout<<false;
		      aDechiffrerFin[deb + (quantityOctetNext * 8)] = false;
		    }
		  deb++;
		  valDecoder = valDecoder / 2;
		  
		} 
	      cout<<endl;
	      quantityOctetNext++;
	    }
	}
      int parcoursBool = 0;
      if(readNext > 8)
	{
	  parcoursBool = 8;
	  readNext = readNext - 8;
	}
      //Si on a pas parcouru ou partiellement l'octet suivant 
      else{
	parcoursBool = readNext;
	readNext = 0;
      }
      //cout<<"voici parcoursBool "<<parcoursBool<<endl;
      cout<<endl;
      int endFileRead = 0;
      while (parcoursBool < 8)
	{
	  int code = powerTwo -  1;
	  int powerTwoDivTwo = powerTwo / 2;
	  for(int k = 0 ; k < bitsRead ; k++)
	    {
	      if(parcoursBool < 8)
		{
		  if(aDechiffrerDebut[parcoursBool] == false)
		    {
		  code = code - powerTwoDivTwo;
		    }
		  
		  powerTwoDivTwo  = powerTwoDivTwo / 2;
		}
	      else
		{
		  if(quantityOctetNext == 0){
		    cout<<"yolo"<<endl;
		    if(boolFirstOctet[endFileRead] == false)
		      {
			code = code - powerTwoDivTwo;
		      }
		    powerTwoDivTwo  = powerTwoDivTwo / 2;
		    readNext++;
		    endFileRead++;
		  }
		  else
		    {
		      if(aDechiffrerFin[parcoursBool - 8] == false)
			{
			  code = code - powerTwoDivTwo;
			}
		      powerTwoDivTwo  = powerTwoDivTwo / 2;
		      readNext++;
		    }
		}
	      
	      parcoursBool++;
	    }
	  //cout<<"parcoursBool round 2 "<<parcoursBool<<endl;
	  if(v.size() + 1 > powerTwo)
	    {
	      bitsRead++;
	      powerTwo = powerTwo * 2;
	    }
	  //cout<<"PowerTwo "<<powerTwo<<endl;
	  //cout<<"bitsRead "<<bitsRead<<endl;
	  isDecoding->addString(v[code]->getName());
	  isDecoding->addNewLine();
	  int parcoursBoolCopy = parcoursBool;
	  powerTwoDivTwo = powerTwo / 2;
	  int codeNext = powerTwo - 1;
	  for(int k = 0 ; k < bitsRead ; k++)
	    {
	      if(parcoursBoolCopy < 8)
		{
		  if(aDechiffrerDebut[parcoursBoolCopy] == false)
		    {
		  codeNext = codeNext - powerTwoDivTwo;
		    }
		  
		  powerTwoDivTwo  = powerTwoDivTwo / 2;
		}
	      else
		{
		   if(quantityOctetNext == 0){
		     if(boolFirstOctet[endFileRead] == false)
		       {
			 codeNext = codeNext - powerTwoDivTwo;
		       }
		     cout<<"yolo"<<endl;
		     powerTwoDivTwo  = powerTwoDivTwo / 2;
		     readNext++;
		     endFileRead++;
		   }
		   else
		     {
		       if(aDechiffrerFin[parcoursBoolCopy - 8] == false)
			 {
			   codeNext = codeNext - powerTwoDivTwo;
			 }
		       powerTwoDivTwo  = powerTwoDivTwo / 2;
		       //readNext++;
		     }
		}
	      parcoursBoolCopy++;
	    }
	  cout<<"Code" <<code<<" CodeNext "<<codeNext<<endl;
	  if(codeNext != v.size())
	    cout<<v[code]->getName()<<" "<<v[codeNext]->getName()<<endl;
	  Coding* newElt = NULL;
	  //cout<<"taille v "<<v.size()<<endl;
	  if(codeNext == v.size())
	    {
	      cout<<"yolo"<<endl;
	      newElt = new Coding(v[code]->getName(),v[code]->getNameRang(0),finalyDico);
	    }
	  else
	    {
	      newElt = new Coding(v[code]->getName(),v[codeNext]->getNameRang(0),finalyDico);
	    }
	  finalyDico++;
	  v.push_back(newElt);
	  
	}
    }
  for(int i = 0 ; i < v.size() ; i++)
    {
      v[i]->toString();
    }
  cout<<(int)firstOctet<<endl;
  for(int i = 0 ; i < 8 ; i++)
    {
      cout<<      boolFirstOctet[i];
    }
  cout<<endl;
  return isDecoding;
}



//Pour les StrinFile

TabCodingLZW::TabCodingLZW(StringFile& file)
{
  int quantityElt=file.size(); //Taille du fichier
  int codeInt=0;
  //Parcours le fichier 
  for(int i=0;i<quantityElt;i++)
    {
      bool isPresent=false;
      char compare=file[i];
      //Parcours la table de codage
      for(int j=0;j<v.size();j++)
	{
	  //Compare  deux éléments
	  if(compare==v[j]->getName()[0])
	    {
	      isPresent=true;
	      v[j]->upQuantity();
	      //sortElt(j);
	    }
	  /////////////////////////////////////
	}
      //////////////////////////////////////
      //Ajout d'un élément non présent dans la table
      if(!isPresent)
	{
	  Coding* newElt=new Coding(compare,codeInt);
	  codeInt++;
	  v.push_back(newElt);
	}
      //////////////////////////////////
    }
  //////////////////////////////////////////
}
TabCodingLZW::TabCodingLZW(StringFile& file,unsigned int n )
{
  int quantityElt=file.size(); //Taille du fichier 
  int codeInt=0;
  vector<char> allChar;
  //Parcours le fichier 
  for(int i=0;i<quantityElt;i++)
    {
      bool isPresent=false;
      char compare=file[i];
      //Parcours l'ensemble de char
      for(int j=0;j<allChar.size();j++)
	{
	  //Si l'élt est deja présent 
	  if(compare==allChar[j])
	    {
	      isPresent=true;
	    }
	  //////////////////////////
	}
      /////////////////////////////////
      //Si l'élement n'est pas présent, ajouter
      if(!isPresent)
	{
	  allChar.push_back(compare);
	}
      ////////////////////////////////////////
    }
  /////////////////////////////////////////////
  string word="";
  valCodeInt=0;
  createDictionary(allChar,word,n);
}

 string TabCodingLZW::codage(StringFile& file , unsigned int n)
{
  unsigned int sizeFile = file.size() - (file.size() % n); //Taille du file moins le surplus non éxpoitable
  int intCode=v.size();
  Coding* encoding=NULL;
  string result="";
  int tripFile=0;
  //Parcours le fichier
  while(tripFile < sizeFile)
    {
      //Parcours la table de codage
      for(int i=0;i<v.size();i++)
	{
	  bool isEncoding=true;
	  //Parcours le nom de l'élt i de la table
	  for(int j=0;j<v[i]->getNameSize();j++)
	    {
	      //Si on ne dépasse pas la taille du fichier
	      if(tripFile+j<sizeFile)
		{
		  //Si les deux char sont différents alors l'élément i dans la table de codage ne correspond pas
		  if(file[tripFile+j]!=v[i]->getNameRang(j))
		    {
		      isEncoding=false;
		      j=v[i]->getNameSize();
		    }
		}
	      /////////////////////////////////////////
	      //L'élément ne corresponds pas dans la table de codage 
	      else
		{
		  j=v[i]->getNameSize();
		  isEncoding=false;
		}
	      /////////////////////////////////////////
	    }
	  ////////////////////////////////////////////
	  //Si on peux encoder avec l'elt trouvé
	  if(isEncoding)
	    {
	      //Si l'elt trouvé est plus grand que l'ancien alors on le garde en mémoire 
	      if(encoding!=NULL && 
		 encoding->getNameSize()<v[i]->getNameSize())
		{
		  encoding=v[i];
		}
	      //////////////////////////////////////////
	      else
		{
		  //Si il n'y pas d'ancien alors on garde l'élt trouvé 
		  if(encoding==NULL)
		    {
		      encoding=v[i];
		    }
		  ///////////////////////////////////
		}
	    }
	}
      /////////////////////////////////////////////////
      //On se place au nouveau endroit dans le fichier 
      tripFile=tripFile+encoding->getNameSize();
      //On ajoute l'encodage dans le résultat
      result=result + encoding->getCode()+" ";
      //Fais attention de pas faire une error de seg dans le fichier et ajoute un elt dans la table de codage
      if(tripFile < sizeFile)
	{
	  string iToj = "";
	  if(tripFile + n < sizeFile)
	    {
	      iToj = file.iToj(tripFile,n);
	    }
	  if(iToj != "")
	    {
	      Coding* newEltDic=new Coding(encoding->getName(),iToj,intCode);
	      intCode++;
	      v.push_back(newEltDic);
	    }
	}
      ////////////////////////////
      encoding=NULL;
    }
  
  return result;
}
/*StringFile* TabCodingLZW::codage(StringFile& file  )
{
  vectorOrdeed();
  char* nameCopie = new char[strlen(file.getName()) + 10];
  strcpy(nameCopie,file.getName());
  strcat(nameCopie,"l");
  StringFile* isCoding   = new StringFile(nameCopie,0);
  bool coding[8];
  int rangIsCoding = 0;
  unsigned int sizeFile = file.size(); //Taille du file 
  int intCode=v.size();
  int intCodeInitial = v.size();
  int quantityBits = 1;
  int powerDeux = 2;
  Coding* encoding=NULL;
  string result="";
  int tripFile=0;   
  strcpy(nameCopie,file.getName());
  strcat(nameCopie,".l");
  StringFile* dicoIsCoding= new StringFile(nameCopie,0);
 
  while(powerDeux <= intCode - 1)
    {
      powerDeux = powerDeux * 2;
    }
  //Parcours le fichier
  while(tripFile < sizeFile)
    {
      cout<<tripFile<<endl;
      //Parcours la table de codage
      ///////////NEW
      bool exit = false;
      int deb = 0;
      int fin = v.size() - 1;
      int d = 0
      while(!exit)
	{
	  d = (deb + fin)/2;
	  bool inf = false;
	  bool sup = false;
	  for(int j=0;j<v[d]->getNameSize();j++)
	    {
	      //Si on ne dépasse pas la taille du fichier
	      if(tripFile+j<sizeFile)
		{
		  char fileChar = file[tripFile+j]
		  //Si les deux char sont différents alors l'élément i dans la table de codage ne correspond pas
		  if(fileChar<v[d]->getNameRang(j))
		    {
		      if(!sup)
			inf = true;
		      isEncoding=false;
		      j=v[i]->getNameSize();
		      
		    }
		  else
		    {
		      if(fileChar>v[d]->getNameRang(j))
			{
			  if(!inf)
			    sup = true;
			  isEncoding=false;
			  j=v[i]->getNameSize();
		      
			}
		    }
		}
	      /////////////////////////////////////////
	      //L'élément ne corresponds pas dans la table de codage 
	      else
		{
		  j=v[d]->getNameSize();
		  isEncoding=false;
		}
	    }
	  if(isEncoding)
	    {
	      exit= true;
	      encoding = v[d];
	    }
	  else
	    {
	      if(inf)
		deb = d + 1; 
	      if(sup)
		fin = d - 1;
	    }
	}
      bool codable = true;
      while(codable)
	{
	  if(d + 1< v.size())
	    {
	      for(int j = 0;j<v[d + 1]->getNameSize();j++)
		{
		  if(tripFile+j < sizeFile)
		    {
		      //Si les deux char sont différents alors l'élément i dans la table de codage ne correspond pas
		      if(file[tripFile+j]!=v[i]->getNameRang(j))
			{
			  codable=false;
			  j=v[i]->getNameSize();
			}
		    }
		  else
		    {
		      j=v[i]->getNameSize();
		      codable=false;
		    }
		}
	      if(codable)
		{
		  encoding = v[i];
		  d++;
		}
	    }
	}
	/////////END NEW
	/*
	for(int i=0;i<v.size();i++)
	{
	  bool isEncoding=true;
	  //Parcours le nom de l'élt i de la table
	  for(int j=0;j<v[i]->getNameSize();j++)
	    {
	      //Si on ne dépasse pas la taille du fichier
	      if(tripFile+j<sizeFile)
		{
		  //Si les deux char sont différents alors l'élément i dans la table de codage ne correspond pas
		  if(file[tripFile+j]!=v[i]->getNameRang(j))
		    {
		      isEncoding=false;
		      j=v[i]->getNameSize();
		    }
		}
	      /////////////////////////////////////////
	      //L'élément ne corresponds pas dans la table de codage 
	      else
		{
		  j=v[i]->getNameSize();
		  isEncoding=false;
		}
	      /////////////////////////////////////////
	    }
	  ////////////////////////////////////////////
	  //Si on peux encoder avec l'elt trouvé
	  if(isEncoding)
	    {
	      //Si l'elt trouvé est plus grand que l'ancien alors on le garde en mémoire 
	      if(encoding!=NULL && 
		 encoding->getNameSize()<v[i]->getNameSize())
		{
		  encoding=v[i];
		}
	      //////////////////////////////////////////
	      else
		{
		  //Si il n'y pas d'ancien alors on garde l'élt trouvé 
		  if(encoding==NULL)
		    {
		      encoding=v[i];
		    }
		  ///////////////////////////////////
		}
	    }
	    }*//*
      /////////////////////////////////////////////////
      //On se place au nouveau endroit dans le fichier 
      tripFile=tripFile+encoding->getNameSize();
      //On ajoute l'encodage dans le résultat
      //cout<<powerDeux<<endl;
      int copiePowerTwo = powerDeux;
      int copiePowerTwoDivTwo = powerDeux / 2;
      int valCode = atoi(encoding->getCode().c_str());
      while(copiePowerTwo != 1)
	{
	  if(valCode >= copiePowerTwoDivTwo && valCode != 0)
	    {
	      coding[rangIsCoding] = true;            
	      valCode = valCode - copiePowerTwoDivTwo;
	    }
	  else
	    {
	      coding[rangIsCoding] = false;
	    }
	 
	  rangIsCoding++;
	  rangIsCoding = rangIsCoding % 8;
	  if(rangIsCoding == 0)
	    {
	      isCoding->addOctet(coding);
	    } 
	  copiePowerTwoDivTwo = copiePowerTwoDivTwo / 2;
	  copiePowerTwo = copiePowerTwo / 2;
	}
      result=result + encoding->getCode()+" ";
      //Fais attention de pas faire une error de seg dans le fichier et ajoute un elt dans la table de codage
      if(tripFile < sizeFile)
	{
	  string iToj = "";
	  if(tripFile + 1 < sizeFile)
	    {
	      iToj = file.iToj(tripFile,1);
	    }
	  if(iToj != "")
	    {
	      Coding* newEltDic=new Coding(encoding->getName(),iToj,intCode);
	      intCode++;
	      if(intCode - 1  >= powerDeux)
		{
		  powerDeux = powerDeux * 2;
		  quantityBits++;
		}
	      v.push_back(newEltDic);
	    }
	}
      ////////////////////////////
      encoding=NULL;
    }
  bool firstOctet[8];
  int parcoursCoding = 0;
  cout<<rangIsCoding<<endl;
  //  if(rangIsCoding > 0) rangIsCoding--;
  for(int i = 0 ; i < 8 ; i++)
    {
      if(7 - i  == rangIsCoding )
	{
	  firstOctet[i] = true;
	} 
      else{
	if(7 - i  < rangIsCoding)
	  {
	    firstOctet[i] = coding[parcoursCoding];
	    parcoursCoding++;
	  }
	else
	  {
	    firstOctet[i] = false;
	  }
      }
    }

  dicoIsCoding->addOctet(firstOctet);

  int valDicoCoding = 128;
  int g=0;
  intCode = intCodeInitial;
  while(valDicoCoding != 0)
    {
      if(intCode  >= valDicoCoding)
	{
	  coding[g] = true;
	  intCode = intCode - valDicoCoding;
	}
      else
	{
	  coding[g] = false;
	}
      g++;
      valDicoCoding = valDicoCoding / 2;
    }
  dicoIsCoding->addOctet(coding);
  intCode = intCodeInitial;
  for(int i = 0 ; i < intCode ; i++)
    {
      dicoIsCoding->addString(v[i]->getName());
    }
  isCoding->addNewLine();
  dicoIsCoding->cp(isCoding);
  dicoIsCoding->addNewLine();
   for(int i = 0 ; i < v.size() ; i++)
    {
      v[i]->toString();
    }
  delete isCoding;
  return dicoIsCoding;
}*/

      /*StringFile* TabCodingLZW::codage(StringFile& file  )
{
  vectorOrdeed();
  createCode();
  this->toString();
  char* nameCopie = new char[strlen(file.getName()) + 10];
  strcpy(nameCopie,file.getName());
  strcat(nameCopie,"l");
  StringFile* isCoding   = new StringFile(nameCopie,0);
  bool coding[8];
  int rangIsCoding = 0;
  unsigned int sizeFile = file.size(); //Taille du file 
  int intCode=v.size();
  int intCodeInitial = v.size();
  int quantityBits = 1;
  int powerDeux = 2;
  Coding* encoding=NULL;
  string result="";
  int tripFile=0;   
  strcpy(nameCopie,file.getName());
  strcat(nameCopie,".l");
  StringFile* dicoIsCoding= new StringFile(nameCopie,0);
 
  while(powerDeux <= intCode - 1)
    {
      powerDeux = powerDeux * 2;
    }
  //Parcours le fichier
  while(tripFile < sizeFile)
    {
      //cout<<tripFile<<endl;
      //Parcours la table de codage
      ///////////NEW
      bool exit = false;
      int deb = 0;
      int fin = v.size() - 1;
      int d = 0;
      while(!exit)
	{
	  d = (deb + fin)/2;
	  bool inf = false;
	  bool sup = false;
	  bool isEncoding = true;
	  for(int j=0;j<v[d]->getNameSize();j++)
	    {
	      char fileChar = file[tripFile+j];
	      //Si on ne dépasse pas la taille du fichier
	      if(tripFile+j<sizeFile)
		{
		  //Si les deux char sont différents alors l'élément i dans la table de codage ne correspond pas
		  if(fileChar<v[d]->getNameRang(j))
		    {
		      if(!inf)
			sup = true;
		      isEncoding=false;
		      j=v[d]->getNameSize();
		      
		    }
		  else
		    {
		      if(fileChar>v[d]->getNameRang(j))
			{
			  if(!sup)
			    inf = true;
			  isEncoding=false;
			  j=v[d]->getNameSize();
		      
			}
		    }
		}
	      /////////////////////////////////////////
	      //L'élément ne corresponds pas dans la table de codage 
	      else
		{
		  j=v[d]->getNameSize();
		  isEncoding=false;
		}
	    }
	  if(isEncoding)
	    {
	      exit= true;
	      encoding = v[d];
	    }
	  else
	    {
	      //cout<<fin<<endl;
	      if(inf)
		deb = d + 1; 
	      if(sup)
		fin = d - 1;
	    }
	}
      bool codable = true;
      cout<<"Enco1 "<<encoding->getName()<<endl;
      while(codable)
	{
	  if(d + 1< v.size())
	    {
	      for(int j = 0;j<v[d + 1]->getNameSize();j++)
		{
		  if(tripFile+j < sizeFile)
		    {
		      //Si les deux char sont différents alors l'élément i dans la table de codage ne correspond pas
		      if(file[tripFile+j]!=v[d]->getNameRang(j))
			{
			  codable=false;
			  j=v[d]->getNameSize();
			}
		    }
		  else
		    {
		      j=v[d]->getNameSize();
		      codable=false;
		    }
		}
	      if(codable)
		{
		  encoding = v[d];
		  d++;
		}
	    }
	}
      cout<<"Enco2 "<<encoding->getName()<<endl;
	/////////END NEW
	


      /*
	for(int i=0;i<v.size();i++)
	{
	  bool isEncoding=true;
	  //Parcours le nom de l'élt i de la table
	  for(int j=0;j<v[i]->getNameSize();j++)
	    {
	      //Si on ne dépasse pas la taille du fichier
	      if(tripFile+j<sizeFile)
		{
		  //Si les deux char sont différents alors l'élément i dans la table de codage ne correspond pas
		  if(file[tripFile+j]!=v[i]->getNameRang(j))
		    {
		      isEncoding=false;
		      j=v[i]->getNameSize();
		    }
		}
	      /////////////////////////////////////////
	      //L'élément ne corresponds pas dans la table de codage 
	      else
		{
		  j=v[i]->getNameSize();
		  isEncoding=false;
		}
	      /////////////////////////////////////////
	    }
	  ////////////////////////////////////////////
	  //Si on peux encoder avec l'elt trouvé
	  if(isEncoding)
	    {
	      //Si l'elt trouvé est plus grand que l'ancien alors on le garde en mémoire 
	      if(encoding!=NULL && 
		 encoding->getNameSize()<v[i]->getNameSize())
		{
		  encoding=v[i];
		}
	      //////////////////////////////////////////
	      else
		{
		  //Si il n'y pas d'ancien alors on garde l'élt trouvé 
		  if(encoding==NULL)
		    {
		      encoding=v[i];
		    }
		  ///////////////////////////////////
		}
	    }
	}*/
      /////////////////////////////////////////////////
      //On se place au nouveau endroit dans le fichier 
      tripFile=tripFile+encoding->getNameSize();
      //On ajoute l'encodage dans le résultat
      //cout<<powerDeux<<endl;
      int copiePowerTwo = powerDeux;
      int copiePowerTwoDivTwo = powerDeux / 2;
      cout<<"D "<<d<<endl;
      cout<<"A "<<atoi(encoding->getCode().c_str())<<endl;
      int valCode = d;//d-1?//atoi(encoding->getCode().c_str());
      while(copiePowerTwo != 1)
	{
	  if(valCode >= copiePowerTwoDivTwo && valCode != 0)
	    {
	      coding[rangIsCoding] = true;            
	      valCode = valCode - copiePowerTwoDivTwo;
	    }
	  else
	    {
	      coding[rangIsCoding] = false;
	    }
	 
	  rangIsCoding++;
	  rangIsCoding = rangIsCoding % 8;
	  if(rangIsCoding == 0)
	    {
	      /*for(int w = 0 ; w < 8 ; w++)
		{
		  cout<<coding[w];
		}
		cout<<endl;*/
	      isCoding->addOctet(coding);
	    } 
	  copiePowerTwoDivTwo = copiePowerTwoDivTwo / 2;
	  copiePowerTwo = copiePowerTwo / 2;
	}
      result=result + encoding->getCode()+" ";
      //Fais attention de pas faire une error de seg dans le fichier et ajoute un elt dans la table de codage
      if(tripFile < sizeFile)
	{
	  string iToj = "";
	  if(tripFile + 1 < sizeFile)
	    {
	      iToj = file.iToj(tripFile,1);
	    }
	  if(iToj != "")
	    {
	      Coding* newEltDic=new Coding(encoding->getName(),iToj,intCode);
	      intCode++;
	      if(intCode - 1  >= powerDeux)
		{
		  powerDeux = powerDeux * 2;
		  quantityBits++;
		}
	      insert(encoding->getCode(),newEltDic);
	      this->toString();
	    }
	}
      ////////////////////////////
      encoding=NULL;
    }
  bool firstOctet[8];
  int parcoursCoding = 0;
  //cout<<rangIsCoding<<endl;
  //  if(rangIsCoding > 0) rangIsCoding--;
  for(int i = 0 ; i < 8 ; i++)
    {
      if(7 - i  == rangIsCoding )
	{
	  firstOctet[i] = true;
	} 
      else{
	if(7 - i  < rangIsCoding)
	  {
	    firstOctet[i] = coding[parcoursCoding];
	    parcoursCoding++;
	  }
	else
	  {
	    firstOctet[i] = false;
	  }
      }
    }

  dicoIsCoding->addOctet(firstOctet);

  int valDicoCoding = 128;
  int g=0;
  intCode = intCodeInitial;
  while(valDicoCoding != 0)
    {
      if(intCode  >= valDicoCoding)
	{
	  coding[g] = true;
	  intCode = intCode - valDicoCoding;
	}
      else
	{
	  coding[g] = false;
	}
      g++;
      valDicoCoding = valDicoCoding / 2;
    }
  dicoIsCoding->addOctet(coding);
  intCode = intCodeInitial;
  for(int i = 0 ; i < intCode ; i++)
    {
      dicoIsCoding->addString(v[i]->getName());
    }
  isCoding->addNewLine();
  dicoIsCoding->cp(isCoding);
  dicoIsCoding->addNewLine();
   for(int i = 0 ; i < v.size() ; i++)
    {
      v[i]->toString();
    }
  delete isCoding;
  return dicoIsCoding;
}*/

 void TabCodingLZW::insert(string code, Coding* add)
 {
   stringstream iss(code);
   int nombre;
   iss >> nombre;
   bool insert = false;
   while(!insert)
     {
       if(nombre + 1 < v.size())
	 {
	   if(v[nombre + 1]->getName() > add->getName())
	     {
	       cout<<add->getName()<<endl;
	       insert = true;
	       v.insert(v.begin() + nombre + 1,add);
	     }
	 }
       else
	 {
	   insert = true;
	   v.push_back(add);
	 }
       nombre++;
     }
 }



void TabCodingLZW::createDictionary(vector<char> allChar,string word,unsigned int n)
{
  //Ajoute élément dans le dico si n = 0
  if(n==0)
    {
      Coding* newElt=new Coding(word,valCodeInt);
      newElt->toString();
      valCodeInt++;
      v.push_back(newElt);
    }
  ///////////////////////////////////////////
  // Si n != 0, création toute les combinaison possible
  else
    {
      for(int i=0; i<allChar.size(); i++)
	{
	  createDictionary(allChar , word + allChar[i] , n - 1);
	}
    }
  /////////////////////////////////////////////
}




TabCodingLZW::~TabCodingLZW()
{
  for(int i=0;i<v.size();i++)
    {
      delete v[i];
    }
}

void TabCodingLZW::vectorOrdeed()
{
  sort(v.begin(),v.end(),trieSizeCoding);
}
bool trieSizeCoding (Coding* i, Coding* j)
{
  return i->getName() < j->getName();
}
 void TabCodingLZW::createCode()
 {
   for(int i = 0 ; i < v.size() ; i++)
     {
       stringstream oss;
       oss << i;
       v[i]->setCode(oss.str());
     }
 }


//Get et Set 
vector<Coding*> TabCodingLZW::getV()const{return v;}


string TabCodingLZW::toString(){
  cout<<v.size();
  for(int i=0;i<v.size();i++){
    v[i]->toString();
  }
  return "";
}
