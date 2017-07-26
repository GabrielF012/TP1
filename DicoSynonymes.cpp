/**
* \file DicoSynonymes.cpp
* \brief Le code des opérateurs du DicoSynonymes.
* \author ?
* \version 0.5
* \date ?
*
* Travail pratique numéro 3.
*
*/

#include "DicoSynonymes.h"
#include "AssertionException.h"

/**
 * \namespace tp3
 * \brief Namespace du tp3 contenant la classe DicoSynonymes.
 */
namespace TP3
{

	// Méthode fournie que vous pouvez modifier si vous voulez

	/**
	 *  \brief chargerDicoSynonyme.
	 *
	 * \pre Fichier non ouvert
	 * \post Charge le dictionnaire de synonymes
	 * \param[in] fichier le fichier a charger
	 */
	void DicoSynonymes::chargerDicoSynonyme(std::ifstream& fichier)
	{
		ASSERTION(fichier.is_open());

		std::string ligne;
		std::string buffer;
		std::string radical;
		int cat = 1;

		while (std::getline(fichier, ligne)) // tant qu'on peut lire dans le fichier
		{

			if (ligne == "$")
			{
				cat = 3;
				std::getline(fichier, ligne);
			}
			if (cat == 1)
			{
				radical = ligne;
				ajouterRadical(radical);
				cat = 2;
			}
			else if (cat == 2)
			{
				std::stringstream ss(ligne);
				while (ss >> buffer)
					ajouterFlexion(radical, buffer);
				cat = 1;
			}
			else
			{
				std::stringstream ss(ligne);
				ss >> radical;
				ss >> buffer;
				int position = -1;
				ajouterSynonyme(radical, buffer, position);
				while (ss >> buffer)
					ajouterSynonyme(radical, buffer, position);
			}
		}
	}

	//Mettez l'implantation des autres méthodes demandées ici.
	/**
	 *  \brief Constructeur par défaut	 *
	 *  \post Une instance de la classe DicoSynonymes est initialisée
	 */
	DicoSynonymes::DicoSynonymes():
				nbRadicaux(0), racine(nullptr), groupesSynonymes(){

	}

	/**
	 *  \brief Constructeur à partir d'un fichier
	 *  \post Une instance de la classe DicoSynonymes est initialisée.
	 */
	DicoSynonymes::DicoSynonymes(std::ifstream& fichier):
						nbRadicaux(0), racine(nullptr), groupesSynonymes() {
		chargerDicoSynonyme(fichier);
	}

	/**
	 *  \brief Destructeur
	 *  \post L'instance de DicoSynonymes est détruite.
	 */
	DicoSynonymes::~DicoSynonymes() {
		_auxDetruire(racine);
	}

	/**
	 *  \brief Ajouter un radical.
	 *
	 * \pre Le radical ne doit pas déjà exister
	 * \post Un nouveau radical est créé
	 * \param[in] motRadical le string à ajouter
	 */
	void DicoSynonymes::ajouterRadical(const std::string& motRadical) {
		ASSERTION(!appartient(motRadical));
		_ajouterRadical(racine, motRadical);
	}

	/**
	 *  \brief Ajouter une flexion.
	 *
	 * \pre Le radical existe pas ou flexion déjà existant
	 * \post Le motFlexion est ajouter au motRadical
	 * \param[in] motFlexion le string à ajouter au motRadical
	 */
	void DicoSynonymes::ajouterFlexion(const std::string& motRadical,
			const std::string& motFlexion) {
	}

	/**
	 *  \brief Ajouter un synonyme.
	 *
	 * \pre Le motSynonyme deja existant
	 * \pre numGroupe incorrecte
	 * \pre motRadical existe pas
	 * \post Le motSynonyme est ajouter au groupe de synonyme du motRadical
	 * \param[in] motSynonyme le string à ajouter à motRadical
	 * \param[in] motRadical le string auquel on va ajouter un synonyme
	 * \param[in] numGroupe int représente le groupe de synonyme à ajouter le synonyme
	 */
	void DicoSynonymes::ajouterSynonyme(const std::string& motRadical,
			const std::string& motSynonyme, int& numGroupe) {
	}

