#include "Produit.h"
#include "OracleConnection.h"
#include <iostream>
#include <vector>
#include <map>
#include <iomanip>

using namespace std;

Produit::Produit() : id(0), nom(""), description(""), prix(0), seuil_minimal(0), id_rayon(0) {}
Produit::Produit(int id, string nom, string description, double prix, int seuil_minimal, int id_rayon) : id(id), nom(nom), description(description), prix(prix), seuil_minimal(seuil_minimal), id_rayon(id_rayon) {}
Produit::~Produit(){}

void Produit::create(OracleConnection& conn) {
    string query = "INSERT INTO Produit (ID_Produit, Nom_Produit, Description, Prix_Unitaire, Seuil_min, ID_Rayon) VALUES (seq_produit.NEXTVAL, '" + nom + "', '" + description + "', " + to_string(prix) + ", " + to_string(seuil_minimal) + ", " + to_string(id_rayon) + ")";
    conn.executeQuery(query);
    this->id = conn.getGeneratedId("seq_produit");
     cout << "Produit ajoute avec succes. ID: " << this->id << endl;
}
bool Produit::read(OracleConnection& conn, int id) {
    string query = "SELECT * FROM Produit WHERE ID_Produit = " + to_string(id);
    vector<map<string, string>> result = conn.executeQuery(query);

    if (!result.empty()) {
        this->id = id;
        if (result[0].count("NOM_PRODUIT"))
           this->nom = result[0].at("NOM_PRODUIT");
        if (result[0].count("DESCRIPTION"))
           this->description = result[0].at("DESCRIPTION");
      if (result[0].count("PRIX_UNITAIRE"))
            this->prix = stod(result[0].at("PRIX_UNITAIRE"));
        if (result[0].count("SEUIL_MIN"))
          this->seuil_minimal = stoi(result[0].at("SEUIL_MIN"));
      if (result[0].count("ID_RAYON"))
            this->id_rayon = stoi(result[0].at("ID_RAYON"));
        return true;
    }
    return false;
}

void Produit::update(OracleConnection& conn) {
    string query = "UPDATE Produit SET Nom_Produit = '" + nom
           + "', Description = '" + description + "', Prix_Unitaire = "
            + to_string(prix) + ", Seuil_min = " + to_string(seuil_minimal) + ", ID_Rayon = " + to_string(id_rayon)
          + " WHERE ID_Produit = " + to_string(id);
   conn.executeQuery(query);
     cout << "Produit mis a jour avec succes." << endl;
}
bool Produit::deleteRecord(OracleConnection& conn) {
    if (read(conn, id)) {
         string query = "DELETE FROM Produit WHERE ID_Produit = " + to_string(id);
       vector<map<string, string>> result = conn.executeQuery(query);
         cout << "Produit supprime avec succes." << endl;
          return true;
     } else {
           cout << "Erreur: Produit non trouve." << endl;
         return false;
     }
}

