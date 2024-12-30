#ifndef BONACHAT_H
#define BONACHAT_H

#include <string>
#include <ctime>
#include "OracleConnection.h"

using namespace std;

class BonAchat {
private:
    int idFournisseur;
    int idProduit;
    int qteCommandee;
    string dateCommande; 

public:
    BonAchat();
    BonAchat(int idFournisseur, int idProduit, int qteCommandee, const string& dateCommande);
    ~BonAchat();

    void create(OracleConnection& conn);
    bool read(OracleConnection& conn, int idFournisseur, int idProduit);
    void update(OracleConnection& conn);
    bool deleteRecord(OracleConnection& conn);

    void afficherTousBons(OracleConnection& conn);
    void afficherBon() const;

    int getIdFournisseur() const;
    int getIdProduit() const;
    int getQteCommandee() const;
    string getDateCommande() const;

    void setIdFournisseur(int idFournisseur);
    void setIdProduit(int idProduit);
    void setQteCommandee(int qteCommandee);
    void setDateCommande(const string& dateCommande);
};

#endif
