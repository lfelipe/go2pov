#include <string.h>
#include <stdlib.h>
#include "povwriter.h"

PovWriter::PovWriter()
{
  m_name=strdup("povwriter");
  m_filename=strdup("sample");
  m_extension=strdup("pov");
  m_texturefile=strdup("gotexture.inc");
  m_goboardfile=strdup("goboard.inc");

  m_thickness  =0.004;
  m_boardheight=0.1;
}

PovWriter::~PovWriter()
{
  free(m_name);
  free(m_filename);
  free(m_extension);
  free(m_goboardfile);
  free(m_texturefile);
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

int PovWriter::writeTexture()
{
  FILE *fp;
  fp=fopen(m_texturefile, "rb");
  if (fp!=NULL)
    {
      fclose(fp);
      return 0;
    }
  fp=fopen(m_texturefile, "wt");
  if (fp==NULL)
    {
      fprintf(stderr, "Cant open the texture-file for writing.\n");
      return 0;
    }
  fprintf(fp, "// Texture-file\n// Definitions for Go2POV-files\n");
  fprintf(fp, "// created by Go2POV (version %s)\n", GO2POV_MAIN_VERSION);
  fprintf(fp, "// If this file exists it will not be overwritten by Go2POV\n");
  fprintf(fp, "\n");
  fprintf(fp, "#declare wood_pigment = pigment{wood color_map{[0.00 color rgb <1.0, 0.8, 0.5>] [0.99 color rgb <0.9, 0.8, 0.5>]} turbulence 0.3 scale 0.1\n}\n");
  fprintf(fp, "#declare wood_finish = finish {phong 0.2}\n\n");
  fprintf(fp, "#declare grid_pigment = pigment {color rgb<0,0,0>}\n");
  fprintf(fp, "#declare grid_finish  = finish{phong 0}\n\n");
  fprintf(fp, "#declare bs_pigment = pigment{color rgb<0,0,0>}\n");
  fprintf(fp, "#declare bs_finish = finish{phong 0.2 phong_size 0.8}\n\n");
  fprintf(fp, "#declare ws_pigment = pigment{color rgb<1,1,1>}\n");
  fprintf(fp, "#declare ws_finish = finish{phong 1 phong_size 150}\n\n");
  fclose(fp);
  return 1;
}

int PovWriter::writeScene()
{
  FILE   *fp;
  char   *n;

  n=(char *)malloc(strlen(m_filename) + strlen(m_extension) + 2);
  sprintf(n,"%s.%s", m_filename,m_extension);
  fp=fopen(n, "wt");
  if (fp==NULL)
    {
      fprintf(stderr, "Can not open scene-pov-file for writing (%s)\n", n);
      free(n);
      return 0;
    }
  free(n);

  fprintf(fp, "// Sample scene from Go2POV (version %s)\n",\
	  GO2POV_MAIN_VERSION);
  fprintf(fp, "#include \"%s\"\n\n", m_goboardfile);
  fprintf(fp, "object {goboard}\n");
  fprintf(fp, "\n");
  fprintf(fp, "camera { location <0.5,3,2> look_at <0,0,0>}\n");
  fprintf(fp, "light_source {<2,5,2> color rgb <1,1,1>}\n");
  fprintf(fp, "background { color rgb <0.2, 0.2, 0.3> }\n");
  fclose(fp);
  return 1;
}


int PovWriter::writeBoard(GoBoard *_board)
{
  FILE   *fp;
  double  b_border=0.02;
  double  width=2.0 - b_border*2 , s_step=width/((double)_board->getSize()+1), s_space=0.01, s_size=(s_step-s_space);
  double  s_off=- (width/2.0 - s_step), s_height=(s_size/2.0) * 0.6666 ;
  int     i,j;
  Stone   color;

  writeTexture();
  fp=fopen(m_goboardfile, "wt");
  if (fp==NULL)
    {
      fprintf(stderr,"failed to open : %s\n", m_goboardfile);
      return 0;
    }
  fprintf(fp, "// POV - scene, automatically generated with Go2Pov\n");
  fprintf(fp, "// version %s\n", GO2POV_MAIN_VERSION);
  fprintf(fp, "#include \"%s\"\n\n", m_texturefile);
  fprintf(fp, "#declare th = %f;\n#declare bh = %f;\n",\
	  m_thickness, m_boardheight);
  fprintf(fp, "#declare ssize = %f;\n#declare srad = %f;\n",\
	  s_size, s_size/2.0);
  fprintf(fp, "#declare sheight = %f;\n", s_height);
  fprintf(fp, "\n");
  fprintf(fp, "#declare stone = object { intersection {\n");
  fprintf(fp, "sphere{<0,0.8,0> 1.0}\nsphere{<0,-0.8,0> 1.0}\n}\nscale <0.8,0.8,0.8>}\n");
  fprintf(fp, "\n");

  fprintf(fp, "\n");
  fprintf(fp, "#declare bs = object { stone pigment {bs_pigment} scale <ssize, ssize, ssize> finish {bs_finish} }\n");
  fprintf(fp, "#declare ws = object { stone pigment {ws_pigment} scale <ssize, ssize, ssize> finish {ws_finish} }\n");
  fprintf(fp, "#declare hline = object { box{<-%f,0,-th/2> <+%f,bh,+th/2>} }\n", s_off, s_off);
  fprintf(fp, "#declare vline = object { box{<-th/2,0,-%f> <+th/2,bh,+%f>} }\n", s_off, s_off);

  fprintf(fp, "#declare hoshi = object { cylinder{<0,0,0><0,bh,0> th*3} }");
  fprintf(fp,"\n");

  fprintf(fp, "#declare hoshis = union {\n");
  if (_board->getSize() == 19)
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
	    fprintf(fp, "object {ws translate <%f,bh+sheight/2,%f>}\n",\
		    s_step*-i-s_off, s_step*j+s_off);
	  if (color==black)
	    fprintf(fp, "object {bs translate <%f,bh+sheight/2,%f>}\n",\
		    s_step*-i-s_off, s_step*j+s_off);
	}
    }
  fprintf(fp, "}\n\n");
  fprintf(fp, "\n");
  fprintf(fp, "#declare grid = object {union {\n");
  for (i=0; i<_board->getSize(); i++)
    {
      fprintf(fp, "object {vline translate <%f,0,0>}\n object {hline translate <0,0,%f>}\n", s_step*-i-s_off, s_step*i+s_off);
    }
  fprintf(fp, "object {hoshis}\n");
  fprintf(fp, "}\npigment {grid_pigment} finish {grid_finish}}\n");
  fprintf(fp, "\n");
  fprintf(fp, "#declare woodboard=object {\n difference {\n");
  fprintf(fp, "object{box{<-1,-bh,-1> <1,bh,1>}} object{grid scale<1,1.01,1>} }\n");
  fprintf(fp, "pigment{wood_pigment} finish{wood_finish}\n");
  fprintf(fp, "}\n");
  fprintf(fp, "\n");
  fprintf(fp, "#declare goboard = union { object{woodboard} object{grid} object{stones}}\n");

  writeScene();
  fclose(fp);
  return 1;
}
