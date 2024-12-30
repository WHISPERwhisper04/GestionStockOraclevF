#include "Depot.h"
#include <iostream>
#include <vector>
#include <map>
#include <iomanip>

using namespace std;

// Constructeur
Depot::Depot() : idDepot(0), nomDepot(""), adresse("") {}
Depot::Depot(int id, const string& nom, const string& adr)
    : idDepot(id), nomDepot(nom), adresse(adr) {}
Depot::~Depot() {}
// Getters
int Depot::getIdDepot() const {
    return idDepot;
}
string Depot::getNomDepot() const {
    return nomDepot;
}
string Depot::getAdresse() const {
    return adresse;
}
void Depot::setIdDepot(int id) {
    idDepot = id;
}
void Depot::setNomDepot(const string& nom) {
    nomDepot = nom;
}
void Depot::setAdresse(const string& adresse) {
   this->adresse = adresse;
}

void Depot::ajouterDepot(OracleConnection& conn) {
    string query = "INSERT INTO Depot (ID_Depot, Nom_Depot, Adresse) VALUES (seq_depot.NEXTVAL, '" + nomDepot + "', '" + adresse + "')";
    conn.executeQuery(query);
    this->idDepot = conn.getGeneratedId("seq_depot");
}
 bool Depot::read(OracleConnection& conn, int id) {
    string query = "SELECT * FROM Depot WHERE ID_Depot = " + to_string(id);
    vector<map<string, string>> result = conn.executeQuery(query);
    if (!result.empty()) {
        this->idDepot = id;
        if (result[0].count("NOM_DEPOT")){
          this->nomDepot = result[0].at("NOM_DEPOT");
        }
         if (result[0].count("ADRESSE")){
            this->adresse = result[0].at("ADRESSE");
       }
      return true;
    }
    return false;
}

void Depot::modifierDepot(OracleConnection& conn, const string& nouveauNom, const string& nouvelleAdresse) {
    string query = "UPDATE Depot SET Nom_Depot = '" + nouveauNom + "', Adresse = '" + nouvelleAdresse + "' WHERE ID_Depot = " + to_string(idDepot);
    conn.executeQuery(query);
    nomDepot = nouveauNom;
    adresse = nouvelleAdresse;
}

bool Depot::supprimerDepot(OracleConnection& conn) {
    if (read(conn, idDepot)) {
         string query = "DELETE FROM Depot WHERE ID_Depot = " + to_string(idDepot);
       vector<map<string, string>> result = conn.executeQuery(query);
        cout << "Depot supprime avec succes." << endl;
        return true;
    }
     cout << "Erreur: Depot non trouve." << endl;
     return false;
}
void Depot::afficherTousDepots(OracleConnection& conn) {
    string query = "SELECT * FROM Depot";
    vector<map<string, string>> result = conn.executeQuery(query);

    if (result.empty()) {
        cout << "Aucun depot trouve." << endl;
    } else {
        int maxIdWidth = 8;
        int maxNomWidth = 10;
        int maxAddressWidth = 10;
        for (const auto& row : result) {
            if (row.count("ID_DEPOT")) {
                maxIdWidth = max(maxIdWidth, (int)row.at("ID_DEPOT").length());
            }
            if (row.count("NOM_DEPOT")) {
                maxNomWidth = max(maxNomWidth, (int)row.at("NOM_DEPOT").length());
             }
            if (row.count("ADRESSE")) {
                maxAddressWidth = max(maxAddressWidth, (int)row.at("ADRESSE").length());
            }
        }
       int totalWidth = maxIdWidth + maxNomWidth + maxAddressWidth + 6;

        // Affichage de l'en-tête
         cout << left << setw(maxIdWidth) << "ID Depot" << " | " << setw(maxNomWidth) << "Nom Depot" << " | " <<  setw(maxAddressWidth) << "Adresse" << endl;
        cout << setfill('-') << setw(totalWidth) << "" << setfill(' ') << endl;

       // Affichage des données
        for (const auto& row : result) {
            if (row.count("ID_DEPOT") && row.count("NOM_DEPOT") && row.count("ADRESSE")){
                 cout << left << setw(maxIdWidth) << row.at("ID_DEPOT") << " | " << setw(maxNomWidth) << row.at("NOM_DEPOT") << " | " << setw(maxAddressWidth) << row.at("ADRESSE") << endl;
              } else {
                   cout << "Erreur: Cle introuvable dans la ligne du depot" << endl;
              }
        }
    }
}
void Depot::afficherDepot() const {
     cout << "ID Depot: " << idDepot << ", Nom Depot: " << nomDepot << ", Adresse: " << adresse << endl;
}
