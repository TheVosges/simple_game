#include <iostream>
#include <conio.h>
#include <cstring>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <fstream>
#include <string>
#include <MMSystem.h>
using namespace std;
/// Settings > Compiler > Linker settings > Add  "   winmm   "
/// Aby działał save należy uzupełnić ścieżke dostępu
char plansza[100][100];
int n=10;
float difficulty=0.2; //max 2n-2
int liczba_elementow=6;
int liczba_pol=n*n;
int zycia1=3;
int zycia=zycia1;
int liczba_bomb=0;
char road='#', bomb=207, nothing=' ', player='@' ,crossed='*', secret='$', enemy=15;
char lg_rog=201, poziom=205, pg_rog=187, pion=186, ld_rog=200, pd_rog=188;
char bomb_exploded=176;
char live=3;
int q=0;
int w=0;
int wtf;
bool pauza_obecna=false;
bool koniec_gry=false;
bool rozpoczecie_gry=false;
int xene, yene;
bool enemy_moved=false;
struct _menu{
    char element[32];       // STRUKTURA MENU
}_Menu[10];

struct _punkt{
    int x;                  // STRUKTURA OPCJI MENU
    int y;
};

void rysuj_plansze2();

void legenda();

void generuj_plansze();

void rysuj_plansze_zapis();                                  // WCZESNY ZAPIS FUNKCJI

void rysuj_plansze();

void rysuj_plansze1();

void odczyt_gry();

void drukuj_menu(_menu t[], int poz, int licz_el);

void menu();

void zapis_gry();

void enemy_movement();

void you_win(){
    system("CLS");                                           // WYGRANA
cout << "You Win" << endl;
cout << "Achievement get!" << endl;
pauza_obecna=false;
q=0;
w=0;
koniec_gry=true;
getch();

menu();}

void game_over(){
system("CLS");
cout << "GAME OVER" << endl;                                //PRZEGRANA
q=0;
w=0;
pauza_obecna=false;
koniec_gry=true;
getch();
menu();
}

