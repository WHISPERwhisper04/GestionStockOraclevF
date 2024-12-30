#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include "OracleConnection.h"

using namespace std;

class Client {
private:
    int id;
    string nom;
    string prenom;
    string adresse;
    string email;

public:
    Client();
    Client(int id, const string& nom, const string& prenom, const string& adresse, const string& email);
    ~Client();

    void create(OracleConnection& conn);
    bool read(OracleConnection& conn, int id);
    void update(OracleConnection& conn);
    bool deleteRecord(OracleConnection& conn);

    void afficherTousClients(OracleConnection& conn);
    void afficherClient() const;
    
   
    int getId() const;
    string getNom() const;
    string getPrenom() const;
    string getAdresse() const;
    string getEmail() const;

    void setId(int id);
    void setNom(const string& nom);
    void setPrenom(const string& prenom);
    void setAdresse(const string& adresse);
    void setEmail(const string& email);
};

#endif
