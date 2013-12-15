#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <string.h>
#include <stdio.h>
using namespace std;

#include "Coding.h"
#include "CodingHuffman.h"
#include "other/StringFile.h"
#include "TabCodingHuffman.h"


//Constructor
TabCodingHuffman::TabCodingHuffman(){}
TabCodingHuffman::TabCodingHuffman(const TabCodingHuffman& tC)
{
  //Copie le vector
  for(int i=0;i<tC.getV().size();i++)
    {
      v.push_back(tC.getV()[i]);
    }
  //
}
TabCodingHuffman::~TabCodingHuffman()
{
  
}

//Pour les StringFile

//Constructor


TabCodingHuffman::TabCodingHuffman(StringFile& file)
{
  int quantityElt=file.size(); //Nombre d'élément dans le StringFile
  char compare=' '; 
  //Parcours char par char
  for(int i=0;i<quantityElt;i++)
    {
      compare=file[i]; //Recupere le char place i
      bool isPresent=false;
      //Parcours la table de codage
      for(int j=0;j<v.size();j++)
	{
	  //Compare un char table de codage et du fichier
	  if(compare==v[j]->getNameRang(0))
	    {
	      isPresent=true;
	      v[j]->upQuantity();
	      sortElt(j);
	    }
	  //////////////////////////////////////////
	}
      ////////////////////////////////////////////
      //Rajouter un elt non present
      if(!isPresent)
	{
	  CodingHuffman *newElt=new CodingHuffman(compare);
	  v.push_back(newElt);
	}
      /////////////////////////////////////////
    }
  ///////////////////////////////////////////
  //Calcul probabilité de chaque élt
  for(int i=0;i<v.size();i++)
    {
      v[i]->calculP(quantityElt);
    }
  //////////////////////////////////////////
}
TabCodingHuffman::TabCodingHuffman(StringFile& file,unsigned int n)
{
  int quantityElt=file.size() - (file.size() % n); //Taille du fichier à traiter
  string compare="";
  //Parcours le fichier n-char par n-char
  for(unsigned i=0;i<quantityElt;i=i+n)
    {
      compare=file.iToj(i,n); //Recupere n-char au rang i
      bool isPresent=false;
      //Parcours la table de codage
      for(int j=0;j<v.size();j++)
	{
	  if(compare==v[j]->getName())
	    {
	      isPresent=true;
	      v[j]->upQuantity();
	      sortElt(j);
	    }
	}
      //
      //Rajoute un n-char non présent dans la table
      if(!isPresent)
	{
	  CodingHuffman *newElt=new CodingHuffman(compare);
	  v.push_back(newElt);
	}
      //
    }
  //
  //Calcule la probabilité de chaque n-char
  for(int i=0;i<v.size();i++)
    {
      v[i]->calculP(quantityElt);
    }
  //
}