	/**
	 *  \brief Supprimer un radical.
	 *
	 * \pre Arbre vide
	 * \pre motRadical existe pas
	 * \post Le motRadical est supprimé
	 * \param[in] motRadical le string à supprimer
	 */
	void DicoSynonymes::supprimerRadical(const std::string& motRadical) {
		ASSERTION(!estVide());
		ASSERTION(appartient(motRadical));
		_enleverRadical(racine, motRadical);
	}

	/**
	 *  \brief Supprimer une flexion.
	 *
	 * \pre Arbre vide
	 * \pre motRadical existe pas
	 * \post motFlexion supprimer de la liste de flexions du motRadical.
	 * \param[in] motFlexion le string à supprimer à la liste de flexions du motRadical
	 * \param[in] motRadical le string utiliser pour enlever la flexion de sa liste
	 */
	void DicoSynonymes::supprimerFlexion(const std::string& motRadical,
			const std::string& motFlexion) {
	}

	/**
	 *  \brief Supprimer un Synonyme.
	 *
	 * \pre motRadical existe pas
	 * \pre motSynonyme existe pas
	 * \pre numGroupe existe pas
	 * \post Retirer motSynonyme faisant partie du numéro de groupe numGroupe du motRadical.
	 * \param[in] motRadical le string utiliser pour enlever le synonyme de son groupe
	 * \param[in] motSynonyme le string à retirer du groupe de synonyme du motRadical
	 * \param[in] numGroupe int representant le groupe dans lequel se trouve le motSynonyme
	 */
	void DicoSynonymes::supprimerSynonyme(const std::string& motRadical,
			const std::string& motSynonyme, int& numGroupe) {
	}

	/**
	 *  \brief Vérifie si dictionnaire vide.
	 *
	 * \param[out] bool si vide true sinon false
	 */
	bool DicoSynonymes::estVide() const {
		return nbRadicaux == 0;
	}

	/**
	 *  \brief Vérifie nombre de radicaux.
	 *
	 * \param[out] int nombre de radicaux
	 */
	int DicoSynonymes::nombreRadicaux() const {
		return nbRadicaux;
	}

	/**
	 *  \brief Recherche un radical.
	 *
	 * \pre arbre vide
	 * \pre si la flexion n'est pas dans la liste de flexions du radical
	 * \post Retourne le mot rechercher.
	 * \param[in] mot le string dans la liste des flexions d'un radical
	 * \param[out] string le radical du mot entré en paramètre
	 */
	std::string DicoSynonymes::rechercherRadical(const std::string& mot) const {
	}

	/**
	 *  \brief Similiture entre deux mots.
	 *
	 * \post Retourne un réel entre 0 et 1 qui représente le degré de similitude entre mot1 et mot2 où
	 * 0 représente deux mots complétement différents et 1 deux mots identiques..
	 * \param[in] mot1 le premier string a comparer
	 * \param[in] mot2 le deuxieme string a comparer
	 * \param[out] float degré de similitude entre 2 mots
	 */
	float DicoSynonymes::similitude(const std::string& mot1,
			const std::string& mot2) const {
	}

	/**
	 *  \brief getNombreSens.
	 *
	 * \post Donne le nombre de groupe de synonyme d'un radical
	 * \param[in] radical le string dont on veux le nombre de groupe de synonyme
	 * \param[out] int Le nombre de cases de appSynonymes pour le radical
	 */
	int DicoSynonymes::getNombreSens(std::string radical) const {
	}

	/**
	 *  \brief getSens.
	 *
	 * \post Donne le premier synonyme du groupe de synonyme du radical
	 * \param[in] radical le string dont trouver le synonyme
	 * \param[in] position savoir quel groupe de synonyme chercher
	 * \param[out] string le premier synonyme du groupe du radical
	 */
	std::string DicoSynonymes::getSens(std::string radical, int position) const {
	}

