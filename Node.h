/* 
 * File:   Node.h
 * Author: M1thr4nd1r
 *
 * Created on 9 de Fevereiro de 2013, 23:08
 */

#ifndef NODE_H
#define	NODE_H

#include <cstdlib>
#include <iostream>
#include <ctime>

class Node {
public:
    static const int b_size = 8;
    int fitness;
    int board[Node::b_size];
    Node();
    void print();
    void write();
private:

};

#endif	/* NODE_H */

