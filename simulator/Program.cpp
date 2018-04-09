#include "program.h"
#include <fstream>
#include <iostream>
#include "instruction.h"
#include "l_direction.h"
#include "l_drop.h"
#include "l_flip.h"
#include "l_mark.h"
#include "l_move.h"
#include "l_pickup.h"
#include "l_sense.h"
#include "l_turn.h"
#include "l_unmark.h"
#include "tokenizer.h"

#include <vector>
using namespace std;

Program::Program(string filename)
{
    ifstream f(filename.c_str());
   
    if(!f.is_open())
    {
        throw "Unable to open the assembly language program file\n";
    }
    
   // vector<string> command;
    int i=0;
    string s;

    while(f.good())
    {
        getline(f,s);
        vector<string> command=tokens_in_vector(s);
        vector<string>::iterator it=command.begin();
        if(*it== "sense"){
            l_sense* t;
            t.parse(command);
            inst.push_back(t);
        }
        else if(*it=="flip"){
            l_flip * f;
            f.parse(command);
            inst.push_back(f);
        }
        else if(*it=="pickup"){
            l_pickup *p;
            p.parse(command);
            inst.push_back(p);
        }
        else if(*it=="mark"){
            l_mark* t;
            t.parse(command);
            inst.push_back(t);
        }
        else if(*it=="unmark"){
            l_unmark* u;
            u.parse(command);
            inst.push_back(u);
        }
        else if(*it =="direction"){
            l_direction * d;
            d.parse(command);
            inst.push_back(d);
        }
        else if(*it=="move"){    
            l_move * m;
            m.parse(command);
            inst.push_back(m);
        }
        else if(*it=="turn"){
            l_turn* t;
            t.parse(command);
            inst.push_back(t);
        }
        else if(*it== "drop"){
            l_drop* dr;
            dr.parse(command);
            inst.push_back(dr); 
        }
        else{
            throw "Unspecified command\n";
        }
    }
    
    
    /*vector<string>::iterator it=command.begin();
    for(it; it!=command.end();it++)
    {
        cout<<*it<<endl; checked if input well read
    }*/
    
}
