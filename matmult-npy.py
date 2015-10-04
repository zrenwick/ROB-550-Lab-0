

import sys
import string
import numpy as np
import time


def matMult(A_mat, B_mat):
    C_mat = np.dot(A_mat, B_mat)
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

A_mat = np.asarray(A_row_txt)
B_mat = np.asarray(B_row_txt)

A_mat = A_mat.astype(np.float)
B_mat = B_mat.astype(np.float)

#Actual multiplication
start = time.time()

C_mat = matMult(A_mat, B_mat);

elapsed = time.time()-start
print elapsed

for a_row_cnt in range(A_numrows):
    for b_col_cnt in range(B_numcols):
        if(b_col_cnt==(B_numcols-1)):  #If we're printing the last column
            outfile.write(str(C_mat[a_row_cnt][b_col_cnt])+"\n") #use a newline instead of a comma
        else:
            outfile.write(str(C_mat[a_row_cnt][b_col_cnt])+",") # print a comma  

outfile.close()



