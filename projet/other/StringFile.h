#ifndef STRINGFILE_H
#define STRINGFILE_H

class StringFile{
 private:
  char * name;
  fstream* file;
  unsigned int sizeClass;
  unsigned int rang;
 public:
  //Constructor
  //Construis un file par rapport à un nom de file 
  StringFile(const char*);
  StringFile(const char*, unsigned int);
  ~StringFile();

  //Get and Set
  char* getName()const;
  fstream* getFile()const;

  
  //Va du char à la place i au char à la place j
  string iToj(unsigned int, unsigned int);

  //Retourne la taille du fichier 
  int size()const;
  
  void afficherFichier();

  //Retourne un char
  char operator[](const unsigned int);

  void addOctet(bool*);
  void addString(string);
  void addNewLine();
  void cp(StringFile*);
};

#endif
