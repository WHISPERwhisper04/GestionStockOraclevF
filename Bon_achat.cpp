#include "Bon_achat.h"
#include "OracleConnection.h"
#include <iostream>
#include <vector>
#include <map>
#include <iomanip>
#include <ctime>

using namespace std;


BonAchat::BonAchat() : idFournisseur(0), idProduit(0), qteCommandee(0), dateCommande("") {}

BonAchat::BonAchat(int idFournisseur, int idProduit, int qteCommandee, const string& dateCommande) :
        idFournisseur(idFournisseur), idProduit(idProduit), qteCommandee(qteCommandee), dateCommande(dateCommande) {}

BonAchat::~BonAchat() {}

void BonAchat::create(OracleConnection& conn) {
   string query = "INSERT INTO Bon_achat (ID_Fournisseur, ID_Produit, Qte_Commandee, Date_Commande) VALUES ("
                 + to_string(idFournisseur) + ", " + to_string(idProduit) + ", " + to_string(qteCommandee) + ", TO_DATE('" + dateCommande + "', 'YYYY-MM-DD'))";
    conn.executeQuery(query);
    cout << "Bon d'achat ajoute avec succes pour le fournisseur " << idFournisseur << " et le produit " << idProduit << endl;
}
bool BonAchat::read(OracleConnection& conn, int idFournisseur, int idProduit) {
    string query = "SELECT ID_Fournisseur, ID_Produit, Qte_Commandee, Date_Commande FROM Bon_achat WHERE ID_Fournisseur = " + to_string(idFournisseur) + " AND ID_Produit = " + to_string(idProduit);
    vector<map<string, string>> result = conn.executeQuery(query);

    if (!result.empty()) {
        this->idFournisseur = idFournisseur;
        this->idProduit = idProduit;
        if (result[0].count("QTE_COMMANDEE"))
            this->qteCommandee = stoi(result[0].at("QTE_COMMANDEE"));
         if (result[0].count("DATE_COMMANDE"))
              this->dateCommande = result[0].at("DATE_COMMANDE");
        return true;
    }
    return false;
}

void BonAchat::update(OracleConnection& conn) {
  string query = "UPDATE Bon_achat SET Qte_Commandee = " + to_string(qteCommandee) + ", Date_Commande = TO_DATE('" + dateCommande + "', 'YYYY-MM-DD') WHERE ID_Fournisseur = " + to_string(idFournisseur) + " AND ID_Produit = " + to_string(idProduit);
   conn.executeQuery(query);
   
}

bool BonAchat::deleteRecord(OracleConnection& conn) {
    if(read(conn, idFournisseur, idProduit)){
        string query = "DELETE FROM Bon_achat WHERE ID_Fournisseur = " + to_string(idFournisseur) + " AND ID_Produit = " + to_string(idProduit);
         conn.executeQuery(query);
        cout << "Bon d'achat supprime avec succes pour le fournisseur " << idFournisseur << " et le produit " << idProduit << endl;
       return true;
    } else {
           cout << "Erreur: Bon d'achat non trouve." << endl;
          return false;
      }
}



void BonAchat::afficherTousBons(OracleConnection& conn) {
    string query = "SELECT ID_Fournisseur, ID_Produit, Qte_Commandee, TO_CHAR(Date_Commande, 'YYYY-MM-DD') AS Date_Commande FROM Bon_achat";
    vector<map<string, string>> result = conn.executeQuery(query);
     if (result.empty()) {
         cout << "Aucun bon d'achat trouve." << endl;
     }else{
          int maxFournisseurWidth = 12;
          int maxProduitWidth = 12;
         int maxQuantiteWidth = 12;
           int maxDateWidth = 12;
        for (const auto& row : result) {
            if (row.count("ID_FOURNISSEUR")) {
                maxFournisseurWidth = max(maxFournisseurWidth, (int)row.at("ID_FOURNISSEUR").length());
            }
           if (row.count("ID_PRODUIT")) {
                maxProduitWidth = max(maxProduitWidth, (int)row.at("ID_PRODUIT").length());
             }
           if (row.count("QTE_COMMANDEE")) {
                 maxQuantiteWidth = max(maxQuantiteWidth, (int)row.at("QTE_COMMANDEE").length());
             }
             if (row.count("DATE_COMMANDE")) {
                maxDateWidth = max(maxDateWidth, (int)row.at("DATE_COMMANDE").length());
            }
        }
       int totalWidth = maxFournisseurWidth + maxProduitWidth + maxQuantiteWidth + maxDateWidth + 10;

       cout << left << setw(maxFournisseurWidth) << "Fournisseur" << " | " << setw(maxProduitWidth) << "Produit" << " | " << setw(maxQuantiteWidth) << "Quantite" << " | " << setw(maxDateWidth) << "Date" << endl;
         cout << setfill('-') << setw(totalWidth) << "" << setfill(' ') << endl;
        for (const auto& row : result) {
            if (row.count("ID_FOURNISSEUR") && row.count("ID_PRODUIT") && row.count("QTE_COMMANDEE") && row.count("DATE_COMMANDE"))
                 cout << left << setw(maxFournisseurWidth) << row.at("ID_FOURNISSEUR") << " | " << setw(maxProduitWidth) << row.at("ID_PRODUIT") << " | " << setw(maxQuantiteWidth) << row.at("QTE_COMMANDEE") << " | " << setw(maxDateWidth) << row.at("DATE_COMMANDE") << endl;
              else {
                   cout << "Erreur: Cle introuvable dans la ligne du bon d'achat" << endl;
                 }
         }
    }
}
void BonAchat::afficherBon() const {
    cout << "ID Fournisseur: " << idFournisseur << ", ID Produit: " << idProduit << ", Quantite commandee: " << qteCommandee << ", Date commande : " << dateCommande << endl;
};
int BonAchat::getIdFournisseur() const {
    return idFournisseur;
}

int BonAchat::getIdProduit() const {
    return idProduit;
}

int BonAchat::getQteCommandee() const {
    return qteCommandee;
}

string BonAchat::getDateCommande() const {
    return dateCommande;
}
void BonAchat::setIdFournisseur(int idFournisseur) {
    this->idFournisseur = idFournisseur;
}
void BonAchat::setIdProduit(int idProduit) {
    this->idProduit = idProduit;
}
void BonAchat::setQteCommandee(int qteCommandee) {
    this->qteCommandee = qteCommandee;
}
void BonAchat::setDateCommande(const string& dateCommande) {
     this->dateCommande = dateCommande;
}
