#include "Client.h"
#include "OracleConnection.h"
#include <iostream>
#include <vector>
#include <map>
#include <iomanip>

using namespace std;

Client::Client() : id(0), nom(""), prenom(""), adresse(""), email("") {}

Client::Client(int id, const string& nom, const string& prenom, const string& adresse, const string& email) :
        id(id), nom(nom), prenom(prenom), adresse(adresse), email(email) {}

Client::~Client() {}

void Client::create(OracleConnection& conn) {
    string query = "INSERT INTO Client (ID_Client, Nom_Client, Prenom_Client, Adresse_Client, Email_Client) VALUES (seq_client.NEXTVAL, '" + nom + "', '" + prenom + "', '" + adresse + "', '" + email + "')";
    conn.executeQuery(query);
     this->id = conn.getGeneratedId("seq_client");
     cout << "Client ajoute avec succes. ID: " << this->id << endl;
}

bool Client::read(OracleConnection& conn, int id) {
    string query = "SELECT * FROM Client WHERE ID_Client = " + to_string(id);
    vector<map<string, string>> result = conn.executeQuery(query);
    if (!result.empty()) {
        this->id = id;
        if (result[0].count("NOM_CLIENT"))
            this->nom = result[0].at("NOM_CLIENT");
        if (result[0].count("PRENOM_CLIENT"))
            this->prenom = result[0].at("PRENOM_CLIENT");
       if (result[0].count("ADRESSE_CLIENT"))
           this->adresse = result[0].at("ADRESSE_CLIENT");
        if (result[0].count("EMAIL_CLIENT"))
           this->email = result[0].at("EMAIL_CLIENT");
        return true;
    }
    return false;
}

void Client::update(OracleConnection& conn) {
    string query = "UPDATE Client SET Nom_Client = '" + nom + "', Prenom_Client = '" + prenom + "', Adresse_Client = '" + adresse + "', Email_Client = '" + email + "' WHERE ID_Client = " + to_string(id);
    conn.executeQuery(query);
    
}

bool Client::deleteRecord(OracleConnection& conn) {
   if (read(conn, id)) {
        string query = "DELETE FROM Client WHERE ID_Client = " + to_string(id);
         conn.executeQuery(query);
        cout << "Client supprime avec succes." << endl;
         return true;
   } else {
        cout << "Erreur: Client non trouve." << endl;
         return false;
    }
}
void Client::afficherTousClients(OracleConnection& conn) {
    string query = "SELECT * FROM Client";
    vector<map<string, string>> result = conn.executeQuery(query);
     if (result.empty()) {
         cout << "Aucun client trouve." << endl;
     } else{
         int maxIdWidth = 8;
        int maxNomWidth = 10;
       int maxPrenomWidth = 10;
        int maxAdresseWidth = 10;
         int maxEmailWidth = 20;
        for (const auto& row : result) {
            if (row.count("ID_CLIENT")) {
                maxIdWidth = max(maxIdWidth, (int)row.at("ID_CLIENT").length());
            }
           if (row.count("NOM_CLIENT")) {
               maxNomWidth = max(maxNomWidth, (int)row.at("NOM_CLIENT").length());
            }
            if (row.count("PRENOM_CLIENT")) {
                maxPrenomWidth = max(maxPrenomWidth, (int)row.at("PRENOM_CLIENT").length());
             }
            if (row.count("ADRESSE_CLIENT")) {
                maxAdresseWidth = max(maxAdresseWidth, (int)row.at("ADRESSE_CLIENT").length());
           }
          if (row.count("EMAIL_CLIENT")) {
              maxEmailWidth = max(maxEmailWidth, (int)row.at("EMAIL_CLIENT").length());
           }
       }
       int totalWidth = maxIdWidth + maxNomWidth + maxPrenomWidth + maxAdresseWidth+ maxEmailWidth + 14;

        cout << left << setw(maxIdWidth) << "ID" << " | " << setw(maxNomWidth) << "Nom" << " | " << setw(maxPrenomWidth) << "Prenom" << " | " << setw(maxAdresseWidth) << "Adresse" << " | " << setw(maxEmailWidth) << "Email" << endl;
        cout << setfill('-') << setw(totalWidth) << "" << setfill(' ') << endl;
      for (const auto& row : result) {
           if (row.count("ID_CLIENT") && row.count("NOM_CLIENT") && row.count("PRENOM_CLIENT") && row.count("ADRESSE_CLIENT") && row.count("EMAIL_CLIENT"))
             cout << left << setw(maxIdWidth) << row.at("ID_CLIENT") << " | " << setw(maxNomWidth) << row.at("NOM_CLIENT") << " | " << setw(maxPrenomWidth) << row.at("PRENOM_CLIENT") << " | " << setw(maxAdresseWidth) << row.at("ADRESSE_CLIENT") << " | " << setw(maxEmailWidth) << row.at("EMAIL_CLIENT") << endl;
            else{
               cout << "Erreur: Cle introuvable dans la ligne du client" << endl;
            }
      }
    }
}
void Client::afficherClient() const {
     cout << "ID Client: " << id << ", Nom Client: " << nom << ", Prenom Client : " << prenom << ", Adresse : " << adresse << ", Email : " << email << endl;
};

int Client::getId() const {
    return id;
}

string Client::getNom() const {
    return nom;
}
string Client::getPrenom() const {
    return prenom;
}

string Client::getAdresse() const {
    return adresse;
}

string Client::getEmail() const {
    return email;
}

void Client::setId(int id) {
    this->id = id;
}

void Client::setNom(const string& nom) {
    this->nom = nom;
}
void Client::setPrenom(const string& prenom) {
    this->prenom = prenom;
}

void Client::setAdresse(const string& adresse) {
    this->adresse = adresse;
}

void Client::setEmail(const string& email) {
    this->email = email;
}
