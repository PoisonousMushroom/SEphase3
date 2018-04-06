#include <iostream>


#include <vector>
#include <string.h>

#include "func.h"
#include "instruction.h"

#include "I_flip.cpp"
#include "I_sense.cpp"
#include "I_mark.cpp"
#include "I_pickup.cpp"
#include "I_turn.cpp"
#include "I_direction.cpp"
#include "I_move.cpp"
#include "I_unmark.cpp"
#include "I_drop.cpp"

using namespace std;

//helper function to tokenize the string
//and push it into a vector

vector<string>str_in_tokens(string args){

  vector<string> v;

  char * token;
  token = strtok (str," ,.-");
  while (token!= NULL)
  {
    v.push_back(token);
    token= strtok (NULL, " ,.-");
  }

  return v;
}

void Instruction::parse(string args){

  vector<string> v;

  v = str_in_tokens(args);

  int i=0;

  while(i<v.size()){
    switch (v[i]) {
      case "flip":
      //we use stoi to convert from string to int
        int p=stoi (v[i+1],nullptr,10);
        tstate x(stoi (v[i+2],nullptr,10));
        tstate y(stoi (v[i+3],nullptr,10));
        //increment i in order to reach the end of the command
        i+=3;

        flip(p, x, y);
        break;

      case "sense":
        tsensedir sdir(stoi (v[i+1],nullptr,10));
        tstate x(stoi (v[i+2],nullptr,10));
        tstate y(stoi (v[i+3],nullptr,10));
        tcondition cond(stoi (v[i+4],nullptr,10));

        i+=4;

        sense(p, x, y,cond);
        break;

      case "mark":
        int nr= sdir(stoi (v[i+1],nullptr,10));
        tstate z(stoi (v[i+2],nullptr,10))

        i+=2;
        mark(nr, z);
        break;

      case "pickup":
        tstate x(stoi (v[i+1],nullptr,10));
        tstate y(stoi (v[i+2],nullptr,10));

        i+=2;
        pickup(x, y);
        break;

      case "unmark":
        int nr= sdir(stoi (v[i+1],nullptr,10));
        tstate z(stoi (v[i+2],nullptr,10))

        i+=2;
        mark(nr, z);
        break;

      case "direction":
        tdirection tdir(stoi (v[i+1],nullptr,10));
        tstate x(stoi (v[i+2],nullptr,10));
        tstate y(stoi (v[i+3],nullptr,10));
        i+=3;
        direction(tdir,x,y);
        break;

      case "turn":
        tleftright lr(stoi (v[i+1],nullptr,10));
        tstate z(stoi (v[i+2],nullptr,10));

        i+=2;
        turn(lr, z);
        break;

      case "move":
        tstate x(stoi (v[i+1],nullptr,10));
        tstate y(stoi (v[i+2],nullptr,10));
        i+=2;
        move(x,y);
        break;

      case "drop":
        tstate z(stoi (v[i+1],nullptr,10));
        i+=1;
        drop(z);
        break;

    }
    //begin to read the next command
    i++;
  }
}
