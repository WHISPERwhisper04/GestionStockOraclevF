#ifndef LIGNECOMMANDE_H
#define LIGNECOMMANDE_H

#include <string>
#include "OracleConnection.h"

using namespace std;

class LigneCommande {
private:
    int idProduit;
    int idCommande;
    int qteCommandee;
    double montantAPayer; 

public:
    LigneCommande();
    LigneCommande(int idProduit, int idCommande, int qteCommandee, double montantAPayer);
    ~LigneCommande();

    void create(OracleConnection& conn);
    bool read(OracleConnection& conn, int idProduit, int idCommande);
    void update(OracleConnection& conn);
    bool deleteRecord(OracleConnection& conn);

    void afficherToutesLignesCommandes(OracleConnection& conn);
     void afficherLigneCommande() const;
    double getProductPrice(OracleConnection& conn, int idProduit);

    int getIdProduit() const;
    int getIdCommande() const;
    int getQteCommandee() const;
    double getMontantAPayer() const;

    void setIdProduit(int idProduit);
    void setIdCommande(int idCommande);
    void setQteCommandee(int qteCommandee);
};

#endif
