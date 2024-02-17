#ifndef SOLVER_H
#define SOLVER_H

#include <stdio.h>
#include <string.h>

typedef struct Node {
    struct Node *left, *right, *up, *down;
    struct ColumnNode *column;
} Node;


typedef struct ColumnNode{
    Node node;
    int size; // number of nodes belonging to the column
    char name[16]; //debugging, will be removed later
} ColumnNode;

#endif