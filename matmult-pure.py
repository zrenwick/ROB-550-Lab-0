

import sys
import string
import time

def matrixMult(A_row_txt, A_numrows, B_row_txt, B_numrows, B_numcols, C_mat):
    for a_row_cnt in range(A_numrows):
        for b_col_cnt in range(B_numcols):
            for b_row_cnt in range(B_numrows):
                C_mat[a_row_cnt][b_col_cnt] += float(A_row_txt[a_row_cnt][b_row_cnt])*float(B_row_txt[b_row_cnt][b_col_cnt])
    return C_mat

if((len(sys.argv)<3) or (sys.argv[1]!='-o')):
    raise StandardError("Please specify the output file using the following format: 'matmult-pure.py -o <filename>'")

if((string.find(sys.argv[2],".csv"))==-1):
    raise StandardError("The output filename provided must be a .csv file");
    
outfile_str = sys.argv[2];

outfile = open(outfile_str, 'w');

Afile = open("A.csv", 'r');
Bfile = open("B.csv", 'r');




A_text = Afile.read();
A_row_txt = A_text.split('\n')
if(A_row_txt[-1]==''):
    A_row_txt = A_row_txt[0:-1]

B_text = Bfile.read();
B_row_txt = B_text.split('\n')[0:-1]
if(B_row_txt[-1]==''):
    B_row_txt = B_row_txt[0:-1]

A_numrows = len(A_row_txt);
B_numrows = len(B_row_txt);

for row in range(len(A_row_txt)):
    A_row_txt[row] = A_row_txt[row].split(',')

 
for row in range(len(B_row_txt)):
    B_row_txt[row] = B_row_txt[row].split(',')

A_numcols = len(A_row_txt[0])
B_numcols = len(B_row_txt[0])

C_mat = [0]*A_numrows
for row in range(A_numrows):
    C_mat[row] = [0]*B_numcols;

#Actual multiplication
start = time.time()
C_mat = matrixMult(A_row_txt, A_numrows, B_row_txt, B_numrows, B_numcols, C_mat)
elapsed = time.time()-start
print elapsed


for a_row_cnt in range(A_numrows):
    for b_col_cnt in range(B_numcols):
        if(b_col_cnt==(B_numcols-1)):  #If we're printing the last column
            outfile.write(str(C_mat[a_row_cnt][b_col_cnt])+"\n") #use a newline instead of a comma
        else:
            outfile.write(str(C_mat[a_row_cnt][b_col_cnt])+",") # print a comma  

outfile.close()



