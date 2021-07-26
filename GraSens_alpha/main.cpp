#include <iostream>
#include <conio.h>
#include <cstring>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

using namespace std;

char plansza[100][100];
int n=25;
float difficulty=0.2;//max 2n-2
int liczba_elementow=5;
int liczba_pol=n*n;
int zycia1=3;
int zycia=zycia1;
int liczba_bomb=0;
char road='#', bomb='X', nothing=' ', player=1 ,crossed='*', secret='$';
int q=0;
int w=0;
int wtf;
bool pauza_obecna=false;

struct _menu{
    char element[32];       // STRUKTURA MENU
}_Menu[10];

struct _punkt{
    int x;                  // STRUKTURA OPCJI MENU
    int y;
};

void generuj_plansze();                                     // WCZESNY ZAPIS FUNKCJI

void rysuj_plansze();

void rysuj_plansze1();

void drukuj_menu(_menu t[], int poz, int licz_el);

void menu();

void you_win(){
    system("CLS");                                           // WYGRANA
cout << "You Win" << endl;
cout << "Achievement get!" << endl;
pauza_obecna=false;
system("pause");
q=0;
w=0;
menu();}

void game_over(){
system("CLS");
cout << "GAME OVER" << endl;                                //PRZEGRANA
q=0;
w=0;
pauza_obecna=false;
system("pause");
menu();

}

void player_movement(){
 char klik;
        int poz;
        int p;
        int u;
        int l;
        l:
        int x=q;
        int y=w;
        int pauza;

do{     klik=getch();
        plansza[q][w]=crossed;
        switch(klik){
            case 77:
                        w++;
                     break;
            case 80:
                        q++;
                    break;
            case 72:
                        q--;
                    break;
            case 75:
                        w--;
                    break;
            case 27:
                    goto pauza;
                    break;
            case 113:zycia--;
                rysuj_plansze1();
                break;
            }
        if (plansza[q][w]==secret) zycia=zycia+5;
        if (q==n) {q--; goto l;}
        if (w==n) {w--; goto l;}
        if (q<0) {q++; goto l;}
        if (w<0) {w++; goto l;}
        if (plansza[q][w]==bomb) {zycia=zycia-1;}
        if (zycia==0) goto u;
        if (q==n-1 & w==n-1){goto p;}
        plansza[q][w]=player;
        rysuj_plansze();
}while (q!=n-1 | w!=n-1);
 if (1==2){   p:
   you_win();}
if (1==2){ u:
game_over();}
if (1==2){pauza:
        pauza_obecna=true;
menu();
    }
}

int main(){
    srand(time(NULL));
    menu();
    cout << "Brawo, dotarles do mety!";
    return 0;
}

void menu(){
    system("CLS");
    char klik;
    int poz=0;
    strcpy(_Menu[0].element,"Nowa gra");
    strcpy(_Menu[1].element,"Kontynuacja");
    strcpy(_Menu[2].element,"Zapisz obecna gre");
    strcpy(_Menu[3].element,"Odczyt");
    strcpy(_Menu[4].element,"Koniec");

    /*for(int i=0; i<256;i++){
    cout <<i<<"/: "<<char(i)<<" :/";
        if ((i+1)%10==0) cout << endl;
    }
    cin >> wtf;*/
    drukuj_menu(_Menu, poz, liczba_elementow);

    do{
        klik=getch();
        switch(klik){
            case 72: poz--;
                     break;
            case 80: poz++;
                    break;
            }
            if(poz<0) poz+=liczba_elementow;
            else poz%=liczba_elementow;
            drukuj_menu(_Menu, poz, liczba_elementow);
        if(klik==13){
            cout<<"Wcisnieto: "<<_Menu[poz].element<<endl;
            switch(poz){
                case 0: q=0; w=0; zycia=zycia1;
                        system("CLS");
                        generuj_plansze();
                        rysuj_plansze1();
                case 4: exit(0);
                case 1: pauza_obecna=false;
                        plansza[q][w]=player;
                        rysuj_plansze();
            }
        }
    }while (klik!=27);

}