unsigned int TabCodingHuffman::createV(StringFile& aDecoder)
{
  cout<<"/////////CREATEV////////////"<<endl;
  bool bitFinish = false;
  unsigned int quantityBitRead = 0;
  int etat = 0; 
  bool aDechiffrerDebut[8];
  bool aDechiffrerFin[100];
  string bitsLetter = "";
  string decoding = "";
  int afterOctetRead = 0;
  unsigned int sizeCoding = 0;
  unsigned int i = 0;
  while(!bitFinish)
    {
      unsigned int valDecoder=128;
      unsigned int deb = 0;
      char addChar = aDecoder[i];
      //Permet de récuperer l'octet à decoder
      //cout<<"Voicia la letre "<<(int)addChar<<endl;
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
      unsigned int octetNext = 1;
      while(octetNext != 3){
	unsigned int fin = 0;
	valDecoder = 128;
	char addCharNext = aDecoder[i+octetNext];
	while(fin < 8)
	  {
	    if(addCharNext >= valDecoder)
	      {
		aDechiffrerFin[fin + (octetNext - 1) * 8] = true;
		  addCharNext = addCharNext - valDecoder;
		} 
	      else
		{
		  
		  aDechiffrerFin[fin + (octetNext - 1) * 8 ] = false;
		}
	      fin++;
	      valDecoder = valDecoder / 2;
	  }
	octetNext++;
      }
      unsigned int parcoursBool = 0;
      if(etat != 2)
	{
	   bitsLetter = "";
	   decoding = "";
	}
      else
	{
	  decoding = "";
	  }
      bool finishTraitement = false;
       
      if(afterOctetRead > 8)
	{
	  finishTraitement = true;
	  parcoursBool = 8;
	  afterOctetRead = afterOctetRead - 8;
	}
      else
	{
	  parcoursBool = afterOctetRead;
	  afterOctetRead = 0;
	}
      if(etat == 0 && parcoursBool!=8  && aDechiffrerDebut[parcoursBool] == false)
	{
	  finishTraitement = true;
	  parcoursBool = 8;
	  bitFinish = true;
	  }
      while(parcoursBool < 8)
	{
	  switch(etat)
	    {
	    case 0:
	      {
		bitsLetter = "";
		decoding = "";
		if(finishTraitement && aDechiffrerDebut[parcoursBool] == false)
		  {
		    etat = 3;
		    finishTraitement = true;
		  }
		else
		  {
		    if(!finishTraitement && aDechiffrerDebut[parcoursBool] == false)
		      {
			etat = 1;
			finishTraitement = true;
			sizeCoding--;
		      }
		    else
		      {
			finishTraitement = false;
			sizeCoding++;
		      }
		    parcoursBool++;
		    
		  }
		break;
	      }
	    case 1:
	      {
		decoding = "";
		if(aDechiffrerDebut[parcoursBool] == false)
		  {
		    bitsLetter = bitsLetter + '0';
		    finishTraitement = false;
		  }
		else
		  {
		    bitsLetter = bitsLetter + '1';
		    finishTraitement = false;
		  }
		if(bitsLetter.size() == 8)
		  {
		    finishTraitement = true;
		    etat = 2;
		  }
		parcoursBool++;
		break;
	      }
	    case 2:
	      {
		if(sizeCoding == decoding.size())
		  {
		    CodingHuffman* elt = new CodingHuffman(octetToChar(bitsLetter), decoding);
		    v.push_back(elt);
		    finishTraitement = true;
		    etat = 0;
		    
		  }
		else
		  {
		    if(aDechiffrerDebut[parcoursBool] == false)
		      {
			decoding = decoding + '0';
		      }
		    else
		      {
			decoding = decoding + '1';
		      }
		    parcoursBool++;
		  }

		break;
	      }
	    case 3:
	      {
	      
		parcoursBool = 8;
		finishTraitement = true;
		bitFinish = true;
	      }
	    }
	}
      parcoursBool = 0;
      if(!finishTraitement)
	{
	  //afterOctetRead = 1;
	}
      while(!finishTraitement)
	{
	  afterOctetRead++;
	  switch(etat)
	    {
	    case 0:
	      {
		bitsLetter = "";
		decoding = "";
		if(finishTraitement && aDechiffrerFin[parcoursBool] == false)
		  {
		    etat = 3;
		    finishTraitement = true;
		  }
		else{
		if(!finishTraitement && aDechiffrerFin[parcoursBool] == false)
		{
		  
		  etat = 1;
		  finishTraitement = true;
		  sizeCoding--;
		}
	      else
		{
		  finishTraitement = false;
		  sizeCoding++;
		}
		parcoursBool++;
		
		}
		break;
	      }
	    case 1:
	      {
		decoding = "";
		if(aDechiffrerFin[parcoursBool] == false)
		  {
		    bitsLetter = bitsLetter + '0';
		    finishTraitement = false;
		  }
		else
		  {
		    bitsLetter = bitsLetter + '1';
		    finishTraitement = false;
		  }
		if(bitsLetter.size() == 8)
		  {
		    finishTraitement = true;
		    etat = 2;
		  }
		parcoursBool++;
		break;
	      }
	    case 2:
	      {
		if(sizeCoding == decoding.size())
		  {
		    CodingHuffman* elt = new CodingHuffman(octetToChar(bitsLetter), decoding);
		    v.push_back(elt);
		    finishTraitement = true;
		    etat = 0;
		    afterOctetRead--;
		  }
		else
		  {
		    if(aDechiffrerFin[parcoursBool] == false)
		      {
			decoding = decoding + '0';
		      }
		    else
		      {
			decoding = decoding + '1';
		      }
		    parcoursBool++;
		  }
		break;
	      }
	    case 3:
	      {
		parcoursBool = 3;
		finishTraitement = true;
		bitFinish = true;
		break;
	      }
	    }
	}
      i++;
    }
  //for(int i = 0 ; i < v.size() ; i++)
  //{
  //  v[i]->toString();
  //}
  cout<<"////////////////////////////////////////////////:"<<endl;
  return i;
}

