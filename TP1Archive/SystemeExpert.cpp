/**
 * \file SystemeExpert.cpp
 * \brief Ce fichier contient une implantation des méthodes de la classe SystemeExpert
 * \author ?
 * \version 0.5
 * \date juin 2017
 *
 */

#include "SystemeExpert.h"
#include <sstream>
#include <fstream>
#include <iostream>

using namespace std;
/**
 * \namespace tp1
 * \brief Namespace du tp1 contenant la classe ListeCirculaire.
 */
namespace tp1{

/**
	 *  \brief Constructeur par défaut
	 *
	 *  \post Une instance de la classe SystemeExpert est initialisée
	 */
	SystemeExpert::SystemeExpert(){

	}

	SystemeExpert::~SystemeExpert(){

	}
	/**
	 *  \brief Constructeur de copie.
	 *
	 * \pre Il faut qu'il y ait suffisamment de mémoire
	 * \post La liste passée en paramètre est copiée
	 * \param[in] r La copie de systemeExpert
	 * \exception bad_alloc s'il n'y a pas assez de mémoire
	 */
	SystemeExpert::SystemeExpert(const SystemeExpert & se){
		baseRegles = se.baseRegles;
		baseFaits = se.baseFaits;
	}
	/**
	 * \brief Surcharge de l'opérateur =
	 *
	 * \pre Il y a assez de mémoire pour l'opération
	 * \post La liste passée en paramètre est copiée
	 * \param[in] r la copie de règle
	 * \exception bad_alloc si la précondition n'est pas respectée
	 */
	SystemeExpert & SystemeExpert::operator = (const SystemeExpert & se){
		if (this == &se){
			return *this;
		}
	}
	/**
	 *  \brief Ajouter une nouvelle regle dans le SE
	 *
	 * \pre La position d'ajout, pos, est comprise entre 1 et |L|+1
	 * \post La liste comprend un élément de plus
	 * \param[in] tr la règle à ajouter
	 * \exception bad_alloc si pas assez de mémoire
	 */
	void SystemeExpert::ajouterRegleSE(const Regle & tr){
		if (!baseRegles.appartient(tr)){
			baseRegles.ajouter(tr, baseRegles.taille()+1);
		}
	}
	/**
	 *  \brief Ajouter un nouveau fait dans le SE
	 *
	 * \pre La position d'ajout, pos, est comprise entre 1 et |L|+1
	 * \post La liste comprend un élément de plus
	 * \param[in] tf le fait à ajouter
	 * \exception bad_alloc si pas assez de mémoire
	 */
	void SystemeExpert::ajouterFaitSE(const TypeFait & tf){
//		auto ajouter = false;
//		for (auto el : baseFaits ){
//			if(tf == el){
//				ajouter = true;
//			}
//		}
//		if (!ajouter){
//			baseFaits.push_back(tf);
//		}
		getBaseFaits().push_back(tf);
	}

	void SystemeExpert::chargerSE(std::ifstream & EntreeFichier){
		if(EntreeFichier){
			string ligne;
			string con = "!>";
			string pre = "!%";
			string fait = "!!";
			string action = pre;
			string prefixRegle = "re";
			int nbr = 1;
			while(getline(EntreeFichier, ligne)){
				if (ligne != pre && ligne != con && ligne != fait){
					if (action == pre){
						string nomRegle = nommerRegle(nbr, prefixRegle);
						Regle * a = new Regle;
						nbr++;
					}else if (action == con){
					}else if (action == fait){
						ajouterFaitSE(ligne);
					}
				} else {
					if (ligne == pre){
						action = pre;
					}else if (ligne == con){
						action = con;
					}else if (ligne == fait){
						action == fait;
					}
				}
			}
		}

	}

	void SystemeExpert::sauvegarderSE(std::ofstream & SortieFichier) const{

	}

	void SystemeExpert::chainageAvant(ListeCirculaire<Regle> & er){

	}

	string SystemeExpert::nommerRegle(int numero, string nom){
		string num = to_string(numero);
		return nom+num;
	}
}