void Produit::afficherTousProduits(OracleConnection& conn) {
    string query = "SELECT ID_Produit, Nom_Produit, Description, Prix_Unitaire, Seuil_min, ID_Rayon FROM Produit";
    vector<map<string, string>> result = conn.executeQuery(query);
    if (result.empty()) {
      cout << "Aucun produit trouve." << endl;
    } else {
       int maxIdWidth = 8;
       int maxNomWidth = 10;
         int maxDescriptionWidth = 10;
         int maxPrixWidth = 12;
        int maxSeuilWidth = 12;
        int maxRayonWidth = 10;
         for (const auto& row : result) {
            if (row.count("ID_PRODUIT")) {
                maxIdWidth = max(maxIdWidth, (int)row.at("ID_PRODUIT").length());
            }
           if (row.count("NOM_PRODUIT")) {
               maxNomWidth = max(maxNomWidth, (int)row.at("NOM_PRODUIT").length());
            }
            if (row.count("DESCRIPTION")) {
                  maxDescriptionWidth = max(maxDescriptionWidth, (int)row.at("DESCRIPTION").length());
            }
            if (row.count("PRIX_UNITAIRE")) {
                 maxPrixWidth = max(maxPrixWidth, (int)row.at("PRIX_UNITAIRE").length());
           }
           if (row.count("SEUIL_MIN")) {
               maxSeuilWidth = max(maxSeuilWidth, (int)row.at("SEUIL_MIN").length());
            }
             if (row.count("ID_RAYON")) {
                maxRayonWidth = max(maxRayonWidth, (int)row.at("ID_RAYON").length());
             }
        }
        int totalWidth = maxIdWidth + maxNomWidth + maxDescriptionWidth + maxPrixWidth+ maxSeuilWidth+ maxRayonWidth + 14;
          // Affichage de l'en-tête
         cout << left << setw(maxIdWidth) << "ID" << " | " << setw(maxNomWidth) << "Nom" << " | " << setw(maxDescriptionWidth) << "Description" << " | " << setw(maxPrixWidth) << "Prix" << " | " << setw(maxSeuilWidth) << "Seuil" <<  " | " << setw(maxRayonWidth) << "Rayon" << endl;
       cout << setfill('-') << setw(totalWidth) << "" << setfill(' ') << endl;
        for (const auto& row : result) {
          if (row.count("ID_PRODUIT") && row.count("NOM_PRODUIT") && row.count("DESCRIPTION") && row.count("PRIX_UNITAIRE") && row.count("SEUIL_MIN") && row.count("ID_RAYON")){
                cout << left << setw(maxIdWidth) << row.at("ID_PRODUIT") << " | " << setw(maxNomWidth) << row.at("NOM_PRODUIT") << " | " << setw(maxDescriptionWidth) << row.at("DESCRIPTION") << " | " << setw(maxPrixWidth) << row.at("PRIX_UNITAIRE") << " | " << setw(maxSeuilWidth) << row.at("SEUIL_MIN") << " | " << setw(maxRayonWidth) << row.at("ID_RAYON") << endl;
             }
            else {
                cout << "Erreur: Cle introuvable dans la ligne du produit" << endl;
              }
        }
    }
}
void Produit::rechercherProduitParId(OracleConnection& conn, int id_produit) {
      string query = "SELECT ID_Produit, Nom_Produit, Description, Prix_Unitaire, Seuil_min, ID_Rayon FROM Produit WHERE ID_Produit = " + to_string(id_produit);
    vector<map<string, string>> result = conn.executeQuery(query);

   if (result.empty()) {
        cout << "Aucun produit trouve avec l'ID : " << id_produit << endl;
     } else {
       cout << "Produit trouve avec succes :" << endl;
      int maxIdWidth = 8;
      int maxNomWidth = 10;
        int maxDescriptionWidth = 10;
        int maxPrixWidth = 12;
         int maxSeuilWidth = 12;
        int maxRayonWidth = 10;
       for (const auto& row : result) {
           if (row.count("ID_PRODUIT")) {
                maxIdWidth = max(maxIdWidth, (int)row.at("ID_PRODUIT").length());
            }
           if (row.count("NOM_PRODUIT")) {
               maxNomWidth = max(maxNomWidth, (int)row.at("NOM_PRODUIT").length());
             }
             if (row.count("DESCRIPTION")) {
                maxDescriptionWidth = max(maxDescriptionWidth, (int)row.at("DESCRIPTION").length());
           }
            if (row.count("PRIX_UNITAIRE")) {
               maxPrixWidth = max(maxPrixWidth, (int)row.at("PRIX_UNITAIRE").length());
            }
           if (row.count("SEUIL_MIN")) {
              maxSeuilWidth = max(maxSeuilWidth, (int)row.at("SEUIL_MIN").length());
           }
           if (row.count("ID_RAYON")) {
              maxRayonWidth = max(maxRayonWidth, (int)row.at("ID_RAYON").length());
             }
        }
      int totalWidth = maxIdWidth + maxNomWidth + maxDescriptionWidth + maxPrixWidth+ maxSeuilWidth+ maxRayonWidth + 14;
        // Affichage de l'en-tête
        cout << left << setw(maxIdWidth) << "ID" << " | " << setw(maxNomWidth) << "Nom" << " | " << setw(maxDescriptionWidth) << "Description" << " | " << setw(maxPrixWidth) << "Prix" << " | " << setw(maxSeuilWidth) << "Seuil" <<  " | " << setw(maxRayonWidth) << "Rayon" << endl;
        cout << setfill('-') << setw(totalWidth) << "" << setfill(' ') << endl;
      for (const auto& row : result) {
          if (row.count("ID_PRODUIT") && row.count("NOM_PRODUIT") && row.count("DESCRIPTION") && row.count("PRIX_UNITAIRE") && row.count("SEUIL_MIN") && row.count("ID_RAYON")){
                cout << left << setw(maxIdWidth) << row.at("ID_PRODUIT") << " | " << setw(maxNomWidth) << row.at("NOM_PRODUIT") << " | " << setw(maxDescriptionWidth) << row.at("DESCRIPTION") << " | " << setw(maxPrixWidth) << row.at("PRIX_UNITAIRE") << " | " << setw(maxSeuilWidth) << row.at("SEUIL_MIN") << " | " << setw(maxRayonWidth) << row.at("ID_RAYON") << endl;
            } else {
               cout << "Erreur: Cle introuvable dans la ligne du produit" << endl;
            }
      }
    }
}
void Produit::rechercherProduitParNom(OracleConnection& conn,const string& nomProduit) {
    string query = "SELECT ID_Produit, Nom_Produit, Description, Prix_Unitaire, Seuil_min, ID_Rayon FROM Produit WHERE Nom_Produit LIKE '%" + nomProduit + "%'";
    vector<map<string, string>> result = conn.executeQuery(query);
    
    if (result.empty()) {
        cout << "Aucun produit trouve avec le nom : " << nomProduit << endl;
    } else {
        cout << "Produit trouve avec succes :" << endl;
          
               // Afficher le produit trouvé 
               Produit produit;
           if (produit.read(conn,stoi(result[0].at("ID_PRODUIT")))) {
                produit.afficherProduit();
             }
         
    }
}
//void Produit::rechercherProduitParNom(OracleConnection& conn,const string& nomProduit) {
//   string query = "SELECT ID_Produit, Nom_Produit, Description, Prix_Unitaire, Seuil_min, ID_Rayon FROM Produit WHERE Nom_Produit = '" + nomProduit + "'";
//   vector<map<string, string>> result = conn.executeQuery(query);
//
//     if (result.empty()) {
//          cout << "Aucun produit trouve avec le nom : " << nomProduit << endl;
//        } else {
//            cout << "Produit trouve avec succes :" << endl;
//            int maxIdWidth = 8;
//           int maxNomWidth = 10;
//            int maxDescriptionWidth = 10;
//          int maxPrixWidth = 12;
//          int maxSeuilWidth = 12;
//           int maxRayonWidth = 10;
//       for (const auto& row : result) {
//           if (row.count("ID_PRODUIT")) {
//                maxIdWidth = max(maxIdWidth, (int)row.at("ID_PRODUIT").length());
//              }
//           if (row.count("NOM_PRODUIT")) {
//               maxNomWidth = max(maxNomWidth, (int)row.at("NOM_PRODUIT").length());
//            }
//            if (row.count("DESCRIPTION")) {
//                 maxDescriptionWidth = max(maxDescriptionWidth, (int)row.at("DESCRIPTION").length());
//             }
//            if (row.count("PRIX_UNITAIRE")) {
//                  maxPrixWidth = max(maxPrixWidth, (int)row.at("PRIX_UNITAIRE").length());
//             }
//            if (row.count("SEUIL_MIN")) {
//                maxSeuilWidth = max(maxSeuilWidth, (int)row.at("SEUIL_MIN").length());
//            }
//          if (row.count("ID_RAYON")) {
//                 maxRayonWidth = max(maxRayonWidth, (int)row.at("ID_RAYON").length());
//            }
//       }
//     int totalWidth = maxIdWidth + maxNomWidth + maxDescriptionWidth + maxPrixWidth+ maxSeuilWidth+ maxRayonWidth + 14;
//        // Affichage de l'en-tête
//         cout << left << setw(maxIdWidth) << "ID" << " | " << setw(maxNomWidth) << "Nom" << " | " << setw(maxDescriptionWidth) << "Description" << " | " << setw(maxPrixWidth) << "Prix" << " | " << setw(maxSeuilWidth) << "Seuil" <<  " | " << setw(maxRayonWidth) << "Rayon" << endl;
//        cout << setfill('-') << setw(totalWidth) << "" << setfill(' ') << endl;
//
//        for (const auto& row : result) {
//            if (row.count("ID_PRODUIT") && row.count("NOM_PRODUIT") && row.count("DESCRIPTION") && row.count("PRIX_UNITAIRE") && row.count("SEUIL_MIN") && row.count("ID_RAYON")){
//                  cout << left << setw(maxIdWidth) << row.at("ID_PRODUIT") << " | " << setw(maxNomWidth) << row.at("NOM_PRODUIT") << " | " << setw(maxDescriptionWidth) << row.at("DESCRIPTION") << " | " << setw(maxPrixWidth) << row.at("PRIX_UNITAIRE") << " | " << setw(maxSeuilWidth) << row.at("SEUIL_MIN") << " | " << setw(maxRayonWidth) << row.at("ID_RAYON") << endl;
//               }
//          else {
//               cout << "Erreur: Cle introuvable dans la ligne du produit" << endl;
//             }
//        }
//   }
//}
void Produit::afficherProduit() const{
     cout << "ID Produit: " << id << ", Nom Produit: " << nom << ", Description : " << description << ", Prix : " << prix << ", Seuil minimal : " << seuil_minimal << ", ID Rayon : " << id_rayon << endl;
};
int Produit::getIdRayon() const {
    return id_rayon;
};
 void Produit::setId(int id) {
        this->id = id;
    }
    int Produit::getId() const {
        return id;
    }
     void Produit::setNom(const string& nom) {
        this->nom = nom;
    }
    string Produit::getNom() const {
       return nom;
     }
       void Produit::setDescription(const string& description) {
        this->description = description;
     }
   string Produit::getDescription() const {
       return description;
   }
    void Produit::setPrix(double prix) {
      this->prix = prix;
     }
  double Produit::getPrix() const {
       return prix;
    }
   void Produit::setSeuilMinimal(int seuil) {
        this->seuil_minimal = seuil;
   }
    int Produit::getSeuilMinimal() const {
       return seuil_minimal;
   }
   void Produit::setIdRayon(int idRayon) {
        this->id_rayon = idRayon;
    }