	/**
	 *  \brief getSynonyme.
	 *
	 * \post Donne tous les synonymes d'un radical pour un groupe en particulier qui est identifé par position.
	 * \param[in] radical le string on doit trouver les synonymes
	 * \param[in] position savoir quel groupe de synonyme chercher
	 * \param[out] vector un vecteur contenant tous les synonymes
	 */
	std::vector<std::string> DicoSynonymes::getSynonymes(std::string radical,
			int position) const {
	}

	/**
	 *  \brief getFlexion.
	 *
	 * \post Donne toutes les flexions d'un radical.
	 * \param[in] radical le string dont on veux trouver les flexions
	 * \param[out] vector Un vecteur est retourné avec toutes les flexions
	 */
	std::vector<std::string> DicoSynonymes::getFlexions(std::string radical) const {
	}

	/**
	 *  \brief _ajouterRadical.
	 *
	 * \post fonction recursive qui ajoute un radical.
	 * \param[in] noeud pointeur du noeud
	 * \param[in] motRadical string a ajouter dans le noeud
	 */
	void DicoSynonymes::_ajouterRadical(NoeudDicoSynonymes *& noeud,
			const std::string& motRadical) {
		if (noeud == nullptr){
			noeud = new NoeudDicoSynonymes(motRadical);
			nbRadicaux++;
			return;
		}else if (noeud->gauche->radical < motRadical){
			_ajouterRadical(noeud->gauche, motRadical);
		}else {
			_ajouterRadical(noeud->droit, motRadical);
		}

		_miseAJourHauteurNoeud(noeud);
		_balancerUnNoeud(noeud);

	}

	/**
	 *  \brief _miseAJourHauteurNoeud.
	 *
	 * \post fonction recursive qui permet de mettre a jour la hauteur du noeud
	 * \param[in] noeud le noeud don on veux mettre à jour la hauteur
	 */
	void DicoSynonymes::_miseAJourHauteurNoeud(NoeudDicoSynonymes *& noeud){
		if(noeud != nullptr){
			noeud->hauteur = 1 + std::max(_hauteur(noeud->gauche), _hauteur(noeud->droit));
		}
	}

	/**
	 *  \brief _hauteur.
	 *
	 * \post Donne la hauteur du noeud
	 * \param[in] noeud le noeud dont on veux savoir la hauteur
	 * \param[out] int la hauteur du noeud
	 */
	int DicoSynonymes::_hauteur(NoeudDicoSynonymes *& noeud) const{
			if (noeud == nullptr){
				return -1;
			}
			return noeud->hauteur;
		}

	/**
	 *  \brief _balancerUnNoeud.
	 *
	 * \post fonction recursive permettant de balancer un noeud.
	 * \param[in] noeud à vérifier s'il debalance l'arbre
	 */
	void DicoSynonymes::_balancerUnNoeud(NoeudDicoSynonymes *& noeud){
		if (noeud == nullptr){
			return;
		}
		if (_debalancementAGauche(noeud)){
			if (_sousArbrePencheADroite(noeud->gauche)){
				_zigZagGauche(noeud);
			} else {
				_zigZigGauche(noeud);
			}
		}else if (_debalancementADroite(noeud)){
			if (_sousArbrePencheAGauche(noeud->droit)){
				_zigZagDroite(noeud);
			} else {
				_zigZigDroite(noeud);
			}
		}
	}

	/**
	 *  \brief _debalancementGauche.
	 *
	 * \post fonction recursive qui verifie s'il y a un debalancement dans le sous arbre de gauche
	 * \param[in] noeud le noeud a partir duquel on verifie s'il y a un debalancement a gauche
	 * \param[out] bool retournant si debalancer ou non
	 */
	bool DicoSynonymes::_debalancementAGauche(NoeudDicoSynonymes*& noeud) const {
		if (noeud == nullptr){
			return false;
		}
		return _hauteur(noeud->gauche) - _hauteur(noeud->droit) >= 2;
	}

