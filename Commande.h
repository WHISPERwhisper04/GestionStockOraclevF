#ifndef COMMANDE_H
#define COMMANDE_H

#include <string>
#include <ctime>
#include "OracleConnection.h"

using namespace std;

class Commande {
private:
    int id;
    string dateCommande;
    string statut;
    int idClient;

public:
    Commande();
    Commande(int id, int idClient, const string& dateCommande, const string& statut);
    ~Commande();

    void create(OracleConnection& conn);
    bool read(OracleConnection& conn, int id);
    void update(OracleConnection& conn);
    bool deleteRecord(OracleConnection& conn);

    void afficherToutesCommandes(OracleConnection& conn);
     void afficherCommande() const;

    int getId() const;
    string getDateCommande() const;
    string getStatut() const;
    int getIdClient() const;

    void setId(int id);
    void setDateCommande(const string& dateCommande);
    void setStatut(const string& statut);
    void setIdClient(int idClient);
};

#endif
