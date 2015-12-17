#include "atoms.h"
#include <stdlib.h>
#include <fstream>

Atoms::Atoms() {
    atoms_str.clear();
    length = 0;
}

Atoms::~Atoms() {
    atoms_str.clear();
}

Atoms& Atoms::instance() {
    static Atoms atom;
    return atom;
}

int Atoms::query_atoms(string s) {
    for (size_t i = 0; i < atoms_str.size(); i++)
        if (s == atoms_str[i])
            return i + 1;
    return -1;
}

int Atoms::add_atoms(string s) {
    atoms_str.push_back(s);
    length++;
    return length;
}

string Atoms::get_atom_string(int i) {
    if (i > 0)
        return atoms_str[i - 1];
    return '~' + atoms_str[i * (-1) - 1];
}

void Atoms::show(FILE *out) const {
    for (int i = 0; i < length; i++)
        fprintf(out, "atom id: %d atom name: %s\n", i + 1, atoms_str[i].c_str());
}

int Atoms::get_true_num(int id) {
    string s = Vocabulary::instance().getAtom(id);
    int k = query_atoms(s);
    if (k == -1)
        return add_atoms(s);
    else
        return k;
}
