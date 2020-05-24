#ifndef _COMP_H
#define _COMP_H
#include "DBestiole.h"
#include "Milieu.h"
#include <iostream>
#include <vector>

#define COMP_MULTIPLE -1
#define COMP_PEUREUSE 0
#define COMP_KAMIKAZE 1
#define COMP_PREVOYANTE 2
#define COMP_GREGAIRE 3

struct Interpreter;
/**Paramètres pour construire un comportement*/
struct ComportParams:BParams
{
   /*-1 Pour Multiple, 0 pour Peureuse, 1 pour Kamikaze, 2 pour Prevoyante, 3 pour Grégaire*/
   int Comportement;
   /**Ajouter ces paramètres à un dictionnaire de paramètres*/
   virtual void Add(Param_Dict& pd) override;
   /**Copier ces paramètres*/
   virtual BParams* cppm() const override;
};
/**Interface définissant les comportements*/
class IComportement{
friend class Interpreter;
protected:
    /*Vitesse de changement de comportement pour le mutiple*/
    static int MULTIPLE_CHANGE_RATE;
public:
    /**Constructeur*/
    IComportement();
    /**Destructeur*/
    virtual ~IComportement();
    /**Décider d'une action à entreprendre, basée sur ce comportement*/
    virtual void operator()(Milieu& monMilieu, DBestiole* coucheExterne)=0;
    /**Annonce si ce comportement est multiple (pour la gestion de ce comportement avec une instance unique pour chaque bestiole)*/
    virtual bool isMultiple() const;
};
/**Comportement par défaut --stupide =aller en ligne droite*/
class Dumb: public IComportement{
public:
    /**Constructeur*/
    Dumb();
    /**Destructeur*/
    virtual ~Dumb();
    /**Entreprendre une action*/
    virtual void operator()(Milieu& monMilieu, DBestiole* coucheExterne) override;
};
/**Multiple: comportement variable*/
class Multiple: public IComportement{
private:
    /*Le comportement actuel*/
    IComportement* ComportementDuMultiple;
public:
    /**Constructeur*/
    Multiple();
    /**Destructeur*/
    virtual ~Multiple();
    /**Entreprendre une action*/
    virtual void operator()(Milieu& monMilieu, DBestiole* coucheExterne) override;
    /**Ce comportement est Multiple*/
    virtual bool isMultiple() const override;
};
/**Peureuse: fuir les groupes*/
class Peureuse:public IComportement{
public:
    /**Constructeur*/
    Peureuse();
    /**Destructeur*/
    virtual ~Peureuse();
    /**Entreprendre une action*/
    virtual void operator()(Milieu& monMilieu, DBestiole* coucheExterne) override;
};
/**Prevoyante: éviter les collisions*/
class Prevoyante:public IComportement{
public:
    /**Constructeur*/
    Prevoyante();
    /**Destructeur*/
    virtual ~Prevoyante();
    /**Entreprendre une action*/
    virtual void operator()(Milieu& monMilieu, DBestiole* coucheExterne) override;
};
/**Kamikaze: rechercher les collisions*/
class Kamikaze:public IComportement{
public:
    /**Constructeur*/
    Kamikaze();
    /**Destructeur*/
    virtual ~Kamikaze();
    /**Entreprendre une action*/
    virtual void operator()(Milieu& monMilieu, DBestiole* coucheExterne) override;
};
/**Gregaire: suivre le groupe*/
class Gregaire:public IComportement{
public:
    Gregaire();
    /**Constructeur*/
    virtual ~Gregaire();
    /**Destructeur*/
    virtual void operator()(Milieu& monMilieu, DBestiole* coucheExterne) override;
    /**Entreprendre une action*/
};
#endif