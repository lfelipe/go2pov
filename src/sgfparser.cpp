#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sgfparser.h"


SGFParser::SGFParser()
{
  name=strdup("SGF-Parser");
}


SGFParser::~SGFParser()
{
  free(name);
}


int SGFParser::tryFile(char *_filename)
{
  if (strstr(_filename, ".sgf")!=NULL)
    return 1;
  if (strstr(_filename, ".SGF")!=NULL)
    return 1;
  return 0;
}


char SGFParser::getNextChar(char **_p1, char *_pe)
{
  char *p;

  if (*_p1==_pe) return 0;

  p=*_p1;
  while(*p<=32 && p!=_pe)
    p++;


  *_p1=p+1;
  if (p+1==_pe)
    return 0;
  if (p==_pe)
    {
      *_p1=p;
      return 0;
    }
  else return *p;
}



GoFile *SGFParser::parseFile(char *_filename)
{
  FILE     *fp;
  GoFile   *file=new GoFile();
  GameTree *tree=NULL;
  long int  length;
  char      *m1, *p1, *pe, done;

  // copy file to memory
  fp=fopen(_filename, "rt");
  if (fp==NULL)
    {
      fprintf(stderr, "Cant open the input-file '%s'.\n", _filename);
      return NULL;
    }
  fseek(fp,0,2);
  length=ftell(fp);
  fseek(fp,0,0);
  m1=(char *)malloc(length);
  fread(m1,1,length,fp);
  fclose(fp);

  // parse all available games from the file
  done=0;
  p1=m1;
  pe=p1+length;
  while(!done)
    {
      m_info=new GameInfo();
      tree=GameTree::New();
      tree=parseTree(&p1, pe);
      if (tree==NULL)
	{
	  delete m_info;
	  done=1;
	} else {
	  file->addGame(tree, m_info);
	  fprintf(stderr,"GameTree added\n");
	}
    }  
  return file;
}


GameTree *SGFParser::parseTree(char **_p1, char *_pe)
{
  GameTree *tree=NULL;
  GameTree *t;
  GameNode *n;
  char     a, *p1, *p2, done, splitted=0;

  done=0;
  p1=*_p1;

  // find start of the tree
  a=getNextChar(&p1, _pe);
  while(a!='(')
    {
      a=getNextChar(&p1, _pe);
      if (a==0) return NULL;
    }

  // parse tree
  fprintf(stderr, "Tree opened '%c'\n", a);
  tree=GameTree::New();
  done=0;
  while(!done)
    {
      p2=p1;
      a=getNextChar(&p1, _pe);
      //if (a==0) {done=1; continue;}
      switch(a)
	{
	case ';':
	  if (splitted)
	    {
	      fprintf(stderr, "Found a node after a tree-split !!\n");
	      return NULL;
	    }
	  n=parseNode(&p1, _pe);
	  if (p1==_pe) done=1;
	  else
	    {
	      tree->addNode(n);
	    }
	  break;
	case '(':
	  p1=p2;
	  splitted=1;
	  t=parseTree(&p1,_pe);
	  if (t==NULL || p1==_pe) done=1;
	  else
	    {
	      tree->addVariation(t);
	    }
	  break;
	case ')':
	  fprintf(stderr, "Tree closed\n");
	  break;
	case '\0':
	  done=1;
	  break;
	default:
	  fprintf(stderr,"Found an error ... (%i, %x, %c)", a,a,a);  delete tree;  return NULL;
	}
    }
  *_p1=p1;
  return tree;
}

GameNode *SGFParser::parseNode(char **_p1, char *_pe)
{
  GameNode *n;//=new GameNode();
  char a,*p1, *p2, done, pi[3], nof_pi=0;

  fprintf(stderr, "  Parsing Node\n");
  p1=*_p1;
  done=0;
  pi[0]=0;
  pi[1]=0;
  pi[2]=0;
  while(!done)
    {
      p2=p1;
      a=getNextChar(&p1, _pe);
      switch(a)
	{
	case ')':
	case '(':
	case ';':
	  p1=p2;
	  fprintf(stderr, "    breaking -> found '%c'\n", a);
	  done=1;
	  break;
	case '[':
	  p1=p2;
	  parseProperty(&p1, _pe, pi, n);
	  nof_pi=0;
	  pi[0]=0;
	  pi[1]=0;
	  pi[2]=0;
	  break;
	default:
	  if (a>='A' && a<='Z')
	    pi[nof_pi++]=a;
	  //fprintf(stderr, "%c", a);
	}
    }
  *_p1=p1;
  return NULL;
}


int SGFParser::parseProperty(char **_p1, char *_pe, char *_id, GameNode *_n)
{
  char *p1, *p2, *p3, opened, untouched, done;

  p1=*_p1;
  p2=p1;
  fprintf(stderr, "      parsing PropID: %s -> ", _id);

  untouched=1;
  opened=0;
  done=0;
  while(p1!=_pe && !done)
    {
      if (opened)
	{
	  if (*p1==']' && *(p1-1)!='\\')
	    opened--;
	} else if (!opened && *p1=='[')
	  {
	    opened++;
	    untouched=0;
	  } else if (!opened && *p1!=32) done=1;
      if (!done) p1++;
    }

  p3=(char *)malloc(p1-p2+1);
  memcpy(p3,p2, p1-p2);
  p3[p1-p2]=0;
  fprintf(stderr, "%s\n", p3);
  free(p3);

  *_p1=p1;
  return 1;
}
