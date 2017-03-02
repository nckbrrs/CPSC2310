#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>
double second();
double t_start,t_end;
double sum,row_sum;

double a[1000][1000],b[1000][1000],c[1000][1000],d[1000][1000];

main(){
  int i,j,k;
  double t00;
/* set coefficients so that result matrix should have 
 * row entries equal to (1/2)*n*(n-1)*i in row i
 */
  for (i=0;i<1000;i++){
    for (j=0;j<1000;j++){
      a[i][j] = b[i][j] = (double) i;
    }
  }
/* try to flush cache */
  for(i=0;i<1000;i++){
    for (j=0;j<1000;j++){
      d[i][j] = 0.0;
    }
  }
/* begin */
t_start=second();
  for(i=0;i<1000;i++){
    for(j=0;j<1000;j++){
      c[i][j]=0.0;
    }
  }
  for(j=0;j<1000;j++){
    for(k=0;k<1000;k++){
      t00=b[k  ][j  ];
      for(i=0;i<1000;i++){
        c[i  ][j  ]+=a[i  ][k  ]*t00;
      }
    }
  }
/* end */
t_end = second();
/* check result */
  sum = 0.5*((double)(1000*(1000-1)));
  for (i=0;i<1000;i++){
    row_sum = ((double)i)*sum;
    for (j=0;j<1000;j++){
      if (c[i][j]!=row_sum){
        printf("error in result entry c[%d][%d]: %e != %e\n",
               i,j,c[i][j],row_sum);
        exit(1);
      }
    }
  }
  printf("for mm algorithm jki");
  printf(" utime is %10.2f secs\n",t_end-t_start);
}
double second(){
  struct rusage ru;
  double t;
  getrusage(RUSAGE_SELF,&ru);
  t = ((double)ru.ru_utime.tv_sec) +
    ((double)ru.ru_utime.tv_usec)/1.0e6;
  return t;
}
