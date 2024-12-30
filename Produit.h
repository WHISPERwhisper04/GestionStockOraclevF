#ifndef PRODUIT_H
#define PRODUIT_H

#include <string>

class OracleConnection;

class Produit {
private:
    int id;
    std::string nom;
    std::string description;
    double prix;
    int seuil_minimal;
    int id_rayon;
public:
    Produit();
    Produit(int id, std::string nom, std::string description, double prix, int seuil_minimal, int id_rayon);
    ~Produit();
    void create(OracleConnection& conn);
    bool read(OracleConnection& conn, int id);
      void afficherProduit() const; 

    void update(OracleConnection& conn);
    bool deleteRecord(OracleConnection& conn);
     void afficherTousProduits(OracleConnection& conn);
      void rechercherProduitParId(OracleConnection& conn, int id_produit);
     void rechercherProduitParNom(OracleConnection& conn, const std::string& nomProduit);

   int getIdRayon() const;
        void setId(int id);
    int getId() const;
    void setNom(const std::string& nom);
    std::string getNom() const;
    void setDescription(const std::string& description);
    std::string getDescription() const;
    void setPrix(double prix);
    double getPrix() const;
    void setSeuilMinimal(int seuil);
    int getSeuilMinimal() const;
    void setIdRayon(int idRayon);
};

#endif
