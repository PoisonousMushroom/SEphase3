/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   world.cpp
 * Author: whitebox
 *
 * Created on March 3, 2018, 3:07 PM
 */

#include <cstdlib>
#include "./headers/bug.h"
#include "./headers/aux.h"
#include "./headers/world.h"
#include <string>
#include <iostream>
#include <fstream>
#include "./headers/Cell.h"
#include <algorithm>
using namespace std;

/*
 * 
 */

bool even(int n){
    return (n % 2);
}

bool odd(int n){
    return !(n%2);
}

int World::load(char* worldfile){
    ifstream wf;
    string line;
    aux::tcolor black, red;
    black.c = 0;
    red.c = 1;
    int bbcount = 0;
    int rbcount = 0;
    wf.open(worldfile, ios::in);
    if(wf.is_open()){
        wf >> width >> length;
    }
    else{
        error("No such file exists. Check again? \n");
        return 1;
    }
    cout << "Width: "<< width << endl;
    cout << "Length: " << length << endl;
    
    cell_container.resize(length);
    cout << "Mother vector resized \n" ;
            
    for(size_t i = 0; i < width; i++){
        cell_container[i].resize(width);
    }
    cout << "Child vectors resized \n";
    
    getline(wf, line);
    cout << line;
    for (int l = 0; l < length; l++){
        getline(wf, line);
        line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
        for (int w = 0; w < width; w++){
            //cout << line[w];
            Cell *new_cell = new Cell(line[w]);
            cell_container[l][w] = new_cell;
            if(line[w] == '+'){
                //Bug new_bug = (new_cell->get_occupant());                
                Bug *new_bug = new Bug(red, rbcount, 0);
                new_bug->set_position(w, l);
                new_bug->set_has_food(false);
                redbugs.push_back(new_bug);
                new_cell->set_occupant(redbugs[rbcount]);
                rbcount++;
                //cout << "Red bug home base found; Creating a bug...\n";
            }
            if(line[w] == '-'){
                //Bug new_bug = (new_cell->get_occupant());
                Bug *new_bug = new Bug(black, bbcount, 0);
                new_bug->set_position(w, l);
                new_bug->set_has_food(false);
                blackbugs.push_back(new_bug);
                new_cell->set_occupant(blackbugs[bbcount]);
                bbcount++;
                //cout << "Black bug home base found; Creating a bug...\n";
            }
            
            //cout << "Cell assigned successfully" << endl;
        }
        cout << endl;
        
    }
    cout << "World initialization complete. \n";
    return 0;
}

int World::cell_test(){
    for(int l = 0; l < length; l++){
        for(int w = 0; w < width; w++){
            if(cell_container[l][w]){
                //cout << "Cell " << l << " " << w << " exists. \n" << endl;
            }
            else{
                return 1;
            }
        }
    }
    return 0;
}

aux::tposition World::adjacent(aux::tdirection dir, aux::tposition pos){
    int d = dir.d;
    aux::tposition res;
    switch(d){
        case 0:
            res.x = pos.x + 1;
            res.y = pos.y;
            break;
        case 1:
            if(even(pos.y)){
                res.x = pos.x;
                res.y = pos.y+1;
            }
            else{
                res.x = pos.x+1;
                res.y = pos.y+1;
            }
            break;
        case 2:
            if(even(pos.y)){
                res.x = pos.x-1;
                res.y = pos.y+1;
            }
            else{
                res.x = pos.x;
                res.y = pos.y+1;
            }
            break;
        case 3:
            res.x = pos.x-1;
            res.y = pos.y;
            break;
        case 4:
            if(even(pos.y)){
                res.x = pos.x-1;
                res.y = pos.y-1;
            }
            else{
                res.x = pos.x;
                res.y = pos.y-1;
            }
            break;
        case 5:
            if(even(pos.y)){
                res.x = pos.x;
                res.y = pos.y-1;
            }
            else{
                res.x = pos.x+1;
                res.y = pos.y-1;
            }
            break;
        default:
            cout << "Error!" << endl;
            res.x = -1;
            res.y = -1;
            throw("Invalid direction integer!\n");
            ///raise exception here;
            break;
    }
    return res;
    
}