	/**
	 *  \brief _debalancementDroit.
	 *
	 * \post fonction recursive qui verifie s'il y a un debalancement dans le sous arbre de droit
	 * \param[in] noeud le noeud a partir duquel on verifie s'il y a un debalancement a droit
	 * \param[out] bool retournant si debalancer ou non
	 */
	bool DicoSynonymes::_debalancementADroite(NoeudDicoSynonymes*& noeud) const {
		if (noeud == nullptr){
				return false;
		}
		return _hauteur(noeud->droit) - _hauteur(noeud->gauche) >= 2;
	}

	/**
	 *  \brief _sousArbrePencheAGauche.
	 *
	 * \post fonction recursive qui verifie si le sous-arbre penche a gauche
	 * \param[in] noeud le noeud à partir duquel on fait la verification
	 * \param[out] bool à savoir si le sous arbre penche a gauche ou non
	 */
	bool DicoSynonymes::_sousArbrePencheAGauche(NoeudDicoSynonymes*& noeud) const {
		if(noeud == nullptr){
			return false;
		}
		return _hauteur(noeud->gauche) > _hauteur(noeud->droit);
	}

	/**
	 *  \brief _sousArbrePencheADroite.
	 *
	 * \post fonction recursive qui verifie si le sous-arbre penche a droite
	 * \param[in] noeud le noeud à partir duquel on fait la verification
	 * \param[out] bool à savoir si le sous arbre penche a droit ou non
	 */
	bool DicoSynonymes::_sousArbrePencheADroite(NoeudDicoSynonymes*& noeud) const {
		if(noeud == nullptr){
			return false;
		}
		return _hauteur(noeud->droit) > _hauteur(noeud->gauche);
	}

	/**
	 *  \brief _zigZigGauche.
	 *
	 * \post Fait une rotation vers la droit des noeuds critique et sous-critique
	 * \param[in] noeudCritique noeud ne respectant pas l'équilibre de l'arbre
	 */
	void DicoSynonymes::_zigZigGauche(NoeudDicoSynonymes*& noeudCritique) {
		NoeudDicoSynonymes * noeudSousCritique = noeudCritique->gauche;
		noeudCritique->gauche = noeudSousCritique->droit;
		noeudSousCritique->droit = noeudCritique;

		_miseAJourHauteurNoeud(noeudCritique);
		_miseAJourHauteurNoeud(noeudSousCritique);

		noeudCritique = noeudSousCritique;
	}

	/**
	 *  \brief _zigZigDroit.
	 *
	 * \post Fait une rotation vers la gauche des noeuds critique et sous-critique
	 * \param[in] noeudCritique noeud ne respectant pas l'équilibre de l'arbre
	 */
	void DicoSynonymes::_zigZigDroite(NoeudDicoSynonymes*& noeudCritique) {
		NoeudDicoSynonymes * noeudSousCritique = noeudCritique->droit;
		noeudCritique->droit = noeudSousCritique->gauche;
		noeudSousCritique->gauche = noeudCritique;

		_miseAJourHauteurNoeud(noeudCritique);
		_miseAJourHauteurNoeud(noeudSousCritique);

		noeudCritique = noeudSousCritique;
	}

	/**
	 *  \brief _zigZagGauche.
	 *
	 * \post Fait deux rotation vers la gauche puis la droit du noeud
	 * \param[in] noeud noeud ne respectant pas l'équilibre de l'arbre
	 */
	void DicoSynonymes::_zigZagGauche(NoeudDicoSynonymes*& noeud) {
		_zigZigDroite(noeud->droit);
		_zigZigGauche(noeud);
	}

	/**
	 *  \brief _zigZagDroit.
	 *
	 * \post Fait deux rotation vers la droite puis la gauche du noeud
	 * \param[in] noeud noeud ne respectant pas l'équilibre de l'arbre
	 */
	void DicoSynonymes::_zigZagDroite(NoeudDicoSynonymes*& noeud) {
		_zigZigGauche(noeud->droit);
		_zigZigDroite(noeud);
	}

