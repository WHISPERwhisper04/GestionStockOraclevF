#include "Inventaire.h"
#include "OracleConnection.h"
#include <iostream>
#include <vector>
#include <map>
#include <iomanip>

using namespace std;

Inventaire::Inventaire() : idRayon(0), idDepot(0), qteStockee(0), dateMaj("") {}

Inventaire::Inventaire(int idRayon, int idDepot, int qteStockee, const string& dateMaj) :
        idRayon(idRayon), idDepot(idDepot), qteStockee(qteStockee), dateMaj(dateMaj) {}

Inventaire::~Inventaire() {}


void Inventaire::create(OracleConnection& conn) {
    string query = "INSERT INTO Inventaire (ID_Rayon, ID_Depot, Qte_stockee, Date_maj) VALUES ("
                   + to_string(idRayon) + ", " + to_string(idDepot) + ", " + to_string(qteStockee) + ", SYSDATE)";
    conn.executeQuery(query);
      cout << "Inventaire ajoute avec succes pour le rayon " << idRayon << " et le depot " << idDepot << endl;
}

bool Inventaire::read(OracleConnection& conn, int idRayon, int idDepot) {
    string query = "SELECT ID_Rayon, ID_Depot, Qte_stockee, TO_CHAR(Date_maj, 'YYYY-MM-DD HH24:MI:SS') AS Date_maj FROM Inventaire WHERE ID_Rayon = " + to_string(idRayon) + " AND ID_Depot = " + to_string(idDepot);
    vector<map<string, string>> result = conn.executeQuery(query);
    if (!result.empty()) {
         this->idRayon = idRayon;
        this->idDepot = idDepot;
        if (result[0].count("QTE_STOCKEE"))
            this->qteStockee = stoi(result[0].at("QTE_STOCKEE"));
       if (result[0].count("DATE_MAJ"))
            this->dateMaj = result[0].at("DATE_MAJ");
          return true;
     }
    return false;
}

void Inventaire::update(OracleConnection& conn) {
    string query = "UPDATE Inventaire SET Qte_stockee = " + to_string(qteStockee) + ", Date_maj = SYSDATE "
                   "WHERE ID_Rayon = " + to_string(idRayon) + " AND ID_Depot = " + to_string(idDepot);
    conn.executeQuery(query);
      cout << "Inventaire mis a jour avec succes pour le rayon " << idRayon << " et le depot " << idDepot << endl;
}

bool Inventaire::deleteRecord(OracleConnection& conn) {
   if (read(conn, idRayon,idDepot)) {
        string query = "DELETE FROM Inventaire WHERE ID_Rayon = " + to_string(idRayon) + " AND ID_Depot = " + to_string(idDepot);
        conn.executeQuery(query);
         cout << "Inventaire supprime avec succes pour le rayon " << idRayon << " et le depot " << idDepot << endl;
        return true;
    } else {
         cout << "Erreur: Inventaire non trouve." << endl;
          return false;
    }
}
void Inventaire::updateInventaire(OracleConnection& conn, int idRayon, int idDepot, int newStock) {
    string query = "UPDATE Inventaire SET Qte_stockee = " + std::to_string(newStock) + ", Date_maj = SYSDATE "
                   "WHERE ID_Rayon = " + std::to_string(idRayon) + " AND ID_Depot = " + std::to_string(idDepot);
    conn.executeQuery(query);
     cout << "Inventaire mis a jour avec succes pour le rayon " << idRayon << " et le depot " << idDepot << endl;
}
void Inventaire::viewInventaireStatus(OracleConnection& conn) {
    string query = "SELECT R.Nom_Rayon, D.Nom_Depot, I.Qte_stockee, TO_CHAR(I.Date_maj, 'YYYY-MM-DD HH24:MI:SS') AS Date_maj "
                   "FROM Inventaire I JOIN Rayon R ON I.ID_Rayon = R.ID_Rayon "
                   "JOIN Depot D ON I.ID_Depot = D.ID_Depot";
    vector<map<string, string>> result = conn.executeQuery(query);
    if(result.empty()){
        cout << "Aucune donnee dans l'inventaire." << endl;
    } else{
        cout << "\nInventaire Status:\n";
        cout << left << setw(15) << "Rayon" << " | " << setw(15) << "Depot" << " | " << setw(10) << "Quantite" << " | " << "Derniere MAJ" << endl;
    cout << setfill('-') << setw(15+3+15+3+10+3+22) << "" << setfill(' ') << endl;

        for (const auto& row : result) {
            cout << left << setw(15) << row.at("NOM_RAYON")
                 << " | " << setw(15) << row.at("NOM_DEPOT")
                  << " | " << setw(10) << row.at("QTE_STOCKEE")
                   << " | " << row.at("DATE_MAJ") << endl;
            }
    }
}