StringFile* TabCodingHuffman::codage(StringFile& file,unsigned int nbLeter){
  char* nameCopie = new char[strlen(file.getName()) + 10];
  cout<<"fileGet "<<file.getName()<<endl;
  strcpy(nameCopie,file.getName());
  strcat(nameCopie,".h");
  cout<<"NameCopie "<<nameCopie<<endl;
  StringFile* fileCopie=new StringFile(nameCopie, 0);
  bool isCoding[8];
  unsigned int rangIsCoding = preprocessingCoding(fileCopie,isCoding);

  unsigned int sizeCoding = file.size();// - (file.size() % nbLeter); //Taille du fichier
  
  unsigned int nbCodingI = 0;

  for(int i=0;i<sizeCoding;i=i+nbLeter)
    {
      int cpt=0; //Permet de parcourir la  table de codage
      bool isCodable=false; 
      //Parcours la table de codage
      while(!isCodable && cpt<v.size())
	{
	  isCodable=true;
	  //Verifie l'appartenance dans la table 
	  for(int j=0;j<v[cpt]->getNameSize();j++)
	    {
	      if(file[i+j]!=v[cpt]->getNameRang(j))
		{
		  isCodable=false;
		}
	    }
	  /////////////////////////////////////
	  cpt++;
	}
      ////////////////////////////////////////
      //Ajoute l'élément coder avec les autres
      if(isCodable)
	{
	  //nbCodingI++;
	  Coding* eltCode=v[cpt-1];
	  for(int k = 0 ; k < eltCode->getCode().size() ; k++)
	    {
	      if(eltCode->getCode()[k] == '0')
		{
		  isCoding[rangIsCoding] = false;
		}
	      else
		{
		  isCoding[rangIsCoding] = true;
		}
	      rangIsCoding++;
	      rangIsCoding = rangIsCoding % 8;
	      if(rangIsCoding == 0)
		{
		  fileCopie->addOctet(isCoding);
		  //i = i - nbCodingI;
		  //sizeCoding = sizeCoding - nbCodingI + 1;
		  //nbCodingI=0;
		} 
	    }
	}
      ///////////////////////////////////////
    }
  
  bool finFile1[8];
  bool finFile2[8];
  for(int i = 0 ; i < 8 ; i++)
    {
      finFile1[i] = false;
      finFile2[i] = false;
	
    }
  int pos = 15;
  int copie = rangIsCoding - 1;
  for(copie ; copie >= 0 ; copie--)
    {
      if(pos >= 8)
	{
	  finFile2[pos - 8] = isCoding[copie];
	}
      else
	{
	  finFile1[pos] = isCoding[rangIsCoding];
	}

      pos--;
    }
  if(pos >=8)
    {
      finFile2[pos - 8] = true;
    }
  else
    {
      finFile1[pos] = true;
    }
  fileCopie->addOctet(finFile1);
  fileCopie->addOctet(finFile2);
  delete[] nameCopie;
  fileCopie->addNewLine();
  return fileCopie;
}
//Decoder un fichier encoder

