#ifndef ORACLECONNECTION_H_
#define ORACLECONNECTION_H_

#include <oci.h>
#include <string>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

class OracleConnection {
private:
    OCIEnv* env;
    OCIError* err;
    OCIServer* srv;
    OCISession* ses;
    OCISvcCtx* svc_ctx;
    
    string username;
    string password;
    string connString;

    void handleError(sword status);

public:
    OracleConnection(const string& username, const string& password, const string& connString);
    bool connect();
    vector<map <string, string>> executeQuery(const string& query);
    int getGeneratedId(const string& sequenceName);
    ~OracleConnection();
};

#endif 
