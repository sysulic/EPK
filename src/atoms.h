#ifndef ATOMS_H
#define	ATOMS_H


#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <cstdio>
#include "structs.h"
using namespace std;

class Atoms{
public:
    Atoms();
    ~Atoms();
    vector<string> atoms_str;
    int length;
public:
    
    static Atoms& instance();
    int query_atoms(string);
    int add_atoms(string);
    string get_atom_string(int);
    inline int atoms_length() const { return length; }
    void show(FILE *out) const;
};

#endif
