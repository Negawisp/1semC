#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

char* S = NULL;
int   P = 0;
#define NOW( to_compare_with ) (S[P] == to_compare_with)
#define MOVE() P++
#define DEG( base, degree ) exp (degree * log (base));
#define FIND( ch )           \
        SkipSpaces();        \
        assert (NOW (ch));  \
        MOVE ();

int SkipSpaces ()
{
    while (NOW (' '))
        MOVE();
    return 0;
}


double GetNumeric ()
{
    double val = 0;
    SkipSpaces();

    if (S[P] < '0' || '9' < S[P])
        assert (!"S[P] is not digit.");

    do
    {
        val = val * 10 + S[P] - '0';
        MOVE ();
    }
    while ('0' <= S[P] && S[P] <= '9');

    if (!NOW('.'))
        return val;
    MOVE ();

    if (S[P] < '0' || '9' < S[P])
        assert (!"S[P] after point is not digit.");

    int tokens_after_point = 1;

    do
    {
        val = val + (S[P] - '0') * DEG (0.1, tokens_after_point);
        MOVE ();
    }
    while ('0' <= S[P] && S[P] <= '9');

    return val;
}

double GetMnogochlen();

double GetCos ()
{
    MOVE ();
    FIND ('o');
    FIND ('s');
    FIND ('(');

    double val = GetMnogochlen ();
    val = cos (val);

    FIND (')');

    return val;
}

double GetSin ()
{
    MOVE ();
    FIND ('i');
    FIND ('n');
    FIND ('(');

    double val = GetMnogochlen ();
    val = sin (val);


    FIND (')');

    return val;
}

double GetDeg ()
{
    MOVE ();
    FIND ('e');
    FIND ('g');
    FIND ('(');

    double base = GetMnogochlen();

    FIND (',');
    SkipSpaces();

    double deg = GetMnogochlen();
    FIND (')');


    return DEG (base, deg);
}


double GetAtom ()
{
    double val = 0;
    SkipSpaces();

    switch (S[P])
    {
    case '(':
        {
        MOVE ();

        SkipSpaces();
        val = GetMnogochlen ();
        FIND (')');

        return val;
        }
        break;

    case 's':
        {
            return GetSin ();
        }
        break;

    case 'c':
        {
            return GetCos ();
        }
        break;

    case 'd':
        {
            return GetDeg ();
        }
        break;

    default:
        {
            return GetNumeric ();
        }
    }
}


double GetOdnochlen ()
{
    double val = GetAtom ();
    SkipSpaces();

    while ( NOW ('*') || NOW ('/') )
    {
        SkipSpaces();
        int op = S[P];
        MOVE();
        int tmp_val = GetAtom ();

        if (op == '*')
            val = val * tmp_val;
        else
            val = val / tmp_val;
    }

    return val;
}


double GetMnogochlen ()
{
    double val = GetOdnochlen ();
    SkipSpaces();

    while ( NOW ('+') || NOW ('-') )
    {
        SkipSpaces();

        int op = S[P];
        MOVE();
        int tmp_val = GetOdnochlen();

        if (op == '+')
            val += tmp_val;
        else
            val -= tmp_val;
    }

    return val;
}


double CountPrimer ()
{
    double val = GetMnogochlen();
    assert (NOW ('\0'));
    return val;
}


int main()
{
    S = "2 + deg(2, 1 + sin(0) )*2";

    printf ("%lf", CountPrimer());

    return 0;
}
