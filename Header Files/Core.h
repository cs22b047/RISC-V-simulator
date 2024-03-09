#include <iostream>
#include <string>
#include <vector>
#include <./IF.h>
#include <./ID.h>
#include <./EXE.h>
#include <./MEM.h>
#include <./WB.h>

class Core
{
public:
    long int regs[32];
    long int pc;
    IF *_if = new IF();
    ID *id = new ID();
    EXE *exe = new EXE();
    MEM *mem = new MEM();
    WB *wb = new  WB();
    void run(){
        while(true){
              
        }
    }
};