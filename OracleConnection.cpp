#include "OracleConnection.h"
#include <cstring>
#include <vector>
#include <map>
#include <string>

void OracleConnection::handleError(sword status) {
    if (status != OCI_SUCCESS && status != OCI_SUCCESS_WITH_INFO) {
        char errorMsg[512];
        sb4 errCode;
        OCIErrorGet(err, 1, nullptr, &errCode, (OraText*)errorMsg, sizeof(errorMsg), OCI_HTYPE_ERROR);
        cerr << "OCI Error: " << errorMsg << endl;
        exit(EXIT_FAILURE);
    }
}

OracleConnection::OracleConnection(const string& username, const string& password, const string& connString)
    : env(nullptr), err(nullptr), srv(nullptr), ses(nullptr), svc_ctx(nullptr),
      username(username), password(password), connString(connString) {}


bool OracleConnection::connect() {
     // Initialize OCI environment
    sword status;
    status = OCIEnvCreate(&env, OCI_DEFAULT, nullptr, nullptr, nullptr, nullptr, 0, nullptr);
    if (status != OCI_SUCCESS) {
        handleError(status);
        return false;
    }
    status = OCIHandleAlloc(env, (void **)&err, OCI_HTYPE_ERROR, 0, nullptr);
        if (status != OCI_SUCCESS) {
        handleError(status);
        return false;
    }
    status = OCIHandleAlloc(env, (void **)&srv, OCI_HTYPE_SERVER, 0, nullptr);
         if (status != OCI_SUCCESS) {
        handleError(status);
        return false;
    }
    status = OCIHandleAlloc(env, (void **)&ses, OCI_HTYPE_SESSION, 0, nullptr);
         if (status != OCI_SUCCESS) {
        handleError(status);
        return false;
    }
    status = OCIHandleAlloc(env, (void **)&svc_ctx, OCI_HTYPE_SVCCTX, 0, nullptr);
        if (status != OCI_SUCCESS) {
        handleError(status);
        return false;
    }

   status = OCILogon(env, err, &svc_ctx, (OraText *)username.c_str(), username.length(),
                            (OraText *)password.c_str(), password.length(), (OraText *)connString.c_str(), connString.length());
    if (status != OCI_SUCCESS) {
         handleError(status);
        return false;
    }
    
    cout << "Connected to Oracle database successfully!" << endl;
    return true;
}


vector<map<string, string>> OracleConnection::executeQuery(const string& query) {
    OCIStmt* stmt = nullptr;
    vector<map<string, string>> result;

    try {
        // Allocate statement handle
        handleError(OCIHandleAlloc(env, (dvoid**)&stmt, OCI_HTYPE_STMT, 0, nullptr));

        // Prepare the query
        handleError(OCIStmtPrepare(stmt, err, (text*)query.c_str(), query.length(), OCI_NTV_SYNTAX, OCI_DEFAULT));

        // Determine whether the query is a SELECT statement
        bool isSelectQuery = (query.find("SELECT") == 0 || query.find("select") == 0);

        if (isSelectQuery) {
            // Execute the statement
            handleError(OCIStmtExecute(svc_ctx, stmt, err, 0, 0, nullptr, nullptr, OCI_DEFAULT));

            // Get the number of columns in the result
            ub4 colCount = 0;
            handleError(OCIAttrGet(stmt, OCI_HTYPE_STMT, &colCount, nullptr, OCI_ATTR_PARAM_COUNT, err));

            // Fetch metadata about each column
            vector<string> columnNames;
            vector<char*> buffers(colCount);
            vector<sb2> indicators(colCount);
            vector<OCIDefine*> defines(colCount);

            for (ub4 colIndex = 1; colIndex <= colCount; ++colIndex) {
                OCIParam* param = nullptr;
                 handleError(OCIParamGet(stmt, OCI_HTYPE_STMT, err, (void**)&param, colIndex));


                text* colName;
                ub4 colNameLen;
                handleError(OCIAttrGet(param, OCI_DTYPE_PARAM, &colName, &colNameLen, OCI_ATTR_NAME, err));

                columnNames.push_back(string(reinterpret_cast<char*>(colName), colNameLen));

                // Allocate buffer for each column
                buffers[colIndex - 1] = new char[1024](); // Initialize with null bytes
                indicators[colIndex - 1] = 0;

                // Define output for each column
                handleError(OCIDefineByPos(stmt, &defines[colIndex - 1], err, colIndex,
                                           buffers[colIndex - 1], 1024, SQLT_STR,
                                           &indicators[colIndex - 1], nullptr, nullptr, OCI_DEFAULT));
            }

            // Fetch rows of data
            while (OCIStmtFetch2(stmt, err, 1, OCI_FETCH_NEXT, 0, OCI_DEFAULT) == OCI_SUCCESS) {
                map<string, string> row;

                for (ub4 colIndex = 1; colIndex <= colCount; ++colIndex) {
                    if (indicators[colIndex - 1] == -1) {
                        row[columnNames[colIndex - 1]] = "NULL";
                    } else {
                        row[columnNames[colIndex - 1]] = string(buffers[colIndex - 1], strnlen(buffers[colIndex - 1], 1024));
                    }
                }
                result.push_back(row);
            }

            // Free column buffers
            for (auto& buffer : buffers) {
                delete[] buffer;
            }
        } else {
            // Execute non-SELECT query
            handleError(OCIStmtExecute(svc_ctx, stmt, err, 1, 0, nullptr, nullptr, OCI_DEFAULT));

            // Commit the transaction for data-changing queries
            if (query.find("INSERT") == 0 || query.find("UPDATE") == 0 || query.find("DELETE") == 0) {
                handleError(OCITransCommit(svc_ctx, err, OCI_DEFAULT));
                cout << "Transaction committed successfully." << endl;
            }
        }

        cout << "Query executed successfully: " << query << endl;
    } catch (const exception& e) {
        cerr << "Error during query execution: " << e.what() << endl;
    }
    if (stmt) {
        OCIHandleFree(stmt, OCI_HTYPE_STMT);
    }

    return result;
}
int OracleConnection::getGeneratedId(const string& sequenceName) {
    string query = "SELECT " + sequenceName + ".CURRVAL FROM dual";  
    vector<map<string, string>> result = executeQuery(query); 

    if (!result.empty()) {
        return stoi(result[0]["CURRVAL"]); 
    }
    return -1; 
}
OracleConnection::~OracleConnection() {
     if (svc_ctx) OCIHandleFree(svc_ctx, OCI_HTYPE_SVCCTX);
    if (ses) OCIHandleFree(ses, OCI_HTYPE_SESSION);
    if (srv) OCIServerDetach(srv, err, OCI_DEFAULT);
    if (err) OCIHandleFree(err, OCI_HTYPE_ERROR);
    if (env) OCIHandleFree(env, OCI_HTYPE_ENV);
    cout << "Disconnected from Oracle database." << endl;
}