StringFile* TabCodingHuffman::decodage(StringFile& aDecoder,unsigned int nbDecoder,char* newNameFile)
{
  //cout<<newNamefile<<endl;
  StringFile* fileDecoding = new StringFile(newNameFile,0);
  bool aDechiffrerDebut[8];
  unsigned int i = createV(aDecoder);
  
  unsigned int maxCodageBits = this->searchMaxBits();
  bool* aDechiffrerFin = new bool[maxCodageBits + 100];
  unsigned int sizeDecoder = 0;
  unsigned int readNext = 0 ;
  bool reste[20];
  bool isReste = false;
  int sizeReste = addEndFile(aDecoder,reste);
  //this->toString();
  //Va parcourir le fichier à decoder
  //return &aDecoder;
  for(i ; i < aDecoder.size() - 2  ; i = i + 1)
    {
      unsigned int valDecoder=128;
      unsigned int deb = 0;
      char addChar = aDecoder[i];
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

      //La quantité d'octet suivant à lire
      int parcoursCharNext = 1;
      /* int quantityOctetRead = 0;
      if(maxCodageBits % 8 == 0)
	{
	  quantityOctetRead = maxCodageBits / 8;
	} 
      else
	{
	  quantityOctetRead = (maxCodageBits / 8) + 1 ;
	  }*/
      int quantityOctetRead = 5;
      
      //Va parcourir les n octets suivant selon la taille du codage max
      while(quantityOctetRead != 0 && i + parcoursCharNext < aDecoder.size() - 2)
	{
	  unsigned int fin = 0;
	  valDecoder = 128;
	  char addCharNext = aDecoder[i+parcoursCharNext];
	  //Parcours les octets suivants
	  while(fin < 8)
	    {
	      if(addCharNext >= valDecoder)
		{
		  aDechiffrerFin[fin + (parcoursCharNext - 1) * 8] = true;
		  addCharNext = addCharNext - valDecoder;
		} 
	      else
		{
		  
		  aDechiffrerFin[fin + (parcoursCharNext - 1) * 8 ] = false;
		}
	      fin++;
	      valDecoder = valDecoder / 2;
	    }
	  quantityOctetRead--;
	  parcoursCharNext++;
	}

      
      unsigned int parcoursBool = 0; //Permet de parcourir l'octet
      //Si on a deja traiter l'octet suivant
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
      //Permet de decoder un octet
      while(parcoursBool < 8)
	{
	  //cout<<parcoursBool<<endl;
	  //cout<<"what"<<i<<endl;
	  unsigned int cpt = 0; //parcours v
	  bool isDecodable = false;
	  while(!isDecodable && cpt < v.size())
	    {
	      //cout<<i<<" "<<aDecoder.size()<<endl;
	      isDecodable = true;
	      int parcoursBoolCopy = parcoursBool;
	      readNext = 0; 
	      for(unsigned int j = 0 ;j <  v[cpt]->getCode().size();j++)
		{
		  //On cherche si dans l'octet qu'on traite, le code correspond
		  if(parcoursBoolCopy < 8)
		    {
		      if((v[cpt]->getCodeRang(j) == '1'
			  && !aDechiffrerDebut[parcoursBoolCopy])
			 || (v[cpt]->getCodeRang(j) == '0'
			     && aDechiffrerDebut[parcoursBoolCopy]))
			{
			  j = v[cpt]->getCode().size();
			  isDecodable = false;
			}
		      else
			{
			  parcoursBoolCopy++;
			}
		    }
		  //Si le code qu'on traite dépends des octets suivant, on regarde si le code correspond bien
		  else
		    {
		      if(i + ((parcoursBoolCopy - 8) / 8)   != aDecoder.size() - 3)
			{
			  if((v[cpt]->getCodeRang(j) == '1'
			      && !aDechiffrerFin[parcoursBoolCopy - 8])
			     || (v[cpt]->getCodeRang(j) == '0'
				 && aDechiffrerFin[parcoursBoolCopy - 8]))
			    {
			      j = v[cpt]->getCode().size();
			      isDecodable = false;
			    }
			  else
			    {
			      parcoursBoolCopy++;
			      readNext++;
			    }
			}
		      else
			{
			  if(v[cpt]->getCodeSize() - j == 5){
			    for(int w = j ; w < v[cpt]->getCodeSize()  ; w++)
			    {
			      cout<<v[cpt]->getCodeRang(w) ;
			    }
			    cout<<endl;
			    for(int w = 0 ; w < sizeReste ; w++)
			      {
				cout<<reste[w];
			      } 
			    cout<<endl;
			  }
			  int copieJ = j ;
			  int w = 0;
			  cout<<"ypmp"<<endl;
			  while(w < sizeReste)
			    {
			      cout<<"je boucle vers l'infini et AU DELA"<<endl;
			      cout<<sizeReste<<" "<<w<<endl;
			      cout<<v[cpt]->getCodeRang(copieJ)<<endl;
			      cout<<reste[w]<<endl;
			      if((v[cpt]->getCodeRang(copieJ) == '1' 
				  && !reste[w])
				 || (v[cpt]->getCodeRang(copieJ) == '0' 
				     && reste[w]))
				{
				  cout<<"oh"<<endl;
				  w = sizeReste;
				  j = v[cpt]->getCode().size();
				  isDecodable = false;
				}
			      else
				{
				  if(w == sizeReste - 1){j = v[cpt]->getCode().size();}
				  w++;
				  copieJ++;
				  parcoursBoolCopy++;
				  readNext++;
				}
			    }
			}
		    }
		}
	      cpt++;
	    }
	  //Si on a trouver un décodage dasn v correspondan
	  if(isDecodable)
	    {
	      
	      parcoursBool = parcoursBool + v[cpt-1]->getCode().size();	
	      fileDecoding->addString(v[cpt-1]->getName());
	      fileDecoding->addNewLine();
	      if( i == aDecoder.size() - 3)
		{
		
		}
	    }
	}
    }
  delete[] aDechiffrerFin;
  delete fileDecoding;
  return fileDecoding;
}
int TabCodingHuffman::addEndFile(StringFile& file,bool* reste)
{
  unsigned int i = 0;
  bool tabEndFile[16];
  char addChar1 = file[file.size() - 2];
  char addChar2 = file[file.size() - 1];
  cout<<endl;
  cout<<(int)addChar1<<(int)addChar2<<endl;
  int valDecoder = 128;
  for(i ; i < 16 ; i++)
    {
      if(i >= 8)
	{
	  if(i == 8)
	    valDecoder = 128;
	  if(addChar2 >= valDecoder)
	    {
	      tabEndFile[i] = true;
	      addChar2 = addChar2 - valDecoder;
	    }
	  else
	    {
	      tabEndFile[i] = false;
	    }
	  valDecoder = valDecoder / 2;
	}
      else
	{
	  if(addChar1 >= valDecoder)
	    {
	      tabEndFile[i] = true;
	      addChar1 = addChar1 - valDecoder;
	    }
	  else
	    {
	      tabEndFile[i] = false;
	    }
	  valDecoder = valDecoder / 2;
	}
    }
  for(int w = 0 ; w < 16 ; w++)
    {
      cout<<tabEndFile[w];
    }
  cout<<endl;
  bool codingFind = false;
  string coding="";
  for(i = 0 ; i < 16 ; i++)
    {
      if(codingFind)
	{
	  if(tabEndFile[i] == true)
	    {
	      coding = coding + '1';
	    }
	  else
	    {
	      coding = coding + '0';
	    }
	}
      else
	{
	  if(tabEndFile[i] == true)
	    codingFind = true;
	}
    }
  for(int k = 0 ; k < coding.size() ; k++)
    {
      if(coding[k] == '0')
	{
	  reste[k] = false;
	}
      else
	{
	  reste[k] = true;
	}
    }
  cout<<"Voici les derniers code "<<coding<<endl;
  return coding.size();
}
/*StringFile* TabCodingHuffman::decodage(StringFile& aDecoder,unsigned int nbDecoder)
{
  StringFile* fileDecoding = new StringFile("aaa",0);
  bool aDechiffrerDebut[8];
  //createV(aDecoder,aDe);
  unsigned int maxCodageBits = this->searchMaxBits();
  bool* aDechiffrerFin = new bool[maxCodageBits + 8];
  unsigned int sizeDecoder = 0;
  unsigned int readNext = 0 ;
  //Va parcourir le fichier à decoder
  for(unsigned int i = 0 ; i < aDecoder.size() ; i = i + 1)
    {

      unsigned int valDecoder=128;
      unsigned int deb = 0;
      char addChar = aDecoder[i];
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

      //La quantité d'octet suivant à lire
      int parcoursCharNext = 1;
      int quantityOctetRead = 0;
      if(maxCodageBits % 8 == 0)
	{
	  quantityOctetRead = maxCodageBits / 8;
	} 
      else
	{
	  quantityOctetRead = (maxCodageBits / 8) + 1 ;
	}
      
      //Va parcourir les n octets suivant selon la taille du codage max
      while(quantityOctetRead != 0 && i + parcoursCharNext < aDecoder.size())
	{
	  unsigned int fin = 0;
	  valDecoder = 128;
	  char addCharNext = aDecoder[i+parcoursCharNext];
	  //Parcours les octets suivants
	  while(fin < 8)
	    {
	      if(addCharNext >= valDecoder)
		{
		  aDechiffrerFin[fin + (parcoursCharNext - 1) * 8] = true;
		  addCharNext = addCharNext - valDecoder;
		} 
	      else
		{
		  
		  aDechiffrerFin[fin + (parcoursCharNext - 1) * 8 ] = false;
		}
	      fin++;
	      valDecoder = valDecoder / 2;
	    }
	  quantityOctetRead--;
	  parcoursCharNext++;
	}

      
      unsigned int parcoursBool = 0; //Permet de parcourir l'octet
      //Si on a deja traiter l'octet suivant
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
      //Permet de decoder un octet
      while(parcoursBool < 8)
	{
	  unsigned int cpt = 0; //parcours v
	  bool isDecodable = false;
	  while(!isDecodable && cpt < v.size())
	    {
	      isDecodable = true;
	      int parcoursBoolCopy = parcoursBool;
	      readNext = 0; 
	      for(unsigned int j = 0 ;j <  v[cpt]->getCode().size();j++)
		{
		  
		  //On cherche si dans l'octet qu'on traite, le code correspond
		  if(parcoursBoolCopy < 8)
		    {
		      if((v[cpt]->getCodeRang(j) == '1'
			  && !aDechiffrerDebut[parcoursBoolCopy])
			 || (v[cpt]->getCodeRang(j) == '0'
			     && aDechiffrerDebut[parcoursBoolCopy]))
			{
			  j = v[cpt]->getCode().size();
			  isDecodable = false;
			}
		      else
			{
			  parcoursBoolCopy++;
			}
		    }
		  //Si le code qu'on traite dépends des octets suivant, on regarde si le code correspond bien
		  else
		    {
		      if((v[cpt]->getCodeRang(j) == '1'
			  && !aDechiffrerFin[parcoursBoolCopy - 8])
			 || (v[cpt]->getCodeRang(j) == '0'
			     && aDechiffrerFin[parcoursBoolCopy - 8]))
			{
			  j = v[cpt]->getCode().size();
			  isDecodable = false;
			}
		      else
			{
			  parcoursBoolCopy++;
			  readNext++;
			}
		    }
		
		}
	      cpt++;
	    }
	  //Si on a trouver un décodage dasn v correspondan
	  if(isDecodable)
	    {
	      parcoursBool = parcoursBool + v[cpt-1]->getCode().size();	
	      fileDecoding->addString(v[cpt-1]->getName());
	      fileDecoding->addNewLine();
	    }
	}
    }
  delete[] aDechiffrerFin;
  delete fileDecoding;
  return fileDecoding;
  }*/
