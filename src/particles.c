#include "particles.h"
int particles_init(Particles* P, int s_num, int p_num, int d)
{
  int ret = 0;//return value
  P->species_num = s_num;
  P->particle_num = p_num;
  P->dim = d;
  
  P->pos = (double**) calloc (s_num,sizeof(double*));
  P->vel = (double**) calloc (s_num,sizeof(double*));
  P->pos_1 = (double**) calloc (s_num,sizeof(double*));
  P->vel_1 = (double**) calloc (s_num,sizeof(double*));
  
  double** tmp [] = {P->pos,P->vel,P->pos_1,P->vel_1};
  int i,j;
  for (j=0;j<4;j++)
  {
    for (i=0;i<s_num;i++)
    {
      tmp[j][i] = (double*) calloc (p_num*d,sizeof(double));
      if (tmp[j][i] == NULL)
      {
        ret = 1;
        goto end;
      }
    }
  }
  
 end:
  // error handling
  if (ret == 1)
  {
    printf ("%s\n","malloc error in Particles_init()");
    for (i=0;i<4;i++)
      for (j=0;j<s_num;j++)
        if(tmp[i][j] != NULL)
          free(tmp[i][j]);
  }
  return ret;
}

int particles_print(Particles* P)
{
  printf ("%s\n","Print out all particles");
  int i,j;
  for (i=0;i<P->species_num;i++)
  {
    printf ("%s %d\n","species",i);
    printf ("%s\n","----------------------------------------------------");
    if (P->dim == 3)
      for (j=0;j<P->particle_num;j++)
        printf ("%5d: p:%10e %10e %10e v:%10e %10e %10e \n",j,P->pos[i][3*j],P->pos[i][3*j+1],P->pos[i][3*j+2],P->vel[i][3*j],P->vel[i][3*j+1],P->vel[i][3*j+2]);
    if (P->dim == 2)
      for (j=0;j<P->particle_num;j++)
        printf ("%5d: p:%10e %10e v:%10e %10e \n",j,P->pos[i][2*j],P->pos[i][2*j+1],P->vel[i][2*j],P->vel[i][2*j+1]);    
  }
  
  return 0;
}