	/**
	 *  \brief _enleverRadical.
	 *
	 * \post fonction recursive permettant d'enlever unnoeud
	 * \param[in] noeud racine de l'arbre
	 * \param[in] motRadical string à enlever
	 */
	void DicoSynonymes::_enleverRadical(NoeudDicoSynonymes *& noeud,
				const std::string& motRadical) {
		if (noeud == nullptr){
			throw std::logic_error("Le noeud est inexistant");
		}

		if (noeud->radical > motRadical){
			_enleverRadical(noeud->gauche, motRadical);
		}else if (noeud->radical < motRadical){
			_enleverRadical(noeud->droit, motRadical);
		}else{
			if (_hauteur(noeud) == 0){
				delete noeud;
				noeud = nullptr;
				nbRadicaux--;
			}else if (!_aDeuxfils(noeud)){
				if (noeud->gauche != nullptr){
					std::swap(noeud->radical, noeud->gauche->radical);
					_enleverRadical(noeud->gauche, motRadical);
				}else{
					std::swap(noeud->radical, noeud->droit->radical);
					_enleverRadical(noeud->droit, motRadical);
				}
			}else{
				NoeudDicoSynonymes * minDroit = _min(noeud->droit);
				std::swap(noeud->radical, minDroit->radical);
				_enleverRadical(noeud->droit, motRadical);
			}
		}

		_miseAJourHauteurNoeud(noeud);
		_balancerUnNoeud(noeud);

		}

	/**
	 *  \brief _aDeuxfils.
	 *
	 * \post verifie si le noeud à deux fils dans l'arbre
	 * \param[in] noeud noeud a savoir s'il possede deux fils
	 * \param[out] bool retourne vrai s'il a deux fils false sinon
	 */
	bool DicoSynonymes::_aDeuxfils(NoeudDicoSynonymes *& noeud) const	{
		if (noeud == nullptr){
			return false;
		}
		return noeud->gauche != nullptr && noeud->droit != nullptr;
	}

	/**
	 *  \brief _min.
	 *
	 * \post Trouve le noeud minimum à partir d'unnoeud
	 * \param[in] noeud noeud duquel nous voulons avoir le noeud minimum
	 * \param[out] pointeur vers le noeud minimum trouvé
	 */
	DicoSynonymes::NoeudDicoSynonymes* DicoSynonymes::_min(NoeudDicoSynonymes * noeud) const {
		if(noeud->gauche == nullptr){
			return noeud;
		}
		return _min(noeud->gauche);

	}

	/**
	 *  \brief _appartient.
	 *
	 * \post Trouve si le noeud appartient à l'arbre
	 * \param[in] motRadical le string dont on veux savoir s'il existe dans l'arbre
	 * \param[out] bool vrai s'il existe false sinon
	 */
	bool DicoSynonymes::appartient(const std::string& motRadical) const {
		return _appartient(racine, motRadical);
	}

	/**
	 *  \brief _appartient.
	 *
	 * \post Fonction recursive permettant de savoir si le noeud existe dans l'arbre
	 * \param[in] noeud racine de l'arbre
	 * \param[in] motRadical string que l'on veut vérifier
	 * \param[out] bool si trouver ou non
	 */
	bool DicoSynonymes::_appartient(NoeudDicoSynonymes* const & noeud,
			const std::string& motRadical) const {
		if (noeud == nullptr){
			return false;
		}else if (noeud->radical == motRadical){
			return true;
		}else if (noeud->radical > motRadical){
			return _appartient(noeud->gauche, motRadical);
		}else{
			return _appartient(noeud->droit, motRadical);
		}
	}

	/**
	 *  \brief _auxDetruiret.
	 *
	 * \post Fonction recursive permettant detruire tous les noeuds dans l'arbre
	 * \param[in] noeud racine de l'arbre
	 */
	void DicoSynonymes::_auxDetruire(NoeudDicoSynonymes*& noeud) {
		if (noeud != nullptr){
			_auxDetruire(noeud->gauche);
			_auxDetruire(noeud->droit);
			delete noeud;
			noeud = nullptr;
		}
	}




} //Fin du namespace

