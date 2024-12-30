#include "Rayon.h"
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <iomanip> // Pour manipuler l'affichage

using namespace std;

Rayon::Rayon() : id(0), nom("") {}
Rayon::Rayon(int id, string nom) : id(id), nom(nom) {}
Rayon::~Rayon() {}

void Rayon::create(OracleConnection& conn) {
    string query = "INSERT INTO Rayon (ID_Rayon, Nom_Rayon) VALUES (seq_rayon.NEXTVAL, '" + nom + "')";
    conn.executeQuery(query);
    this->id = conn.getGeneratedId("seq_rayon");
}

bool Rayon::read(OracleConnection& conn, int id) {
    string query = "SELECT * FROM Rayon WHERE ID_Rayon = " + to_string(id);
    vector<map<string, string>> result = conn.executeQuery(query);

    if (!result.empty()) {
        this->id = id;
         if (result[0].count("NOM_RAYON")){
            this->nom = result[0].at("NOM_RAYON");
         }
        return true;
    }
    return false;
}

void Rayon::update(OracleConnection& conn) {
    string query = "UPDATE Rayon SET Nom_Rayon = '" + nom + "' WHERE ID_Rayon = " + to_string(id);
    conn.executeQuery(query);
}
bool Rayon::deleteRecord(OracleConnection& conn) {
    if (read(conn, id)) {
         string query = "DELETE FROM Rayon WHERE ID_Rayon = " + to_string(id);
       vector<map<string, string>> result = conn.executeQuery(query);
        cout << "Rayon supprime avec succes." << endl;
        return true;
    }
     cout << "Erreur: Rayon non trouve." << endl;
     return false;
}
void Rayon::afficherTousRayons(OracleConnection& conn) {
    string query = "SELECT * FROM Rayon";
    vector<map<string, string>> result = conn.executeQuery(query);

    if (result.empty()) {
        cout << "Aucun rayon trouve." << endl;
    } else {
        int maxIdWidth = 8;
        int maxNomWidth = 10; 
        for (const auto& row : result) {
            if (row.count("ID_RAYON")) {
                maxIdWidth = max(maxIdWidth, (int)row.at("ID_RAYON").length());
            }
            if (row.count("NOM_RAYON")) {
                maxNomWidth = max(maxNomWidth, (int)row.at("NOM_RAYON").length());
            }
        }

        // Affichage de l'en-tête
        cout << left << setw(maxIdWidth) << "ID Rayon" << " | " << setw(maxNomWidth) << "Nom Rayon" << endl;
        cout << setfill('-') << setw(maxIdWidth + maxNomWidth + 3) << "" << setfill(' ') << endl;

        // Affichage des données
        for (const auto& row : result) {
            if (row.count("ID_RAYON") && row.count("NOM_RAYON")) {
                cout << left << setw(maxIdWidth) << row.at("ID_RAYON") << " | " << setw(maxNomWidth) << row.at("NOM_RAYON") << endl;
            } else {
                cout << "Erreur: Clé introuvable dans la ligne du rayon" << endl;
            }
        }
    }
}
  void Rayon::afficherRayon() const{
    cout << "ID Rayon: " << id << ", Nom Rayon: " << nom << endl;
}

int Rayon::getId() {
    return id;
}

void Rayon::setId(int id) {
    this->id = id;
}

string Rayon::getNom() {
    return nom;
}

void Rayon::setNom(string nom) {
    this->nom = nom;
}
