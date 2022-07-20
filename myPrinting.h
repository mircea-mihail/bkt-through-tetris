void pred();
void pgreen();
void pyellow();
void pblue();
void ppurple();
void plightblue();
void pp();
void pmatrix(int **t, int n, int m);
void pnum(int **t, int n, int m);
void printsol(int solcount, int nobkt);

void pred(){
    printf( "\033[41m \033[0m");
}
void pgreen(){
    printf( "\033[42m \033[0m");
}
void pyellow(){
    printf( "\033[43m \033[0m");
}
void pblue(){
    printf("\033[44m \033[0m");
}
void ppurple(){
    printf( "\033[45m \033[0m");
}
void plightblue(){
    printf( "\033[46m \033[0m");
}
void pp(){
    printf( "\033[40m \033[0m");
}
void printsol(int solcount, int nobkt){
    printf("sol count: %d\nbkt count: %d\n", solcount, nobkt);
}

void pmatrix(int **t, int n, int m){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(t[i][j] == 0){
                pp();
                pp();
            }
            else
            switch(t[i][j] % 6){
                case 0:
                    pred();
                    pred();
                    break;
                case 1:
                    pgreen();
                    pgreen();
                    break;
                case 2:
                    pyellow();
                    pyellow();
                    break;
                case 3:
                    pblue();
                    pblue();
                    break;
                case 4:
                    ppurple();
                    ppurple();
                    break;
                case 5:
                    plightblue();
                    plightblue();
                    break;
                default:
                    break;
            }
        }
        printf("\n");
    }
}
void pnum(int **t, int n, int m){
    FILE *fp = fopen("sols.out", "a");
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++)
            fprintf(fp, "%d ", t[i][j]);
        fprintf(fp, "\n");
    }
    fprintf(fp, "\n");
    fclose(fp);
}