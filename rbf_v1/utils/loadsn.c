#define real float

real *
loadsn(char *filename, int *m, int *n)
{
  return 0 ;
} ;

int 
main(int argc, char **args)
{
  int m, n, i, j ;
  real * M=loadsn(args[1], &m, &n) ;
  for (i=0;i<m;i++)
    {
      for (j=0; j<n; j++)
	  printf("%f, ", M[i*n+j]) ;
      printf("\n") ;
    } ;
} ;
