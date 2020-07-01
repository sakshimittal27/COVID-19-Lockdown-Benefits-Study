#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
struct people
{
    int service;
    int infected;
    int interact;
    int check;
};
int i,j,k,a;
int p=5000;
int ran;
int ir=30;
float s=(3*5000)/100;
int matrix[5000][5000];
int a;
int t[5000][5000];
struct people town[5000];
float nons=5000-((3*5000)/100);

int randomYes()
{
    for(int ran=1;;ran++)
    {
        if(ran%1000==0)
            return 1;
        return 0;
    }
}
int transitive(int t[p][p])
{
    int total=0;
    for (int i=0;i<p;i++)
    {
        town[i].check=0;
    }
    for( int i=0;i<p;i++)
    {
        if(town[i].infected==1)
        {
            for(int j=0;j<p;j++)
            {
                if(t[i][j]==1)
                {
                    town[j].check=1;
                }
            }
        }
    }
    for( i=0;i<p;i++)
    {
        if(town[i].check==1 && town[i].infected==0)
            total++;
    }
    return total;
}
int countprimefactors(int x, int y)
{
    int count=0;

    for(int i=2;i<=x&&i<=y;i++)
    {
        int factor=0; int v=0;
        if(x%i==0 && y%i==0)
        {v=1;
            for(int j=2;j<=i/2;j++)
            {
                if(i%j==0)
                    factor++;
            }
        }
        if(factor==0 &&v==1)
        {
            int z=2;
            int flag=0;
            count++;
            while(flag==0)
            {
                if(x%(int)(pow(i,z++))==0 && y%(int)(pow(i,z++))==0)
                    count++;
                else
                    flag=1;
            }
        }
    }
    return count;
}
int biasedyes(int x, int y)
{
    int common=countprimefactors(x+1001,y+1001);
    return(rand()%100 < common);
}
int doexperiment()
{
    int in=0,sp=0;
float total= (((s*2*(5*p))/100)+((nons*20)));
float per=(nons*20);
float ser=((s*2*(5*p))/100);

    for(int i=0;i<p;i++)
    {
        for(int j=0;j<p;j++)
        {
            matrix[i][j]=0;
        }
    }

    for(int i=0;i<p;i++)
    {
        town[i].service=0;
    }
    for(int i=0;i<p;i++)
    {
        town[i].infected=0;
    }
    while(sp<s)            // Setting the service providers
    { i=rand()%p;
        if(town[i].service==0)
        {
            town[i].service=1;
            sp=sp+town[i].service;
        }

    }


   while(in<ir)          // Setting the infected people
    {i=rand()%p;
        if(town[i].infected==0)
        {
            town[i].infected=1;
            in=in+town[i].infected;
        }

    }
    int q=0;
while(q<(0.9*per))
{
    for(int i=0;i<p-1 && q<(0.9*per) ;i++)
    {
        if(town[i].service==0)
        {
                for(int j=i+1;j<p &&q<(per) ;j++)
                {  int b=biasedyes(i,j);
                if(b==1)
                 {
                if(matrix[i][j]==0 && town[j].service==0)

                    {
                        matrix[i][j]=1;
                        matrix[j][i]=1;
                        q+=2;

                    }
                 }
                 }

        }
    }}
    if(q>(per*1.1))
    {
        while(q>(per*1.1)){
        int i=rand()%p;
        int j=rand()%p;
        if(town[i].service==0 && town[j].service==0 && matrix[i][j]==1)
        {
            matrix[i][j]=0;
            q=q-2;
        }
    }}

    int y=0;
    while(y<(0.9*ser))
    {
    for(int i=0;i<p && y<(0.9*ser);i++)
    {
        if(town[i].service==1)
        {
                        for( j=i+1;j<p && y<(ser);j++)
                {  int b=biasedyes(i,j);
                if(b==1)
                    {


                    if(matrix[i][j]==0)
                    {
                        matrix[i][j]=1;
                        matrix[j][i]=1;
                        y+=2;

                    }
                }}
            }

        }
    }
    if(y>(1.1*ser))
    {
        while(y>(1.1*ser))
        {
            int i=rand()%p;
            int j=rand()%p;
            if(town[i].service==1 || town[j].service==1)
            {
                matrix[i][j]=0;
                        matrix[j][i]=0;
                        y=y-2;
            }

        }
    }int co=0;
for(int i=0;i<p;i++)
    for(int j=0;j<p;j++)
    co+=matrix[i][j];

    printf("INTERACTIONS: %d \t",co);
    for (int k=0;k<p;k++)
    {
        for (int i=0;i<p;i++)
        {
            if(matrix[i][k]==1)
            {
                for (int j=0;j<p;j++)
                {
                    matrix[i][j]=(matrix[i][j]||(matrix[i][k] && matrix[k][j]));
                }
            }
        }
    }
    a=transitive(matrix); printf("CHECK: a=%d ", a);
}
int main(void)
{
    int repeats;
    int resultsT100[10];
    printf("5000 3  T100 \n");
    for(repeats=0;repeats<10;repeats++)
    {
        doexperiment();
        printf("\n");

    }

}


