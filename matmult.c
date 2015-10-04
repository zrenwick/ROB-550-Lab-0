
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>



int checkInput(int argc, char** argv, FILE ** outfile){
    char *outfile_str = NULL;
    int flag = 0;
    int string_set_flag = 0;

    while((flag = getopt(argc, argv, "o:")) != -1){
        switch(flag){
            case 'o':
                outfile_str = optarg;
                string_set_flag = 1;
                break;
            case '?':
                fprintf(stderr, "Error: The -o flag requires a .csv file name as input\n");
                return -1;
        }
    }    

    if(!string_set_flag){
        fprintf(stderr, "Error: The -o flag must be used to provide a .csv file name as input\n");
        return -1;
    }
    
    if(strstr(outfile_str, ".csv")==NULL){
        fprintf(stderr, "Error: The -o flag requires a .csv file name as input\n");
        return -1;
    }

    if(outfile_str!=NULL){
        if ((*outfile = fopen(outfile_str,"w")) == NULL) {
            fprintf(stderr,"Error opening output file.\n");  
            return -1;
        }
    }
    else{
        fprintf(stderr, "A .csv output file must be specified using the -o flag\n");
        return -1;
    }                 

    return 0;
}

void readMatrix(FILE * Mfile, int rownum, int colnum, double * mat){
    int row_cnt = 0;
    int col_cnt = 0;
    for(row_cnt=0; row_cnt<rownum; row_cnt++){
        for(col_cnt=0; col_cnt<colnum; col_cnt++){
            if(col_cnt==(colnum-1)){
                fscanf(Mfile, "%lf", &mat[row_cnt*colnum + col_cnt]);
            }
            else{ 
                fscanf(Mfile, "%lf,", &mat[row_cnt*colnum + col_cnt]);
            }
        }
    }
}

void matrixMult(double *a_mat, int a_rownum, int a_colnum, double *b_mat, int b_rownum, int b_colnum, double *ab_mat){
    int a_row_cnt = 0;
    int b_row_cnt = 0;
    int b_col_cnt = 0;
    int ab_rownum = a_rownum;
    int ab_colnum = b_colnum;

    // Multiplication starts here
    for(a_row_cnt=0; a_row_cnt<a_rownum; a_row_cnt++){
        for(b_col_cnt=0; b_col_cnt<b_colnum; b_col_cnt++){
            for(b_row_cnt=0; b_row_cnt<b_rownum; b_row_cnt++){
                 ab_mat[a_row_cnt*ab_colnum + b_col_cnt] += a_mat[a_row_cnt*a_colnum + b_row_cnt]*b_mat[b_row_cnt*b_colnum + b_col_cnt];
            }
        }
    }
}

void printOutput(int ab_rownum, int ab_colnum, double * ab_mat, FILE *outfile){
   int a_row_cnt = 0;
   int a_col_cnt = 0;
   for(a_row_cnt=0; a_row_cnt<ab_rownum; a_row_cnt++){
        for(a_col_cnt=0; a_col_cnt<ab_colnum; a_col_cnt++){
            if(a_col_cnt==(ab_colnum-1)){  //If we're printing the last column
                fprintf(outfile, "%lf\n",ab_mat[a_row_cnt*ab_colnum + a_col_cnt]); //use a newline instead of a comma
            } else{
                fprintf(outfile, "%lf,",ab_mat[a_row_cnt*ab_colnum + a_col_cnt]); // print a comma
            }
        }        
    }    
}

int main(int argc, char** argv){

    FILE *Afile = NULL;
    FILE *Bfile = NULL;
    FILE *outfile = NULL;

    

    int a_rownum = 0;
    int a_colnum = 0;
    int b_rownum = 0;
    int b_colnum = 0;
    int a_row_cnt = 0;
    int a_col_cnt = 0;
    int b_row_cnt = 0;
    int b_col_cnt = 0;

    if(checkInput(argc, argv, &outfile)==-1){
        return -1;
    }

    fprintf(stdout, "Please enter the number of rows and columns in matrix A (<rows> <cols>): ");
    scanf("%d %d", &a_rownum, &a_colnum);

    if((a_rownum<0)||(a_colnum<0)){
        printf("Error: All matrix dimensions must be positive integers\n");
        return -1;
    }

    fprintf(stdout, "Please enter the number of rows and columns in matrix B (<rows> <cols>): ");
    fscanf(stdin, "%d %d", &b_rownum, &b_colnum);

    if((b_rownum<0)||(b_colnum<0)){
        fprintf(stderr, "Error: All matrix dimensions must be positive integers\n");
        return -1;
    }

    if(a_colnum!=b_rownum){
        fprintf(stderr, "\nError: The number of columns in matrix A \nmust match the number of rows in matrix B \nfor A*B to be possible.\n\n");
        return -1;
    }

    int ab_rownum = a_rownum;
    int ab_colnum = b_colnum;

    double *a_mat = malloc(sizeof(double)*a_rownum*a_colnum);
    double *b_mat = malloc( sizeof(double)*b_rownum*b_colnum);
    double *ab_mat = malloc(sizeof(double)*ab_rownum*ab_colnum);

    // Zero return value indicates file open error;
    // Error checks are included in the below code
    if ((Afile = fopen("A.csv","r")) == NULL) {
      fprintf(stderr, "Error opening A.csv\n"); 
      return -1;
    }
    if ((Bfile = fopen("B.csv","r")) == NULL) {
      fprintf(stderr, "Error opening B.csv\n");  
      return -1;
    }
    


    readMatrix(Afile, a_rownum, a_colnum, a_mat);
    readMatrix(Bfile, b_rownum, b_colnum, b_mat);

    clock_t start = clock(), diff;

    matrixMult( a_mat, a_rownum, a_colnum, b_mat, b_rownum, b_colnum, ab_mat);
    printOutput(ab_rownum, ab_colnum, ab_mat, outfile);

    fclose(outfile);
    return 0;
}


    

