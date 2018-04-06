/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   aux.h
 * Author: whitebox
 *
 * Created on February 28, 2018, 11:01 PM
 */

#ifndef AUX_H
#define AUX_H

#include <string>

namespace aux{
    struct tcolor{
        int c; //0 or 1 for black or red 
    };

    struct tdirection{
        int d;
    };

    struct tsensedir{
        int s;
    };

    struct tleftright{
        int l;
    };

    struct tmark{
        int m;
    };

    struct tstate{
        int st;
    };

    struct tcondition{
        int cond;
    };

    struct tposition{
        int x;
        int y;
    };
};
#endif /* AUX_H */

