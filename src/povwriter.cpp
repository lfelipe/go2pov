#include <string.h>
#include <stdlib.h>
#include "povwriter.h"

PovWriter::PovWriter()
{
  m_name=strdup("povwriter");
  m_filename=strdup("goboard");
  m_extension=strdup("pov");

  m_thickness  =0.003;
  m_boardheight=0.1;
}


void PovWriter::setFilename(char *_filename)
{
  free(m_filename);
  m_filename=strdup(_filename);
}

void PovWriter::setExtension(char *_extension)
{
  free(m_extension);
  m_extension=strdup(_extension);
}


int PovWriter::writeBoard(GoBoard *_board)
{
  FILE   *fp;
  char   *n;
  double  b_border=0.1;
  double  width=2.0 - b_border*2 , s_step=width/((double)_board->getSize()-1), s_space=0.01, s_size=(s_step-s_space);
  double  s_off=- (width/2.0 - s_space), s_height=(s_size/2.0) * 0.6666 ;
  int     i,j;
  Stone   color;

  n=(char *)malloc(strlen(m_filename) + strlen(m_extension) + 2);
  sprintf(n,"%s.%s", m_filename,m_extension);

  fp=fopen(n, "wt");
  if (fp==NULL)
    {
      fprintf(stderr,"failed to open : %s\n", n);
      return 0;
    }
  fprintf(fp, "// POV - scene, automatically generated with Go2Pov version %s\n", GO2POV_MAIN_VERSION);
  fprintf(fp, "\n");
  fprintf(fp, "#declare th = %f;\n#declare bh = %f;\n", m_thickness, m_boardheight);
  fprintf(fp, "#declare ssize = %f;\n#declare srad = %f;\n", s_size, s_size/2.0);
  fprintf(fp, "#declare sheight = %f;\n", s_height);
  fprintf(fp, "\n");
  fprintf(fp, "#declare stone = object { intersection {\n");
  fprintf(fp, "sphere{<0,0.8,0> 1.0}\nsphere{<0,-0.8,0> 1.0}\n}\nscale <0.8,0.8,0.8>}\n");
  fprintf(fp, "\n");
  //fprintf(fp, "object {stone translate 1*y}\n");

  fprintf(fp, "#declare bs = object { stone pigment {color rgb<0,0,0>} scale <ssize, ssize, ssize> finish {phong 0.2 phong_size 0.8} }\n");
  fprintf(fp, "#declare ws = object { stone pigment {color rgb<1,1,1>} scale <ssize, ssize, ssize> finish {phong 1 phong_size 150} }\n");
  
  fprintf(fp, "#declare hline = object { box{<-%f,0,-th> <+%f,bh,+th>} }\n",
	  width/2, width/2);
  fprintf(fp, "#declare vline = object { box{<-th,0,-%f> <+th,bh,+%f>} }\n",
	  width/2, width/2);
  fprintf(fp, "#declare hoshi = object { cylinder{<0,0,0><0,bh,0> th*5} }");
  fprintf(fp,"\n");

  fprintf(fp, "#declare hoshis = union {\n");
  if (_board->getSize() >= 19)
    {
      fprintf(fp, " object {hoshi translate<%f,0,%f>}\n", s_step*- 3-s_off, s_step* 3+s_off);
      fprintf(fp, " object {hoshi translate<%f,0,%f>}\n", s_step*- 9-s_off, s_step* 3+s_off);
      fprintf(fp, " object {hoshi translate<%f,0,%f>}\n", s_step*-15-s_off, s_step* 3+s_off);

      fprintf(fp, " object {hoshi translate<%f,0,%f>}\n", s_step*- 3-s_off, s_step* 9+s_off);
      fprintf(fp, " object {hoshi translate<%f,0,%f>}\n", s_step*- 9-s_off, s_step* 9+s_off);
      fprintf(fp, " object {hoshi translate<%f,0,%f>}\n", s_step*-15-s_off, s_step* 9+s_off);

      fprintf(fp, " object {hoshi translate<%f,0,%f>}\n", s_step*- 3-s_off, s_step*15+s_off);
      fprintf(fp, " object {hoshi translate<%f,0,%f>}\n", s_step*- 9-s_off, s_step*15+s_off);
      fprintf(fp, " object {hoshi translate<%f,0,%f>}\n", s_step*-15-s_off, s_step*15+s_off);
    }
  fprintf(fp, "}\n");
  fprintf(fp, "\n");

  fprintf(fp, "#declare stones = union {\n");
  for (i=0; i<_board->getSize(); i++)
    {
      for (j=0; j<_board->getSize(); j++)
	{
	  color=_board->get(i,j);
	  if (color==empty) continue;
	  if (color==white)
	    fprintf(fp, "object {ws translate <%f,bh+sheight/2,%f>}\n", s_step*-i-s_off, s_step*j+s_off);
	  if (color==black)
	    fprintf(fp, "object {bs translate <%f,bh+sheight/2,%f>}\n", s_step*-i-s_off, s_step*j+s_off);
	}
    }
  fprintf(fp, "}\n\n");
  fprintf(fp, "\n");
  fprintf(fp, "#declare grid = object {union {\n");
  for (i=0; i<_board->getSize(); i++)
    {
      fprintf(fp, "object {vline translate <%f,0,0>}\n object {hline translate <0,0,%f>}\n",
	      s_step*-i-s_off, s_step*i+s_off);
    }
  fprintf(fp, "object {hoshis}\n");
  fprintf(fp, "}\npigment {color rgb <0.5,0.5,0.5>}}\n");
  fprintf(fp, "\n");
  fprintf(fp, "#declare woodboard=object {\n difference {\n");
  fprintf(fp, "object{box{<-1,-bh,-1> <1,bh,1>}} object{grid scale<1,1.01,1>} }\n");
  fprintf(fp, "pigment{wood color_map{[0.00 color rgb <1.0, 0.8, 0.5>] [0.99 color rgb <0.9, 0.8, 0.5>]}\n");
  fprintf(fp, "turbulence 0.3 scale 0.1}\n}\n");
  fprintf(fp, "\n");
  fprintf(fp, "#declare board = union { object{woodboard} object{grid} }\n");


  fprintf(fp, "object { stones}\n");
  fprintf(fp, "object { board}\n");
  fprintf(fp, "\n");
  //fprintf(fp, "camera { location <1,2,1> look_at <0,-bh,0>}\n");
  fprintf(fp, "camera { location <0,2,.5> look_at <0,0,0>}\n");
  fprintf(fp, "light_source {<2,5,2> color rgb <1,1,1>}\n");
  fprintf(fp, "background { color rgb <0.2, 0.2, 0.3> }\n");
  fclose(fp);
  return 1;
}
