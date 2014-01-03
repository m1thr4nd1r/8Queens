/* 
 * File:   main.cpp
 * Author: M1thr4nd1r
 *
 * Created on 24 de Fevereiro de 2013, 14:31
 */

#include "Node.h"
#include "Population.h"

using namespace std;

Node* reproduce(Node* x,Node* y)
{
    Node* child = new Node();
    
    int c = rand() % Node::b_size;
    
    for (int i = 0; i < Node::b_size; i++)
        child->board[i] = (i < c+1)? x->board[i] : y->board[i]; 
        
    return child;
}

void tests()
{
    const int p_size = 4;
    
    Node *population[p_size] = {NULL,NULL,NULL,NULL};
    
    population[0]->board[0] = 2;
    population[0]->board[1] = 4;
    population[0]->board[2] = 7;
    population[0]->board[3] = 4;
    population[0]->board[4] = 8;
    population[0]->board[5] = 5;
    population[0]->board[6] = 5;
    population[0]->board[7] = 2;
    
    population[1]->board[0] = 3;
    population[1]->board[1] = 2;
    population[1]->board[2] = 7;
    population[1]->board[3] = 5;
    population[1]->board[4] = 2;
    population[1]->board[5] = 4;
    population[1]->board[6] = 1;
    population[1]->board[7] = 1;
    
    population[2]->board[0] = 2;
    population[2]->board[1] = 4;
    population[2]->board[2] = 4;
    population[2]->board[3] = 1;
    population[2]->board[4] = 5;
    population[2]->board[5] = 1;
    population[2]->board[6] = 2;
    population[2]->board[7] = 4;
    
    population[3]->board[0] = 3;
    population[3]->board[1] = 2;
    population[3]->board[2] = 5;
    population[3]->board[3] = 4;
    population[3]->board[4] = 3;
    population[3]->board[5] = 2;
    population[3]->board[6] = 1;
    population[3]->board[7] = 3;
    
//    cout<<population[0]->calculaFitness()<<endl;
//    cout<<population[1]->calculaFitness()<<endl;
//    cout<<population[2]->calculaFitness()<<endl;
//    cout<<population[3]->calculaFitness()<<endl;
}

void order(Population** p)
{
    for (int i = 0; i < Population::size; i++)
        for (int j = 0; j < Population::size; j++)
            if ((*p)->pop[i]->fitness > (*p)->pop[j]->fitness)
            {
                Node* aux = (*p)->pop[i];
                (*p)->pop[i] = (*p)->pop[j];
                (*p)->pop[j] = aux;
                int a = (*p)->fit_percent[i];
                (*p)->fit_percent[i] = (*p)->fit_percent[j];
                (*p)->fit_percent[j] = a;
            }
}

void random_selection(Population* p, Node** X, Node** Y)
{
    bool flag = false;
    float percent_X = abs((float)rand()/((float)RAND_MAX/100));
    float percent_Y = abs((float)rand()/((float)RAND_MAX/100));
    
    while (!flag)
    {
        if (percent_X < p->fit_percent[3])
            (*X) = p->pop[3];
        else if (percent_X < (p->fit_percent[2] + p->fit_percent[3]))  
            (*X) = p->pop[2];
        else if (percent_X < (p->fit_percent[1] + p->fit_percent[2] + p->fit_percent[3]))  
            (*X) = p->pop[1];
        else 
            (*X) = p->pop[0];
        
        if (percent_Y < p->fit_percent[3])
            (*Y) = p->pop[3];
        else if (percent_Y < (p->fit_percent[2] + p->fit_percent[3]))  
            (*Y) = p->pop[2];
        else if (percent_Y < (p->fit_percent[1] + p->fit_percent[2] + p->fit_percent[3]))  
            (*Y) = p->pop[1];
        else 
            (*Y) = p->pop[0];
        
        if ((*X) != (*Y))
            flag = true;
        else
        {
            percent_Y = abs((float)rand()/((float)RAND_MAX/100));
            percent_X = abs((float)rand()/((float)RAND_MAX/100));
        }       
    }
}

int GA(Population** p)
{
    float mutationR = 0.015; //(float) rand() / RAND_MAX;
    int generation = 0;
    do
    {
        generation++;
        (*p)->pop[0]->write();
        cout<<"Geracao: "<<generation<<" Fitness: "<<(*p)->pop[0]->fitness<<endl;
        
        Population* new_p = NULL;
        
        new_p = new Population();
        Node* child = NULL;
        
        for (int i = 0; i < Population::size; i++)
        {
            Node* X = NULL, *Y = NULL;
            random_selection((*p),&X,&Y);
            child = reproduce(X,Y);
            
            new_p->pop[i] = child;
        }
        
        for (int i = 0; i < Population::size; i++)
            for (int j = 0; j < Node::b_size; j++)
            {
                float chance = (float) rand() / RAND_MAX;
                if(chance < mutationR)
                    new_p->pop[i]->board[j] = rand() % Node::b_size;
            }
        
        new_p->update();
        
        delete (*p);
        
        (*p) = new_p;
        
        order(p);
        
    }while((*p)->pop[0]->fitness < (*p)->fit_goal);
    
    return generation;
}

int main(int argc, char** argv) {

    clock_t begin = 0, end = 0;
    
    srand(time(0));
    
    Population* population = NULL;
    
    population = new Population();
    
    population->start();
    
    order(&population);
    
    begin = clock();
    
    int count = GA(&population) + 1;
    
    end = clock();
    
    population->pop[0]->write();
    cout<<"Geracao: "<<count<<" Fitness: "<<population->pop[0]->fitness<<endl;
    
    cout<<"-------------------------"<<endl<<"  Configuracao Final"<<endl;
    
    population->pop[0]->print();
    
    cout <<"Tempo total necessario para a execucao: " << (double)(end-begin)/CLOCKS_PER_SEC << " segundos."<<endl;
    
    return 0;
}