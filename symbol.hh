#ifndef SYMBOL_HH
#define SYMBOL_HH
#include "string.hh"
#include "boxes.hh"

struct Symbol {
    String tex;
    Box dim;

    Symbol (String, Box);
    Symbol();
};

struct Parametric_symbol {    
    
    Symbol eval(String args1) const; // convenience
    Symbol eval(String args1,String arg2) const; // convenience
    virtual Symbol eval(svec<String> args)const =0;
    virtual ~Parametric_symbol();    
};

#endif