void drukuj_menu(_menu t[], int poz, int licz_el){
    system("CLS");
    if (pauza_obecna==true) {cout << "--ZAPAUZOWANO GRE--" << endl<<endl; }
    for(int i=0; i<licz_el; i++){
        if(i==poz) cout<<"*";
        else cout<<" ";
        cout<<t[i].element<<endl;
    }

}

void generuj_plansze(){
    bool t;
    int x=0, y=0;
    int k=n*n-1;

    _punkt lista[n*n];

    for(int xb=0; xb<n; xb++)
        for(int yb=0; yb<n; yb++){
            lista[xb+yb*n].x=xb;
            lista[xb+yb*n].y=yb;
        }

    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++) plansza[i][j]=nothing;

    plansza[x][y]=player;
    swap(lista[x+y*n],lista[k]);
    k--;
    while(x!=n-1 || y!=n-1){
        t=rand()%2;
        if(t)x++;
        else y++;
        if(x>=n || y>=n){
            if(x>=n) x=n-1;
            if(y>=n) y=n-1;
        }else{
            plansza[x][y]=road;
            swap(lista[x+y*n].x,lista[k].x);
            swap(lista[x+y*n].y,lista[k].y);
            k--;
        }
    }
    int p;
    int r;
    for(int i=0; i<liczba_pol*difficulty; i++){
        p:
        r=rand()%k+1;
        if (plansza[lista[r].x][lista[r].y]!=road && plansza[lista[r].x][lista[r].y]!=player ){
                plansza[lista[r].x][lista[r].y]=bomb;
        }
        if (plansza[lista[r].x][lista[r].y]==road && plansza[lista[r].x][lista[r].y]==player) goto p;
        swap(lista[r].x,lista[k].x);
        swap(lista[r].y,lista[k].y);
        k--;

    }
int x1;
int y1;
bool sekret=false;
do{x1=rand()%n;
y1=rand()%n;
if (plansza[x1][y1]!=bomb & plansza[x1][y1]!=player ){plansza[x1][y1]=secret; sekret=true;}
}while(sekret!=true);
}

void rysuj_plansze(){
    system("CLS");                                              //FAKSTYCZNY STATUS EKRANU

     //KOLORY TEKSTU I T£A
    HANDLE hOut;
                                                                                                                                                                                hOut=GetStdHandle(STD_OUTPUT_HANDLE);
    //SetConsoleTextAttribute(hOut,FOREGROUND_RED); //kolor tekstu
    //SetConsoleTextAttribute(hOut,BACKGROUND_INTENSITY); //kolor t³a
    liczba_bomb=0;
                                                                                                                                                                                SetConsoleTextAttribute(hOut,FOREGROUND_GREEN);
    cout << "+";
                                                                                                                                                                                SetConsoleTextAttribute(hOut,7);
    for (int lengh=0;lengh<=n-1;lengh++){
                                                                                                                                                                                    SetConsoleTextAttribute(hOut,FOREGROUND_GREEN);
        cout << "-";}
    cout << "+";
    cout << endl;
                                                                                                                                                                            SetConsoleTextAttribute(hOut,7);
    for(int x=0; x<n; x++){
                                                                                                                                                                                        SetConsoleTextAttribute(hOut,FOREGROUND_GREEN);
    cout <<"|";
                                                                                                                                                                                SetConsoleTextAttribute(hOut,7);
        for(int y=0; y<n; y++) {if (plansza[x][y]==player){SetConsoleTextAttribute(hOut,FOREGROUND_RED);}
                                if (plansza[x][y]!=road & plansza[x][y]!=bomb & plansza[x][y]!=secret){
                                cout<< plansza[x][y];}
                                else cout << " ";
                                if (plansza[x][y]==player){SetConsoleTextAttribute(hOut,7);}
                                if (plansza[x][y]==bomb) liczba_bomb++;}
                                                                                                                                                                                    SetConsoleTextAttribute(hOut,FOREGROUND_GREEN);
        cout<<"|"<<endl;
                                                                                                                                                                                    SetConsoleTextAttribute(hOut,7);
    }
                                                                                                                                                                                SetConsoleTextAttribute(hOut,FOREGROUND_GREEN);
    cout << "+";
    for(int x=0; x<n; x++) cout<<"-";
    cout<<"+"<<endl;
                                                                                                                                                                                SetConsoleTextAttribute(hOut,7);
                                                                                                                                                                                SetConsoleTextAttribute(hOut,FOREGROUND_RED);
    for (int i=zycia-1;i>=0;i--)
        cout << " <3 ";
                                                                                                                                                                                SetConsoleTextAttribute(hOut,7);
    cout << endl;
    cout << "Liczba bomb na planszy: " << liczba_bomb;
    cout << endl;
    cout << "Wcisnij Q aby pokazac bomby...    (Koszt: 1 zycie)";
    cout << endl;
    cout << "Wcisnij ESC aby zapauzowac...";
    player_movement();
}

