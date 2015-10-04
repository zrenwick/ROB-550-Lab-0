
#include <stdio.h>  // C input/output functions including FILEs
#include <stdlib.h>
#include <string.h>

int main()
{
  FILE *infile, *outfile;
  int a;
  int b;
  int case_num=0;

  // Zero return value indicates file open error;
  // Error checks are included in the below code
  if ((infile = fopen("inputdata.txt","r")) == NULL) {
    fprintf(stderr, "Error opening input file.\n"); 
    return -1;
  }
  if ((outfile = fopen("outputdata.txt","w")) == NULL) {
    fprintf(stderr, "Error opening output file.\n");  
    return -1;
  }
  
  while(1){
	  fscanf(infile,"%d %d ", &a, &b);
	  //printf("%d,%d \n", a, b);
	  if(a==0){
            break;
          }
          case_num++;
          printf("Case %d:\n",case_num);
          fprintf(outfile,"Case %d:\n",case_num);
	  unsigned char *in_word_array;
	  unsigned char *out_word_array;
	  unsigned char *out_byte_positive_array;
	  unsigned char *out_byte_negative_array;
	  unsigned char *in_byte_positive_array;
	  unsigned char *in_byte_negative_array;

	  int num_bits = a*8;

	  in_word_array = malloc(sizeof(unsigned char)*(a*b));
	  out_word_array = malloc(sizeof(unsigned char)*(a*b));
	  out_byte_positive_array = malloc(sizeof(unsigned char)*a);
	  out_byte_negative_array = malloc(sizeof(unsigned char)*a);
	  in_byte_positive_array = malloc(sizeof(unsigned char)*a);
	  in_byte_negative_array = malloc(sizeof(unsigned char)*a);

	  int k = 0;
	  for(k=0;k<(a*b);k++){
	    fscanf(infile, "%02x", &in_word_array[k]);
	  }

	  for(k=0;k<(a*b);k++){
	    fscanf(infile, "%02x", &out_word_array[k]);
	  }
          /*
	  for(k=0;k<(a*b);k++){
	    printf("%02x", in_word_array[k]);
	  }
	  printf("\n");

	  for(k=0;k<(a*b);k++){
	    printf("%02x", out_word_array[k]);
	  }
	  printf("\n");
          */
	  for(k=0;k<a;k++){
	    out_byte_negative_array[k] = 0x00;
	    in_byte_negative_array[k] = 0x00;
	    out_byte_positive_array[k] = 0xff;
	    in_byte_positive_array[k] = 0xff;  
	  }

	  int word_num = 0;
	  for(word_num=0; word_num<b; word_num++){
	    for(k=(a-1);k>=0;k--){
	      out_byte_negative_array[k] = (out_byte_negative_array[k] | out_word_array[((word_num*a) + k)]); 
	      in_byte_negative_array[k] = (in_byte_negative_array[k] | in_word_array[((word_num*a) + k)]);
	      out_byte_positive_array[k] = (out_byte_positive_array[k] & out_word_array[((word_num*a) + k)]); 
	      in_byte_positive_array[k] = (in_byte_positive_array[k] & in_word_array[((word_num*a) + k)]); 
	    }
	  }
	  /*
          printf("out_byte_positive_array after\n");
	  for(k=0;k<a;k++){
	    printf("%02x    ", out_byte_positive_array[k]);
	  }
	  printf("\n");

	  //printf("out_byte_negative_array after\n");
	  for(k=0;k<a;k++){
	    printf("%02x    ", out_byte_negative_array[k]);
	  }
	  printf("\n");
          */
	  int kk = 0;
	  char status[] = "  ?"; 
	  printf("Bit:    ");
	  fprintf(outfile,"Bit:    ");
	  for(k =(num_bits-1);k>=0;k--){
	    printf("%2d ", k);  
  	    fprintf(outfile,"%2d ", k);  
	  }
	  printf("\nStatus:");
          fprintf(outfile,"\nStatus:"); 
	  for(k=0;k<a;k++){
	    for(kk=0;kk<8;kk++){
	      strcpy(status,"  ?");
	      //tester = ((1<<7)>>kk);
	      //printf("\n%x\n",((1<<7)>>kk));
	      //printf("%x\n",((~out_byte_positive_array[k])&((1<<7)>>kk)));
	      if(((~out_byte_positive_array[k])&((1<<7)>>kk))&&((out_byte_negative_array[k])&((1<<7)>>kk))){
		strcpy(status," OK");
	      }
	      if(((~in_byte_positive_array[k])&((1<<7)>>kk))&&(!((~out_byte_positive_array[k])&((1<<7)>>kk)))){  //If a zero came into the input, but no zero ever came out of the output
		strcpy(status,"  +");
	      } 
	      else{ 
		if(((in_byte_negative_array[k])&((1<<7)>>kk))&&(!((out_byte_negative_array[k])&((1<<7)>>kk)))){
		  strcpy(status,"  -");
		}
	      }
	      printf("%s",status);
              fprintf(outfile,"%s",status);
	    }

	  }
	  free(in_word_array);
          in_word_array = NULL;
	  free(out_word_array);
          out_word_array = NULL;
	  free(out_byte_positive_array);
          out_byte_positive_array = NULL;
	  free(out_byte_negative_array);
          out_byte_negative_array = NULL;
	  free(in_byte_positive_array);
          in_byte_positive_array = NULL;
	  free(in_byte_negative_array);
          in_byte_negative_array = NULL;
          
 	  printf("\n");
	  fprintf(outfile,"\n");
  }


  
  fclose(infile);
  fclose(outfile);

  return 0;
  
}
