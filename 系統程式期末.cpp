#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <math.h>
#include <string.h>
using namespace std;
char opcode[10];
char operand[21];
char label[9];
string str;
int loc[100] {0};
int LDA_count=0;
int now =1; //從1開始，第二行的LOC
int pig=0;
int base, Ltorg, LtorgNow, X=0;
int equ_count;
bool f1=false;

//郡
int Num_Of_Lines = 0;
struct Line
{
    int LineNo;
    int LOC;
    char Label[9];
    char Opcode[10];
    char Operand[21];
    char ObjectCode[9];
};
Line LINE[100];

//約翰
struct symbol
{
    char name[10];
    char status;
    int address;
};
struct symbol s[100];
int snum =0;

//約翰+郡
void reset() //得到每行 label，opcode，operand
{
    for(int i=0; i<8; i++)
    {
        label[i]=str[i];
        LINE[Num_Of_Lines].Label[i] = str[i];
    }
    for(int i=0; i<9; i++)
    {
        opcode[i]=str[i+11];
        LINE[Num_Of_Lines].Opcode[i] = str[i+11];
    }
    for(int i=0; i<20; i++)
    {
        operand[i]=str[i+23];
        LINE[Num_Of_Lines].Operand[i] = str[i+23];
    }

    LINE[Num_Of_Lines].LineNo = Num_Of_Lines;

}

void setloc()
{
    if (opcode[0]=='S'&&opcode[1]=='T'&&opcode[2]=='A'&&opcode[3]=='R'&&opcode[4]=='T')
    {
        int t=0;
        int tt=0;
        int ttt=0;
        while(operand[t]>='0'&&operand[t]<='9')
        {
            t++;
        }
        int tm=t;
        for(int j=0; j<tm; j++)
        {
            t--;
            int a;
            tt=pow(10,t);
            a=(operand[j]-48)*tt;
            ttt+=a;
        }
        loc[0]=ttt;
        loc[now]=loc[now-1];
    }
    else if(opcode[0]=='+')
        loc[now]=loc[now-1]+4;
    else if(label[0]=='.')
    {
        loc[now]=loc[now-1];
    }
    else if(opcode[0]=='A'&&opcode[1]=='D'&&opcode[2]=='D')
        loc[now]=loc[now-1]+3;
    else if(opcode[0]=='C'&&opcode[1]=='L'&&opcode[2]=='E'&&opcode[3]=='A'&&opcode[4]=='R')
    {
        if(pig==1)
        {
            loc[now-1]=equ_count;
            pig=0;
        }
        loc[now]=loc[now-1]+2;
    }
    else if(opcode[0]=='C'&&opcode[1]=='O'&&opcode[2]=='M'&&opcode[3]=='P'&&opcode[4]=='R')
        loc[now]=loc[now-1]+2;
    else if(opcode[0]=='C'&&opcode[1]=='O'&&opcode[2]=='M'&&opcode[3]=='P')
        loc[now]=loc[now-1]+3;
    else if(opcode[0]=='D'&&opcode[1]=='I'&&opcode[2]=='V')
        loc[now]=loc[now-1]+3;
    else if(opcode[0]=='J'&&opcode[1]=='S'&&opcode[2]=='U'&&opcode[3]=='B')
        loc[now]=loc[now-1]+3;
    else if(opcode[0]=='J'&&opcode[1]=='L'&&opcode[2]=='T')
        loc[now]=loc[now-1]+3;
    else if(opcode[0]=='J'&&opcode[1]=='G'&&opcode[2]=='T')
        loc[now]=loc[now-1]+3;
    else if(opcode[0]=='J'&&opcode[1]=='E'&&opcode[2]=='T')
        loc[now]=loc[now-1]+3;
    else if(opcode[0]=='J')
        loc[now]=loc[now-1]+3;
    else if(opcode[0]=='L'&&opcode[1]=='D'&&opcode[2]=='A')
    {
        loc[now]=loc[now-1]+3;
        if(operand[0]=='=')
        {
            int i=3;
            while(operand[i]>='A'&&operand[i]<='Z')
            {
                LDA_count++;
                i++;
                continue;
            }
        }
    }
    else if(opcode[0]=='L'&&opcode[1]=='D'&&opcode[2]=='B')
        loc[now]=loc[now-1]+3;
    else if(opcode[0]=='L'&&opcode[1]=='D'&&opcode[2]=='C'&&opcode[3]=='H')
        loc[now]=loc[now-1]+3;
    else if(opcode[0]=='L'&&opcode[1]=='D'&&opcode[2]=='L')
        loc[now]=loc[now-1]+3;
    else if(opcode[0]=='L'&&opcode[1]=='D'&&opcode[2]=='S')
        loc[now]=loc[now-1]+3;
    else if(opcode[0]=='L'&&opcode[1]=='D'&&opcode[2]=='T')
        loc[now]=loc[now-1]+3;
    else if(opcode[0]=='L'&&opcode[1]=='D'&&opcode[2]=='X')
        loc[now]=loc[now-1]+3;
    else if(opcode[0]=='M'&&opcode[1]=='U'&&opcode[2]=='L')
        loc[now]=loc[now-1]+3;
    else if(opcode[0]=='R'&&opcode[1]=='D')
        loc[now]=loc[now-1]+3;
    else if(opcode[0]=='R'&&opcode[1]=='S'&&opcode[2]=='U'&&opcode[3]=='B')
        loc[now]=loc[now-1]+3;
    else if(opcode[0]=='S'&&opcode[1]=='T'&&opcode[2]=='A')
        loc[now]=loc[now-1]+3;
    else if(opcode[0]=='S'&&opcode[1]=='T'&&opcode[2]=='B')
        loc[now]=loc[now-1]+3;
    else if(opcode[0]=='S'&&opcode[1]=='T'&&opcode[2]=='C'&&opcode[3]=='H')
        loc[now]=loc[now-1]+3;
    else if(opcode[0]=='S'&&opcode[1]=='T'&&opcode[2]=='L')
        loc[now]=loc[now-1]+3;
    else if(opcode[0]=='S'&&opcode[1]=='T'&&opcode[2]=='X')
        loc[now]=loc[now-1]+3;
    else if(opcode[0]=='S'&&opcode[1]=='U'&&opcode[2]=='B')
        loc[now]=loc[now-1]+3;
    else if(opcode[0]=='T'&&opcode[1]=='I'&&opcode[2]=='X'&&opcode[3]=='R')
        loc[now]=loc[now-1]+2;
    else if(opcode[0]=='T'&&opcode[1]=='I'&&opcode[2]=='X')
        loc[now]=loc[now-1]+3;
    else if(opcode[0]=='T'&&opcode[1]=='D')
        loc[now]=loc[now-1]+3;
    else if(opcode[0]=='W'&&opcode[1]=='D')
        loc[now]=loc[now-1]+3;
    else if(opcode[0]=='E'&&opcode[1]=='N'&&opcode[2]=='D')
        loc[now]=loc[now-1];
    else if(opcode[0]=='B'&&opcode[1]=='Y'&&opcode[2]=='T'&&opcode[3]=='E')
    {
        if(operand[0]=='X')
        {
            int t=2;
            while(operand[t]>='0'&&operand[t]<='9'||operand[t]>='A'&&operand[t]<='F')
            {
                t++;
            }
            t-=2;
            if(t%2==0)
            {
                t=t/2;
            }
            else
            {
                t=t/2+1;
            }
            loc[now]=loc[now-1]+t;
        }
        else if(operand[0]=='C')
        {
            int t=2;
            while(operand[t]>='0'&&operand[t]<='9'||operand[t]>='A'&&operand[t]<='Z'||operand[t]>='a'&&operand[t]<='z')
            {
                t++;
            }
            t-=2;
            loc[now]=loc[now-1]+t;
        }
    }
    else if(opcode[0]=='W'&&opcode[1]=='O'&&opcode[2]=='R'&&opcode[3]=='D')
        loc[now]=loc[now-1]+3;
    else if(opcode[0]=='R'&&opcode[1]=='E'&&opcode[2]=='S'&&opcode[3]=='W')
    {
        int t=0;
        int tt=0;
        int ttt=0;
        while(operand[t]>='0'&&operand[t]<='9')
        {
            t++;
        }
        int tm=t;
        for(int j=0; j<tm; j++)
        {
            t--;
            int a;
            tt=pow(10,t);
            a=(operand[j]-48)*tt;
            ttt+=a;
        }
        loc[now]=loc[now-1]+ttt*3;
    }
    else if(opcode[0]=='R'&&opcode[1]=='E'&&opcode[2]=='S'&&opcode[3]=='B')
    {
        int t=0;
        int tt=0;
        int ttt=0;
        while(operand[t]>='0'&&operand[t]<='9')
        {
            t++;
        }
        int tm=t;
        for(int j=0; j<tm; j++)
        {
            t--;
            int a;
            tt=pow(10,t);
            a=(operand[j]-'0')*tt;
            ttt+=a;
        }
        loc[now]=loc[now-1]+ttt;
    }
    else if(opcode[0]=='B'&&opcode[1]=='A'&&opcode[2]=='S'&&opcode[3]=='E')
    {
        loc[now]=loc[now-1];
        loc[now-1]=loc[now-2];
        base=now-1;
    }

    else if(opcode[0]=='L'&&opcode[1]=='T'&&opcode[2]=='O'&&opcode[3]=='R'&&opcode[4]=='G')
    {
        loc[now]=loc[now-1];
        //loc[now]=loc[now-1]+LDA_count;

        LtorgNow=now-1;
        Ltorg=loc[now];
        now++;
        loc[now]=loc[now-1]+LDA_count;
    }


    else if(opcode[0]=='E'&&opcode[1]=='Q'&&opcode[2]=='U')
    {
        pig=1;
        equ_count=loc[now-1];
        if(operand[0]=='*')
        {
            loc[now] = loc[now-1];
        }
        else
        {
            f1=true;
            char EQU1[10]= {};
            char EQU2[10]= {};
            int i=0;
            while(true)
            {
                if(operand[i]>='A'&&operand[i]<='Z')
                {
                    EQU1[i]=operand[i];
                    i++;
                }
                else if(operand[i]=='-')            //遇到-
                {
                    i++;
                    break;
                }
            }
            int EQU_count=0;
            while(true)
            {
                if(operand[i]>='A'&&operand[i]<='Z')
                {
                    EQU2[EQU_count]=operand[i];
                    EQU_count++;
                    i++;
                }
                else
                {
                    break;
                }
            }
            int loc1=0,loc2=0;
            for(int i=0; i<snum; i++)
            {
                if(strcmp(EQU1,s[i].name)==0)
                {
                    loc1 = s[i].address;
                    break;
                }
            }
            for(int j=0; j<snum; j++)
            {
                if(strcmp(EQU2,s[j].name)==0)
                {
                    loc2 = s[j].address;
                    break;
                }
            }
            loc[now-1] = loc1-loc2;
            loc[now] = loc[now-1];
        }
    }


    now++;
}