//StringFile* TabCodingHuffman::decodage(StringFile
//Get et Set 
  vector<CodingHuffman*> TabCodingHuffman::getV()const{return v;}

//Creation de l'arbre de Huffman
CodingHuffman* TabCodingHuffman::createTree(){
  return TabCodingHuffman(*this).createTreeRec();
  
}

CodingHuffman* TabCodingHuffman::createTreeRec(){
  if(v.size()==1){
    return v[0]; //Retourne la racine
  }
  else{
    //crée les noeuds et les feuilles
    CodingHuffman* sumElt=new CodingHuffman(v[v.size()-2],v[v.size()-1]);
    v.pop_back();
    v.pop_back();
    v.push_back(sumElt);
    sortElt(v.size()-1);
    createTreeRec();
  }
}

//Recherche du code de plus longue taille
unsigned int TabCodingHuffman::searchMaxBits()
 {
   unsigned int max = 0;
   for(unsigned int i = 0 ; i < v.size() ; i++)
     {
       if(max < v[i]->getCode().size())
	 {
	   max = v[i]->getCode().size();
	 }
     } 
   return max;
 }


int TabCodingHuffman::preprocessingCoding(StringFile* file, bool* isCoding)
{
  vectorOrdeed();
  
  int sizeDif = 0;
  int rangIsCoding = 0;
  string coder = "";
  for(int i = 0 ; i < v.size() ; i++)
    {
      v[i]->toString();
      int sizeMin = 0;
      int sizeVI = v[i]->getCodeSize();
      if(sizeVI > sizeDif)
	{
	  sizeMin = sizeVI - sizeDif;
	  sizeDif = sizeVI;
	} 
      for(int j = 0 ; j < sizeMin ; j++)
	{
	  
	  isCoding[rangIsCoding] = true;
	  coder = coder + '1';
	  rangIsCoding++;
	  rangIsCoding = rangIsCoding % 8;
	  if(rangIsCoding == 0)
	    {
	      file->addOctet(isCoding);
	    }
	}
      coder = coder + '1';
      isCoding[rangIsCoding] = true;
      rangIsCoding++;
      rangIsCoding = rangIsCoding % 8;
      if(rangIsCoding == 0)
	{
	  file->addOctet(isCoding);
	}
      coder = coder + '0';
      isCoding[rangIsCoding] = false;
      rangIsCoding++;
      rangIsCoding = rangIsCoding % 8;
      if(rangIsCoding == 0)
	{
	  file->addOctet(isCoding);
	}
      unsigned int valCoding = 128;
      char charAddFile = v[i]->getNameRang(0);
      for(int j = 0 ; j < 8 ;j++)
	{
	  if(charAddFile >= valCoding)
	    {
	      coder = coder + '1';
	      isCoding[rangIsCoding] = true;
	      charAddFile = charAddFile - valCoding;
	    }
	  else
	    {
	      coder = coder + '0';
	      isCoding[rangIsCoding] = false;
	    }
	  valCoding = valCoding / 2;
	  rangIsCoding++;
	  rangIsCoding = rangIsCoding % 8;
	  if(rangIsCoding == 0)
	    {
	      file->addOctet(isCoding);
	    }
	}
      for(int j = 0 ; j < v[i]->getCode().size() ; j++)
	{
	  if(v[i]->getCodeRang(j) == '0')
	    {
	      coder = coder + '0';
	      isCoding[rangIsCoding] = false;
	    }
	  else
	    {
	      coder = coder + '1';
	      isCoding[rangIsCoding] = true;
	    }
	  rangIsCoding++;
	  rangIsCoding = rangIsCoding % 8;
	  if(rangIsCoding == 0)
	    {
	      file->addOctet(isCoding);
	    }
	}
      
    }
  //Oblige de mettre 0(défini dans le protocole)
  coder = coder + 'O';
  isCoding[rangIsCoding] = false;
  rangIsCoding++;
  rangIsCoding = rangIsCoding % 8;
  if(rangIsCoding == 0)
    {
      file->addOctet(isCoding);
    }
  while(rangIsCoding != 0)
    {
      coder = coder + 'O';
      isCoding[rangIsCoding] = false;
      rangIsCoding++;
      rangIsCoding = rangIsCoding % 8;
      if(rangIsCoding == 0)
	{
	  file->addOctet(isCoding);
	}
    }
  return 0;
}

