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
		auto ajouter = false;
		for (auto el : baseFaits ){
			if(tf == el){
				ajouter = true;
			}
		}
		if (!ajouter){
			baseFaits.push_back(tf);
		}
	}

	void SystemeExpert::chargerSE(std::ifstream & EntreeFichier){
		if(EntreeFichier){
			string ligne;
			string pre = "!>";
			int nbl = 0;
			bool test = false;
			while(getline(EntreeFichier, ligne)){
				++nbl;
				if (test){
					cout << "Ligne" << nbl << " : " << ligne << endl;
					test = false;
				}
				if(ligne.find(pre) != string::npos){
					cout << "ligne" << nbl << " : " << ligne << endl;
					test = true;
				}
			}
		}

	}

	void SystemeExpert::sauvegarderSE(std::ofstream & SortieFichier) const{

	}

	void SystemeExpert::chainageAvant(ListeCirculaire<Regle> & er){

	}

	int SystemeExpert::trouverNbLigne(std::ifstream & EntreeFichier){
		if(EntreeFichier){
			std::string ligne;
			auto nbl = 0;
			while (std::getline(EntreeFichier, ligne)){
				nbl++;
			}
			return nbl;
		}
	}
}

