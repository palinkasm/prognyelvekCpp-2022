#ifndef PIPE_H
#define PIPE_H

#include <vector>

template<typename T>
class Pipe{
public:

    Pipe<T>() {};

    Pipe<T>(T (* param)(T)){
        funcs.push_back(param);
    }

    T operator()(T param){
        return run(param);
    }

    Pipe operator|(Pipe r){
        Pipe<T> newPipe = *this;
        newPipe += r;
        return newPipe;
    }

    void operator+=(Pipe &r){
        int size = r.funcs.size();
        int i = 0;
        while(i<size) {
            funcs.push_back(r.funcs[i]);
            i++;
        }
    }

    void add_operation( T (*func)(T)){ //elso T a funk visszateresi tipusa ,masodik T pedig hogy a funkcio milyen tipusu parametert var
        funcs.push_back(func);
    }

    T run(T param){
        T r = param;
        for (long unsigned int i = 0; i < funcs.size(); ++i) {
            r = funcs[i](r);
        }
        return r;
    }

    void clear(){
        funcs.clear();
    }

private:
    std::vector<T (*)(T)> funcs;
};

#endif