//trie
void TabCodingHuffman::sortElt(int rang){
  if(rang==0)
    return;
  else{
    if(v[rang]->getQuantity()>v[rang-1]->getQuantity()){
      swap(rang,rang-1);
      sortElt(rang-1);
    }
    else
      return;
  }
}

void TabCodingHuffman::vectorOrdeed()
{
  sort(v.begin(),v.end(),trieSizeCoding);
}
bool trieSizeCoding (CodingHuffman* i, CodingHuffman* j)
{
  return i->getCodeSize() < j->getCodeSize();
}
char octetToChar(string bits)
{
  char result = 0;
  unsigned int valCoding = 128;
  for(int i = 0; i < 8 ; i++)
    {
      if(bits[i] != '0')
	{
	  result = result + valCoding;
	}
      valCoding= valCoding / 2;
    }
  return result;
}
//Echange
void TabCodingHuffman::swap(int i1,int i2){
  CodingHuffman* p=v[i1];
  v[i1]=v[i2];
  v[i2]=p;
}

//Affichage
string TabCodingHuffman::toString(){
  for(int i=0;i<v.size();i++){
    v[i]->toString();
  }
  return "";
}











////////////////////////////////////////////////////////////
/////////////////////////Devenu Inutile////////////////////
////////////////////////////////////////////////////////////
string TabCodingHuffman::codage(const string aCoder,int nbLeter){
  string estCoder="";
  //Parcours l'élement à coder
  for(int i=0;i<aCoder.size();i=i+nbLeter)
    {
      int cpt=0; //Parcours la table de codage
      bool isCodable=false;
      //Cherche un élément correspondant dans la table
      while(!isCodable && cpt<v.size())
	{
	  isCodable=true;
	  //Regarde si le n-char string = n-char table
	  for(int j=0;j<v[cpt]->getNameSize();j++)
	    {
	    if(aCoder[i+j]!=v[cpt]->getNameRang(j))
	      {
		isCodable=false;
	      }
	    }
	  //
	cpt++;
      }
      //
      //Code l'élement et le rajoute
      if(isCodable)
	{
	  estCoder=estCoder+v[cpt-1]->getCode();
	}
    }
  //
  return estCoder;
}

