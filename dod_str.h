#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* Mora se voditi računa da destinacioni niz ima dovoljno mesta za prihvat stringove
da ne došlo do "buffer overflow-a", takodje se mora posle deklaracije niza nulifikovati sa
davanjem vrednosti('\0') prvom članu niza. */
/*Moze se dinamicki alocirati memorija, ali samo u programu, a ne i u biblioteci. */

int counter_str(char *destination){

    int counter=0;
    char strcnt;
    int i;
    for(i=0;i<strlen(destination);i++){

        strcnt=destination[i];
        if(strcnt=='#'){

            counter++;

        }

    }



    return counter;
}

char dod_str(char *destination, char *source){

    int counterX=counter_str(destination);
    int i=0;
    if(counterX==0){


        for(i=strlen(destination);i-->0;)// FOR petlja koja ide unatraske. Pocetna vrednost je stavljena kao zadnji indeks, a " i " se smanjuje dok ne dotakne nulu.

            if(destination[0]!='#')
            destination[i]='\0';


    }


    if(((sizeof(destination)/sizeof(destination[0]))-(strlen(destination)*sizeof(destination[0])))<(sizeof(source)/sizeof(source[0])))
        //Iako je prvobitno 'destination' nastanjen u 'stack'-u, ukoliko je potrebno, obezbedjuje se dodatna memorija u 'heap'-u. Obezbedjeno je naknadno ciscenje alocirane memorije funkcijom 'free_str(destination)'.
        destination = (char *) realloc(destination, (((sizeof(source)/sizeof(source[0]))-((sizeof(destination)))/sizeof(destination[0]))-(strlen(destination)*sizeof(destination)))+1);


    if(strlen(destination)==0){


        strcpy(destination,"#");
        strcat(destination,source);

    }

    else{

        strcat(destination,"#");
        strcat(destination,source);

    }

    return *destination;
}

char free_str(char *destination){

    if(strlen(destination)>0){

        destination[0]='\0';

    }
    return *destination;
}



char *get_str(char *destination, int br_str){

    int pos=0;
    int n=0;//duzina stringa
    char *sd_str;
    sd_str=(char*) malloc(n*sizeof(char));
    int counter=0;
    char strcnt;
    int i=0;
    for(i=0;i<strlen(destination);i++){

        strcnt=destination[i];


            if(strcnt=='#'){

            counter++;

        }
        if(br_str==counter && strcnt!='#'){

                n++;//duzina stringa se povecava kada se nadje karakter posle provere br_str sa counterom
                pos=i;

        }


    }


    int pocetna=pos-n+1;
    //int krajnja=pocetna+n;
    int c=0;
        do{

            strcnt=destination[c];
            sd_str[c] = destination[pocetna+c];

            c++;
        }
        while (c < n);
        sd_str[c] = '\0';


    return sd_str;
}

float str_to_float(char *destination){

    float brojx=0;
    int pos=0;
    int counter=-1; // "counter promenljiva se setuje na -1 jer neko moze uneti na nultom clanu niza tacku.
    int tacka=0;

    int i;
    for(i=0;i<strlen(destination);i++){

        if(!(destination[0]>=48 && destination[0]<=57)){ //Ovde se ispituje da li je prvi clan niza izmedju 0-9.

            printf("\nNiste uneli broj ...");
            exit(0);

        }
        if((destination[i]<48 || destination[i]>57) && destination[i]!=46){ //Ovde se ispituje da li bilo koji clan nije izmedju 0-9 ili ako nije '.', tj. sve drugo ne spada u "float".

            printf("\nNiste uneli broj ...");
            exit(0);

        }
            if(destination[i]=='.'){ //Ovde se ispituje ako je clan niza '.'(46) tacka i sve sve vezano za nju.
                tacka++; //Belezi koliko je "tacaka" nadjeno.

            if(tacka>1){ //Ovde se proverava da li je nadjeno vise od jedne tacke, ukoliko jeste, to automatski diskvalifikuje string kao broj(float).

            printf("\nNiste uneli broj ...");
            exit(0);

            }

                if(i==strlen(destination)-1){ //Ako je iscitavanje niza doslo do zadnjeg mesta, a tacka je zadna procitana, tj. posle nje nema ijedna decimala, to se ne smatra za broj.

                    printf("\nNiste uneli broj ...");
                    exit(0);
                }
                else if(!(destination[strlen(destination)-1]>=48 && destination[strlen(destination)-1]<=57)){ //Ovde se ispituje da li se na zadnjem mestu niza nalazi cifra.

                    printf("\nNiste uneli broj ...");
                    exit(0);

                }


                pos=i; //U promenljivoj "pos" kada se naidje na tacku se belezi njena pozicija u nizu.


            }




            if(pos>0){ //Ukoliko je pozicija tacke u nizu na mestu "vecem" od nulte pozicije niza, taj broj se moze smatrati kao "float".
                        //A belezi se iz razloga da bi se znalo koliko ima decimala posle decimalne tacke.
                counter++; //Belezi koliko ima decimalnih brojeva posle tacke.
            }



            if((destination[i]>=48 && destination[i]<=57)){
                                            //Ovde se npr. broj "123.4" zabelezio kao 1234, te sem ekstrakcije iz stringa, nije odredjena decimala.

                brojx=brojx*10+(destination[i]-48);

        }

    }
int cnt=0;
while(counter>cnt){ //Ovde se konacno decimalni broj "stvara". Ukoliko je nadjena tacka posle koje ima decimala, te se toliko puta koliko ima decimala dobijeni broj deli sa brojem 10.

brojx=brojx/10;
    cnt++;       //Pomocna promenljiva koja zabelezi svaki prolaz deljenja sa 10.
}

    return brojx;
}

int str_to_int(char *destination){

    int brojx=0;



    int i;
    for(i=0;i<strlen(destination);i++){




            if((destination[i]>=48 && destination[i]<=57)){
                                            //Ovde se npr. broj "123.4" zabelezio kao 1234, te sem ekstrakcije iz stringa, nije odredjena decimala.

                brojx=brojx*10+(destination[i]-48);

        }
        if((destination[i]<48 || destination[i]>57)){

            printf("\nNiste uneli broj ...");
            exit(0);

        }

    }


    return brojx;
}

















#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dod_str.h"

int main()
{
    char *niz1;
    char *niz2="Ovo je string.";
    char *niz3="Ovo je drugi string.";
    dod_str(niz1,niz2);
    dod_str(niz1,niz3);
    char niz4[10];
    printf("\nUnesi string: ");
    scanf("%9s", niz4);
    dod_str(niz1,niz4);
    dod_str(niz1," i na kraju, kraj.");
    char *niz5="Ovo je peti string.";
    dod_str(niz1,niz5);

    char *niz6="123.45";
    dod_str(niz1,niz6);

    printf("\nSada je string niz1:\n");
    printf("%s",niz1);

    printf("\nSada je duzina stringa niz1:");
    printf("%d",strlen(niz1));
    int sor=counter_str(niz1);
    printf("\nOvoliko ima stringa u niz1: %d", sor);

    int k=0;
    printf("\nKoji zelite string iz niz1: ");
    scanf("%d",&k);
    char *nizx=get_str(niz1,k);
    printf("\nOvaj ste string izabrali iz niz1: %s", nizx);

    printf("\nBrojka(float) je: %f",str_to_float(nizx));
    printf("\nBrojka(int) je: %d",str_to_int(nizx));

    free_str(niz1);

    return 0;
}
