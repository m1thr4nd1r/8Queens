/* 
 * File:   Population.cpp
 * Author: M1thr4nd1r
 * 
 * Created on 24 de Fevereiro de 2013, 17:32
 */

#include "Population.h"

Population::Population() {
    for (int i = 0; i < Population::size; i++)
    {
        this->pop[i] = NULL;
        this->fit_percent[i] = 0;
    }
    this->fit_goal = (Node::b_size * (Node::b_size - 1)) / 2;
    this->fit_total = 0;
}

int Population::calculaFitness(Node* individual)
{
    int sum = 0;
    for (int i = 0; i < Node::b_size - 1; i++)
        for (int j = i+1; j < Node::b_size; j++)
        {
            int dist = i - j;
            if (!(
                    (individual->board[i] == individual->board[j]) || // Mesma Horizontal
                    (individual->board[i] == individual->board[j] + dist) || // Mesma Diagonal (Superior)
                    (individual->board[i] == individual->board[j] - dist) // Mesma Diagonal (Inferior)
                 ))
                    sum++;
        }
    return sum;
}

void Population::start()
{
    for (int i = 0; i < Population::size; i++)
    {
        this->pop[i] = new Node();
        this->pop[i]->fitness = this->calculaFitness(pop[i]);
        this->fit_total += this->pop[i]->fitness;
    }
    for (int i = 0; i < Population::size; i++)
        this->fit_percent[i] = round (((float) (this->pop[i]->fitness * 100)) / this->fit_total);
}

void Population::update()
{
    for (int i = 0; i < Population::size; i++)
    {
        this->pop[i]->fitness = this->calculaFitness(pop[i]);
        this->fit_total += this->pop[i]->fitness;
    }
    for (int i = 0; i < Population::size; i++)
        this->fit_percent[i] = round (((float) (this->pop[i]->fitness * 100)) / this->fit_total);
}