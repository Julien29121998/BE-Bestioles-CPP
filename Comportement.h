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


struct ComportParams:BParams
{
   int Comportement;
   virtual void Add(Param_Dict& pd) override;
   virtual BParams* cppm() const override;
};

class IComportement{
protected:
    static const int MULTIPLE_CHANGE_RATE;
public:
    IComportement();
    virtual ~IComportement();
    virtual void operator()(Milieu& monMilieu, DBestiole* coucheExterne)=0;
    virtual bool isMultiple() const;
};
class Dumb: public IComportement{
public:
    Dumb();
    virtual ~Dumb();
    virtual void operator()(Milieu& monMilieu, DBestiole* coucheExterne) override;
};
class Multiple: public IComportement{
private:
    IComportement* ComportementDuMultiple;
public:
    Multiple();
    virtual ~Multiple();
    virtual void operator()(Milieu& monMilieu, DBestiole* coucheExterne) override;
    virtual bool isMultiple() const override;
};
class Peureuse:public IComportement{
public:
    Peureuse();
    virtual ~Peureuse();
    virtual void operator()(Milieu& monMilieu, DBestiole* coucheExterne) override;
};
class Prevoyante:public IComportement{
public:
    Prevoyante();
    virtual ~Prevoyante();
    virtual void operator()(Milieu& monMilieu, DBestiole* coucheExterne) override;
};
class Kamikaze:public IComportement{
public:
    Kamikaze();
    virtual ~Kamikaze();
    virtual void operator()(Milieu& monMilieu, DBestiole* coucheExterne) override;
};
class Gregaire:public IComportement{
public:
    Gregaire();
    virtual ~Gregaire();
    virtual void operator()(Milieu& monMilieu, DBestiole* coucheExterne) override;
};
#endif