void set_symbol()
{
    if (opcode[0]=='S'&&opcode[1]=='T'&&opcode[2]=='A'&&opcode[3]=='R'&&opcode[4]=='T')
    {
        int i=0;
        while(label[i]!=' ')
        {
            s[snum].name[i]=label[i];
            i++;
        }

        s[snum].status= 'R';


        s[snum].address= loc[0];
        snum++;
    }
    else if(label[0]!='.'&&opcode[0]=='E'&&opcode[1]=='Q'&&opcode[2]=='U')
    {
        int i=0;
        while(label[i]!=' ')
        {
            s[snum].name[i]=label[i];
            i++;
        }
        if(f1)
        {
            s[snum].status= 'A';
        }
        else
        {
            s[snum].status= 'R';
        }
        s[snum].address= loc[now-1];
        snum++;
    }
    else if(label[0]!=' '&&label[0]!='.')
    {
        int i=0;
        while(label[i]!=' ')
        {
            s[snum].name[i]=label[i];
            i++;
        }
        s[snum].status= 'R';
        s[snum].address= loc[now-2];
        snum++;
    }

}

//郡
void Pass2()
{
    int disp, ZeroPading, Base, TA;
    char stri[6];
    for(int i=0; i<Num_Of_Lines+2; i++)
    {
        //王
        if(LINE[i].Opcode[0]=='S'&&LINE[i].Opcode[1]=='T'&&LINE[i].Opcode[2]=='A'&&LINE[i].Opcode[3]=='R'&&LINE[i].Opcode[4]=='T')
        {
            LINE[i].ObjectCode[0]='n';
            LINE[i].ObjectCode[1]='o';
            LINE[i].ObjectCode[2]='n';
            LINE[i].ObjectCode[3]='e';
        }
        //郡+廖
        else if(LINE[i].Opcode[0]=='S'&&LINE[i].Opcode[1]=='T'&&LINE[i].Opcode[2]=='L')
        {
            LINE[i].ObjectCode[0]='1';
            LINE[i].ObjectCode[1]='4';
            if(LINE[i].Operand[0]!='#'&&LINE[i].Operand[0]!='@')
            {
                LINE[i].ObjectCode[1]+=3;
                if(LINE[i].Operand[0]=='R'&&LINE[i].Operand[1]=='E'&&LINE[i].Operand[2]=='T'&&LINE[i].Operand[3]=='A'&&LINE[i].Operand[4]=='D'&&LINE[i].Operand[5]=='R')
                {
                    for(int j=0; j<snum; j++)
                    {
                        if(s[j].name[0]=='R'&&s[j].name[1]=='E'&&s[j].name[2]=='T'&&s[j].name[3]=='A'&&s[j].name[4]=='D'&&s[j].name[5]=='R')
                        {
                            disp = s[j].address-(LINE[i].LOC+3);
                        }

                        _itoa(disp, stri, 16);
                        ZeroPading = 4-strlen(stri);
                        for(int k=0; k<ZeroPading; k++)
                        {
                            LINE[i].ObjectCode[2+k]='0';
                        }

                        int m=0;
                        for(int k=ZeroPading+2; k<6; k++)
                        {
                            LINE[i].ObjectCode[k]=stri[m];
                            m++;
                        }
                    }
                    if(-2048 <= disp && disp <= 2047)
                        LINE[i].ObjectCode[2]='2';
                    else
                        LINE[i].ObjectCode[2]='4';
                }
            }
        }
        //郡+廖+鄭+張
        else if(LINE[i].Opcode[0]=='L'&&LINE[i].Opcode[1]=='D'&&LINE[i].Opcode[2]!='T'&&LINE[i].Opcode[2]!='C')
        {
            //鄭
            if(LINE[i].Opcode[2]=='B')
            {
                LINE[i].ObjectCode[0]='6';
                LINE[i].ObjectCode[1]='8';
                if(LINE[i].Operand[0]!='#'&&LINE[i].Operand[0]!='@')
                {

                }
                else if(LINE[i].Operand[0]=='#')//@ 或 # 或數字
                {
                    LINE[i].ObjectCode[1]+=1;
                    for(int j=0; j<snum; j++)
                    {
                        if(s[j].name[0]==LINE[i].Operand[1]&&s[j].name[1]==LINE[i].Operand[2]&&s[j].name[2]==LINE[i].Operand[3]&&s[j].name[3]==LINE[i].Operand[4]&&s[j].name[4]==LINE[i].Operand[5]&&s[j].name[5]==LINE[i].Operand[6])
                        {
                            disp = s[j].address - (LINE[i].LOC +3);
                            _itoa(disp, stri, 16);
                            ZeroPading = 3-strlen(stri);
                            for(int k=0; k<ZeroPading; k++)
                            {
                                LINE[i].ObjectCode[3+k]='0';
                            }

                            int m=0;
                            for(int k=ZeroPading+3; k<6; k++)
                            {
                                LINE[i].ObjectCode[k]=stri[m];
                                m++;
                            }

                            if(-2048 <= disp && disp <= 2047)
                                LINE[i].ObjectCode[2]='2';
                            break;
                        }
                    }
                }
            }
            //鄭
            else if(LINE[i].Opcode[2]=='A')
            {
                LINE[i].ObjectCode[0]='0';
                LINE[i].ObjectCode[1]='0';
                if(LINE[i].Operand[0]!='#'&&LINE[i].Operand[0]!='@'&&LINE[i].Operand[0]!='=')
                {
                    LINE[i].ObjectCode[1]+=3;
                    for(int j=0; j<snum; j++)
                    {
                        if(s[j].name[0]==toupper(LINE[i].Operand[0]) && s[j].name[1]==LINE[i].Operand[1]
                                && s[j].name[2]==LINE[i].Operand[2] && s[j].name[3]==LINE[i].Operand[3]
                                && s[j].name[4]==LINE[i].Operand[4] )
                        {
                            int total= 0;
                            if(LINE[i].Operand[5]=='+')
                            {

                                int k=6;

                                while(LINE[i].Operand[k]>='0'&&LINE[i].Operand[k]<='9')
                                {
                                    total = total*10 + (LINE[i].Operand[k]-'0');
                                    k++;
                                }

                            }

                            disp = s[j].address - (LINE[i].LOC +3) +total;
                            _itoa(disp, stri, 16);
                            ZeroPading = 3-strlen(stri);
                            for(int k=0; k<ZeroPading; k++)
                            {
                                LINE[i].ObjectCode[3+k]='0';
                            }

                            int m=0;
                            for(int k=ZeroPading+3; k<6; k++)
                            {
                                LINE[i].ObjectCode[k]=stri[m];
                                m++;
                            }

                            if(-2048 <= disp && disp <= 2047)
                                LINE[i].ObjectCode[2]='2';
                            break;
                        }
                    }
                }

                //張
                else //@ 或 # 或數字
                {
                    if(LINE[i].Operand[0]=='#') //#
                    {
                        LINE[i].ObjectCode[1]+=1;
                        int j=1;
                        int total=0;
                        while(LINE[i].Operand[j]>='0'&&LINE[i].Operand[j]<='9')
                        {
                            total = total*10 + (LINE[i].Operand[j]-'0');
                            j++;
                        }
                        _itoa(total, stri, 16);
                        ZeroPading = 4-strlen(stri);
                        for(int k=0; k<ZeroPading; k++)
                        {
                            LINE[i].ObjectCode[2+k]='0';
                        }

                        int m=0;
                        for(int k=ZeroPading+2; k<6; k++)
                        {
                            LINE[i].ObjectCode[k]=stri[m];
                            m++;
                        }
                    }
                    else if(LINE[i].Operand[0]=='=')
                    {
                        LINE[i].ObjectCode[0]='0';
                        LINE[i].ObjectCode[1]='3';
                        LINE[i].ObjectCode[2]='2';
                        disp = Ltorg- (LINE[i].LOC +3);
                        _itoa(disp, stri, 16);
                        ZeroPading = 3-strlen(stri);
                        for(int k=0; k<ZeroPading; k++)
                        {
                            LINE[i].ObjectCode[3+k]='0';
                        }

                        int m=0;
                        for(int k=ZeroPading+3; k<6; k++)
                        {
                            LINE[i].ObjectCode[k]=stri[m];
                            m++;
                        }
                    }
                }
            }
            else if(LINE[i].Opcode[2]=='S')
            {
                LINE[i].ObjectCode[0]='6';
                LINE[i].ObjectCode[1]='C';
                if(LINE[i].Operand[0]=='#')
                {
                    LINE[i].ObjectCode[1]+=1;

                    int j=1;
                    int total=0;
                    while(LINE[i].Operand[j]>='0'&&LINE[i].Operand[j]<='9')
                    {
                        total = total*10 + (LINE[i].Operand[j]-'0');
                        j++;
                    }
                    _itoa(total, stri, 16);
                    ZeroPading = 3-strlen(stri);
                    for(int k=0; k<ZeroPading; k++)
                    {
                        LINE[i].ObjectCode[3+k]='0';
                    }

                    int m=0;
                    for(int k=ZeroPading+3; k<6; k++)
                    {
                        LINE[i].ObjectCode[k]=stri[m];
                        m++;
                    }
                    if(-2048 <= disp && disp <= 2047)
                        LINE[i].ObjectCode[2]='2';

                }
            }

        }
        //廖
        else if(LINE[i].Opcode[0]=='B'&&LINE[i].Opcode[1]=='A'&&LINE[i].Opcode[2]=='S'&&LINE[i].Opcode[3]=='E')
        {
            LINE[i].ObjectCode[0]='n';
            LINE[i].ObjectCode[1]='o';
            LINE[i].ObjectCode[2]='n';
            LINE[i].ObjectCode[3]='e';
            for(int j=0; j<snum; j++)
            {
                if(s[j].name[0]==LINE[i].Operand[0] && s[j].name[1]==LINE[i].Operand[1]
                        && s[j].name[2]==LINE[i].Operand[2] && s[j].name[3]==LINE[i].Operand[3]
                        && s[j].name[4]==LINE[i].Operand[4] && s[j].name[5]==LINE[i].Operand[5])
                {
                    Base = s[j].address;
                }
            }
        }
        //郡+廖+王
        else if(LINE[i].Opcode[0]=='+') //format 4
        {
            LINE[i].ObjectCode[2]='1';

            if(LINE[i].Opcode[1]=='J'&&LINE[i].Opcode[2]=='S'&&LINE[i].Opcode[3]=='U'&&LINE[i].Opcode[4]=='B')
            {
                LINE[i].ObjectCode[0]='4';
                LINE[i].ObjectCode[1]='B';


                for(int j=0; j<snum; j++)
                {
                    if(s[j].name[0]==LINE[i].Operand[0] && s[j].name[1]==LINE[i].Operand[1] && s[j].name[2]==LINE[i].Operand[2] && s[j].name[3]==LINE[i].Operand[3] && s[j].name[4]==LINE[i].Operand[4] )
                    {
                        disp = s[j].address;
                        _itoa(disp, stri, 16);

                        ZeroPading = 5-strlen(stri);
                        for(int k=0; k<ZeroPading; k++)
                        {
                            LINE[i].ObjectCode[3+k]='0';
                        }

                        int m=0;
                        for(int k=ZeroPading+3; k<8; k++)
                        {
                            LINE[i].ObjectCode[k]=stri[m];
                            m++;
                        }

                        break;
                    }
                }
            }
            //王
            else if(LINE[i].Opcode[1]=='L'&&LINE[i].Opcode[2]=='D'&&LINE[i].Opcode[3]=='T')
            {
                LINE[i].ObjectCode[0]='7';
                LINE[i].ObjectCode[1]='4';
                if(LINE[i].Operand[0]=='#')
                {
                    LINE[i].ObjectCode[1]+=1;
                    for(int j=0; j<snum; j++)
                    {
                        if(s[j].name[0]==LINE[i].Operand[1] && s[j].name[1]==LINE[i].Operand[2]
                                && s[j].name[2]==LINE[i].Operand[3] && s[j].name[3]==LINE[i].Operand[4]
                                && s[j].name[4]==LINE[i].Operand[5] && s[j].name[5]==LINE[i].Operand[6])
                        {
                            disp = s[j].address;
                            _itoa(disp, stri, 16);
                            ZeroPading = 5-strlen(stri);
                            for(int k=0; k<ZeroPading; k++)
                            {
                                LINE[i].ObjectCode[3+k]='0';
                            }

                            int m=0;
                            for(int k=ZeroPading+3; k<8; k++)
                            {
                                LINE[i].ObjectCode[k]=stri[m];
                                m++;
                            }

                            if(-2048 <= disp && disp <= 2047)
                                LINE[i].ObjectCode[2]='2';

                            break;
                        }
                    }
                }
            }
        }
        //張+鄭
        else if(LINE[i].Opcode[0]=='C'&&LINE[i].Opcode[1]=='O'&&LINE[i].Opcode[2]=='M'&&LINE[i].Opcode[3]=='P'&&LINE[i].Opcode[4]!='R')
        {
            LINE[i].ObjectCode[0]='2';
            LINE[i].ObjectCode[1]='8';
            if(LINE[i].Operand[0]=='#')
            {
                LINE[i].ObjectCode[1]+=1;
                LINE[i].ObjectCode[2]='0';

                int j=1;
                int total=0;

                while(LINE[i].Operand[j]>='0'&&LINE[i].Operand[j]<='9')
                {
                    total = total*10 + (LINE[i].Operand[j]-'0');
                    j++;
                }
                _itoa(total, stri, 16);
                ZeroPading = 3-strlen(stri);
                for(int k=0; k<ZeroPading; k++)
                {
                    LINE[i].ObjectCode[3+k]='0';
                }

                int m=0;
                for(int k=ZeroPading+3; k<6; k++)
                {
                    LINE[i].ObjectCode[k]=stri[m];
                    m++;
                }
            }

        }
        //張
        else if(LINE[i].Opcode[0]=='C'&&LINE[i].Opcode[1]=='O'&&LINE[i].Opcode[2]=='M'&&LINE[i].Opcode[3]=='P'&&LINE[i].Opcode[4]=='R')
        {
            LINE[i].ObjectCode[0]='A';
            LINE[i].ObjectCode[1]='0';

            if(LINE[i].Operand[0]=='A')
                LINE[i].ObjectCode[2]='0';
            if(LINE[i].Operand[2]=='S')
                LINE[i].ObjectCode[3]='4';
        }
        //郡+廖
        else if(LINE[i].Opcode[0]=='J'&&LINE[i].Opcode[1]=='E'&&LINE[i].Opcode[2]=='Q')
        {
            LINE[i].ObjectCode[0]='3';
            LINE[i].ObjectCode[1]='0';
            if(LINE[i].Operand[0]!='#'&&LINE[i].Operand[0]!='@')
            {
                LINE[i].ObjectCode[1]+=3;
                for(int j=0; j<snum; j++)
                {
                    if(s[j].name[0]==LINE[i].Operand[0] && s[j].name[1]==LINE[i].Operand[1]
                            && s[j].name[2]==LINE[i].Operand[2] && s[j].name[3]==LINE[i].Operand[3]
                            && s[j].name[4]==LINE[i].Operand[4] && s[j].name[5]==LINE[i].Operand[5])
                    {
                        disp = s[j].address - (LINE[i].LOC +3);
                        _itoa(disp, stri, 16);
                        if(stri[0]=='f')
                        {
                            stri[0]=stri[5];
                            stri[1]=stri[6];
                            stri[2]=stri[7];
                            stri[3]='\0';
                        }
                        ZeroPading = 3-strlen(stri);
                        for(int k=0; k<ZeroPading; k++)
                        {
                            LINE[i].ObjectCode[3+k]='0';
                        }

                        int m=0;
                        for(int k=ZeroPading+3; k<6; k++)
                        {
                            LINE[i].ObjectCode[k]=stri[m];
                            m++;
                        }

                        if(-2048 <= disp && disp <= 2047)
                            LINE[i].ObjectCode[2]='2';

                        break;
                    }
                }
            }
        }

        //王+張+鄭
        else if(LINE[i].Opcode[0]=='J'&&LINE[i].Opcode[1]!='E'&&LINE[i].Opcode[1]!='L')
        {
            LINE[i].ObjectCode[0]='3';
            LINE[i].ObjectCode[1]='C';
            if(LINE[i].Operand[0]!='#'&&LINE[i].Operand[0]!='@')
            {
                LINE[i].ObjectCode[1]+=3;
                for(int j=0; j<snum; j++)
                {
                    if(s[j].name[0]==LINE[i].Operand[0] && s[j].name[1]==LINE[i].Operand[1]
                            && s[j].name[2]==LINE[i].Operand[2] && s[j].name[3]==LINE[i].Operand[3]
                            && s[j].name[4]==LINE[i].Operand[4] )
                    {
                        disp = s[j].address - (LINE[i].LOC +3);
                        _itoa(disp, stri, 16);
                        if(stri[0]=='f')
                        {
                            stri[0]=stri[5];
                            stri[1]=stri[6];
                            stri[2]=stri[7];
                            stri[3]='\0';
                        }
                        ZeroPading = 3-strlen(stri);
                        for(int k=0; k<ZeroPading; k++)
                        {
                            LINE[i].ObjectCode[3+k]='0';
                        }

                        int m=0;
                        for(int k=ZeroPading+3; k<6; k++)
                        {
                            LINE[i].ObjectCode[k]=stri[m];
                            m++;
                        }

                        if(-2048 <= disp && disp <= 2047)
                            LINE[i].ObjectCode[2]='2';
                        break;
                    }
                }
            }
            //王
            else //@
            {
                LINE[i].ObjectCode[1]+=2;
                for(int j=0; j<snum; j++)
                {
                    if(s[j].name[0]==LINE[i].Operand[1] && s[j].name[1]==LINE[i].Operand[2]
                            && s[j].name[2]==LINE[i].Operand[3] && s[j].name[3]==LINE[i].Operand[4]
                            && s[j].name[4]==LINE[i].Operand[5] && s[j].name[5]==LINE[i].Operand[6] )
                    {
                        disp = s[j].address - (LINE[i].LOC +3);
                        _itoa(disp, stri, 16);
                        ZeroPading = 3-strlen(stri);
                        for(int k=0; k<ZeroPading; k++)
                        {
                            LINE[i].ObjectCode[3+k]='0';
                        }

                        int m=0;
                        for(int k=ZeroPading+3; k<6; k++)
                        {
                            LINE[i].ObjectCode[k]=stri[m];
                            m++;
                        }

                        if(-2048 <= disp && disp <= 2047)
                            LINE[i].ObjectCode[2]='2';

                        break;
                    }
                }
            }
        }
        //張+鄭
        else if(LINE[i].Opcode[0]=='S'&&LINE[i].Opcode[1]=='T'&&LINE[i].Opcode[2]=='A')
        {
            LINE[i].ObjectCode[0]='0';
            LINE[i].ObjectCode[1]='C';
            if(LINE[i].Operand[0]!='#'&&LINE[i].Operand[0]!='@')
            {
                LINE[i].ObjectCode[1]+=3;
                for(int j=0; j<snum; j++)
                {
                    if(s[j].name[0]==LINE[i].Operand[0] && s[j].name[1]==LINE[i].Operand[1]
                            && s[j].name[2]==LINE[i].Operand[2] && s[j].name[3]==LINE[i].Operand[3]
                            && s[j].name[4]==LINE[i].Operand[4] )
                    {
                        disp = s[j].address - (LINE[i].LOC +3);
                        _itoa(disp, stri, 16);
                        ZeroPading = 3-strlen(stri);
                        for(int k=0; k<ZeroPading; k++)
                        {
                            LINE[i].ObjectCode[3+k]='0';
                        }

                        int m=0;
                        for(int k=ZeroPading+3; k<6; k++)
                        {
                            LINE[i].ObjectCode[k]=stri[m];
                            m++;
                        }

                        if(-2048 <= disp && disp <= 2047)
                            LINE[i].ObjectCode[2]='2';

                        break;
                    }
                }
            }
        }
        //張
        else if(LINE[i].Opcode[0]=='L'&&LINE[i].Opcode[1]=='T'&&LINE[i].Opcode[2]=='O'&&LINE[i].Opcode[3]=='R'&&LINE[i].Opcode[4]=='G')
        {
            LINE[i].ObjectCode[0]='n';
            LINE[i].ObjectCode[1]='o';
            LINE[i].ObjectCode[2]='n';
            LINE[i].ObjectCode[3]='e';
            LINE[i+1].ObjectCode[0]='4';
            LINE[i+1].ObjectCode[1]='5';
            LINE[i+1].ObjectCode[2]='4';
            LINE[i+1].ObjectCode[3]='F';
            LINE[i+1].ObjectCode[4]='4';
            LINE[i+1].ObjectCode[5]='6';
            i++;
        }
        //張
        else if(LINE[i].Opcode[0]=='R'&&LINE[i].Opcode[1]=='E'&&LINE[i].Opcode[2]=='S'&&LINE[i].Opcode[3]=='W')
        {
            LINE[i].ObjectCode[0]='n';
            LINE[i].ObjectCode[1]='o';
            LINE[i].ObjectCode[2]='n';
            LINE[i].ObjectCode[3]='e';
        }
        //張
        else if(LINE[i].Opcode[0]=='R'&&LINE[i].Opcode[1]=='E'&&LINE[i].Opcode[2]=='S'&&LINE[i].Opcode[3]=='B')
        {
            LINE[i].ObjectCode[0]='n';
            LINE[i].ObjectCode[1]='o';
            LINE[i].ObjectCode[2]='n';
            LINE[i].ObjectCode[3]='e';
        }
        //張
        else if(LINE[i].Opcode[0]=='E'&&LINE[i].Opcode[1]=='Q'&&LINE[i].Opcode[2]=='U')
        {
            LINE[i].ObjectCode[0]='n';
            LINE[i].ObjectCode[1]='o';
            LINE[i].ObjectCode[2]='n';
            LINE[i].ObjectCode[3]='e';
        }
        //鄭
        else if(LINE[i].Label[0]=='.')
        {
            continue;
        }
        //鄭
        else if(LINE[i].Opcode[0]=='C'&&LINE[i].Opcode[1]=='L'&&LINE[i].Opcode[2]=='E'&&LINE[i].Opcode[3]=='A'&&LINE[i].Opcode[4]=='R')
        {
            LINE[i].ObjectCode[0]='B';
            LINE[i].ObjectCode[1]='4';

            if(LINE[i].Operand[0]=='X')
                LINE[i].ObjectCode[2]='1';
            else if(LINE[i].Operand[0]=='A')
                LINE[i].ObjectCode[2]='0';
            else if(LINE[i].Operand[0]=='S')
                LINE[i].ObjectCode[2]='4';

            LINE[i].ObjectCode[3]='0';
        }
        //郡+廖
        else if(LINE[i].Opcode[0]=='T'&&LINE[i].Opcode[1]=='D')
        {
            LINE[i].ObjectCode[0]='E';
            LINE[i].ObjectCode[1]='0';

            if(LINE[i].Operand[0]!='#'&&LINE[i].Operand[0]!='@'&&LINE[i].Operand[0]!='=')
            {
                LINE[i].ObjectCode[1]+=3;
                for(int j=0; j<snum; j++)
                {
                    if(s[j].name[0]==LINE[i].Operand[0] && s[j].name[1]==LINE[i].Operand[1]
                            && s[j].name[2]==LINE[i].Operand[2] && s[j].name[3]==LINE[i].Operand[3]
                            && s[j].name[4]==LINE[i].Operand[4] )
                    {
                        disp = s[j].address - (LINE[i].LOC +3);
                        _itoa(disp, stri, 16);
                        //cout << hex << s[j].address << " " << LINE[i].LOC +3 << endl;
                        ZeroPading = 3-strlen(stri);
                        for(int k=0; k<ZeroPading; k++)
                        {
                            LINE[i].ObjectCode[3+k]='0';
                        }

                        int m=0;
                        for(int k=ZeroPading+3; k<6; k++)
                        {
                            LINE[i].ObjectCode[k]=stri[m];
                            m++;
                        }

                        if(-2048 <= disp && disp <= 2047)
                            LINE[i].ObjectCode[2]='2';

                        break;
                    }
                }
            }
            else if(LINE[i].Operand[0]=='=')
            {
                LINE[i].ObjectCode[1]+=3;

                TA = loc[now-1];
                disp = TA - (LINE[i].LOC +3);

                _itoa(disp, stri, 16);
                ZeroPading = 3-strlen(stri);
                for(int k=0; k<ZeroPading; k++)
                {
                    LINE[i].ObjectCode[3+k]='0';
                }

                int m=0;
                for(int k=ZeroPading+3; k<6; k++)
                {
                    LINE[i].ObjectCode[k]=stri[m];
                    m++;
                }

                if(-2048 <= disp && disp <= 2047)
                    LINE[i].ObjectCode[2]='2';


            }
        }
        //郡+廖
        else if(LINE[i].Opcode[0]=='R'&&LINE[i].Opcode[1]=='D')
        {
            LINE[i].ObjectCode[0]='D';
            LINE[i].ObjectCode[1]='8';

            if(LINE[i].Operand[0]!='#'&&LINE[i].Operand[0]!='@')
            {
                LINE[i].ObjectCode[1]='B';
                for(int j=0; j<snum; j++)
                {
                    if(s[j].name[0]==LINE[i].Operand[0] && s[j].name[1]==LINE[i].Operand[1]
                            && s[j].name[2]==LINE[i].Operand[2] && s[j].name[3]==LINE[i].Operand[3]
                            && s[j].name[4]==LINE[i].Operand[4] )
                    {
                        disp = s[j].address - (LINE[i].LOC +3);
                        _itoa(disp, stri, 16);
                        ZeroPading = 3-strlen(stri);
                        for(int k=0; k<ZeroPading; k++)
                        {
                            LINE[i].ObjectCode[3+k]='0';
                        }

                        int m=0;
                        for(int k=ZeroPading+3; k<6; k++)
                        {
                            LINE[i].ObjectCode[k]=stri[m];
                            m++;
                        }

                        if(-2048 <= disp && disp <= 2047)
                            LINE[i].ObjectCode[2]='2';

                        break;
                    }
                }
            }

        }
        //郡+廖
        else if(LINE[i].Opcode[0]=='W'&&LINE[i].Opcode[1]=='D')
        {
            LINE[i].ObjectCode[0]='D';
            LINE[i].ObjectCode[1]='C';

            if(LINE[i].Operand[0]!='#'&&LINE[i].Operand[0]!='@')
            {
                LINE[i].ObjectCode[1]+=3;

                TA = loc[now-1];
                disp = TA - (LINE[i].LOC +3);

                _itoa(disp, stri, 16);
                ZeroPading = 3-strlen(stri);
                for(int k=0; k<ZeroPading; k++)
                {
                    LINE[i].ObjectCode[3+k]='0';
                }

                int m=0;
                for(int k=ZeroPading+3; k<6; k++)
                {
                    LINE[i].ObjectCode[k]=stri[m];
                    m++;
                }

                if(-2048 <= disp && disp <= 2047)
                    LINE[i].ObjectCode[2]='2';
            }
        }

        //王
        else if(LINE[i].Opcode[0]=='S'&&LINE[i].Opcode[1]=='T'&&LINE[i].Opcode[2]=='C'&&LINE[i].Opcode[3]=='H')
        {
            LINE[i].ObjectCode[0]='5';
            LINE[i].ObjectCode[1]='4';
            if(LINE[i].Operand[0]!='#'&&LINE[i].Operand[0]!='@')
            {
                LINE[i].ObjectCode[1]+=3;
                for(int j=0; j<snum; j++)
                {
                    if(s[j].name[0]==LINE[i].Operand[0] && s[j].name[1]==LINE[i].Operand[1]
                            && s[j].name[2]==LINE[i].Operand[2] && s[j].name[3]==LINE[i].Operand[3]
                            && s[j].name[4]==LINE[i].Operand[4] && s[j].name[5]==LINE[i].Operand[5]
                            && LINE[i].Operand[7]=='X')
                    {
                        disp = s[j].address - (LINE[i].LOC +3);
                        if(-2048 <= disp && disp <= 2047)
                            LINE[i].ObjectCode[2]='A';
                        else
                            LINE[i].ObjectCode[2]='C';  //base relative

                        disp = s[j].address - Base + X;
                        _itoa(disp, stri, 16);
                        ZeroPading = 3-strlen(stri);
                        for(int k=0; k<ZeroPading; k++)
                        {
                            LINE[i].ObjectCode[3+k]='0';
                        }

                        int m=0;
                        for(int k=ZeroPading+3; k<6; k++)
                        {
                            LINE[i].ObjectCode[k]=stri[m];
                            m++;
                        }

                        break;
                    }
                }
            }
        }
        //張
        else if(LINE[i].Opcode[0]=='T'&&LINE[i].Opcode[1]=='I'&&LINE[i].Opcode[2]=='X'&&LINE[i].Opcode[3]=='R')
        {
            LINE[i].ObjectCode[0]='B';
            LINE[i].ObjectCode[1]='8';
            if(LINE[i].Operand[0]=='T')
                LINE[i].ObjectCode[2]='5';
            LINE[i].ObjectCode[3]='0';
        }
        //王+張+鄭
        else if(LINE[i].Opcode[0]=='J'&&LINE[i].Opcode[1]=='L'&&LINE[i].Opcode[2]=='T')
        {
            LINE[i].ObjectCode[0]='3';
            LINE[i].ObjectCode[1]='8';

            if(LINE[i].Operand[0]!='#'&&LINE[i].Operand[0]!='@')
            {
                LINE[i].ObjectCode[1]='B';
                for(int j=0; j<snum; j++)
                {
                    if(s[j].name[0]==toupper(LINE[i].Operand[0]) && s[j].name[1]==toupper(LINE[i].Operand[1])
                            && s[j].name[2]==toupper(LINE[i].Operand[2]) && s[j].name[3]==toupper(LINE[i].Operand[3])
                            && s[j].name[4]==toupper(LINE[i].Operand[4]) )
                    {

                        disp = s[j].address - (LINE[i].LOC +3);

                        _itoa(disp, stri, 16);

                        if(stri[0]=='f')
                        {
                            stri[0]=stri[5];
                            stri[1]=stri[6];
                            stri[2]=stri[7];
                            stri[3]='\0';
                        }

                        ZeroPading = 3-strlen(stri);
                        for(int k=0; k<ZeroPading; k++)
                        {
                            LINE[i].ObjectCode[3+k]='0';
                        }

                        int m=0;
                        for(int k=ZeroPading+3; k<6; k++)
                        {
                            LINE[i].ObjectCode[k]=stri[m];
                            m++;
                        }

                        if(-2048 <= -22 && -22 <= 2047)
                        {

                            LINE[i].ObjectCode[2]='2';
                        }
                        break;
                    }
                }
            }
        }
        //郡+廖
        else if(LINE[i].Opcode[0]=='S'&&LINE[i].Opcode[1]=='T'&&LINE[i].Opcode[2]=='X')
        {
            LINE[i].ObjectCode[0]='1';
            LINE[i].ObjectCode[1]='0';

            if(LINE[i].Operand[0]!='#'&&LINE[i].Operand[0]!='@')
            {
                LINE[i].ObjectCode[1]='3';
                for(int j=0; j<snum; j++)
                {
                    if(s[j].name[0]==LINE[i].Operand[0] && s[j].name[1]==LINE[i].Operand[1]
                            && s[j].name[2]==LINE[i].Operand[2] && s[j].name[3]==LINE[i].Operand[3]
                            && s[j].name[4]==LINE[i].Operand[4] && s[j].name[5]==LINE[i].Operand[5])
                    {
                        disp = s[j].address - (LINE[i].LOC +3);

                        if(2048 <= disp && disp <= 2047)
                            LINE[i].ObjectCode[2]='2';
                        else
                            LINE[i].ObjectCode[2]='4';

                        disp = s[j].address - Base;
                        _itoa(disp, stri, 16);
                        ZeroPading = 3-strlen(stri);
                        for(int k=0; k<ZeroPading; k++)
                        {
                            LINE[i].ObjectCode[3+k]='0';
                        }

                        int m=0;
                        for(int k=ZeroPading+3; k<6; k++)
                        {
                            LINE[i].ObjectCode[k]=stri[m];
                            m++;
                        }
                        break;
                    }
                }
            }
        }
        //鄭
        else if(LINE[i].Opcode[0]=='R'&&LINE[i].Opcode[1]=='S'&&LINE[i].Opcode[2]=='U'&&LINE[i].Opcode[3]=='B')
        {
            LINE[i].ObjectCode[0]='4';
            LINE[i].ObjectCode[1]='C';

            if(LINE[i].Operand[0]!='#'&&LINE[i].Operand[0]!='@')
            {
                LINE[i].ObjectCode[1]+=3;
                if(LINE[i].Operand[0]!=' ')
                {
                    LINE[i].ObjectCode[2]='0';
                    LINE[i].ObjectCode[3]='0';
                    LINE[i].ObjectCode[4]='0';
                    LINE[i].ObjectCode[5]='0';
                }
            }
        }
        //張
        else if(LINE[i].Opcode[0]=='B'&&LINE[i].Opcode[1]=='Y'&&LINE[i].Opcode[2]=='T'&&LINE[i].Opcode[3]=='E')
        {
            //****
            if(LINE[i].Operand[2]=='F'&&LINE[i].Operand[3]=='1')
            {
                LINE[i].ObjectCode[0]='F';
                LINE[i].ObjectCode[1]='1';
            }
        }
        //張+王+鄭
        else if(LINE[i].Opcode[0]=='L'&&LINE[i].Opcode[1]=='D'&&LINE[i].Opcode[2]=='T')
        {
            LINE[i].ObjectCode[0]='7';
            LINE[i].ObjectCode[1]='4';

            if(LINE[i].Operand[0]!='#'&&LINE[i].Operand[0]!='@')
            {
                LINE[i].ObjectCode[1]+=3;
                for(int j=0; j<snum; j++)
                {
                    if(s[j].name[0]==LINE[i].Operand[0] && s[j].name[1]==toupper(LINE[i].Operand[1])
                            && s[j].name[2]==toupper(LINE[i].Operand[2]) && s[j].name[3]==toupper(LINE[i].Operand[3])
                            && s[j].name[4]==toupper(LINE[i].Operand[4]) && s[j].name[5]==toupper(LINE[i].Operand[5]))
                    {
                        disp = s[j].address - (LINE[i].LOC +3);
                        if(-2048 <= disp && disp <= 2047)
                            LINE[i].ObjectCode[2]='2';
                        else
                            LINE[i].ObjectCode[2]='4';

                        disp = s[j].address - Base;
                        _itoa(disp, stri, 16);
                        ZeroPading = 3-strlen(stri);
                        for(int k=0; k<ZeroPading; k++)
                        {
                            LINE[i].ObjectCode[3+k]='0';
                        }

                        int m=0;
                        for(int k=ZeroPading+3; k<6; k++)
                        {
                            LINE[i].ObjectCode[k]=stri[m];
                            m++;
                        }

                        break;
                    }
                }
            }
        }
        //張+王+鄭
        else if(LINE[i].Opcode[0]=='L'&&LINE[i].Opcode[1]=='D'&&LINE[i].Opcode[2]=='C'&&LINE[i].Opcode[3]=='H')
        {
            LINE[i].ObjectCode[0]='5';
            LINE[i].ObjectCode[1]='0';
            if(LINE[i].Operand[0]!='#'&&LINE[i].Operand[0]!='@')
            {
                LINE[i].ObjectCode[1]+=3;
                for(int j=0; j<snum; j++)
                {
                    if(s[j].name[0]==toupper(LINE[i].Operand[0]) && s[j].name[1]==toupper(LINE[i].Operand[1])
                            && s[j].name[2]==toupper(LINE[i].Operand[2]) && s[j].name[3]==toupper(LINE[i].Operand[3])
                            && s[j].name[4]==toupper(LINE[i].Operand[4]) && s[j].name[5]==toupper(LINE[i].Operand[5])
                            && LINE[i].Operand[7]=='X')
                    {
                        disp = s[j].address - (LINE[i].LOC +3);
                        if(-2048 <= disp && disp <= 2047)
                            LINE[i].ObjectCode[2]='A';
                        else
                            LINE[i].ObjectCode[2]='C';  //base relative

                        disp = s[j].address - Base;
                        _itoa(disp, stri, 16);
                        ZeroPading = 3-strlen(stri);
                        for(int k=0; k<ZeroPading; k++)
                        {
                            LINE[i].ObjectCode[3+k]='0';
                        }

                        int m=0;
                        for(int k=ZeroPading+3; k<6; k++)
                        {
                            LINE[i].ObjectCode[k]=stri[m];
                            m++;
                        }

                        break;
                    }
                }
            }
        }
        //鄭
        else if(LINE[i].Opcode[0]=='E'&&LINE[i].Opcode[1]=='N'&&LINE[i].Opcode[2]=='D')
        {
            LINE[i].ObjectCode[0]='n';
            LINE[i].ObjectCode[1]='o';
            LINE[i].ObjectCode[2]='n';
            LINE[i].ObjectCode[3]='e';
            LINE[i+1].ObjectCode[0]='0';
            LINE[i+1].ObjectCode[1]='5';
            i++;
        }
    }
}

