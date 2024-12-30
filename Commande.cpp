#include "Commande.h"
#include "OracleConnection.h"
#include <iostream>
#include <vector>
#include <map>
#include <iomanip>

using namespace std;

Commande::Commande() : id(0), dateCommande(""), statut(""), idClient(0) {}

Commande::Commande(int id, int idClient, const string& dateCommande, const string& statut) :
        id(id), idClient(idClient), dateCommande(dateCommande), statut(statut) {}

Commande::~Commande() {}

void Commande::create(OracleConnection& conn) {
    string query = "INSERT INTO Commande (ID_Commande, Date_Commande, Statut, ID_Client) VALUES (seq_commande.NEXTVAL, TO_DATE('" + dateCommande + "', 'YYYY-MM-DD'), '" + statut + "', " + to_string(idClient) + ")";
    conn.executeQuery(query);
   this->id = conn.getGeneratedId("seq_commande");
    cout << "Commande ajoutee avec succes. ID: " << this->id << endl;
}

bool Commande::read(OracleConnection& conn, int id) {
    string query = "SELECT * FROM Commande WHERE ID_Commande = " + to_string(id);
    vector<map<string, string>> result = conn.executeQuery(query);
    if (!result.empty()) {
        this->id = id;
        if (result[0].count("DATE_COMMANDE"))
           this->dateCommande = result[0].at("DATE_COMMANDE");
        if (result[0].count("STATUT"))
            this->statut = result[0].at("STATUT");
         if (result[0].count("ID_CLIENT"))
           this->idClient = stoi(result[0].at("ID_CLIENT"));
        return true;
    }
    return false;
}

void Commande::update(OracleConnection& conn) {
    string query = "UPDATE Commande SET Date_Commande = TO_DATE('" + dateCommande + "', 'YYYY-MM-DD'), Statut = '" + statut + "', ID_Client = " + to_string(idClient)
                    + " WHERE ID_Commande = " + to_string(id);
    conn.executeQuery(query);
      
}

bool Commande::deleteRecord(OracleConnection& conn) {
     if(read(conn, id)){
        string query = "DELETE FROM Commande WHERE ID_Commande = " + to_string(id);
        conn.executeQuery(query);
        cout << "Commande supprimee avec succes." << endl;
         return true;
   } else {
         cout << "Erreur: Commande non trouvee." << endl;
         return false;
    }
}
void Commande::afficherToutesCommandes(OracleConnection& conn) {
    string query = "SELECT ID_Commande, Date_Commande, Statut, ID_Client FROM Commande";
    vector<map<string, string>> result = conn.executeQuery(query);
   if (result.empty()) {
       cout << "Aucune commande trouvee." << endl;
    } else {
        int maxIdWidth = 10;
      int maxDateWidth = 12;
       int maxStatutWidth = 10;
         int maxClientWidth = 10;

        for (const auto& row : result) {
           if (row.count("ID_COMMANDE")) {
                maxIdWidth = max(maxIdWidth, (int)row.at("ID_COMMANDE").length());
            }
            if (row.count("DATE_COMMANDE")) {
               maxDateWidth = max(maxDateWidth, (int)row.at("DATE_COMMANDE").length());
            }
            if (row.count("STATUT")) {
                 maxStatutWidth = max(maxStatutWidth, (int)row.at("STATUT").length());
            }
            if (row.count("ID_CLIENT")) {
               maxClientWidth = max(maxClientWidth, (int)row.at("ID_CLIENT").length());
             }
        }
       int totalWidth = maxIdWidth + maxDateWidth + maxStatutWidth + maxClientWidth + 14;

          cout << left << setw(maxIdWidth) << "ID" << " | " << setw(maxDateWidth) << "Date" << " | " << setw(maxStatutWidth) << "Statut" << " | " << setw(maxClientWidth) << "Client" << endl;
        cout << setfill('-') << setw(totalWidth) << "" << setfill(' ') << endl;
      for (const auto& row : result) {
            if(row.count("ID_COMMANDE") && row.count("DATE_COMMANDE") && row.count("STATUT") && row.count("ID_CLIENT")){
                cout << left << setw(maxIdWidth) << row.at("ID_COMMANDE") << " | " << setw(maxDateWidth) << row.at("DATE_COMMANDE") << " | " << setw(maxStatutWidth) << row.at("STATUT") << " | " << setw(maxClientWidth) << row.at("ID_CLIENT") << endl;
             }else {
                  cout << "Erreur: Cle introuvable dans la ligne de la commande" << endl;
                }
        }
    }
}
void Commande::afficherCommande() const {
    cout << "ID Commande: " << id << ", Date commande: " << dateCommande << ", Status: " << statut << ", ID client : " << idClient << endl;
};

int Commande::getId() const {
    return id;
}

string Commande::getDateCommande() const {
    return dateCommande;
}

string Commande::getStatut() const {
    return statut;
}
int Commande::getIdClient() const {
    return idClient;
}

void Commande::setId(int id) {
    this->id = id;
}

void Commande::setDateCommande(const string& dateCommande) {
    this->dateCommande = dateCommande;
}
void Commande::setStatut(const string& statut) {
    this->statut = statut;
}
void Commande::setIdClient(int idClient) {
    this->idClient = idClient;
}
