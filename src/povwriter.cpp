#include <string.h>
#include <stdlib.h>
#include "povwriter.h"

PovWriter::PovWriter()
{
  m_name=strdup("povwriter");
  m_extension=strdup("pov");

  m_thickness  =0.003;
  m_boardheight=0.1;
}


void PovWriter::setExtension(char *_extension)
{
  free(m_extension);
  m_extension=strdup(_extension);
}


int PovWriter::writeBoard(GoBoard *_board, char *_filename)
{
  FILE *fp;
  char *n;

  n=(char *)malloc(strlen(_filename) + strlen(m_extension) + 2);
  sprintf(n,"%s.%s", _filename,m_extension);

  fp=fopen(n, "wt");
  if (fp==NULL)
    {
      fprintf(stderr,"failed to open : %s\n", n);
      return 0;
    }
  fprintf(fp, "// POV - scene, automatically generated with Go2Pov version %s\n", GO2POV_MAIN_VERSION);
  fprintf(fp, "\n");
  fprintf(fp, "#declare th = %f\n#declare bh = %f\n", m_thickness, m_boardheight);
  fprintf(fp, "\n");
  fprintf(fp, "#declare stone = object { intersection {\nsphere{<0,size*0.025,0> size*0.05}\nsphere{<0,size*-0.025,0> size*0.05}\n} translate <0,bh/2,0>}\n");
  fprintf(fp, "\n");
  fprintf(fp, "#declare bs = object { stone pigment {color rgb<0,0,0>} finish {phong 0.2 phong_size 0.8} }\n");
  fprintf(fp, "#declare ws = object { stone pigment {color rgb<1,1,1>} finish {phong 1 phong_size 150} }\n");
  fprintf(fp, "#declare hline = object { box[<-0.1,0,0.1-th> <-0.1,bh,0.1+th>} pigment {color rgb<0,0,0>} }\n");
  fprintf(fp, "#declare vline = object { box[<-0.1-th,0,0.1> <-0.1+th,bh,0.1>} pigment {color rgb<0,0,0>} }\n");
  fclose(fp);
  return 1;
}
