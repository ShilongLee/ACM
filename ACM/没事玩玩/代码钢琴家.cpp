#include<stdio.h>
#include<windows.h>
#include<time.h>
#include<string>
#include<string.h>
#include<iostream>
#include<fstream>
using namespace std;
int tonematrix[22][8]= {0,0,0,0,0,0,0,0,0,221,248,131,147,165,175,196,0,248,278,147,165,175,196,221,0,278,294,165,175,196,221,234,0,294,330,175,196,221,234,262,0,330,371,196,221,248,262,294,0,371,416,221,248,278,294,330,0,416,467,248,278,312,330,371,0,441,495,262,294,330,350,393,0,495,556,294,330,350,393,441,0,556,624,330,350,393,441,495,0,589,661,350,393,441,465,556,0,661,742,393,441,495,556,624,0,742,833,441,495,556,624,661,0,833,935,495,556,624,661,742,0,882,990,525,589,661,700,786,0,990,1112,589,661,700,786,882,0,1112,1178,661,700,786,882,990,0,1178,1322,700,786,882,935,1049,0,1322,1484,786,882,990,1049,1178,0,1484,1665,882,990,1112,1178,1322,0,1665,1869,990,1112,1248,1322,1484};
int music[1005][3];
int flag;
int ms,note=1;
string tone;
string tonestyle;
void filestyle()
{
    int col;
    ifstream fin("song.txt");
    fin>>note;
    fin>>tonestyle;
    if(tonestyle=="A"){col=1;}
    else if(tonestyle=="B"){col=2;}
    else if(tonestyle=="C"){col=3;}
    else if(tonestyle=="D"){col=4;}
    else if(tonestyle=="E"){col=5;}
    else if(tonestyle=="F"){col=6;}
    else if(tonestyle=="G"){col=7;}
    for(int i=0; i<=note; i++)
    {
        fin>>tone;
        if(tone=="1b"){music[i][1]=tonematrix[1][col];}
        else if(tone=="2b"){music[i][1]=tonematrix[2][col];}
        else if(tone=="3b"){music[i][1]=tonematrix[3][col];}
        else if(tone=="4b"){music[i][1]=tonematrix[4][col];}
        else if(tone=="5b"){music[i][1]=tonematrix[5][col];}
        else if(tone=="6b"){music[i][1]=tonematrix[6][col];}
        else if(tone=="7b"){music[i][1]=tonematrix[7][col];}
        else if(tone=="1"){music[i][1]=tonematrix[8][col];}
        else if(tone=="2"){music[i][1]=tonematrix[9][col];}
        else if(tone=="3"){music[i][1]=tonematrix[10][col];}
        else if(tone=="4"){music[i][1]=tonematrix[11][col];}
        else if(tone=="5"){music[i][1]=tonematrix[12][col];}
        else if(tone=="6"){music[i][1]=tonematrix[13][col];}
        else if(tone=="7"){music[i][1]=tonematrix[14][col];}
        else if(tone=="1#"){music[i][1]=tonematrix[15][col];}
        else if(tone=="2#"){music[i][1]=tonematrix[16][col];}
        else if(tone=="3#"){music[i][1]=tonematrix[17][col];}
        else if(tone=="4#"){music[i][1]=tonematrix[18][col];}
        else if(tone=="5#"){music[i][1]=tonematrix[19][col];}
        else if(tone=="6#"){music[i][1]=tonematrix[20][col];}
        else if(tone=="7#"){music[i][1]=tonematrix[21][col];}
        fin>>music[i][2];
    }
    fin.close();
    Beep(0,0);
    for(int i=0; i<=note; i++)
        Beep(music[i][1],music[i][2]);
        cout<<"演奏完毕"<<endl;
}
void fingerstyle()
{
    int col;
    cout<<"选用什么调:"<<endl;
    cin>>tonestyle;
    if(tonestyle=="A"){col=1;}
    else if(tonestyle=="B"){col=2;}
    else if(tonestyle=="C"){col=3;}
    else if(tonestyle=="D"){col=4;}
    else if(tonestyle=="E"){col=5;}
    else if(tonestyle=="F"){col=6;}
    else if(tonestyle=="G"){col=7;}
    cout<<"输入乐谱:"<<endl;
    ofstream fout("song.txt");
    fout<<"\t\t\t\t";
    fout<<endl<<tonestyle<<endl;
    while(cin>>tone>>ms)
    {
        if(tone=="1b"){music[note][1]=tonematrix[1][col];}
        else if(tone=="2b"){music[note][1]=tonematrix[2][col];}
        else if(tone=="3b"){music[note][1]=tonematrix[3][col];}
        else if(tone=="4b"){music[note][1]=tonematrix[4][col];}
        else if(tone=="5b"){music[note][1]=tonematrix[5][col];}
        else if(tone=="6b"){music[note][1]=tonematrix[6][col];}
        else if(tone=="7b"){music[note][1]=tonematrix[7][col];}
        else if(tone=="1"){music[note][1]=tonematrix[8][col];}
        else if(tone=="2"){music[note][1]=tonematrix[9][col];}
        else if(tone=="3"){music[note][1]=tonematrix[10][col];}
        else if(tone=="4"){music[note][1]=tonematrix[11][col];}
        else if(tone=="5"){music[note][1]=tonematrix[12][col];}
        else if(tone=="6"){music[note][1]=tonematrix[13][col];}
        else if(tone=="7"){music[note][1]=tonematrix[14][col];}
        else if(tone=="1#"){music[note][1]=tonematrix[15][col];}
        else if(tone=="2#"){music[note][1]=tonematrix[16][col];}
        else if(tone=="3#"){music[note][1]=tonematrix[17][col];}
        else if(tone=="4#"){music[note][1]=tonematrix[18][col];}
        else if(tone=="5#"){music[note][1]=tonematrix[19][col];}
        else if(tone=="6#"){music[note][1]=tonematrix[20][col];}
        else if(tone=="7#"){music[note][1]=tonematrix[21][col];}
        music[note][2]=ms;
        note++;
        fout<<tone<<' ';
        fout<<ms<<endl;
    }
    fout.seekp(0);
    fout<<note;
    fout.close();
    Beep(0,0);
    for(int i=0; i<note; i++)
        Beep(music[i][1],music[i][2]);
        cout<<"演奏完毕"<<endl;
}
int main()
{
    cout<<"1：文件读入乐谱     2：手动输入乐谱"<<endl;
    scanf("%d",&flag);
    if(flag==1)
        filestyle();
    else
        fingerstyle();
        /*for(int i=15;i<=21;i++)
        {
            for(int j=1;j<=7;j++)
                printf("%d ",tonematrix[i][j]);
            printf("\n");
        }*/
}
