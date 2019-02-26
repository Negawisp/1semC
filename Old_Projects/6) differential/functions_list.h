
#define L  branch_copy (node-> left_branch, line)
#define R  branch_copy (node->right_branch, line)
#define dR differential (node->right_branch, diff_var_number, tex, line)
#define dL differential (node-> left_branch, diff_var_number, tex, line)
#define N_NODE(numeric)  node_construct(#numeric, 'mun', line)

#define ADD(l, r)        OpPlus  (l, r)
#define MIN(l, r)        OpMinus (l, r)
#define MUL(l, r)        OpMult  (l, r)
#define DIV(l, r)        OpDiv   (l, r)

#define POW(l, r)        OpDeg   (l, r)
#define LN( node )       OpLog (node, N_NODE(2.7182818286))

#define SIN( node )      OpSin    (node)
#define COS( node )      OpCos    (node)
#define TG(  node )      OpTg     (node)
#define CTG( node )      OpCtg    (node)
#define ASIN(node )      OpArcsin (node)
#define ACOS(node )      OpArccos (node)

#define F                node
#define MAKE_f           struct tree_node* r_node
#define f                r_node

#define TEX()                          \
fprintf (tex, "\\begin{equation}\n("); \
tex_branch(F, tex, line);              \
fprintf (tex, ")'=");                  \
tex_branch(f, tex, line);              \
fprintf (tex, "\\end{equation}");

#define RETURN( arg ) { MAKE_f = arg; TEX(); return f; }

DEF_FUNC( "+", 1,    { RETURN (ADD (dL, dR)); } )
DEF_FUNC( "-", 2,    { RETURN (MIN(dL, dR)); } )
DEF_FUNC( "/", 3,    { RETURN (DIV(MIN(MUL(dL, R), MUL(dR, L)), POW(R, N_NODE(2)))); } )
DEF_FUNC( "*", 4,    { RETURN (ADD(MUL(dL, R), MUL(dR, L))); } )

DEF_FUNC( "^", 5,    { int is_l_f = runner(node->left_branch,  diff_var_number, line, 0, is_var);                            \
                       int is_r_f = runner(node->right_branch, diff_var_number, line, 0, is_var);                            \
                       if (is_l_f && is_r_f)                                                                                 \
                           RETURN (MUL(POW(N_NODE(2.7182818286), MUL(R, LN(L))), ADD(MUL(R, DIV(dL, L)), MUL(dR, LN(L)))));  \
                       if (is_l_f)                                                                                           \
                           RETURN (MUL(R, MUL(POW(L, MIN(R, N_NODE(1))), dL)));                                              \
                       if (is_r_f)                                                                                           \
                           RETURN (MUL(POW(L, R), LN(L)));                                                                   \
                     } )                                                                                                     \

DEF_FUNC( "log", 18, { RETURN (DIV(MIN(MUL(LN(R), DIV(dL, L)), MUL(LN(L), DIV(dR, R))), POW(LN(R), N_NODE(2)))); } )

DEF_FUNC( "sin", 6,     { RETURN (MUL(dL, SIN(ADD(L, N_NODE(1.5707963268)))));  } )
DEF_FUNC( "cos", 7,     { RETURN (MUL(dL, COS(ADD(L, N_NODE(1.5707963268)))));  } )
DEF_FUNC( "tg",  8,     { RETURN (DIV(                dL,  POW(L, N_NODE(2)))); } )
DEF_FUNC( "ctg", 9,     { RETURN (DIV(MUL(N_NODE(-1), dL), POW(L, N_NODE(2)))); } )
DEF_FUNC( "arcsin", 10, { RETURN (DIV(dL, POW(MIN(N_NODE(1), POW(L, N_NODE(2))), N_NODE(0.5)))); } )
DEF_FUNC( "arccos", 11, { RETURN (MUL(N_NODE(-1), DIV(dL, POW(MIN(N_NODE(1), POW(L, N_NODE(2))), N_NODE(0.5))))); } )
DEF_FUNC( "arctg",  12, { RETURN (DIV(dL,  ADD(N_NODE(1), POW(L, N_NODE(2))))); } )
DEF_FUNC( "arcctg", 13, { RETURN (MUL(dL, DIV(N_NODE(-1),  ADD(N_NODE(1), POW(L, N_NODE(2)))))); } )
DEF_FUNC( "sh",  14, { RETURN (MUL(OpCh(L), dL)); } )
DEF_FUNC( "ch",  15, { RETURN (MUL(OpSh(L), dL)); } )
DEF_FUNC( "th",  16, { RETURN (DIV(dL, POW(OpCh(L), N_NODE(2)))); } )
DEF_FUNC( "cth", 17, { RETURN (MUL(dL, DIV(N_NODE(-1), POW(OpSh(L), N_NODE(2))))); } )

#undef RETURN
#undef TEX
#undef f
#undef MAKE_f
#undef F
#undef ACOS
#undef ASIN
#undef CTG
#undef TG
#undef COS
#undef SIN
#undef LN
#undef POW
#undef DIV
#undef MUL
#undef MIN
#undef ADD
#undef N_NODE
#undef dL
#undef dR
#undef R
#undef L
