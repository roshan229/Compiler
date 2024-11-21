// Arnold Beck

/****************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lex.h"

static FILE  *pIF;			/* Quellfile 				*/
static tMorph MorphInit;		/* Morphem   				*/
tMorph Morph;
static signed char X;			/* Aktuelles Eingabezeichen 		*/
static int    Z;			/* Aktueller Zustand des Automaten 	*/
static char   vBuf[128+1],*pBuf;	/* Ausgabepuffer */
static int    Ende;			/* Flag 				*/
static int    line, col;

/*---- Initialisierung der lexiaklischen Analyse ----*/
int initLex(char* fname)
{
  pIF=fopen(fname,"r+t");  //Opens the file specified by fname in read and write, text mode.
  if (pIF) X=fgetc(pIF);  //reads the first character from the file into X using fgetc
  Morph.MC=mcEmpty;
  line = col =0;
  return (int)pIF;
}




/* Zeichenklassenvektor */
static char vZKl[128]=/*     0 1 2 3 4 5 6 7 8 9 A B C D E F */
                      /*--------------------...--------------*/
                      /* 0*/{7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,/* 0*/
                      /*10*/ 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,/*10*/
                      /*20*/ 7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,/*20*/
                      /*30*/ 1,1,1,1,1,1,1,1,1,1,3,0,5,4,6,0,/*30*/
                      /*40*/ 0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,/*40*/
                      /*50*/ 2,2,2,2,2,2,2,2,2,2,2,0,0,0,0,0,/*50*/
                      /*60*/ 0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,/*60*/
                      /*70*/ 2,2,2,2,2,2,2,2,2,2,2,0,0,0,0,7}/*70*/;


/* Automatentabelle */
static entry vSMatrix[][8]=
{
/*    SoZei    Ziffer      Buchstaben         :           =           <           >         sonst */  
  {{9, ifslb},{1, ifsl},   {2, ifgl},   {3, ifsl},  {9, ifslb},   {4, ifslb}, {5, ifslb}, {0, ifl}},      /*Z0*/ //hier war beenden 
  {{1, ifb},  {1, ifsl},   {1, ifb},    {1, ifb},   {1, ifb},     {1, ifb},   {1, ifb},   {1, ifb}},      /*Z1*/
  {{2, ifb},  {2, ifsl},   {2, ifgl},   {2, ifb},   {2, ifb},     {2, ifb},   {2, ifb},   {2, ifb}},      /*Z2*/
  {{3, ifb},  {3, ifb},    {3, ifb},    {3, ifb},   {6, ifb},     {3, ifb},   {3, ifb},   {3, ifb}},      /*Z3*/
  {{4, ifb},  {4, ifb},    {4, ifb},    {4, ifslb}, {7, ifsl},    {4, ifb},   {4, ifb},   {4, ifb}},      /*Z4*/
  {{5, ifb},  {5, ifb},    {5, ifb},    {5, ifb},   {8, ifsl},    {5, ifb},   {5, ifb},   {5, ifb}},      /*Z5*/
  {{6, ifb},  {6, ifb},    {6, ifb},    {6, ifb},   {6, ifb},     {6, ifb},   {6, ifb},   {6, ifb}},      /*Z6*/
  {{7, ifb},  {7, ifb},    {7, ifb},    {7, ifb},   {7, ifb},     {7, ifb},   {7, ifb},   {7, ifb}}       /*Z7*/  ,  
};


//.. to be continue

/* Ausgabefunktionen des Automaten */
static void fl  (void);
static void fb  (void);
static void fgl (void);
static void fsl (void);
static void fslb(void);

typedef void (*FX)(void);

static FX vfx[]={fl,fb,fgl,fsl,fslb};

/*---- Lexikalische Analyse ----*/
tMorph* Lex(void)
{
  int Zn;
  Morph=MorphInit;
  Morph.PosLine = line;
  Morph.PosCol= col;
  pBuf=vBuf;
  Ende=0;
  Z=0;
  do
  {
    printf("in lex: %c ",X);
    printf("akt Zustand: %d\n", Z);
    if(X==EOF && Z==0) {
      Morph.MC=mcSymb;
      Morph.Val.Symb=-1;
      return &Morph;
    }
  
    /* Berechnung des Folgezustands */
    Zn=   vSMatrix[Z][vZKl[X&0x7f]].zustand;
    /* Ausfuehrung der Aktion (Ausgabefunktion */
    vfx[((vSMatrix[Z][vZKl[X&0x7f]])).aktion]();
    /* Automat schaltet */
    Z=Zn;
  
  }while (Ende==0);
  return &Morph;
}




//die Aktion Funktion
static void fl (void)
{ 
  X=fgetc(pIF);
  if (X=='\n') line++,col=0;
  else col++;
}


      /*---- schreiben als Grossbuchstabe, lesen ----*/
static void fgl (void)
{ 
  *pBuf=(char)toupper(X);// oder *Buf=(char)X&0xdf;
  *(++pBuf)=0;
  fl();
}
      /*---- schreiben, lesen ----*/
static void fsl (void)
{ 
  *pBuf=(char)X;
  *(++pBuf)=0;
  fl();
}



        /*---- schreiben, lesen, beenden ----*/
static void fslb(void)
{ 
  fsl();fb();
}


static void fb ()
{
  int i,j;
  switch (Z)
  {
       /*Bezeichner*/
  case 2:
        int i=0;
        for (i;i< sizeof(keyWords)/sizeof(keyWords[0]);i++) {
          if (strcmp(vBuf,keyWords[i])==0) break;
        }

        

        Morph.Val.pStr=vBuf;
        Morph.MC =mcIdent;
        break;
  /* Symbol */
  case 3: // :
  case 4: // <
  case 5: // >
  case 0:Morph.Val.Symb=vBuf[0];
  Morph.MC =mcSymb;
  break;
  /* Zahl */
  case 1:Morph.Val.Num=atol(vBuf);
  Morph.MC =mcNum;
  break;
  /* Ergibtzeichen */
  case 6:Morph.Val.Symb=(long)zERG;
  Morph.MC =mcSymb;
  break;
  /* KleinerGleich */
  case 7:Morph.Val.Symb=(long)zLE;
  Morph.MC =mcSymb;
  break;
  /* GroesserGleich */
  case 8:Morph.Val.Symb=(long)zGE;
  Morph.MC =mcSymb;
  break;

}
  Ende=1; // entfällt bei Variante mit Zustand zEnd
}

