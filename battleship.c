/*
 * Battaglia Navale / Battleship
 * 
 * An implementation of the classic board game Battleship in C
 * using the Windows.h library for console-based graphics.
 * 
 * Copyright (c) 2023 Battaglia Navale
 * 
 * Questo software è concesso in licenza secondo i termini della licenza MIT.
 * Consultare il file LICENSE.md per i dettagli completi.
 * 
 * This software is licensed under the terms of the MIT license.
 * See the LICENSE.md file for complete details.
 */

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
int B[10][10],ra[5],te,o=0,k,j=1,ok,tsc,tsr,ok2,srb,scb,s,a,sr,r,sc,nag,nab,c,n,nl,NG[26],NB[26], np[5];
int pp[100], dp = 0; // possible positions, position size
char rr,ro ,P[10][10], rf[2];
short i;
void gotoxy(short x, short y);
int main(){
    time_t t;
    srand((unsigned) time(&t));
    for (i = 0; i < 54 ; i++) {
        gotoxy(i-1, 15);
        printf("            ");
        gotoxy(i, 15);
        printf("Battaglia");
        gotoxy(108-i, 16);
        printf("            ");
        gotoxy(107-i, 16);
        printf("Navale ");
        Sleep(1);
    }
    Sleep(250);
    gotoxy(51, 18);
    printf("Caricamento...");
    Sleep(500);
    gotoxy(50, 15);
    printf("            ");
    gotoxy(50, 16);
    printf("            ");
    gotoxy(51, 18);
    printf("              ");

    do {
        //inizio reset e inizializzazioni
        i=2;
        j=1;
        te=0;
        o=0;
        nag=0;
        nab=0;
        s=0;
        for (k = 0; k < 5; ++k) {
            np[k]=0;
            ra[k]=0;
        }
        for (k = 0; k < 25; ++k) {
            NG[k]=0;
            NB[k]=0;
        }
        for (r = 0; r < 10 ; r++) {
            for (c = 0; c < 10 ; c++) {
                B[r][c]=0;
            }
        }
        for (r = 0; r < 10 ; r++) {
            for (c = 0; c < 10 ; c++) {
                P[r][c]='-';
            }
        }
        //fine reset e inizializzazioni
        gotoxy(91, 0);
        printf(" 1 2 3 4 5 6 7 8 9 10");
        gotoxy(91, 1);
        printf("______________________");
        gotoxy(90, 2);
        for (r = 0; r < 10 ; r++) {
            printf("|");
            for (c = 0; c < 10 ; c++) {
                printf(" -");
            }
            printf(" |");
            i++;
            gotoxy(90, i);
        }
        gotoxy(89, 2); printf("A"); gotoxy(89, 3); printf("B"); gotoxy(89, 4); printf("C");
        gotoxy(89, 5); printf("D"); gotoxy(89, 6); printf("E"); gotoxy(89, 7); printf("F");
        gotoxy(89, 8); printf("G"); gotoxy(89, 9); printf("H"); gotoxy(89, 10); printf("I");
        gotoxy(89, 11); printf("J");
        gotoxy(90, 12);
        printf("|_____________________|");
        gotoxy(41, 0);
        printf(" 1 2 3 4 5 6 7 8 9 10");
        gotoxy(41, 1);
        printf("______________________");
        gotoxy(40, 2);
        i=2;
        for (r = 0; r < 10 ; r++) {
            printf("|");
            for (c = 0; c < 10 ; c++) {
                printf(" %c", P[r][c]);
            }
            printf(" |");
            i++;
            gotoxy(40, i);
        }
        gotoxy(39, 2); printf("A"); gotoxy(39, 3); printf("B"); gotoxy(39, 4); printf("C");
        gotoxy(39, 5); printf("D"); gotoxy(39, 6); printf("E"); gotoxy(39, 7); printf("F");
        gotoxy(39, 8); printf("G"); gotoxy(39, 9); printf("H"); gotoxy(39, 10); printf("I");
        gotoxy(39, 11); printf("J");
        gotoxy(40, 12);
        printf("|_____________________|");
        gotoxy(41, 14);
        printf("________");
        gotoxy(40,15);
        printf("|___5___/");
        gotoxy(51,14);
        printf("_______");
        gotoxy(50,15);
        printf("|___4__/");
        gotoxy(41,16);
        printf("______");
        gotoxy(40,17);
        printf("|__3__/");
        gotoxy(49,16);
        printf("______");
        gotoxy(48,17);
        printf("/__2__/");
        gotoxy(57,16);
        printf("_____");
        gotoxy(56,17);
        printf("|__1_/");
        nl=0;
        // posizionamento navi giocatore
        do {
            for (i = 3; i < 10 ; ++i) {
                gotoxy(0,i);
                printf("                               ");
            }
            do {
                gotoxy(1,3);
                printf("quale nave vuoi posizionare?");
                gotoxy(1,4);
                fflush(stdin);
                scanf("%d", &n);
                for (i = 5; i < 10 ; ++i) {
                    gotoxy(0,i);
                    printf("                              ");
                }
                gotoxy(1, 2);
                switch (n) {
                    case 1:
                        if (np[0]==0){
                            nl=2;
                            gotoxy(57,16);
                            printf("         ");
                            gotoxy(56,17);
                            printf("      ");
                        }else {
                            for (i = 2; i < 10 ; ++i) {
                                gotoxy(0,i);
                                printf("                              ");
                            }
                            gotoxy(1,2);
                            printf("nave gia' posizionata");
                            nl=0;
                        }
                        np[0]=1;
                        break;
                    case 2:
                        if (np[1]==0) {
                            nl=3;
                            gotoxy(49,16);
                            printf("      ");
                            gotoxy(48,17);
                            printf("       ");
                        }else {
                            for (i = 2; i < 10 ; ++i) {
                                gotoxy(0,i);
                                printf("                              ");
                            }
                            gotoxy(1,2);
                            printf("nave gia' posizionata");

                            nl=0;
                        }
                        np[1]=1;
                        break;
                    case 3:
                        if (np[2]==0) {
                            nl=3;
                            gotoxy(41,16);
                            printf("        ");
                            gotoxy(40,17);
                            printf("       ");
                        }else {
                            for (i = 2; i < 10 ; ++i) {
                                gotoxy(0,i);
                                printf("                              ");
                            }
                            gotoxy(1, 2);
                            printf("nave gia' posizionata");
                            nl=0;
                        }
                        np[2]=1;
                        break;
                    case 4:
                        if (np[3]==0){
                            nl=4;
                            gotoxy(51,14);
                            printf("       ");
                            gotoxy(50,15);
                            printf("        ");
                        }else {
                            for (i = 2; i < 10 ; ++i) {
                                gotoxy(0,i);
                                printf("                              ");
                            }
                            gotoxy(1, 2);
                            printf("nave gia' posizionata");
                            nl=0;
                        }
                        np[3]=1;
                        break;
                    case 5:
                        if (np[4]==0) {
                            nl=5;
                            gotoxy(41, 14);
                            printf("        ");
                            gotoxy(40,15);
                            printf("         ");
                        }else {
                            for (i = 2; i < 10 ; ++i) {
                                gotoxy(0,i);
                                printf("                             ");
                            }
                            gotoxy(1, 2);
                            printf("nave gia' posizionata");
                            nl=0;
                        }
                        np[4]=1;
                        break;
                    default: {
                        for (i = 2; i < 10 ; ++i) {
                            gotoxy(0,i);
                            printf("                              ");
                        }
                        gotoxy(1, 2);
                        printf("numero nave non valido");
                    }
                }
            }while (nl==0);
            for (i = 0; i < 10 ; ++i) {
                gotoxy(0,i);
                printf("                               ");
            }
            do {
                ok=1;
                for (i = 3; i < 10 ; ++i) {
                    gotoxy(0,i);
                    printf("                               ");
                }
                gotoxy(1,3);
                printf("dove la vuoi posizionare?");
                gotoxy(1,4);
                printf("(esempio: F 9)");
                gotoxy(1,5);
                fflush(stdin);
                scanf("%c %d", &rr,&sc);
                gotoxy(1,3);
                if (sc>10 || sc<1) {
                    ok=0;
                    for (i = 2; i < 10 ; ++i) {
                        gotoxy(0,i);
                        printf("                              ");
                    }
                    gotoxy(1, 2);
                    printf("posizione non valida");
                }
                switch (rr) {
                    case 'A':
                        sr=1;
                        break;
                    case 'B':
                        sr=2;
                        break;
                    case 'C':
                        sr=3;
                        break;
                    case 'D':
                        sr=4;
                        break;
                    case 'E':
                        sr=5;
                        break;
                    case 'F':
                        sr=6;
                        break;
                    case 'G':
                        sr=7;
                        break;
                    case 'H':
                        sr=8;
                        break;
                    case 'I':
                        sr=9;
                        break;
                    case 'J':
                        sr=10;
                        break;
                    default: {
                        ok=0;
                        for (i = 2; i < 10 ; ++i) {
                            gotoxy(0,i);
                            printf("                              ");
                        }
                        gotoxy(1, 2);
                        printf("posizione non valida");
                    }
                }
                if (ok==0)
                    continue;
                if (o==0){
                    if (sr+nl>10) {
                        sr=sr-(sr+nl-11);
                    }
                    r=sr;
                    c=sc;
                    for (k = 0; k < nl && ok!=0; ++k) {
                        if (P[r-1][c-1]=='H')
                            ok=0;
                        r++;
                    }
                    if (ok!=o) {
                        r=sr;
                        c=sc;
                        for (k = 0; k < nl ; ++k) {
                            P[r-1][c-1]='H';
                            r++;
                        }
                    }
                } else {
                    if (sc+nl>10) {
                        sc=sc-(sc+nl-11);
                    }
                    c=sc;
                    r=sr;
                    for (k = 0; k < nl && ok!=0; k++) {
                        if (P[r-1][c-1]=='H')
                            ok=0;
                        c++;
                    }
                    if (ok!=0) {
                        r=sr;
                        c=sc;
                        for (k = 0; k < nl ; k++) {
                            P[r-1][c-1]='H';
                            c++;
                        }
                    }
                }
                gotoxy(41, 2);
                i=2;
                for (r = 0; r < 10 ; r++) {
                    for (c = 0; c < 10 ; c++) {
                        printf(" %c", P[r][c]);
                    }
                    i++;
                    gotoxy(41, i);
                }
                gotoxy(1,3);
                for (i = 3; i < 6 ; ++i) {
                    gotoxy(1,i);
                    printf("                              ");
                }
                if (ok==0) {
                    for (i = 2; i < 10 ; ++i) {
                        gotoxy(0,i);
                        printf("                              ");
                    }
                    gotoxy(1, 2);
                    printf("posizione non valida");
                    continue;
                }
                for (i = 0; i < 10 ; ++i) {
                    gotoxy(0,i);
                    printf("                               ");
                }
                do {
                    for (i = 3; i < 10 ; ++i) {
                        gotoxy(0,i);
                        printf("                               ");
                    }
                    gotoxy(1,3);
                    printf("ruotare (R) o confermare (C)?");
                    gotoxy(1,4);
                    fflush(stdin);
                    scanf("%c", &ro);
                    for (i = 4; i < 10 ; ++i) {
                        gotoxy(1,i);
                        printf("                              ");
                    }
                    if (ro=='R'){
                        ok=0;
                        c=sc;
                        r=sr;
                        if (o==1){
                            for (k = 0; k < nl ; k++) {
                                P[r-1][c-1]='-';
                                c++;
                            }
                        }else {
                            for (k = 0; k < nl ; k++) {
                                P[r-1][c-1]='-';
                                r++;
                            }
                        }
                        o=-o+1;
                    } else if(ro=='C'){
                        ok=1;
                        NG[j]=nl;
                        NG[j+1]=n;
                        NG[j+2]=o;
                        if (NG[j+2]==0) {
                            NG[j+3]=sc-1;
                            NG[j+4]=sr-1;
                        } else {
                            NG[j+3]=sr-1;
                            NG[j+4]=sc-1;
                        }
                        j+=5;
                    } else {
                        ok=0;
                        for (i = 3; i < 6 ; ++i) {
                            gotoxy(0,i);
                            printf("                              ");
                        }
                        gotoxy(1, 2);
                        printf("comando non valido");
                    }
                }while (ro!='R' && ro!='C');
                for (i = 2; i < 10 ; ++i) {
                    gotoxy(0,i);
                    printf("                              ");
                }
            }while (ok==0);
            NG[0]++;
        }while (NG[0]<5);
        NB[0]=0;
        j=1;
        // posizionamento navi computer (bot)
        do {
            n=-NB[0]+5;
            nl=5-NB[0];
            if (NB[0]==3)
                nl=3;
            if (NB[0]==4)
                nl=2;
            do {
                ok=1;
                srb=rand() % 10;
                scb=rand() % 10;
                o=rand() % 2;
                o=-o+1;
                if (o==0){
                    if (srb+nl>10) {
                        srb=srb-(srb+nl-10);
                    }
                    r=srb;
                    c=scb;
                    for (k = 0; k < nl && ok!=0; ++k) {
                        if (B[r][c]==2)
                            ok=0;
                        r++;
                    }
                    if (ok!=o) {
                        r=srb;
                        c=scb;
                        for (k = 0; k < nl ; ++k) {
                            B[r][c]=2;
                            r++;
                        }
                    }
                } else {
                    if (scb+nl>10) {
                        scb=scb-(scb+nl-10);
                    }
                    c=scb;
                    r=srb;
                    for (k = 0; k < nl && ok!=0; k++) {
                        if (B[r][c]==2)
                            ok=0;
                        c++;
                    }
                    if (ok!=0) {
                        r=srb;
                        c=scb;
                        for (k = 0; k < nl ; k++) {
                            B[r][c]=2;
                            c++;
                        }
                    }
                }
            }while (ok==0);
            NB[j]=nl;
            NB[j+1]=n;
            NB[j+2]=o;
            if (NB[j+2]==0) {
                NB[j+3]=scb;
                NB[j+4]=srb;
            } else {
                NB[j+3]=srb;
                NB[j+4]=scb;
            }
            j+=5;
            NB[0]++;
        }while (NB[0]<5);
        for (i = 0; i < 100; i+=2) {
            pp[dp] = i + i / 10 % 2;
            dp++;
        }
        gotoxy(91, 2);
        i=2;
        for (i = 0; i < 10 ; ++i) {
            gotoxy(0,i);
            printf("                              ");
        }
        // game loop
        do{
            // display player board
            gotoxy(41, 2);
            i=2;
            for (r = 0; r < 10 ; r++) {
                for (c = 0; c < 10 ; c++) {
                    printf(" %c", P[r][c]);
                }
                i++;
                gotoxy(41, i);
            }
            gotoxy(91, 2);
            i=2;
            for (r = 0; r < 10 ; r++) {
                for (c = 0; c < 10 ; c++) {
                    switch (B[r][c]) {
                        case 0:
                            printf(" -");
                            break;
                        case 1:
                            printf(" O");
                            break;
                        case 2:
                            printf(" -");
                            break;
                        case 3:
                            printf(" X");
                    }
                }
                i++;
                gotoxy(91, i);
            }
            // turno giocatore
            do {
                ok=1;
                for (i = 3; i < 10 ; ++i) {
                    gotoxy(0,i);
                    printf("                              ");
                }
                gotoxy(1,3);
                printf("dove vuoi attaccare?");
                gotoxy(1,4);
                printf("(esempio: F 9)");
                gotoxy(1,5);
                fflush(stdin);
                scanf("%c %d", &rr,&sc);
                gotoxy(1,3);
                if (sc>10 || sc<1) {
                    ok=0;
                    for (i = 3; i < 10 ; ++i) {
                        gotoxy(0,i);
                        printf("                              ");
                    }
                    gotoxy(1, 2);
                    printf("posizione non valida");
                }
                switch (rr) {
                    case 'A':
                        sr=1;
                        break;
                    case 'B':
                        sr=2;
                        break;
                    case 'C':
                        sr=3;
                        break;
                    case 'D':
                        sr=4;
                        break;
                    case 'E':
                        sr=5;
                        break;
                    case 'F':
                        sr=6;
                        break;
                    case 'G':
                        sr=7;
                        break;
                    case 'H':
                        sr=8;
                        break;
                    case 'I':
                        sr=9;
                        break;
                    case 'J':
                        sr=10;
                        break;
                    default: {
                        ok=0;
                        for (i = 2; i < 10 ; ++i) {
                            gotoxy(0,i);
                            printf("                              ");
                        }
                        gotoxy(1, 2);
                        printf("posizione non valida");
                    }
                }
                // convalidazione mossa
                if (ok==1) {
                    sr--;
                    sc--;
                    if (B[sr][sc]==1 || B[sr][sc]==3) {
                        ok=0;
                        for (i = 2; i < 10 ; ++i) {
                            gotoxy(0,i);
                            printf("                              ");
                        }
                        gotoxy(1, 2);
                        printf("posizione gia' attaccata");
                    } else if (B[sr][sc]==0) {
                        B[sr][sc]=1;
                        for (i = 2; i < 10 ; ++i) {
                            gotoxy(0,i);
                            printf("                              ");
                        }
                        gotoxy(1,2);
                        printf("nave mancata");
                    } else if (B[sr][sc]==2){
                        B[sr][sc]=3;
                        for (i = 2; i < 10 ; ++i) {
                            gotoxy(0,i);
                            printf("                              ");
                        }
                        gotoxy(1,2);
                        printf("nave colpita");
                        j=1;
                        NB[0]=0;
                        // verifica affondamento nave
                        do {
                            ok2=0;
                            nl=NB[j];
                            if (nl!=0) {
                                n=NB[j+1];
                                if (NB[j+2]==0) {
                                    c=NB[j+3];
                                    r=NB[j+4];
                                    for (k = 0; k < nl && B[r+k][c]==3 ; k++) {}
                                    if (k==nl) {
                                        ok2=1;
                                    }
                                } else {
                                    r=NB[j+3];
                                    c=NB[j+4];
                                    for (k = 0; k < nl && B[r][c+k]==3 ; k++) {}
                                    if (k==nl) {
                                        ok2=1;
                                    }
                                }
                                if (ok2==1){
                                    nab++;
                                    NB[j]=0;
                                    gotoxy(13,2);
                                    printf(" e affondata!");
                                    break;
                                }
                            }
                            j+=5;
                            NB[0]++;
                        }while (NB[0]<5);
                    }
                }
            }while (ok==0);
            // condizione vittoria giocatore
            if (nab==5)
                continue;
            // turno computer
            do {
                ok=1;
                // te == 0 -> no clue, random
                if (te==0) {
                    if (dp == 0) {
                        nab = 5; // bot resigns
                        break;
                    }
                    srb=rand() % dp;
                    scb=pp[srb];
                    for (int m = srb; m < dp - 1; m++) {
                        pp[m] = pp[m + 1];
                    }
                    dp--;
                    srb=scb/10;
                    scb=scb%10;
                    if (P[srb][scb]=='O' || P[srb][scb]=='X') {
                        ok=0;
                        continue;
                    }
                    if (s==1) {
                        if (srb-1<0 || P[srb-1][scb]=='O' || P[srb-1][scb]=='X') {
                            if ((srb+1>9 || P[srb+1][scb]=='O' || P[srb+1][scb]=='X') && (srb+2>9 || P[srb+2][scb]=='O' || P[srb+2][scb]=='X'))
                                s=0;
                        } else if(srb-2<0 || P[srb-2][scb]=='O' || P[srb-2][scb]=='X'){
                            s=0;
                        }
                        if (s==0) {
                            s=1;
                            if (scb-1<0 || P[srb][scb-1]=='O' || P[srb-1][scb-1]=='X') {
                                if ((scb+1>9 || P[srb][scb+1]=='O' || P[srb][scb+1]=='X') && (scb+2>9 || P[srb][scb+2]=='O' || P[srb][scb+2]=='X')){
                                    ok=0;
                                    continue;
                                }
                            }else if (srb-2<0 || P[srb-2][scb]=='O' || P[srb-2][scb]=='X'){
                                ok=0;
                                continue;
                            }
                        }
                        s=1;
                    }
                }
                // te == 1 -> hit, discovery phase
                if (te==1) {
                    scb=tsc;
                    srb=tsr;
                }
                if (P[srb][scb]=='-') {
                    P[srb][scb]='O';
                    if (te==1) {
                        te=2;
                    }
                    if (te==3)
                        te=4;
                }
                if (P[srb][scb]=='H') {
                    P[srb][scb]='X';
                    for (int m = 0; m < 4; m++) {
                        int tmpr = (m + 1) / 2;
                        int tmpc = 2 * (m % 2);
                        tmpc = 1 - tmpc;
                        tmpc *= (tmpr & 1);
                        tmpr = 1 - tmpr;

                        if (srb + tmpr < 0 || srb + tmpr > 9 || scb + tmpc < 0 || scb + tmpc > 9)
                            continue;

                        if (P[srb + tmpr][scb + tmpc] == 'O' || P[srb + tmpr][scb + tmpc] == 'X')
                            continue;

                        ok2 = 1;
                        for (int l = 0; l < dp; l++) {
                            if (pp[l] == (srb + tmpr) * 10 + (scb + tmpc)) {
                                ok2 = 0;
                                break;
                            }
                        }
                        if (ok2 == 1) {
                            pp[dp] = (srb + tmpr) * 10 + (scb + tmpc);
                            dp++;
                        }
                    }

                    if (te==1)
                        te=3;
                    if (te==0)
                        te=1;
                    j=1;
                    NG[0]=0;
                    do {
                        ok2=0;
                        nl=NG[j];
                        if (nl!=0) {
                            n=NG[j+1];
                            if (NG[j+2]==0) {
                                c=NG[j+3];
                                r=NG[j+4];
                                for (k = 0; k < nl && P[r+k][c]=='X' ; k++) {}
                                if (k==nl) {
                                    ok2=1;
                                }
                            } else {
                                r=NG[j+3];
                                c=NG[j+4];
                                for (k = 0; k < nl && P[r][c+k]=='X' ; k++) {}
                                if (k==nl) {
                                    ok2=1;
                                }
                            }
                            if (ok2==1){
                                if (NG[j]==2)
                                    s=1;
                                NG[j]=0;
                                te=0;
                                nag++;
                                NG[0]=5;
                                break;
                            }
                        }
                        j+=5;
                        NG[0]++;
                    }while (NG[0]<5);
                }
                // te == 2 -> hit, direction known
                if (te==2) {
                    if (ra[0]==1) {
                        srb++;
                    } else if (ra[0]==2) {
                        scb--;
                    } else if (ra[0]==3) {
                        srb--;
                    } else if (ra[0]==4) {
                        scb++;
                    }
                    te=1;
                }
                // te == 3 -> hit, moving in known direction
                if (te==3) {
                    if (ra[0]==1 && srb-1>=0 && P[srb-1][scb]!='O' && P[srb-1][scb]!='X') {
                        srb--;
                    } else if (ra[0]==2 && scb+1<=9 && P[srb][scb+1]!='O' && P[srb][scb+1]!='X') {
                        scb++;
                    } else if (ra[0]==3 && srb+1<=9 && P[srb+1][scb]!='O' && P[srb+1][scb]!='X') {
                        srb++;
                    } else if (ra[0]==4 && scb-1>=0 && P[srb][scb-1]!='O' && P[srb][scb-1]!='X') {
                        scb--;
                    } else
                        te=4;
                }
                // te == 4 -> hit, reversing direction
                if (te==4) {
                    if (ra[0]==1) {
                        if (tsr+2>9 || P[tsr+2][tsc]=='O' || P[tsr+2][tsc]=='X') {
                            srb--;
                            te=1;
                        }else {
                            srb=tsr+2;
                            scb=tsc;
                            tsr++;
                            te=3;
                            ra[0]=3;
                        }
                    } else if (ra[0]==2) {
                        if (tsc-2<0 || P[tsr][tsc-2]=='O' || P[tsr][tsc-2]=='X') {
                            scb--;
                            te=1;
                        }else {
                            scb=tsc-2;
                            srb=tsr;
                            tsc--;
                            te=3;
                            ra[0]=4;
                        }
                    } else if (ra[0]==3) {
                        if (tsr-2<0 || P[tsr-2][tsc]=='O' || P[tsr-2][tsc]=='X') {
                            srb--;
                            te=1;
                        }else {
                            srb=tsr-2;
                            scb=tsc;
                            tsr--;
                            te=3;
                            ra[0]=1;
                        }
                    } else if (ra[0]==4) {
                        if (tsc+2>9 || P[tsr][tsc+2]=='O' || P[tsr][tsc+2]=='X') {
                            scb++;
                            te=1;
                        }else {
                            srb=tsr;
                            scb=tsc+2;
                            tsc++;
                            te=3;
                            ra[0]=2;
                        }
                    }
                }
                int aj[4] = {1, 2, 3, 4};
                int daj = 4;
                int raj;

                if (te!=1)
                    continue;
                do {
                    ok2=1;
                    if (daj==0) {
                        for (int m = 0; m < 4; m++) {
                            aj[m] = m + 1;
                        }
                        daj=4;
                        ok2=1;
                        do {
                            if (daj==0) {
                                te=0;
                                break;
                            }
                            raj = rand() % daj;
                            ra[0]=aj[raj];
                            for (int m = raj; m < daj - 1; m++) {
                                aj[m] = aj[m + 1];
                            }
                            daj--;

                            if (ra[0]==1 && srb-1>=0 && P[srb-1][scb]=='X') {
                                srb=srb-1;
                            } else if (ra[0]==2 && scb+1<=9 && P[srb][scb+1]=='X') {
                                scb=scb+1;
                            } else if (ra[0]==3 && srb+1<=9 && P[srb+1][scb]=='X') {
                                srb=srb+1;
                            } else if (ra[0]==4 && scb-1>=0 && P[srb][scb-1]=='X') {
                                scb=scb-1;
                            } else {
                                ok2=0;
                            }
                            if (ok2==1) {
                                for (int m = 0; m < 4; m++) {
                                    aj[m] = m + 1;
                                }
                                daj=4;
                            }
                        }while (ok2==0);
                        if (te==0)
                            break;
                    }
                    raj = rand() % daj;
                    ra[0]=aj[raj];
                    for (int m = raj; m < daj - 1; m++) {
                        aj[m] = aj[m + 1];
                    }
                    daj--;
                    if (ra[0]==1 && srb-1>=0 && P[srb-1][scb]!='O' && P[srb-1][scb]!='X') {
                        tsr=srb-1;
                        tsc=scb;
                    } else if (ra[0]==2 && scb+1<=9 && P[srb][scb+1]!='O' && P[srb][scb+1]!='X') {
                        tsr=srb;
                        tsc=scb+1;
                    } else if (ra[0]==3 && srb+1<=9 && P[srb+1][scb]!='O' && P[srb+1][scb]!='X') {
                        tsr=srb+1;
                        tsc=scb;
                    } else if (ra[0]==4 && scb-1>=0 && P[srb][scb-1]!='O' && P[srb][scb-1]!='X') {
                        tsr=srb;
                        tsc=scb-1;
                    } else {
                        ok2=0;
                    }
                }while (ok2==0);
            }while (ok==0);
        }while (nag<5 && nab<5);
        gotoxy(0,0);
        for (i = 1; i < 10 ; ++i) {
            gotoxy(0,i);
            printf("                              ");
        }
        gotoxy(3,6);
        if (nab==5)
            printf("il giocatore ha vinto!");
        else
            printf("il giocatore ha perso!");
        gotoxy(41, 2);
        i=2;
        for (r = 0; r < 10 ; r++) {
            for (c = 0; c < 10 ; c++) {
                printf(" %c", P[r][c]);
            }
            i++;
            gotoxy(41, i);
        }
        gotoxy(91, 2);
        i=2;
        for (r = 0; r < 10 ; r++) {
            for (c = 0; c < 10 ; c++) {
                switch (B[r][c]) {
                    case 0:
                        printf(" -");
                        break;
                    case 1:
                        printf(" O");
                        break;
                    case 2:
                        printf(" H");
                        break;
                    case 3:
                        printf(" X");
                }
            }
            i++;
            gotoxy(91, i);
        }
        gotoxy(4,7);
        printf("vuoi giocare ancora?");
        gotoxy(5,8);
        printf("SI / NO");
        gotoxy(5,9);
        fflush(stdin);
        scanf("%s", rf);
    }while (rf[0]=='S' || rf[0]=='s');
    return 0;
}
void gotoxy(short x, short y){
    COORD pos ={x,y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