//Implemented Oana's 
aux::tcolor World::other_color(aux::tcolor c){
    aux::tcolor res;
    res.c = 1 - c.c;
    
    return res;
}

//winner method

int World::red_food(){
    int count = 0;
    for(int i = 0; i<World::red_count(); i++){
        if(redbugs[i]->get_has_food()){
            cout << "Red Bug "<< i<< " has food\n";
            count++;
        }
    }
    return count;
}

int World::black_food(){
    int count = 0;
    for(int i = 0; i<World::black_count(); i++){
        if(blackbugs[i]->get_has_food()){
            cout << "Black Bug "<< i<< " has food\n";
            count++;
        }
    }
    return count;
}

int World::red_count(){
    return redbugs.size();
}
int World::black_count(){
    return blackbugs.size();
}

void World::error(string msg){
    cout << msg << endl;
}

void World::log(string msg){
    ofstream logfile;
    logfile.open("log.txt", ios::out);
    if(logfile.is_open()){
        logfile << msg << endl;
        cout << "successfully logged \n"; 
    }
    logfile.close();
    
}

void World::print_grid(){
    for(int i = 0; i < cell_container.size(); i++){
        for(int j = 0; j < cell_container[0].size(); j++){
            cout << cell_container[i][j]->get_char() << " ";
        }
        cout << endl;
    }
}

bool World::place_at(aux::tposition p, Bug* b){
    if(cell_container[p.y][p.x]->occupied()){
        throw ("The cell is already occupied!");
    }
    else{
        b->set_position(p.x, p.y);
    }
}

int World::food_at(aux::tposition p){
    return get_cell(p)->get_food();
};
bool World::set_food_at(aux::tposition p, int f){ //not additive;
    if(get_cell(p)->get_obstructed() ){
        return false;
    }
    else{
        get_cell(p)->set_food(f);
    }
};
    
bool World::base_at(aux::tposition p, aux::tcolor c){
    if(c.c = 0){
        return get_cell(p)->is_black_home_area();
    }
    else return get_cell(p)->is_red_home_area();
};
bool World::other_base_at(aux::tposition p, aux::tcolor c){
    return !base_at(p, c);
};
    
//Martial arts
int World::adjacent_other_bugs(aux::tposition p, aux::tcolor c){
    aux::tdirection d;
    int count = 0;
    for(int i = 0; i < 6; i++){
        d.d = i;
        aux::tposition adjp = adjacent(d, p);
        if(get_cell(adjp)->occupied()){
            if(get_cell(adjp)->get_occupant()->get_color().c == c.c){
                count++;
            }
        }
    }
    return count;
};

void World::kill_if_surrounded(aux::tposition p){
    if(p.x < 1 || p.y < 1 || p.x > width - 2 || p.y > length - 2){
        //cout << "Invalid coordinates. \n";
        return;
    }
    if(get_cell(p)->occupied()){
        Bug* b = get_cell(p)->get_occupant();
        aux::tcolor oc = other_color(b->get_color());
        if(adjacent_other_bugs(p, oc) > 4){
            cout <<"This bug is surrounded! Alas, I must commit seppuku...\n";
            int i = 0;
            if (b->get_has_food()){ //drop an extra food if bug had one
                i = 1;
            }
            
            //set the cell up accordingly 
            set_food_at(p, (5 + i));
            cout << "Coordinates of the dead bug: \n" << "x: " << p.x << " y: " << p.y << endl;
            get_cell(p)->get_occupant()->kill();
            get_cell(p)->set_occupant(NULL);
            get_cell(p)->set_occupancy(false);
        }
        else{
           //cout <<"I shall live to see another day!\n";
        }
    }
};

void World::check_for_surrounded_bugs(aux::tposition p){
    kill_if_surrounded(p);
    aux::tdirection dir;
    for(int d = 0; d < 6; d++){
        dir.d = d;
        kill_if_surrounded(adjacent(dir, p));
    }
};