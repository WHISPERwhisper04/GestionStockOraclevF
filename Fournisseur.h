#ifndef FOURNISSEUR_H
#define FOURNISSEUR_H

#include <string>
#include "OracleConnection.h"

using namespace std; 

class Fournisseur {
private:
    int id;
    string nom;
    string tel;
    string email;

public:
    Fournisseur();
    Fournisseur(int id, string nom, string tel, string email);
    ~Fournisseur();

    void create(OracleConnection& conn);
    bool read(OracleConnection& conn, int id);
    void update(OracleConnection& conn);
    bool deleteRecord(OracleConnection& conn);

    void afficherTousFournisseurs(OracleConnection& conn);
     void afficherFournisseur() const;

    int getId() const;
    string getNom() const;
    string getTel() const;
    string getEmail() const;

    void setId(int id);
    void setNom(const string& nom);
    void setTel(const string& tel);
    void setEmail(const string& email);
};

#endif
