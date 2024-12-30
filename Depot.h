#ifndef DEPOT_H
#define DEPOT_H

#include <string>
#include "OracleConnection.h"

using namespace std;

class Depot {
private:
    int idDepot;
    string nomDepot;
    string adresse;

public:
    Depot();
    Depot(int id, const string& nom, const string& adr);
    ~Depot();

    int getIdDepot() const;
    string getNomDepot() const;
    string getAdresse() const;
    void setIdDepot(int id);
    void setNomDepot(const string& nom);
    void setAdresse(const string& adresse);
     

    void ajouterDepot(OracleConnection& conn);
    void modifierDepot(OracleConnection& conn, const string& nouveauNom, const string& nouvelleAdresse);
    bool supprimerDepot(OracleConnection& conn);
  	void afficherDepot() const;
   	void afficherTousDepots(OracleConnection& conn);
    bool read(OracleConnection& conn, int id);
};

#endif
