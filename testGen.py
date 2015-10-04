


import sys
import numpy as np

if(len(sys.argv)<3):
    raise StandardError("Not enough input arguments were provided.  Two integers must be provided specifying the desired number of rows and columns.")

elif(len(sys.argv)>3):
    raise StandardError("Too many input arguments were provided.  Two integers must be provided specifying the desired number of rows and columns.")

try:
    num_rows = int(sys.argv[1])
except ValueError:
    raise StandardError("Expected integer for <rows>")

try:
    num_cols = int(sys.argv[2])
except ValueError:
    raise StandardError("Expected integer for <cols>")

if((num_rows<0) or (num_cols<0)):
    raise StandardError("row and column numbers must be positive integers")

norm_mat = np.random.normal(0, 1, (num_rows, num_cols))

for row in range(0,norm_mat.shape[0]):
    for col in range(0, norm_mat.shape[1]):
        if(col < (norm_mat.shape[1]-1)):
            addnl_str = ','
        else:
            addnl_str = '\n'

        sys.stdout.write(str(norm_mat[row, col])+addnl_str)


