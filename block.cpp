#include "block.h"
#include <QTime>
#include <time.h>
#include <QDebug>

block::block()
{

}

block::block(int row,int col,int boom)
{
    //初始化私有成员
    this->row=row;
    this->col=col;
    this->boom=boom;
    this->timeNum=0;
    this->flagNum=boom;
    winNum=1;
    det=1;

    //创建二维数组，自行建立难度系数
    p=new int *[row];
    for(int i=0;i<row;i++)
    {
        p[i]=new int [col];
    }
    //数组置初值
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<col;j++)
        {
            p[i][j]=100;
        }
    }
    //产生随机数字炸弹,且int值赋为99
    srand((unsigned)time(0));
    for(int i=0;i<boom;i++)
    {
        int c=rand()%(row*col)-1;
        int a=c/col;
        int b=c%col;
        if(p[a][b]!=99)
        {
            p[a][b]=99;
        }
        else
        i--;
    }
    //为炸弹外的格子赋值
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<col;j++)
        {
            if(p[i][j]!=99)
            {
                int num=0;
                for(int xrow=i-1;xrow<=i+1;xrow++)
                {
                    for(int ycol=j-1;ycol<=j+1;ycol++)
                    {
                        if(xrow<0||ycol<0||xrow>=row||ycol>=col||(xrow==i&&ycol==j))
                        continue;
                        if(p[xrow][ycol]==99)
                        num++;
                    }
                }
            p[i][j]+=num;
            }
        }
    }

}

block::~block()
{
    for(int i=0;i<row;i++)
    {
        delete[] p[i];
    }
    delete [] p;
}

block::restart()
{
    //数组置初值
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<col;j++)
        {
            p[i][j]=100;
        }
    }
    //产生随机数字炸弹,且int值赋为99
    srand((unsigned)time(0));
    for(int i=0;i<boom;i++)
    {
        int c=rand()%(row*col)-1;
        int a=c/col;
        int b=c%col;
        if(p[a][b]!=99)
        {
            p[a][b]=99;
        }
        else
        i--;
    }
    //为炸弹外的格子赋值
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<col;j++)
        {
            if(p[i][j]!=99)
            {
                int num=0;
                for(int xrow=i-1;xrow<=i+1;xrow++)
                {
                    for(int ycol=j-1;ycol<=j+1;ycol++)
                    {
                        if(xrow<0||ycol<0||xrow>=row||ycol>=col||(xrow==i&&ycol==j))
                        continue;
                        if(p[xrow][ycol]==99)
                        num++;
                    }
                }
            p[i][j]+=num;
            }
        }
    }
}

bool block::click(int m,int n)
{
    qDebug() << "点击左键";


    //检测递归中格子有无雷
    if(winNum==0||winNum==2)
    {
        return false;
    }
    if(m>=row||n>=col||m<0||n<0)
    {
        return false;
    }
    if(p[m][n]<=108&&p[m][n]>=101)
    {
        p[m][n]-=100;
        ifWin();
        return true;
    }
    //使用递归点开周围无雷的格子
    if(p[m][n]==100)
    {
        p[m][n]-=100;
        click(m,n-1);
        click(m,n+1);
        click(m-1,n);
        click(m+1,n);
        click(m-1,n+1);
        click(m-1,n-1);
        click(m+1,n-1);
        click(m+1,n+1);
    }
    if(p[m][n]==99)
    {
        if(det)
        {
            boom--;
            int i,j,temp=0;
            for(i=m-1;i<=m+1;i++)
            {
                for(j=n-1;j<=n+1;j++)
                {
                    if(i<row&&j<col&&j>0&&i>0&&(i!=m||j!=n))
                    {
                        if(p[i][j]>99)
                        {
                            p[i][j]--;
                        }
                        if(p[i][j]==99)
                        temp++;
                    }
                }
                det=0;
            }
            //p[m][n]=temp+100;
            click(m,n);
            return true;
        }
        for(int i=0;i<row;i++)
        {
            for(int j=0;j<col;j++)
            {
                if(p[i][j]==99)
                p[i][j]=-1;
                if(p[i][j]>49&&p[i][j]<60)
                p[i][j]=-2;
            }
            winNum=0;
        }
    }
    return true;
}

int block::ctnflag(int m,int n)
{
    int t = 0;
    if (m >= row || m < 0 || n >= col || n < 0)
        return -1;
    int a, b;
    for (a = -1; a < 2; a++)
        for (b = -1; b < 2; b++)
        {
            if ((m + a >= row) || (n + b >= col) || (m + a<0) || (n + b<0) || (p[m + a][n + b] > 60) || (p[m + a][n + b] < 40))
                continue;
            t++;
        }
    return t;
}


//右键点击标红旗
bool block::clickred(int m,int n)
{
    if(winNum==0||winNum==2)
    {
        return false;
    }
    if(p[m][n]>90)
    {
        p[m][n]-=50;
        boom--;
    }
    else if(p[m][n]>40&&p[m][n]<60)
    {
        boom++;
        p[m][n]+=50;
    }
    return true;
}

bool block::clicklr(int m,int n)
{
    if (m >= row || m < 0 || n >= col || n < 0||p[m][n]>40)
        return false;
    if (p[m][n] == ctnflag(m, n))
    {
        click(m - 1, n);
        click(m + 1, n);
        click(m, n - 1);
        click(m, n + 1);
        click(m - 1, n - 1);
        click(m + 1, n - 1);
        click(m - 1, n + 1);
        click(m + 1, n + 1);
    }
    return true;
}

bool block::ifWin()
{
    int i, j;
    for(i=0;i<row;i++)
    {
        for(j=0;j<col;j++)
        {
            if (p[i][j]>99);
                return false;
            if (p[i][j]>49&&p[i][j]<59)
                return false;
        }
    }
    winNum = 2;
    return true;
}
