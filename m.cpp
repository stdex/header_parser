#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE	*infile, *outfile;
char	memo[1024L*1024L];
char	*cptr, *ceptr, *csptr;

void deletetail(char *inptr)
{
 char           *tailptr;

 for (tailptr=inptr+strlen(inptr)-1;(*tailptr)&&((unsigned char)(*tailptr)<=' ');tailptr--) ;
 tailptr++;
 *tailptr=0;
}

int findliteral()
{
 for (;*cptr;cptr++)
  if ((*cptr=='_')||(((unsigned char)(*cptr)>='A')&&((unsigned char)(*cptr)<='z'))) return 1;
 return 0;
}

int findparenthesis()
{
 for (;*cptr;cptr++)
  if (*cptr==')') return 1;
 return 0;
}

int skipliteral()
{
 int		n;

 for (n=0;*cptr;cptr++,n++)
  if ((*cptr!='_')&&(((unsigned char)(*cptr)<'A')||((unsigned char)(*cptr)>'z'))&&
   (((unsigned char)(*cptr)<'0')||((unsigned char)(*cptr)>'9'))) return n;
 return n;
}

int skipspace()
{
 int		n;

 for (n=0;*cptr;cptr++,n++)
  if ((unsigned char)(*cptr)>' ') return n;
 return n;
}

int	findfunction()
{
 char fskip;

 for (fskip=0;*cptr;) {
  if (!findliteral()) return 0;
  if (!fskip) csptr=cptr;
  fskip=0;
  if (!skipliteral()) continue;
  if (!strncmp(csptr,"unsigned",cptr-csptr)) {
   fskip=1;
   continue;
  }
  if (!skipspace()) continue;
  if ((*cptr!='_')&&(((unsigned char)(*cptr)<'A')||((unsigned char)(*cptr)>'z'))) continue;
  if (!skipliteral()) continue;
  skipspace();
  if (*cptr!='(') continue;
  if (!findparenthesis()) return 0;
  cptr++;
  skipspace();
  if (*cptr==';') {
   ceptr=cptr;
   return 1;
  }  
 }
 return 0;
}

int main(int argc, char *argv[])
{
 char	fname[512], fullname[512], workstring[1024];
 int	l, ch;

 memset(memo,0,sizeof(memo));
 printf("Input name of h-file without extension ");
 scanf("%s",fname);
 
 /*
 char c;
 c = getchar();
 while(c != '\n')
 c = getchar();
 */
 
 while((ch=getchar())!='\n');
 
 strcpy(fullname,fname);
 strcat(fullname,".h");
 
 if (!(infile=fopen(fullname,"rt"))) {
  printf("Error. File %s not found.\n",fullname);
  return 0;
 }
 
 cptr=&memo[0];
 
 // читаем и обрабатываем файл построчно
 while (!feof(infile)) {
  workstring[0]=0;
  fgets(workstring,sizeof(workstring),infile);
  
  deletetail(workstring);
  
  while ((workstring[0])&&((unsigned char)workstring[0]<=' ')) { strcpy(&workstring[0],&workstring[1]);  printf("%s \n\n",workstring[0]); }
  
  if ((!workstring[0])||(workstring[0]=='#')||((workstring[0]=='/')&&(workstring[1]=='/'))) continue;
  
  memcpy(cptr,workstring,strlen(workstring));
  
  cptr+=strlen(workstring);
  
 }
 
 *cptr=0;
 
 fclose(infile);
 strcpy(fullname,fname);
 strcat(fullname,".map");
 
 if (!(outfile=fopen(fullname,"wt"))) {
  printf("Error. Unable open file for output %s.\n",fullname);
  return 0;
 }
 
 cptr=&memo[0];
 
 while (findfunction()) {
  l=ceptr-csptr;
  memcpy(workstring,csptr,l);
  workstring[l]=0;
  fprintf(outfile,"%s;\n",workstring);
  printf("%s;\n",workstring);
 }
 
 fclose(outfile);
 
 getch();
 return 0;
}
