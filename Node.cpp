/* 
 * File:   Node.cpp
 * Author: M1thr4nd1r
 * 
 * Created on 9 de Fevereiro de 2013, 23:08
 */

#include "Node.h"

using namespace std;

Node::Node()
{
    for (int i = 0; i < Node::b_size; i++)
        this->board[i] = rand() % Node::b_size;
    this->fitness = -1;
}

void Node::print()
{
    for (int i = 0; i < Node::b_size; i++)
    {
        for (int j = 0; j < Node::b_size; j++)
            if (this->board[j] == i)
                cout<<" 1 ";
            else
                cout<<" 0 ";
        cout<<endl;
    }
    cout<<endl;
}

void Node::write()
{
    for (int i = 0; i < Node::b_size; i++)
        cout<<" "<<this->board[i]<<" ";
}