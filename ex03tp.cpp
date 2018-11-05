#include <iostream>
#include <string.h>
using namespace std;

struct produit
{
  char code_prod[9], designation[50];
  char um[3];
  double pua_ht, qte;
  short tva;
};

struct element
{
  produit prod;
  element *suivant;
};

extern element *Q = NULL, *p = NULL, *tete = NULL;

void ajouter()
{
  Q = new element();
  cout << "Donner le code du produit: "; cin >> Q -> prod.code_prod;
  cout << "Donner la désignation du produit: "; cin >> Q -> prod.designation;
  cout << "Donner la quantité du produit: "; cin >> Q -> prod.qte;
  cout << "Donner l'unité de mesure pour le produit: "; cin >> Q -> prod.um;
  cout << "Donner le prix du produit: "; cin >> Q -> prod.pua_ht;
  cout << "Donner la tva (21 ou 9): "; cin >> Q -> prod.tva;
  Q -> suivant = NULL;
  if(tete != NULL)
    p -> suivant = Q;
  else
    tete = Q;
  p = Q;
}

void afficher()
{
  p = tete;
  if(tete == NULL)
    cout << "ERREUR 404 Liste not found !!!" << endl;
  else
  {
    while(p != NULL)
    {
      cout << "---------------------------------------" << endl;
      cout << "- Code du produit: " << p -> prod.code_prod << endl;
      cout << "- Désignation du produit: " << p -> prod.designation << endl;
      cout << "- Quantité du produit: " << p -> prod.qte << endl;
      cout << "- Unité de mesure pour le produit: " << Q -> prod.um << endl;
      cout << "- Prix du produit: " << p -> prod.pua_ht << endl;
      cout << "- Tva: " << p -> prod.tva << "%" << endl;
      cout << "--------------------------------------" << endl;
      p = p -> suivant;
    }
  }
}

void afficher_total(int &nb_prod , double &ht, double &tva_t, double &ttc)
{

  p = tete;
  if(tete == NULL)
    cout << "ERREUR 404 Liste not found !!!" << endl;
  else
  {
      while(p != NULL)
      {
        nb_prod ++;
        ht = ht + p -> prod.pua_ht * p -> prod.qte;
        double a = p -> prod.pua_ht * p -> prod.qte;
        tva_t = tva_t + (a * p -> prod.tva)/100;
        p = p -> suivant;
      }
      ttc = ht + tva_t;
      cout << "Le nombre des produits: " << nb_prod << endl;
      cout << "Le HT des produits: " << ht << endl;
      cout << "Le TVA total: " << tva_t << endl;
      cout << "Le prix TTC: " << ttc << endl;
  }

}

void remise(double &ttc)
{
  double montant_p;
  do {
    if(tete == NULL)
    {
      cout << "ERREUR la liste est vide: " << endl;
      break;
    }
    else
    {
      if(ttc == 0)
        cout << "ERREUR le TTC n'est pas calculé encore !!!" << endl;
      else
      {
        cout << "Donner le montant a payé: ";
        cin >> montant_p;
      }
    }
  } while(montant_p < ttc);
  cout << "Remise = " << montant_p - ttc << endl;
}

void supprimer()
{
  char desig[50], pro[50];
  p = tete;
  element *a = NULL;
  if(tete == NULL)
    cout << "ERREUR 404 Liste not found !!!" << endl;
  else
  {
    cout << "Donner la désignation du produit que vous rechercher: ";
    cin >> desig;
    bool trouve = false;
    int compteur;
    while(p != NULL && trouve == false)
    {
      for(int i = 0; i < 50; i++)
      {
        pro[i] = p -> prod.designation[i];
      }
      compteur = 0;
      if(strlen(pro) == strlen(desig))
      {
        for(int i = 0; i < strlen(pro); i++)
        {
          if (pro[i] == desig[i])
            compteur ++;
        }
      }
      if(compteur == strlen(pro))
        trouve = true;
      else
      {
        a = p;
        p = p -> suivant;
      }
    }
    if(trouve == false)
      cout << "Le produit que vous voulez supprimer est introuvable." << endl;
    else
    {
      if(p -> suivant == NULL)
      {
        a -> suivant = NULL;
        if(tete -> suivant == NULL)
        {
          tete = NULL;
          a = NULL;
        }
        free(p);
      }
      else if(p == tete)
      {
        tete = tete -> suivant;
        a = NULL;
        free(p);
      }
      else
      {
        a -> suivant = p -> suivant;
        p -> suivant = NULL;
        free(p);
      }
    }
  }
}

void max_min()
{
  p = tete;
  if(tete == NULL)
    cout << "ERREUR 404 Liste not found !!!" << endl;
  else
  {
    double max = 0;
    double min = p -> prod.pua_ht;
    element *e = NULL;
    while(p != NULL)
    {
      if(max < p -> prod.pua_ht)
        max = p -> prod.pua_ht;
      if(min > p -> prod.pua_ht)
        min = p -> prod.pua_ht;
      p = p -> suivant;
    }
    cout << "Le prix max = " << max << endl;
    cout << "Le prix min = " << min << endl;
  }
}

void vider()
{
  p = tete;
  if(tete == NULL)
    cout << "La liste est vide !!!!!" << endl;
  else
  {
    while(tete != NULL)
    {
      tete = tete -> suivant;
      free(p);
    }
    if(tete == NULL)
      cout << "La liste a été vider !!!!" << endl;
  }
}

void menu()
{
  cout << "----------------------------MENU----------------------------------" << endl;
  cout << "- 1. AJOUTER.                                                    -" << endl;
  cout << "- 2. AFFICHER la liste.                                          -" << endl;
  cout << "- 3. AFFICHER nombre de produits, total HT, total TVA, total TTC.-" << endl;
  cout << "- 4. AFFICHER remise.                                            -" << endl;
  cout << "- 5. SUPPRIMER un produit.                                       -" << endl;
  cout << "- 6. AFFICHER prix max et prix min.                              -" << endl;
  cout << "- 7. VIDER la liste.                                             -" << endl;
  cout << "- 8. ARRET du programme.                                         -" << endl;
  cout << "------------------------------------------------------------------" << endl;
}

int main()
{
  double ht, tva_t, ttc = 0;
  int nb_prod = 0;
  short choix;
  bool contin = true;
  do {
    menu();
    do {
      cout << "Donner votre choix: ";
      cin >> choix;
    } while(choix < 1 || choix > 8);
    switch(choix)
    {
      case 1:
        ajouter();
        system("clear");
        break;
      case 2:
        afficher();
        break;
      case 3:
        afficher_total(nb_prod, ht, tva_t, ttc);
        break;
      case 4:
        remise(ttc);
        break;
      case 5:
        supprimer();
        break;
      case 6:
        max_min();
        break;
      case 7:
        vider();
        break;
      case 8:
        contin = false;
        break;
    }
  } while(contin);

  return 0;
}