void rysuj_plansze1(){
    system("CLS");                                                      //WCZESNE WYWO£ANIE BOMB
    plansza[q][w]=player;
     //KOLORY TEKSTU I T£A
    HANDLE hOut;
                                                                                                                                                                                hOut=GetStdHandle(STD_OUTPUT_HANDLE);
    //SetConsoleTextAttribute(hOut,FOREGROUND_RED); //kolor tekstu
    //SetConsoleTextAttribute(hOut,BACKGROUND_INTENSITY); //kolor t³a
    liczba_bomb=0;
                                                                                                                                                                                SetConsoleTextAttribute(hOut,FOREGROUND_GREEN);
    cout << "+";
                                                                                                                                                                                SetConsoleTextAttribute(hOut,7);
    for (int lengh=0;lengh<=n-1;lengh++){
                                                                                                                                                                                    SetConsoleTextAttribute(hOut,FOREGROUND_GREEN);
        cout << "-";}
    cout << "+";
    cout << endl;
                                                                                                                                                                            SetConsoleTextAttribute(hOut,7);
    for(int x=0; x<n; x++){
                                                                                                                                                                                        SetConsoleTextAttribute(hOut,FOREGROUND_GREEN);
    cout <<"|";
                                                                                                                                                                                SetConsoleTextAttribute(hOut,7);
        for(int y=0; y<n; y++) {if (plansza[x][y]==player){SetConsoleTextAttribute(hOut,FOREGROUND_RED);}
                              if (plansza[x][y]!=road){
                                    if (plansza[x][y]==secret) SetConsoleTextAttribute(hOut,BACKGROUND_BLUE);
                              cout<< plansza[x][y];
                                    if (plansza[x][y]==secret) SetConsoleTextAttribute(hOut,7);
                              }
                                else cout << " ";
                                if (plansza[x][y]==player){SetConsoleTextAttribute(hOut,7);}
                                if (plansza[x][y]==bomb) liczba_bomb++;}
                                                                                                                                                                                    SetConsoleTextAttribute(hOut,FOREGROUND_GREEN);
        cout<<"|"<<endl;
                                                                                                                                                                                    SetConsoleTextAttribute(hOut,7);
    }
                                                                                                                                                                                SetConsoleTextAttribute(hOut,FOREGROUND_GREEN);
    cout << "+";
    for(int x=0; x<n; x++) cout<<"-";
    cout<<"+"<<endl;
                                                                                                                                                                                SetConsoleTextAttribute(hOut,7);
                                                                                                                                                                                SetConsoleTextAttribute(hOut,FOREGROUND_RED);
    for (int i=zycia-1;i>=0;i--)
        cout << " <3 ";
                                                                                                                                                                                SetConsoleTextAttribute(hOut,7);
    cout << endl;
    cout << "Liczba bomb na planszy: " << liczba_bomb;
    cout << endl;
    cout << "Wcisnij Q aby pokazac bomby...    (Koszt: 1 zycie)";
    cout << endl;
    cout << "Wcisnij ESC aby zapauzowac...";
    if (zycia==0) game_over();
    Sleep(1000);
    rysuj_plansze();

}