//王+鄭
void ObjCodeDump()
{
    for(int i=0; i<now-1; i++)
    {
        if(i==base)
            cout << dec << setw(2) << i+1 << " LOC：      " << LINE[i].ObjectCode << endl;
        else if(i==Ltorg)
            cout << dec << setw(2) << i+1 << " LOC：      " << LINE[i].ObjectCode << endl;
        else
            cout << dec << setw(2) << i+1 << " LOC：" << hex << setw(4) << setfill('0')<< loc[i]
                 << "  " << LINE[i].ObjectCode << endl;
    }
}

//王+鄭
void GetLineLoc()
{
    for(int i=0; i<now-1; i++)
    {
        LINE[i].LOC = loc[i];
    }
}

//main修改：郡+
//main報告後修改新增寫檔：廖
int main()
{
    str="";
    while(getline(cin, str))
    {
        f1=false;
        reset();
        setloc();
        set_symbol();
        str="";

        Num_Of_Lines++;
    }
    GetLineLoc();
    Pass2();

    cout<<"== Symbol Table =="<<endl;
    for(int i=0; i<snum; i++)
    {
        cout<<s[i].name<<" "<<s[i].status<<" "<<hex << setw(4) << setfill('0')<<s[i].address<<endl;
    }
    cout<<endl;
    cout<<"== Location Counter =="<<endl;
    for(int i=0; i<now; i++)
    {
        cout << "16進位： " << hex << setw(4) << setfill('0')<< loc[i]<< endl;
    }

    cout<<"== Object Code =="<<endl;
    ObjCodeDump();
}
