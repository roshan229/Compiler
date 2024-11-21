#include "stdio.h"
#include "stdlib.h"
#include "ctype.h"

typedef struct morph
{
    int mc;
    union
    {
        double dval;
        char cval;
    };
} MORPHEM;

enum mcodes
{
    mempty,
    mop,
    mdbl
};
static MORPHEM m;

void lex(char *pX)
{
    static char *px;
    /* Initialisierung*/
    if (pX != NULL)
    {
        m.mc = mempty;
        px = pX;
    }
    /* lexiaklische Analyse */
    if (*px == '\0')
    {
        m.mc = mempty;
    }
    else
    {
        for (; *px == ' ' || *px == '\t'; px++)
            ;
        if (isdigit(*px) || *px == '.')
        // numeral
        {
            m.dval = strtod(px, &px); // String to double
            m.mc = mdbl;
        }
        else
            // Symbol
            switch (*px)
            {
            case '+':
            case '*':
            case '-':
            case '/':
            case '(':
            case ')':
                m.cval = *px++;
                m.mc = mop;
                break;
            // end or wrong char
            default:
                m.mc = mempty;
            }
    }
}

        
double expr(void);
double Rexpr(double tmp);
double term(void);
double Rterm(double tmp);
double fac();


double expr(void)
{
    double tmp;
    tmp=term();

    return Rexpr(tmp);
}

double Rexpr(double tmp)
{
    if (m.cval=='-' && m.mc==mop )
        {lex(NULL); tmp -=term();tmp=Rexpr(tmp);} else
        if (m.cval=='+' && m.mc==mop )
        {lex(NULL); tmp+=term();tmp=Rexpr(tmp);}
    return tmp;
}


double term(void)
{
    double tmp;
    tmp = fac();
    return Rterm(tmp);
}

double Rterm(double tmp)
{
    if (m.cval=='*' && m.mc==mop )
        {lex(NULL); tmp *=fac();tmp=Rterm(tmp);} else
        if (m.cval=='/' && m.mc==mop )
        {lex(NULL); tmp/=fac();tmp=Rterm(tmp);}
    return tmp;
}


double fac()
{
    double tmp;
    if (m.mc == mop)
    {
        if (m.cval == '(')
        {
            lex(NULL);
            tmp = expr();
            if (m.mc != mop || m.cval != ')')
                exit(1);
            lex(NULL);
        }
        else
            exit(1);
    }
    else if (m.mc == mdbl)
    {
        tmp = m.dval;
        lex(NULL);
    }
    else
        exit(1);
    return tmp;
}

int main(int argc, char *argv[])
{
    char *pBuf = argv[1];
    printf("%s\n", pBuf);
    lex(pBuf);
    printf("%-10.4f\n", expr());
    return 0;
}

// px zeigt immer auf nächste