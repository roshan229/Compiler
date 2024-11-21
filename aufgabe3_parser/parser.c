#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parser.h"
#include "lex.h"

typedef unsigned long ul;


tBog gProgramm[]= 
{
/* 0*/ {BgGr,{(ul)gBlock}, NULL, 1, 0}, //1 zu alternative
/* 1*/ {BgSy,{(ul)'.'},    NULL, 2, 0},
/* 2*/ {BgEn,{(ul)0 },     NULL, 0, 0} 
};


tBog gBlock []=
{
/* 0*/ {BgSy,{(ul)zCST},    NULL, 1, 6},
/* 1*/ {BgMo,{(ul)mcIdent}, NULL, 2, 0},
/* 2*/ {BgSy,{(ul)'=' },    NULL, 3, 0},
/* 3*/ {BgMo,{(ul)mcNum},   NULL, 4, 0},
/* 4*/ {BgSy,{(ul)',' },    NULL, 2, 6},

/* 6*/ {BgSy,{(ul)zVAR},    NULL, 7, 9}, //muss Mo sein ?
/* 7*/ {BgMo,{(ul)mcIdent}, NULL, 8, 0},
/* 8*/ {BgSy,{(ul)','},     NULL, 7, 9},

/* 9*/ {BgSy,{(ul)zPRC},    NULL,10,14},  //Symbol ?
/* 10*/{BgMo,{(ul)mcIdent}, NULL,11, 0},
/* 11*/{BgSy,{(ul)';'},     NULL,12, 0},
/* 12*/{BgGr,{(ul)gBlock},  NULL,13, 0},
/* 13*/{BgSy,{(ul)';'},     NULL, 9, 0},
/* 14*/{BgGr,{(ul)zState},  NULL, 0, 0}


};

tBog gExpr []=
{
/* 0*/ {BgSy,{(ul)'-'},     NULL, 1, 1},
/* 1*/ {BgGr,{(ul)gTerm},   NULL, 2, 0},
/* 2*/ {BgSy,{(ul)'+' },    NULL, 1, 3},
/* 3*/ {BgSy,{(ul)'-' },    NULL, 1, 4},
/* 4*/ {BgEn,{(ul)0 },      NULL, 0, 0}
};



tBog gTerm[]= 
{
/* 0*/ {BgGr,{(ul)gFact},   NULL, 1, 0},
/* 1*/ {BgSy,{(ul)'*'},     NULL, 0, 2},
/* 2*/ {BgSy,{(ul)'/' },    NULL, 0, 3},
/* 3*/ {BgEn,{(ul)0 },      NULL, 0, 0}
};




tBog gState[]= 
{
/* 0*/ {BgMo,{(ul)mcIdent},     NULL, 1, 3},
/* 1*/ {BgSy,{(ul)zERG},        NULL, 2, 0} , //muss Mo oder Symbol ?
/* 2*/ {BgGr,{(ul)gExpr },      NULL,20, 0},

/* 3*/ {BgSy,{(ul)zIF},         NULL, 4, 7},
/* 4*/ {BgGr,{(ul)gCond},       NULL, 5, 0},  
/* 5*/ {BgSy,{(ul)zTHN },       NULL, 6, 0},
/* 6*/ {BgGr,{(ul)gState },     NULL,20, 0}    ,
 
/* 7*/ {BgSy,{(ul)zWHL},        NULL, 8,11},
/* 8*/ {BgGr,{(ul)gCond},       NULL, 9, 0},  
/* 9*/ {BgSy,{(ul)zDO },        NULL,10, 0},
/*10*/ {BgGr,{(ul)gState },     NULL,20, 0},
            //Begin
/*11*/ {BgSy,{(ul)zBGN},        NULL,12,15},
/*12*/ {BgGr,{(ul)gState },     NULL,13,14},
/*13*/ {BgSy,{(ul)zEND},        NULL,20, 0},  
/*14*/ {BgSy,{(ul)';' },        NULL,12, 0},


/*15*/ {BgSy,{(ul)zCLL },       NULL,16,17},
/*16*/ {BgMo,{(ul)mcIdent },    NULL,20, 0},

/*17*/ {BgSy,{(ul)'?' },        NULL,16,18},
/*8*/ {BgSy,{(ul)'!' },         NULL,19,20},
/*19*/ {BgGr,{(ul)gExpr },      NULL,20, 0},


/*20*/ {BgEn,{(ul)0 },          NULL, 0, 0}

};






tBog gFact[]=
{
/* 0*/ {BgMo,{(ul)mcIdent}, NULL, 5, 1},
/* 1*/ {BgMo,{(ul)mcNum }, NULL, 5, 2},
/* 2*/ {BgSy,{(ul)'(' },    NULL, 3, 0},
/* 3*/ {BgGr,{(ul)gExpr },  NULL, 4, 0},
/* 4*/ {BgSy,{(ul)')' },    NULL, 5, 0},
/* 5*/ {BgEn,{(ul)0 },      NULL, 0, 0} 
};



tBog gCond [] =
{
/* 0*/ {BgSy,{(ul)zODD},   NULL, 1, 3},
/* 1*/ {BgGr,{(ul)gExpr }, NULL, 2, 0},
/* 2*/ {BgEn,{(ul)0 },     NULL, 0, 0}, //End
/* 3*/ {BgGr,{(ul)gExpr },  NULL, 4, 0},
/* 4*/ {BgSy,{(ul)'=' },    NULL, 5, 6},
/* 5*/ {BgGr,{(ul)gExpr },  NULL, 2, 0},
/* 6*/ {BgSy,{(ul)'#' },    NULL, 5, 7},
/* 7*/ {BgSy,{(ul)'<' },    NULL, 5, 8},
/* 8*/ {BgSy,{(ul)'>' },    NULL, 5, 9},
/* 9*/ {BgSy,{(ul)zLE },    NULL, 5, 10},
/*10*/ {BgSy,{(ul)zGE },    NULL, 5, 0}  //Frage hier

};