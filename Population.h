/* 
 * File:   Population.h
 * Author: M1thr4nd1r
 *
 * Created on 24 de Fevereiro de 2013, 17:32
 */

#ifndef POPULATION_H
#define	POPULATION_H

#include "Node.h"
#include <cmath>

class Population {
public:
    Population();
    static const int size = 4;
    Node* pop[Population::size];
    int fit_percent[Population::size];
    int fit_goal, fit_total;
    void start();
    int calculaFitness(Node* individual);
    void update();
private:

};

#endif	/* POPULATION_H */

