void read(int ***t, int *n, int *m);
void cp(int **fromcp, int **tocp, int n, int m);
void alloc(int ***t, int n, int m);
int pick(int *n, int *m);
void toFree(int **t, int n, int m);
int nozeros(int **t, int n, int m);   //checks for 0s
void zero_mat(int **t, int n, int m); //fills the matrix with 0s
void assert_business(int solcount, int rtype, int n, int m);

void toFree(int **t, int n, int m){
    for(int i = 0; i< n; i++)
        free(t[i]);
    free(t);
}
int nozeros(int **t, int n, int m){
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
        if(t[i][j] == 0)
            return 0;
    return 1;
}
void zero_mat(int **t, int n, int m){
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            t[i][j] = 0;
}

//citeste matricea
void read(int ***t, int *n, int *m){
    FILE *fp = fopen("matrix.in", "r");
    if(fp == NULL){
        printf("error reading from the file\n");
        exit(EXIT_FAILURE);
    }
    fscanf(fp,"%d", &*n);
    fscanf(fp,"%d", &*m);
    
    (*t) = (int **)malloc(*n *sizeof(int *));
    
    if((*t) == NULL){
        printf("malloc error\n");
        exit(EXIT_FAILURE);
    }      

    for(int i = 0; i < *n; i++){
        (*t)[i] = (int *)malloc(*m * sizeof(int));
        if((*t)[i] == NULL){
            printf("malloc error\n");
            for(int j = 0; j < i; j++)
                free((*t)[j]);
            free(*t);
            exit(EXIT_FAILURE);
        } 
    }

    fclose(fp);
}

void cp(int **fromcp, int **tocp, int n, int m){
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            tocp[i][j] = fromcp[i][j];
}

void alloc(int ***t, int n, int m){
    (*t) = (int **)malloc(n *sizeof(int *));
    
    if((*t) == NULL){
        printf("malloc error\n");
        exit(EXIT_FAILURE);
    }      

    for(int i = 0; i < n; i++){
        (*t)[i] = (int *)malloc(m * sizeof(int));
        if((*t)[i] == NULL){
            printf("malloc error\n");
            for(int j = 0; j < i; j++)
                free((*t)[j]);
            free(*t);
            exit(EXIT_FAILURE);
        } 
    }
}

void assert_business(int solcount, int rtype, int n, int m){
    switch (rtype){
    case 1:
        //one no sol case
        assert(solcount == 0);
        break;
    case 2:
        //one square, single sol case
        assert(solcount == 1);
        break;
    case 3:
        //2/4: 3 sol case
        assert(solcount == 3);
        break;
    default:
        break;
    }
}

int pick(int *n, int *m){
    int var;
    printf("0: uses the matrix.in data\n");
    printf("1: checks for n = 1, m = 1\n");
    printf("2: checks for n = 2, m = 2\n");
    printf("3: checks for n = 2, m = 4\n");
    printf("4: reads n&m from keyboard\n");
    scanf("%d", &var);
    switch (var)
    {
    case 0:
        return 0;
        break;
    case 1:
        *n = 3;
        *m = 15;
        return 1;
        break;
    case 2:
        *n = 2;
        *m = 2;
        return 2;
        break;
    case 3:
        *n = 2;
        *m = 4;
        return 3;
        break;
    case 4:
        scanf("%d", &*n);
        scanf("%d", &*m);
        return 4;
        break;
    default:
        return 0;
        break;
    }
    return 0;
}