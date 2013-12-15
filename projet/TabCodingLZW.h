#ifndef TABCODINGLZW_H
#define TABCODINGLZW_H

class TabCodingLZW{
 private:
  vector<Coding*> v;
 public:
  //Constructeur
  TabCodingLZW();
  //Pour les string
  
  //Permet de créer la table de codage d'un fichier 
  //qui est recopier dans un string.
  //Cette table prend char par char
  TabCodingLZW(const string);
  //Permet de créer la table de codage d'un fichier 
  //Cette table travaille n-char par n-char
  TabCodingLZW(const string,unsigned int);
  //Code un fichier en utilisant le principe du travaille
  //n-char par n-char
  string codage(const string , unsigned int);
  //decode un string n-char par n-char
  string decodage(const string);


  //Pour les StringFile
  
  //Permet de créer la table de codage d'un fichier 
  //Cette table prend char par char
  TabCodingLZW(StringFile&);
  //Permet de créer la table de codage d'un fichier 
  //Cette table travaille n-char par n-char
  TabCodingLZW(StringFile&,unsigned int);
  //Code un fichier en utilisant le princide du travaille
  //n-char par n-char
  string codage(StringFile& , unsigned int);
  void insert(string,Coding*);
  StringFile* codage(StringFile&);
  int createV(StringFile&);
  StringFile* decodage(StringFile&,char*);
  //Création du dictionnaire d'origine
  void createDictionary(vector<char> , string , unsigned int);
  ~TabCodingLZW();

  void vectorOrdeed();
  void createCode();
  //Get et Set
  vector<Coding*> getV()const;
  
  //Affichage
  string toString();
};
bool trieSizeCoding(Coding*, Coding*);
#endif
