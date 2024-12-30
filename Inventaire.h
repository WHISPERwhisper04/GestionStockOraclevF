#ifndef INVENTAIRE_H
#define INVENTAIRE_H

#include <string>
#include "OracleConnection.h"

class Inventaire {
private:
    int idRayon;
    int idDepot;
    int qteStockee;
    std::string dateMaj;

public:
    Inventaire();
    Inventaire(int idRayon, int idDepot, int qteStockee, const std::string& dateMaj);
    ~Inventaire();

    void create(OracleConnection& conn);
    bool read(OracleConnection& conn, int idRayon, int idDepot);
    void update(OracleConnection& conn);
    bool deleteRecord(OracleConnection& conn);

    void updateInventaire(OracleConnection& conn, int idRayon, int idDepot, int newStock);
    void viewInventaireStatus(OracleConnection& conn);
    void viewInventaireStatusByRayon(OracleConnection& conn,int idRayon);
    void viewInventaireStatusByDepot(OracleConnection& conn,int idDepot);

    int getIdRayon() const;
    int getIdDepot() const;
    int getQteStockee() const;
    std::string getDateMaj() const;

    void setIdRayon(int idRayon);
    void setIdDepot(int idDepot);
    void setQteStockee(int qteStockee);
    void setDateMaj(const std::string& dateMaj);


};

#endif
