#ifndef BLOCK_H
#define BLOCK_H

//#include "iostream"
//#include "ctime"
//#include "stdlib.h"
//#include <QDebug>

class block
{
    //private:
public:
        int timeNum,flagNum;

    public:
        int row,col,boom;
        int winNum;
        int det;
        int **p;

        block();
        block(int row,int col,int boom);
        ~block();

        restart();
        bool ifWin();
        int ctnflag(int m,int n);
        bool click(int m,int n);
        bool clickred(int m,int n);
        bool clicklr(int m,int n);


};

#endif // BLOCK_H
