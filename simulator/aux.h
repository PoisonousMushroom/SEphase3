

#ifndef AUX_H
#define AUX_H

#include <string>
using std::string;
namespace aux{
    struct tcolor{
        int c; //0 or 1 for black or red 
        tcolor(int x):c(x){};
        tcolor():c(0){};
    };

    struct tdirection{
        int d;
        tdirection(int x):d(x){};
        tdirection():d(0){};
    };

    struct tsensedir{
        int s;
        tsensedir(int x):s(x){};
    };

    struct tleftright{
        int l;
        tleftright(int x):l(x){};
    };

    struct tmark{
        int m;
        tmark():m(0){};
        tmark(int x):m(x){};
    };

    struct tstate{
        int st;
        tstate(int x):st(x){};
        tstate():st(0){};
        tstate(string x):st(stoi(x)){};
    };

    struct tcondition{
        int cond;
        tcondition(int x):cond(x){};
    };

    struct tposition{
        int x;
        int y;
        tposition(int t, int q):x(t),y(q){};
        tposition():x(0),y(0){};
    };
};
#endif /* AUX_H */