void player_movement(){
    HANDLE hOut;
    hOut=GetStdHandle(STD_OUTPUT_HANDLE);
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
        if (plansza[q][w]==enemy) zycia=0;
        if (plansza[q][w]==bomb) {zycia=zycia-1;
        q++;
        if (plansza[q][w]!=bomb && plansza[q][w]!=secret) plansza[q][w]=bomb_exploded;
        q--;
        q--;
        if (plansza[q][w]!=bomb && plansza[q][w]!=secret) plansza[q][w]=bomb_exploded;
        q++;
        w++;
        if (plansza[q][w]!=bomb && plansza[q][w]!=secret) plansza[q][w]=bomb_exploded;
        w--;
        w--;
        if (plansza[q][w]!=bomb && plansza[q][w]!=secret) plansza[q][w]=bomb_exploded;
        w++;
        }
        if (zycia==0) goto u;
        if (q==n-1 & w==n-1){goto p;}
        plansza[q][w]=player;

        enemy_movement();
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
int kierunek;
int powtorzenie=0;
void enemy_movement(){
if (powtorzenie<1){
    plansza[xene][yene]=nothing;
    int granica;
    powtorzenie++;
    granica:
    kierunek=rand()%4;
    if (kierunek==0){yene--;           ///LEWO
    if (yene<0) {yene++; goto granica;}
    if (plansza[xene][yene]==bomb) {yene++; goto granica;}
    }

    if (kierunek==1){yene++;           ///PRAWO
    if (yene==n) {yene--; goto granica;}
    if (xene==n-1 & yene==n-1) {yene--; goto granica;}
    if (plansza[xene][yene]==bomb) {yene--; goto granica;}
    }

    if (kierunek==2){ xene++;          ///DOL
    if (xene==n) {xene--; goto granica;}
    if (xene==n-1 & yene==n-1) {xene--; goto granica;}
    if (plansza[xene][yene]==bomb) {xene--; goto granica;}
    }

    if (kierunek==3){ xene--;          ///GORA
    if (xene<0) {xene++; goto granica;}
    if (plansza[xene][yene]==bomb) {xene++; goto granica;}
    }
plansza[xene][yene]=enemy;
if (plansza[xene][yene]==player) zycia=0;
}
else powtorzenie=0;

}

int main(){
    srand(time(NULL));
    PlaySound(TEXT("muza.wav"), NULL, SND_ASYNC);
    menu();

    return 0;
}

void menu(){
    system("CLS");
    char klik;
    int poz=0;
    int bug;
    strcpy(_Menu[0].element,"Nowa gra");
    strcpy(_Menu[1].element,"Kontynuacja");
    strcpy(_Menu[2].element,"Zapisz obecna gre");
    strcpy(_Menu[3].element,"Odczyt");
    strcpy(_Menu[4].element,"Pomoc gry");
    strcpy(_Menu[5].element,"Koniec");

   /* for(int i=0; i<256;i++){
    cout <<i<<"/: "<<char(i)<<" :/" << endl;
        if ((i+1)%10==0) cout << endl;
    }
    cin >> wtf;*/
    drukuj_menu(_Menu, poz, liczba_elementow);
    bug:
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
           // cout<<"Wcisnieto: "<<_Menu[poz].element<<endl;
            switch(poz){
                case 0: q=0; w=0; zycia=zycia1;
                        rozpoczecie_gry=true;
                        system("CLS");
                        generuj_plansze();
                        rysuj_plansze1();
                case 5: exit(0);
                case 4: legenda();
                case 1: if (koniec_gry==true) {cout << "Nie masz obecnej gry"; goto bug;}
                        if (rozpoczecie_gry==false) {cout << "Nie masz obecnej gry"; goto bug;}
                        pauza_obecna=false;
                        plansza[q][w]=player;
                        rysuj_plansze();
                case 2: if (koniec_gry==true) {cout << "Nie masz obecnej gry"; goto bug;}
                        if (rozpoczecie_gry==false) {cout << "Nie masz obecnej gry"; goto bug;}
                    rysuj_plansze_zapis();
                case 3: odczyt_gry();
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

void generuj_plansze(){koniec_gry=false;
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
bool wrog_obecny=false;
do{x1=rand()%n;
y1=rand()%n;
if (plansza[x1][y1]!=bomb & plansza[x1][y1]!=player &  plansza[x1][y1]!=secret){plansza[x1][y1]=enemy;
xene=x1;
yene=y1;
wrog_obecny=true;}
}while(wrog_obecny!=true);
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
    cout << lg_rog;
                                                                                                                                                                                SetConsoleTextAttribute(hOut,7);
    for (int lengh=0;lengh<=n-1;lengh++){
                                                                                                                                                                                    SetConsoleTextAttribute(hOut,FOREGROUND_GREEN);
        cout << poziom;}
    cout << pg_rog;
    cout << endl;
                                                                                                                                                                            SetConsoleTextAttribute(hOut,7);
    for(int x=0; x<n; x++){
                                                                                                                                                                                        SetConsoleTextAttribute(hOut,FOREGROUND_GREEN);
    cout <<pion;
                                                                                                                                                                                SetConsoleTextAttribute(hOut,7);
        for(int y=0; y<n; y++) {if (plansza[x][y]==player){SetConsoleTextAttribute(hOut,FOREGROUND_RED);}
                                if (plansza[x][y]!=road & plansza[x][y]!=bomb & plansza[x][y]!=secret){
                                cout<< plansza[x][y];}
                                else cout << " ";
                                if (plansza[x][y]==player){SetConsoleTextAttribute(hOut,7);}
                                if (plansza[x][y]==bomb) liczba_bomb++;}
                                                                                                                                                                                    SetConsoleTextAttribute(hOut,FOREGROUND_GREEN);
        cout<<pion<<endl;
                                                                                                                                                                                    SetConsoleTextAttribute(hOut,7);
    }
                                                                                                                                                                                SetConsoleTextAttribute(hOut,FOREGROUND_GREEN);
    cout << ld_rog;
    for(int x=0; x<n; x++) cout<<poziom;
    cout<<pd_rog<<endl;
                                                                                                                                                                                SetConsoleTextAttribute(hOut,7);
                                                                                                                                                                                SetConsoleTextAttribute(hOut,FOREGROUND_RED);
    for (int i=zycia-1;i>=0;i--)
        cout << live;
                                                                                                                                                                                SetConsoleTextAttribute(hOut,7);
    cout << endl;
    cout << "Liczba bomb: " << liczba_bomb;
    cout << endl;
    cout << "Wcisnij Q aby pokazac bomby...    (Koszt: 1 zycie)";
    cout << endl;
    cout << "Wcisnij ESC aby zapauzowac...";

    player_movement();
}

void rysuj_plansze1(){
    system("CLS");
    plansza[q][w]=player;
     //KOLORY TEKSTU I T£A
    HANDLE hOut;
                                                                                                                                                                                hOut=GetStdHandle(STD_OUTPUT_HANDLE);
    //SetConsoleTextAttribute(hOut,FOREGROUND_RED); //kolor tekstu
    //SetConsoleTextAttribute(hOut,BACKGROUND_INTENSITY); //kolor t³a
    liczba_bomb=0;
                                                                                                                                                                                SetConsoleTextAttribute(hOut,FOREGROUND_GREEN);
    cout << lg_rog;
                                                                                                                                                                                SetConsoleTextAttribute(hOut,7);
    for (int lengh=0;lengh<=n-1;lengh++){
                                                                                                                                                                                SetConsoleTextAttribute(hOut,FOREGROUND_GREEN);
        cout << poziom;}
    cout << pg_rog;
    cout << endl;
                                                                                                                                                                                SetConsoleTextAttribute(hOut,7);
    for(int x=0; x<n; x++){
                                                                                                                                                                                SetConsoleTextAttribute(hOut,FOREGROUND_GREEN);
    cout <<pion;
                                                                                                                                                                                SetConsoleTextAttribute(hOut,7);
        for(int y=0; y<n; y++) {if (plansza[x][y]==player){SetConsoleTextAttribute(hOut,FOREGROUND_RED);}
                                if (plansza[x][y]!=road){
                                cout<< plansza[x][y];}
                                else cout << " ";
                                if (plansza[x][y]==player){SetConsoleTextAttribute(hOut,7);}
                                if (plansza[x][y]==bomb) liczba_bomb++;}
                                                                                                                                                                                SetConsoleTextAttribute(hOut,FOREGROUND_GREEN);
        cout<<pion<<endl;
                                                                                                                                                                                SetConsoleTextAttribute(hOut,7);
    }
                                                                                                                                                                                SetConsoleTextAttribute(hOut,FOREGROUND_GREEN);
    cout << ld_rog;
    for(int x=0; x<n; x++) cout<<poziom;
    cout<<pd_rog<<endl;
                                                                                                                                                                                SetConsoleTextAttribute(hOut,7);
                                                                                                                                                                                SetConsoleTextAttribute(hOut,FOREGROUND_RED);
    for (int i=zycia-1;i>=0;i--)
        cout << live;
                                                                                                                                                                                SetConsoleTextAttribute(hOut,7);
    cout << endl;
    cout << "Liczba bomb: " << liczba_bomb;
    cout << endl;
    cout << "Wcisnij Q aby pokazac bomby...    (Koszt: 1 zycie)";
    cout << endl;
    cout << "Wcisnij ESC aby zapauzowac...";
    if (zycia==0) game_over();
    Sleep(1000);
    rysuj_plansze();

}

void zapis_gry(){
    plansza[q][w]=player;
  //  system("CLS");
  //  cout << "Wspolrzedne gracza: [" <<w<<":"<<q<<"]"<<endl;
  //  cout << "Wspolrzedne bomb: " << endl;
    int x1=0, y1=0;
    int liczba=0;
    int liczba_bomb1=0;
    bool koniec=false;
/*do{y1++;
liczba++;
    if (y1==n+1) {y1=0; x1++;}
    if (plansza[x1][y1]==bomb) { liczba_bomb1++; cout << liczba_bomb1<<" : "<< "["<<y1<<":"<<x1<<"]"<<endl;}

}while(liczba!=n*n+n);*/
 //   cout << "Liczba pozostalych zyc: " << zycia << endl;


fstream plik("C://Users//user//Desktop//save.txt", ios::out );
    if( plik.good() )
    {
      // plik << q << " " <<w << endl;
int x2,y2;
/*do{


    if (y1==n) {y1=0; x1++;}
    if (plansza[x1][y1]==player){
    plik << x1 << " : " << y1 << endl;
    koniec=true;
    x2=x1;
    y2=y1;
    }
    y1++;
  //  if (plansza[x1][y1]==bomb) { plik << "["<<y1<<":"<<x1<<"]"<<endl;}
}while(koniec==false);*/
x1=0;
y1=0;
do{


    if (y1==n) {y1=0; x1++;
   // plik<<endl;
    }
    if (plansza[x1][y1]==player) plik << "3";
    if (plansza[x1][y1]==bomb) plik << "1";
    if (plansza[x1][y1]==road) plik << "2";
    if (plansza[x1][y1]==secret) plik << "4";
    if (plansza[x1][y1]==nothing) plik << "0";
    if (plansza[x1][y1]==crossed) plik << "5";
    if (plansza[x1][y1]==bomb_exploded) plik << "6";
   // plik << plansza[x1][y1];
    y1++;
  //  if (plansza[x1][y1]==bomb) { plik << "["<<y1<<":"<<x1<<"]"<<endl;}
}while(x1<n);

          //  plik << i << ", ";
            //plik.flush();
        plik << "X" << zycia;
        plik.close();
    }

    /*int i;
    fstream plik;
    plik.open("C://Users//uczen//Desktop//ZapisGry.txt",ios::in);
    if (plik.good()){
    char ciag[20]="";

    while (!plik.eof()){
        {
        plik>>ciag;


            i=atoi (ciag);
            funkcja(i);

        }}
    /cout <<endl << funkcja << endl;

    }

}
*/
getch();
menu();
}

void odczyt_gry(){
rozpoczecie_gry=true;
int i=0;
int x1=0, y1=0;
int x2, y2;
string odczyt;
q=0;
w=0;
int pomoc=n*n;
char odczyt_1[100]="";
fstream plik;
plik.open("C://Users//user//Desktop//save.txt", ios::in );
if (plik.good()){
    while (!plik.eof()){
        getline(plik,odczyt);
        strcpy(odczyt_1, odczyt.c_str());
       // cout << odczyt_1;
        }
}
cout << endl;
for (i=0;i<=pomoc-1;i++){
        if (y1==n) {y1=0; x1++; }
        if (odczyt_1[i]=='1') plansza[x1][y1]=bomb;
        if (odczyt_1[i]=='2') plansza[x1][y1]=road;
        if (odczyt_1[i]=='3') {plansza[x1][y1]=player; x2=x1; y2=y1;}
        if (odczyt_1[i]=='4') plansza[x1][y1]=secret;
        if (odczyt_1[i]=='0') plansza[x1][y1]=nothing;
        if (odczyt_1[i]=='5') plansza[x1][y1]=crossed;
        if (odczyt_1[i]=='6') plansza[x1][y1]=bomb_exploded;
        y1++;
}
i++;
int pomocna;
pomocna=odczyt_1[i]-48;
zycia=pomocna;

q=x2;
w=y2;
plansza[q][w]=player;
rysuj_plansze();
}

void legenda(){
    system("CLS");
    cout << "CEL GRY:" << endl;
    cout << "Jestes porwyanym przez komunistow saperem amerykanskiej armii (wszelkie stereotypy  zostaly przypadkowo dobrane ;) ) " << endl <<
    "Udalo ci sie uciec z lagrow i chcesz powiadomic swoja armie o efektach inwigilacji. Baza twojej armi znajduje sie na poludniowy zachod od twojego poczatkowego miejsca polozena (lewy dolny rog mapy)" << endl <<
    "Jako glowny bohater masz 3 zycia i wchodzac na zaminowane pole zmartwychwstajesz jak Supermen z Ligi Sprawiedliwosci (porownanie zupelnie przypadkowe)" << endl << endl;

    cout << "LEGENDA:" << endl;
    cout << live << " - " << "twoja obecna liczba zyc" << endl;
    cout << secret << " - " << "gdzies na mapie ukryty jest sekret zapewnajacy ci DODATKOWE 5 zyc"<< endl;
    cout << bomb_exploded << " - " << "wlasnie wszedles w bombe, wokol ciebie utworzyl sie lej jednoczesnie ukazujac czy obok znajdowal sie jakis obiekt (kolejna bomba albo sekret)"<< endl;
    cout << crossed << " - " << "twoja trasa ktora kroczysz, jest juz przez ciebie sprawdzona i nie moze na niej znajdowac sie bomba"<< endl;
    cout << player << " - " << "to jestes ty :D" << endl;
    cout << enemy << " - " << "na polu szuka cie jeden z komunistow, nie daj mu sie zpalac, bo od razu twoj zywot dobiega konca"<< endl;

    getch();
    menu();
}

void rysuj_plansze_zapis(){
    system("CLS");                                              //FAKSTYCZNY STATUS EKRANU
    plansza[q][w]=player;
     //KOLORY TEKSTU I T£A
    HANDLE hOut;
     cout << "'WYGLAD TWOJEJ ZAPISANEJ GRY...'" << endl << endl;                                                                                                                                                                           hOut=GetStdHandle(STD_OUTPUT_HANDLE);
    //SetConsoleTextAttribute(hOut,FOREGROUND_RED); //kolor tekstu
    //SetConsoleTextAttribute(hOut,BACKGROUND_INTENSITY); //kolor t³a
    liczba_bomb=0;
                                                                                                                                                                                SetConsoleTextAttribute(hOut,FOREGROUND_GREEN);
    cout << lg_rog;
                                                                                                                                                                                SetConsoleTextAttribute(hOut,7);
    for (int lengh=0;lengh<=n-1;lengh++){
                                                                                                                                                                                    SetConsoleTextAttribute(hOut,FOREGROUND_GREEN);
        cout << poziom;}
    cout << pg_rog;
    cout << endl;
                                                                                                                                                                            SetConsoleTextAttribute(hOut,7);
    for(int x=0; x<n; x++){
                                                                                                                                                                                        SetConsoleTextAttribute(hOut,FOREGROUND_GREEN);
    cout <<pion;
                                                                                                                                                                                SetConsoleTextAttribute(hOut,7);
        for(int y=0; y<n; y++) {if (plansza[x][y]==player){SetConsoleTextAttribute(hOut,FOREGROUND_RED);}
                               // if (plansza[x][y]!=road & plansza[x][y]!=bomb & plansza[x][y]!=secret){
                                cout<< plansza[x][y];//}
                               // else cout << " ";
                                if (plansza[x][y]==player){SetConsoleTextAttribute(hOut,7);}
                                if (plansza[x][y]==bomb) liczba_bomb++;}
                                                                                                                                                                                    SetConsoleTextAttribute(hOut,FOREGROUND_GREEN);
        cout<<pion<<endl;
                                                                                                                                                                                    SetConsoleTextAttribute(hOut,7);
    }
                                                                                                                                                                                SetConsoleTextAttribute(hOut,FOREGROUND_GREEN);
    cout << ld_rog;
    for(int x=0; x<n; x++) cout<<poziom;
    cout<<pd_rog<<endl;
                                                                                                                                                                                SetConsoleTextAttribute(hOut,7);
SetConsoleTextAttribute(hOut,FOREGROUND_RED);
    for (int i=zycia-1;i>=0;i--)
        cout << live;
 SetConsoleTextAttribute(hOut,7);
    zapis_gry();
}