string TabCodingHuffman::decodage(const string aDecoder,int nbMacCode){
  string isDecoder="";
  int sizeDecoder=0; //Permet de parcourir le fichier à decoder
  //Parcours le string à decoder
  for(int i=0;i<aDecoder.size();i=i+sizeDecoder)
    {
      int cpt=0; 
      bool isDecodable=false;
      //Parcours la table de codage
      while(!isDecodable && cpt<v.size())
	{
	  isDecodable=true;
	  int copieI=i;
	  //Verifie si l'élement à decoder corresponds
	  for(int j=0;j<v[cpt]->getCodeSize();j++){
	    if(aDecoder[copieI]!=v[cpt]->getCodeRang(j)){
	      isDecodable=false;
	    }
	    copieI++;
	  }
	  //
	  cpt++;
    
	}
      //
      //Ajouter l'élement decoder
      if(isDecodable)
	{
	  sizeDecoder=v[cpt-1]->getCodeSize();
	  isDecoder+=v[cpt-1]->getName();
	}
    }
  //
  return isDecoder;
}

string TabCodingHuffman::codage(StringFile& aCoder,int nbLeter){
  unsigned int sizeCoding = aCoder.size()-(aCoder.size() % nbLeter); //La taille du fichier - La taille du fichier % n-char
  string estCoder="";
  //Parcours le fichier n-char par n-char 
  for(int i=0;i<sizeCoding;i=i+nbLeter)
    {
      int cpt=0; //Permet de parcourir la  table de codage
      bool isCodable=false;
      //Parcours la table de codage
      while(!isCodable && cpt<v.size())
	{
	  isCodable=true;
	  //Verifie l'appartenance dans la table 
	  for(int j=0;j<v[cpt]->getNameSize();j++)
	    {
	      if(aCoder[i+j]!=v[cpt]->getNameRang(j))
		{
		  isCodable=false;
		}
	    }
	  /////////////////////////////////////
	  cpt++;
	}
      ////////////////////////////////////////
      //Ajoute l'élément coder avec les autres
      if(isCodable)
	{
	  estCoder=estCoder+v[cpt-1]->getCode();
	}
      ///////////////////////////////////////
    }
  ///////////////////////////////////////////
  return estCoder;
}
//Pour les string

//Constructor

TabCodingHuffman::TabCodingHuffman(const string file)
{
  int quantityElt=file.size(); //nombre de char du fichier
  //Parcours le fichier char par char 
  for(int i=0;i<quantityElt;i++)
    {
    
    bool isPresent=false;
    //Parcours la table de codage
    for(int j=0;j<v.size();j++)
      {
	//Compare un char fichier et un char table codage
	if(file[i]==v[j]->getName()[0])
	  {
	    isPresent=true;
	    v[j]->upQuantity();
	    sortElt(j);
	  }
	///////////////////////////////////////////////
      }
    //////////////////////////////////////////////////
    //Rajoute un élt dans la table de codage
    if(!isPresent)
      {
	CodingHuffman *newElt=new CodingHuffman(file[i]);
	v.push_back(newElt);
      }
    ///////////////////////////////////////////////
  }
  /////////////////////////////////////////////////
  //Calcule la proba de chaque char
  for(int i=0;i<v.size();i++)
    v[i]->calculP(quantityElt);
  ///////////////////////////////////////////////
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