void Inventaire::viewInventaireStatusByRayon(OracleConnection& conn,int idRayon) {
    string query = "SELECT R.Nom_Rayon, D.Nom_Depot, I.Qte_stockee, TO_CHAR(I.Date_maj, 'YYYY-MM-DD HH24:MI:SS') AS Date_maj "
                   "FROM Inventaire I JOIN Rayon R ON I.ID_Rayon = R.ID_Rayon "
                   "JOIN Depot D ON I.ID_Depot = D.ID_Depot WHERE I.ID_Rayon = " + to_string(idRayon);
    vector<map<string, string>> result = conn.executeQuery(query);
      if (result.empty()) {
        cout << "Aucune donnee dans l'inventaire pour ce rayon." << endl;
      } else{
          cout << "\nInventaire Status par rayon :\n";
           cout << left << setw(15) << "Rayon" << " | " << setw(15) << "Depot" << " | " << setw(10) << "Quantite" << " | " << "Derniere MAJ" << endl;
    cout << setfill('-') << setw(15+3+15+3+10+3+22) << "" << setfill(' ') << endl;

            for (const auto& row : result) {
                 cout << left << setw(15) << row.at("NOM_RAYON")
                 << " | " << setw(15) << row.at("NOM_DEPOT")
                  << " | " << setw(10) << row.at("QTE_STOCKEE")
                   << " | " << row.at("DATE_MAJ") << endl;
            }
      }
}
void Inventaire::viewInventaireStatusByDepot(OracleConnection& conn,int idDepot) {
    string query = "SELECT R.Nom_Rayon, D.Nom_Depot, I.Qte_stockee, TO_CHAR(I.Date_maj, 'YYYY-MM-DD HH24:MI:SS') AS Date_maj "
                   "FROM Inventaire I JOIN Rayon R ON I.ID_Rayon = R.ID_Rayon "
                   "JOIN Depot D ON I.ID_Depot = D.ID_Depot WHERE I.ID_Depot = " + to_string(idDepot);
    vector<map<string, string>> result = conn.executeQuery(query);
    if (result.empty()) {
       cout << "Aucune donnee dans l'inventaire pour ce depot." << endl;
     } else{
          cout << "\nInventaire Status par depot :\n";
         cout << left << setw(15) << "Rayon" << " | " << setw(15) << "Depot" << " | " << setw(10) << "Quantite" << " | " << "Derniere MAJ" << endl;
       cout << setfill('-') << setw(15+3+15+3+10+3+22) << "" << setfill(' ') << endl;
             for (const auto& row : result) {
                  cout << left << setw(15) << row.at("NOM_RAYON")
                 << " | " << setw(15) << row.at("NOM_DEPOT")
                  << " | " << setw(10) << row.at("QTE_STOCKEE")
                   << " | " << row.at("DATE_MAJ") << endl;
              }
    }

}
int Inventaire::getIdRayon() const {
    return idRayon;
}

int Inventaire::getIdDepot() const {
    return idDepot;
}
int Inventaire::getQteStockee() const {
    return qteStockee;
}
string Inventaire::getDateMaj() const{
    return dateMaj;
}

void Inventaire::setIdRayon(int idRayon) {
    this->idRayon = idRayon;
}
void Inventaire::setIdDepot(int idDepot) {
    this->idDepot = idDepot;
}
void Inventaire::setQteStockee(int qteStockee) {
    this->qteStockee = qteStockee;
}
void Inventaire::setDateMaj(const string& dateMaj) {
    this->dateMaj = dateMaj;
}
