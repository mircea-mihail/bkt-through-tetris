//rlutil -- github library for more complex colours
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "myPrinting.h"
#include "basicUtility.h"

int color = 1;
int n, m;
int noShapes = 15;
int solcount = 0; 
int nobkt = 0;

//main code
int fit(int **t, int i, int j, int v);
void bkt(int **t,int i, int j);

int main(){
    FILE *fp = fopen("sols.out", "w");
    fclose(fp);
    int **t, rtype = pick(&n, &m);

    if(rtype == 0)
        read(&t, &n, &m);
    else
        alloc(&t, n, m);

    if(n*m % 4 == 0){
        zero_mat(t, n, m);
        bkt(t, n-1, 0);
    }
    else{
        printf("the board cannot be entirely filled\nusing only tetris blocks\n");
    }

    FILE *fp1 = fopen("sols.out", "a");
    fprintf(fp1, "sol count: %d\nbkt count: %d\n", solcount, nobkt);
    fclose(fp1);

    assert_business(solcount, rtype, n, m);

    printsol(solcount, nobkt);
    toFree(t, n, m);

    return 0;
}

void bkt(int **t,int i, int j){
    int **neverForget;

    alloc(&neverForget, n, m);

    cp(t, neverForget, n, m);
    nobkt ++;
    int ii, jj;
    //i and j are board coordonates 
    int v;
    for(v = 1; v <= noShapes; v++){
        ii = i;
        jj = j;
        //fitiing the current shape
        if(t[i][j] == 0){
            fit(t, i, j, v);
        }
        //partial solution: the current square has been filled
        if(t[i][j] != 0){
            //full solution: there are no zeros left in the matrix
            if(nozeros(t, n, m) == 1){
                pmatrix(t, n, m);
                printf("\n");
                pnum(t, n, m);
                solcount ++;
            }
            //if the current square is full, the next 0 square is saught
            else{
                while(t[ii][jj] != 0 && (ii != 0 || jj != m-1)){
                    if(jj < m-1)
                        jj++;
                    if(jj == m-1 && ii != 0 && t[ii][jj] != 0){
                        ii -= 1;
                        jj = 0;
                    }
                }
                bkt(t, ii, jj);
            }
            //when looping back through the for, we need the previous matrix state,
            //from before entering the for, in order to attempt another shape
            color --;
            cp(neverForget, t, n, m);
        }
    }
    toFree(neverForget, n, m);
}

