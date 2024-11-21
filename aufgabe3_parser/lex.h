// Arnold Beck
typedef enum T_Fx {ifl,ifb,ifgl,ifsl,ifslb}tFx;

/* Morphemcodes */
typedef enum T_MC {mcEmpty, mcSymb, mcNum, mcIdent, mcStrng}tMC;

typedef enum T_ZS
  {
  zNIL,
  zERG=128,zLE,zGE,
  zBGN,zCLL,zCST,zDO,zEND,zIF,zODD,zPRC,zTHN,zVAR,zWHL
  }tZS;


typedef struct
{
  tMC  MC;		/* Morphemcode */
  int  PosLine;/* Zeile       */
  int  PosCol;	/* Spalte      */
  union VAL
  {
    long Num;
    char*pStr;
    int  Symb;
  }Val;
  int  MLen;   /* Morpheml„nge*/
}tMorph;


typedef struct
{   
  int zustand;
  tFx aktion;

}entry;

int initLex(char* fname); //Initializes the lexical analyzer with a given filename

tMorph* Lex(void);  //Returns the next morpheme (of type tMorph) in the source code.

