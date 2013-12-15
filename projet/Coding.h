#ifndef CODING_H
#define CODING_H

class Coding {
 protected:
  string name;
  int quantity;
  string code;
 public:
  //Constructor
  Coding();
  Coding(const char);
  Coding(const char,int);
  Coding(const string);
  Coding(char,const string);
  Coding(const string,const char,int);
  Coding(const string,const string,int);
  Coding(string,unsigned int);
  ~Coding();

  //Get and Set
  string getName()const;
  char getNameRang(const int)const;
  int getNameSize()const;
  int getQuantity()const;
  string getCode()const;
  char getCodeRang(const int)const;
  int getCodeSize()const;

  void setName(const string n);
  void setQuantity(const int q);
  void setCode(const string);
  
  //Methode d'ajout d'occurence
  void upQuantity();
  

  //Affichage 
  string toString()const;
 
};



#endif
