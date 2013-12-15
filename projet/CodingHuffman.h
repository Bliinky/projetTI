#ifndef CODINGHUFFMAN_H
#define CODINGHUFFMAN_H

class CodingHuffman : public Coding{
 protected: 
  float p;
  CodingHuffman* left;
  CodingHuffman* right;
 public:
  //Constructeur 
  CodingHuffman();
  CodingHuffman(const char);
  CodingHuffman(const string);
  CodingHuffman(char,string);
  CodingHuffman(CodingHuffman*, CodingHuffman*);
  ~CodingHuffman();

  //Get and Set
  float getP()const;
  CodingHuffman* getLeft()const;
  CodingHuffman* getRight()const;

  void setP(const float prob);

  //Methode d'ajout d'occurence
  void calculP(const int);

  //Creation codage 
  CodingHuffman* createCode(string);

  //Affichage
  void toStringTree()const;
};

#endif