int fit(int **t, int i, int j, int v){
    
    if(i >= n || j >= m || i < 0 || j < 0){
        printf("fit error\n");
        exit(EXIT_FAILURE);
    }
    switch (v){
        //THE I

        // ----lenghtwise 
        case 1:
            if(m - j >= 4 && (t)[i][j] == 0 && (t)[i][j+1] == 0 && (t)[i][j+2] == 0 && (t)[i][j+3] == 0){
                (t)[i][j] = color;
                (t)[i][j+1] = color;
                (t)[i][j+2] = color;
                (t)[i][j+3] = color;
                color++;
                return 1;
            }
            break;
        //- heightwise
        //-
        //-
        //-
        case 2:
            if(i >= 3 && (t)[i][j] == 0 && (t)[i-1][j] == 0 && (t)[i-2][j] == 0 && (t)[i-3][j] == 0){
                (t)[i][j] = color;
                (t)[i-1][j] = color;
                (t)[i-2][j] = color;
                (t)[i-3][j] = color;
                color++;
                return 2;
            }
            break;

        //THE SQUARE

        // -- the one pos
        // --
        case 3:
            if(m - j >= 2 && i > 0 && (t)[i-1][j] == 0 && (t)[i-1][j+1] == 0 && (t)[i][j] == 0 && (t)[i][j+1] == 0){
                (t)[i-1][j] = color;
                (t)[i-1][j+1] = color;
                (t)[i][j] = color;
                (t)[i][j+1] = color;
                color++;
                return 3;
            }
            break;
        
        //THE L
        //  - on back L
        //---   
        case 4:
            if(m - j >= 3 && i >=1 && (t)[i][j] == 0 && (t)[i][j+1] == 0 && (t)[i][j+2] == 0 && (t)[i-1][j+2] == 0){
                (t)[i][j] = color;
                (t)[i][j+1] = color;
                (t)[i][j+2] = color;
                (t)[i-1][j+2] = color;
                color++;
                return 4;
            }
            break;        
        //--- on front L
        //-
        case 5:
            if(m - j >= 3 && i >=1 && (t)[i][j] == 0 && (t)[i-1][j] == 0 && (t)[i-1][j+1] == 0 && (t)[i-1][j+2] == 0){
                (t)[i][j] = color;
                (t)[i-1][j] = color;
                (t)[i-1][j+1] = color;
                (t)[i-1][j+2] = color;
                color++;
                return 5;
            }
            break;  
        //-  regular L
        //-
        //--
        case 6:
            if(m - j >= 2 && i >=2 && (t)[i][j] == 0 && (t)[i][j+1] == 0 && (t)[i-1][j] == 0 && (t)[i-2][j] == 0){
                (t)[i][j] = color;
                (t)[i][j+1] = color;
                (t)[i-1][j] = color;
                (t)[i-2][j] = color;
                color++;
                return 6;
            }
            break;
        //-- upside down L
        // -
        // -
        case 7:
            if(j-1 >= 0 && m - j >= 1 && i >=2 && (t)[i][j] == 0 && (t)[i-1][j] == 0 && (t)[i-2][j] == 0 && (t)[i-2][j-1] == 0){
                (t)[i][j] = color;
                (t)[i-1][j] = color;
                (t)[i-2][j] = color;
                (t)[i-2][j-1] = color;
                color++;
                return 7;
            }
            break;

        //the ZZ top

        //--  basic z
        // --

        case 8:
            if(j-1 >= 0 && m - j >= 2 && i >=1 && (t)[i][j] == 0 && (t)[i][j+1] == 0 && (t)[i-1][j] == 0 && (t)[i-1][j-1] == 0){
                (t)[i][j] = color;
                (t)[i][j+1] = color;
                (t)[i-1][j] = color;
                (t)[i-1][j-1] = color;
                color++;
                return 8;
            }
            break;        
        // - tall z
        //-- 
        //-
        case 9:
            if(m - j >= 2 && i >= 2 && (t)[i][j] == 0 && (t)[i-1][j] == 0 && (t)[i-1][j+1] == 0 && (t)[i-2][j+1] == 0){
                (t)[i][j] = color;
                (t)[i-1][j] = color;
                (t)[i-1][j+1] = color;
                (t)[i-2][j+1] = color;
                color++;
                return 9;
            }
            break;  
        // -- rev z
        //--
        case 10:
            if(m - j >= 3 && i >=1 && (t)[i][j] == 0 && (t)[i][j+1] == 0 && (t)[i-1][j+1] == 0 && (t)[i-1][j+2] == 0){
                (t)[i][j] = color;
                (t)[i][j+1] = color;
                (t)[i-1][j+1] = color;
                (t)[i-1][j+2] = color;
                color++;
                return 10;
            }
            break;
        //- rev tall z
        //--
        // - 
        case 11:
            if(j - 1 >= 0 && m - j >= 1 && i >= 2 && (t)[i][j] == 0 && (t)[i-1][j] == 0 && (t)[i-1][j-1] == 0 && (t)[i-2][j-1] == 0){
                (t)[i][j] = color;
                (t)[i-1][j] = color;
                (t)[i-1][j-1] = color;
                (t)[i-2][j-1] = color;
                color++;
                return 11;
            }
            break;

        //the pp

        // -  basic pp
        //---

        case 12:
            if(m - j >= 3 && i >= 1 && (t)[i][j] == 0 && (t)[i][j+1] == 0 && (t)[i][j+2] == 0 && (t)[i-1][j+1] == 0){
                (t)[i][j] = color;
                (t)[i][j+1] = color;
                (t)[i][j+2] = color;
                (t)[i-1][j+1] = color;
                color++;
                return 12;
            }
            break;        
        //-  tall pp
        //-- 
        //-
        case 13:
            if(m - j >= 2 && i >= 2 && (t)[i][j] == 0 && (t)[i-1][j] == 0 && (t)[i-1][j+1] == 0 && (t)[i-2][j] == 0){
                (t)[i][j] = color;
                (t)[i-1][j] = color;
                (t)[i-1][j+1] = color;
                (t)[i-2][j] = color;
                color++;
                return 13;
            }
            break;  
        //--- rev pp
        // -
        case 14:
            if(j-1 >= 0 && m - j >= 2 && i >=1 && (t)[i][j] == 0 && (t)[i-1][j] == 0 && (t)[i-1][j+1] == 0 && (t)[i-1][j-1] == 0){
                (t)[i][j] = color;
                (t)[i-1][j] = color;
                (t)[i-1][j+1] = color;
                (t)[i-1][j-1] = color;
                color++;
                return 14;
            }
            break;
        // - rev tall pp
        //--
        // - 
        case 15:
            if(j - 1 >= 0 && m - j >= 1 && i >= 2 && (t)[i][j] == 0 && (t)[i-1][j] == 0 && (t)[i-1][j-1] == 0 && (t)[i-2][j] == 0){
                (t)[i][j] = color;
                (t)[i-1][j] = color;
                (t)[i-1][j-1] = color;
                (t)[i-2][j] = color;
                color++;
                return 15;
            }
            break;
        default:
            break;
    }
    
    // printf("no fit :(\n");
    return 0;
}