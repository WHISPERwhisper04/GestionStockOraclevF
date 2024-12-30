#include <iostream>
#include "Depot.h"
#include "Rayon.h"
#include "Produit.h"
#include "Inventaire.h"
#include "Fournisseur.h"
#include "Client.h"
#include "Bon_achat.h"  
#include "Commande.h"
#include "Ligne_Commande.h"
#include "OracleConnection.h"

using namespace std;

int main() {

    OracleConnection conn("stock", "root", "XE");
    if (!conn.connect()) {
        return 1;
    }

    int choixPrincipal;
    do {
        cout << "\n--- Menu Principal ---" << endl;
        cout << "1: Gerer les rayons" << endl;
        cout << "2: Gerer les depots" << endl;
        cout << "3: Gerer les produits" << endl;
        cout << "4: Gerer l'inventaire" << endl;
        cout << "5: Gerer les fournisseurs" << endl;
        cout << "6: Gerer les clients" << endl;
        cout << "7: Gerer les bons d'achat" << endl; 
        cout << "8: Gerer les commandes" << endl; 
        cout << "9: Gerer les lignes de commande" << endl; 
        cout << "0: Quitter" << endl;
        cout << "Choisissez une option : ";
        cin >> choixPrincipal;

        switch (choixPrincipal) {
            case 1: {
                int choixRayon;
                do {
                    cout << "\n--- Menu Gestion des Rayons ---" << endl;
                    cout << "1: Creer un rayon" << endl;
                    cout << "2: Lire un rayon par ID" << endl;
                    cout << "3: Mettre a jour un rayon" << endl;
                    cout << "4: Supprimer un rayon" << endl;
                    cout << "5: Afficher tous les rayons" << endl;
                    cout << "0: Retour au menu principal" << endl;
                    cout << "Choisissez une option : ";
                    cin >> choixRayon;
                    cin.ignore();

                    switch (choixRayon) {
                        case 1: {
                            string nomRayon;
                            cout << "Saisissez le nom du rayon : ";
                            getline(cin, nomRayon);
                            Rayon newRayon;
                            newRayon.setNom(nomRayon);
                            newRayon.create(conn);
                            break;
                        }
                        case 2: {
                            int idRayon;
                            cout << "Saisissez l'ID du rayon : ";
                            cin >> idRayon;
                            cin.ignore();
                            Rayon rayon1;
                            if (rayon1.read(conn, idRayon)) {
                                cout << "Rayon trouve : " << endl;
                                rayon1.afficherRayon();
                            } else {
                                cout << "Rayon non trouve." << endl;
                            }
                            break;
                        }
                        case 3: {
                            int idRayon;
                            string nomRayon;
                            cout << "Saisissez l'ID du rayon a modifier : ";
                            cin >> idRayon;
                            cin.ignore();
                            Rayon rayonToModify;
                            if (rayonToModify.read(conn, idRayon)) {
                                cout << "Saisissez le nouveau nom du rayon : ";
                                getline(cin, nomRayon);
                                rayonToModify.setNom(nomRayon);
                                rayonToModify.update(conn);
                                cout << "Rayon mis a jour avec succes." << endl;
                            } else {
                                cout << "Rayon non trouve." << endl;
                            }
                            break;
                        }
                        case 4: {
                            int idRayon;
                            cout << "Saisissez l'ID du rayon a supprimer : ";
                            cin >> idRayon;
                            cin.ignore();
                            Rayon toDelete;
                            toDelete.setId(idRayon);
                            toDelete.deleteRecord(conn);
                            break;
                        }
                        case 5: {
                            Rayon rayon;
                            rayon.afficherTousRayons(conn);
                            break;
                        }
                        case 0: {
                            break;
                        }
                        default: {
                            cout << "Choix invalide. Veuillez reessayer." << endl;
                            break;
                        }
                    }
                } while (choixRayon != 0);
                break;
            }
            case 2: {
                int choixDepot;
                do {
                    cout << "\n--- Menu Gestion des Depots ---" << endl;
                    cout << "1: Creer un depot" << endl;
                    cout << "2: Lire un depot par ID" << endl;
                    cout << "3: Mettre a jour un depot" << endl;
                    cout << "4: Supprimer un depot" << endl;
                    cout << "5: Afficher tous les depots" << endl;
                    cout << "0: Retour au menu principal" << endl;
                    cout << "Choisissez une option : ";
                    cin >> choixDepot;
                    cin.ignore();

                    switch (choixDepot) {
                        case 1: {
                            string nomDepot, adresseDepot;
                            cout << "Saisissez le nom du depot : ";
                            getline(cin, nomDepot);
                            cout << "Saisissez l'adresse du depot : ";
                            getline(cin, adresseDepot);
                            Depot newDepot;
                            newDepot.setNomDepot(nomDepot);
                            newDepot.setAdresse(adresseDepot);
                            newDepot.ajouterDepot(conn);
                            if (newDepot.getIdDepot() != 0) {
                                cout << "Depot cree avec succes. ID: " << newDepot.getIdDepot() << endl;
                            } else {
                                cout << "Erreur lors de la creation du depot" << endl;
                            }
                            break;
                        }
                        case 2: {
                            int idDepot;
                            cout << "Saisissez l'ID du depot : ";
                            cin >> idDepot;
                            cin.ignore();
                            Depot depot1;
                            if (depot1.read(conn, idDepot)) {
                                cout << "Depot trouve : " << endl;
                                depot1.afficherDepot();
                            } else {
                                cout << "Depot non trouve." << endl;
                            }
                            break;
                        }
                        case 3: {
                            int idDepot;
                            string nomDepot, adresseDepot;
                            cout << "Saisissez l'ID du depot a modifier : ";
                            cin >> idDepot;
                            cin.ignore();
                            Depot depotToModify;
                            if (depotToModify.read(conn, idDepot)) {
                                cout << "Saisissez le nouveau nom du depot : ";
                                getline(cin, nomDepot);
                                cout << "Saisissez la nouvelle adresse du depot : ";
                                getline(cin, adresseDepot);
                                depotToModify.setNomDepot(nomDepot);
                                depotToModify.setAdresse(adresseDepot);
                                depotToModify.modifierDepot(conn, nomDepot, adresseDepot);
                                cout << "Depot mis a jour avec succes." << endl;
                            } else {
                                cout << "Depot non trouve." << endl;
                            }
                            break;
                        }
                        case 4: {
                            int idDepot;
                            cout << "Saisissez l'ID du depot a supprimer : ";
                            cin >> idDepot;
                            cin.ignore();
                            Depot toDelete;
                            toDelete.setIdDepot(idDepot);
                            toDelete.supprimerDepot(conn);
                            break;
                        }
                        case 5: {
                            Depot depot;
                            depot.afficherTousDepots(conn);
                            break;
                        }
                        case 0: {
                            break;
                        }
                        default: {
                            cout << "Choix invalide. Veuillez reessayer." << endl;
                            break;
                        }
                    }
                } while (choixDepot != 0);
                break;
            }
            case 3: {
                int choixProduit;
                do {
                    cout << "\n--- Menu Gestion des Produits ---" << endl;
                    cout << "1: Creer un produit" << endl;
                    cout << "2: Lire un produit par ID" << endl;
                    cout << "3: Mettre a jour un produit" << endl;
                    cout << "4: Supprimer un produit" << endl;
                    cout << "5: Afficher tous les produits" << endl;
                    cout << "6: Rechercher un produit par nom" << endl;
                    cout << "7: Rechercher un produit par id" << endl;
                    cout << "0: Retour au menu principal" << endl;
                    cout << "Choisissez une option : ";
                    cin >> choixProduit;
                    cin.ignore();

                    switch (choixProduit) {
                        case 1: {
                            string nomProduit, descriptionProduit;
                            double prixProduit;
                            int seuilProduit, idRayonProduit;

                            cout << "Saisissez le nom du produit : ";
                            getline(cin, nomProduit);
                            cout << "Saisissez la description du produit : ";
                            getline(cin, descriptionProduit);
                            cout << "Saisissez le prix du produit : ";
                            cin >> prixProduit;
                            cout << "Saisissez le seuil minimal du produit : ";
                            cin >> seuilProduit;
                            cout << "Saisissez l'ID du rayon : ";
                            cin >> idRayonProduit;
                             cin.ignore();

                            Produit newProduit;
                            newProduit.setNom(nomProduit);
                            newProduit.setDescription(descriptionProduit);
                            newProduit.setPrix(prixProduit);
                            newProduit.setSeuilMinimal(seuilProduit);
                            newProduit.setIdRayon(idRayonProduit);
                            newProduit.create(conn);
                            break;
                        }
                        case 2: {
                            int idProduit;
                            cout << "Saisissez l'ID du produit : ";
                            cin >> idProduit;
                            cin.ignore();
                            Produit produit1;
                            if (produit1.read(conn, idProduit)) {
                                cout << "Produit trouve : " << endl;
                                produit1.afficherProduit();
                            } else {
                                cout << "Produit non trouve." << endl;
                            }
                            break;
                        }
                        case 3: {
                            int idProduit;
                            string nomProduit, descriptionProduit;
                            double prixProduit;
                            int seuilProduit, idRayonProduit;
                            cout << "Saisissez l'ID du produit a modifier : ";
                            cin >> idProduit;
                            cin.ignore();
                            Produit produitToModify;
                            if (produitToModify.read(conn, idProduit)) {
                                cout << "Saisissez le nouveau nom du produit : ";
                                getline(cin, nomProduit);
                                cout << "Saisissez la nouvelle description du produit : ";
                                getline(cin, descriptionProduit);
                                cout << "Saisissez le nouveau prix du produit : ";
                                cin >> prixProduit;
                                cout << "Saisissez le nouveau seuil minimal du produit : ";
                                cin >> seuilProduit;
                                cout << "Saisissez le nouveau ID du rayon du produit : ";
                                cin >> idRayonProduit;
                                cin.ignore();
                                produitToModify.setNom(nomProduit);
                                produitToModify.setDescription(descriptionProduit);
                                produitToModify.setPrix(prixProduit);
                                produitToModify.setSeuilMinimal(seuilProduit);
                                produitToModify.setIdRayon(idRayonProduit);
                                produitToModify.update(conn);
                            } else {
                                cout << "Produit non trouve." << endl;
                            }
                            break;
                        }
                        case 4: {
                            int idProduit;
                            cout << "Saisissez l'ID du produit a supprimer : ";
                            cin >> idProduit;
                            cin.ignore();
                            Produit toDelete;
                            toDelete.setId(idProduit);
                            toDelete.deleteRecord(conn);
                            break;
                        }
                        case 5: {
                            Produit produit;
                            produit.afficherTousProduits(conn);
                            break;
                        }
                        case 6: {
                            string nomProduit;
                            cout << "Saisissez le nom du produit a rechercher : ";
                            getline(cin, nomProduit);
                            Produit produit;
                            produit.rechercherProduitParNom(conn, nomProduit);
                            break;
                        }
                        case 7: {
                            int idProduit;
                            cout << "Saisissez l'ID du produit a rechercher : ";
                            cin >> idProduit;
                             cin.ignore();
                            Produit produit;
                            produit.rechercherProduitParId(conn, idProduit);
                            break;
                        }
                        case 0: {
                            break;
                        }
                        default: {
                            cout << "Choix invalide. Veuillez reessayer." << endl;
                            break;
                        }
                    }
                } while (choixProduit != 0);
                break;
            }
          case 4: {
                int choixInventaire;
                do {
                    cout << "\n--- Menu Gestion de l'Inventaire ---" << endl;
                    cout << "1: Creer une entree d'inventaire" << endl;
                    cout << "2: Lire une entree d'inventaire par ID Rayon et ID Depot" << endl;
                    cout << "3: Mettre a jour une entree d'inventaire" << endl;
                   cout << "4: Supprimer une entree d'inventaire" << endl;
                   cout << "5: Mettre a jour le stock d'un produit" << endl;
                    cout << "6: Afficher l'etat de l'inventaire" << endl;
                    cout << "7: Afficher l'etat de l'inventaire par rayon" << endl;
                    cout << "8: Afficher l'etat de l'inventaire par depot" << endl;
                  cout << "0: Retour au menu principal" << endl;
                    cout << "Choisissez une option : ";
                    cin >> choixInventaire;
                    cin.ignore();

                    switch (choixInventaire) {
                       case 1:{
                             int idRayon, idDepot, qteStockee;

                             cout << "Saisissez l'ID du rayon : ";
                            cin >> idRayon;
                            cout << "Saisissez l'ID du depot : ";
                           cin >> idDepot;
                            cout << "Saisissez la quantite stockee : ";
                           cin >> qteStockee;
                           cin.ignore();
                         Inventaire newInventaire;
                            newInventaire.setIdRayon(idRayon);
                           newInventaire.setIdDepot(idDepot);
                            newInventaire.setQteStockee(qteStockee);
                           newInventaire.create(conn);
                            break;
                          }
                          case 2:{
                            int idRayon, idDepot;
                            cout << "Saisissez l'ID du rayon : ";
                            cin >> idRayon;
                            cout << "Saisissez l'ID du depot : ";
                            cin >> idDepot;
                             cin.ignore();
                           Inventaire inventaire;
                             if(inventaire.read(conn,idRayon,idDepot)){
                                   cout << "Inventaire trouve : " << endl;
                                 cout << "ID Rayon: " << inventaire.getIdRayon() << ", ID Depot : " << inventaire.getIdDepot() << ", Quantite stockee : " << inventaire.getQteStockee() << ", Date MAJ : " << inventaire.getDateMaj() << endl;
                            } else {
                                cout << "Inventaire non trouve." << endl;
                           }
                            break;
                         }
                     case 3:{
                          int idRayon, idDepot, qteStockee;

                            cout << "Saisissez l'ID du rayon : ";
                            cin >> idRayon;
                            cout << "Saisissez l'ID du depot : ";
                            cin >> idDepot;
                            cout << "Saisissez la nouvelle quantite stockee : ";
                             cin >> qteStockee;
                             cin.ignore();
                             Inventaire inventaireToModify;
                           if(inventaireToModify.read(conn,idRayon,idDepot)){
                                  inventaireToModify.setQteStockee(qteStockee);
                                 inventaireToModify.update(conn);
                                  cout << "Inventaire mis a jour avec succes." << endl;
                           }else{
                                  cout << "Inventaire non trouve." << endl;
                            }
                           break;
                         }
                    case 4:{
                          int idRayon, idDepot;
                         cout << "Saisissez l'ID du rayon : ";
                            cin >> idRayon;
                            cout << "Saisissez l'ID du depot : ";
                            cin >> idDepot;
                            cin.ignore();
                           Inventaire toDelete;
                            if (toDelete.read(conn, idRayon, idDepot)){
                              toDelete.deleteRecord(conn);
                            }
                             break;
                          }
                    case 5: {
                           int idRayon, idDepot, newStock;
                            cout << "Saisissez l'ID du rayon : ";
                           cin >> idRayon;
                             cout << "Saisissez l'ID du depot : ";
                             cin >> idDepot;
                            cout << "Saisissez la nouvelle quantite de stock : ";
                           cin >> newStock;
                            cin.ignore();
                            Inventaire inventaire;
                           inventaire.updateInventaire(conn, idRayon, idDepot, newStock);
                            break;
                       }
                       case 6: {
                          Inventaire inventaire;
                           inventaire.viewInventaireStatus(conn);
                           break;
                     }
                    case 7:{
                         int idRayon;
                           cout << "Saisissez l'ID du rayon pour consulter l'inventaire: ";
                         cin >> idRayon;
                          cin.ignore();
                        Inventaire inventaire;
                           inventaire.viewInventaireStatusByRayon(conn,idRayon);
                           break;
                    }
                    case 8:{
                        int idDepot;
                           cout << "Saisissez l'ID du depot pour consulter l'inventaire: ";
                           cin >> idDepot;
                           cin.ignore();
                        Inventaire inventaire;
                           inventaire.viewInventaireStatusByDepot(conn, idDepot);
                         break;
                     }
                     case 0: {
                            break;
                        }
                        default: {
                            cout << "Choix invalide. Veuillez reessayer." << endl;
                            break;
                        }
                    }
                } while (choixInventaire != 0);
                break;
            }
          case 5: {
                int choixFournisseur;
                do {
                    cout << "\n--- Menu Gestion des Fournisseurs ---" << endl;
                    cout << "1: Creer un fournisseur" << endl;
                    cout << "2: Lire un fournisseur par ID" << endl;
                    cout << "3: Mettre a jour un fournisseur" << endl;
                   cout << "4: Supprimer un fournisseur" << endl;
                    cout << "5: Afficher tous les fournisseurs" << endl;
                    cout << "0: Retour au menu principal" << endl;
                    cout << "Choisissez une option : ";
                    cin >> choixFournisseur;
                    cin.ignore();

                    switch (choixFournisseur) {
                        case 1:{
                            string nomFournisseur, telFournisseur, emailFournisseur;

                           cout << "Saisissez le nom du fournisseur : ";
                            getline(cin,nomFournisseur);
                             cout << "Saisissez le telephone du fournisseur : ";
                             getline(cin,telFournisseur);
                            cout << "Saisissez l'email du fournisseur : ";
                             getline(cin,emailFournisseur);
                            Fournisseur newFournisseur;
                           newFournisseur.setNom(nomFournisseur);
                            newFournisseur.setTel(telFournisseur);
                           newFournisseur.setEmail(emailFournisseur);
                            newFournisseur.create(conn);
                            break;
                       }
                        case 2:{
                            int idFournisseur;
                            cout << "Saisissez l'ID du fournisseur : ";
                            cin >> idFournisseur;
                            cin.ignore();
                           Fournisseur fournisseur1;
                            if(fournisseur1.read(conn,idFournisseur)){
                                 cout << "Fournisseur trouve : " << endl;
                                fournisseur1.afficherFournisseur();
                            }else {
                                  cout << "Fournisseur non trouve." << endl;
                             }
                            break;
                       }
                       case 3:{
                            int idFournisseur;
                            string nomFournisseur, telFournisseur, emailFournisseur;
                            cout << "Saisissez l'ID du fournisseur a modifier : ";
                            cin >> idFournisseur;
                             cin.ignore();
                           Fournisseur fournisseurToModify;
                           if (fournisseurToModify.read(conn,idFournisseur)) {
                              cout << "Saisissez le nouveau nom du fournisseur : ";
                                 getline(cin,nomFournisseur);
                             cout << "Saisissez le nouveau telephone du fournisseur : ";
                               getline(cin,telFournisseur);
                            cout << "Saisissez le nouveau email du fournisseur : ";
                             getline(cin,emailFournisseur);
                             fournisseurToModify.setNom(nomFournisseur);
                            fournisseurToModify.setTel(telFournisseur);
                             fournisseurToModify.setEmail(emailFournisseur);
                             fournisseurToModify.update(conn);
                                cout << "Fournisseur mis a jour avec succes." << endl;
                         }
                           else {
                                cout << "Fournisseur non trouve." << endl;
                            }
                            break;
                       }
                      case 4:{
                            int idFournisseur;
                            cout << "Saisissez l'ID du fournisseur a supprimer : ";
                            cin >> idFournisseur;
                            cin.ignore();
                           Fournisseur toDelete;
                            toDelete.setId(idFournisseur);
                            toDelete.deleteRecord(conn);
                            break;
                       }
                      case 5:{
                           Fournisseur fournisseur;
                            fournisseur.afficherTousFournisseurs(conn);
                            break;
                       }
                        case 0: {
                            break;
                        }
                        default: {
                            cout << "Choix invalide. Veuillez reessayer." << endl;
                            break;
                        }
                    }
                } while (choixFournisseur != 0);
                break;
            }
            case 6: {
                int choixClient;
                do {
                    cout << "\n--- Menu Gestion des Clients ---" << endl;
                    cout << "1: Creer un client" << endl;
                    cout << "2: Lire un client par ID" << endl;
                    cout << "3: Mettre a jour un client" << endl;
                    cout << "4: Supprimer un client" << endl;
                    cout << "5: Afficher tous les clients" << endl;
                    cout << "0: Retour au menu principal" << endl;
                    cout << "Choisissez une option : ";
                    cin >> choixClient;
                    cin.ignore();

                    switch (choixClient) {
                        case 1: {
                           string nomClient, prenomClient, adresseClient, emailClient;
                            cout << "Saisissez le nom du client : ";
                             getline(cin,nomClient);
                           cout << "Saisissez le prenom du client : ";
                            getline(cin,prenomClient);
                           cout << "Saisissez l'adresse du client : ";
                             getline(cin,adresseClient);
                           cout << "Saisissez l'email du client : ";
                             getline(cin,emailClient);
                            Client newClient;
                           newClient.setNom(nomClient);
                            newClient.setPrenom(prenomClient);
                           newClient.setAdresse(adresseClient);
                           newClient.setEmail(emailClient);
                            newClient.create(conn);
                            break;
                         }
                        case 2: {
                            int idClient;
                            cout << "Saisissez l'ID du client : ";
                            cin >> idClient;
                            cin.ignore();
                           Client client1;
                            if (client1.read(conn, idClient)) {
                                cout << "Client trouve : " << endl;
                                 client1.afficherClient();
                             } else {
                                cout << "Client non trouve." << endl;
                            }
                            break;
                        }
                        case 3: {
                           int idClient;
                            string nomClient, prenomClient, adresseClient, emailClient;
                            cout << "Saisissez l'ID du client a modifier : ";
                             cin >> idClient;
                              cin.ignore();
                            Client clientToModify;
                           if(clientToModify.read(conn, idClient)){
                             cout << "Saisissez le nouveau nom du client : ";
                            getline(cin,nomClient);
                              cout << "Saisissez le nouveau prenom du client : ";
                             getline(cin,prenomClient);
                            cout << "Saisissez la nouvelle adresse du client : ";
                             getline(cin,adresseClient);
                            cout << "Saisissez le nouvel email du client : ";
                            getline(cin,emailClient);
                             clientToModify.setNom(nomClient);
                           clientToModify.setPrenom(prenomClient);
                             clientToModify.setAdresse(adresseClient);
                             clientToModify.setEmail(emailClient);
                             clientToModify.update(conn);
                               cout << "Client mis a jour avec succes." << endl;
                           }
                          else {
                                cout << "Client non trouve." << endl;
                            }
                             break;
                       }
                        case 4: {
                            int idClient;
                            cout << "Saisissez l'ID du client a supprimer : ";
                            cin >> idClient;
                            cin.ignore();
                            Client toDelete;
                            toDelete.setId(idClient);
                             toDelete.deleteRecord(conn);
                            break;
                        }
                       case 5:{
                            Client client;
                           client.afficherTousClients(conn);
                            break;
                       }
                       case 0: {
                            break;
                        }
                        default: {
                            cout << "Choix invalide. Veuillez reessayer." << endl;
                            break;
                        }
                    }
                } while (choixClient != 0);
                break;
            }
         case 7: {
                int choixBonAchat;
                do {
                    cout << "\n--- Menu Gestion des Bons d'Achat ---" << endl;
                    cout << "1: Creer un bon d'achat" << endl;
                    cout << "2: Lire un bon d'achat par ID Fournisseur et ID Produit" << endl;
                   cout << "3: Mettre a jour un bon d'achat" << endl;
                  cout << "4: Supprimer un bon d'achat" << endl;
                    cout << "5: Afficher tous les bons d'achat" << endl;
                    cout << "0: Retour au menu principal" << endl;
                    cout << "Choisissez une option : ";
                    cin >> choixBonAchat;
                    cin.ignore();

                    switch (choixBonAchat) {
                        case 1: {
                            int idFournisseur, idProduit, qteCommandee;
                            string dateCommande;

                            cout << "Saisissez l'ID du fournisseur : ";
                            cin >> idFournisseur;
                            cout << "Saisissez l'ID du produit : ";
                            cin >> idProduit;
                            cout << "Saisissez la quantite commandee : ";
                            cin >> qteCommandee;
                            cin.ignore();
                            cout << "Saisissez la date de commande (YYYY-MM-DD) : ";
                             getline(cin, dateCommande);

                            BonAchat newBonAchat;
                            newBonAchat.setIdFournisseur(idFournisseur);
                            newBonAchat.setIdProduit(idProduit);
                            newBonAchat.setQteCommandee(qteCommandee);
                            newBonAchat.setDateCommande(dateCommande);
                            newBonAchat.create(conn);
                            break;
                         }
                        case 2: {
                             int idFournisseur, idProduit;
                             cout << "Saisissez l'ID du fournisseur : ";
                              cin >> idFournisseur;
                               cout << "Saisissez l'ID du produit : ";
                              cin >> idProduit;
                              cin.ignore();

                             BonAchat bonAchat;
                            if(bonAchat.read(conn, idFournisseur, idProduit)) {
                                 cout << "Bon d'achat trouve : " << endl;
                                 bonAchat.afficherBon();
                             } else {
                                  cout << "Bon d'achat non trouve." << endl;
                             }
                             break;
                        }
                        case 3: {
                             int idFournisseur, idProduit, qteCommandee;
                            string dateCommande;

                             cout << "Saisissez l'ID du fournisseur : ";
                            cin >> idFournisseur;
                           cout << "Saisissez l'ID du produit : ";
                             cin >> idProduit;
                             cout << "Saisissez la nouvelle quantite commandee : ";
                            cin >> qteCommandee;
                             cin.ignore();
                            cout << "Saisissez la nouvelle date de commande (YYYY-MM-DD) : ";
                           getline(cin, dateCommande);
                             BonAchat bonAchatToModify;
                           if(bonAchatToModify.read(conn,idFournisseur,idProduit)){
                              bonAchatToModify.setQteCommandee(qteCommandee);
                             bonAchatToModify.setDateCommande(dateCommande);
                            bonAchatToModify.update(conn);
                                 cout << "Bon d'achat mis a jour avec succes." << endl;
                           } else {
                                  cout << "Bon d'achat non trouve." << endl;
                              }
                             break;
                        }
                        case 4: {
                            int idFournisseur, idProduit;
                            cout << "Saisissez l'ID du fournisseur : ";
                           cin >> idFournisseur;
                            cout << "Saisissez l'ID du produit : ";
                            cin >> idProduit;
                             cin.ignore();
                            BonAchat toDelete;
                            toDelete.setIdFournisseur(idFournisseur);
    						toDelete.setIdProduit(idProduit);
  							 if (!toDelete.deleteRecord(conn)) {
    						cout << "Aucune action n'a ete effectuee." << endl;
   						 }
                            break;
                      }
                         case 5: {
                            BonAchat bonAchat;
                            bonAchat.afficherTousBons(conn);
                             break;
                           }
                        case 0: {
                            break;
                        }
                        default: {
                            cout << "Choix invalide. Veuillez reessayer." << endl;
                            break;
                        }
                    }
                } while (choixBonAchat != 0);
                break;
            }
             case 8: { 
                int choixCommande;
                do {
                    cout << "\n--- Menu Gestion des Commandes ---" << endl;
                    cout << "1: Creer une commande" << endl;
                    cout << "2: Lire une commande par ID" << endl;
                    cout << "3: Mettre a jour une commande" << endl;
                    cout << "4: Supprimer une commande" << endl;
                    cout << "5: Afficher toutes les commandes" << endl;
                    cout << "0: Retour au menu principal" << endl;
                    cout << "Choisissez une option : ";
                    cin >> choixCommande;
                    cin.ignore();

                    switch (choixCommande) {
                        case 1: { 
                            int idClient;
                            string dateCommande, statut;

                            cout << "Saisissez l'ID du client : ";
                            cin >> idClient;
                            cin.ignore();
                            cout << "Saisissez la date de commande (YYYY-MM-DD) : ";
                            getline(cin, dateCommande);
                            cout << "Saisissez le statut de la commande : ";
                            getline(cin, statut);

                            Commande newCommande;
                            newCommande.setIdClient(idClient);
                            newCommande.setDateCommande(dateCommande);
                            newCommande.setStatut(statut);
                            newCommande.create(conn);
                            break;
                        }
                        case 2: { 
                            int idCommande;
                            cout << "Saisissez l'ID de la commande : ";
                            cin >> idCommande;
                            cin.ignore();

                            Commande commande;
                            if (commande.read(conn, idCommande)) {
                                cout << "Commande trouvee : " << endl;
                                commande.afficherCommande();
                            } else {
                                cout << "Commande non trouvee." << endl;
                            }
                            break;
                        }
                        case 3: { 
                            int idCommande, idClient;
                            string dateCommande, statut;

                            cout << "Saisissez l'ID de la commande a modifier : ";
                            cin >> idCommande;
                            cin.ignore();
                            Commande commandeToModify;
                            if (commandeToModify.read(conn, idCommande)) {
                                cout << "Saisissez le nouvel ID du client : ";
                                cin >> idClient;
                                cin.ignore();
                                cout << "Saisissez la nouvelle date de commande (YYYY-MM-DD) : ";
                                getline(cin, dateCommande);
                                cout << "Saisissez le nouveau statut de la commande : ";
                                getline(cin, statut);

                                commandeToModify.setIdClient(idClient);
                                commandeToModify.setDateCommande(dateCommande);
                                commandeToModify.setStatut(statut);
                                commandeToModify.update(conn);
                                cout << "Commande mise a jour avec succes." << endl;
                            } else {
                                cout << "Commande non trouvee." << endl;
                            }
                            break;
                        }
                        case 4: { 
                            int idCommande;
                            cout << "Saisissez l'ID de la commande a supprimer : ";
                            cin >> idCommande;
                            cin.ignore();

                            Commande toDelete;
                            toDelete.setId(idCommande);
                            if (!toDelete.deleteRecord(conn)) {
                                cout << "Aucune action n'a ete effectuee." << endl;
                            }
                            break;
                        }
                        case 5: { 
                            Commande commande;
                            commande.afficherToutesCommandes(conn);
                            break;
                        }
                        case 0: { 
                            break;
                        }
                        default: {
                            cout << "Choix invalide. Veuillez reessayer." << endl;
                            break;
                        }
                    }
                } while (choixCommande != 0);
                break;
            }
                case 9: { 
                 int choixLigneCommande;
                do {
                    cout << "\n--- Menu Gestion des Lignes de Commande ---" << endl;
                     cout << "1: Creer une ligne de commande" << endl;
                    cout << "2: Lire une ligne de commande par ID Produit et ID Commande" << endl;
                    cout << "3: Mettre a jour une ligne de commande" << endl;
                    cout << "4: Supprimer une ligne de commande" << endl;
                    cout << "5: Afficher toutes les lignes de commande" << endl;
                    cout << "0: Retour au menu principal" << endl;
                   cout << "Choisissez une option : ";
                    cin >> choixLigneCommande;
                  cin.ignore();

                    switch (choixLigneCommande) {
                      case 1:{
                             int idProduit, idCommande, qteCommandee;
                              cout << "Saisissez l'ID du produit : ";
                             cin >> idProduit;
                            cout << "Saisissez l'ID de la commande : ";
                            cin >> idCommande;
                           cout << "Saisissez la quantite commandee : ";
                            cin >> qteCommandee;
                           cin.ignore();
                           LigneCommande newLigneCommande;
                            newLigneCommande.setIdProduit(idProduit);
                           newLigneCommande.setIdCommande(idCommande);
                           newLigneCommande.setQteCommandee(qteCommandee);
                           newLigneCommande.create(conn);
                           break;
                      }
                     case 2: {
                            int idProduit, idCommande;
                           cout << "Saisissez l'ID du produit : ";
                          cin >> idProduit;
                           cout << "Saisissez l'ID de la commande : ";
                            cin >> idCommande;
                            cin.ignore();
                          LigneCommande ligneCommande1;
                         if (ligneCommande1.read(conn,idProduit,idCommande)) {
                                cout << "Ligne de commande trouvee : " << endl;
                                ligneCommande1.afficherLigneCommande();
                            }
                          else {
                              cout << "Ligne de commande non trouvee." << endl;
                            }
                            break;
                         }
                       case 3: {
                           int idProduit, idCommande, qteCommandee;
                            cout << "Saisissez l'ID du produit : ";
                           cin >> idProduit;
                           cout << "Saisissez l'ID de la commande : ";
                             cin >> idCommande;
                          cout << "Saisissez la nouvelle quantite commandee : ";
                           cin >> qteCommandee;
                            cin.ignore();

                          LigneCommande ligneCommandeToModify;
                           if (ligneCommandeToModify.read(conn,idProduit,idCommande)) {
                                 ligneCommandeToModify.setQteCommandee(qteCommandee);
                                 ligneCommandeToModify.update(conn);
                                   cout << "Ligne de commande mise a jour avec succes." << endl;
                          }else {
                                 cout << "Ligne de commande non trouvee." << endl;
                             }
                            break;
                       }
                   case 4:{
                        int idProduit, idCommande;
                        cout << "Saisissez l'ID du produit : ";
                        cin >> idProduit;
                         cout << "Saisissez l'ID de la commande : ";
                         cin >> idCommande;
                         cin.ignore();
                       LigneCommande toDelete;
                        if(toDelete.read(conn, idProduit, idCommande))
                             toDelete.deleteRecord(conn);
                        else {
                             cout << "Ligne de commande non trouvee." << endl;
                            }
                          break;
                        }
                    case 5:{
                          LigneCommande ligneCommande;
                         ligneCommande.afficherToutesLignesCommandes(conn);
                         break;
                      }
                    case 0: {
                            break;
                        }
                        default: {
                            cout << "Choix invalide. Veuillez reessayer." << endl;
                            break;
                        }
                  }
                } while (choixLigneCommande != 0);
                break;
            }
            case 0: {
                cout << "Au revoir !" << endl;
                break;
            }
            default: {
                cout << "Choix invalide. Veuillez reessayer." << endl;
                break;
            }
        }
    } while (choixPrincipal != 0);

    return 0;
}
