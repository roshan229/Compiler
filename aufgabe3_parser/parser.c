#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parser.h"


typedef unsigned long ul;


tBog gProgramm[]= 
{
/* 0*/ {BgGr,{(ul)gBlock}, NULL, 1, 0}, //1 zu alternative
/* 1*/ {BgSy,{(ul)'.'},    NULL, 2, 0},
/* 2*/ {BgEn,{(ul)0 },     NULL, 0, 0} 
};


tBog gBlock=
{
/* 0*/ {BgSy,{(ul)zCST},    NULL, 1, 6},
/* 1*/ {BgMo,{(ul)mcIdent}, NULL, 2, 0},
/* 2*/ {BgSy,{(ul)'=' },    NULL, 3, 0},
/* 3*/ {BgMo,{(ul)mcNum},   NULL, 4, 0},
/* 4*/ {BgSy,{(ul)',' },    NULL, 2, 6},

/* 6*/ {BgsY,{(ul)zVAR},    NULL, 7, 9},
/* 7*/ {BgsY,{(ul)mcIdent}, NULL, 8, 0},
/* 8*/ {BgsY,{(ul)zVAR},    NULL, 7, 9},
/* 9*/ {BgsY,{(ul)zVAR},    NULL, 7, 9},
/* 10*/{BgsY,{(ul)zVAR},    NULL, 7, 9},
/* 11*/{BgsY,{(ul)zVAR},    NULL, 7, 9},
/* 12*/{BgsY,{(ul)zVAR},    NULL, 7, 9},
/* 13*/{BgsY,{(ul)zVAR},    NULL, 7, 9},
/* 14*/{BgsY,{(ul)zVAR},    NULL, 7, 9},
/* 15*/{BgsY,{(ul)zVAR},    NULL, 7, 9},
/* 16*/{BgsY,{(ul)zVAR},    NULL, 7, 9},
/* 17*/{BgsY,{(ul)zVAR},    NULL, 7, 9},
/* 6*/ {BgsY,{(ul)zVAR},    NULL, 7, 9} 


};

tBog Expr=
{
/* 0*/ {BgMo,{(ul)mcIdent}, NULL, 5, 1},/*(0)---ident--->(E)*/
/* 1*/ {BgMo,{(ul)mcNum },  NULL, 5, 2},/* +---number--->(E)*/
/* 2*/ {BgSy,{(ul)'(' },    NULL, 3, 0},/*(+)----'('---->(3)*/
/* 3*/ {BgGr,{(ul)gExpr },  NULL, 4, 0},/*(1)---express->(4)*/
/* 4*/ {BgSy,{(ul)')' },    NULL, 5, 0},/*(0)----')'---->(E)*/
/* 5*/ {BgEn,{(ul)0 },      NULL, 0, 0} /*(E)--------(ENDE) */
};



tBog gFact[]=
{
/* 0*/ {BgMo,{(ul)mcIdent}, NULL, 5, 1},/*(0)---ident--->(E)*/
/* 1*/ {BgMo,{(ul)mcNum }, NULL, 5, 2},/* +---number--->(E)*/
/* 2*/ {BgSy,{(ul)'(' },    NULL, 3, 0},/*(+)----'('---->(3)*/
/* 3*/ {BgGr,{(ul)gExpr },  NULL, 4, 0},/*(1)---express->(4)*/
/* 4*/ {BgSy,{(ul)')' },    NULL, 5, 0},/*(0)----')'---->(E)*/
/* 5*/ {BgEn,{(ul)0 },      NULL, 0, 0} /*(E)--------(ENDE) */
};