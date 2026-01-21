#include <iomanip>
#include "timing.h"
#include <ctime>

using namespace TIME;

std::ostream& operator<<(std::ostream& f, const Date& x){ x.afficher(f); return f;} 
std::ostream& operator<<(std::ostream& f, const Duree & d){ d.afficher(f); return f; }
std::ostream& operator<<(std::ostream& f, const Horaire & h){ h.afficher(f); return f; }
std::ostream& operator<<(std::ostream& f, const Periode & p){ p.afficher(f); return f; }


void Date::setDate(unsigned short int j, unsigned short int m, unsigned int a){
	// initialisation de la date, renvoie vrai si la date est valide
	if (a>=0&&a<=3000) annee=a; else throw TimeException("erreur: annee invalide");
	if (m>=1&&m<=12) mois=m; else throw TimeException("erreur: mois invalide");
	switch(m){
	case 1: case 3: case 5: case 7: case 8: case 10: case 12: if (j>=1 && j<=31) jour=j; else throw TimeException("erreur: jour invalide"); break;
	case 4: case 6: case 9: case 11: if (j>=1 && j<=30) jour=j; else throw TimeException("erreur: jour invalide"); break;
	case 2: if (j>=1 && (j<=29 || (j==30 && a%4==0))) jour=j; else throw TimeException("erreur: jour invalide"); break;
	}
}

void Date::afficher(std::ostream& f) const{
	// affiche le date sous le format JJ/MM/AAAA
	f<<std::setfill('0')<<std::setw(2)<<jour<<"/"<<std::setw(2)<<mois<<"/"<<annee<<std::setfill(' ');
}

bool Date::operator==(const Date& d) const{
	if (annee<d.annee) return false;
	if (annee>d.annee) return false;
	if (mois<d.mois) return false;
	if (mois>d.mois) return false;
	if (jour<d.jour) return false;
	if (jour>d.jour) return false;
	return true;
}

bool Date::operator<(const Date& d) const{
	if (annee<d.annee) return true;
	if (annee>d.annee) return false;
	if (mois<d.mois) return true;
	if (mois>d.mois) return false;
	if (jour<d.jour) return true;
	if (jour>d.jour) return false;
	return false;
}

int Date::operator-(const Date& d) const{
	int n=(annee-d.annee)*365+(annee-d.annee)/4;
	n+=int((mois-d.mois)*30.5);
	n+=jour-d.jour;
	return n;
}

Date Date::demain() const{
	Date d=*this;
	d.jour+=1;
	switch(d.mois){
	case 1: case 3: case 5: case 7: case 8: case 10: case 12: if (d.jour==30) { d.jour=1; d.mois++; } break;
	case 4: case 6: case 9: case 11: if (d.jour==31) { d.jour=1; d.mois++; } break;
	case 2: if (d.jour==29 && d.annee%4>0) { d.jour=1; d.mois++; } if (d.jour==30) { d.jour=1; d.mois++; } break;
	}
	if (d.mois==13){ d.annee++; d.mois=1; }
	return d;
}

Date Date::operator+(unsigned int nb_jours) const{
	Date d=*this;
	while(nb_jours>0) { d=d.demain(); nb_jours--; }
	return d;
}

bool Horaire::operator<(const Horaire& h) const{
	if (heure<h.heure) return true;
	if (heure>h.heure) return false;
	if (minute<h.minute) return true;
	if (minute>h.minute) return false;
	return true;
}

Periode::Periode(unsigned int j, unsigned int m, unsigned int a): 
		   nb_jours(j), nb_mois(m), nb_annees(a) {
	if (j>364) throw TimeException("erreur: initialisation periode invalide");
	if (m>11) throw TimeException("erreur: initialisation periode invalide");
}


std::ostream& operator<<(std::ostream& f, const Intervalle& x){ x.afficher(f); return f;}


Intervalle::Intervalle(const Date & d, const Date & f):debut(d),fin(f){
	if (fin<debut) throw TimeException("Erreur dans la creation d'un intervalle: fin<debut");
}

bool Intervalle::operator&&(const Intervalle & v) const {
	if (debut<v.debut){
		if (fin<v.debut) return false; else return true;
	}
	if (v.fin<fin){
		if (v.fin<debut) return false; else return true;
	}
	return true;
}

Intervalle Intervalle::operator+(const Intervalle & i) const {
	Date d=fin.demain();
	if (d==i.debut){
		return Intervalle(debut,i.fin);
	}else throw TimeException("Ne peut pas faire l'union de 2 intervalles (ils ne se touchent pas...");
}

void Intervalle::afficher(std::ostream& f) const {
	f<<"["<<debut<<" ; "<<fin<<"]";
}

std::istream& operator>>(std::istream& flot, TIME::Date& date){
	unsigned int short j,m,a;
	bool ok=true;
	flot>>j;
	if (flot) while (flot.peek()==' ') flot.ignore(); // passe les espaces
	else ok=false;

	if (!flot) ok=false;

	if(flot.peek()=='/') {
		flot.ignore();
		flot>>m;
		if (!flot) ok=false;
	}
	else {
		ok=false;
	}
	if(flot.peek()=='/') {
		flot.ignore();
		flot>>a;
		if (!flot) ok=false;
	}
	else {
		ok=false;
	}

	if (ok) date=Date(j,m,a); else flot.clear(std::ios::failbit);
	return flot;
}

std::istream& operator>>(std::istream& flot, TIME::Duree& duree){
	unsigned int h,m;
	bool ok=true;
	flot>>h;
	if (flot) while (flot.peek()==' ') flot.ignore(); // passe les espaces
	else ok=false;

	if (!flot) ok=false;

	if(flot.peek()=='H') {
		flot.ignore();
		flot>>m;
		if (!flot) ok=false;
	}
	else {
		ok=false;
	}
	if (ok) duree=Duree(h,m); else flot.clear(std::ios::failbit);
	return flot;
}