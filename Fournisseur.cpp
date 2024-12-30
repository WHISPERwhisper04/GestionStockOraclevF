#include "Fournisseur.h"
#include "OracleConnection.h"
#include <iostream>
#include <vector>
#include <map>
#include <iomanip>

using namespace std;

Fournisseur::Fournisseur() : id(0), nom(""), tel(""), email("") {}

Fournisseur::Fournisseur(int id, string nom, string tel, string email) :
        id(id), nom(nom), tel(tel), email(email) {}

Fournisseur::~Fournisseur() {}

void Fournisseur::create(OracleConnection& conn) {
    string query = "INSERT INTO Fournisseur (ID_Fournisseur, Nom_Fournisseur, Tel_Fournisseur, Email_Fournisseur) VALUES (seq_fournisseur.NEXTVAL, '" + nom + "', '" + tel + "', '" + email + "')";
    conn.executeQuery(query);
     this->id = conn.getGeneratedId("seq_fournisseur");
      cout << "Fournisseur ajoute avec succes. ID: " << this->id << endl;
}

bool Fournisseur::read(OracleConnection& conn, int id) {
    string query = "SELECT * FROM Fournisseur WHERE ID_Fournisseur = " + to_string(id);
    vector<map<string, string>> result = conn.executeQuery(query);
    if (!result.empty()) {
        this->id = id;
        if (result[0].count("NOM_FOURNISSEUR"))
            this->nom = result[0].at("NOM_FOURNISSEUR");
       if (result[0].count("TEL_FOURNISSEUR"))
           this->tel = result[0].at("TEL_FOURNISSEUR");
       if (result[0].count("EMAIL_FOURNISSEUR"))
           this->email = result[0].at("EMAIL_FOURNISSEUR");
        return true;
    }
    return false;
}

void Fournisseur::update(OracleConnection& conn) {
    string query = "UPDATE Fournisseur SET Nom_Fournisseur = '" + nom + "', Tel_Fournisseur = '" + tel + "', Email_Fournisseur = '" + email + "' WHERE ID_Fournisseur = " + to_string(id);
    conn.executeQuery(query);
    
}

bool Fournisseur::deleteRecord(OracleConnection& conn) {
  if (read(conn, id)) {
        string query = "DELETE FROM Fournisseur WHERE ID_Fournisseur = " + to_string(id);
         conn.executeQuery(query);
          cout << "Fournisseur supprime avec succes." << endl;
         return true;
      } else {
         cout << "Erreur: Fournisseur non trouve." << endl;
         return false;
     }
}

void Fournisseur::afficherTousFournisseurs(OracleConnection& conn) {
    string query = "SELECT ID_Fournisseur, Nom_Fournisseur, Tel_Fournisseur, Email_Fournisseur FROM Fournisseur";
    vector<map<string, string>> result = conn.executeQuery(query);
    if (result.empty()) {
       cout << "Aucun fournisseur trouve." << endl;
     }else {
         int maxIdWidth = 8;
        int maxNomWidth = 10;
        int maxTelWidth = 15;
          int maxEmailWidth = 20;
        for (const auto& row : result) {
            if (row.count("ID_FOURNISSEUR")) {
                maxIdWidth = max(maxIdWidth, (int)row.at("ID_FOURNISSEUR").length());
             }
            if (row.count("NOM_FOURNISSEUR")) {
                maxNomWidth = max(maxNomWidth, (int)row.at("NOM_FOURNISSEUR").length());
            }
           if (row.count("TEL_FOURNISSEUR")) {
                maxTelWidth = max(maxTelWidth, (int)row.at("TEL_FOURNISSEUR").length());
            }
           if (row.count("EMAIL_FOURNISSEUR")) {
                maxEmailWidth = max(maxEmailWidth, (int)row.at("EMAIL_FOURNISSEUR").length());
           }
        }
       int totalWidth = maxIdWidth + maxNomWidth + maxTelWidth + maxEmailWidth + 10;

         cout << left << setw(maxIdWidth) << "ID" << " | " << setw(maxNomWidth) << "Nom" << " | " << setw(maxTelWidth) << "Telephone" << " | " << setw(maxEmailWidth) << "Email" << endl;
        cout << setfill('-') << setw(totalWidth) << "" << setfill(' ') << endl;
        for (const auto& row : result) {
             if (row.count("ID_FOURNISSEUR") && row.count("NOM_FOURNISSEUR") && row.count("TEL_FOURNISSEUR") && row.count("EMAIL_FOURNISSEUR")){
                 cout << left << setw(maxIdWidth) << row.at("ID_FOURNISSEUR") << " | " << setw(maxNomWidth) << row.at("NOM_FOURNISSEUR") << " | " << setw(maxTelWidth) << row.at("TEL_FOURNISSEUR") << " | " << setw(maxEmailWidth) << row.at("EMAIL_FOURNISSEUR") << endl;
               }
           else {
                cout << "Erreur: Cle introuvable dans la ligne du fournisseur" << endl;
            }
        }
    }
}
void Fournisseur::afficherFournisseur() const {
    cout << "ID Fournisseur: " << id << ", Nom Fournisseur: " << nom << ", Telephone : " << tel << ", Email : " << email << endl;
};

int Fournisseur::getId() const {
    return id;
}

string Fournisseur::getNom() const {
    return nom;
}

string Fournisseur::getTel() const {
    return tel;
}
string Fournisseur::getEmail() const {
    return email;
}

void Fournisseur::setId(int id) {
    this->id = id;
}

void Fournisseur::setNom(const string& nom) {
    this->nom = nom;
}

void Fournisseur::setTel(const string& tel) {
    this->tel = tel;
}
void Fournisseur::setEmail(const string& email) {
    this->email = email;
}
