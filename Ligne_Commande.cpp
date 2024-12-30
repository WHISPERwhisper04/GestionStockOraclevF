#include "Ligne_Commande.h"
#include "OracleConnection.h"
#include <iostream>
#include <vector>
#include <map>
#include <iomanip>

using namespace std;

LigneCommande::LigneCommande() : idProduit(0), idCommande(0), qteCommandee(0), montantAPayer(0) {}

LigneCommande::LigneCommande(int idProduit, int idCommande, int qteCommandee, double montantAPayer) :
        idProduit(idProduit), idCommande(idCommande), qteCommandee(qteCommandee), montantAPayer(montantAPayer) {}

LigneCommande::~LigneCommande() {}
double LigneCommande::getProductPrice(OracleConnection& conn, int idProduit) {
    string query = "SELECT Prix_Unitaire FROM Produit WHERE ID_Produit = " + to_string(idProduit);
    vector<map<string, string>> result = conn.executeQuery(query);
    if(!result.empty()){
        return stod(result[0].at("PRIX_UNITAIRE"));
    }
    else {
         cout << "Erreur : Aucun prix trouve pour le produit avec ID " << idProduit << endl;
            return 0.0;
       }

}

void LigneCommande::create(OracleConnection& conn) {
    double prixUnitaire = getProductPrice(conn, idProduit);
   this->montantAPayer = qteCommandee * prixUnitaire;
    string query = "INSERT INTO Ligne_Commande (ID_Produit, ID_Commande, Qte_Commandee, Montant_a_Payer) VALUES ("
                 + to_string(idProduit) + ", " + to_string(idCommande) + ", " + to_string(qteCommandee) + ", " + to_string(montantAPayer) + ")";
    conn.executeQuery(query);
    cout << "Ligne de commande ajoutee avec succes pour le produit " << idProduit << " et la commande " << idCommande << endl;
}
bool LigneCommande::read(OracleConnection& conn, int idProduit, int idCommande) {
    string query = "SELECT * FROM Ligne_Commande WHERE ID_Produit = " + to_string(idProduit) + " AND ID_Commande = " + to_string(idCommande);
    vector<map<string, string>> result = conn.executeQuery(query);
    if (!result.empty()) {
         this->idProduit = idProduit;
        this->idCommande = idCommande;
       if (result[0].count("QTE_COMMANDEE"))
           this->qteCommandee = stoi(result[0].at("QTE_COMMANDEE"));
        if (result[0].count("MONTANT_A_PAYER"))
            this->montantAPayer = stod(result[0].at("MONTANT_A_PAYER"));
          return true;
      }
    return false;
}
void LigneCommande::update(OracleConnection& conn) {
   double prixUnitaire = getProductPrice(conn, idProduit);
   this->montantAPayer = qteCommandee * prixUnitaire;
   string query = "UPDATE Ligne_Commande SET Qte_Commandee = " + to_string(qteCommandee) + ", Montant_a_Payer = " + to_string(montantAPayer)
                   + " WHERE ID_Produit = " + to_string(idProduit) + " AND ID_Commande = " + to_string(idCommande);
   conn.executeQuery(query);
    cout << "Ligne de commande mise a jour avec succes pour le produit " << idProduit << " et la commande " << idCommande << endl;
}
bool LigneCommande::deleteRecord(OracleConnection& conn) {
    if(read(conn, idProduit, idCommande)){
       string query = "DELETE FROM Ligne_Commande WHERE ID_Produit = " + to_string(idProduit) + " AND ID_Commande = " + to_string(idCommande);
        conn.executeQuery(query);
         cout << "Ligne de commande supprimee avec succes pour le produit " << idProduit << " et la commande " << idCommande << endl;
         return true;
   } else {
        cout << "Erreur: Ligne de commande non trouvee." << endl;
        return false;
   }
}

void LigneCommande::afficherToutesLignesCommandes(OracleConnection& conn) {
    string query = "SELECT ID_Produit, ID_Commande, Qte_Commandee, Montant_a_Payer FROM Ligne_Commande";
    vector<map<string, string>> result = conn.executeQuery(query);
      if (result.empty()) {
          cout << "Aucune ligne de commande trouvee." << endl;
      } else {
        int maxProduitWidth = 10;
         int maxCommandeWidth = 10;
          int maxQuantiteWidth = 12;
          int maxMontantWidth = 12;
       for (const auto& row : result) {
            if (row.count("ID_PRODUIT")) {
                maxProduitWidth = max(maxProduitWidth, (int)row.at("ID_PRODUIT").length());
            }
             if (row.count("ID_COMMANDE")) {
                maxCommandeWidth = max(maxCommandeWidth, (int)row.at("ID_COMMANDE").length());
             }
             if (row.count("QTE_COMMANDEE")) {
                maxQuantiteWidth = max(maxQuantiteWidth, (int)row.at("QTE_COMMANDEE").length());
             }
            if (row.count("MONTANT_A_PAYER")) {
                 maxMontantWidth = max(maxMontantWidth, (int)row.at("MONTANT_A_PAYER").length());
            }
        }
      int totalWidth = maxProduitWidth + maxCommandeWidth + maxQuantiteWidth + maxMontantWidth + 14;
        cout << left << setw(maxProduitWidth) << "Produit" << " | " << setw(maxCommandeWidth) << "Commande" << " | " << setw(maxQuantiteWidth) << "Quantite" << " | " << setw(maxMontantWidth) << "Montant" << endl;
      cout << setfill('-') << setw(totalWidth) << "" << setfill(' ') << endl;
        for (const auto& row : result) {
             if (row.count("ID_PRODUIT") && row.count("ID_COMMANDE") && row.count("QTE_COMMANDEE") && row.count("MONTANT_A_PAYER"))
                 cout << left << setw(maxProduitWidth) << row.at("ID_PRODUIT") << " | " << setw(maxCommandeWidth) << row.at("ID_COMMANDE") << " | " << setw(maxQuantiteWidth) << row.at("QTE_COMMANDEE") << " | " << setw(maxMontantWidth) << row.at("MONTANT_A_PAYER") << endl;
              else {
                   cout << "Erreur: Cle introuvable dans la ligne de commande" << endl;
               }
        }
      }
}
void LigneCommande::afficherLigneCommande() const {
   cout << "ID Produit: " << idProduit << ", ID Commande: " << idCommande << ", Quantite commandee: " << qteCommandee << ", Montant a payer : " << montantAPayer << endl;
};
int LigneCommande::getIdProduit() const {
    return idProduit;
}

int LigneCommande::getIdCommande() const {
    return idCommande;
}
int LigneCommande::getQteCommandee() const {
    return qteCommandee;
}
double LigneCommande::getMontantAPayer() const {
   return montantAPayer;
}

void LigneCommande::setIdProduit(int idProduit) {
     this->idProduit = idProduit;
 }
void LigneCommande::setIdCommande(int idCommande) {
     this->idCommande = idCommande;
}
void LigneCommande::setQteCommandee(int qteCommandee) {
     this->qteCommandee = qteCommandee;
}
