#ifndef TABCODINGHUFFMAN_H
#define TABCODINGHUFFMAN_H

class TabCodingHuffman{
 private:
  vector<CodingHuffman*> v;
  string finFichier;
 public:
  //Constructor
  TabCodingHuffman();
  TabCodingHuffman(const TabCodingHuffman&);
  ~TabCodingHuffman();
  
  
  //Pour les string
  
  //Permet de créer la table de codage d'un fichier 
  //qui est recopier dans un string.
  //Cette table prend char par char
  TabCodingHuffman(const string);
  //Code un string n-char par n-char
  string codage(const string,int);
  //decode un string n-char par n-char
  string decodage(string,int);
  


  //Pour les StringFile
  
  //Permet de créer la table de codage d'un fichier 
  //Cette table prend char par char
  TabCodingHuffman(StringFile&);
  //Permet de créer la table de codage d'un fichier 
  //Cette table travaille n-char par n-char
  TabCodingHuffman(StringFile&,unsigned int);
  //Code un fichier en utilisant le princide du travaille
  //n-char par n-char
  unsigned int createV(StringFile&);
  string codage(StringFile&,int);
  StringFile* codage(StringFile&, unsigned int);
  StringFile* decodage(StringFile&,unsigned int,char*);
  int addEndFile(StringFile& file,bool*);


  //Get et Set
  vector<CodingHuffman*> getV()const;
  
  //Creation de l'arbre de huffman
  CodingHuffman* createTree();
  CodingHuffman* createTreeRec();


  //Recherche du code de plus longue taille
  unsigned int searchMaxBits();

  int preprocessingCoding(StringFile*, bool*);

  //Trie 
  void sortElt(int);
  void vectorOrdeed();


  //Echange deux elt
  void swap(int,int);

  //Affichage
  string toString();
};
bool trieSizeCoding(CodingHuffman*, CodingHuffman*);
char octetToChar(string);
#endif
