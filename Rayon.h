#ifndef RAYON_H
#define RAYON_H

#include <string>
#include <vector>
#include "OracleConnection.h" 

using namespace std;

class Rayon {
private:
    int id;
    string nom;

public:
    Rayon();
    Rayon(int id, string nom);
    ~Rayon();

    void create(OracleConnection& conn);
    bool read(OracleConnection& conn, int id);
    void update(OracleConnection& conn);
    bool deleteRecord(OracleConnection& conn);
    void afficherTousRayons(OracleConnection& conn); 
      void afficherRayon()const;

    int getId();
    void setId(int id);
    string getNom();
    void setNom(string nom);
};

#endif
