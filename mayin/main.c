#include <stdio.h>
#include <stdlib.h>
#define BOYUT 8
#define MAYIN 7
#define KAZAN 1
#define KAYBET -1
#define TEKRAR 0

int tarla[BOYUT+2][BOYUT+2];
char tablo[BOYUT+2][BOYUT+2];
int bayrak_sayisi=0;
int y=0;
int bomba;
void alt_tablo();
void tabloyu_baslat();
void alti_bastir();
void tabloyu_bastir();
void mayin_yerlestir();
int kazandim_mi();
void mayinlari_kontrol();
int ac(int satir,int sutun);
int main()
{
    int satir,sutun;
    int ilerleme;

    int yeniden;
    char aksiyon;
    printf("oyun baslasinnn\n\n");
    alt_tablo();
    tabloyu_baslat();

    mayin_yerlestir();
    do
    {
       tabloyu_bastir();
       printf("ac: c,satir,sutun\nbayrak: d,satir,sutun\nbayragi kaldir: e,satir,sutun\n");
       scanf("%c,%d,%d",&aksiyon,&satir,&sutun);
       if(aksiyon == 'c')
       {
           ilerleme=ac(satir,sutun);
       }
       else if(aksiyon=='d')
       {
           if(MAYIN>bayrak_sayisi)
           {
               bayrak_sayisi++;
               tablo[satir][sutun]='D';
               ilerleme=kazandim_mi();
           }
       }
       else if(aksiyon=='e')
       {
           if(bayrak_sayisi>0)
           {
               bayrak_sayisi--;
               tablo[satir][sutun]='#';
               ilerleme=ac(satir,sutun);
           }
       }
       if(ilerleme==KAYBET)
       {
           printf("\nkaybettiniz\n");
           alti_bastir();
           printf("\nYeni oyun icin :1, cikmak icin:2");
           scanf("%d",&yeniden);
           switch(yeniden)
           {
           case 0:
            {
                printf("\nbyee");
                return 0;
                break;
            }
           case 1:
            {
                bayrak_sayisi=0;
                ilerleme=TEKRAR;
                alt_tablo();
                tabloyu_baslat();
                break;
            }
           default:
            {
                printf("\nyanlis bir deger girdiniz..");
                break;
            }
           }
       }
       if(ilerleme==KAZAN)
       {
           printf("\nHarikaa, kazandiniz..\n");
           alti_bastir();
           printf("\nYeni oyun icin :1, cikmak icin:2");
           scanf("%d",&yeniden);
           switch(yeniden)
           {
           case 0:
            {
                printf("\nbyee");
                return 0;
                break;
            }
           case 1:
            {
                bayrak_sayisi=0;
                ilerleme=TEKRAR;
                alt_tablo();
                tabloyu_baslat();
                break;
            }
           default:
            {
                printf("\nyanlis bir deger girdiniz..");
                break;
            }


       }
       }
    }while(1);
    return 0;
}
void alt_tablo()
{
    int i,j,bomba;
    for(i=0;i<=BOYUT+1;i++)
    {
        for(j=0;j<=BOYUT+1;j++)
        {
            tarla[i][j]=0;
        }
    }
    for(i=0;i<=BOYUT+1;i++)
    {
        tarla[i][0]=1;
        tarla[i][BOYUT+1]=1;
    }
    for(i=0;i<BOYUT+1;i++)
    {
        tarla[0][i]=1;
        tarla[BOYUT+1][i]=1;
    }
    bomba=MAYIN;

}
void tabloyu_baslat()
{
    int i,j;
    for(i=0;i<=BOYUT+1;i++)
    {
        for(j=0;j<=BOYUT+1;j++)
        {
            tablo[i][j]='#';
        }
    }
    for(i=0;i<=BOYUT+1;i++)
    {
        tablo[i][0]=1;
        tablo[i][BOYUT+1]='*';
    }
    for(i=0;i<BOYUT+1;i++)
    {
        tablo[0][i]=1;
        tablo[BOYUT+1][i]='*';
    }
}
void tabloyu_bastir()
{
    int i,j;
    for(i=1;i<=BOYUT;i++)
    {
        printf("%d   ",i);
    }
    printf("\n");
    for(i=1;i<=BOYUT;i++)
    {
        printf("-   ");
    }
    printf("\n");
    for(i=1;i<=BOYUT;i++)
    {
        for(j=1;j<=BOYUT;j++)
        {
            printf("%c   ",tablo[i][j]);
        }
        printf("|%d\n",i);
    }
}
void mayin_yerlestir()
{
    int i,j,k,l,satir,sutun,bombalar;
    bombalar=MAYIN;
    srand(time(0));
    for(i=1;i<=bombalar;i++)
    {
        satir=1+rand()%BOYUT;
        sutun=1+rand()%BOYUT;
        if(tarla[satir][sutun]==-1)
        {
            i--;
        }
        tarla[satir][sutun]=-1;
        for(k=-1;k<=1;k++)
        {
            for(j=-1;j<1;j++)
            {
                if(tarla[satir+k][sutun+j]!=-1)
                {
                    tarla[satir+k][sutun+j]++;
                }
            }
        }
    }

}
int ac(int satir,int sutun)
{
    int x=0;
    if(tarla[satir][sutun]==-1)
    {
        x=KAYBET;
    }
    else if(tarla[satir][sutun]>0)
    {
        tablo[satir][sutun]=('0'+tarla[satir][sutun]);
        //x=kazandim_mi();
        x=TEKRAR;

    }
    else
    {
        alti_bastir(satir,sutun);
    }
    return x;
}
void alti_bastir(int satir,int sutun)
{
    int i,j;
    tablo[satir+i][sutun+j]='0'+tarla[satir+i][sutun+j];
    for(i=-1;i<=1;i++)
    {
        for(j=-1;j<=1;j++)
        {
            if(tarla[satir+i][sutun+j]>0 && tablo[satir+i][sutun+j]=='#')
            {
                tablo[satir+i][sutun+j]='0'+tarla[satir+i][sutun+j];
            }
            else if(tarla[satir+i][sutun+j]==0 && tablo[satir+i][sutun+j]=='#')
            {
                alti_bastir(satir+i,sutun+j);
            }
        }
    }
}
int kazandim_mi()
{
    int i,j;
    int y=0;
    int sonuc;
    for(i=1;i<=BOYUT;i++)
    {
        for(j=1;j<=BOYUT;j++)
        {
            if(tablo[i][j]=='D')
            {
                if(tarla[i][j]==-1)
                {
                    y++;
                }
            }
        }
    }
    if(y==MAYIN)
    {
        sonuc=KAZAN;
    }
    else
    {
        sonuc=TEKRAR;
    }
    return sonuc;
}
