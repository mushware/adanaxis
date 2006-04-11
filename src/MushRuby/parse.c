//%Header {
/*****************************************************************************
 *
 * File: src/MushRuby/parse.c
 *
 * This file has been taken the ruby distribution and may have been modified.
 * For more information on the original see http://www.ruby-lang.org/.
 *
 * This file may contain original work and modifications by Andy Southgate.
 * In regard to these the author and his employer (Mushware Limited)
 * irrevocably waive all of their copyright rights vested in this particular
 * version of this file to the furthest extent permitted.  The author and
 * Mushware Limited also irrevocably waive any and all of their intellectual
 * property rights arising from said file and its modification and/or additions
 * that would otherwise restrict the rights of any party to use and/or
 * distribute the use of, the techniques and methods used herein.  A written
 * waiver can be obtained via http://www.mushware.com/.  This waiver does not
 * affect the rights of the original author or authors.
 *
 * This software carries NO WARRANTY of any kind from Andy Southgate or
 * Mushware Limited.
 *
 ****************************************************************************/
//%Header } Jor9z96VNYnV7InOAAKMQw
/* A Bison parser, made from parse.y
   by GNU bison 1.35.  */

#define YYBISON 1  /* Identify Bison output.  */

# define	kCLASS	257
# define	kMODULE	258
# define	kDEF	259
# define	kUNDEF	260
# define	kBEGIN	261
# define	kRESCUE	262
# define	kENSURE	263
# define	kEND	264
# define	kIF	265
# define	kUNLESS	266
# define	kTHEN	267
# define	kELSIF	268
# define	kELSE	269
# define	kCASE	270
# define	kWHEN	271
# define	kWHILE	272
# define	kUNTIL	273
# define	kFOR	274
# define	kBREAK	275
# define	kNEXT	276
# define	kREDO	277
# define	kRETRY	278
# define	kIN	279
# define	kDO	280
# define	kDO_COND	281
# define	kDO_BLOCK	282
# define	kRETURN	283
# define	kYIELD	284
# define	kSUPER	285
# define	kSELF	286
# define	kNIL	287
# define	kTRUE	288
# define	kFALSE	289
# define	kAND	290
# define	kOR	291
# define	kNOT	292
# define	kIF_MOD	293
# define	kUNLESS_MOD	294
# define	kWHILE_MOD	295
# define	kUNTIL_MOD	296
# define	kRESCUE_MOD	297
# define	kALIAS	298
# define	kDEFINED	299
# define	klBEGIN	300
# define	klEND	301
# define	k__LINE__	302
# define	k__FILE__	303
# define	tIDENTIFIER	304
# define	tFID	305
# define	tGVAR	306
# define	tIVAR	307
# define	tCONSTANT	308
# define	tCVAR	309
# define	tINTEGER	310
# define	tFLOAT	311
# define	tSTRING_CONTENT	312
# define	tNTH_REF	313
# define	tBACK_REF	314
# define	tREGEXP_END	315
# define	tUPLUS	316
# define	tUMINUS	317
# define	tPOW	318
# define	tCMP	319
# define	tEQ	320
# define	tEQQ	321
# define	tNEQ	322
# define	tGEQ	323
# define	tLEQ	324
# define	tANDOP	325
# define	tOROP	326
# define	tMATCH	327
# define	tNMATCH	328
# define	tDOT2	329
# define	tDOT3	330
# define	tAREF	331
# define	tASET	332
# define	tLSHFT	333
# define	tRSHFT	334
# define	tCOLON2	335
# define	tCOLON3	336
# define	tOP_ASGN	337
# define	tASSOC	338
# define	tLPAREN	339
# define	tLPAREN_ARG	340
# define	tRPAREN	341
# define	tLBRACK	342
# define	tLBRACE	343
# define	tLBRACE_ARG	344
# define	tSTAR	345
# define	tAMPER	346
# define	tSYMBEG	347
# define	tSTRING_BEG	348
# define	tXSTRING_BEG	349
# define	tREGEXP_BEG	350
# define	tWORDS_BEG	351
# define	tQWORDS_BEG	352
# define	tSTRING_DBEG	353
# define	tSTRING_DVAR	354
# define	tSTRING_END	355
# define	tLOWEST	356
# define	tUMINUS_NUM	357
# define	tLAST_TOKEN	358

#line 13 "parse.y"


#define YYDEBUG 1
#define YYERROR_VERBOSE 1
#ifndef YYSTACK_USE_ALLOCA
#define YYSTACK_USE_ALLOCA 0
#endif

#include "ruby.h"
#include "env.h"
#include "intern.h"
#include "node.h"
#include "st.h"
#include <stdio.h>
#include <errno.h>
#include <ctype.h>

#define YYMALLOC	rb_parser_malloc
#define YYREALLOC	rb_parser_realloc
#define YYCALLOC	rb_parser_calloc
#define YYFREE 	rb_parser_free
#define malloc	YYMALLOC
#define realloc	YYREALLOC
#define calloc	YYCALLOC
#define free	YYFREE
static void *rb_parser_malloc _((size_t));
static void *rb_parser_realloc _((void *, size_t));
static void *rb_parser_calloc _((size_t, size_t));
static void rb_parser_free _((void *));

#define yyparse ruby_yyparse
#define yylex ruby_yylex
#define yyerror ruby_yyerror
#define yylval ruby_yylval
#define yychar ruby_yychar
#define yydebug ruby_yydebug

#define ID_SCOPE_SHIFT 3
#define ID_SCOPE_MASK 0x07
#define ID_LOCAL    0x01
#define ID_INSTANCE 0x02
#define ID_GLOBAL   0x03
#define ID_ATTRSET  0x04
#define ID_CONST    0x05
#define ID_CLASS    0x06
#define ID_JUNK     0x07
#define ID_INTERNAL ID_JUNK

#define is_notop_id(id) ((id)>tLAST_TOKEN)
#define is_local_id(id) (is_notop_id(id)&&((id)&ID_SCOPE_MASK)==ID_LOCAL)
#define is_global_id(id) (is_notop_id(id)&&((id)&ID_SCOPE_MASK)==ID_GLOBAL)
#define is_instance_id(id) (is_notop_id(id)&&((id)&ID_SCOPE_MASK)==ID_INSTANCE)
#define is_attrset_id(id) (is_notop_id(id)&&((id)&ID_SCOPE_MASK)==ID_ATTRSET)
#define is_const_id(id) (is_notop_id(id)&&((id)&ID_SCOPE_MASK)==ID_CONST)
#define is_class_id(id) (is_notop_id(id)&&((id)&ID_SCOPE_MASK)==ID_CLASS)
#define is_junk_id(id) (is_notop_id(id)&&((id)&ID_SCOPE_MASK)==ID_JUNK)

#define is_asgn_or_id(id) ((is_notop_id(id)) && \
	(((id)&ID_SCOPE_MASK) == ID_GLOBAL || \
	 ((id)&ID_SCOPE_MASK) == ID_INSTANCE || \
	 ((id)&ID_SCOPE_MASK) == ID_CLASS))

NODE *ruby_eval_tree_begin = 0;
NODE *ruby_eval_tree = 0;

char *ruby_sourcefile;		/* current source file */
int   ruby_sourceline;		/* current line no. */

static int yylex();
static int yyerror();

static enum lex_state {
    EXPR_BEG,			/* ignore newline, +/- is a sign. */
    EXPR_END,			/* newline significant, +/- is a operator. */
    EXPR_ARG,			/* newline significant, +/- is a operator. */
    EXPR_CMDARG,		/* newline significant, +/- is a operator. */
    EXPR_ENDARG,		/* newline significant, +/- is a operator. */
    EXPR_MID,			/* newline significant, +/- is a operator. */
    EXPR_FNAME,			/* ignore newline, no reserved words. */
    EXPR_DOT,			/* right after `.' or `::', no reserved words. */
    EXPR_CLASS,			/* immediate after `class', no here document. */
} lex_state;
static NODE *lex_strterm;

#ifdef HAVE_LONG_LONG
typedef unsigned LONG_LONG stack_type;
#else
typedef unsigned long stack_type;
#endif

#define BITSTACK_PUSH(stack, n)	(stack = (stack<<1)|((n)&1))
#define BITSTACK_POP(stack)	(stack >>= 1)
#define BITSTACK_LEXPOP(stack)	(stack = (stack >> 1) | (stack & 1))
#define BITSTACK_SET_P(stack)	(stack&1)

static stack_type cond_stack = 0;
#define COND_PUSH(n)	BITSTACK_PUSH(cond_stack, n)
#define COND_POP()	BITSTACK_POP(cond_stack)
#define COND_LEXPOP()	BITSTACK_LEXPOP(cond_stack)
#define COND_P()	BITSTACK_SET_P(cond_stack)

static stack_type cmdarg_stack = 0;
#define CMDARG_PUSH(n)	BITSTACK_PUSH(cmdarg_stack, n)
#define CMDARG_POP()	BITSTACK_POP(cmdarg_stack)
#define CMDARG_LEXPOP()	BITSTACK_LEXPOP(cmdarg_stack)
#define CMDARG_P()	BITSTACK_SET_P(cmdarg_stack)

static int class_nest = 0;
static int in_single = 0;
static int in_def = 0;
static int compile_for_eval = 0;
static ID cur_mid = 0;

static NODE *cond();
static NODE *logop();
static int cond_negative();

static NODE *newline_node();
static void fixpos();

static int value_expr0();
static void void_expr0();
static void void_stmts();
static NODE *remove_begin();
#define value_expr(node) value_expr0((node) = remove_begin(node))
#define void_expr(node) void_expr0((node) = remove_begin(node))

static NODE *block_append();
static NODE *list_append();
static NODE *list_concat();
static NODE *arg_concat();
static NODE *arg_prepend();
static NODE *literal_concat();
static NODE *new_evstr();
static NODE *evstr2dstr();
static NODE *call_op();
static int in_defined = 0;

static NODE *negate_lit();
static NODE *ret_args();
static NODE *arg_blk_pass();
static NODE *new_call();
static NODE *new_fcall();
static NODE *new_super();
static NODE *new_yield();

static NODE *gettable();
static NODE *assignable();
static NODE *aryset();
static NODE *attrset();
static void rb_backref_error();
static NODE *node_assign();

static NODE *match_gen();
static void local_push();
static void local_pop();
static int  local_append();
static int  local_cnt();
static int  local_id();
static ID  *local_tbl();
static ID   internal_id();

static struct RVarmap *dyna_push();
static void dyna_pop();
static int dyna_in_block();
static NODE *dyna_init();

static void top_local_init();
static void top_local_setup();

#define RE_OPTION_ONCE 0x80

#define NODE_STRTERM NODE_ZARRAY	/* nothing to gc */
#define NODE_HEREDOC NODE_ARRAY 	/* 1, 3 to gc */
#define SIGN_EXTEND(x,n) (((1<<(n)-1)^((x)&~(~0<<(n))))-(1<<(n)-1))
#define nd_func u1.id
#if SIZEOF_SHORT == 2
#define nd_term(node) ((signed short)(node)->u2.id)
#else
#define nd_term(node) SIGN_EXTEND((node)->u2.id, CHAR_BIT*2)
#endif
#define nd_paren(node) (char)((node)->u2.id >> CHAR_BIT*2)
#define nd_nest u3.id

/* Older versions of Yacc set YYMAXDEPTH to a very low value by default (150,
   for instance).  This is too low for Ruby to parse some files, such as
   date/format.rb, therefore bump the value up to at least Bison's default. */
#ifdef OLD_YACC
#ifndef YYMAXDEPTH
#define YYMAXDEPTH 10000
#endif
#endif


#line 208 "parse.y"
#ifndef YYSTYPE
typedef union {
    NODE *node;
    ID id;
    int num;
    struct RVarmap *vars;
} yystype;
# define YYSTYPE yystype
# define YYSTYPE_IS_TRIVIAL 1
#endif
#ifndef YYDEBUG
# define YYDEBUG 0
#endif



#define	YYFINAL		895
#define	YYFLAG		-32768
#define	YYNTBASE	132

/* YYTRANSLATE(YYLEX) -- Bison token number corresponding to YYLEX. */
#define YYTRANSLATE(x) ((unsigned)(x) <= 358 ? yytranslate[x] : 274)

/* YYTRANSLATE[YYLEX] -- Bison token number corresponding to YYLEX. */
static const short yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     130,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,   129,   117,     2,     2,     2,   115,   110,     2,
     128,   125,   113,   111,   126,   112,   124,   114,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   105,   131,
     107,   103,   106,   104,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   122,     2,   123,   109,     2,   127,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   120,   108,   121,   118,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   116,   119
};

#if YYDEBUG
static const short yyprhs[] =
{
       0,     0,     1,     4,     9,    12,    14,    16,    20,    23,
      24,    29,    33,    37,    41,    44,    48,    52,    56,    60,
      64,    65,    71,    76,    80,    84,    88,    95,   101,   107,
     113,   117,   121,   125,   129,   131,   133,   137,   141,   144,
     147,   149,   151,   153,   155,   158,   161,   164,   166,   171,
     176,   177,   178,   185,   188,   192,   197,   203,   208,   214,
     217,   220,   222,   226,   228,   232,   234,   237,   241,   244,
     247,   249,   251,   255,   258,   262,   264,   269,   273,   277,
     281,   285,   288,   290,   292,   297,   301,   305,   309,   313,
     316,   318,   320,   322,   325,   327,   331,   333,   335,   337,
     339,   341,   343,   345,   347,   348,   353,   355,   357,   359,
     361,   363,   365,   367,   369,   371,   373,   375,   377,   379,
     381,   383,   385,   387,   389,   391,   393,   395,   397,   399,
     401,   403,   405,   407,   409,   411,   413,   415,   417,   419,
     421,   423,   425,   427,   429,   431,   433,   435,   437,   439,
     441,   443,   445,   447,   449,   451,   453,   455,   457,   459,
     461,   463,   465,   467,   469,   471,   473,   475,   477,   479,
     481,   483,   485,   487,   491,   497,   501,   508,   514,   520,
     526,   532,   537,   541,   545,   549,   553,   557,   561,   565,
     569,   573,   578,   583,   586,   589,   593,   597,   601,   605,
     609,   613,   617,   621,   625,   629,   633,   637,   641,   644,
     647,   651,   655,   659,   663,   664,   669,   675,   677,   679,
     681,   684,   687,   693,   696,   700,   704,   709,   714,   721,
     723,   725,   727,   730,   736,   739,   745,   750,   758,   762,
     764,   769,   773,   779,   787,   790,   796,   801,   808,   816,
     826,   830,   832,   833,   836,   838,   839,   843,   844,   849,
     852,   855,   857,   859,   863,   867,   872,   875,   877,   879,
     881,   883,   885,   887,   889,   891,   893,   894,   899,   900,
     906,   910,   914,   917,   922,   926,   930,   932,   937,   941,
     943,   944,   951,   954,   956,   959,   966,   973,   974,   975,
     983,   984,   985,   993,   999,  1004,  1010,  1011,  1012,  1022,
    1023,  1030,  1031,  1032,  1041,  1042,  1048,  1049,  1056,  1057,
    1058,  1068,  1070,  1072,  1074,  1076,  1078,  1080,  1082,  1084,
    1087,  1089,  1091,  1093,  1095,  1101,  1103,  1106,  1108,  1110,
    1112,  1115,  1117,  1121,  1122,  1123,  1130,  1133,  1138,  1143,
    1146,  1151,  1156,  1160,  1163,  1165,  1166,  1167,  1174,  1175,
    1176,  1183,  1189,  1191,  1196,  1199,  1201,  1203,  1210,  1212,
    1214,  1216,  1218,  1221,  1223,  1226,  1228,  1230,  1232,  1234,
    1236,  1238,  1241,  1245,  1249,  1253,  1257,  1261,  1262,  1266,
    1268,  1271,  1275,  1279,  1280,  1284,  1285,  1288,  1289,  1292,
    1294,  1295,  1299,  1300,  1305,  1307,  1309,  1311,  1313,  1316,
    1318,  1320,  1322,  1324,  1328,  1330,  1332,  1335,  1338,  1340,
    1342,  1344,  1346,  1348,  1350,  1352,  1354,  1356,  1358,  1360,
    1362,  1364,  1366,  1368,  1370,  1371,  1376,  1379,  1384,  1387,
    1394,  1399,  1404,  1407,  1412,  1415,  1418,  1420,  1421,  1423,
    1425,  1427,  1429,  1431,  1433,  1437,  1441,  1443,  1447,  1449,
    1451,  1454,  1456,  1458,  1460,  1463,  1466,  1468,  1470,  1471,
    1477,  1479,  1482,  1485,  1487,  1491,  1495,  1497,  1499,  1501,
    1503,  1505,  1507,  1509,  1511,  1513,  1515,  1517,  1519,  1520,
    1522,  1523,  1525,  1526,  1528,  1530,  1532,  1534,  1536,  1539
};
static const short yyrhs[] =
{
      -1,   133,   135,     0,   135,   217,   201,   220,     0,   136,
     268,     0,   273,     0,   137,     0,   136,   272,   137,     0,
       1,   137,     0,     0,    44,   158,   138,   158,     0,    44,
      52,    52,     0,    44,    52,    60,     0,    44,    52,    59,
       0,     6,   159,     0,   137,    39,   141,     0,   137,    40,
     141,     0,   137,    41,   141,     0,   137,    42,   141,     0,
     137,    43,   137,     0,     0,    46,   139,   120,   135,   121,
       0,    47,   120,   135,   121,     0,   154,   103,   142,     0,
     148,   103,   142,     0,   244,    83,   142,     0,   197,   122,
     166,   123,    83,   142,     0,   197,   124,    50,    83,   142,
       0,   197,   124,    54,    83,   142,     0,   197,    81,    50,
      83,   142,     0,   245,    83,   142,     0,   154,   103,   179,
       0,   148,   103,   165,     0,   148,   103,   179,     0,   140,
       0,   142,     0,   140,    36,   140,     0,   140,    37,   140,
       0,    38,   140,     0,   117,   142,     0,   163,     0,   140,
       0,   147,     0,   143,     0,    29,   169,     0,    21,   169,
       0,    22,   169,     0,   207,     0,   207,   124,   265,   171,
       0,   207,    81,   265,   171,     0,     0,     0,    90,   145,
     203,   146,   135,   121,     0,   264,   171,     0,   264,   171,
     144,     0,   197,   124,   265,   171,     0,   197,   124,   265,
     171,   144,     0,   197,    81,   265,   171,     0,   197,    81,
     265,   171,   144,     0,    31,   171,     0,    30,   171,     0,
     150,     0,    85,   149,   125,     0,   150,     0,    85,   149,
     125,     0,   152,     0,   152,   151,     0,   152,    91,   153,
       0,   152,    91,     0,    91,   153,     0,    91,     0,   153,
       0,    85,   149,   125,     0,   151,   126,     0,   152,   151,
     126,     0,   242,     0,   197,   122,   166,   123,     0,   197,
     124,    50,     0,   197,    81,    50,     0,   197,   124,    54,
       0,   197,    81,    54,     0,    82,    54,     0,   245,     0,
     242,     0,   197,   122,   166,   123,     0,   197,   124,    50,
       0,   197,    81,    50,     0,   197,   124,    54,     0,   197,
      81,    54,     0,    82,    54,     0,   245,     0,    50,     0,
      54,     0,    82,   155,     0,   155,     0,   197,    81,   155,
       0,    50,     0,    54,     0,    51,     0,   161,     0,   162,
       0,   157,     0,   238,     0,   158,     0,     0,   159,   126,
     160,   158,     0,   108,     0,   109,     0,   110,     0,    65,
       0,    66,     0,    67,     0,    73,     0,   106,     0,    69,
       0,   107,     0,    70,     0,    79,     0,    80,     0,   111,
       0,   112,     0,   113,     0,    91,     0,   114,     0,   115,
       0,    64,     0,   118,     0,    62,     0,    63,     0,    77,
       0,    78,     0,   127,     0,    48,     0,    49,     0,    46,
       0,    47,     0,    44,     0,    36,     0,     7,     0,    21,
       0,    16,     0,     3,     0,     5,     0,    45,     0,    26,
       0,    15,     0,    14,     0,    10,     0,     9,     0,    35,
       0,    20,     0,    25,     0,     4,     0,    22,     0,    33,
       0,    38,     0,    37,     0,    23,     0,     8,     0,    24,
       0,    29,     0,    32,     0,    31,     0,    13,     0,    34,
       0,     6,     0,    17,     0,    30,     0,    39,     0,    40,
       0,    41,     0,    42,     0,    43,     0,   154,   103,   163,
       0,   154,   103,   163,    43,   163,     0,   244,    83,   163,
       0,   197,   122,   166,   123,    83,   163,     0,   197,   124,
      50,    83,   163,     0,   197,   124,    54,    83,   163,     0,
     197,    81,    50,    83,   163,     0,   197,    81,    54,    83,
     163,     0,    82,    54,    83,   163,     0,   245,    83,   163,
       0,   163,    75,   163,     0,   163,    76,   163,     0,   163,
     111,   163,     0,   163,   112,   163,     0,   163,   113,   163,
       0,   163,   114,   163,     0,   163,   115,   163,     0,   163,
      64,   163,     0,   116,    56,    64,   163,     0,   116,    57,
      64,   163,     0,    62,   163,     0,    63,   163,     0,   163,
     108,   163,     0,   163,   109,   163,     0,   163,   110,   163,
       0,   163,    65,   163,     0,   163,   106,   163,     0,   163,
      69,   163,     0,   163,   107,   163,     0,   163,    70,   163,
       0,   163,    66,   163,     0,   163,    67,   163,     0,   163,
      68,   163,     0,   163,    73,   163,     0,   163,    74,   163,
       0,   117,   163,     0,   118,   163,     0,   163,    79,   163,
       0,   163,    80,   163,     0,   163,    71,   163,     0,   163,
      72,   163,     0,     0,    45,   269,   164,   163,     0,   163,
     104,   163,   105,   163,     0,   180,     0,   163,     0,   273,
       0,   147,   269,     0,   178,   270,     0,   178,   126,    91,
     163,   269,     0,   262,   270,     0,    91,   163,   269,     0,
     128,   273,   125,     0,   128,   169,   269,   125,     0,   128,
     207,   269,   125,     0,   128,   178,   126,   207,   269,   125,
       0,   273,     0,   167,     0,   147,     0,   178,   177,     0,
     178,   126,    91,   165,   177,     0,   262,   177,     0,   262,
     126,    91,   165,   177,     0,   178,   126,   262,   177,     0,
     178,   126,   262,   126,    91,   163,   177,     0,    91,   165,
     177,     0,   176,     0,   165,   126,   178,   177,     0,   165,
     126,   176,     0,   165,   126,    91,   165,   177,     0,   165,
     126,   178,   126,    91,   165,   177,     0,   262,   177,     0,
     262,   126,    91,   165,   177,     0,   165,   126,   262,   177,
       0,   165,   126,   178,   126,   262,   177,     0,   165,   126,
     262,   126,    91,   165,   177,     0,   165,   126,   178,   126,
     262,   126,    91,   165,   177,     0,    91,   165,   177,     0,
     176,     0,     0,   172,   173,     0,   169,     0,     0,    86,
     174,   125,     0,     0,    86,   170,   175,   125,     0,    92,
     165,     0,   126,   176,     0,   273,     0,   165,     0,   178,
     126,   165,     0,   178,   126,   165,     0,   178,   126,    91,
     165,     0,    91,   165,     0,   221,     0,   222,     0,   225,
       0,   226,     0,   227,     0,   230,     0,   243,     0,   245,
       0,    51,     0,     0,     7,   181,   134,    10,     0,     0,
      86,   140,   182,   269,   125,     0,    85,   135,   125,     0,
     197,    81,    54,     0,    82,    54,     0,   197,   122,   166,
     123,     0,    88,   166,   123,     0,    89,   261,   121,     0,
      29,     0,    30,   128,   169,   125,     0,    30,   128,   125,
       0,    30,     0,     0,    45,   269,   128,   183,   140,   125,
       0,   264,   209,     0,   208,     0,   208,   209,     0,    11,
     141,   198,   135,   200,    10,     0,    12,   141,   198,   135,
     201,    10,     0,     0,     0,    18,   184,   141,   199,   185,
     135,    10,     0,     0,     0,    19,   186,   141,   199,   187,
     135,    10,     0,    16,   141,   268,   214,    10,     0,    16,
     268,   214,    10,     0,    16,   268,    15,   135,    10,     0,
       0,     0,    20,   202,    25,   188,   141,   199,   189,   135,
      10,     0,     0,     3,   156,   246,   190,   134,    10,     0,
       0,     0,     3,    79,   140,   191,   271,   192,   134,    10,
       0,     0,     4,   156,   193,   134,    10,     0,     0,     5,
     157,   194,   248,   134,    10,     0,     0,     0,     5,   259,
     267,   195,   157,   196,   248,   134,    10,     0,    21,     0,
      22,     0,    23,     0,    24,     0,   180,     0,   271,     0,
     105,     0,    13,     0,   271,    13,     0,   271,     0,   105,
       0,    27,     0,   201,     0,    14,   141,   198,   135,   200,
       0,   273,     0,    15,   135,     0,   154,     0,   148,     0,
     273,     0,   108,   108,     0,    72,     0,   108,   202,   108,
       0,     0,     0,    28,   205,   203,   206,   135,    10,     0,
     147,   204,     0,   207,   124,   265,   168,     0,   207,    81,
     265,   168,     0,   264,   167,     0,   197,   124,   265,   168,
       0,   197,    81,   265,   167,     0,   197,    81,   266,     0,
      31,   167,     0,    31,     0,     0,     0,   120,   210,   203,
     211,   135,   121,     0,     0,     0,    26,   212,   203,   213,
     135,    10,     0,    17,   215,   198,   135,   216,     0,   178,
       0,   178,   126,    91,   165,     0,    91,   165,     0,   201,
       0,   214,     0,     8,   218,   219,   198,   135,   217,     0,
     273,     0,   165,     0,   179,     0,   273,     0,    84,   154,
       0,   273,     0,     9,   135,     0,   273,     0,   241,     0,
     238,     0,   240,     0,   223,     0,   224,     0,   223,   224,
       0,    94,   232,   101,     0,    95,   233,   101,     0,    96,
     233,    61,     0,    97,   129,   101,     0,    97,   228,   101,
       0,     0,   228,   229,   129,     0,   234,     0,   229,   234,
       0,    98,   129,   101,     0,    98,   231,   101,     0,     0,
     231,    58,   129,     0,     0,   232,   234,     0,     0,   233,
     234,     0,    58,     0,     0,   100,   235,   237,     0,     0,
      99,   236,   135,   121,     0,    52,     0,    53,     0,    55,
       0,   245,     0,    93,   239,     0,   157,     0,    53,     0,
      52,     0,    55,     0,    93,   233,   101,     0,    56,     0,
      57,     0,   116,    56,     0,   116,    57,     0,    50,     0,
      53,     0,    52,     0,    54,     0,    55,     0,    33,     0,
      32,     0,    34,     0,    35,     0,    49,     0,    48,     0,
     242,     0,   242,     0,    59,     0,    60,     0,   271,     0,
       0,   107,   247,   141,   271,     0,     1,   271,     0,   128,
     249,   269,   125,     0,   249,   271,     0,   251,   126,   253,
     126,   255,   258,     0,   251,   126,   253,   258,     0,   251,
     126,   255,   258,     0,   251,   258,     0,   253,   126,   255,
     258,     0,   253,   258,     0,   255,   258,     0,   257,     0,
       0,    54,     0,    53,     0,    52,     0,    55,     0,    50,
       0,   250,     0,   251,   126,   250,     0,    50,   103,   165,
       0,   252,     0,   253,   126,   252,     0,   113,     0,    91,
       0,   254,    50,     0,   254,     0,   110,     0,    92,     0,
     256,    50,     0,   126,   257,     0,   273,     0,   243,     0,
       0,   128,   260,   140,   269,   125,     0,   273,     0,   262,
     270,     0,   178,   270,     0,   263,     0,   262,   126,   263,
       0,   165,    84,   165,     0,    50,     0,    54,     0,    51,
       0,    50,     0,    54,     0,    51,     0,   161,     0,    50,
       0,    51,     0,   161,     0,   124,     0,    81,     0,     0,
     272,     0,     0,   130,     0,     0,   130,     0,   126,     0,
     131,     0,   130,     0,   271,     0,   272,   131,     0,     0
};

#endif

#if YYDEBUG
/* YYRLINE[YYN] -- source line where rule number YYN was defined. */
static const short yyrline[] =
{
       0,   345,   345,   370,   390,   397,   398,   402,   406,   412,
     412,   416,   420,   427,   432,   436,   445,   454,   466,   478,
     482,   482,   496,   504,   508,   514,   539,   558,   570,   582,
     594,   599,   603,   608,   613,   616,   617,   621,   625,   629,
     633,   636,   643,   644,   645,   649,   653,   659,   660,   664,
     670,   670,   670,   685,   690,   702,   707,   719,   724,   736,
     741,   748,   749,   755,   756,   762,   766,   770,   774,   778,
     782,   788,   789,   795,   799,   805,   809,   813,   817,   821,
     825,   831,   837,   844,   848,   852,   856,   860,   864,   870,
     876,   883,   887,   890,   894,   898,   904,   905,   906,   907,
     912,   919,   920,   923,   927,   927,   933,   934,   935,   936,
     937,   938,   939,   940,   941,   942,   943,   944,   945,   946,
     947,   948,   949,   950,   951,   952,   953,   954,   955,   956,
     957,   958,   961,   961,   961,   961,   962,   962,   962,   962,
     962,   962,   962,   963,   963,   963,   963,   963,   963,   963,
     964,   964,   964,   964,   964,   964,   965,   965,   965,   965,
     965,   965,   965,   966,   966,   966,   966,   966,   967,   967,
     967,   967,   967,   970,   974,   978,  1003,  1022,  1034,  1046,
    1058,  1063,  1068,  1073,  1086,  1099,  1103,  1107,  1111,  1115,
    1119,  1123,  1127,  1131,  1140,  1144,  1148,  1152,  1156,  1160,
    1164,  1168,  1172,  1176,  1180,  1184,  1188,  1192,  1196,  1200,
    1204,  1208,  1212,  1216,  1220,  1220,  1225,  1230,  1236,  1243,
    1244,  1249,  1253,  1258,  1262,  1269,  1273,  1277,  1282,  1289,
    1290,  1293,  1298,  1302,  1307,  1312,  1317,  1322,  1328,  1332,
    1335,  1339,  1343,  1348,  1353,  1358,  1363,  1368,  1373,  1378,
    1383,  1387,  1390,  1390,  1402,  1403,  1403,  1408,  1408,  1415,
    1421,  1425,  1428,  1432,  1438,  1442,  1446,  1452,  1453,  1454,
    1455,  1456,  1457,  1458,  1459,  1460,  1464,  1464,  1477,  1477,
    1482,  1486,  1490,  1494,  1502,  1511,  1515,  1519,  1523,  1527,
    1531,  1531,  1536,  1542,  1543,  1552,  1565,  1578,  1578,  1578,
    1588,  1588,  1588,  1598,  1605,  1609,  1613,  1613,  1613,  1620,
    1620,  1636,  1636,  1636,  1658,  1658,  1674,  1674,  1692,  1692,
    1692,  1707,  1711,  1715,  1719,  1725,  1732,  1733,  1734,  1735,
    1738,  1739,  1740,  1743,  1744,  1753,  1754,  1760,  1761,  1764,
    1765,  1769,  1773,  1779,  1779,  1779,  1794,  1803,  1807,  1813,
    1818,  1823,  1828,  1832,  1836,  1842,  1842,  1842,  1854,  1854,
    1854,  1868,  1875,  1876,  1880,  1886,  1887,  1890,  1901,  1904,
    1908,  1909,  1912,  1916,  1919,  1927,  1930,  1931,  1935,  1938,
    1951,  1952,  1958,  1964,  1987,  2020,  2024,  2030,  2034,  2040,
    2041,  2047,  2051,  2057,  2061,  2067,  2071,  2077,  2081,  2087,
    2088,  2088,  2099,  2099,  2120,  2121,  2122,  2123,  2126,  2133,
    2134,  2135,  2136,  2139,  2172,  2173,  2174,  2178,  2184,  2185,
    2186,  2187,  2188,  2189,  2190,  2191,  2192,  2193,  2194,  2197,
    2203,  2209,  2210,  2213,  2217,  2217,  2225,  2228,  2233,  2239,
    2243,  2247,  2251,  2255,  2259,  2263,  2267,  2271,  2277,  2281,
    2285,  2289,  2293,  2304,  2305,  2311,  2321,  2326,  2332,  2333,
    2336,  2344,  2350,  2351,  2354,  2364,  2368,  2371,  2381,  2381,
    2406,  2407,  2411,  2420,  2421,  2427,  2433,  2434,  2435,  2438,
    2439,  2440,  2441,  2444,  2445,  2446,  2449,  2450,  2453,  2454,
    2457,  2458,  2461,  2462,  2463,  2466,  2467,  2470,  2471,  2474
};
#endif


#if (YYDEBUG) || defined YYERROR_VERBOSE

/* YYTNAME[TOKEN_NUM] -- String name of the token TOKEN_NUM. */
static const char *const yytname[] =
{
  "$", "error", "$undefined.", "kCLASS", "kMODULE", "kDEF", "kUNDEF", 
  "kBEGIN", "kRESCUE", "kENSURE", "kEND", "kIF", "kUNLESS", "kTHEN", 
  "kELSIF", "kELSE", "kCASE", "kWHEN", "kWHILE", "kUNTIL", "kFOR", 
  "kBREAK", "kNEXT", "kREDO", "kRETRY", "kIN", "kDO", "kDO_COND", 
  "kDO_BLOCK", "kRETURN", "kYIELD", "kSUPER", "kSELF", "kNIL", "kTRUE", 
  "kFALSE", "kAND", "kOR", "kNOT", "kIF_MOD", "kUNLESS_MOD", "kWHILE_MOD", 
  "kUNTIL_MOD", "kRESCUE_MOD", "kALIAS", "kDEFINED", "klBEGIN", "klEND", 
  "k__LINE__", "k__FILE__", "tIDENTIFIER", "tFID", "tGVAR", "tIVAR", 
  "tCONSTANT", "tCVAR", "tINTEGER", "tFLOAT", "tSTRING_CONTENT", 
  "tNTH_REF", "tBACK_REF", "tREGEXP_END", "tUPLUS", "tUMINUS", "tPOW", 
  "tCMP", "tEQ", "tEQQ", "tNEQ", "tGEQ", "tLEQ", "tANDOP", "tOROP", 
  "tMATCH", "tNMATCH", "tDOT2", "tDOT3", "tAREF", "tASET", "tLSHFT", 
  "tRSHFT", "tCOLON2", "tCOLON3", "tOP_ASGN", "tASSOC", "tLPAREN", 
  "tLPAREN_ARG", "tRPAREN", "tLBRACK", "tLBRACE", "tLBRACE_ARG", "tSTAR", 
  "tAMPER", "tSYMBEG", "tSTRING_BEG", "tXSTRING_BEG", "tREGEXP_BEG", 
  "tWORDS_BEG", "tQWORDS_BEG", "tSTRING_DBEG", "tSTRING_DVAR", 
  "tSTRING_END", "tLOWEST", "'='", "'?'", "':'", "'>'", "'<'", "'|'", 
  "'^'", "'&'", "'+'", "'-'", "'*'", "'/'", "'%'", "tUMINUS_NUM", "'!'", 
  "'~'", "tLAST_TOKEN", "'{'", "'}'", "'['", "']'", "'.'", "')'", "','", 
  "'`'", "'('", "' '", "'\\n'", "';'", "program", "@1", "bodystmt", 
  "compstmt", "stmts", "stmt", "@2", "@3", "expr", "expr_value", 
  "command_call", "block_command", "cmd_brace_block", "@4", "@5", 
  "command", "mlhs", "mlhs_entry", "mlhs_basic", "mlhs_item", "mlhs_head", 
  "mlhs_node", "lhs", "cname", "cpath", "fname", "fitem", "undef_list", 
  "@6", "op", "reswords", "arg", "@7", "arg_value", "aref_args", 
  "paren_args", "opt_paren_args", "call_args", "call_args2", 
  "command_args", "@8", "open_args", "@9", "@10", "block_arg", 
  "opt_block_arg", "args", "mrhs", "primary", "@11", "@12", "@13", "@14", 
  "@15", "@16", "@17", "@18", "@19", "@20", "@21", "@22", "@23", "@24", 
  "@25", "@26", "primary_value", "then", "do", "if_tail", "opt_else", 
  "block_var", "opt_block_var", "do_block", "@27", "@28", "block_call", 
  "method_call", "brace_block", "@29", "@30", "@31", "@32", "case_body", 
  "when_args", "cases", "opt_rescue", "exc_list", "exc_var", "opt_ensure", 
  "literal", "strings", "string", "string1", "xstring", "regexp", "words", 
  "word_list", "word", "qwords", "qword_list", "string_contents", 
  "xstring_contents", "string_content", "@33", "@34", "string_dvar", 
  "symbol", "sym", "dsym", "numeric", "variable", "var_ref", "var_lhs", 
  "backref", "superclass", "@35", "f_arglist", "f_args", "f_norm_arg", 
  "f_arg", "f_opt", "f_optarg", "restarg_mark", "f_rest_arg", 
  "blkarg_mark", "f_block_arg", "opt_f_block_arg", "singleton", "@36", 
  "assoc_list", "assocs", "assoc", "operation", "operation2", 
  "operation3", "dot_or_colon", "opt_terms", "opt_nl", "trailer", "term", 
  "terms", "none", 0
};
#endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives. */
static const short yyr1[] =
{
       0,   133,   132,   134,   135,   136,   136,   136,   136,   138,
     137,   137,   137,   137,   137,   137,   137,   137,   137,   137,
     139,   137,   137,   137,   137,   137,   137,   137,   137,   137,
     137,   137,   137,   137,   137,   140,   140,   140,   140,   140,
     140,   141,   142,   142,   142,   142,   142,   143,   143,   143,
     145,   146,   144,   147,   147,   147,   147,   147,   147,   147,
     147,   148,   148,   149,   149,   150,   150,   150,   150,   150,
     150,   151,   151,   152,   152,   153,   153,   153,   153,   153,
     153,   153,   153,   154,   154,   154,   154,   154,   154,   154,
     154,   155,   155,   156,   156,   156,   157,   157,   157,   157,
     157,   158,   158,   159,   160,   159,   161,   161,   161,   161,
     161,   161,   161,   161,   161,   161,   161,   161,   161,   161,
     161,   161,   161,   161,   161,   161,   161,   161,   161,   161,
     161,   161,   162,   162,   162,   162,   162,   162,   162,   162,
     162,   162,   162,   162,   162,   162,   162,   162,   162,   162,
     162,   162,   162,   162,   162,   162,   162,   162,   162,   162,
     162,   162,   162,   162,   162,   162,   162,   162,   162,   162,
     162,   162,   162,   163,   163,   163,   163,   163,   163,   163,
     163,   163,   163,   163,   163,   163,   163,   163,   163,   163,
     163,   163,   163,   163,   163,   163,   163,   163,   163,   163,
     163,   163,   163,   163,   163,   163,   163,   163,   163,   163,
     163,   163,   163,   163,   164,   163,   163,   163,   165,   166,
     166,   166,   166,   166,   166,   167,   167,   167,   167,   168,
     168,   169,   169,   169,   169,   169,   169,   169,   169,   169,
     170,   170,   170,   170,   170,   170,   170,   170,   170,   170,
     170,   170,   172,   171,   173,   174,   173,   175,   173,   176,
     177,   177,   178,   178,   179,   179,   179,   180,   180,   180,
     180,   180,   180,   180,   180,   180,   181,   180,   182,   180,
     180,   180,   180,   180,   180,   180,   180,   180,   180,   180,
     183,   180,   180,   180,   180,   180,   180,   184,   185,   180,
     186,   187,   180,   180,   180,   180,   188,   189,   180,   190,
     180,   191,   192,   180,   193,   180,   194,   180,   195,   196,
     180,   180,   180,   180,   180,   197,   198,   198,   198,   198,
     199,   199,   199,   200,   200,   201,   201,   202,   202,   203,
     203,   203,   203,   205,   206,   204,   207,   207,   207,   208,
     208,   208,   208,   208,   208,   210,   211,   209,   212,   213,
     209,   214,   215,   215,   215,   216,   216,   217,   217,   218,
     218,   218,   219,   219,   220,   220,   221,   221,   221,   222,
     223,   223,   224,   225,   226,   227,   227,   228,   228,   229,
     229,   230,   230,   231,   231,   232,   232,   233,   233,   234,
     235,   234,   236,   234,   237,   237,   237,   237,   238,   239,
     239,   239,   239,   240,   241,   241,   241,   241,   242,   242,
     242,   242,   242,   242,   242,   242,   242,   242,   242,   243,
     244,   245,   245,   246,   247,   246,   246,   248,   248,   249,
     249,   249,   249,   249,   249,   249,   249,   249,   250,   250,
     250,   250,   250,   251,   251,   252,   253,   253,   254,   254,
     255,   255,   256,   256,   257,   258,   258,   259,   260,   259,
     261,   261,   261,   262,   262,   263,   264,   264,   264,   265,
     265,   265,   265,   266,   266,   266,   267,   267,   268,   268,
     269,   269,   270,   270,   270,   271,   271,   272,   272,   273
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN. */
static const short yyr2[] =
{
       0,     0,     2,     4,     2,     1,     1,     3,     2,     0,
       4,     3,     3,     3,     2,     3,     3,     3,     3,     3,
       0,     5,     4,     3,     3,     3,     6,     5,     5,     5,
       3,     3,     3,     3,     1,     1,     3,     3,     2,     2,
       1,     1,     1,     1,     2,     2,     2,     1,     4,     4,
       0,     0,     6,     2,     3,     4,     5,     4,     5,     2,
       2,     1,     3,     1,     3,     1,     2,     3,     2,     2,
       1,     1,     3,     2,     3,     1,     4,     3,     3,     3,
       3,     2,     1,     1,     4,     3,     3,     3,     3,     2,
       1,     1,     1,     2,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     5,     3,     6,     5,     5,     5,
       5,     4,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     4,     4,     2,     2,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     2,     2,
       3,     3,     3,     3,     0,     4,     5,     1,     1,     1,
       2,     2,     5,     2,     3,     3,     4,     4,     6,     1,
       1,     1,     2,     5,     2,     5,     4,     7,     3,     1,
       4,     3,     5,     7,     2,     5,     4,     6,     7,     9,
       3,     1,     0,     2,     1,     0,     3,     0,     4,     2,
       2,     1,     1,     3,     3,     4,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     0,     5,
       3,     3,     2,     4,     3,     3,     1,     4,     3,     1,
       0,     6,     2,     1,     2,     6,     6,     0,     0,     7,
       0,     0,     7,     5,     4,     5,     0,     0,     9,     0,
       6,     0,     0,     8,     0,     5,     0,     6,     0,     0,
       9,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       1,     1,     1,     1,     5,     1,     2,     1,     1,     1,
       2,     1,     3,     0,     0,     6,     2,     4,     4,     2,
       4,     4,     3,     2,     1,     0,     0,     6,     0,     0,
       6,     5,     1,     4,     2,     1,     1,     6,     1,     1,
       1,     1,     2,     1,     2,     1,     1,     1,     1,     1,
       1,     2,     3,     3,     3,     3,     3,     0,     3,     1,
       2,     3,     3,     0,     3,     0,     2,     0,     2,     1,
       0,     3,     0,     4,     1,     1,     1,     1,     2,     1,
       1,     1,     1,     3,     1,     1,     2,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     2,     4,     2,     6,
       4,     4,     2,     4,     2,     2,     1,     0,     1,     1,
       1,     1,     1,     1,     3,     3,     1,     3,     1,     1,
       2,     1,     1,     1,     2,     2,     1,     1,     0,     5,
       1,     2,     2,     1,     3,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     1,
       0,     1,     0,     1,     1,     1,     1,     1,     2,     0
};

/* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
   doesn't specify something else to do.  Zero means the default is an
   error. */
static const short yydefact[] =
{
       1,     0,     0,     0,     0,     0,     0,   276,     0,     0,
     488,   297,   300,     0,   321,   322,   323,   324,   286,   289,
     354,   424,   423,   425,   426,     0,     0,   490,    20,     0,
     428,   427,   418,   275,   420,   419,   421,   422,   414,   415,
     431,   432,     0,     0,     0,     0,     0,   499,   499,    70,
     397,   395,   397,   397,   387,   393,     0,     0,     0,     2,
     488,     6,    34,    35,    43,    42,     0,    61,     0,    65,
      71,     0,    40,   217,     0,    47,   293,   267,   268,   379,
     380,   269,   270,   271,   272,   377,   378,   376,   429,   273,
       0,   274,   252,     5,     8,   321,   322,   286,   289,   354,
     490,    91,    92,     0,     0,     0,     0,    94,     0,   325,
       0,   429,   274,     0,   314,   141,   152,   142,   165,   138,
     158,   148,   147,   163,   146,   145,   140,   166,   150,   139,
     153,   157,   159,   151,   144,   160,   167,   162,   161,   154,
     164,   149,   137,   156,   155,   168,   169,   170,   171,   172,
     136,   143,   134,   135,   132,   133,    96,    98,    97,   127,
     128,   125,   109,   110,   111,   114,   116,   112,   129,   130,
     117,   118,   122,   113,   115,   106,   107,   108,   119,   120,
     121,   123,   124,   126,   131,   468,   316,    99,   100,   467,
       0,   161,   154,   164,   149,   132,   133,    96,    97,     0,
     101,   103,    14,   102,     0,     0,    41,     0,     0,     0,
     429,     0,   274,     0,   496,   495,   488,     0,   497,   489,
       0,     0,     0,   338,   337,     0,     0,   429,   274,     0,
       0,     0,   231,   218,   262,    45,   239,   499,   499,   473,
      46,    44,     0,    60,     0,   499,   353,    59,    38,     0,
       9,   491,   214,     0,     0,   193,     0,   194,   282,     0,
       0,     0,    61,   278,     0,   490,     0,   492,   492,   219,
     492,     0,   492,   470,     0,    69,     0,    75,    82,   411,
     410,   412,   409,     0,   408,     0,     0,     0,     0,     0,
       0,     0,   416,   417,    39,   208,   209,     4,   489,     0,
       0,     0,     0,     0,     0,     0,   343,   346,     0,    73,
       0,    68,    66,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   499,     0,     0,     0,   358,   355,   294,   381,     0,
       0,   349,    53,   292,     0,   311,    91,    92,    93,   416,
     417,     0,   434,   309,   433,     0,   499,     0,     0,     0,
     447,   487,   486,   318,   104,     0,   499,   282,   328,   327,
       0,   326,     0,     0,   499,     0,     0,     0,     0,     0,
       0,     0,     0,   498,     0,     0,   282,     0,   499,     0,
     306,   499,   259,     0,     0,   232,   261,     0,   234,   288,
       0,   255,   254,   253,   231,   490,   499,   490,     0,    11,
      13,    12,     0,   290,     0,     0,     0,     0,     0,     0,
       0,   280,    62,   490,   490,   220,   284,   494,   493,   221,
     494,   223,   494,   472,   285,   471,    81,     0,   499,     0,
     399,   402,   400,   413,   398,   382,   396,   383,   384,   385,
     386,     0,   389,   391,     0,   392,     0,     0,     7,    15,
      16,    17,    18,    19,    36,    37,   499,     0,    24,    32,
       0,    33,     0,    67,    74,    23,   173,   262,    31,   190,
     198,   203,   204,   205,   200,   202,   212,   213,   206,   207,
     183,   184,   210,   211,     0,   199,   201,   195,   196,   197,
     185,   186,   187,   188,   189,   479,   484,   480,   485,   252,
     352,     0,   479,   481,   480,   482,   499,   479,   480,   252,
     252,   499,   499,    25,   175,    30,   182,    50,    54,     0,
     436,     0,     0,    91,    92,    95,     0,     0,   499,     0,
     490,   452,   450,   449,   448,   451,   459,   463,   462,   458,
     447,     0,     0,   453,   499,   456,   499,   461,   499,     0,
     446,     0,     0,   277,   499,   499,   368,   499,   329,   173,
     483,   281,     0,   479,   480,   499,     0,     0,     0,   362,
       0,   304,   332,   331,   298,   330,   301,   483,   281,     0,
     479,   480,     0,     0,   238,   475,     0,   263,   260,   499,
       0,     0,   474,   287,     0,    40,     0,   257,     0,   251,
     499,     0,     0,     0,     0,     0,   225,    10,     0,   215,
       0,    22,   181,    62,     0,   224,     0,   263,    78,    80,
       0,   479,   480,     0,     0,   388,   390,   394,   191,   192,
     341,     0,   344,   339,   266,     0,    72,     0,     0,     0,
       0,   351,    57,   283,     0,     0,   230,   350,    55,   229,
     348,    49,   347,    48,   359,   356,   499,   312,     0,     0,
     283,   315,     0,     0,   490,     0,   438,     0,   442,   466,
       0,   444,   460,     0,   445,   464,   319,   105,   369,   370,
     499,   371,     0,   499,   335,     0,     0,   333,     0,   283,
       0,     0,     0,   303,   305,   364,     0,     0,     0,     0,
     283,     0,   499,     0,   236,   499,   499,     0,     0,   256,
       0,   244,   226,     0,   490,   499,   499,   227,     0,    21,
     279,   490,    76,     0,   404,   405,   406,   401,   407,   340,
       0,     0,     0,   264,   174,   216,    29,   179,   180,    58,
       0,    27,   177,    28,   178,    56,     0,     0,    51,     0,
     435,   310,   469,   455,     0,   317,   454,   499,   499,   465,
       0,   457,   499,   447,     0,     0,   373,   336,     0,     3,
     375,     0,   295,     0,   296,     0,   499,     0,     0,   307,
     233,     0,   235,   250,     0,   241,   499,   499,   258,     0,
       0,   291,   222,   403,   342,     0,   265,    26,   176,     0,
       0,     0,     0,   437,     0,   440,   441,   443,     0,     0,
     372,     0,    83,    90,     0,   374,     0,   363,   365,   366,
     361,   299,   302,     0,   499,   499,     0,   240,     0,   246,
     499,   228,   345,   360,   357,     0,   313,   499,     0,    89,
       0,   499,     0,   499,   499,     0,   237,   242,     0,   499,
       0,   245,    52,   439,   320,   483,    88,     0,   479,   480,
     367,   334,   308,   499,     0,   247,   499,    84,   243,     0,
     248,   499,   249,     0,     0,     0
};

static const short yydefgoto[] =
{
     893,     1,   375,   376,    60,    61,   422,   253,    62,   207,
      63,    64,   538,   676,   821,    65,    66,   261,    67,    68,
      69,    70,   208,   107,   108,   200,   201,   202,   572,   525,
     188,    72,   424,   234,   266,   666,   667,   235,   617,   243,
     244,   413,   618,   728,   608,   405,   267,   481,    73,   204,
     433,   628,   220,   718,   221,   719,   602,   843,   542,   539,
     769,   368,   370,   571,   783,   256,   380,   594,   706,   707,
     226,   652,   307,   476,   751,    75,    76,   353,   532,   767,
     531,   766,   392,   590,   840,   575,   700,   785,   789,    77,
      78,    79,    80,    81,    82,    83,   289,   461,    84,   291,
     285,   283,   454,   644,   643,   747,    85,   284,    86,    87,
     210,    89,   211,   212,   363,   541,   561,   562,   563,   564,
     565,   566,   567,   568,   569,   779,   688,   190,   369,   271,
     268,   239,   113,   546,   520,   373,   217,   252,   439,   381,
     219,    93
};

static const short yypact[] =
{
  -32768,  2226,  5380,  7848,  8145,  3749,  5039,-32768,  6719,  6719,
    3630,-32768,-32768,  7947,  5586,  5586,-32768,-32768,  5586,  4382,
    4485,-32768,-32768,-32768,-32768,  6719,  4923,   -34,-32768,   -12,
  -32768,-32768,  3867,  3970,-32768,-32768,  4073,-32768,-32768,-32768,
  -32768,-32768,  7543,  7543,    52,  3040,  6719,  6822,  7543,  8244,
    4807,-32768,-32768,-32768,    -9,     2,   226,  7646,  7543,-32768,
     329,   725,   430,-32768,-32768,    87,    42,-32768,    36,  8046,
  -32768,   110,  9349,    14,    41,    96,    62,-32768,-32768,   127,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,    29,-32768,
     160,   277,    19,-32768,   725,-32768,-32768,-32768,   129,   131,
     -34,   355,   383,  6719,   117,  3171,   415,-32768,    30,-32768,
     167,-32768,-32768,    19,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,   138,   157,
     333,   462,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,   473,   477,   478,-32768,   513,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
     523,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,  4807,
  -32768,-32768,   121,-32768,  2468,   215,   430,    63,   169,   346,
      43,   204,    73,    63,-32768,-32768,   329,   106,-32768,   166,
    6719,  6719,   275,-32768,-32768,   439,   322,   103,   115,  7543,
    7543,  7543,-32768,  9349,   285,-32768,-32768,   316,   324,-32768,
  -32768,-32768,  5272,-32768,  5689,  5586,-32768,-32768,-32768,   326,
  -32768,-32768,   320,   334,  3302,-32768,   459,   397,   319,  3040,
     348,   353,   357,   430,  7543,   -34,   390,   158,   224,-32768,
     321,   359,   224,-32768,   463,-32768,   512,   539,   571,-32768,
  -32768,-32768,-32768,   299,-32768,   423,   510,   650,   418,   532,
     425,   584,   465,   468,-32768,-32768,-32768,-32768,  3527,  6719,
    6719,  6719,  6719,  5380,  6719,  6719,-32768,-32768,  6925,-32768,
    3040,  8244,   426,  6925,  7543,  7543,  7543,  7543,  7543,  7543,
    7543,  7543,  7543,  7543,  7543,  7543,  7543,  7543,  7543,  7543,
    7543,  7543,  7543,  7543,  7543,  7543,  7543,  7543,  7543,  7543,
    8406,  6822,  8472,  8538,  8538,-32768,-32768,-32768,-32768,  7646,
    7646,-32768,   454,-32768,   320,   430,-32768,   576,-32768,-32768,
  -32768,   329,-32768,-32768,-32768,  8604,  6822,  8538,  2468,  6719,
     573,-32768,-32768,-32768,-32768,   554,   557,   100,-32768,-32768,
    2590,   563,  7543,  8670,  6822,  8736,  7543,  7543,  2834,   553,
    3424,  7028,   569,-32768,    11,    11,   119,  8802,  6822,  8868,
  -32768,   498,-32768,  7543,  5792,-32768,-32768,  5895,-32768,-32768,
     505,  5483,-32768,-32768,    87,   -34,   522,     3,   530,-32768,
  -32768,-32768,  5039,-32768,  7543,  3302,   537,  8670,  8736,  7543,
     534,-32768,   540,   -34,  9196,-32768,-32768,  7131,-32768,-32768,
    7543,-32768,  7543,-32768,-32768,-32768,   576,  8934,  6822,  9000,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,    35,-32768,-32768,   531,-32768,  7543,  7543,   725,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,    22,  7543,-32768,   542,
     544,-32768,   547,-32768,-32768,-32768,  8340,-32768,-32768,   397,
    1935,  1935,  1935,  1935,   870,   870,  9470,  9418,  1935,  1935,
    9401,  9401,   502,   502,  9332,   870,   870,   879,   879,   888,
      38,    38,   397,   397,   397,  2337,  4588,  2056,  4691,   131,
  -32768,   552,   401,-32768,   413,-32768,  4485,-32768,-32768,  1955,
    1955,    22,    22,-32768,  9349,-32768,  9349,-32768,-32768,   329,
  -32768,  6719,  2468,   467,   315,-32768,   131,   559,   131,   578,
      88,   574,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
     626,  2468,   329,-32768,   561,-32768,   565,   642,   580,   649,
  -32768,  5155,  5039,-32768,  7234,   692,-32768,   520,-32768,  2317,
    4176,  4279,   587,   273,   279,   692,   705,   709,  7543,   597,
      63,-32768,-32768,-32768,-32768,-32768,-32768,    46,    58,   601,
     145,   150,  6719,   635,-32768,-32768,  7543,   285,-32768,   604,
    7543,   285,-32768,-32768,  7543,  9248,    17,-32768,   607,-32768,
     609,   608,  5998,  8538,  8538,   612,-32768,-32768,  6719,  9349,
     619,-32768,  9349,   528,   616,-32768,  7543,-32768,   467,   315,
     620,    84,   330,  3302,   703,-32768,-32768,-32768,   397,   397,
  -32768,  7749,-32768,-32768,-32768,  7337,-32768,  7543,  7543,  7646,
    7543,-32768,   454,   447,  7646,  7646,-32768,-32768,   454,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,    22,-32768,   329,   737,
  -32768,-32768,   627,  7543,   -34,   741,-32768,   626,-32768,-32768,
     303,-32768,-32768,   163,-32768,-32768,-32768,-32768,   542,-32768,
     669,-32768,  2937,   748,-32768,  6719,   751,-32768,  7543,   337,
    7543,  7543,   759,-32768,-32768,-32768,  7440,  2712,  3424,  3424,
     153,    11,   498,  6101,-32768,   498,   498,  6204,   646,-32768,
    6307,-32768,-32768,    87,     3,   131,   131,-32768,    54,-32768,
  -32768,  9196,   581,   651,-32768,-32768,-32768,-32768,-32768,-32768,
     665,  3424,  7543,   648,  9349,  9349,-32768,  9349,  9349,-32768,
    7646,-32768,  9349,-32768,  9349,-32768,  3424,  3302,-32768,  2468,
  -32768,-32768,-32768,-32768,   652,-32768,-32768,   654,   580,-32768,
     574,-32768,   580,   573,  8343,    63,-32768,-32768,  3424,-32768,
  -32768,    63,-32768,  7543,-32768,  7543,   142,   765,   766,-32768,
  -32768,  7543,-32768,-32768,  7543,-32768,   656,   657,-32768,  7543,
     653,-32768,-32768,-32768,-32768,   774,-32768,-32768,  9349,   776,
     667,  3302,   781,-32768,   303,-32768,-32768,-32768,  2468,   738,
  -32768,   590,   539,   571,  2468,-32768,  2590,-32768,-32768,-32768,
  -32768,-32768,-32768,  3424,  9269,   498,  6410,-32768,  6513,-32768,
     498,-32768,-32768,-32768,-32768,   672,-32768,   580,   784,   576,
    9066,  6822,  9132,   557,   520,   786,-32768,-32768,  7543,   671,
    7543,-32768,-32768,-32768,-32768,    76,   315,   683,    94,   137,
  -32768,-32768,-32768,   498,  6616,-32768,   498,   581,-32768,  7543,
  -32768,   498,-32768,   811,   812,-32768
};

static const short yypgoto[] =
{
  -32768,-32768,  -307,   890,-32768,    28,-32768,-32768,   814,    65,
      25,-32768,  -551,-32768,-32768,    51,   -11,  -181,    69,   745,
  -32768,   -37,  1085,   -67,   813,     9,   -21,-32768,-32768,    47,
  -32768,   -14,-32768,  1352,  -299,   -13,  -472,    95,-32768,    12,
  -32768,-32768,-32768,-32768,    -5,   220,    33,  -294,    23,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,   187,  -207,  -379,   -48,  -536,
     168,  -491,-32768,-32768,-32768,  -234,-32768,   742,-32768,-32768,
  -32768,-32768,  -371,-32768,-32768,   -42,-32768,-32768,-32768,-32768,
  -32768,-32768,   746,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,   586,  -239,-32768,-32768,-32768,    -3,-32768,-32768,-32768,
     917,   815,  1185,  1055,-32768,-32768,    44,   266,   141,-32768,
    -666,   144,-32768,  -610,-32768,  -362,  -512,-32768,-32768,-32768,
       7,  -372,   500,  -280,-32768,-32768,   -43,   -85,    91,    10,
     773,   678
};


#define	YYLAST		9585


static const short yytable[] =
{
     233,   233,   223,   203,   233,   250,   388,   246,   570,   236,
     236,   417,   275,   236,   186,   354,   596,   297,   586,   488,
     218,   238,   238,   203,   781,   238,   109,   109,   255,   257,
      94,   361,   247,   233,   233,   612,   109,   358,   592,   703,
     674,   675,   521,   295,   296,   345,   456,   237,   237,   712,
     462,   237,   187,   187,   691,   272,   694,   670,   672,   282,
     519,   549,   526,   529,   530,   232,   232,   547,   612,   232,
     218,   -86,   109,   187,   213,   216,   378,   778,   430,   351,
     782,   270,   294,   -88,   623,   582,   246,   548,   345,   -86,
     304,   305,   109,   450,   650,  -325,   251,   187,   265,   599,
     351,   403,   314,   519,   352,   526,   258,   -85,   254,   -77,
     240,   759,  -430,   241,   262,   306,   593,   765,   364,   548,
     288,   390,   340,   391,   304,   305,  -430,   624,   -83,   482,
     651,   290,   -83,   251,   451,   452,  -325,   362,  -325,   346,
     -90,   214,   215,   727,   -89,   308,   -83,   245,   548,   640,
     -87,   337,   338,   339,   -86,   -75,   387,   702,   781,   391,
     214,   215,   309,   341,   645,   342,   -88,   356,   379,   548,
     -85,   357,   -78,   389,  -479,   -87,   -90,   343,   -84,   811,
     435,   -86,   346,   429,   -80,   768,  -480,   -77,    74,    74,
     110,   110,   -77,   214,   215,   209,   209,   209,   570,   -85,
     225,   209,   209,   -89,  -479,   209,   -86,   -86,   282,   -77,
     -77,   -83,   209,   313,   857,   233,   233,   295,   251,  -424,
     344,    51,   646,   -90,   -85,   -85,   218,   -89,   233,   -75,
     233,   233,    74,   209,   209,   679,   276,   236,  -423,   236,
     236,   -82,   -87,   349,   209,   -81,   187,   374,   365,   238,
     434,   238,   238,   -85,   685,   557,   276,   242,   -87,   245,
     838,   -84,  -424,   670,   672,   825,   826,   -87,   -87,   377,
     827,   -77,   382,   558,   483,   237,   -79,   237,   416,   -76,
     699,  -423,   292,   293,   437,   394,   395,   386,   438,   366,
     209,   367,    74,   232,   233,   232,   414,   393,   545,   486,
     489,   490,   491,   492,   493,   494,   495,   496,   497,   498,
     499,   500,   501,   502,   503,   504,   505,   506,   507,   508,
     509,   510,   511,   512,   513,   514,   468,   233,   262,   396,
     621,   473,   625,   478,   109,   534,   536,   410,   485,   412,
     415,   480,   799,   735,   736,   873,   480,   400,   634,   635,
     440,   612,   233,   780,   438,   -79,   710,   450,   612,   441,
     350,   443,   711,   445,   469,   470,   471,   472,   579,   403,
     233,   540,   534,   536,   533,   535,   -85,   233,   419,   262,
     -90,  -476,   -87,   717,   233,   420,   421,   518,   734,   233,
     233,    74,   265,   233,   556,   557,  -281,   615,   451,   452,
     453,   627,   429,   -82,   595,   595,   619,   209,   209,  -477,
     629,   609,   518,   558,  -425,   632,   559,   265,   620,   203,
     793,   570,   -89,   233,   589,   839,   233,   383,   233,   209,
     518,   209,   209,   -79,   233,   265,  -418,  -281,   -79,  -281,
     -84,    74,   404,  -480,   518,   -81,    74,   442,   423,   265,
     407,   438,   648,   649,   425,   -79,   -79,  -425,   408,   214,
     215,   314,   822,   233,  -421,   682,   304,   305,   384,   187,
     385,   359,   360,   431,   518,  -476,   612,  -418,   432,  -418,
     444,   450,   -63,  -476,   664,    74,   209,   209,   209,   209,
      74,   209,   209,  -483,   518,   209,   665,    74,   276,   265,
     209,    92,    92,  -477,   -85,  -421,   661,  -421,    92,    92,
      92,  -477,   612,   436,    92,    92,   -87,   446,    92,   459,
     397,   858,   451,   452,   455,    92,   463,   -77,   209,   466,
     760,   662,   467,   661,   705,   702,   209,   209,   668,   -79,
     427,   671,   673,  -426,   537,    92,    92,    92,  -483,   677,
     -84,   697,   484,   209,  -428,    74,   209,    92,  -427,  -418,
     233,   398,   877,   399,   573,   574,   314,    74,   450,   203,
     391,   209,   686,   -76,   233,    74,   578,    74,   834,   591,
     696,   384,   548,   428,   836,   209,  -426,  -483,   681,  -483,
     450,  -483,   233,   447,  -421,  -479,   233,  -428,   209,   774,
     233,  -427,  -418,    92,   371,    92,   678,   480,   233,   451,
     452,   457,    74,   335,   336,   337,   338,   339,   187,   187,
    -429,   604,   741,   551,   603,   552,   553,   554,   555,   609,
     613,   451,   452,   460,   448,   209,   449,  -421,   286,   287,
     223,   233,   464,   754,   755,   757,   758,   372,   622,   810,
     762,   764,  -274,   -64,   -72,   626,   812,  -282,   631,   633,
     647,  -429,  -283,  -429,   556,   557,   -72,   721,  -262,   233,
     655,   860,   656,   733,   109,   663,   551,   683,   552,   553,
     554,   555,   680,   558,   756,   465,   559,   687,   770,   761,
     763,   690,   692,  -274,   757,  -274,   762,   764,  -282,   695,
    -282,   560,   233,  -283,    92,  -283,   693,   702,   450,   233,
     709,   458,   861,   233,   862,   713,   233,   556,   557,   714,
      92,    92,   805,   716,   720,   269,   273,   230,   209,    74,
     723,   595,   729,   732,   807,   730,   558,   737,   233,   559,
     739,   740,    92,   742,    92,    92,   818,   771,    74,   451,
     452,   775,   772,   784,    92,   744,   745,   788,   746,    92,
     806,   792,    40,    41,   299,   300,   301,   302,   303,   794,
     791,   808,   813,   814,  -263,   841,   842,   823,   851,   818,
     824,   233,   846,   848,   852,   817,   853,   844,   854,   209,
     233,   856,   859,   872,   874,   233,   882,   884,    92,    92,
      92,    92,    92,    92,    92,    92,   887,   109,    92,   209,
      92,   894,   895,    92,   312,   209,   881,   114,   347,   750,
     189,   880,   206,   206,   206,   348,   684,   828,   776,   724,
      74,   777,   233,   298,   233,     0,     0,     0,   225,   248,
     731,    92,     0,     0,     0,     0,   209,   233,     0,    92,
      92,   209,   209,   869,   233,     0,   233,     0,     0,     0,
     263,     0,     0,     0,     0,     0,    92,     0,    92,    92,
     233,     0,     0,     0,     0,   233,     0,     0,     0,     0,
      92,     0,     0,     0,    92,     0,     0,     0,    92,    74,
      92,    59,   209,     0,     0,     0,     0,     0,    92,     0,
       0,     0,     0,     0,    74,    74,    74,   518,     0,     0,
       0,    92,   265,     0,     0,   406,   406,   355,    88,    88,
     111,   111,   111,   418,     0,    92,     0,     0,     0,     0,
     227,     0,     0,     0,   314,   260,     0,     0,    74,     0,
       0,     0,   800,   314,     0,   802,   803,   209,    92,   327,
     328,     0,   314,    74,    74,     0,    74,     0,   327,   328,
       0,     0,    88,     0,     0,     0,   277,   327,   328,     0,
       0,   831,     0,     0,     0,    74,     0,     0,   332,   333,
     334,   335,   336,   337,   338,   339,   277,     0,     0,   334,
     335,   336,   337,   338,   339,   260,     0,     0,     0,   335,
     336,   337,   338,   339,     0,     0,     0,     0,    74,     0,
       0,     0,     0,     0,     0,    74,     0,     0,     0,   269,
       0,    74,    88,    74,     0,     0,   847,   849,     0,     0,
      74,     0,     0,     0,   206,   206,     0,     0,     0,     0,
       0,    92,    92,     0,   269,     0,     0,     0,   209,     0,
       0,     0,     0,     0,   576,     0,    91,    91,   112,   112,
       0,    92,   269,     0,   866,   867,     0,     0,   228,     0,
     871,     0,     0,     0,     0,     0,   269,     0,     0,   406,
       0,     0,     0,     0,     0,     0,    71,    71,     0,   885,
       0,     0,     0,     0,   406,     0,     0,     0,   224,     0,
      91,     0,    92,   888,   278,     0,   890,     0,     0,     0,
       0,   892,     0,   206,   206,   206,   206,     0,   474,   475,
       0,    88,    92,     0,   278,     0,   269,     0,    92,     0,
      71,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    92,   426,     0,     0,     0,     0,   260,
       0,     0,     0,     0,   653,     0,     0,     0,     0,    92,
      91,     0,     0,     0,    92,    92,     0,     0,     0,     0,
       0,    88,     0,     0,     0,     0,    88,     0,     0,     0,
       0,     0,     0,   550,     0,     0,    90,    90,     0,     0,
      71,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     260,     0,    92,     0,   669,    92,     0,   669,   669,   653,
     653,     0,     0,     0,     0,    88,     0,    92,    92,    92,
      88,     0,     0,     0,     0,   263,   669,    88,   277,     0,
      90,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   689,     0,   689,     0,   689,     0,     0,     0,
       0,    92,   701,   704,     0,   704,     0,     0,     0,    91,
      92,     0,     0,   704,     0,     0,    92,    92,     0,    92,
     577,     0,     0,     0,     0,     0,     0,     0,   585,     0,
     587,     0,     0,     0,     0,    88,     0,   406,    92,    71,
      90,     0,     0,     0,     0,     0,     0,    88,   406,     0,
       0,     0,     0,     0,     0,    88,     0,    88,     0,    91,
       0,     0,     0,     0,    91,   630,     0,     0,     0,     0,
       0,    92,     0,     0,     0,     0,     0,     0,    92,     0,
       0,     0,     0,     0,    92,     0,    92,     0,     0,    71,
       0,     0,    88,    92,    71,     0,     0,     0,     0,     0,
       0,     0,     0,    91,   653,   206,     0,     0,    91,     0,
       0,    92,     0,     0,     0,    91,   278,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   786,     0,
       0,   790,     0,    71,     0,     0,     0,     0,    71,    90,
       0,     0,     0,     0,     0,    71,     0,     0,     0,     0,
     406,     0,     0,   406,   406,     0,     0,     0,     0,     0,
       0,     0,     0,   669,   669,     0,   206,     0,     0,     0,
       0,     0,     0,    91,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    91,     0,     0,     0,    90,
       0,     0,   738,    91,    90,    91,     0,     0,     0,     0,
       0,     0,     0,    71,     0,   689,   689,     0,     0,    88,
     689,     0,     0,     0,     0,    71,     0,     0,     0,     0,
       0,     0,     0,    71,   704,    71,     0,     0,    88,     0,
      91,     0,     0,    90,   406,   406,     0,     0,    90,     0,
       0,     0,     0,     0,     0,    90,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      71,     0,     0,     0,     0,     0,     0,     0,     0,   206,
       0,     0,   406,   406,     0,     0,     0,     0,   406,     0,
       0,     0,     0,   743,     0,   689,     0,     0,     0,   269,
       0,   576,   704,     0,     0,     0,     0,   406,     0,     0,
       0,     0,     0,    90,     0,     0,     0,     0,     0,     0,
      88,   406,     0,     0,   406,    90,     0,     0,   227,   406,
       0,     0,     0,    90,     0,    90,     0,     0,     0,     0,
       0,   401,   402,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   787,     0,     0,     0,     0,    91,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   796,   797,   798,
      90,     0,     0,     0,     0,     0,    91,     0,     0,    88,
       0,     0,     0,     0,     0,     0,     0,    71,     0,     0,
       0,     0,     0,     0,    88,    88,    88,     0,     0,     0,
       0,   815,     0,     0,     0,     0,    71,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   819,   820,     0,     0,
     479,     0,     0,     0,     0,   487,     0,     0,    88,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   835,     0,
       0,     0,     0,    88,    88,     0,    88,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    91,   748,
       0,   832,     0,     0,     0,    88,   228,     0,     0,     0,
       0,   855,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   863,     0,   864,    90,    71,     0,
       0,     0,     0,   865,     0,     0,   224,     0,    88,     0,
       0,     0,     0,   487,     0,    88,    90,     0,     0,     0,
       0,    88,     0,    88,     0,   605,   607,    91,     0,   611,
      88,     0,     0,   616,     0,     0,     0,     0,     0,     0,
       0,     0,    91,    91,    91,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    71,     0,   637,
       0,     0,   611,     0,   637,     0,     0,     0,     0,     0,
       0,     0,    71,    71,    71,     0,    91,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    91,    91,     0,    91,     0,     0,     0,    90,   654,
       0,     0,     0,     0,     0,     0,    71,     0,     0,   833,
       0,     0,     0,    91,     0,     0,     0,     0,     0,     0,
       0,    71,    71,     0,    71,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   830,
       0,     0,     0,    71,     0,     0,    91,     0,     0,     0,
       0,     0,     0,    91,     0,     0,     0,    90,     0,    91,
       0,    91,     0,     0,     0,     0,     0,     0,    91,     0,
       0,     0,    90,    90,    90,     0,    71,     0,     0,     0,
       0,     0,     0,    71,     0,     0,     0,     0,     0,    71,
       0,    71,     0,     0,     0,     0,   698,     0,    71,     0,
       0,     0,     0,     0,     0,     0,    90,     0,     0,     0,
     715,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    90,    90,     0,    90,  -499,     0,     0,   722,     0,
       0,     0,   725,  -499,  -499,  -499,   726,     0,  -499,  -499,
    -499,     0,  -499,    90,   607,     0,     0,     0,     0,     0,
       0,     0,  -499,     0,     0,     0,     0,     0,     0,     0,
       0,  -499,  -499,     0,  -499,  -499,  -499,  -499,  -499,   314,
  -32768,-32768,-32768,-32768,   319,   320,    90,   753,-32768,-32768,
       0,     0,     0,    90,   327,   328,     0,     0,     0,    90,
       0,    90,     0,     0,     0,     0,     0,     0,    90,     0,
       0,     0,     0,     0,     0,   773,  -499,     0,     0,     0,
       0,   330,   331,   332,   333,   334,   335,   336,   337,   338,
     339,     0,     0,     0,     0,     0,  -281,     0,     0,     0,
    -499,     0,     0,     0,  -281,  -281,  -281,     0,   637,     0,
    -281,  -281,     0,  -281,     0,   611,  -499,     0,     0,  -499,
    -499,     0,   611,   245,     0,  -499,  -499,     0,     0,     0,
       0,     0,  -281,  -281,     0,  -281,  -281,  -281,  -281,  -281,
       0,     0,     0,     0,   816,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    -281,  -281,  -281,  -281,  -281,  -281,  -281,  -281,  -281,  -281,
    -281,  -281,  -281,     0,     0,  -281,  -281,  -281,     0,   660,
       0,     0,     0,     0,     0,     0,     0,   837,     0,     0,
       0,     0,     0,     0,     0,     0,   845,     0,     0,   -88,
    -281,   850,  -281,  -281,  -281,  -281,  -281,  -281,  -281,  -281,
    -281,  -281,     0,     0,     0,     0,     0,  -281,  -281,     0,
    -281,  -281,   -80,     0,     0,     0,  -281,  -281,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   607,     0,
     611,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     883,     0,   886,     0,     0,     0,  -499,     2,     0,     3,
       4,     5,     6,     7,     0,     0,   611,     8,     9,     0,
       0,   891,    10,     0,    11,    12,    13,    14,    15,    16,
      17,     0,     0,     0,     0,    18,    19,    20,    21,    22,
      23,    24,     0,     0,    25,     0,     0,     0,     0,     0,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,     0,    40,    41,     0,    42,    43,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    44,     0,
       0,    45,    46,     0,    47,    48,     0,    49,     0,    50,
      51,    52,    53,    54,    55,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  -483,     0,     0,
       0,     0,    56,    57,    58,  -483,  -483,  -483,     0,     0,
       0,  -483,  -483,     0,  -483,     0,  -499,  -499,     0,     0,
     657,     0,     0,  -483,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  -483,  -483,     0,  -483,  -483,  -483,  -483,
    -483,   314,   315,   316,   317,   318,   319,   320,   321,   322,
     323,   324,   325,   326,     0,     0,   327,   328,     0,     0,
       0,  -483,  -483,  -483,  -483,  -483,  -483,  -483,  -483,  -483,
    -483,  -483,  -483,  -483,     0,     0,  -483,  -483,  -483,     0,
     659,   329,     0,   330,   331,   332,   333,   334,   335,   336,
     337,   338,   339,     0,     0,     0,     0,     0,     0,     0,
     -86,  -483,     0,  -483,  -483,  -483,  -483,  -483,  -483,  -483,
    -483,  -483,  -483,     0,     0,     0,     0,  -483,  -483,  -483,
       0,  -483,  -483,   -78,     0,     0,     0,  -483,  -483,     2,
       0,     3,     4,     5,     6,     7,  -499,  -499,  -499,     8,
       9,     0,     0,  -499,    10,     0,    11,    12,    13,    14,
      15,    16,    17,     0,     0,     0,     0,    18,    19,    20,
      21,    22,    23,    24,     0,     0,    25,     0,     0,     0,
       0,     0,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,     0,    40,    41,     0,
      42,    43,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      44,     0,     0,    45,    46,     0,    47,    48,     0,    49,
       0,    50,    51,    52,    53,    54,    55,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    56,    57,    58,     0,     0,     0,
       0,     2,     0,     3,     4,     5,     6,     7,  -499,  -499,
    -499,     8,     9,     0,  -499,  -499,    10,     0,    11,    12,
      13,    14,    15,    16,    17,     0,     0,     0,     0,    18,
      19,    20,    21,    22,    23,    24,     0,     0,    25,     0,
       0,     0,     0,     0,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,     0,    40,
      41,     0,    42,    43,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    44,     0,     0,    45,    46,     0,    47,    48,
       0,    49,     0,    50,    51,    52,    53,    54,    55,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    56,    57,    58,     0,
       0,     0,     0,     2,     0,     3,     4,     5,     6,     7,
    -499,  -499,  -499,     8,     9,     0,     0,  -499,    10,  -499,
      11,    12,    13,    14,    15,    16,    17,     0,     0,     0,
       0,    18,    19,    20,    21,    22,    23,    24,     0,     0,
      25,     0,     0,     0,     0,     0,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
       0,    40,    41,     0,    42,    43,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    44,     0,     0,    45,    46,     0,
      47,    48,     0,    49,     0,    50,    51,    52,    53,    54,
      55,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    56,    57,
      58,     0,     0,     0,     0,     2,     0,     3,     4,     5,
       6,     7,  -499,  -499,  -499,     8,     9,     0,     0,  -499,
      10,     0,    11,    12,    13,    14,    15,    16,    17,     0,
       0,     0,     0,    18,    19,    20,    21,    22,    23,    24,
       0,     0,    25,     0,     0,     0,     0,     0,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,     0,    40,    41,     0,    42,    43,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    44,     0,     0,    45,
      46,     0,    47,    48,     0,    49,     0,    50,    51,    52,
      53,    54,    55,     0,     0,     0,     0,     0,     2,     0,
       3,     4,     5,     6,     7,     0,  -499,  -499,     8,     9,
      56,    57,    58,    10,     0,    11,    12,    13,    14,    15,
      16,    17,     0,     0,  -499,  -499,    18,    19,    20,    21,
      22,    23,    24,     0,     0,    25,     0,     0,     0,     0,
       0,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,     0,    40,    41,     0,    42,
      43,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    44,
       0,     0,    45,    46,     0,    47,    48,     0,    49,     0,
      50,    51,    52,    53,    54,    55,     0,     0,     0,     0,
       0,     2,     0,     3,     4,     5,     6,     7,     0,     0,
       0,     8,     9,    56,    57,    58,    10,     0,    11,    12,
      13,    14,    15,    16,    17,     0,     0,  -499,  -499,    18,
      19,    20,    21,    22,    23,    24,     0,     0,    25,     0,
       0,     0,     0,     0,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,     0,    40,
      41,     0,    42,    43,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    44,     0,     0,   259,    46,     0,    47,    48,
       0,    49,     0,    50,    51,    52,    53,    54,    55,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    56,    57,    58,     0,
       0,     0,     0,     0,     0,  -499,     0,     0,     0,     0,
    -499,  -499,     2,     0,     3,     4,     5,     6,     7,     0,
       0,     0,     8,     9,     0,     0,     0,    10,     0,    11,
      12,    13,    14,    15,    16,    17,     0,     0,     0,     0,
      18,    19,    20,    21,    22,    23,    24,     0,     0,    25,
       0,     0,     0,     0,     0,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,     0,
      40,    41,     0,    42,    43,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    44,     0,     0,    45,    46,     0,    47,
      48,     0,    49,     0,    50,    51,    52,    53,    54,    55,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    56,    57,    58,
       0,     0,     0,     0,     0,     0,  -499,     0,     0,     0,
       0,  -499,  -499,     2,     0,     3,     4,     5,     6,     7,
       0,     0,     0,     8,     9,     0,     0,     0,    10,     0,
      11,    12,    13,    14,    15,    16,    17,     0,     0,     0,
       0,    18,    19,    20,    21,    22,    23,    24,     0,     0,
      25,     0,     0,     0,     0,     0,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
       0,    40,    41,     0,    42,    43,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    44,     0,     0,    45,    46,     0,
      47,    48,     0,    49,     0,    50,    51,    52,    53,    54,
      55,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    56,    57,
      58,     0,     0,  -499,     0,     2,     0,     3,     4,     5,
       6,     7,  -499,  -499,  -499,     8,     9,     0,     0,     0,
      10,     0,    11,    12,    13,    14,    15,    16,    17,     0,
       0,     0,     0,    18,    19,    20,    21,    22,    23,    24,
       0,     0,    25,     0,     0,     0,     0,     0,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,     0,    40,    41,     0,    42,    43,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    44,     0,     0,    45,
      46,     0,    47,    48,     0,    49,     0,    50,    51,    52,
      53,    54,    55,     0,     0,     0,     0,     0,     0,     0,
       3,     4,     5,     6,     7,     0,     0,     0,     8,     9,
      56,    57,    58,    10,     0,    11,    12,    13,    14,    15,
      16,    17,     0,     0,  -499,  -499,    18,    19,    20,    21,
      22,    23,    24,     0,     0,    25,     0,     0,     0,     0,
       0,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,     0,    40,    41,     0,    42,
      43,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    44,
       0,     0,    45,    46,     0,    47,    48,     0,    49,     0,
      50,    51,    52,    53,    54,    55,     0,     0,     0,     0,
       0,     0,     0,     3,     4,     5,     0,     7,     0,     0,
       0,     8,     9,    56,    57,    58,    10,     0,    11,    12,
      13,    14,    15,    16,    17,     0,     0,     0,   393,    18,
      19,    20,    21,    22,    23,    24,     0,     0,    25,     0,
       0,     0,     0,     0,     0,    27,     0,     0,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,     0,    40,
      41,     0,    42,    43,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   205,     0,     0,   105,    46,     0,    47,    48,
       0,     0,     0,    50,    51,    52,    53,    54,    55,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    56,    57,    58,     0,
       0,     0,   115,   116,   117,   118,   119,   120,   121,   122,
     214,   215,   123,   124,   125,   126,   127,     0,     0,   128,
     129,   130,   131,   132,   133,   134,     0,     0,   135,   136,
     137,   138,   139,   140,   141,   142,   143,   144,   145,   146,
     147,   148,   149,   150,   151,   152,   153,   154,   155,   156,
     157,    34,    35,   158,    37,     0,     0,     0,     0,     0,
       0,   159,   160,   161,   162,   163,   164,     0,   165,   166,
       0,     0,   167,     0,     0,     0,   168,   169,   170,   171,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     172,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   173,   174,   175,   176,   177,
     178,   179,   180,   181,   182,     0,     0,   183,     0,     0,
    -476,  -476,  -476,     0,  -476,     0,   184,   185,  -476,  -476,
       0,     0,     0,  -476,     0,  -476,  -476,  -476,  -476,  -476,
    -476,  -476,     0,  -476,     0,     0,  -476,  -476,  -476,  -476,
    -476,  -476,  -476,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  -476,     0,     0,  -476,  -476,  -476,  -476,  -476,
    -476,  -476,  -476,  -476,  -476,     0,  -476,  -476,     0,  -476,
    -476,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  -476,
       0,     0,  -476,  -476,     0,  -476,  -476,     0,  -476,  -476,
    -476,  -476,  -476,  -476,  -476,  -476,     0,     0,     0,     0,
       0,     0,     0,  -478,  -478,  -478,     0,  -478,     0,     0,
       0,  -478,  -478,  -476,  -476,  -476,  -478,  -476,  -478,  -478,
    -478,  -478,  -478,  -478,  -478,  -476,  -478,     0,     0,  -478,
    -478,  -478,  -478,  -478,  -478,  -478,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  -478,     0,     0,  -478,  -478,
    -478,  -478,  -478,  -478,  -478,  -478,  -478,  -478,     0,  -478,
    -478,     0,  -478,  -478,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  -478,     0,     0,  -478,  -478,     0,  -478,  -478,
       0,  -478,  -478,  -478,  -478,  -478,  -478,  -478,  -478,     0,
       0,     0,     0,     0,     0,     0,  -477,  -477,  -477,     0,
    -477,     0,     0,     0,  -477,  -477,  -478,  -478,  -478,  -477,
    -478,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -478,  -477,
       0,     0,  -477,  -477,  -477,  -477,  -477,  -477,  -477,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  -477,     0,
       0,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,  -477,
    -477,     0,  -477,  -477,     0,  -477,  -477,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  -477,     0,     0,  -477,  -477,
       0,  -477,  -477,     0,  -477,  -477,  -477,  -477,  -477,  -477,
    -477,  -477,     0,     0,     0,     0,     0,     0,     0,  -479,
    -479,  -479,     0,  -479,     0,     0,     0,  -479,  -479,  -477,
    -477,  -477,  -479,  -477,  -479,  -479,  -479,  -479,  -479,  -479,
    -479,  -477,     0,     0,     0,  -479,  -479,  -479,  -479,  -479,
    -479,  -479,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  -479,     0,     0,  -479,  -479,  -479,  -479,  -479,  -479,
    -479,  -479,  -479,  -479,     0,  -479,  -479,     0,  -479,  -479,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  -479,   708,
       0,  -479,  -479,     0,  -479,  -479,     0,  -479,  -479,  -479,
    -479,  -479,  -479,  -479,  -479,     0,     0,     0,     0,   -86,
       0,     0,  -480,  -480,  -480,     0,  -480,     0,     0,     0,
    -480,  -480,  -479,  -479,  -479,  -480,     0,  -480,  -480,  -480,
    -480,  -480,  -480,  -480,  -479,     0,     0,     0,  -480,  -480,
    -480,  -480,  -480,  -480,  -480,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  -480,     0,     0,  -480,  -480,  -480,
    -480,  -480,  -480,  -480,  -480,  -480,  -480,     0,  -480,  -480,
       0,  -480,  -480,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  -480,   660,     0,  -480,  -480,     0,  -480,  -480,     0,
    -480,  -480,  -480,  -480,  -480,  -480,  -480,  -480,     0,     0,
       0,     0,   -88,     0,     0,  -252,  -252,  -252,     0,  -252,
       0,     0,     0,  -252,  -252,  -480,  -480,  -480,  -252,     0,
    -252,  -252,  -252,  -252,  -252,  -252,  -252,  -480,     0,     0,
       0,  -252,  -252,  -252,  -252,  -252,  -252,  -252,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  -252,     0,     0,
    -252,  -252,  -252,  -252,  -252,  -252,  -252,  -252,  -252,  -252,
       0,  -252,  -252,     0,  -252,  -252,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  -252,     0,     0,  -252,  -252,     0,
    -252,  -252,     0,  -252,  -252,  -252,  -252,  -252,  -252,  -252,
    -252,     0,     0,     0,     0,     0,     0,     0,  -252,  -252,
    -252,     0,  -252,     0,     0,     0,  -252,  -252,  -252,  -252,
    -252,  -252,     0,  -252,  -252,  -252,  -252,  -252,  -252,  -252,
     242,     0,     0,     0,  -252,  -252,  -252,  -252,  -252,  -252,
    -252,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    -252,     0,     0,  -252,  -252,  -252,  -252,  -252,  -252,  -252,
    -252,  -252,  -252,     0,  -252,  -252,     0,  -252,  -252,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  -252,     0,     0,
    -252,  -252,     0,  -252,  -252,     0,  -252,  -252,  -252,  -252,
    -252,  -252,  -252,  -252,     0,     0,     0,     0,     0,     0,
       0,  -481,  -481,  -481,     0,  -481,     0,     0,     0,  -481,
    -481,  -252,  -252,  -252,  -481,     0,  -481,  -481,  -481,  -481,
    -481,  -481,  -481,   245,     0,     0,     0,  -481,  -481,  -481,
    -481,  -481,  -481,  -481,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  -481,     0,     0,  -481,  -481,  -481,  -481,
    -481,  -481,  -481,  -481,  -481,  -481,     0,  -481,  -481,     0,
    -481,  -481,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    -481,     0,     0,  -481,  -481,     0,  -481,  -481,     0,  -481,
    -481,  -481,  -481,  -481,  -481,  -481,  -481,     0,     0,     0,
       0,     0,     0,     0,  -482,  -482,  -482,     0,  -482,     0,
       0,     0,  -482,  -482,  -481,  -481,  -481,  -482,     0,  -482,
    -482,  -482,  -482,  -482,  -482,  -482,  -481,     0,     0,     0,
    -482,  -482,  -482,  -482,  -482,  -482,  -482,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  -482,     0,     0,  -482,
    -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,     0,
    -482,  -482,     0,  -482,  -482,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  -482,     0,     0,  -482,  -482,     0,  -482,
    -482,     0,  -482,  -482,  -482,  -482,  -482,  -482,  -482,  -482,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  -482,  -482,  -482,
     115,   116,   117,   118,   119,   120,   121,   122,     0,  -482,
     123,   124,   125,   126,   127,     0,     0,   128,   129,   130,
     131,   132,   133,   134,     0,     0,   135,   136,   137,   191,
     192,   193,   194,   142,   143,   144,   145,   146,   147,   148,
     149,   150,   151,   152,   153,   195,   196,   197,   157,   279,
     280,   198,   281,     0,     0,     0,     0,     0,     0,   159,
     160,   161,   162,   163,   164,     0,   165,   166,     0,     0,
     167,     0,     0,     0,   168,   169,   170,   171,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   172,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   173,   174,   175,   176,   177,   178,   179,
     180,   181,   182,     0,     0,   183,   115,   116,   117,   118,
     119,   120,   121,   122,   184,     0,   123,   124,   125,   126,
     127,     0,     0,   128,   129,   130,   131,   132,   133,   134,
       0,     0,   135,   136,   137,   191,   192,   193,   194,   142,
     143,   144,   145,   146,   147,   148,   149,   150,   151,   152,
     153,   195,   196,   197,   157,   249,     0,   198,     0,     0,
       0,     0,     0,     0,     0,   159,   160,   161,   162,   163,
     164,     0,   165,   166,     0,     0,   167,     0,     0,     0,
     168,   169,   170,   171,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   172,     0,   199,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   173,
     174,   175,   176,   177,   178,   179,   180,   181,   182,     0,
       0,   183,   115,   116,   117,   118,   119,   120,   121,   122,
     184,     0,   123,   124,   125,   126,   127,     0,     0,   128,
     129,   130,   131,   132,   133,   134,     0,     0,   135,   136,
     137,   191,   192,   193,   194,   142,   143,   144,   145,   146,
     147,   148,   149,   150,   151,   152,   153,   195,   196,   197,
     157,     0,     0,   198,     0,     0,     0,     0,     0,     0,
       0,   159,   160,   161,   162,   163,   164,     0,   165,   166,
       0,     0,   167,     0,     0,     0,   168,   169,   170,   171,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     172,     0,   199,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   173,   174,   175,   176,   177,
     178,   179,   180,   181,   182,     0,     0,   183,   115,   116,
     117,   118,   119,   120,   121,   122,   184,     0,   123,   124,
     125,   126,   127,     0,     0,   128,   129,   130,   131,   132,
     133,   134,     0,     0,   135,   136,   137,   191,   192,   193,
     194,   142,   143,   144,   145,   146,   147,   148,   149,   150,
     151,   152,   153,   195,   196,   197,   157,     0,     0,   198,
       0,     0,     0,     0,     0,     0,     0,   159,   160,   161,
     162,   163,   164,     0,   165,   166,     0,     0,   167,     0,
       0,     0,   168,   169,   170,   171,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   172,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     182,     0,     0,   183,     0,     3,     4,     5,     0,     7,
       0,     0,   184,     8,     9,     0,     0,     0,    10,     0,
      11,    12,    13,    95,    96,    16,    17,     0,     0,     0,
       0,    97,    19,    20,    21,    22,    23,    24,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    27,     0,     0,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
       0,    40,    41,     0,    42,    43,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   205,     0,     0,   105,    46,     0,
      47,    48,     0,   229,   230,    50,    51,    52,    53,    54,
      55,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     3,     4,     5,     6,     7,    56,   231,
      58,     8,     9,     0,     0,     0,    10,   409,    11,    12,
      13,    14,    15,    16,    17,     0,     0,     0,     0,    18,
      19,    20,    21,    22,    23,    24,     0,     0,    25,     0,
       0,     0,     0,     0,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,     0,    40,
      41,     0,    42,    43,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    44,     0,     0,    45,    46,     0,    47,    48,
       0,    49,     0,    50,    51,    52,    53,    54,    55,     0,
       0,     0,     0,     0,     0,     0,     3,     4,     5,     0,
       7,     0,     0,     0,     8,     9,    56,    57,    58,    10,
       0,    11,    12,    13,    14,    15,    16,    17,     0,     0,
       0,     0,    18,    19,    20,    21,    22,    23,    24,     0,
       0,    25,     0,     0,     0,     0,     0,     0,    27,     0,
       0,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,     0,    40,    41,     0,    42,    43,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   205,     0,     0,   105,    46,
       0,    47,    48,     0,   614,   230,    50,    51,    52,    53,
      54,    55,     0,     0,     0,     0,     0,     0,     0,     3,
       4,     5,     0,     7,     0,     0,     0,     8,     9,    56,
      57,    58,    10,     0,    11,    12,    13,    95,    96,    16,
      17,     0,     0,     0,     0,    97,    19,    20,    21,    22,
      23,    24,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    27,     0,     0,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,     0,    40,    41,     0,    42,    43,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   205,     0,
       0,   105,    46,     0,    47,    48,     0,   229,   230,    50,
      51,    52,    53,    54,    55,     0,     0,     0,     0,     0,
       0,     0,     3,     4,     5,     0,     7,     0,     0,     0,
       8,     9,    56,   231,    58,    10,     0,    11,    12,    13,
      95,    96,    16,    17,     0,     0,     0,     0,    97,    19,
      20,    21,    22,    23,    24,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    27,     0,     0,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,     0,    40,    41,
       0,    42,    43,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   205,     0,     0,   105,   411,     0,    47,    48,     0,
     229,   230,    50,    51,    52,    53,    54,    55,     0,     0,
       0,     0,     0,     0,     0,     3,     4,     5,     0,     7,
       0,     0,     0,     8,     9,    56,   231,    58,    10,     0,
      11,    12,    13,    95,    96,    16,    17,     0,     0,     0,
       0,    97,    98,    99,    21,    22,    23,    24,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    27,     0,     0,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
       0,    40,    41,     0,    42,    43,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   205,     0,     0,   105,    46,     0,
      47,    48,     0,   606,   230,    50,    51,    52,    53,    54,
      55,     0,     0,     0,     0,     0,     0,     0,     3,     4,
       5,     0,     7,     0,     0,     0,     8,     9,    56,   231,
      58,    10,     0,    11,    12,    13,    95,    96,    16,    17,
       0,     0,     0,     0,    97,    98,    99,    21,    22,    23,
      24,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      27,     0,     0,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,     0,    40,    41,     0,    42,    43,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   205,     0,     0,
     105,    46,     0,    47,    48,     0,   610,   230,    50,    51,
      52,    53,    54,    55,     0,     0,     0,     0,     0,     0,
       0,     3,     4,     5,     0,     7,     0,     0,     0,     8,
       9,    56,   231,    58,    10,     0,    11,    12,    13,    95,
      96,    16,    17,     0,     0,     0,     0,    97,    19,    20,
      21,    22,    23,    24,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    27,     0,     0,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,     0,    40,    41,     0,
      42,    43,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     205,     0,     0,   105,    46,     0,    47,    48,     0,   606,
     230,    50,    51,    52,    53,    54,    55,     0,     0,     0,
       0,     0,     0,     0,     3,     4,     5,     0,     7,     0,
       0,     0,     8,     9,    56,   231,    58,    10,     0,    11,
      12,    13,    95,    96,    16,    17,     0,     0,     0,     0,
      97,    98,    99,    21,    22,    23,    24,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    27,     0,     0,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,     0,
      40,    41,     0,    42,    43,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   205,     0,     0,   105,    46,     0,    47,
      48,     0,   801,   230,    50,    51,    52,    53,    54,    55,
       0,     0,     0,     0,     0,     0,     0,     3,     4,     5,
       0,     7,     0,     0,     0,     8,     9,    56,   231,    58,
      10,     0,    11,    12,    13,    95,    96,    16,    17,     0,
       0,     0,     0,    97,    98,    99,    21,    22,    23,    24,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    27,
       0,     0,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,     0,    40,    41,     0,    42,    43,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   205,     0,     0,   105,
      46,     0,    47,    48,     0,   804,   230,    50,    51,    52,
      53,    54,    55,     0,     0,     0,     0,     0,     0,     0,
       3,     4,     5,     0,     7,     0,     0,     0,     8,     9,
      56,   231,    58,    10,     0,    11,    12,    13,    95,    96,
      16,    17,     0,     0,     0,     0,    97,    98,    99,    21,
      22,    23,    24,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    27,     0,     0,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,     0,    40,    41,     0,    42,
      43,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   205,
       0,     0,   105,    46,     0,    47,    48,     0,   809,   230,
      50,    51,    52,    53,    54,    55,     0,     0,     0,     0,
       0,     0,     0,     3,     4,     5,     0,     7,     0,     0,
       0,     8,     9,    56,   231,    58,    10,     0,    11,    12,
      13,    95,    96,    16,    17,     0,     0,     0,     0,    97,
      98,    99,    21,    22,    23,    24,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    27,     0,     0,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,     0,    40,
      41,     0,    42,    43,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   205,     0,     0,   105,    46,     0,    47,    48,
       0,   868,   230,    50,    51,    52,    53,    54,    55,     0,
       0,     0,     0,     0,     0,     0,     3,     4,     5,     0,
       7,     0,     0,     0,     8,     9,    56,   231,    58,    10,
       0,    11,    12,    13,    95,    96,    16,    17,     0,     0,
       0,     0,    97,    98,    99,    21,    22,    23,    24,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    27,     0,
       0,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,     0,    40,    41,     0,    42,    43,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   205,     0,     0,   105,    46,
       0,    47,    48,     0,   870,   230,    50,    51,    52,    53,
      54,    55,     0,     0,     0,     0,     0,     0,     0,     3,
       4,     5,     0,     7,     0,     0,     0,     8,     9,    56,
     231,    58,    10,     0,    11,    12,    13,    95,    96,    16,
      17,     0,     0,     0,     0,    97,    98,    99,    21,    22,
      23,    24,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    27,     0,     0,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,     0,    40,    41,     0,    42,    43,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   205,     0,
       0,   105,    46,     0,    47,    48,     0,   889,   230,    50,
      51,    52,    53,    54,    55,     0,     0,     0,     0,     0,
       0,     0,     3,     4,     5,     0,     7,     0,     0,     0,
       8,     9,    56,   231,    58,    10,     0,    11,    12,    13,
      14,    15,    16,    17,     0,     0,     0,     0,    18,    19,
      20,    21,    22,    23,    24,     0,     0,    25,     0,     0,
       0,     0,     0,     0,    27,     0,     0,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,     0,    40,    41,
       0,    42,    43,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   205,     0,     0,   105,    46,     0,    47,    48,     0,
       0,     0,    50,    51,    52,    53,    54,    55,     0,     0,
       0,     0,     0,     0,     0,     3,     4,     5,     0,     7,
       0,     0,     0,     8,     9,    56,    57,    58,    10,     0,
      11,    12,    13,    95,    96,    16,    17,     0,     0,     0,
       0,    97,    19,    20,    21,    22,    23,    24,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    27,     0,     0,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
       0,    40,    41,     0,    42,    43,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   205,     0,     0,   105,    46,     0,
      47,    48,     0,   264,     0,    50,    51,    52,    53,    54,
      55,     0,     0,     0,     0,     0,     0,     0,     3,     4,
       5,     0,     7,     0,     0,     0,     8,     9,    56,   231,
      58,    10,     0,    11,    12,    13,    14,    15,    16,    17,
       0,     0,     0,     0,    18,    19,    20,    21,    22,    23,
      24,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      27,     0,     0,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,     0,    40,    41,     0,    42,    43,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   205,     0,     0,
     105,    46,     0,    47,    48,     0,   477,     0,    50,    51,
      52,    53,    54,    55,     0,     0,     0,     0,     0,     0,
       0,     3,     4,     5,     0,     7,     0,     0,     0,     8,
       9,    56,   231,    58,    10,     0,    11,    12,    13,    95,
      96,    16,    17,     0,     0,     0,     0,    97,    98,    99,
      21,    22,    23,    24,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    27,     0,     0,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,     0,    40,    41,     0,
      42,    43,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     205,     0,     0,   105,    46,     0,    47,    48,     0,   588,
       0,    50,    51,    52,    53,    54,    55,     0,     0,     0,
       0,     0,     0,     0,     3,     4,     5,     0,     7,     0,
       0,     0,     8,     9,    56,   231,    58,    10,     0,    11,
      12,    13,    95,    96,    16,    17,     0,     0,     0,     0,
      97,    98,    99,    21,    22,    23,    24,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    27,     0,     0,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,     0,
      40,    41,     0,    42,    43,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   205,     0,     0,   105,    46,     0,    47,
      48,     0,   636,     0,    50,    51,    52,    53,    54,    55,
       0,     0,     0,     0,     0,     0,     0,     3,     4,     5,
       0,     7,     0,     0,     0,     8,     9,    56,   231,    58,
      10,     0,    11,    12,    13,    95,    96,    16,    17,     0,
       0,     0,     0,    97,    98,    99,    21,    22,    23,    24,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    27,
       0,     0,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,     0,    40,    41,     0,    42,    43,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   205,     0,     0,   105,
      46,     0,    47,    48,     0,   477,     0,    50,    51,    52,
      53,    54,    55,     0,     0,     0,     0,     0,     0,     0,
       3,     4,     5,     0,     7,     0,     0,     0,     8,     9,
      56,   231,    58,    10,     0,    11,    12,    13,    95,    96,
      16,    17,     0,     0,     0,     0,    97,    98,    99,    21,
      22,    23,    24,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    27,     0,     0,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,     0,    40,    41,     0,    42,
      43,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   205,
       0,     0,   105,    46,     0,    47,    48,     0,   752,     0,
      50,    51,    52,    53,    54,    55,     0,     0,     0,     0,
       0,     0,     0,     3,     4,     5,     0,     7,     0,     0,
       0,     8,     9,    56,   231,    58,    10,     0,    11,    12,
      13,    95,    96,    16,    17,     0,     0,     0,     0,    97,
      98,    99,    21,    22,    23,    24,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    27,     0,     0,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,     0,    40,
      41,     0,    42,    43,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   205,     0,     0,   105,    46,     0,    47,    48,
       0,   795,     0,    50,    51,    52,    53,    54,    55,     0,
       0,     0,     0,     0,     0,     0,     3,     4,     5,     0,
       7,     0,     0,     0,     8,     9,    56,   231,    58,    10,
       0,    11,    12,    13,    95,    96,    16,    17,     0,     0,
       0,     0,    97,    98,    99,    21,    22,    23,    24,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    27,     0,
       0,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,     0,    40,    41,     0,    42,    43,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   205,     0,     0,   105,    46,
       0,    47,    48,     0,     0,     0,    50,    51,    52,    53,
      54,    55,     0,     0,     0,     0,     0,     0,     0,     3,
       4,     5,     0,     7,     0,     0,     0,     8,     9,    56,
     231,    58,    10,     0,    11,    12,    13,    14,    15,    16,
      17,     0,     0,     0,     0,    18,    19,    20,    21,    22,
      23,    24,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    27,     0,     0,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,     0,    40,    41,     0,    42,    43,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   205,     0,
       0,   105,    46,     0,    47,    48,     0,     0,     0,    50,
      51,    52,    53,    54,    55,     0,     0,     0,     0,     0,
       0,     0,     3,     4,     5,     0,     7,     0,     0,     0,
       8,     9,    56,   231,    58,    10,     0,    11,    12,    13,
      95,    96,    16,    17,     0,     0,     0,     0,    97,    98,
      99,    21,    22,    23,    24,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   100,     0,     0,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,     0,    40,    41,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   222,     0,     0,    45,    46,     0,    47,    48,     0,
      49,     0,    50,    51,    52,    53,    54,    55,     0,     0,
       0,     3,     4,     5,     0,     7,     0,   749,     0,     8,
       9,     0,     0,     0,    10,   106,    11,    12,    13,    95,
      96,    16,    17,     0,     0,     0,     0,    97,    98,    99,
      21,    22,    23,    24,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   100,     0,     0,    30,    31,   101,    33,
      34,    35,   102,    37,    38,    39,     0,    40,    41,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   103,     0,     0,
     104,     0,     0,   105,    46,     0,    47,    48,     0,     0,
       0,    50,    51,    52,    53,    54,    55,     0,     0,     0,
       3,     4,     5,     0,     7,     0,     0,     0,     8,     9,
       0,     0,     0,    10,   106,    11,    12,    13,    95,    96,
      16,    17,     0,     0,     0,     0,    97,    98,    99,    21,
      22,    23,    24,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   100,     0,     0,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,     0,    40,    41,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   222,
       0,     0,    45,    46,     0,    47,    48,     0,    49,     0,
      50,    51,    52,    53,    54,    55,     0,     0,     0,     3,
       4,     5,     0,     7,     0,     0,     0,     8,     9,     0,
       0,     0,    10,   106,    11,    12,    13,    95,    96,    16,
      17,     0,     0,     0,     0,    97,    98,    99,    21,    22,
      23,    24,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   100,     0,     0,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,     0,    40,    41,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   274,     0,
       0,   310,    46,     0,    47,    48,     0,   311,     0,    50,
      51,    52,    53,    54,    55,     0,     0,     0,     3,     4,
       5,     0,     7,     0,     0,     0,     8,     9,     0,     0,
       0,    10,   106,    11,    12,    13,    95,    96,    16,    17,
       0,     0,     0,     0,    97,    98,    99,    21,    22,    23,
      24,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     100,     0,     0,    30,    31,   101,    33,    34,    35,   102,
      37,    38,    39,     0,    40,    41,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   104,     0,     0,
     105,    46,     0,    47,    48,     0,     0,     0,    50,    51,
      52,    53,    54,    55,     0,     0,     0,     3,     4,     5,
       0,     7,     0,     0,     0,     8,     9,     0,     0,     0,
      10,   106,    11,    12,    13,    95,    96,    16,    17,     0,
       0,     0,     0,    97,    98,    99,    21,    22,    23,    24,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   100,
       0,     0,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,     0,    40,    41,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   274,     0,     0,   105,
      46,     0,    47,    48,     0,     0,     0,    50,    51,    52,
      53,    54,    55,     0,     0,     0,     3,     4,     5,     0,
       7,     0,     0,     0,     8,     9,     0,     0,     0,    10,
     106,    11,    12,    13,    95,    96,    16,    17,     0,     0,
       0,     0,    97,    98,    99,    21,    22,    23,    24,     0,
       0,     0,     0,   657,     0,     0,     0,     0,   100,     0,
       0,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,     0,    40,    41,   314,   315,   316,   317,   318,   319,
     320,   321,   322,   323,   324,   325,   326,     0,     0,   327,
     328,     0,     0,     0,     0,   829,     0,     0,   105,    46,
       0,    47,    48,     0,     0,     0,    50,    51,    52,    53,
      54,    55,     0,     0,   329,     0,   330,   331,   332,   333,
     334,   335,   336,   337,   338,   339,   515,   516,     0,   106,
     517,     0,     0,     0,     0,     0,  -218,     0,   159,   160,
     161,   162,   163,   164,     0,   165,   166,     0,     0,   167,
       0,     0,     0,   168,   169,   170,   171,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   172,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   173,   174,   175,   176,   177,   178,   179,   180,
     181,   182,   522,   523,   183,     0,   524,     0,     0,     0,
       0,     0,     0,   184,   159,   160,   161,   162,   163,   164,
       0,   165,   166,     0,     0,   167,     0,     0,     0,   168,
     169,   170,   171,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   172,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   173,   174,
     175,   176,   177,   178,   179,   180,   181,   182,   527,   523,
     183,     0,   528,     0,     0,     0,     0,     0,     0,   184,
     159,   160,   161,   162,   163,   164,     0,   165,   166,     0,
       0,   167,     0,     0,     0,   168,   169,   170,   171,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   172,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   173,   174,   175,   176,   177,   178,
     179,   180,   181,   182,   543,   516,   183,     0,   544,     0,
       0,     0,     0,     0,     0,   184,   159,   160,   161,   162,
     163,   164,     0,   165,   166,     0,     0,   167,     0,     0,
       0,   168,   169,   170,   171,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   172,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     173,   174,   175,   176,   177,   178,   179,   180,   181,   182,
     580,   516,   183,     0,   581,     0,     0,     0,     0,     0,
       0,   184,   159,   160,   161,   162,   163,   164,     0,   165,
     166,     0,     0,   167,     0,     0,     0,   168,   169,   170,
     171,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   172,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   173,   174,   175,   176,
     177,   178,   179,   180,   181,   182,   583,   523,   183,     0,
     584,     0,     0,     0,     0,     0,     0,   184,   159,   160,
     161,   162,   163,   164,     0,   165,   166,     0,     0,   167,
       0,     0,     0,   168,   169,   170,   171,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   172,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   173,   174,   175,   176,   177,   178,   179,   180,
     181,   182,   597,   516,   183,     0,   598,     0,     0,     0,
       0,     0,     0,   184,   159,   160,   161,   162,   163,   164,
       0,   165,   166,     0,     0,   167,     0,     0,     0,   168,
     169,   170,   171,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   172,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   173,   174,
     175,   176,   177,   178,   179,   180,   181,   182,   600,   523,
     183,     0,   601,     0,     0,     0,     0,     0,     0,   184,
     159,   160,   161,   162,   163,   164,     0,   165,   166,     0,
       0,   167,     0,     0,     0,   168,   169,   170,   171,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   172,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   173,   174,   175,   176,   177,   178,
     179,   180,   181,   182,   638,   516,   183,     0,   639,     0,
       0,     0,     0,     0,     0,   184,   159,   160,   161,   162,
     163,   164,     0,   165,   166,     0,     0,   167,     0,     0,
       0,   168,   169,   170,   171,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   172,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     173,   174,   175,   176,   177,   178,   179,   180,   181,   182,
     641,   523,   183,     0,   642,     0,     0,     0,     0,     0,
       0,   184,   159,   160,   161,   162,   163,   164,     0,   165,
     166,     0,     0,   167,     0,     0,     0,   168,   169,   170,
     171,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   172,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   173,   174,   175,   176,
     177,   178,   179,   180,   181,   182,   875,   516,   183,     0,
     876,     0,     0,     0,     0,     0,     0,   184,   159,   160,
     161,   162,   163,   164,     0,   165,   166,     0,     0,   167,
       0,     0,     0,   168,   169,   170,   171,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   172,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   173,   174,   175,   176,   177,   178,   179,   180,
     181,   182,   878,   523,   183,     0,   879,     0,     0,     0,
       0,     0,     0,   184,   159,   160,   161,   162,   163,   164,
       0,   165,   166,     0,     0,   167,     0,     0,     0,   168,
     169,   170,   171,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   172,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   173,   174,
     175,   176,   177,   178,   179,   180,   181,   182,     0,     0,
     183,     0,     0,     0,     0,     0,     0,     0,     0,   184,
     314,   315,   316,   317,   318,   319,   320,   321,   322,   323,
     324,   325,   326,     0,     0,   327,   328,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     329,     0,   330,   331,   332,   333,   334,   335,   336,   337,
     338,   339,   314,   315,   316,   317,   318,   319,   320,   321,
     322,   323,   324,   325,   326,     0,   251,   327,   328,     0,
       0,     0,  -218,   314,   315,   316,   317,   318,   319,   320,
     321,   322,   323,   324,   325,   326,     0,     0,   327,   328,
       0,     0,   329,     0,   330,   331,   332,   333,   334,   335,
     336,   337,   338,   339,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   329,  -218,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   603,   314,   315,   316,   317,
     318,   319,   320,   321,   322,   323,   324,   325,   326,     0,
       0,   327,   328,   314,   315,   316,   317,   318,   319,   320,
     321,   322,   323,   324,   325,   326,     0,     0,   327,   328,
       0,     0,     0,     0,     0,     0,   329,   658,   330,   331,
     332,   333,   334,   335,   336,   337,   338,   339,     0,     0,
       0,     0,     0,   329,     0,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   314,   315,   316,   317,   318,
     319,   320,   321,   322,   323,   324,-32768,-32768,     0,     0,
     327,   328,   314,   315,   316,   317,   318,   319,   320,   321,
       0,   323,   324,     0,     0,     0,     0,   327,   328,     0,
       0,     0,     0,     0,     0,     0,     0,   330,   331,   332,
     333,   334,   335,   336,   337,   338,   339,     0,     0,     0,
       0,     0,     0,     0,   330,   331,   332,   333,   334,   335,
     336,   337,   338,   339,   314,   315,   316,   317,   318,   319,
     320,     0,     0,   323,   324,     0,     0,     0,     0,   327,
     328,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   330,   331,   332,   333,
     334,   335,   336,   337,   338,   339
};

static const short yycheck[] =
{
      14,    15,    13,     6,    18,    26,   213,    20,   370,    14,
      15,   245,    49,    18,     5,   100,   395,    60,   389,   313,
      10,    14,    15,    26,   690,    18,     3,     4,    42,    43,
       2,     1,    20,    47,    48,   407,    13,   104,    27,   575,
     531,   532,   341,    57,    58,    26,   285,    14,    15,   585,
     289,    18,     5,     6,   566,    48,   568,   529,   530,    50,
     340,   368,   342,   343,   344,    14,    15,   366,   440,    18,
      60,    25,    49,    26,     9,    10,    13,   687,   259,    92,
     690,    48,    57,    25,    81,   384,    99,   367,    26,    13,
      36,    37,    69,    58,    72,    81,   130,    50,    47,   398,
     113,    84,    64,   383,    92,   385,    54,    13,   120,    25,
      15,   662,    83,    18,    45,    28,   105,   668,   108,   399,
     129,    15,    81,    17,    36,    37,    83,   124,    25,   310,
     108,   129,   103,   130,    99,   100,   122,   107,   124,   120,
      25,   130,   131,   126,    25,   103,   103,   128,   428,   448,
      13,   113,   114,   115,   108,   126,    83,    15,   824,    17,
     130,   131,   126,   122,   129,   124,   108,    50,   105,   449,
      25,    54,   126,   216,   128,    25,   103,    81,    25,   125,
     265,   105,   120,    83,   126,   676,   128,   103,     1,     2,
       3,     4,   108,   130,   131,     8,     9,    10,   560,   105,
      13,    14,    15,   103,   128,    18,   130,   131,   199,   125,
     126,   108,    25,   103,   824,   229,   230,   231,   130,    81,
     124,    94,   461,   108,   130,   131,   216,   108,   242,   126,
     244,   245,    45,    46,    47,   542,    49,   242,    81,   244,
     245,   126,   105,    83,    57,   126,   199,   126,    81,   242,
     264,   244,   245,   108,   561,    92,    69,   128,   108,   128,
     796,   108,   124,   735,   736,   777,   778,   130,   131,    54,
     782,   126,   103,   110,   311,   242,   126,   244,   245,   126,
     574,   124,    56,    57,   126,   220,   221,    83,   130,   122,
     103,   124,   105,   242,   308,   244,   245,   131,   365,   313,
     314,   315,   316,   317,   318,   319,   320,   321,   322,   323,
     324,   325,   326,   327,   328,   329,   330,   331,   332,   333,
     334,   335,   336,   337,   338,   339,   298,   341,   259,    54,
     415,   303,   417,   308,   311,   349,   350,   242,   313,   244,
     245,   308,   721,   623,   624,   857,   313,    25,   433,   434,
     126,   723,   366,    50,   130,    25,    83,    58,   730,   268,
      83,   270,    83,   272,   299,   300,   301,   302,   382,    84,
     384,   361,   386,   387,   349,   350,   103,   391,    52,   310,
     103,    26,   103,   590,   398,    59,    60,   340,   622,   403,
     404,   204,   341,   407,    91,    92,    81,   411,    99,   100,
     101,   422,    83,   126,   394,   395,   411,   220,   221,    26,
     424,   404,   365,   110,    81,   429,   113,   366,   411,   422,
      83,   783,   103,   437,   391,   796,   440,    81,   442,   242,
     383,   244,   245,   103,   448,   384,    81,   122,   108,   124,
     103,   254,   126,   128,   397,   126,   259,   126,   128,   398,
     126,   130,   466,   467,   120,   125,   126,   124,   238,   130,
     131,    64,   769,   477,    81,   550,    36,    37,   122,   422,
     124,    56,    57,   125,   427,   120,   848,   122,   125,   124,
     121,    58,   125,   128,    83,   298,   299,   300,   301,   302,
     303,   304,   305,    26,   447,   308,    83,   310,   311,   448,
     313,     1,     2,   120,   103,   122,   519,   124,     8,     9,
      10,   128,   884,   123,    14,    15,   103,    54,    18,   101,
      81,   828,    99,   100,   101,    25,   101,   126,   341,    64,
      83,   519,    64,   546,    14,    15,   349,   350,   526,   126,
      81,   529,   530,    81,    90,    45,    46,    47,    81,   539,
     103,   572,   126,   366,    81,   368,   369,    57,    81,    81,
     574,   122,   861,   124,    10,     8,    64,   380,    58,   572,
      17,   384,   562,   126,   588,   388,    13,   390,   785,    10,
     571,   122,   862,   124,   791,   398,   124,   120,    10,   122,
      58,   124,   606,    81,    81,   128,   610,   124,   411,   684,
     614,   124,   124,   103,    81,   105,   541,   574,   622,    99,
     100,   101,   425,   111,   112,   113,   114,   115,   571,   572,
      81,   401,   636,    50,   126,    52,    53,    54,    55,   622,
     125,    99,   100,   101,   122,   448,   124,   124,    52,    53,
     651,   655,    58,   657,   658,   659,   660,   124,   126,   734,
     664,   665,    81,   125,   126,   125,   741,    81,   121,   125,
     129,   122,    81,   124,    91,    92,   126,   602,   126,   683,
     126,    81,   125,   622,   651,   123,    50,   103,    52,    53,
      54,    55,   123,   110,   659,   101,   113,   126,   678,   664,
     665,   126,    50,   122,   708,   124,   710,   711,   122,    50,
     124,   128,   716,   122,   204,   124,   126,    15,    58,   723,
     123,    61,   122,   727,   124,    10,   730,    91,    92,    10,
     220,   221,   727,   126,   123,    47,    48,    92,   541,   542,
     126,   721,   125,   125,   727,   126,   110,   125,   752,   113,
     121,   125,   242,   123,   244,   245,   760,    10,   561,    99,
     100,    10,   125,    84,   254,    52,    53,     9,    55,   259,
     727,    10,    59,    60,    39,    40,    41,    42,    43,    10,
     705,   125,   121,   108,   126,    10,    10,   125,   125,   793,
     126,   795,   126,   126,    10,   760,    10,   801,   121,   602,
     804,    10,    54,   121,    10,   809,    10,   126,   298,   299,
     300,   301,   302,   303,   304,   305,   123,   784,   308,   622,
     310,     0,     0,   313,    69,   628,   864,     4,    76,   651,
       5,   863,     8,     9,    10,    79,   560,   783,   687,   609,
     643,   687,   846,    60,   848,    -1,    -1,    -1,   651,    25,
     620,   341,    -1,    -1,    -1,    -1,   659,   861,    -1,   349,
     350,   664,   665,   846,   868,    -1,   870,    -1,    -1,    -1,
      46,    -1,    -1,    -1,    -1,    -1,   366,    -1,   368,   369,
     884,    -1,    -1,    -1,    -1,   889,    -1,    -1,    -1,    -1,
     380,    -1,    -1,    -1,   384,    -1,    -1,    -1,   388,   702,
     390,     1,   705,    -1,    -1,    -1,    -1,    -1,   398,    -1,
      -1,    -1,    -1,    -1,   717,   718,   719,   860,    -1,    -1,
      -1,   411,   861,    -1,    -1,   237,   238,   103,     1,     2,
       3,     4,     5,   245,    -1,   425,    -1,    -1,    -1,    -1,
      13,    -1,    -1,    -1,    64,    45,    -1,    -1,   751,    -1,
      -1,    -1,   722,    64,    -1,   725,   726,   760,   448,    79,
      80,    -1,    64,   766,   767,    -1,   769,    -1,    79,    80,
      -1,    -1,    45,    -1,    -1,    -1,    49,    79,    80,    -1,
      -1,   784,    -1,    -1,    -1,   788,    -1,    -1,   108,   109,
     110,   111,   112,   113,   114,   115,    69,    -1,    -1,   110,
     111,   112,   113,   114,   115,   105,    -1,    -1,    -1,   111,
     112,   113,   114,   115,    -1,    -1,    -1,    -1,   821,    -1,
      -1,    -1,    -1,    -1,    -1,   828,    -1,    -1,    -1,   341,
      -1,   834,   105,   836,    -1,    -1,   806,   807,    -1,    -1,
     843,    -1,    -1,    -1,   220,   221,    -1,    -1,    -1,    -1,
      -1,   541,   542,    -1,   366,    -1,    -1,    -1,   861,    -1,
      -1,    -1,    -1,    -1,   376,    -1,     1,     2,     3,     4,
      -1,   561,   384,    -1,   844,   845,    -1,    -1,    13,    -1,
     850,    -1,    -1,    -1,    -1,    -1,   398,    -1,    -1,   401,
      -1,    -1,    -1,    -1,    -1,    -1,     1,     2,    -1,   869,
      -1,    -1,    -1,    -1,   416,    -1,    -1,    -1,    13,    -1,
      45,    -1,   602,   883,    49,    -1,   886,    -1,    -1,    -1,
      -1,   891,    -1,   299,   300,   301,   302,    -1,   304,   305,
      -1,   204,   622,    -1,    69,    -1,   448,    -1,   628,    -1,
      45,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   643,   254,    -1,    -1,    -1,    -1,   259,
      -1,    -1,    -1,    -1,   476,    -1,    -1,    -1,    -1,   659,
     105,    -1,    -1,    -1,   664,   665,    -1,    -1,    -1,    -1,
      -1,   254,    -1,    -1,    -1,    -1,   259,    -1,    -1,    -1,
      -1,    -1,    -1,   369,    -1,    -1,     1,     2,    -1,    -1,
     105,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     310,    -1,   702,    -1,   526,   705,    -1,   529,   530,   531,
     532,    -1,    -1,    -1,    -1,   298,    -1,   717,   718,   719,
     303,    -1,    -1,    -1,    -1,   411,   548,   310,   311,    -1,
      45,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   564,    -1,   566,    -1,   568,    -1,    -1,    -1,
      -1,   751,   574,   575,    -1,   577,    -1,    -1,    -1,   204,
     760,    -1,    -1,   585,    -1,    -1,   766,   767,    -1,   769,
     380,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   388,    -1,
     390,    -1,    -1,    -1,    -1,   368,    -1,   609,   788,   204,
     105,    -1,    -1,    -1,    -1,    -1,    -1,   380,   620,    -1,
      -1,    -1,    -1,    -1,    -1,   388,    -1,   390,    -1,   254,
      -1,    -1,    -1,    -1,   259,   425,    -1,    -1,    -1,    -1,
      -1,   821,    -1,    -1,    -1,    -1,    -1,    -1,   828,    -1,
      -1,    -1,    -1,    -1,   834,    -1,   836,    -1,    -1,   254,
      -1,    -1,   425,   843,   259,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   298,   676,   541,    -1,    -1,   303,    -1,
      -1,   861,    -1,    -1,    -1,   310,   311,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   700,    -1,
      -1,   703,    -1,   298,    -1,    -1,    -1,    -1,   303,   204,
      -1,    -1,    -1,    -1,    -1,   310,    -1,    -1,    -1,    -1,
     722,    -1,    -1,   725,   726,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   735,   736,    -1,   602,    -1,    -1,    -1,
      -1,    -1,    -1,   368,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   380,    -1,    -1,    -1,   254,
      -1,    -1,   628,   388,   259,   390,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   368,    -1,   777,   778,    -1,    -1,   542,
     782,    -1,    -1,    -1,    -1,   380,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   388,   796,   390,    -1,    -1,   561,    -1,
     425,    -1,    -1,   298,   806,   807,    -1,    -1,   303,    -1,
      -1,    -1,    -1,    -1,    -1,   310,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     425,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   705,
      -1,    -1,   844,   845,    -1,    -1,    -1,    -1,   850,    -1,
      -1,    -1,    -1,   643,    -1,   857,    -1,    -1,    -1,   861,
      -1,   863,   864,    -1,    -1,    -1,    -1,   869,    -1,    -1,
      -1,    -1,    -1,   368,    -1,    -1,    -1,    -1,    -1,    -1,
     643,   883,    -1,    -1,   886,   380,    -1,    -1,   651,   891,
      -1,    -1,    -1,   388,    -1,   390,    -1,    -1,    -1,    -1,
      -1,   229,   230,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   702,    -1,    -1,    -1,    -1,   542,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   717,   718,   719,
     425,    -1,    -1,    -1,    -1,    -1,   561,    -1,    -1,   702,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   542,    -1,    -1,
      -1,    -1,    -1,    -1,   717,   718,   719,    -1,    -1,    -1,
      -1,   751,    -1,    -1,    -1,    -1,   561,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   766,   767,    -1,    -1,
     308,    -1,    -1,    -1,    -1,   313,    -1,    -1,   751,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   788,    -1,
      -1,    -1,    -1,   766,   767,    -1,   769,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   643,   644,
      -1,   784,    -1,    -1,    -1,   788,   651,    -1,    -1,    -1,
      -1,   821,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   834,    -1,   836,   542,   643,    -1,
      -1,    -1,    -1,   843,    -1,    -1,   651,    -1,   821,    -1,
      -1,    -1,    -1,   391,    -1,   828,   561,    -1,    -1,    -1,
      -1,   834,    -1,   836,    -1,   403,   404,   702,    -1,   407,
     843,    -1,    -1,   411,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   717,   718,   719,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   702,    -1,   437,
      -1,    -1,   440,    -1,   442,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   717,   718,   719,    -1,   751,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   766,   767,    -1,   769,    -1,    -1,    -1,   643,   477,
      -1,    -1,    -1,    -1,    -1,    -1,   751,    -1,    -1,   784,
      -1,    -1,    -1,   788,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   766,   767,    -1,   769,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   784,
      -1,    -1,    -1,   788,    -1,    -1,   821,    -1,    -1,    -1,
      -1,    -1,    -1,   828,    -1,    -1,    -1,   702,    -1,   834,
      -1,   836,    -1,    -1,    -1,    -1,    -1,    -1,   843,    -1,
      -1,    -1,   717,   718,   719,    -1,   821,    -1,    -1,    -1,
      -1,    -1,    -1,   828,    -1,    -1,    -1,    -1,    -1,   834,
      -1,   836,    -1,    -1,    -1,    -1,   574,    -1,   843,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   751,    -1,    -1,    -1,
     588,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   766,   767,    -1,   769,     0,    -1,    -1,   606,    -1,
      -1,    -1,   610,     8,     9,    10,   614,    -1,    13,    14,
      15,    -1,    17,   788,   622,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    27,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    36,    37,    -1,    39,    40,    41,    42,    43,    64,
      65,    66,    67,    68,    69,    70,   821,   655,    73,    74,
      -1,    -1,    -1,   828,    79,    80,    -1,    -1,    -1,   834,
      -1,   836,    -1,    -1,    -1,    -1,    -1,    -1,   843,    -1,
      -1,    -1,    -1,    -1,    -1,   683,    81,    -1,    -1,    -1,
      -1,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,    -1,    -1,    -1,    -1,    -1,     0,    -1,    -1,    -1,
     105,    -1,    -1,    -1,     8,     9,    10,    -1,   716,    -1,
      14,    15,    -1,    17,    -1,   723,   121,    -1,    -1,   124,
     125,    -1,   730,   128,    -1,   130,   131,    -1,    -1,    -1,
      -1,    -1,    36,    37,    -1,    39,    40,    41,    42,    43,
      -1,    -1,    -1,    -1,   752,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    -1,    -1,    79,    80,    81,    -1,    83,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   795,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   804,    -1,    -1,   103,
     104,   809,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,    -1,    -1,    -1,    -1,    -1,   121,   122,    -1,
     124,   125,   126,    -1,    -1,    -1,   130,   131,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   846,    -1,
     848,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     868,    -1,   870,    -1,    -1,    -1,     0,     1,    -1,     3,
       4,     5,     6,     7,    -1,    -1,   884,    11,    12,    -1,
      -1,   889,    16,    -1,    18,    19,    20,    21,    22,    23,
      24,    -1,    -1,    -1,    -1,    29,    30,    31,    32,    33,
      34,    35,    -1,    -1,    38,    -1,    -1,    -1,    -1,    -1,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    -1,    59,    60,    -1,    62,    63,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    82,    -1,
      -1,    85,    86,    -1,    88,    89,    -1,    91,    -1,    93,
      94,    95,    96,    97,    98,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     0,    -1,    -1,
      -1,    -1,   116,   117,   118,     8,     9,    10,    -1,    -1,
      -1,    14,    15,    -1,    17,    -1,   130,   131,    -1,    -1,
      43,    -1,    -1,    26,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    36,    37,    -1,    39,    40,    41,    42,
      43,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    -1,    -1,    79,    80,    -1,    -1,
      -1,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    -1,    -1,    79,    80,    81,    -1,
      83,   104,    -1,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     103,   104,    -1,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,    -1,    -1,    -1,    -1,   120,   121,   122,
      -1,   124,   125,   126,    -1,    -1,    -1,   130,   131,     1,
      -1,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    -1,    -1,    15,    16,    -1,    18,    19,    20,    21,
      22,    23,    24,    -1,    -1,    -1,    -1,    29,    30,    31,
      32,    33,    34,    35,    -1,    -1,    38,    -1,    -1,    -1,
      -1,    -1,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    -1,    59,    60,    -1,
      62,    63,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      82,    -1,    -1,    85,    86,    -1,    88,    89,    -1,    91,
      -1,    93,    94,    95,    96,    97,    98,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   116,   117,   118,    -1,    -1,    -1,
      -1,     1,    -1,     3,     4,     5,     6,     7,   130,   131,
      10,    11,    12,    -1,    14,    15,    16,    -1,    18,    19,
      20,    21,    22,    23,    24,    -1,    -1,    -1,    -1,    29,
      30,    31,    32,    33,    34,    35,    -1,    -1,    38,    -1,
      -1,    -1,    -1,    -1,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    -1,    59,
      60,    -1,    62,    63,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    82,    -1,    -1,    85,    86,    -1,    88,    89,
      -1,    91,    -1,    93,    94,    95,    96,    97,    98,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   116,   117,   118,    -1,
      -1,    -1,    -1,     1,    -1,     3,     4,     5,     6,     7,
     130,   131,    10,    11,    12,    -1,    -1,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    -1,    -1,    -1,
      -1,    29,    30,    31,    32,    33,    34,    35,    -1,    -1,
      38,    -1,    -1,    -1,    -1,    -1,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      -1,    59,    60,    -1,    62,    63,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    82,    -1,    -1,    85,    86,    -1,
      88,    89,    -1,    91,    -1,    93,    94,    95,    96,    97,
      98,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   116,   117,
     118,    -1,    -1,    -1,    -1,     1,    -1,     3,     4,     5,
       6,     7,   130,   131,    10,    11,    12,    -1,    -1,    15,
      16,    -1,    18,    19,    20,    21,    22,    23,    24,    -1,
      -1,    -1,    -1,    29,    30,    31,    32,    33,    34,    35,
      -1,    -1,    38,    -1,    -1,    -1,    -1,    -1,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    -1,    59,    60,    -1,    62,    63,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    82,    -1,    -1,    85,
      86,    -1,    88,    89,    -1,    91,    -1,    93,    94,    95,
      96,    97,    98,    -1,    -1,    -1,    -1,    -1,     1,    -1,
       3,     4,     5,     6,     7,    -1,     9,    10,    11,    12,
     116,   117,   118,    16,    -1,    18,    19,    20,    21,    22,
      23,    24,    -1,    -1,   130,   131,    29,    30,    31,    32,
      33,    34,    35,    -1,    -1,    38,    -1,    -1,    -1,    -1,
      -1,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    -1,    59,    60,    -1,    62,
      63,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    82,
      -1,    -1,    85,    86,    -1,    88,    89,    -1,    91,    -1,
      93,    94,    95,    96,    97,    98,    -1,    -1,    -1,    -1,
      -1,     1,    -1,     3,     4,     5,     6,     7,    -1,    -1,
      -1,    11,    12,   116,   117,   118,    16,    -1,    18,    19,
      20,    21,    22,    23,    24,    -1,    -1,   130,   131,    29,
      30,    31,    32,    33,    34,    35,    -1,    -1,    38,    -1,
      -1,    -1,    -1,    -1,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    -1,    59,
      60,    -1,    62,    63,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    82,    -1,    -1,    85,    86,    -1,    88,    89,
      -1,    91,    -1,    93,    94,    95,    96,    97,    98,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   116,   117,   118,    -1,
      -1,    -1,    -1,    -1,    -1,   125,    -1,    -1,    -1,    -1,
     130,   131,     1,    -1,     3,     4,     5,     6,     7,    -1,
      -1,    -1,    11,    12,    -1,    -1,    -1,    16,    -1,    18,
      19,    20,    21,    22,    23,    24,    -1,    -1,    -1,    -1,
      29,    30,    31,    32,    33,    34,    35,    -1,    -1,    38,
      -1,    -1,    -1,    -1,    -1,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    -1,
      59,    60,    -1,    62,    63,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    82,    -1,    -1,    85,    86,    -1,    88,
      89,    -1,    91,    -1,    93,    94,    95,    96,    97,    98,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   116,   117,   118,
      -1,    -1,    -1,    -1,    -1,    -1,   125,    -1,    -1,    -1,
      -1,   130,   131,     1,    -1,     3,     4,     5,     6,     7,
      -1,    -1,    -1,    11,    12,    -1,    -1,    -1,    16,    -1,
      18,    19,    20,    21,    22,    23,    24,    -1,    -1,    -1,
      -1,    29,    30,    31,    32,    33,    34,    35,    -1,    -1,
      38,    -1,    -1,    -1,    -1,    -1,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      -1,    59,    60,    -1,    62,    63,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    82,    -1,    -1,    85,    86,    -1,
      88,    89,    -1,    91,    -1,    93,    94,    95,    96,    97,
      98,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   116,   117,
     118,    -1,    -1,   121,    -1,     1,    -1,     3,     4,     5,
       6,     7,   130,   131,    10,    11,    12,    -1,    -1,    -1,
      16,    -1,    18,    19,    20,    21,    22,    23,    24,    -1,
      -1,    -1,    -1,    29,    30,    31,    32,    33,    34,    35,
      -1,    -1,    38,    -1,    -1,    -1,    -1,    -1,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    -1,    59,    60,    -1,    62,    63,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    82,    -1,    -1,    85,
      86,    -1,    88,    89,    -1,    91,    -1,    93,    94,    95,
      96,    97,    98,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       3,     4,     5,     6,     7,    -1,    -1,    -1,    11,    12,
     116,   117,   118,    16,    -1,    18,    19,    20,    21,    22,
      23,    24,    -1,    -1,   130,   131,    29,    30,    31,    32,
      33,    34,    35,    -1,    -1,    38,    -1,    -1,    -1,    -1,
      -1,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    -1,    59,    60,    -1,    62,
      63,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    82,
      -1,    -1,    85,    86,    -1,    88,    89,    -1,    91,    -1,
      93,    94,    95,    96,    97,    98,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     3,     4,     5,    -1,     7,    -1,    -1,
      -1,    11,    12,   116,   117,   118,    16,    -1,    18,    19,
      20,    21,    22,    23,    24,    -1,    -1,    -1,   131,    29,
      30,    31,    32,    33,    34,    35,    -1,    -1,    38,    -1,
      -1,    -1,    -1,    -1,    -1,    45,    -1,    -1,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    -1,    59,
      60,    -1,    62,    63,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    82,    -1,    -1,    85,    86,    -1,    88,    89,
      -1,    -1,    -1,    93,    94,    95,    96,    97,    98,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   116,   117,   118,    -1,
      -1,    -1,     3,     4,     5,     6,     7,     8,     9,    10,
     130,   131,    13,    14,    15,    16,    17,    -1,    -1,    20,
      21,    22,    23,    24,    25,    26,    -1,    -1,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    -1,    -1,    -1,    -1,    -1,
      -1,    62,    63,    64,    65,    66,    67,    -1,    69,    70,
      -1,    -1,    73,    -1,    -1,    -1,    77,    78,    79,    80,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      91,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,    -1,    -1,   118,    -1,    -1,
       3,     4,     5,    -1,     7,    -1,   127,   128,    11,    12,
      -1,    -1,    -1,    16,    -1,    18,    19,    20,    21,    22,
      23,    24,    -1,    26,    -1,    -1,    29,    30,    31,    32,
      33,    34,    35,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    45,    -1,    -1,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    -1,    59,    60,    -1,    62,
      63,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    82,
      -1,    -1,    85,    86,    -1,    88,    89,    -1,    91,    92,
      93,    94,    95,    96,    97,    98,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     3,     4,     5,    -1,     7,    -1,    -1,
      -1,    11,    12,   116,   117,   118,    16,   120,    18,    19,
      20,    21,    22,    23,    24,   128,    26,    -1,    -1,    29,
      30,    31,    32,    33,    34,    35,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    45,    -1,    -1,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    -1,    59,
      60,    -1,    62,    63,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    82,    -1,    -1,    85,    86,    -1,    88,    89,
      -1,    91,    92,    93,    94,    95,    96,    97,    98,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,    -1,
       7,    -1,    -1,    -1,    11,    12,   116,   117,   118,    16,
     120,    18,    19,    20,    21,    22,    23,    24,   128,    26,
      -1,    -1,    29,    30,    31,    32,    33,    34,    35,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    45,    -1,
      -1,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    -1,    59,    60,    -1,    62,    63,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    82,    -1,    -1,    85,    86,
      -1,    88,    89,    -1,    91,    92,    93,    94,    95,    96,
      97,    98,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,
       4,     5,    -1,     7,    -1,    -1,    -1,    11,    12,   116,
     117,   118,    16,   120,    18,    19,    20,    21,    22,    23,
      24,   128,    -1,    -1,    -1,    29,    30,    31,    32,    33,
      34,    35,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    45,    -1,    -1,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    -1,    59,    60,    -1,    62,    63,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    82,    83,
      -1,    85,    86,    -1,    88,    89,    -1,    91,    92,    93,
      94,    95,    96,    97,    98,    -1,    -1,    -1,    -1,   103,
      -1,    -1,     3,     4,     5,    -1,     7,    -1,    -1,    -1,
      11,    12,   116,   117,   118,    16,    -1,    18,    19,    20,
      21,    22,    23,    24,   128,    -1,    -1,    -1,    29,    30,
      31,    32,    33,    34,    35,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    45,    -1,    -1,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    -1,    59,    60,
      -1,    62,    63,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    82,    83,    -1,    85,    86,    -1,    88,    89,    -1,
      91,    92,    93,    94,    95,    96,    97,    98,    -1,    -1,
      -1,    -1,   103,    -1,    -1,     3,     4,     5,    -1,     7,
      -1,    -1,    -1,    11,    12,   116,   117,   118,    16,    -1,
      18,    19,    20,    21,    22,    23,    24,   128,    -1,    -1,
      -1,    29,    30,    31,    32,    33,    34,    35,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    45,    -1,    -1,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      -1,    59,    60,    -1,    62,    63,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    82,    -1,    -1,    85,    86,    -1,
      88,    89,    -1,    91,    92,    93,    94,    95,    96,    97,
      98,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,     4,
       5,    -1,     7,    -1,    -1,    -1,    11,    12,   116,   117,
     118,    16,    -1,    18,    19,    20,    21,    22,    23,    24,
     128,    -1,    -1,    -1,    29,    30,    31,    32,    33,    34,
      35,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      45,    -1,    -1,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    -1,    59,    60,    -1,    62,    63,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    82,    -1,    -1,
      85,    86,    -1,    88,    89,    -1,    91,    92,    93,    94,
      95,    96,    97,    98,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     3,     4,     5,    -1,     7,    -1,    -1,    -1,    11,
      12,   116,   117,   118,    16,    -1,    18,    19,    20,    21,
      22,    23,    24,   128,    -1,    -1,    -1,    29,    30,    31,
      32,    33,    34,    35,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    45,    -1,    -1,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    -1,    59,    60,    -1,
      62,    63,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      82,    -1,    -1,    85,    86,    -1,    88,    89,    -1,    91,
      92,    93,    94,    95,    96,    97,    98,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     3,     4,     5,    -1,     7,    -1,
      -1,    -1,    11,    12,   116,   117,   118,    16,    -1,    18,
      19,    20,    21,    22,    23,    24,   128,    -1,    -1,    -1,
      29,    30,    31,    32,    33,    34,    35,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    45,    -1,    -1,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    -1,
      59,    60,    -1,    62,    63,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    82,    -1,    -1,    85,    86,    -1,    88,
      89,    -1,    91,    92,    93,    94,    95,    96,    97,    98,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   116,   117,   118,
       3,     4,     5,     6,     7,     8,     9,    10,    -1,   128,
      13,    14,    15,    16,    17,    -1,    -1,    20,    21,    22,
      23,    24,    25,    26,    -1,    -1,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    -1,    -1,    -1,    -1,    -1,    -1,    62,
      63,    64,    65,    66,    67,    -1,    69,    70,    -1,    -1,
      73,    -1,    -1,    -1,    77,    78,    79,    80,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    91,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,    -1,    -1,   118,     3,     4,     5,     6,
       7,     8,     9,    10,   127,    -1,    13,    14,    15,    16,
      17,    -1,    -1,    20,    21,    22,    23,    24,    25,    26,
      -1,    -1,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    -1,    54,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    62,    63,    64,    65,    66,
      67,    -1,    69,    70,    -1,    -1,    73,    -1,    -1,    -1,
      77,    78,    79,    80,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    91,    -1,    93,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,    -1,
      -1,   118,     3,     4,     5,     6,     7,     8,     9,    10,
     127,    -1,    13,    14,    15,    16,    17,    -1,    -1,    20,
      21,    22,    23,    24,    25,    26,    -1,    -1,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    -1,    -1,    54,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    62,    63,    64,    65,    66,    67,    -1,    69,    70,
      -1,    -1,    73,    -1,    -1,    -1,    77,    78,    79,    80,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      91,    -1,    93,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,    -1,    -1,   118,     3,     4,
       5,     6,     7,     8,     9,    10,   127,    -1,    13,    14,
      15,    16,    17,    -1,    -1,    20,    21,    22,    23,    24,
      25,    26,    -1,    -1,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    -1,    -1,    54,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    62,    63,    64,
      65,    66,    67,    -1,    69,    70,    -1,    -1,    73,    -1,
      -1,    -1,    77,    78,    79,    80,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    91,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,    -1,    -1,   118,    -1,     3,     4,     5,    -1,     7,
      -1,    -1,   127,    11,    12,    -1,    -1,    -1,    16,    -1,
      18,    19,    20,    21,    22,    23,    24,    -1,    -1,    -1,
      -1,    29,    30,    31,    32,    33,    34,    35,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    45,    -1,    -1,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      -1,    59,    60,    -1,    62,    63,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    82,    -1,    -1,    85,    86,    -1,
      88,    89,    -1,    91,    92,    93,    94,    95,    96,    97,
      98,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     3,     4,     5,     6,     7,   116,   117,
     118,    11,    12,    -1,    -1,    -1,    16,   125,    18,    19,
      20,    21,    22,    23,    24,    -1,    -1,    -1,    -1,    29,
      30,    31,    32,    33,    34,    35,    -1,    -1,    38,    -1,
      -1,    -1,    -1,    -1,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    -1,    59,
      60,    -1,    62,    63,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    82,    -1,    -1,    85,    86,    -1,    88,    89,
      -1,    91,    -1,    93,    94,    95,    96,    97,    98,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,    -1,
       7,    -1,    -1,    -1,    11,    12,   116,   117,   118,    16,
      -1,    18,    19,    20,    21,    22,    23,    24,    -1,    -1,
      -1,    -1,    29,    30,    31,    32,    33,    34,    35,    -1,
      -1,    38,    -1,    -1,    -1,    -1,    -1,    -1,    45,    -1,
      -1,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    -1,    59,    60,    -1,    62,    63,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    82,    -1,    -1,    85,    86,
      -1,    88,    89,    -1,    91,    92,    93,    94,    95,    96,
      97,    98,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,
       4,     5,    -1,     7,    -1,    -1,    -1,    11,    12,   116,
     117,   118,    16,    -1,    18,    19,    20,    21,    22,    23,
      24,    -1,    -1,    -1,    -1,    29,    30,    31,    32,    33,
      34,    35,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    45,    -1,    -1,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    -1,    59,    60,    -1,    62,    63,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    82,    -1,
      -1,    85,    86,    -1,    88,    89,    -1,    91,    92,    93,
      94,    95,    96,    97,    98,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     3,     4,     5,    -1,     7,    -1,    -1,    -1,
      11,    12,   116,   117,   118,    16,    -1,    18,    19,    20,
      21,    22,    23,    24,    -1,    -1,    -1,    -1,    29,    30,
      31,    32,    33,    34,    35,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    45,    -1,    -1,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    -1,    59,    60,
      -1,    62,    63,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    82,    -1,    -1,    85,    86,    -1,    88,    89,    -1,
      91,    92,    93,    94,    95,    96,    97,    98,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     3,     4,     5,    -1,     7,
      -1,    -1,    -1,    11,    12,   116,   117,   118,    16,    -1,
      18,    19,    20,    21,    22,    23,    24,    -1,    -1,    -1,
      -1,    29,    30,    31,    32,    33,    34,    35,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    45,    -1,    -1,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      -1,    59,    60,    -1,    62,    63,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    82,    -1,    -1,    85,    86,    -1,
      88,    89,    -1,    91,    92,    93,    94,    95,    96,    97,
      98,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,     4,
       5,    -1,     7,    -1,    -1,    -1,    11,    12,   116,   117,
     118,    16,    -1,    18,    19,    20,    21,    22,    23,    24,
      -1,    -1,    -1,    -1,    29,    30,    31,    32,    33,    34,
      35,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      45,    -1,    -1,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    -1,    59,    60,    -1,    62,    63,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    82,    -1,    -1,
      85,    86,    -1,    88,    89,    -1,    91,    92,    93,    94,
      95,    96,    97,    98,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     3,     4,     5,    -1,     7,    -1,    -1,    -1,    11,
      12,   116,   117,   118,    16,    -1,    18,    19,    20,    21,
      22,    23,    24,    -1,    -1,    -1,    -1,    29,    30,    31,
      32,    33,    34,    35,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    45,    -1,    -1,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    -1,    59,    60,    -1,
      62,    63,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      82,    -1,    -1,    85,    86,    -1,    88,    89,    -1,    91,
      92,    93,    94,    95,    96,    97,    98,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     3,     4,     5,    -1,     7,    -1,
      -1,    -1,    11,    12,   116,   117,   118,    16,    -1,    18,
      19,    20,    21,    22,    23,    24,    -1,    -1,    -1,    -1,
      29,    30,    31,    32,    33,    34,    35,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    45,    -1,    -1,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    -1,
      59,    60,    -1,    62,    63,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    82,    -1,    -1,    85,    86,    -1,    88,
      89,    -1,    91,    92,    93,    94,    95,    96,    97,    98,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,
      -1,     7,    -1,    -1,    -1,    11,    12,   116,   117,   118,
      16,    -1,    18,    19,    20,    21,    22,    23,    24,    -1,
      -1,    -1,    -1,    29,    30,    31,    32,    33,    34,    35,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    45,
      -1,    -1,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    -1,    59,    60,    -1,    62,    63,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    82,    -1,    -1,    85,
      86,    -1,    88,    89,    -1,    91,    92,    93,    94,    95,
      96,    97,    98,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       3,     4,     5,    -1,     7,    -1,    -1,    -1,    11,    12,
     116,   117,   118,    16,    -1,    18,    19,    20,    21,    22,
      23,    24,    -1,    -1,    -1,    -1,    29,    30,    31,    32,
      33,    34,    35,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    45,    -1,    -1,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    -1,    59,    60,    -1,    62,
      63,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    82,
      -1,    -1,    85,    86,    -1,    88,    89,    -1,    91,    92,
      93,    94,    95,    96,    97,    98,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     3,     4,     5,    -1,     7,    -1,    -1,
      -1,    11,    12,   116,   117,   118,    16,    -1,    18,    19,
      20,    21,    22,    23,    24,    -1,    -1,    -1,    -1,    29,
      30,    31,    32,    33,    34,    35,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    45,    -1,    -1,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    -1,    59,
      60,    -1,    62,    63,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    82,    -1,    -1,    85,    86,    -1,    88,    89,
      -1,    91,    92,    93,    94,    95,    96,    97,    98,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,    -1,
       7,    -1,    -1,    -1,    11,    12,   116,   117,   118,    16,
      -1,    18,    19,    20,    21,    22,    23,    24,    -1,    -1,
      -1,    -1,    29,    30,    31,    32,    33,    34,    35,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    45,    -1,
      -1,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    -1,    59,    60,    -1,    62,    63,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    82,    -1,    -1,    85,    86,
      -1,    88,    89,    -1,    91,    92,    93,    94,    95,    96,
      97,    98,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,
       4,     5,    -1,     7,    -1,    -1,    -1,    11,    12,   116,
     117,   118,    16,    -1,    18,    19,    20,    21,    22,    23,
      24,    -1,    -1,    -1,    -1,    29,    30,    31,    32,    33,
      34,    35,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    45,    -1,    -1,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    -1,    59,    60,    -1,    62,    63,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    82,    -1,
      -1,    85,    86,    -1,    88,    89,    -1,    91,    92,    93,
      94,    95,    96,    97,    98,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     3,     4,     5,    -1,     7,    -1,    -1,    -1,
      11,    12,   116,   117,   118,    16,    -1,    18,    19,    20,
      21,    22,    23,    24,    -1,    -1,    -1,    -1,    29,    30,
      31,    32,    33,    34,    35,    -1,    -1,    38,    -1,    -1,
      -1,    -1,    -1,    -1,    45,    -1,    -1,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    -1,    59,    60,
      -1,    62,    63,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    82,    -1,    -1,    85,    86,    -1,    88,    89,    -1,
      -1,    -1,    93,    94,    95,    96,    97,    98,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     3,     4,     5,    -1,     7,
      -1,    -1,    -1,    11,    12,   116,   117,   118,    16,    -1,
      18,    19,    20,    21,    22,    23,    24,    -1,    -1,    -1,
      -1,    29,    30,    31,    32,    33,    34,    35,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    45,    -1,    -1,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      -1,    59,    60,    -1,    62,    63,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    82,    -1,    -1,    85,    86,    -1,
      88,    89,    -1,    91,    -1,    93,    94,    95,    96,    97,
      98,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,     4,
       5,    -1,     7,    -1,    -1,    -1,    11,    12,   116,   117,
     118,    16,    -1,    18,    19,    20,    21,    22,    23,    24,
      -1,    -1,    -1,    -1,    29,    30,    31,    32,    33,    34,
      35,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      45,    -1,    -1,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    -1,    59,    60,    -1,    62,    63,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    82,    -1,    -1,
      85,    86,    -1,    88,    89,    -1,    91,    -1,    93,    94,
      95,    96,    97,    98,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     3,     4,     5,    -1,     7,    -1,    -1,    -1,    11,
      12,   116,   117,   118,    16,    -1,    18,    19,    20,    21,
      22,    23,    24,    -1,    -1,    -1,    -1,    29,    30,    31,
      32,    33,    34,    35,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    45,    -1,    -1,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    -1,    59,    60,    -1,
      62,    63,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      82,    -1,    -1,    85,    86,    -1,    88,    89,    -1,    91,
      -1,    93,    94,    95,    96,    97,    98,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     3,     4,     5,    -1,     7,    -1,
      -1,    -1,    11,    12,   116,   117,   118,    16,    -1,    18,
      19,    20,    21,    22,    23,    24,    -1,    -1,    -1,    -1,
      29,    30,    31,    32,    33,    34,    35,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    45,    -1,    -1,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    -1,
      59,    60,    -1,    62,    63,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    82,    -1,    -1,    85,    86,    -1,    88,
      89,    -1,    91,    -1,    93,    94,    95,    96,    97,    98,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,
      -1,     7,    -1,    -1,    -1,    11,    12,   116,   117,   118,
      16,    -1,    18,    19,    20,    21,    22,    23,    24,    -1,
      -1,    -1,    -1,    29,    30,    31,    32,    33,    34,    35,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    45,
      -1,    -1,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    -1,    59,    60,    -1,    62,    63,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    82,    -1,    -1,    85,
      86,    -1,    88,    89,    -1,    91,    -1,    93,    94,    95,
      96,    97,    98,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       3,     4,     5,    -1,     7,    -1,    -1,    -1,    11,    12,
     116,   117,   118,    16,    -1,    18,    19,    20,    21,    22,
      23,    24,    -1,    -1,    -1,    -1,    29,    30,    31,    32,
      33,    34,    35,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    45,    -1,    -1,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    -1,    59,    60,    -1,    62,
      63,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    82,
      -1,    -1,    85,    86,    -1,    88,    89,    -1,    91,    -1,
      93,    94,    95,    96,    97,    98,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     3,     4,     5,    -1,     7,    -1,    -1,
      -1,    11,    12,   116,   117,   118,    16,    -1,    18,    19,
      20,    21,    22,    23,    24,    -1,    -1,    -1,    -1,    29,
      30,    31,    32,    33,    34,    35,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    45,    -1,    -1,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    -1,    59,
      60,    -1,    62,    63,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    82,    -1,    -1,    85,    86,    -1,    88,    89,
      -1,    91,    -1,    93,    94,    95,    96,    97,    98,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,    -1,
       7,    -1,    -1,    -1,    11,    12,   116,   117,   118,    16,
      -1,    18,    19,    20,    21,    22,    23,    24,    -1,    -1,
      -1,    -1,    29,    30,    31,    32,    33,    34,    35,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    45,    -1,
      -1,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    -1,    59,    60,    -1,    62,    63,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    82,    -1,    -1,    85,    86,
      -1,    88,    89,    -1,    -1,    -1,    93,    94,    95,    96,
      97,    98,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,
       4,     5,    -1,     7,    -1,    -1,    -1,    11,    12,   116,
     117,   118,    16,    -1,    18,    19,    20,    21,    22,    23,
      24,    -1,    -1,    -1,    -1,    29,    30,    31,    32,    33,
      34,    35,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    45,    -1,    -1,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    -1,    59,    60,    -1,    62,    63,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    82,    -1,
      -1,    85,    86,    -1,    88,    89,    -1,    -1,    -1,    93,
      94,    95,    96,    97,    98,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     3,     4,     5,    -1,     7,    -1,    -1,    -1,
      11,    12,   116,   117,   118,    16,    -1,    18,    19,    20,
      21,    22,    23,    24,    -1,    -1,    -1,    -1,    29,    30,
      31,    32,    33,    34,    35,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    45,    -1,    -1,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    -1,    59,    60,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    82,    -1,    -1,    85,    86,    -1,    88,    89,    -1,
      91,    -1,    93,    94,    95,    96,    97,    98,    -1,    -1,
      -1,     3,     4,     5,    -1,     7,    -1,   108,    -1,    11,
      12,    -1,    -1,    -1,    16,   116,    18,    19,    20,    21,
      22,    23,    24,    -1,    -1,    -1,    -1,    29,    30,    31,
      32,    33,    34,    35,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    45,    -1,    -1,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    -1,    59,    60,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    79,    -1,    -1,
      82,    -1,    -1,    85,    86,    -1,    88,    89,    -1,    -1,
      -1,    93,    94,    95,    96,    97,    98,    -1,    -1,    -1,
       3,     4,     5,    -1,     7,    -1,    -1,    -1,    11,    12,
      -1,    -1,    -1,    16,   116,    18,    19,    20,    21,    22,
      23,    24,    -1,    -1,    -1,    -1,    29,    30,    31,    32,
      33,    34,    35,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    45,    -1,    -1,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    -1,    59,    60,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    82,
      -1,    -1,    85,    86,    -1,    88,    89,    -1,    91,    -1,
      93,    94,    95,    96,    97,    98,    -1,    -1,    -1,     3,
       4,     5,    -1,     7,    -1,    -1,    -1,    11,    12,    -1,
      -1,    -1,    16,   116,    18,    19,    20,    21,    22,    23,
      24,    -1,    -1,    -1,    -1,    29,    30,    31,    32,    33,
      34,    35,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    45,    -1,    -1,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    -1,    59,    60,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    82,    -1,
      -1,    85,    86,    -1,    88,    89,    -1,    91,    -1,    93,
      94,    95,    96,    97,    98,    -1,    -1,    -1,     3,     4,
       5,    -1,     7,    -1,    -1,    -1,    11,    12,    -1,    -1,
      -1,    16,   116,    18,    19,    20,    21,    22,    23,    24,
      -1,    -1,    -1,    -1,    29,    30,    31,    32,    33,    34,
      35,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      45,    -1,    -1,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    -1,    59,    60,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    82,    -1,    -1,
      85,    86,    -1,    88,    89,    -1,    -1,    -1,    93,    94,
      95,    96,    97,    98,    -1,    -1,    -1,     3,     4,     5,
      -1,     7,    -1,    -1,    -1,    11,    12,    -1,    -1,    -1,
      16,   116,    18,    19,    20,    21,    22,    23,    24,    -1,
      -1,    -1,    -1,    29,    30,    31,    32,    33,    34,    35,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    45,
      -1,    -1,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    -1,    59,    60,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    82,    -1,    -1,    85,
      86,    -1,    88,    89,    -1,    -1,    -1,    93,    94,    95,
      96,    97,    98,    -1,    -1,    -1,     3,     4,     5,    -1,
       7,    -1,    -1,    -1,    11,    12,    -1,    -1,    -1,    16,
     116,    18,    19,    20,    21,    22,    23,    24,    -1,    -1,
      -1,    -1,    29,    30,    31,    32,    33,    34,    35,    -1,
      -1,    -1,    -1,    43,    -1,    -1,    -1,    -1,    45,    -1,
      -1,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    -1,    59,    60,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    -1,    -1,    79,
      80,    -1,    -1,    -1,    -1,    82,    -1,    -1,    85,    86,
      -1,    88,    89,    -1,    -1,    -1,    93,    94,    95,    96,
      97,    98,    -1,    -1,   104,    -1,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,    50,    51,    -1,   116,
      54,    -1,    -1,    -1,    -1,    -1,   126,    -1,    62,    63,
      64,    65,    66,    67,    -1,    69,    70,    -1,    -1,    73,
      -1,    -1,    -1,    77,    78,    79,    80,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    91,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,    50,    51,   118,    -1,    54,    -1,    -1,    -1,
      -1,    -1,    -1,   127,    62,    63,    64,    65,    66,    67,
      -1,    69,    70,    -1,    -1,    73,    -1,    -1,    -1,    77,
      78,    79,    80,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    91,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,    50,    51,
     118,    -1,    54,    -1,    -1,    -1,    -1,    -1,    -1,   127,
      62,    63,    64,    65,    66,    67,    -1,    69,    70,    -1,
      -1,    73,    -1,    -1,    -1,    77,    78,    79,    80,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    91,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,    50,    51,   118,    -1,    54,    -1,
      -1,    -1,    -1,    -1,    -1,   127,    62,    63,    64,    65,
      66,    67,    -1,    69,    70,    -1,    -1,    73,    -1,    -1,
      -1,    77,    78,    79,    80,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    91,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
      50,    51,   118,    -1,    54,    -1,    -1,    -1,    -1,    -1,
      -1,   127,    62,    63,    64,    65,    66,    67,    -1,    69,
      70,    -1,    -1,    73,    -1,    -1,    -1,    77,    78,    79,
      80,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    91,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,    50,    51,   118,    -1,
      54,    -1,    -1,    -1,    -1,    -1,    -1,   127,    62,    63,
      64,    65,    66,    67,    -1,    69,    70,    -1,    -1,    73,
      -1,    -1,    -1,    77,    78,    79,    80,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    91,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,    50,    51,   118,    -1,    54,    -1,    -1,    -1,
      -1,    -1,    -1,   127,    62,    63,    64,    65,    66,    67,
      -1,    69,    70,    -1,    -1,    73,    -1,    -1,    -1,    77,
      78,    79,    80,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    91,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,    50,    51,
     118,    -1,    54,    -1,    -1,    -1,    -1,    -1,    -1,   127,
      62,    63,    64,    65,    66,    67,    -1,    69,    70,    -1,
      -1,    73,    -1,    -1,    -1,    77,    78,    79,    80,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    91,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,    50,    51,   118,    -1,    54,    -1,
      -1,    -1,    -1,    -1,    -1,   127,    62,    63,    64,    65,
      66,    67,    -1,    69,    70,    -1,    -1,    73,    -1,    -1,
      -1,    77,    78,    79,    80,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    91,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
      50,    51,   118,    -1,    54,    -1,    -1,    -1,    -1,    -1,
      -1,   127,    62,    63,    64,    65,    66,    67,    -1,    69,
      70,    -1,    -1,    73,    -1,    -1,    -1,    77,    78,    79,
      80,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    91,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,    50,    51,   118,    -1,
      54,    -1,    -1,    -1,    -1,    -1,    -1,   127,    62,    63,
      64,    65,    66,    67,    -1,    69,    70,    -1,    -1,    73,
      -1,    -1,    -1,    77,    78,    79,    80,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    91,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,    50,    51,   118,    -1,    54,    -1,    -1,    -1,
      -1,    -1,    -1,   127,    62,    63,    64,    65,    66,    67,
      -1,    69,    70,    -1,    -1,    73,    -1,    -1,    -1,    77,
      78,    79,    80,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    91,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,    -1,    -1,
     118,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   127,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    -1,    -1,    79,    80,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     104,    -1,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    -1,   130,    79,    80,    -1,
      -1,    -1,    84,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    -1,    -1,    79,    80,
      -1,    -1,   104,    -1,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   104,   126,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   126,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    -1,
      -1,    79,    80,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    -1,    -1,    79,    80,
      -1,    -1,    -1,    -1,    -1,    -1,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,    -1,    -1,
      -1,    -1,    -1,   104,    -1,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    -1,    -1,
      79,    80,    64,    65,    66,    67,    68,    69,    70,    71,
      -1,    73,    74,    -1,    -1,    -1,    -1,    79,    80,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,    64,    65,    66,    67,    68,    69,
      70,    -1,    -1,    73,    74,    -1,    -1,    -1,    -1,    79,
      80,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115
};
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "/usr/share/bison/bison.simple"

/* Skeleton output parser for bison,

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002 Free Software
   Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* This is the parser code that is written into each bison parser when
   the %semantic_parser declaration is not specified in the grammar.
   It was written by Richard Stallman by simplifying the hairy parser
   used when %semantic_parser is specified.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

#if ! defined (yyoverflow) || defined (YYERROR_VERBOSE)

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# if YYSTACK_USE_ALLOCA
#  define YYSTACK_ALLOC alloca
# else
#  ifndef YYSTACK_USE_ALLOCA
#   if defined (alloca) || defined (_ALLOCA_H)
#    define YYSTACK_ALLOC alloca
#   else
#    ifdef __GNUC__
#     define YYSTACK_ALLOC __builtin_alloca
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning. */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
# else
#  if defined (__STDC__) || defined (__cplusplus)
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   define YYSIZE_T size_t
#  endif
#  define YYSTACK_ALLOC malloc
#  define YYSTACK_FREE free
# endif
#endif /* ! defined (yyoverflow) || defined (YYERROR_VERBOSE) */


#if (! defined (yyoverflow) \
     && (! defined (__cplusplus) \
	 || (YYLTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short yyss;
  YYSTYPE yyvs;
# if YYLSP_NEEDED
  YYLTYPE yyls;
# endif
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAX (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# if YYLSP_NEEDED
#  define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE) + sizeof (YYLTYPE))	\
      + 2 * YYSTACK_GAP_MAX)
# else
#  define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE))				\
      + YYSTACK_GAP_MAX)
# endif

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  register YYSIZE_T yyi;		\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (0)
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAX;	\
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (0)

#endif


#if ! defined (YYSIZE_T) && defined (__SIZE_TYPE__)
# define YYSIZE_T __SIZE_TYPE__
#endif
#if ! defined (YYSIZE_T) && defined (size_t)
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T)
# if defined (__STDC__) || defined (__cplusplus)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# endif
#endif
#if ! defined (YYSIZE_T)
# define YYSIZE_T unsigned int
#endif

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0
#define YYACCEPT	goto yyacceptlab
#define YYABORT 	goto yyabortlab
#define YYERROR		goto yyerrlab1
/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */
#define YYFAIL		goto yyerrlab
#define YYRECOVERING()  (!!yyerrstatus)
#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yychar1 = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { 								\
      yyerror ("syntax error: cannot back up");			\
      YYERROR;							\
    }								\
while (0)

#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Compute the default location (before the actions
   are run).

   When YYLLOC_DEFAULT is run, CURRENT is set the location of the
   first token.  By default, to implement support for ranges, extend
   its range to the last symbol.  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)       	\
   Current.last_line   = Rhs[N].last_line;	\
   Current.last_column = Rhs[N].last_column;
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#if YYPURE
# if YYLSP_NEEDED
#  ifdef YYLEX_PARAM
#   define YYLEX		yylex (&yylval, &yylloc, YYLEX_PARAM)
#  else
#   define YYLEX		yylex (&yylval, &yylloc)
#  endif
# else /* !YYLSP_NEEDED */
#  ifdef YYLEX_PARAM
#   define YYLEX		yylex (&yylval, YYLEX_PARAM)
#  else
#   define YYLEX		yylex (&yylval)
#  endif
# endif /* !YYLSP_NEEDED */
#else /* !YYPURE */
# define YYLEX			yylex ()
#endif /* !YYPURE */


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (0)
/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
#endif /* !YYDEBUG */

/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   SIZE_MAX < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#if YYMAXDEPTH == 0
# undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif

#ifdef YYERROR_VERBOSE

# ifndef yystrlen
#  if defined (__GLIBC__) && defined (_STRING_H)
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
#   if defined (__STDC__) || defined (__cplusplus)
yystrlen (const char *yystr)
#   else
yystrlen (yystr)
     const char *yystr;
#   endif
{
  register const char *yys = yystr;

  while (*yys++ != '\0')
    continue;

  return yys - yystr - 1;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined (__GLIBC__) && defined (_STRING_H) && defined (_GNU_SOURCE)
#   include <string.h>
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
#   if defined (__STDC__) || defined (__cplusplus)
yystpcpy (char *yydest, const char *yysrc)
#   else
yystpcpy (yydest, yysrc)
     char *yydest;
     const char *yysrc;
#   endif
{
  register char *yyd = yydest;
  register const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif
#endif

#line 316 "/usr/share/bison/bison.simple"


/* The user can define YYPARSE_PARAM as the name of an argument to be passed
   into yyparse.  The argument should have type void *.
   It should actually point to an object.
   Grammar actions can access the variable by casting it
   to the proper pointer type.  */

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
#  define YYPARSE_PARAM_ARG void *YYPARSE_PARAM
#  define YYPARSE_PARAM_DECL
# else
#  define YYPARSE_PARAM_ARG YYPARSE_PARAM
#  define YYPARSE_PARAM_DECL void *YYPARSE_PARAM;
# endif
#else /* !YYPARSE_PARAM */
# define YYPARSE_PARAM_ARG
# define YYPARSE_PARAM_DECL
#endif /* !YYPARSE_PARAM */

/* Prevent warning if -Wstrict-prototypes.  */
#ifdef __GNUC__
# ifdef YYPARSE_PARAM
int yyparse (void *);
# else
int yyparse (void);
# endif
#endif

/* YY_DECL_VARIABLES -- depending whether we use a pure parser,
   variables are global, or local to YYPARSE.  */

#define YY_DECL_NON_LSP_VARIABLES			\
/* The lookahead symbol.  */				\
int yychar;						\
							\
/* The semantic value of the lookahead symbol. */	\
YYSTYPE yylval;						\
							\
/* Number of parse errors so far.  */			\
int yynerrs;

#if YYLSP_NEEDED
# define YY_DECL_VARIABLES			\
YY_DECL_NON_LSP_VARIABLES			\
						\
/* Location data for the lookahead symbol.  */	\
YYLTYPE yylloc;
#else
# define YY_DECL_VARIABLES			\
YY_DECL_NON_LSP_VARIABLES
#endif


/* If nonreentrant, generate the variables here. */

#if !YYPURE
YY_DECL_VARIABLES
#endif  /* !YYPURE */

int
yyparse (YYPARSE_PARAM_ARG)
     YYPARSE_PARAM_DECL
{
  /* If reentrant, generate the variables here. */
#if YYPURE
  YY_DECL_VARIABLES
#endif  /* !YYPURE */

  register int yystate;
  register int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Lookahead token as an internal (translated) token number.  */
  int yychar1 = 0;

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack. */
  short	yyssa[YYINITDEPTH];
  short *yyss = yyssa;
  register short *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  register YYSTYPE *yyvsp;

#if YYLSP_NEEDED
  /* The location stack.  */
  YYLTYPE yylsa[YYINITDEPTH];
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;
#endif

#if YYLSP_NEEDED
# define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
# define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

  YYSIZE_T yystacksize = YYINITDEPTH;


  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
#if YYLSP_NEEDED
  YYLTYPE yyloc;
#endif

  /* When reducing, the number of symbols on the RHS of the reduced
     rule. */
  int yylen;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;
#if YYLSP_NEEDED
  yylsp = yyls;
#endif
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed. so pushing a state here evens the stacks.
     */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyssp >= yyss + yystacksize - 1)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack. Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	short *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  */
# if YYLSP_NEEDED
	YYLTYPE *yyls1 = yyls;
	/* This used to be a conditional around just the two extra args,
	   but that might be undefined if yyoverflow is a macro.  */
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);
	yyls = yyls1;
# else
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);
# endif
	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyoverflowlab;
# else
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	goto yyoverflowlab;
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;

      {
	short *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyoverflowlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);
# if YYLSP_NEEDED
	YYSTACK_RELOCATE (yyls);
# endif
# undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
#if YYLSP_NEEDED
      yylsp = yyls + yysize - 1;
#endif

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyssp >= yyss + yystacksize - 1)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (yychar <= 0)		/* This means end of input. */
    {
      yychar1 = 0;
      yychar = YYEOF;		/* Don't call YYLEX any more */

      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yychar1 = YYTRANSLATE (yychar);

#if YYDEBUG
     /* We have to keep this `#if YYDEBUG', since we use variables
	which are defined only if `YYDEBUG' is set.  */
      if (yydebug)
	{
	  YYFPRINTF (stderr, "Next token is %d (%s",
		     yychar, yytname[yychar1]);
	  /* Give the individual parser a way to print the precise
	     meaning of a token, for further debugging info.  */
# ifdef YYPRINT
	  YYPRINT (stderr, yychar, yylval);
# endif
	  YYFPRINTF (stderr, ")\n");
	}
#endif
    }

  yyn += yychar1;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
    goto yydefault;

  yyn = yytable[yyn];

  /* yyn is what to do for this token type in this state.
     Negative => reduce, -yyn is rule number.
     Positive => shift, yyn is new state.
       New state is final state => don't bother to shift,
       just return success.
     0, or most negative number => error.  */

  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrlab;

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */
  YYDPRINTF ((stderr, "Shifting token %d (%s), ",
	      yychar, yytname[yychar1]));

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
#if YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  yystate = yyn;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to the semantic value of
     the lookahead token.  This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

#if YYLSP_NEEDED
  /* Similarly for the default location.  Let the user run additional
     commands if for instance locations are ranges.  */
  yyloc = yylsp[1-yylen];
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
#endif

#if YYDEBUG
  /* We have to keep this `#if YYDEBUG', since we use variables which
     are defined only if `YYDEBUG' is set.  */
  if (yydebug)
    {
      int yyi;

      YYFPRINTF (stderr, "Reducing via rule %d (line %d), ",
		 yyn, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (yyi = yyprhs[yyn]; yyrhs[yyi] > 0; yyi++)
	YYFPRINTF (stderr, "%s ", yytname[yyrhs[yyi]]);
      YYFPRINTF (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif

  switch (yyn) {

case 1:
#line 345 "parse.y"
{
			lex_state = EXPR_BEG;
                        top_local_init();
			if (ruby_class == rb_cObject) class_nest = 0;
			else class_nest = 1;
		    }
    break;
case 2:
#line 352 "parse.y"
{
			if (yyvsp[0].node && !compile_for_eval) {
                            /* last expression should not be void */
			    if (nd_type(yyvsp[0].node) != NODE_BLOCK) void_expr(yyvsp[0].node);
			    else {
				NODE *node = yyvsp[0].node;
				while (node->nd_next) {
				    node = node->nd_next;
				}
				void_expr(node->nd_head);
			    }
			}
			ruby_eval_tree = block_append(ruby_eval_tree, yyvsp[0].node);
                        top_local_setup();
			class_nest = 0;
		    }
    break;
case 3:
#line 374 "parse.y"
{
		        yyval.node = yyvsp[-3].node;
			if (yyvsp[-2].node) {
			    yyval.node = NEW_RESCUE(yyvsp[-3].node, yyvsp[-2].node, yyvsp[-1].node);
			}
			else if (yyvsp[-1].node) {
			    rb_warn("else without rescue is useless");
			    yyval.node = block_append(yyval.node, yyvsp[-1].node);
			}
			if (yyvsp[0].node) {
			    yyval.node = NEW_ENSURE(yyval.node, yyvsp[0].node);
			}
			fixpos(yyval.node, yyvsp[-3].node);
		    }
    break;
case 4:
#line 391 "parse.y"
{
			void_stmts(yyvsp[-1].node);
		        yyval.node = yyvsp[-1].node;
		    }
    break;
case 6:
#line 399 "parse.y"
{
			yyval.node = newline_node(yyvsp[0].node);
		    }
    break;
case 7:
#line 403 "parse.y"
{
			yyval.node = block_append(yyvsp[-2].node, newline_node(yyvsp[0].node));
		    }
    break;
case 8:
#line 407 "parse.y"
{
			yyval.node = yyvsp[0].node;
		    }
    break;
case 9:
#line 412 "parse.y"
{lex_state = EXPR_FNAME;}
    break;
case 10:
#line 413 "parse.y"
{
		        yyval.node = NEW_ALIAS(yyvsp[-2].id, yyvsp[0].id);
		    }
    break;
case 11:
#line 417 "parse.y"
{
		        yyval.node = NEW_VALIAS(yyvsp[-1].id, yyvsp[0].id);
		    }
    break;
case 12:
#line 421 "parse.y"
{
			char buf[3];

			sprintf(buf, "$%c", (char)yyvsp[0].node->nd_nth);
		        yyval.node = NEW_VALIAS(yyvsp[-1].id, rb_intern(buf));
		    }
    break;
case 13:
#line 428 "parse.y"
{
		        yyerror("can't make alias for the number variables");
		        yyval.node = 0;
		    }
    break;
case 14:
#line 433 "parse.y"
{
			yyval.node = yyvsp[0].node;
		    }
    break;
case 15:
#line 437 "parse.y"
{
			yyval.node = NEW_IF(cond(yyvsp[0].node), yyvsp[-2].node, 0);
		        fixpos(yyval.node, yyvsp[0].node);
			if (cond_negative(&yyval.node->nd_cond)) {
		            yyval.node->nd_else = yyval.node->nd_body;
		            yyval.node->nd_body = 0;
			}
		    }
    break;
case 16:
#line 446 "parse.y"
{
			yyval.node = NEW_UNLESS(cond(yyvsp[0].node), yyvsp[-2].node, 0);
		        fixpos(yyval.node, yyvsp[0].node);
			if (cond_negative(&yyval.node->nd_cond)) {
		            yyval.node->nd_body = yyval.node->nd_else;
		            yyval.node->nd_else = 0;
			}
		    }
    break;
case 17:
#line 455 "parse.y"
{
			if (yyvsp[-2].node && nd_type(yyvsp[-2].node) == NODE_BEGIN) {
			    yyval.node = NEW_WHILE(cond(yyvsp[0].node), yyvsp[-2].node->nd_body, 0);
			}
			else {
			    yyval.node = NEW_WHILE(cond(yyvsp[0].node), yyvsp[-2].node, 1);
			}
			if (cond_negative(&yyval.node->nd_cond)) {
			    nd_set_type(yyval.node, NODE_UNTIL);
			}
		    }
    break;
case 18:
#line 467 "parse.y"
{
			if (yyvsp[-2].node && nd_type(yyvsp[-2].node) == NODE_BEGIN) {
			    yyval.node = NEW_UNTIL(cond(yyvsp[0].node), yyvsp[-2].node->nd_body, 0);
			}
			else {
			    yyval.node = NEW_UNTIL(cond(yyvsp[0].node), yyvsp[-2].node, 1);
			}
			if (cond_negative(&yyval.node->nd_cond)) {
			    nd_set_type(yyval.node, NODE_WHILE);
			}
		    }
    break;
case 19:
#line 479 "parse.y"
{
			yyval.node = NEW_RESCUE(yyvsp[-2].node, NEW_RESBODY(0,yyvsp[0].node,0), 0);
		    }
    break;
case 20:
#line 483 "parse.y"
{
			if (in_def || in_single) {
			    yyerror("BEGIN in method");
			}
			local_push(0);
		    }
    break;
case 21:
#line 490 "parse.y"
{
			ruby_eval_tree_begin = block_append(ruby_eval_tree_begin,
						            NEW_PREEXE(yyvsp[-1].node));
		        local_pop();
		        yyval.node = 0;
		    }
    break;
case 22:
#line 497 "parse.y"
{
			if (in_def || in_single) {
			    rb_warn("END in method; use at_exit");
			}

			yyval.node = NEW_ITER(0, NEW_POSTEXE(), yyvsp[-1].node);
		    }
    break;
case 23:
#line 505 "parse.y"
{
			yyval.node = node_assign(yyvsp[-2].node, yyvsp[0].node);
		    }
    break;
case 24:
#line 509 "parse.y"
{
			value_expr(yyvsp[0].node);
			yyvsp[-2].node->nd_value = (yyvsp[-2].node->nd_head) ? NEW_TO_ARY(yyvsp[0].node) : NEW_ARRAY(yyvsp[0].node);
			yyval.node = yyvsp[-2].node;
		    }
    break;
case 25:
#line 515 "parse.y"
{
			value_expr(yyvsp[0].node);
			if (yyvsp[-2].node) {
			    ID vid = yyvsp[-2].node->nd_vid;
			    if (yyvsp[-1].id == tOROP) {
				yyvsp[-2].node->nd_value = yyvsp[0].node;
				yyval.node = NEW_OP_ASGN_OR(gettable(vid), yyvsp[-2].node);
				if (is_asgn_or_id(vid)) {
				    yyval.node->nd_aid = vid;
				}
			    }
			    else if (yyvsp[-1].id == tANDOP) {
				yyvsp[-2].node->nd_value = yyvsp[0].node;
				yyval.node = NEW_OP_ASGN_AND(gettable(vid), yyvsp[-2].node);
			    }
			    else {
				yyval.node = yyvsp[-2].node;
				yyval.node->nd_value = call_op(gettable(vid),yyvsp[-1].id,1,yyvsp[0].node);
			    }
			}
			else {
			    yyval.node = 0;
			}
		    }
    break;
case 26:
#line 540 "parse.y"
{
                        NODE *args;

			value_expr(yyvsp[0].node);
		        args = NEW_LIST(yyvsp[0].node);
			if (yyvsp[-3].node && nd_type(yyvsp[-3].node) != NODE_ARRAY)
			    yyvsp[-3].node = NEW_LIST(yyvsp[-3].node);
			yyvsp[-3].node = list_append(yyvsp[-3].node, NEW_NIL());
			list_concat(args, yyvsp[-3].node);
			if (yyvsp[-1].id == tOROP) {
			    yyvsp[-1].id = 0;
			}
			else if (yyvsp[-1].id == tANDOP) {
			    yyvsp[-1].id = 1;
			}
			yyval.node = NEW_OP_ASGN1(yyvsp[-5].node, yyvsp[-1].id, args);
		        fixpos(yyval.node, yyvsp[-5].node);
		    }
    break;
case 27:
#line 559 "parse.y"
{
			value_expr(yyvsp[0].node);
			if (yyvsp[-1].id == tOROP) {
			    yyvsp[-1].id = 0;
			}
			else if (yyvsp[-1].id == tANDOP) {
			    yyvsp[-1].id = 1;
			}
			yyval.node = NEW_OP_ASGN2(yyvsp[-4].node, yyvsp[-2].id, yyvsp[-1].id, yyvsp[0].node);
		        fixpos(yyval.node, yyvsp[-4].node);
		    }
    break;
case 28:
#line 571 "parse.y"
{
			value_expr(yyvsp[0].node);
			if (yyvsp[-1].id == tOROP) {
			    yyvsp[-1].id = 0;
			}
			else if (yyvsp[-1].id == tANDOP) {
			    yyvsp[-1].id = 1;
			}
			yyval.node = NEW_OP_ASGN2(yyvsp[-4].node, yyvsp[-2].id, yyvsp[-1].id, yyvsp[0].node);
		        fixpos(yyval.node, yyvsp[-4].node);
		    }
    break;
case 29:
#line 583 "parse.y"
{
			value_expr(yyvsp[0].node);
			if (yyvsp[-1].id == tOROP) {
			    yyvsp[-1].id = 0;
			}
			else if (yyvsp[-1].id == tANDOP) {
			    yyvsp[-1].id = 1;
			}
			yyval.node = NEW_OP_ASGN2(yyvsp[-4].node, yyvsp[-2].id, yyvsp[-1].id, yyvsp[0].node);
		        fixpos(yyval.node, yyvsp[-4].node);
		    }
    break;
case 30:
#line 595 "parse.y"
{
		        rb_backref_error(yyvsp[-2].node);
			yyval.node = 0;
		    }
    break;
case 31:
#line 600 "parse.y"
{
			yyval.node = node_assign(yyvsp[-2].node, NEW_SVALUE(yyvsp[0].node));
		    }
    break;
case 32:
#line 604 "parse.y"
{
			yyvsp[-2].node->nd_value = (yyvsp[-2].node->nd_head) ? NEW_TO_ARY(yyvsp[0].node) : NEW_ARRAY(yyvsp[0].node);
			yyval.node = yyvsp[-2].node;
		    }
    break;
case 33:
#line 609 "parse.y"
{
			yyvsp[-2].node->nd_value = yyvsp[0].node;
			yyval.node = yyvsp[-2].node;
		    }
    break;
case 36:
#line 618 "parse.y"
{
			yyval.node = logop(NODE_AND, yyvsp[-2].node, yyvsp[0].node);
		    }
    break;
case 37:
#line 622 "parse.y"
{
			yyval.node = logop(NODE_OR, yyvsp[-2].node, yyvsp[0].node);
		    }
    break;
case 38:
#line 626 "parse.y"
{
			yyval.node = NEW_NOT(cond(yyvsp[0].node));
		    }
    break;
case 39:
#line 630 "parse.y"
{
			yyval.node = NEW_NOT(cond(yyvsp[0].node));
		    }
    break;
case 41:
#line 637 "parse.y"
{
			value_expr(yyval.node);
			yyval.node = yyvsp[0].node;
		    }
    break;
case 44:
#line 646 "parse.y"
{
			yyval.node = NEW_RETURN(ret_args(yyvsp[0].node));
		    }
    break;
case 45:
#line 650 "parse.y"
{
			yyval.node = NEW_BREAK(ret_args(yyvsp[0].node));
		    }
    break;
case 46:
#line 654 "parse.y"
{
			yyval.node = NEW_NEXT(ret_args(yyvsp[0].node));
		    }
    break;
case 48:
#line 661 "parse.y"
{
			yyval.node = new_call(yyvsp[-3].node, yyvsp[-1].id, yyvsp[0].node);
		    }
    break;
case 49:
#line 665 "parse.y"
{
			yyval.node = new_call(yyvsp[-3].node, yyvsp[-1].id, yyvsp[0].node);
		    }
    break;
case 50:
#line 671 "parse.y"
{
			yyval.vars = dyna_push();
			yyvsp[0].num = ruby_sourceline;
		    }
    break;
case 51:
#line 675 "parse.y"
{yyval.vars = ruby_dyna_vars;}
    break;
case 52:
#line 678 "parse.y"
{
			yyval.node = NEW_ITER(yyvsp[-3].node, 0, dyna_init(yyvsp[-1].node, yyvsp[-2].vars));
			nd_set_line(yyval.node, yyvsp[-5].num);
			dyna_pop(yyvsp[-4].vars);
		    }
    break;
case 53:
#line 686 "parse.y"
{
			yyval.node = new_fcall(yyvsp[-1].id, yyvsp[0].node);
		        fixpos(yyval.node, yyvsp[0].node);
		   }
    break;
case 54:
#line 691 "parse.y"
{
			yyval.node = new_fcall(yyvsp[-2].id, yyvsp[-1].node);
			if (yyvsp[0].node) {
			    if (nd_type(yyval.node) == NODE_BLOCK_PASS) {
				rb_compile_error("both block arg and actual block given");
			    }
			    yyvsp[0].node->nd_iter = yyval.node;
			    yyval.node = yyvsp[0].node;
			}
		        fixpos(yyval.node, yyvsp[-1].node);
		   }
    break;
case 55:
#line 703 "parse.y"
{
			yyval.node = new_call(yyvsp[-3].node, yyvsp[-1].id, yyvsp[0].node);
		        fixpos(yyval.node, yyvsp[-3].node);
		    }
    break;
case 56:
#line 708 "parse.y"
{
			yyval.node = new_call(yyvsp[-4].node, yyvsp[-2].id, yyvsp[-1].node);
			if (yyvsp[0].node) {
			    if (nd_type(yyval.node) == NODE_BLOCK_PASS) {
				rb_compile_error("both block arg and actual block given");
			    }
			    yyvsp[0].node->nd_iter = yyval.node;
			    yyval.node = yyvsp[0].node;
			}
		        fixpos(yyval.node, yyvsp[-4].node);
		   }
    break;
case 57:
#line 720 "parse.y"
{
			yyval.node = new_call(yyvsp[-3].node, yyvsp[-1].id, yyvsp[0].node);
		        fixpos(yyval.node, yyvsp[-3].node);
		    }
    break;
case 58:
#line 725 "parse.y"
{
			yyval.node = new_call(yyvsp[-4].node, yyvsp[-2].id, yyvsp[-1].node);
			if (yyvsp[0].node) {
			    if (nd_type(yyval.node) == NODE_BLOCK_PASS) {
				rb_compile_error("both block arg and actual block given");
			    }
			    yyvsp[0].node->nd_iter = yyval.node;
			    yyval.node = yyvsp[0].node;
			}
		        fixpos(yyval.node, yyvsp[-4].node);
		   }
    break;
case 59:
#line 737 "parse.y"
{
			yyval.node = new_super(yyvsp[0].node);
		        fixpos(yyval.node, yyvsp[0].node);
		    }
    break;
case 60:
#line 742 "parse.y"
{
			yyval.node = new_yield(yyvsp[0].node);
		        fixpos(yyval.node, yyvsp[0].node);
		    }
    break;
case 62:
#line 750 "parse.y"
{
			yyval.node = yyvsp[-1].node;
		    }
    break;
case 64:
#line 757 "parse.y"
{
			yyval.node = NEW_MASGN(NEW_LIST(yyvsp[-1].node), 0);
		    }
    break;
case 65:
#line 763 "parse.y"
{
			yyval.node = NEW_MASGN(yyvsp[0].node, 0);
		    }
    break;
case 66:
#line 767 "parse.y"
{
			yyval.node = NEW_MASGN(list_append(yyvsp[-1].node,yyvsp[0].node), 0);
		    }
    break;
case 67:
#line 771 "parse.y"
{
			yyval.node = NEW_MASGN(yyvsp[-2].node, yyvsp[0].node);
		    }
    break;
case 68:
#line 775 "parse.y"
{
			yyval.node = NEW_MASGN(yyvsp[-1].node, -1);
		    }
    break;
case 69:
#line 779 "parse.y"
{
			yyval.node = NEW_MASGN(0, yyvsp[0].node);
		    }
    break;
case 70:
#line 783 "parse.y"
{
			yyval.node = NEW_MASGN(0, -1);
		    }
    break;
case 72:
#line 790 "parse.y"
{
			yyval.node = yyvsp[-1].node;
		    }
    break;
case 73:
#line 796 "parse.y"
{
			yyval.node = NEW_LIST(yyvsp[-1].node);
		    }
    break;
case 74:
#line 800 "parse.y"
{
			yyval.node = list_append(yyvsp[-2].node, yyvsp[-1].node);
		    }
    break;
case 75:
#line 806 "parse.y"
{
			yyval.node = assignable(yyvsp[0].id, 0);
		    }
    break;
case 76:
#line 810 "parse.y"
{
			yyval.node = aryset(yyvsp[-3].node, yyvsp[-1].node);
		    }
    break;
case 77:
#line 814 "parse.y"
{
			yyval.node = attrset(yyvsp[-2].node, yyvsp[0].id);
		    }
    break;
case 78:
#line 818 "parse.y"
{
			yyval.node = attrset(yyvsp[-2].node, yyvsp[0].id);
		    }
    break;
case 79:
#line 822 "parse.y"
{
			yyval.node = attrset(yyvsp[-2].node, yyvsp[0].id);
		    }
    break;
case 80:
#line 826 "parse.y"
{
			if (in_def || in_single)
			    yyerror("dynamic constant assignment");
			yyval.node = NEW_CDECL(0, 0, NEW_COLON2(yyvsp[-2].node, yyvsp[0].id));
		    }
    break;
case 81:
#line 832 "parse.y"
{
			if (in_def || in_single)
			    yyerror("dynamic constant assignment");
			yyval.node = NEW_CDECL(0, 0, NEW_COLON3(yyvsp[0].id));
		    }
    break;
case 82:
#line 838 "parse.y"
{
		        rb_backref_error(yyvsp[0].node);
			yyval.node = 0;
		    }
    break;
case 83:
#line 845 "parse.y"
{
			yyval.node = assignable(yyvsp[0].id, 0);
		    }
    break;
case 84:
#line 849 "parse.y"
{
			yyval.node = aryset(yyvsp[-3].node, yyvsp[-1].node);
		    }
    break;
case 85:
#line 853 "parse.y"
{
			yyval.node = attrset(yyvsp[-2].node, yyvsp[0].id);
		    }
    break;
case 86:
#line 857 "parse.y"
{
			yyval.node = attrset(yyvsp[-2].node, yyvsp[0].id);
		    }
    break;
case 87:
#line 861 "parse.y"
{
			yyval.node = attrset(yyvsp[-2].node, yyvsp[0].id);
		    }
    break;
case 88:
#line 865 "parse.y"
{
			if (in_def || in_single)
			    yyerror("dynamic constant assignment");
			yyval.node = NEW_CDECL(0, 0, NEW_COLON2(yyvsp[-2].node, yyvsp[0].id));
		    }
    break;
case 89:
#line 871 "parse.y"
{
			if (in_def || in_single)
			    yyerror("dynamic constant assignment");
			yyval.node = NEW_CDECL(0, 0, NEW_COLON3(yyvsp[0].id));
		    }
    break;
case 90:
#line 877 "parse.y"
{
		        rb_backref_error(yyvsp[0].node);
			yyval.node = 0;
		    }
    break;
case 91:
#line 884 "parse.y"
{
			yyerror("class/module name must be CONSTANT");
		    }
    break;
case 93:
#line 891 "parse.y"
{
			yyval.node = NEW_COLON3(yyvsp[0].id);
		    }
    break;
case 94:
#line 895 "parse.y"
{
			yyval.node = NEW_COLON2(0, yyval.node);
		    }
    break;
case 95:
#line 899 "parse.y"
{
			yyval.node = NEW_COLON2(yyvsp[-2].node, yyvsp[0].id);
		    }
    break;
case 99:
#line 908 "parse.y"
{
			lex_state = EXPR_END;
			yyval.id = yyvsp[0].id;
		    }
    break;
case 100:
#line 913 "parse.y"
{
			lex_state = EXPR_END;
			yyval.id = yyvsp[0].id;
		    }
    break;
case 103:
#line 924 "parse.y"
{
			yyval.node = NEW_UNDEF(yyvsp[0].id);
		    }
    break;
case 104:
#line 927 "parse.y"
{lex_state = EXPR_FNAME;}
    break;
case 105:
#line 928 "parse.y"
{
			yyval.node = block_append(yyvsp[-3].node, NEW_UNDEF(yyvsp[0].id));
		    }
    break;
case 106:
#line 933 "parse.y"
{ yyval.id = '|'; }
    break;
case 107:
#line 934 "parse.y"
{ yyval.id = '^'; }
    break;
case 108:
#line 935 "parse.y"
{ yyval.id = '&'; }
    break;
case 109:
#line 936 "parse.y"
{ yyval.id = tCMP; }
    break;
case 110:
#line 937 "parse.y"
{ yyval.id = tEQ; }
    break;
case 111:
#line 938 "parse.y"
{ yyval.id = tEQQ; }
    break;
case 112:
#line 939 "parse.y"
{ yyval.id = tMATCH; }
    break;
case 113:
#line 940 "parse.y"
{ yyval.id = '>'; }
    break;
case 114:
#line 941 "parse.y"
{ yyval.id = tGEQ; }
    break;
case 115:
#line 942 "parse.y"
{ yyval.id = '<'; }
    break;
case 116:
#line 943 "parse.y"
{ yyval.id = tLEQ; }
    break;
case 117:
#line 944 "parse.y"
{ yyval.id = tLSHFT; }
    break;
case 118:
#line 945 "parse.y"
{ yyval.id = tRSHFT; }
    break;
case 119:
#line 946 "parse.y"
{ yyval.id = '+'; }
    break;
case 120:
#line 947 "parse.y"
{ yyval.id = '-'; }
    break;
case 121:
#line 948 "parse.y"
{ yyval.id = '*'; }
    break;
case 122:
#line 949 "parse.y"
{ yyval.id = '*'; }
    break;
case 123:
#line 950 "parse.y"
{ yyval.id = '/'; }
    break;
case 124:
#line 951 "parse.y"
{ yyval.id = '%'; }
    break;
case 125:
#line 952 "parse.y"
{ yyval.id = tPOW; }
    break;
case 126:
#line 953 "parse.y"
{ yyval.id = '~'; }
    break;
case 127:
#line 954 "parse.y"
{ yyval.id = tUPLUS; }
    break;
case 128:
#line 955 "parse.y"
{ yyval.id = tUMINUS; }
    break;
case 129:
#line 956 "parse.y"
{ yyval.id = tAREF; }
    break;
case 130:
#line 957 "parse.y"
{ yyval.id = tASET; }
    break;
case 131:
#line 958 "parse.y"
{ yyval.id = '`'; }
    break;
case 173:
#line 971 "parse.y"
{
			yyval.node = node_assign(yyvsp[-2].node, yyvsp[0].node);
		    }
    break;
case 174:
#line 975 "parse.y"
{
			yyval.node = node_assign(yyvsp[-4].node, NEW_RESCUE(yyvsp[-2].node, NEW_RESBODY(0,yyvsp[0].node,0), 0));
		    }
    break;
case 175:
#line 979 "parse.y"
{
			value_expr(yyvsp[0].node);
			if (yyvsp[-2].node) {
			    ID vid = yyvsp[-2].node->nd_vid;
			    if (yyvsp[-1].id == tOROP) {
				yyvsp[-2].node->nd_value = yyvsp[0].node;
				yyval.node = NEW_OP_ASGN_OR(gettable(vid), yyvsp[-2].node);
				if (is_asgn_or_id(vid)) {
				    yyval.node->nd_aid = vid;
				}
			    }
			    else if (yyvsp[-1].id == tANDOP) {
				yyvsp[-2].node->nd_value = yyvsp[0].node;
				yyval.node = NEW_OP_ASGN_AND(gettable(vid), yyvsp[-2].node);
			    }
			    else {
				yyval.node = yyvsp[-2].node;
				yyval.node->nd_value = call_op(gettable(vid),yyvsp[-1].id,1,yyvsp[0].node);
			    }
			}
			else {
			    yyval.node = 0;
			}
		    }
    break;
case 176:
#line 1004 "parse.y"
{
                        NODE *args;

			value_expr(yyvsp[0].node);
			args = NEW_LIST(yyvsp[0].node);
			if (yyvsp[-3].node && nd_type(yyvsp[-3].node) != NODE_ARRAY)
			    yyvsp[-3].node = NEW_LIST(yyvsp[-3].node);
			yyvsp[-3].node = list_append(yyvsp[-3].node, NEW_NIL());
			list_concat(args, yyvsp[-3].node);
			if (yyvsp[-1].id == tOROP) {
			    yyvsp[-1].id = 0;
			}
			else if (yyvsp[-1].id == tANDOP) {
			    yyvsp[-1].id = 1;
			}
			yyval.node = NEW_OP_ASGN1(yyvsp[-5].node, yyvsp[-1].id, args);
		        fixpos(yyval.node, yyvsp[-5].node);
		    }
    break;
case 177:
#line 1023 "parse.y"
{
			value_expr(yyvsp[0].node);
			if (yyvsp[-1].id == tOROP) {
			    yyvsp[-1].id = 0;
			}
			else if (yyvsp[-1].id == tANDOP) {
			    yyvsp[-1].id = 1;
			}
			yyval.node = NEW_OP_ASGN2(yyvsp[-4].node, yyvsp[-2].id, yyvsp[-1].id, yyvsp[0].node);
		        fixpos(yyval.node, yyvsp[-4].node);
		    }
    break;
case 178:
#line 1035 "parse.y"
{
			value_expr(yyvsp[0].node);
			if (yyvsp[-1].id == tOROP) {
			    yyvsp[-1].id = 0;
			}
			else if (yyvsp[-1].id == tANDOP) {
			    yyvsp[-1].id = 1;
			}
			yyval.node = NEW_OP_ASGN2(yyvsp[-4].node, yyvsp[-2].id, yyvsp[-1].id, yyvsp[0].node);
		        fixpos(yyval.node, yyvsp[-4].node);
		    }
    break;
case 179:
#line 1047 "parse.y"
{
			value_expr(yyvsp[0].node);
			if (yyvsp[-1].id == tOROP) {
			    yyvsp[-1].id = 0;
			}
			else if (yyvsp[-1].id == tANDOP) {
			    yyvsp[-1].id = 1;
			}
			yyval.node = NEW_OP_ASGN2(yyvsp[-4].node, yyvsp[-2].id, yyvsp[-1].id, yyvsp[0].node);
		        fixpos(yyval.node, yyvsp[-4].node);
		    }
    break;
case 180:
#line 1059 "parse.y"
{
			yyerror("constant re-assignment");
			yyval.node = 0;
		    }
    break;
case 181:
#line 1064 "parse.y"
{
			yyerror("constant re-assignment");
			yyval.node = 0;
		    }
    break;
case 182:
#line 1069 "parse.y"
{
		        rb_backref_error(yyvsp[-2].node);
			yyval.node = 0;
		    }
    break;
case 183:
#line 1074 "parse.y"
{
			value_expr(yyvsp[-2].node);
			value_expr(yyvsp[0].node);
			if (nd_type(yyvsp[-2].node) == NODE_LIT && FIXNUM_P(yyvsp[-2].node->nd_lit) &&
			    nd_type(yyvsp[0].node) == NODE_LIT && FIXNUM_P(yyvsp[0].node->nd_lit)) {
			    yyvsp[-2].node->nd_lit = rb_range_new(yyvsp[-2].node->nd_lit, yyvsp[0].node->nd_lit, Qfalse);
			    yyval.node = yyvsp[-2].node;
			}
			else {
			    yyval.node = NEW_DOT2(yyvsp[-2].node, yyvsp[0].node);
			}
		    }
    break;
case 184:
#line 1087 "parse.y"
{
			value_expr(yyvsp[-2].node);
			value_expr(yyvsp[0].node);
			if (nd_type(yyvsp[-2].node) == NODE_LIT && FIXNUM_P(yyvsp[-2].node->nd_lit) &&
			    nd_type(yyvsp[0].node) == NODE_LIT && FIXNUM_P(yyvsp[0].node->nd_lit)) {
			    yyvsp[-2].node->nd_lit = rb_range_new(yyvsp[-2].node->nd_lit, yyvsp[0].node->nd_lit, Qtrue);
			    yyval.node = yyvsp[-2].node;
			}
			else {
			    yyval.node = NEW_DOT3(yyvsp[-2].node, yyvsp[0].node);
			}
		    }
    break;
case 185:
#line 1100 "parse.y"
{
			yyval.node = call_op(yyvsp[-2].node, '+', 1, yyvsp[0].node);
		    }
    break;
case 186:
#line 1104 "parse.y"
{
		        yyval.node = call_op(yyvsp[-2].node, '-', 1, yyvsp[0].node);
		    }
    break;
case 187:
#line 1108 "parse.y"
{
		        yyval.node = call_op(yyvsp[-2].node, '*', 1, yyvsp[0].node);
		    }
    break;
case 188:
#line 1112 "parse.y"
{
			yyval.node = call_op(yyvsp[-2].node, '/', 1, yyvsp[0].node);
		    }
    break;
case 189:
#line 1116 "parse.y"
{
			yyval.node = call_op(yyvsp[-2].node, '%', 1, yyvsp[0].node);
		    }
    break;
case 190:
#line 1120 "parse.y"
{
			yyval.node = call_op(yyvsp[-2].node, tPOW, 1, yyvsp[0].node);
		    }
    break;
case 191:
#line 1124 "parse.y"
{
			yyval.node = call_op(call_op(yyvsp[-2].node, tPOW, 1, yyvsp[0].node), tUMINUS, 0, 0);
		    }
    break;
case 192:
#line 1128 "parse.y"
{
			yyval.node = call_op(call_op(yyvsp[-2].node, tPOW, 1, yyvsp[0].node), tUMINUS, 0, 0);
		    }
    break;
case 193:
#line 1132 "parse.y"
{
			if (yyvsp[0].node && nd_type(yyvsp[0].node) == NODE_LIT) {
			    yyval.node = yyvsp[0].node;
			}
			else {
			    yyval.node = call_op(yyvsp[0].node, tUPLUS, 0, 0);
			}
		    }
    break;
case 194:
#line 1141 "parse.y"
{
			yyval.node = call_op(yyvsp[0].node, tUMINUS, 0, 0);
		    }
    break;
case 195:
#line 1145 "parse.y"
{
		        yyval.node = call_op(yyvsp[-2].node, '|', 1, yyvsp[0].node);
		    }
    break;
case 196:
#line 1149 "parse.y"
{
			yyval.node = call_op(yyvsp[-2].node, '^', 1, yyvsp[0].node);
		    }
    break;
case 197:
#line 1153 "parse.y"
{
			yyval.node = call_op(yyvsp[-2].node, '&', 1, yyvsp[0].node);
		    }
    break;
case 198:
#line 1157 "parse.y"
{
			yyval.node = call_op(yyvsp[-2].node, tCMP, 1, yyvsp[0].node);
		    }
    break;
case 199:
#line 1161 "parse.y"
{
			yyval.node = call_op(yyvsp[-2].node, '>', 1, yyvsp[0].node);
		    }
    break;
case 200:
#line 1165 "parse.y"
{
			yyval.node = call_op(yyvsp[-2].node, tGEQ, 1, yyvsp[0].node);
		    }
    break;
case 201:
#line 1169 "parse.y"
{
			yyval.node = call_op(yyvsp[-2].node, '<', 1, yyvsp[0].node);
		    }
    break;
case 202:
#line 1173 "parse.y"
{
			yyval.node = call_op(yyvsp[-2].node, tLEQ, 1, yyvsp[0].node);
		    }
    break;
case 203:
#line 1177 "parse.y"
{
			yyval.node = call_op(yyvsp[-2].node, tEQ, 1, yyvsp[0].node);
		    }
    break;
case 204:
#line 1181 "parse.y"
{
			yyval.node = call_op(yyvsp[-2].node, tEQQ, 1, yyvsp[0].node);
		    }
    break;
case 205:
#line 1185 "parse.y"
{
			yyval.node = NEW_NOT(call_op(yyvsp[-2].node, tEQ, 1, yyvsp[0].node));
		    }
    break;
case 206:
#line 1189 "parse.y"
{
			yyval.node = match_gen(yyvsp[-2].node, yyvsp[0].node);
		    }
    break;
case 207:
#line 1193 "parse.y"
{
			yyval.node = NEW_NOT(match_gen(yyvsp[-2].node, yyvsp[0].node));
		    }
    break;
case 208:
#line 1197 "parse.y"
{
			yyval.node = NEW_NOT(cond(yyvsp[0].node));
		    }
    break;
case 209:
#line 1201 "parse.y"
{
			yyval.node = call_op(yyvsp[0].node, '~', 0, 0);
		    }
    break;
case 210:
#line 1205 "parse.y"
{
			yyval.node = call_op(yyvsp[-2].node, tLSHFT, 1, yyvsp[0].node);
		    }
    break;
case 211:
#line 1209 "parse.y"
{
			yyval.node = call_op(yyvsp[-2].node, tRSHFT, 1, yyvsp[0].node);
		    }
    break;
case 212:
#line 1213 "parse.y"
{
			yyval.node = logop(NODE_AND, yyvsp[-2].node, yyvsp[0].node);
		    }
    break;
case 213:
#line 1217 "parse.y"
{
			yyval.node = logop(NODE_OR, yyvsp[-2].node, yyvsp[0].node);
		    }
    break;
case 214:
#line 1220 "parse.y"
{in_defined = 1;}
    break;
case 215:
#line 1221 "parse.y"
{
		        in_defined = 0;
			yyval.node = NEW_DEFINED(yyvsp[0].node);
		    }
    break;
case 216:
#line 1226 "parse.y"
{
			yyval.node = NEW_IF(cond(yyvsp[-4].node), yyvsp[-2].node, yyvsp[0].node);
		        fixpos(yyval.node, yyvsp[-4].node);
		    }
    break;
case 217:
#line 1231 "parse.y"
{
			yyval.node = yyvsp[0].node;
		    }
    break;
case 218:
#line 1237 "parse.y"
{
			value_expr(yyvsp[0].node);
			yyval.node = yyvsp[0].node;
		    }
    break;
case 220:
#line 1245 "parse.y"
{
		        rb_warn("parenthesize argument(s) for future version");
			yyval.node = NEW_LIST(yyvsp[-1].node);
		    }
    break;
case 221:
#line 1250 "parse.y"
{
			yyval.node = yyvsp[-1].node;
		    }
    break;
case 222:
#line 1254 "parse.y"
{
			value_expr(yyvsp[-1].node);
			yyval.node = arg_concat(yyvsp[-4].node, yyvsp[-1].node);
		    }
    break;
case 223:
#line 1259 "parse.y"
{
			yyval.node = NEW_LIST(NEW_HASH(yyvsp[-1].node));
		    }
    break;
case 224:
#line 1263 "parse.y"
{
			value_expr(yyvsp[-1].node);
			yyval.node = NEW_NEWLINE(NEW_SPLAT(yyvsp[-1].node));
		    }
    break;
case 225:
#line 1270 "parse.y"
{
			yyval.node = yyvsp[-1].node;
		    }
    break;
case 226:
#line 1274 "parse.y"
{
			yyval.node = yyvsp[-2].node;
		    }
    break;
case 227:
#line 1278 "parse.y"
{
		        rb_warn("parenthesize argument for future version");
			yyval.node = NEW_LIST(yyvsp[-2].node);
		    }
    break;
case 228:
#line 1283 "parse.y"
{
		        rb_warn("parenthesize argument for future version");
			yyval.node = list_append(yyvsp[-4].node, yyvsp[-2].node);
		    }
    break;
case 231:
#line 1294 "parse.y"
{
		        rb_warn("parenthesize argument(s) for future version");
			yyval.node = NEW_LIST(yyvsp[0].node);
		    }
    break;
case 232:
#line 1299 "parse.y"
{
			yyval.node = arg_blk_pass(yyvsp[-1].node, yyvsp[0].node);
		    }
    break;
case 233:
#line 1303 "parse.y"
{
			yyval.node = arg_concat(yyvsp[-4].node, yyvsp[-1].node);
			yyval.node = arg_blk_pass(yyval.node, yyvsp[0].node);
		    }
    break;
case 234:
#line 1308 "parse.y"
{
			yyval.node = NEW_LIST(NEW_HASH(yyvsp[-1].node));
			yyval.node = arg_blk_pass(yyval.node, yyvsp[0].node);
		    }
    break;
case 235:
#line 1313 "parse.y"
{
			yyval.node = arg_concat(NEW_LIST(NEW_HASH(yyvsp[-4].node)), yyvsp[-1].node);
			yyval.node = arg_blk_pass(yyval.node, yyvsp[0].node);
		    }
    break;
case 236:
#line 1318 "parse.y"
{
			yyval.node = list_append(yyvsp[-3].node, NEW_HASH(yyvsp[-1].node));
			yyval.node = arg_blk_pass(yyval.node, yyvsp[0].node);
		    }
    break;
case 237:
#line 1323 "parse.y"
{
			value_expr(yyvsp[-1].node);
			yyval.node = arg_concat(list_append(yyvsp[-6].node, NEW_HASH(yyvsp[-4].node)), yyvsp[-1].node);
			yyval.node = arg_blk_pass(yyval.node, yyvsp[0].node);
		    }
    break;
case 238:
#line 1329 "parse.y"
{
			yyval.node = arg_blk_pass(NEW_SPLAT(yyvsp[-1].node), yyvsp[0].node);
		    }
    break;
case 240:
#line 1336 "parse.y"
{
			yyval.node = arg_blk_pass(list_concat(NEW_LIST(yyvsp[-3].node),yyvsp[-1].node), yyvsp[0].node);
		    }
    break;
case 241:
#line 1340 "parse.y"
{
                        yyval.node = arg_blk_pass(yyvsp[-2].node, yyvsp[0].node);
                    }
    break;
case 242:
#line 1344 "parse.y"
{
			yyval.node = arg_concat(NEW_LIST(yyvsp[-4].node), yyvsp[-1].node);
			yyval.node = arg_blk_pass(yyval.node, yyvsp[0].node);
		    }
    break;
case 243:
#line 1349 "parse.y"
{
                       yyval.node = arg_concat(list_concat(NEW_LIST(yyvsp[-6].node),yyvsp[-4].node), yyvsp[-1].node);
			yyval.node = arg_blk_pass(yyval.node, yyvsp[0].node);
		    }
    break;
case 244:
#line 1354 "parse.y"
{
			yyval.node = NEW_LIST(NEW_HASH(yyvsp[-1].node));
			yyval.node = arg_blk_pass(yyval.node, yyvsp[0].node);
		    }
    break;
case 245:
#line 1359 "parse.y"
{
			yyval.node = arg_concat(NEW_LIST(NEW_HASH(yyvsp[-4].node)), yyvsp[-1].node);
			yyval.node = arg_blk_pass(yyval.node, yyvsp[0].node);
		    }
    break;
case 246:
#line 1364 "parse.y"
{
			yyval.node = list_append(NEW_LIST(yyvsp[-3].node), NEW_HASH(yyvsp[-1].node));
			yyval.node = arg_blk_pass(yyval.node, yyvsp[0].node);
		    }
    break;
case 247:
#line 1369 "parse.y"
{
			yyval.node = list_append(list_concat(NEW_LIST(yyvsp[-5].node),yyvsp[-3].node), NEW_HASH(yyvsp[-1].node));
			yyval.node = arg_blk_pass(yyval.node, yyvsp[0].node);
		    }
    break;
case 248:
#line 1374 "parse.y"
{
			yyval.node = arg_concat(list_append(NEW_LIST(yyvsp[-6].node), NEW_HASH(yyvsp[-4].node)), yyvsp[-1].node);
			yyval.node = arg_blk_pass(yyval.node, yyvsp[0].node);
		    }
    break;
case 249:
#line 1379 "parse.y"
{
			yyval.node = arg_concat(list_append(list_concat(NEW_LIST(yyvsp[-8].node), yyvsp[-6].node), NEW_HASH(yyvsp[-4].node)), yyvsp[-1].node);
			yyval.node = arg_blk_pass(yyval.node, yyvsp[0].node);
		    }
    break;
case 250:
#line 1384 "parse.y"
{
			yyval.node = arg_blk_pass(NEW_SPLAT(yyvsp[-1].node), yyvsp[0].node);
		    }
    break;
case 252:
#line 1390 "parse.y"
{
			yyval.num = cmdarg_stack;
			CMDARG_PUSH(1);
		    }
    break;
case 253:
#line 1395 "parse.y"
{
			/* CMDARG_POP() */
		        cmdarg_stack = yyvsp[-1].num;
			yyval.node = yyvsp[0].node;
		    }
    break;
case 255:
#line 1403 "parse.y"
{lex_state = EXPR_ENDARG;}
    break;
case 256:
#line 1404 "parse.y"
{
		        rb_warn("don't put space before argument parentheses");
			yyval.node = 0;
		    }
    break;
case 257:
#line 1408 "parse.y"
{lex_state = EXPR_ENDARG;}
    break;
case 258:
#line 1409 "parse.y"
{
		        rb_warn("don't put space before argument parentheses");
			yyval.node = yyvsp[-2].node;
		    }
    break;
case 259:
#line 1416 "parse.y"
{
			yyval.node = NEW_BLOCK_PASS(yyvsp[0].node);
		    }
    break;
case 260:
#line 1422 "parse.y"
{
			yyval.node = yyvsp[0].node;
		    }
    break;
case 262:
#line 1429 "parse.y"
{
			yyval.node = NEW_LIST(yyvsp[0].node);
		    }
    break;
case 263:
#line 1433 "parse.y"
{
			yyval.node = list_append(yyvsp[-2].node, yyvsp[0].node);
		    }
    break;
case 264:
#line 1439 "parse.y"
{
			yyval.node = list_append(yyvsp[-2].node, yyvsp[0].node);
		    }
    break;
case 265:
#line 1443 "parse.y"
{
			yyval.node = arg_concat(yyvsp[-3].node, yyvsp[0].node);
		    }
    break;
case 266:
#line 1447 "parse.y"
{
			yyval.node = NEW_SPLAT(yyvsp[0].node);
		    }
    break;
case 275:
#line 1461 "parse.y"
{
			yyval.node = NEW_FCALL(yyvsp[0].id, 0);
		    }
    break;
case 276:
#line 1465 "parse.y"
{
			yyvsp[0].num = ruby_sourceline;
		    }
    break;
case 277:
#line 1470 "parse.y"
{
			if (yyvsp[-1].node == NULL)
			    yyval.node = NEW_NIL();
			else
			    yyval.node = NEW_BEGIN(yyvsp[-1].node);
			nd_set_line(yyval.node, yyvsp[-3].num);
		    }
    break;
case 278:
#line 1477 "parse.y"
{lex_state = EXPR_ENDARG;}
    break;
case 279:
#line 1478 "parse.y"
{
		        rb_warning("(...) interpreted as grouped expression");
			yyval.node = yyvsp[-3].node;
		    }
    break;
case 280:
#line 1483 "parse.y"
{
			yyval.node = yyvsp[-1].node;
		    }
    break;
case 281:
#line 1487 "parse.y"
{
			yyval.node = NEW_COLON2(yyvsp[-2].node, yyvsp[0].id);
		    }
    break;
case 282:
#line 1491 "parse.y"
{
			yyval.node = NEW_COLON3(yyvsp[0].id);
		    }
    break;
case 283:
#line 1495 "parse.y"
{
			if (yyvsp[-3].node && nd_type(yyvsp[-3].node) == NODE_SELF)
			    yyval.node = NEW_FCALL(tAREF, yyvsp[-1].node);
			else
			    yyval.node = NEW_CALL(yyvsp[-3].node, tAREF, yyvsp[-1].node);
			fixpos(yyval.node, yyvsp[-3].node);
		    }
    break;
case 284:
#line 1503 "parse.y"
{
		        if (yyvsp[-1].node == 0) {
			    yyval.node = NEW_ZARRAY(); /* zero length array*/
			}
			else {
			    yyval.node = yyvsp[-1].node;
			}
		    }
    break;
case 285:
#line 1512 "parse.y"
{
			yyval.node = NEW_HASH(yyvsp[-1].node);
		    }
    break;
case 286:
#line 1516 "parse.y"
{
			yyval.node = NEW_RETURN(0);
		    }
    break;
case 287:
#line 1520 "parse.y"
{
			yyval.node = new_yield(yyvsp[-1].node);
		    }
    break;
case 288:
#line 1524 "parse.y"
{
			yyval.node = NEW_YIELD(0, Qfalse);
		    }
    break;
case 289:
#line 1528 "parse.y"
{
			yyval.node = NEW_YIELD(0, Qfalse);
		    }
    break;
case 290:
#line 1531 "parse.y"
{in_defined = 1;}
    break;
case 291:
#line 1532 "parse.y"
{
		        in_defined = 0;
			yyval.node = NEW_DEFINED(yyvsp[-1].node);
		    }
    break;
case 292:
#line 1537 "parse.y"
{
			yyvsp[0].node->nd_iter = NEW_FCALL(yyvsp[-1].id, 0);
			yyval.node = yyvsp[0].node;
			fixpos(yyvsp[0].node->nd_iter, yyvsp[0].node);
		    }
    break;
case 294:
#line 1544 "parse.y"
{
			if (yyvsp[-1].node && nd_type(yyvsp[-1].node) == NODE_BLOCK_PASS) {
			    rb_compile_error("both block arg and actual block given");
			}
			yyvsp[0].node->nd_iter = yyvsp[-1].node;
			yyval.node = yyvsp[0].node;
		        fixpos(yyval.node, yyvsp[-1].node);
		    }
    break;
case 295:
#line 1556 "parse.y"
{
			yyval.node = NEW_IF(cond(yyvsp[-4].node), yyvsp[-2].node, yyvsp[-1].node);
		        fixpos(yyval.node, yyvsp[-4].node);
			if (cond_negative(&yyval.node->nd_cond)) {
		            NODE *tmp = yyval.node->nd_body;
		            yyval.node->nd_body = yyval.node->nd_else;
		            yyval.node->nd_else = tmp;
			}
		    }
    break;
case 296:
#line 1569 "parse.y"
{
			yyval.node = NEW_UNLESS(cond(yyvsp[-4].node), yyvsp[-2].node, yyvsp[-1].node);
		        fixpos(yyval.node, yyvsp[-4].node);
			if (cond_negative(&yyval.node->nd_cond)) {
		            NODE *tmp = yyval.node->nd_body;
		            yyval.node->nd_body = yyval.node->nd_else;
		            yyval.node->nd_else = tmp;
			}
		    }
    break;
case 297:
#line 1578 "parse.y"
{COND_PUSH(1);}
    break;
case 298:
#line 1578 "parse.y"
{COND_POP();}
    break;
case 299:
#line 1581 "parse.y"
{
			yyval.node = NEW_WHILE(cond(yyvsp[-4].node), yyvsp[-1].node, 1);
		        fixpos(yyval.node, yyvsp[-4].node);
			if (cond_negative(&yyval.node->nd_cond)) {
			    nd_set_type(yyval.node, NODE_UNTIL);
			}
		    }
    break;
case 300:
#line 1588 "parse.y"
{COND_PUSH(1);}
    break;
case 301:
#line 1588 "parse.y"
{COND_POP();}
    break;
case 302:
#line 1591 "parse.y"
{
			yyval.node = NEW_UNTIL(cond(yyvsp[-4].node), yyvsp[-1].node, 1);
		        fixpos(yyval.node, yyvsp[-4].node);
			if (cond_negative(&yyval.node->nd_cond)) {
			    nd_set_type(yyval.node, NODE_WHILE);
			}
		    }
    break;
case 303:
#line 1601 "parse.y"
{
			yyval.node = NEW_CASE(yyvsp[-3].node, yyvsp[-1].node);
		        fixpos(yyval.node, yyvsp[-3].node);
		    }
    break;
case 304:
#line 1606 "parse.y"
{
			yyval.node = yyvsp[-1].node;
		    }
    break;
case 305:
#line 1610 "parse.y"
{
			yyval.node = yyvsp[-1].node;
		    }
    break;
case 306:
#line 1613 "parse.y"
{COND_PUSH(1);}
    break;
case 307:
#line 1613 "parse.y"
{COND_POP();}
    break;
case 308:
#line 1616 "parse.y"
{
			yyval.node = NEW_FOR(yyvsp[-7].node, yyvsp[-4].node, yyvsp[-1].node);
		        fixpos(yyval.node, yyvsp[-7].node);
		    }
    break;
case 309:
#line 1621 "parse.y"
{
			if (in_def || in_single)
			    yyerror("class definition in method body");
			class_nest++;
			local_push(0);
		        yyval.num = ruby_sourceline;
		    }
    break;
case 310:
#line 1630 "parse.y"
{
		        yyval.node = NEW_CLASS(yyvsp[-4].node, yyvsp[-1].node, yyvsp[-3].node);
		        nd_set_line(yyval.node, yyvsp[-2].num);
		        local_pop();
			class_nest--;
		    }
    break;
case 311:
#line 1637 "parse.y"
{
			yyval.num = in_def;
		        in_def = 0;
		    }
    break;
case 312:
#line 1642 "parse.y"
{
		        yyval.num = in_single;
		        in_single = 0;
			class_nest++;
			local_push(0);
		    }
    break;
case 313:
#line 1650 "parse.y"
{
		        yyval.node = NEW_SCLASS(yyvsp[-5].node, yyvsp[-1].node);
		        fixpos(yyval.node, yyvsp[-5].node);
		        local_pop();
			class_nest--;
		        in_def = yyvsp[-4].num;
		        in_single = yyvsp[-2].num;
		    }
    break;
case 314:
#line 1659 "parse.y"
{
			if (in_def || in_single)
			    yyerror("module definition in method body");
			class_nest++;
			local_push(0);
		        yyval.num = ruby_sourceline;
		    }
    break;
case 315:
#line 1668 "parse.y"
{
		        yyval.node = NEW_MODULE(yyvsp[-3].node, yyvsp[-1].node);
		        nd_set_line(yyval.node, yyvsp[-2].num);
		        local_pop();
			class_nest--;
		    }
    break;
case 316:
#line 1675 "parse.y"
{
			yyval.id = cur_mid;
			cur_mid = yyvsp[0].id;
			in_def++;
			local_push(0);
		    }
    break;
case 317:
#line 1684 "parse.y"
{
			if (!yyvsp[-1].node) yyvsp[-1].node = NEW_NIL();
			yyval.node = NEW_DEFN(yyvsp[-4].id, yyvsp[-2].node, yyvsp[-1].node, NOEX_PRIVATE);
		        fixpos(yyval.node, yyvsp[-2].node);
		        local_pop();
			in_def--;
			cur_mid = yyvsp[-3].id;
		    }
    break;
case 318:
#line 1692 "parse.y"
{lex_state = EXPR_FNAME;}
    break;
case 319:
#line 1693 "parse.y"
{
			in_single++;
			local_push(0);
		        lex_state = EXPR_END; /* force for args */
		    }
    break;
case 320:
#line 1701 "parse.y"
{
			yyval.node = NEW_DEFS(yyvsp[-7].node, yyvsp[-4].id, yyvsp[-2].node, yyvsp[-1].node);
		        fixpos(yyval.node, yyvsp[-7].node);
		        local_pop();
			in_single--;
		    }
    break;
case 321:
#line 1708 "parse.y"
{
			yyval.node = NEW_BREAK(0);
		    }
    break;
case 322:
#line 1712 "parse.y"
{
			yyval.node = NEW_NEXT(0);
		    }
    break;
case 323:
#line 1716 "parse.y"
{
			yyval.node = NEW_REDO();
		    }
    break;
case 324:
#line 1720 "parse.y"
{
			yyval.node = NEW_RETRY();
		    }
    break;
case 325:
#line 1726 "parse.y"
{
			value_expr(yyvsp[0].node);
			yyval.node = yyvsp[0].node;
		    }
    break;
case 334:
#line 1747 "parse.y"
{
			yyval.node = NEW_IF(cond(yyvsp[-3].node), yyvsp[-1].node, yyvsp[0].node);
		        fixpos(yyval.node, yyvsp[-3].node);
		    }
    break;
case 336:
#line 1755 "parse.y"
{
			yyval.node = yyvsp[0].node;
		    }
    break;
case 340:
#line 1766 "parse.y"
{
			yyval.node = (NODE*)1;
		    }
    break;
case 341:
#line 1770 "parse.y"
{
			yyval.node = (NODE*)1;
		    }
    break;
case 342:
#line 1774 "parse.y"
{
			yyval.node = yyvsp[-1].node;
		    }
    break;
case 343:
#line 1780 "parse.y"
{
		        yyval.vars = dyna_push();
			yyvsp[0].num = ruby_sourceline;
		    }
    break;
case 344:
#line 1784 "parse.y"
{yyval.vars = ruby_dyna_vars;}
    break;
case 345:
#line 1787 "parse.y"
{
			yyval.node = NEW_ITER(yyvsp[-3].node, 0, dyna_init(yyvsp[-1].node, yyvsp[-2].vars));
			nd_set_line(yyval.node, yyvsp[-5].num);
			dyna_pop(yyvsp[-4].vars);
		    }
    break;
case 346:
#line 1795 "parse.y"
{
			if (yyvsp[-1].node && nd_type(yyvsp[-1].node) == NODE_BLOCK_PASS) {
			    rb_compile_error("both block arg and actual block given");
			}
			yyvsp[0].node->nd_iter = yyvsp[-1].node;
			yyval.node = yyvsp[0].node;
		        fixpos(yyval.node, yyvsp[-1].node);
		    }
    break;
case 347:
#line 1804 "parse.y"
{
			yyval.node = new_call(yyvsp[-3].node, yyvsp[-1].id, yyvsp[0].node);
		    }
    break;
case 348:
#line 1808 "parse.y"
{
			yyval.node = new_call(yyvsp[-3].node, yyvsp[-1].id, yyvsp[0].node);
		    }
    break;
case 349:
#line 1814 "parse.y"
{
			yyval.node = new_fcall(yyvsp[-1].id, yyvsp[0].node);
		        fixpos(yyval.node, yyvsp[0].node);
		    }
    break;
case 350:
#line 1819 "parse.y"
{
			yyval.node = new_call(yyvsp[-3].node, yyvsp[-1].id, yyvsp[0].node);
		        fixpos(yyval.node, yyvsp[-3].node);
		    }
    break;
case 351:
#line 1824 "parse.y"
{
			yyval.node = new_call(yyvsp[-3].node, yyvsp[-1].id, yyvsp[0].node);
		        fixpos(yyval.node, yyvsp[-3].node);
		    }
    break;
case 352:
#line 1829 "parse.y"
{
			yyval.node = new_call(yyvsp[-2].node, yyvsp[0].id, 0);
		    }
    break;
case 353:
#line 1833 "parse.y"
{
			yyval.node = new_super(yyvsp[0].node);
		    }
    break;
case 354:
#line 1837 "parse.y"
{
			yyval.node = NEW_ZSUPER();
		    }
    break;
case 355:
#line 1843 "parse.y"
{
		        yyval.vars = dyna_push();
			yyvsp[0].num = ruby_sourceline;
		    }
    break;
case 356:
#line 1847 "parse.y"
{yyval.vars = ruby_dyna_vars;}
    break;
case 357:
#line 1849 "parse.y"
{
			yyval.node = NEW_ITER(yyvsp[-3].node, 0, dyna_init(yyvsp[-1].node, yyvsp[-2].vars));
			nd_set_line(yyval.node, yyvsp[-5].num);
			dyna_pop(yyvsp[-4].vars);
		    }
    break;
case 358:
#line 1855 "parse.y"
{
		        yyval.vars = dyna_push();
			yyvsp[0].num = ruby_sourceline;
		    }
    break;
case 359:
#line 1859 "parse.y"
{yyval.vars = ruby_dyna_vars;}
    break;
case 360:
#line 1861 "parse.y"
{
			yyval.node = NEW_ITER(yyvsp[-3].node, 0, dyna_init(yyvsp[-1].node, yyvsp[-2].vars));
			nd_set_line(yyval.node, yyvsp[-5].num);
			dyna_pop(yyvsp[-4].vars);
		    }
    break;
case 361:
#line 1871 "parse.y"
{
			yyval.node = NEW_WHEN(yyvsp[-3].node, yyvsp[-1].node, yyvsp[0].node);
		    }
    break;
case 363:
#line 1877 "parse.y"
{
			yyval.node = list_append(yyvsp[-3].node, NEW_WHEN(yyvsp[0].node, 0, 0));
		    }
    break;
case 364:
#line 1881 "parse.y"
{
			yyval.node = NEW_LIST(NEW_WHEN(yyvsp[0].node, 0, 0));
		    }
    break;
case 367:
#line 1893 "parse.y"
{
		        if (yyvsp[-3].node) {
		            yyvsp[-3].node = node_assign(yyvsp[-3].node, NEW_GVAR(rb_intern("$!")));
			    yyvsp[-1].node = block_append(yyvsp[-3].node, yyvsp[-1].node);
			}
			yyval.node = NEW_RESBODY(yyvsp[-4].node, yyvsp[-1].node, yyvsp[0].node);
		        fixpos(yyval.node, yyvsp[-4].node?yyvsp[-4].node:yyvsp[-1].node);
		    }
    break;
case 369:
#line 1905 "parse.y"
{
			yyval.node = NEW_LIST(yyvsp[0].node);
		    }
    break;
case 372:
#line 1913 "parse.y"
{
			yyval.node = yyvsp[0].node;
		    }
    break;
case 374:
#line 1920 "parse.y"
{
			if (yyvsp[0].node)
			    yyval.node = yyvsp[0].node;
			else
			    /* place holder */
			    yyval.node = NEW_NIL();
		    }
    break;
case 377:
#line 1932 "parse.y"
{
			yyval.node = NEW_LIT(ID2SYM(yyvsp[0].id));
		    }
    break;
case 379:
#line 1939 "parse.y"
{
			NODE *node = yyvsp[0].node;
			if (!node) {
			    node = NEW_STR(rb_str_new(0, 0));
			}
			else {
			    node = evstr2dstr(node);
			}
			yyval.node = node;
		    }
    break;
case 381:
#line 1953 "parse.y"
{
			yyval.node = literal_concat(yyvsp[-1].node, yyvsp[0].node);
		    }
    break;
case 382:
#line 1959 "parse.y"
{
			yyval.node = yyvsp[-1].node;
		    }
    break;
case 383:
#line 1965 "parse.y"
{
			NODE *node = yyvsp[-1].node;
			if (!node) {
			    node = NEW_XSTR(rb_str_new(0, 0));
			}
			else {
			    switch (nd_type(node)) {
			      case NODE_STR:
				nd_set_type(node, NODE_XSTR);
				break;
			      case NODE_DSTR:
				nd_set_type(node, NODE_DXSTR);
				break;
			      default:
				node = NEW_NODE(NODE_DXSTR, rb_str_new(0, 0), 1, NEW_LIST(node));
				break;
			    }
			}
			yyval.node = node;
		    }
    break;
case 384:
#line 1988 "parse.y"
{
			int options = yyvsp[0].num;
			NODE *node = yyvsp[-1].node;
			if (!node) {
			    node = NEW_LIT(rb_reg_new("", 0, options & ~RE_OPTION_ONCE));
			}
			else switch (nd_type(node)) {
			  case NODE_STR:
			    {
				VALUE src = node->nd_lit;
				nd_set_type(node, NODE_LIT);
				node->nd_lit = rb_reg_new(RSTRING(src)->ptr,
							  RSTRING(src)->len,
							  options & ~RE_OPTION_ONCE);
			    }
			    break;
			  default:
			    node = NEW_NODE(NODE_DSTR, rb_str_new(0, 0), 1, NEW_LIST(node));
			  case NODE_DSTR:
			    if (options & RE_OPTION_ONCE) {
				nd_set_type(node, NODE_DREGX_ONCE);
			    }
			    else {
				nd_set_type(node, NODE_DREGX);
			    }
			    node->nd_cflag = options & ~RE_OPTION_ONCE;
			    break;
			}
			yyval.node = node;
		    }
    break;
case 385:
#line 2021 "parse.y"
{
			yyval.node = NEW_ZARRAY();
		    }
    break;
case 386:
#line 2025 "parse.y"
{
			yyval.node = yyvsp[-1].node;
		    }
    break;
case 387:
#line 2031 "parse.y"
{
			yyval.node = 0;
		    }
    break;
case 388:
#line 2035 "parse.y"
{
			yyval.node = list_append(yyvsp[-2].node, evstr2dstr(yyvsp[-1].node));
		    }
    break;
case 390:
#line 2042 "parse.y"
{
			yyval.node = literal_concat(yyvsp[-1].node, yyvsp[0].node);
		    }
    break;
case 391:
#line 2048 "parse.y"
{
			yyval.node = NEW_ZARRAY();
		    }
    break;
case 392:
#line 2052 "parse.y"
{
			yyval.node = yyvsp[-1].node;
		    }
    break;
case 393:
#line 2058 "parse.y"
{
			yyval.node = 0;
		    }
    break;
case 394:
#line 2062 "parse.y"
{
			yyval.node = list_append(yyvsp[-2].node, yyvsp[-1].node);
		    }
    break;
case 395:
#line 2068 "parse.y"
{
			yyval.node = 0;
		    }
    break;
case 396:
#line 2072 "parse.y"
{
			yyval.node = literal_concat(yyvsp[-1].node, yyvsp[0].node);
		    }
    break;
case 397:
#line 2078 "parse.y"
{
			yyval.node = 0;
		    }
    break;
case 398:
#line 2082 "parse.y"
{
			yyval.node = literal_concat(yyvsp[-1].node, yyvsp[0].node);
		    }
    break;
case 400:
#line 2089 "parse.y"
{
			yyval.node = lex_strterm;
			lex_strterm = 0;
			lex_state = EXPR_BEG;
		    }
    break;
case 401:
#line 2095 "parse.y"
{
			lex_strterm = yyvsp[-1].node;
		        yyval.node = NEW_EVSTR(yyvsp[0].node);
		    }
    break;
case 402:
#line 2100 "parse.y"
{
			yyval.node = lex_strterm;
			lex_strterm = 0;
			lex_state = EXPR_BEG;
			COND_PUSH(0);
			CMDARG_PUSH(0);
		    }
    break;
case 403:
#line 2108 "parse.y"
{
			lex_strterm = yyvsp[-2].node;
			COND_LEXPOP();
			CMDARG_LEXPOP();
			if ((yyval.node = yyvsp[-1].node) && nd_type(yyval.node) == NODE_NEWLINE) {
			    yyval.node = yyval.node->nd_next;
			    rb_gc_force_recycle((VALUE)yyvsp[-1].node);
			}
			yyval.node = new_evstr(yyval.node);
		    }
    break;
case 404:
#line 2120 "parse.y"
{yyval.node = NEW_GVAR(yyvsp[0].id);}
    break;
case 405:
#line 2121 "parse.y"
{yyval.node = NEW_IVAR(yyvsp[0].id);}
    break;
case 406:
#line 2122 "parse.y"
{yyval.node = NEW_CVAR(yyvsp[0].id);}
    break;
case 408:
#line 2127 "parse.y"
{
		        lex_state = EXPR_END;
			yyval.id = yyvsp[0].id;
		    }
    break;
case 413:
#line 2140 "parse.y"
{
		        lex_state = EXPR_END;
			if (!(yyval.node = yyvsp[-1].node)) {
			    yyerror("empty symbol literal");
			}
			else {
			    VALUE lit;

			    switch (nd_type(yyval.node)) {
			      case NODE_DSTR:
				nd_set_type(yyval.node, NODE_DSYM);
				break;
			      case NODE_STR:
				lit = yyval.node->nd_lit;
				if (RSTRING(lit)->len == 0) {
				    yyerror("empty symbol literal");
				    break;
				}
				if (strlen(RSTRING(lit)->ptr) == RSTRING(lit)->len) {
				    yyval.node->nd_lit = ID2SYM(rb_intern(RSTRING(yyval.node->nd_lit)->ptr));
				    nd_set_type(yyval.node, NODE_LIT);
				    break;
				}
				/* fall through */
			      default:
				yyval.node = NEW_NODE(NODE_DSYM, rb_str_new(0, 0), 1, NEW_LIST(yyval.node));
				break;
			    }
			}
		    }
    break;
case 416:
#line 2175 "parse.y"
{
			yyval.node = negate_lit(yyvsp[0].node);
		    }
    break;
case 417:
#line 2179 "parse.y"
{
			yyval.node = negate_lit(yyvsp[0].node);
		    }
    break;
case 423:
#line 2189 "parse.y"
{yyval.id = kNIL;}
    break;
case 424:
#line 2190 "parse.y"
{yyval.id = kSELF;}
    break;
case 425:
#line 2191 "parse.y"
{yyval.id = kTRUE;}
    break;
case 426:
#line 2192 "parse.y"
{yyval.id = kFALSE;}
    break;
case 427:
#line 2193 "parse.y"
{yyval.id = k__FILE__;}
    break;
case 428:
#line 2194 "parse.y"
{yyval.id = k__LINE__;}
    break;
case 429:
#line 2198 "parse.y"
{
			yyval.node = gettable(yyvsp[0].id);
		    }
    break;
case 430:
#line 2204 "parse.y"
{
			yyval.node = assignable(yyvsp[0].id, 0);
		    }
    break;
case 433:
#line 2214 "parse.y"
{
			yyval.node = 0;
		    }
    break;
case 434:
#line 2218 "parse.y"
{
			lex_state = EXPR_BEG;
		    }
    break;
case 435:
#line 2222 "parse.y"
{
			yyval.node = yyvsp[-1].node;
		    }
    break;
case 436:
#line 2225 "parse.y"
{yyerrok; yyval.node = 0;}
    break;
case 437:
#line 2229 "parse.y"
{
			yyval.node = yyvsp[-2].node;
			lex_state = EXPR_BEG;
		    }
    break;
case 438:
#line 2234 "parse.y"
{
			yyval.node = yyvsp[-1].node;
		    }
    break;
case 439:
#line 2240 "parse.y"
{
			yyval.node = block_append(NEW_ARGS(yyvsp[-5].num, yyvsp[-3].node, yyvsp[-1].id), yyvsp[0].node);
		    }
    break;
case 440:
#line 2244 "parse.y"
{
			yyval.node = block_append(NEW_ARGS(yyvsp[-3].num, yyvsp[-1].node, -1), yyvsp[0].node);
		    }
    break;
case 441:
#line 2248 "parse.y"
{
			yyval.node = block_append(NEW_ARGS(yyvsp[-3].num, 0, yyvsp[-1].id), yyvsp[0].node);
		    }
    break;
case 442:
#line 2252 "parse.y"
{
			yyval.node = block_append(NEW_ARGS(yyvsp[-1].num, 0, -1), yyvsp[0].node);
		    }
    break;
case 443:
#line 2256 "parse.y"
{
			yyval.node = block_append(NEW_ARGS(0, yyvsp[-3].node, yyvsp[-1].id), yyvsp[0].node);
		    }
    break;
case 444:
#line 2260 "parse.y"
{
			yyval.node = block_append(NEW_ARGS(0, yyvsp[-1].node, -1), yyvsp[0].node);
		    }
    break;
case 445:
#line 2264 "parse.y"
{
			yyval.node = block_append(NEW_ARGS(0, 0, yyvsp[-1].id), yyvsp[0].node);
		    }
    break;
case 446:
#line 2268 "parse.y"
{
			yyval.node = block_append(NEW_ARGS(0, 0, -1), yyvsp[0].node);
		    }
    break;
case 447:
#line 2272 "parse.y"
{
			yyval.node = NEW_ARGS(0, 0, -1);
		    }
    break;
case 448:
#line 2278 "parse.y"
{
			yyerror("formal argument cannot be a constant");
		    }
    break;
case 449:
#line 2282 "parse.y"
{
                        yyerror("formal argument cannot be an instance variable");
		    }
    break;
case 450:
#line 2286 "parse.y"
{
                        yyerror("formal argument cannot be a global variable");
		    }
    break;
case 451:
#line 2290 "parse.y"
{
                        yyerror("formal argument cannot be a class variable");
		    }
    break;
case 452:
#line 2294 "parse.y"
{
			if (!is_local_id(yyvsp[0].id))
			    yyerror("formal argument must be local variable");
			else if (local_id(yyvsp[0].id))
			    yyerror("duplicate argument name");
			local_cnt(yyvsp[0].id);
			yyval.num = 1;
		    }
    break;
case 454:
#line 2306 "parse.y"
{
			yyval.num += 1;
		    }
    break;
case 455:
#line 2312 "parse.y"
{
			if (!is_local_id(yyvsp[-2].id))
			    yyerror("formal argument must be local variable");
			else if (local_id(yyvsp[-2].id))
			    yyerror("duplicate optional argument name");
			yyval.node = assignable(yyvsp[-2].id, yyvsp[0].node);
		    }
    break;
case 456:
#line 2322 "parse.y"
{
			yyval.node = NEW_BLOCK(yyvsp[0].node);
			yyval.node->nd_end = yyval.node;
		    }
    break;
case 457:
#line 2327 "parse.y"
{
			yyval.node = block_append(yyvsp[-2].node, yyvsp[0].node);
		    }
    break;
case 460:
#line 2337 "parse.y"
{
			if (!is_local_id(yyvsp[0].id))
			    yyerror("rest argument must be local variable");
			else if (local_id(yyvsp[0].id))
			    yyerror("duplicate rest argument name");
			yyval.id = local_cnt(yyvsp[0].id);
		    }
    break;
case 461:
#line 2345 "parse.y"
{
			yyval.id = -2;
		    }
    break;
case 464:
#line 2355 "parse.y"
{
			if (!is_local_id(yyvsp[0].id))
			    yyerror("block argument must be local variable");
			else if (local_id(yyvsp[0].id))
			    yyerror("duplicate block argument name");
			yyval.node = NEW_BLOCK_ARG(yyvsp[0].id);
		    }
    break;
case 465:
#line 2365 "parse.y"
{
			yyval.node = yyvsp[0].node;
		    }
    break;
case 467:
#line 2372 "parse.y"
{
			if (nd_type(yyvsp[0].node) == NODE_SELF) {
			    yyval.node = NEW_SELF();
			}
			else {
			    yyval.node = yyvsp[0].node;
		            value_expr(yyval.node);
			}
		    }
    break;
case 468:
#line 2381 "parse.y"
{lex_state = EXPR_BEG;}
    break;
case 469:
#line 2382 "parse.y"
{
			if (yyvsp[-2].node == 0) {
			    yyerror("can't define singleton method for ().");
			}
			else {
			    switch (nd_type(yyvsp[-2].node)) {
			      case NODE_STR:
			      case NODE_DSTR:
			      case NODE_XSTR:
			      case NODE_DXSTR:
			      case NODE_DREGX:
			      case NODE_LIT:
			      case NODE_ARRAY:
			      case NODE_ZARRAY:
				yyerror("can't define singleton method for literals");
			      default:
				value_expr(yyvsp[-2].node);
				break;
			    }
			}
			yyval.node = yyvsp[-2].node;
		    }
    break;
case 471:
#line 2408 "parse.y"
{
			yyval.node = yyvsp[-1].node;
		    }
    break;
case 472:
#line 2412 "parse.y"
{
			if (yyvsp[-1].node->nd_alen%2 != 0) {
			    yyerror("odd number list for Hash");
			}
			yyval.node = yyvsp[-1].node;
		    }
    break;
case 474:
#line 2422 "parse.y"
{
			yyval.node = list_concat(yyvsp[-2].node, yyvsp[0].node);
		    }
    break;
case 475:
#line 2428 "parse.y"
{
			yyval.node = list_append(NEW_LIST(yyvsp[-2].node), yyvsp[0].node);
		    }
    break;
case 495:
#line 2466 "parse.y"
{yyerrok;}
    break;
case 498:
#line 2471 "parse.y"
{yyerrok;}
    break;
case 499:
#line 2474 "parse.y"
{yyval.node = 0;}
    break;
}

#line 706 "/usr/share/bison/bison.simple"


  yyvsp -= yylen;
  yyssp -= yylen;
#if YYLSP_NEEDED
  yylsp -= yylen;
#endif

#if YYDEBUG
  if (yydebug)
    {
      short *yyssp1 = yyss - 1;
      YYFPRINTF (stderr, "state stack now");
      while (yyssp1 != yyssp)
	YYFPRINTF (stderr, " %d", *++yyssp1);
      YYFPRINTF (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;
#if YYLSP_NEEDED
  *++yylsp = yyloc;
#endif

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTBASE];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;

#ifdef YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (yyn > YYFLAG && yyn < YYLAST)
	{
	  YYSIZE_T yysize = 0;
	  char *yymsg;
	  int yyx, yycount;

	  yycount = 0;
	  /* Start YYX at -YYN if negative to avoid negative indexes in
	     YYCHECK.  */
	  for (yyx = yyn < 0 ? -yyn : 0;
	       yyx < (int) (sizeof (yytname) / sizeof (char *)); yyx++)
	    if (yycheck[yyx + yyn] == yyx)
	      yysize += yystrlen (yytname[yyx]) + 15, yycount++;
	  yysize += yystrlen ("parse error, unexpected ") + 1;
	  yysize += yystrlen (yytname[YYTRANSLATE (yychar)]);
	  yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg != 0)
	    {
	      char *yyp = yystpcpy (yymsg, "parse error, unexpected ");
	      yyp = yystpcpy (yyp, yytname[YYTRANSLATE (yychar)]);

	      if (yycount < 5)
		{
		  yycount = 0;
		  for (yyx = yyn < 0 ? -yyn : 0;
		       yyx < (int) (sizeof (yytname) / sizeof (char *));
		       yyx++)
		    if (yycheck[yyx + yyn] == yyx)
		      {
			const char *yyq = ! yycount ? ", expecting " : " or ";
			yyp = yystpcpy (yyp, yyq);
			yyp = yystpcpy (yyp, yytname[yyx]);
			yycount++;
		      }
		}
	      yyerror (yymsg);
	      YYSTACK_FREE (yymsg);
	    }
	  else
	    yyerror ("parse error; also virtual memory exhausted");
	}
      else
#endif /* defined (YYERROR_VERBOSE) */
	yyerror ("parse error");
    }
  goto yyerrlab1;


/*--------------------------------------------------.
| yyerrlab1 -- error raised explicitly by an action |
`--------------------------------------------------*/
yyerrlab1:
  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      /* return failure if at end of input */
      if (yychar == YYEOF)
	YYABORT;
      YYDPRINTF ((stderr, "Discarding token %d (%s).\n",
		  yychar, yytname[yychar1]));
      yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */

  yyerrstatus = 3;		/* Each real token shifted decrements this */

  goto yyerrhandle;


/*-------------------------------------------------------------------.
| yyerrdefault -- current state does not do anything special for the |
| error token.                                                       |
`-------------------------------------------------------------------*/
yyerrdefault:
#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */

  /* If its default is to accept any token, ok.  Otherwise pop it.  */
  yyn = yydefact[yystate];
  if (yyn)
    goto yydefault;
#endif


/*---------------------------------------------------------------.
| yyerrpop -- pop the current state because it cannot handle the |
| error token                                                    |
`---------------------------------------------------------------*/
yyerrpop:
  if (yyssp == yyss)
    YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#if YYLSP_NEEDED
  yylsp--;
#endif

#if YYDEBUG
  if (yydebug)
    {
      short *yyssp1 = yyss - 1;
      YYFPRINTF (stderr, "Error: state stack now");
      while (yyssp1 != yyssp)
	YYFPRINTF (stderr, " %d", *++yyssp1);
      YYFPRINTF (stderr, "\n");
    }
#endif

/*--------------.
| yyerrhandle.  |
`--------------*/
yyerrhandle:
  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yyerrdefault;

  yyn += YYTERROR;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
    goto yyerrdefault;

  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrpop;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrpop;

  if (yyn == YYFINAL)
    YYACCEPT;

  YYDPRINTF ((stderr, "Shifting error token, "));

  *++yyvsp = yylval;
#if YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

/*---------------------------------------------.
| yyoverflowab -- parser overflow comes here.  |
`---------------------------------------------*/
yyoverflowlab:
  yyerror ("parser stack overflow");
  yyresult = 2;
  /* Fall through.  */

yyreturn:
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  return yyresult;
}
#line 2476 "parse.y"

#ifdef yystacksize
#undef YYMALLOC
#endif

#include "regex.h"
#include "util.h"

/* We remove any previous definition of `SIGN_EXTEND_CHAR',
   since ours (we hope) works properly with all combinations of
   machines, compilers, `char' and `unsigned char' argument types.
   (Per Bothner suggested the basic approach.)  */
#undef SIGN_EXTEND_CHAR
#if __STDC__
# define SIGN_EXTEND_CHAR(c) ((signed char)(c))
#else  /* not __STDC__ */
/* As in Harbison and Steele.  */
# define SIGN_EXTEND_CHAR(c) ((((unsigned char)(c)) ^ 128) - 128)
#endif
#define is_identchar(c) (SIGN_EXTEND_CHAR(c)!=-1&&(ISALNUM(c) || (c) == '_' || ismbchar(c)))

static char *tokenbuf = NULL;
static int   tokidx, toksiz = 0;

#define LEAVE_BS 1

static VALUE (*lex_gets)();	/* gets function */
static VALUE lex_input;		/* non-nil if File */
static VALUE lex_lastline;	/* gc protect */
static char *lex_pbeg;
static char *lex_p;
static char *lex_pend;

static int
yyerror(msg)
    const char *msg;
{
    char *p, *pe, *buf;
    int len, i;

    rb_compile_error("%s", msg);
    p = lex_p;
    while (lex_pbeg <= p) {
	if (*p == '\n') break;
	p--;
    }
    p++;

    pe = lex_p;
    while (pe < lex_pend) {
	if (*pe == '\n') break;
	pe++;
    }

    len = pe - p;
    if (len > 4) {
	buf = ALLOCA_N(char, len+2);
	MEMCPY(buf, p, char, len);
	buf[len] = '\0';
	rb_compile_error_append("%s", buf);

	i = lex_p - p;
	p = buf; pe = p + len;

	while (p < pe) {
	    if (*p != '\t') *p = ' ';
	    p++;
	}
	buf[i] = '^';
	buf[i+1] = '\0';
	rb_compile_error_append("%s", buf);
    }

    return 0;
}

static int heredoc_end;
static int command_start = Qtrue;

int ruby_in_compile = 0;
int ruby__end__seen;

static VALUE ruby_debug_lines;
#ifdef YYMALLOC
static NODE *parser_heap;
#endif

static NODE*
yycompile(f, line)
    char *f;
    int line;
{
    int n;
    NODE *node = 0;
    struct RVarmap *vp, *vars = ruby_dyna_vars;

    ruby_in_compile = 1;
    if (!compile_for_eval && rb_safe_level() == 0 &&
	rb_const_defined(rb_cObject, rb_intern("SCRIPT_LINES__"))) {
	VALUE hash, fname;

	hash = rb_const_get(rb_cObject, rb_intern("SCRIPT_LINES__"));
	if (TYPE(hash) == T_HASH) {
	    fname = rb_str_new2(f);
	    ruby_debug_lines = rb_hash_aref(hash, fname);
	    if (NIL_P(ruby_debug_lines)) {
		ruby_debug_lines = rb_ary_new();
		rb_hash_aset(hash, fname, ruby_debug_lines);
	    }
	}
	if (line > 1) {
	    VALUE str = rb_str_new(0,0);
	    while (line > 1) {
		rb_ary_push(ruby_debug_lines, str);
		line--;
	    }
	}
    }

    ruby__end__seen = 0;
    ruby_eval_tree = 0;
    heredoc_end = 0;
    lex_strterm = 0;
    ruby_current_node = 0;
    ruby_sourcefile = rb_source_filename(f);
    n = yyparse();
    ruby_debug_lines = 0;
    compile_for_eval = 0;
    ruby_in_compile = 0;
    cond_stack = 0;
    cmdarg_stack = 0;
    command_start = 1;
    class_nest = 0;
    in_single = 0;
    in_def = 0;
    cur_mid = 0;

    vp = ruby_dyna_vars;
    ruby_dyna_vars = vars;
    lex_strterm = 0;
    while (vp && vp != vars) {
	struct RVarmap *tmp = vp;
	vp = vp->next;
	rb_gc_force_recycle((VALUE)tmp);
    }
    if (n == 0) node = ruby_eval_tree;
    else ruby_eval_tree_begin = 0;
    return node;
}

static int lex_gets_ptr;

static VALUE
lex_get_str(s)
    VALUE s;
{
    char *beg, *end, *pend;

    beg = RSTRING(s)->ptr;
    if (lex_gets_ptr) {
	if (RSTRING(s)->len == lex_gets_ptr) return Qnil;
	beg += lex_gets_ptr;
    }
    pend = RSTRING(s)->ptr + RSTRING(s)->len;
    end = beg;
    while (end < pend) {
	if (*end++ == '\n') break;
    }
    lex_gets_ptr = end - RSTRING(s)->ptr;
    return rb_str_new(beg, end - beg);
}

static VALUE
lex_getline()
{
    VALUE line = (*lex_gets)(lex_input);
    if (ruby_debug_lines && !NIL_P(line)) {
	rb_ary_push(ruby_debug_lines, line);
    }
    return line;
}

NODE*
rb_compile_string(f, s, line)
    const char *f;
    VALUE s;
    int line;
{
    lex_gets = lex_get_str;
    lex_gets_ptr = 0;
    lex_input = s;
    lex_pbeg = lex_p = lex_pend = 0;
    ruby_sourceline = line - 1;
    compile_for_eval = ruby_in_eval;

    return yycompile(f, line);
}

NODE*
rb_compile_cstr(f, s, len, line)
    const char *f, *s;
    int len, line;
{
    return rb_compile_string(f, rb_str_new(s, len), line);
}

NODE*
rb_compile_file(f, file, start)
    const char *f;
    VALUE file;
    int start;
{
    lex_gets = rb_io_gets;
    lex_input = file;
    lex_pbeg = lex_p = lex_pend = 0;
    ruby_sourceline = start - 1;

    return yycompile(f, start);
}

static inline int
nextc()
{
    int c;

    if (lex_p == lex_pend) {
	if (lex_input) {
	    VALUE v = lex_getline();

	    if (NIL_P(v)) return -1;
	    if (heredoc_end > 0) {
		ruby_sourceline = heredoc_end;
		heredoc_end = 0;
	    }
	    ruby_sourceline++;
	    lex_pbeg = lex_p = RSTRING(v)->ptr;
	    lex_pend = lex_p + RSTRING(v)->len;
	    lex_lastline = v;
	}
	else {
	    lex_lastline = 0;
	    return -1;
	}
    }
    c = (unsigned char)*lex_p++;
    if (c == '\r' && lex_p < lex_pend && *lex_p == '\n') {
	lex_p++;
	c = '\n';
    }

    return c;
}

static void
pushback(c)
    int c;
{
    if (c == -1) return;
    lex_p--;
}

#define was_bol() (lex_p == lex_pbeg + 1)
#define peek(c) (lex_p != lex_pend && (c) == *lex_p)

#define tokfix() (tokenbuf[tokidx]='\0')
#define tok() tokenbuf
#define toklen() tokidx
#define toklast() (tokidx>0?tokenbuf[tokidx-1]:0)

static char*
newtok()
{
    tokidx = 0;
    if (!tokenbuf) {
	toksiz = 60;
	tokenbuf = ALLOC_N(char, 60);
    }
    if (toksiz > 4096) {
	toksiz = 60;
	REALLOC_N(tokenbuf, char, 60);
    }
    return tokenbuf;
}

static void
tokadd(c)
    char c;
{
    tokenbuf[tokidx++] = c;
    if (tokidx >= toksiz) {
	toksiz *= 2;
	REALLOC_N(tokenbuf, char, toksiz);
    }
}

static int
read_escape()
{
    int c;

    switch (c = nextc()) {
      case '\\':	/* Backslash */
	return c;

      case 'n':	/* newline */
	return '\n';

      case 't':	/* horizontal tab */
	return '\t';

      case 'r':	/* carriage-return */
	return '\r';

      case 'f':	/* form-feed */
	return '\f';

      case 'v':	/* vertical tab */
	return '\13';

      case 'a':	/* alarm(bell) */
	return '\007';

      case 'e':	/* escape */
	return 033;

      case '0': case '1': case '2': case '3': /* octal constant */
      case '4': case '5': case '6': case '7':
	{
	    int numlen;

	    pushback(c);
	    c = scan_oct(lex_p, 3, &numlen);
	    lex_p += numlen;
	}
	return c;

      case 'x':	/* hex constant */
	{
	    int numlen;

	    c = scan_hex(lex_p, 2, &numlen);
	    if (numlen == 0) {
		yyerror("Invalid escape character syntax");
		return 0;
	    }
	    lex_p += numlen;
	}
	return c;

      case 'b':	/* backspace */
	return '\010';

      case 's':	/* space */
	return ' ';

      case 'M':
	if ((c = nextc()) != '-') {
	    yyerror("Invalid escape character syntax");
	    pushback(c);
	    return '\0';
	}
	if ((c = nextc()) == '\\') {
	    return read_escape() | 0x80;
	}
	else if (c == -1) goto eof;
	else {
	    return ((c & 0xff) | 0x80);
	}

      case 'C':
	if ((c = nextc()) != '-') {
	    yyerror("Invalid escape character syntax");
	    pushback(c);
	    return '\0';
	}
      case 'c':
	if ((c = nextc())== '\\') {
	    c = read_escape();
	}
	else if (c == '?')
	    return 0177;
	else if (c == -1) goto eof;
	return c & 0x9f;

      eof:
      case -1:
        yyerror("Invalid escape character syntax");
	return '\0';

      default:
	return c;
    }
}

static int
tokadd_escape(term)
    int term;
{
    int c;

    switch (c = nextc()) {
      case '\n':
	return 0;		/* just ignore */

      case '0': case '1': case '2': case '3': /* octal constant */
      case '4': case '5': case '6': case '7':
	{
	    int i;

	    tokadd('\\');
	    tokadd(c);
	    for (i=0; i<2; i++) {
		c = nextc();
		if (c == -1) goto eof;
		if (c < '0' || '7' < c) {
		    pushback(c);
		    break;
		}
		tokadd(c);
	    }
	}
	return 0;

      case 'x':	/* hex constant */
	{
	    int numlen;

	    tokadd('\\');
	    tokadd(c);
	    scan_hex(lex_p, 2, &numlen);
	    if (numlen == 0) {
		yyerror("Invalid escape character syntax");
		return -1;
	    }
	    while (numlen--)
		tokadd(nextc());
	}
	return 0;

      case 'M':
	if ((c = nextc()) != '-') {
	    yyerror("Invalid escape character syntax");
	    pushback(c);
	    return 0;
	}
	tokadd('\\'); tokadd('M'); tokadd('-');
	goto escaped;

      case 'C':
	if ((c = nextc()) != '-') {
	    yyerror("Invalid escape character syntax");
	    pushback(c);
	    return 0;
	}
	tokadd('\\'); tokadd('C'); tokadd('-');
	goto escaped;

      case 'c':
	tokadd('\\'); tokadd('c');
      escaped:
	if ((c = nextc()) == '\\') {
	    return tokadd_escape(term);
	}
	else if (c == -1) goto eof;
	tokadd(c);
	return 0;

      eof:
      case -1:
        yyerror("Invalid escape character syntax");
	return -1;

      default:
	if (c != '\\' || c != term)
	    tokadd('\\');
	tokadd(c);
    }
    return 0;
}

static int
regx_options()
{
    char kcode = 0;
    int options = 0;
    int c;

    newtok();
    while (c = nextc(), ISALPHA(c)) {
	switch (c) {
	  case 'i':
	    options |= RE_OPTION_IGNORECASE;
	    break;
	  case 'x':
	    options |= RE_OPTION_EXTENDED;
	    break;
	  case 'm':
	    options |= RE_OPTION_MULTILINE;
	    break;
	  case 'o':
	    options |= RE_OPTION_ONCE;
	    break;
	  case 'n':
	    kcode = 16;
	    break;
	  case 'e':
	    kcode = 32;
	    break;
	  case 's':
	    kcode = 48;
	    break;
	  case 'u':
	    kcode = 64;
	    break;
	  default:
	    tokadd(c);
	    break;
	}
    }
    pushback(c);
    if (toklen()) {
	tokfix();
	rb_compile_error("unknown regexp option%s - %s",
			 toklen() > 1 ? "s" : "", tok());
    }
    return options | kcode;
}

#define STR_FUNC_ESCAPE 0x01
#define STR_FUNC_EXPAND 0x02
#define STR_FUNC_REGEXP 0x04
#define STR_FUNC_QWORDS 0x08
#define STR_FUNC_SYMBOL 0x10
#define STR_FUNC_INDENT 0x20

enum string_type {
    str_squote = (0),
    str_dquote = (STR_FUNC_EXPAND),
    str_xquote = (STR_FUNC_EXPAND),
    str_regexp = (STR_FUNC_REGEXP|STR_FUNC_ESCAPE|STR_FUNC_EXPAND),
    str_sword  = (STR_FUNC_QWORDS),
    str_dword  = (STR_FUNC_QWORDS|STR_FUNC_EXPAND),
    str_ssym   = (STR_FUNC_SYMBOL),
    str_dsym   = (STR_FUNC_SYMBOL|STR_FUNC_EXPAND),
};

static void
dispose_string(str)
    VALUE str;
{
    xfree(RSTRING(str)->ptr);
    rb_gc_force_recycle(str);
}

static int
tokadd_string(func, term, paren, nest)
    int func, term, paren, *nest;
{
    int c;

    while ((c = nextc()) != -1) {
	if (paren && c == paren) {
	    ++*nest;
	}
	else if (c == term) {
	    if (!nest || !*nest) {
		pushback(c);
		break;
	    }
	    --*nest;
	}
	else if ((func & STR_FUNC_EXPAND) && c == '#' && lex_p < lex_pend) {
	    int c2 = *lex_p;
	    if (c2 == '$' || c2 == '@' || c2 == '{') {
		pushback(c);
		break;
	    }
	}
	else if (c == '\\') {
	    c = nextc();
	    switch (c) {
	      case '\n':
		if (func & STR_FUNC_QWORDS) break;
		if (func & STR_FUNC_EXPAND) continue;
		tokadd('\\');
		break;

	      case '\\':
		if (func & STR_FUNC_ESCAPE) tokadd(c);
		break;

	      default:
		if (func & STR_FUNC_REGEXP) {
		    pushback(c);
		    if (tokadd_escape(term) < 0)
			return -1;
		    continue;
		}
		else if (func & STR_FUNC_EXPAND) {
		    pushback(c);
		    if (func & STR_FUNC_ESCAPE) tokadd('\\');
		    c = read_escape();
		}
		else if ((func & STR_FUNC_QWORDS) && ISSPACE(c)) {
		    /* ignore backslashed spaces in %w */
		}
		else if (c != term && !(paren && c == paren)) {
		    tokadd('\\');
		}
	    }
	}
	else if (ismbchar(c)) {
	    int i, len = mbclen(c)-1;

	    for (i = 0; i < len; i++) {
		tokadd(c);
		c = nextc();
	    }
	}
	else if ((func & STR_FUNC_QWORDS) && ISSPACE(c)) {
	    pushback(c);
	    break;
	}
	if (!c && (func & STR_FUNC_SYMBOL)) {
	    func &= ~STR_FUNC_SYMBOL;
	    rb_compile_error("symbol cannot contain '\\0'");
	    continue;
	}
	tokadd(c);
    }
    return c;
}

#define NEW_STRTERM(func, term, paren) \
	rb_node_newnode(NODE_STRTERM, (func), (term) | ((paren) << (CHAR_BIT * 2)), 0)

static int
parse_string(quote)
    NODE *quote;
{
    int func = quote->nd_func;
    int term = nd_term(quote);
    int paren = nd_paren(quote);
    int c, space = 0;

    if (func == -1) return tSTRING_END;
    c = nextc();
    if ((func & STR_FUNC_QWORDS) && ISSPACE(c)) {
	do {c = nextc();} while (ISSPACE(c));
	space = 1;
    }
    if (c == term && !quote->nd_nest) {
	if (func & STR_FUNC_QWORDS) {
	    quote->nd_func = -1;
	    return ' ';
	}
	if (!(func & STR_FUNC_REGEXP)) return tSTRING_END;
	yylval.num = regx_options();
	return tREGEXP_END;
    }
    if (space) {
	pushback(c);
	return ' ';
    }
    newtok();
    if ((func & STR_FUNC_EXPAND) && c == '#') {
	switch (c = nextc()) {
	  case '$':
	  case '@':
	    pushback(c);
	    return tSTRING_DVAR;
	  case '{':
	    return tSTRING_DBEG;
	}
	tokadd('#');
    }
    pushback(c);
    if (tokadd_string(func, term, paren, &quote->nd_nest) == -1) {
	ruby_sourceline = nd_line(quote);
	rb_compile_error("unterminated string meets end of file");
	return tSTRING_END;
    }

    tokfix();
    yylval.node = NEW_STR(rb_str_new(tok(), toklen()));
    return tSTRING_CONTENT;
}

static int
heredoc_identifier()
{
    int c = nextc(), term, func = 0, len;

    if (c == '-') {
	c = nextc();
	func = STR_FUNC_INDENT;
    }
    switch (c) {
      case '\'':
	func |= str_squote; goto quoted;
      case '"':
	func |= str_dquote; goto quoted;
      case '`':
	func |= str_xquote;
      quoted:
	newtok();
	tokadd(func);
	term = c;
	while ((c = nextc()) != -1 && c != term) {
	    len = mbclen(c);
	    do {tokadd(c);} while (--len > 0 && (c = nextc()) != -1);
	}
	if (c == -1) {
	    rb_compile_error("unterminated here document identifier");
	    return 0;
	}
	break;

      default:
	if (!is_identchar(c)) {
	    pushback(c);
	    if (func & STR_FUNC_INDENT) {
		pushback('-');
	    }
	    return 0;
	}
	newtok();
	term = '"';
	tokadd(func |= str_dquote);
	do {
	    len = mbclen(c);
	    do {tokadd(c);} while (--len > 0 && (c = nextc()) != -1);
	} while ((c = nextc()) != -1 && is_identchar(c));
	pushback(c);
	break;
    }

    tokfix();
    len = lex_p - lex_pbeg;
    lex_p = lex_pend;
    lex_strterm = rb_node_newnode(NODE_HEREDOC,
				  rb_str_new(tok(), toklen()),	/* nd_lit */
				  len,				/* nd_nth */
				  lex_lastline);		/* nd_orig */
    return term == '`' ? tXSTRING_BEG : tSTRING_BEG;
}

static void
heredoc_restore(here)
    NODE *here;
{
    VALUE line = here->nd_orig;
    lex_lastline = line;
    lex_pbeg = RSTRING(line)->ptr;
    lex_pend = lex_pbeg + RSTRING(line)->len;
    lex_p = lex_pbeg + here->nd_nth;
    heredoc_end = ruby_sourceline;
    ruby_sourceline = nd_line(here);
    dispose_string(here->nd_lit);
    rb_gc_force_recycle((VALUE)here);
}

static int
whole_match_p(eos, len, indent)
    char *eos;
    int len, indent;
{
    char *p = lex_pbeg;
    int n;

    if (indent) {
	while (*p && ISSPACE(*p)) p++;
    }
    n= lex_pend - (p + len);
    if (n < 0 || (n > 0 && p[len] != '\n' && p[len] != '\r')) return Qfalse;
    if (strncmp(eos, p, len) == 0) return Qtrue;
    return Qfalse;
}

static int
here_document(here)
    NODE *here;
{
    int c, func, indent = 0;
    char *eos, *p, *pend;
    long len;
    VALUE str = 0;

    eos = RSTRING(here->nd_lit)->ptr;
    len = RSTRING(here->nd_lit)->len - 1;
    indent = (func = *eos++) & STR_FUNC_INDENT;

    if ((c = nextc()) == -1) {
      error:
	rb_compile_error("can't find string \"%s\" anywhere before EOF", eos);
	heredoc_restore(lex_strterm);
	lex_strterm = 0;
	return 0;
    }
    if (was_bol() && whole_match_p(eos, len, indent)) {
	heredoc_restore(lex_strterm);
	return tSTRING_END;
    }

    if (!(func & STR_FUNC_EXPAND)) {
	do {
	    p = RSTRING(lex_lastline)->ptr;
	    pend = lex_pend;
	    if (pend > p) {
		switch (pend[-1]) {
		  case '\n':
		    if (--pend == p || pend[-1] != '\r') {
			pend++;
			break;
		    }
		  case '\r':
		    --pend;
		}
	    }
	    if (str)
		rb_str_cat(str, p, pend - p);
	    else
		str = rb_str_new(p, pend - p);
	    if (pend < lex_pend) rb_str_cat(str, "\n", 1);
	    lex_p = lex_pend;
	    if (nextc() == -1) {
		if (str) dispose_string(str);
		goto error;
	    }
	} while (!whole_match_p(eos, len, indent));
    }
    else {
	newtok();
	if (c == '#') {
	    switch (c = nextc()) {
	      case '$':
	      case '@':
		pushback(c);
		return tSTRING_DVAR;
	      case '{':
		return tSTRING_DBEG;
	    }
	    tokadd('#');
	}
	do {
	    pushback(c);
	    if ((c = tokadd_string(func, '\n', 0, NULL)) == -1) goto error;
	    if (c != '\n') {
		yylval.node = NEW_STR(rb_str_new(tok(), toklen()));
		return tSTRING_CONTENT;
	    }
	    tokadd(nextc());
	    if ((c = nextc()) == -1) goto error;
	} while (!whole_match_p(eos, len, indent));
	str = rb_str_new(tok(), toklen());
    }
    heredoc_restore(lex_strterm);
    lex_strterm = NEW_STRTERM(-1, 0, 0);
    yylval.node = NEW_STR(str);
    return tSTRING_CONTENT;
}

#include "lex.c"

static void
arg_ambiguous()
{
    rb_warning("ambiguous first argument; put parentheses or even spaces");
}

#define IS_ARG() (lex_state == EXPR_ARG || lex_state == EXPR_CMDARG)

static int
yylex()
{
    register int c;
    int space_seen = 0;
    int cmd_state;
    enum lex_state last_state;

    if (lex_strterm) {
	int token;
	if (nd_type(lex_strterm) == NODE_HEREDOC) {
	    token = here_document(lex_strterm);
	    if (token == tSTRING_END) {
		lex_strterm = 0;
		lex_state = EXPR_END;
	    }
	}
	else {
	    token = parse_string(lex_strterm);
	    if (token == tSTRING_END || token == tREGEXP_END) {
		rb_gc_force_recycle((VALUE)lex_strterm);
		lex_strterm = 0;
		lex_state = EXPR_END;
	    }
	}
	return token;
    }
    cmd_state = command_start;
    command_start = Qfalse;
  retry:
    switch (c = nextc()) {
      case '\0':		/* NUL */
      case '\004':		/* ^D */
      case '\032':		/* ^Z */
      case -1:			/* end of script. */
	return 0;

	/* white spaces */
      case ' ': case '\t': case '\f': case '\r':
      case '\13': /* '\v' */
	space_seen++;
	goto retry;

      case '#':		/* it's a comment */
	while ((c = nextc()) != '\n') {
	    if (c == -1)
		return 0;
	}
	/* fall through */
      case '\n':
	switch (lex_state) {
	  case EXPR_BEG:
	  case EXPR_FNAME:
	  case EXPR_DOT:
	  case EXPR_CLASS:
	    goto retry;
	  default:
	    break;
	}
	command_start = Qtrue;
	lex_state = EXPR_BEG;
	return '\n';

      case '*':
	if ((c = nextc()) == '*') {
	    if ((c = nextc()) == '=') {
		yylval.id = tPOW;
		lex_state = EXPR_BEG;
		return tOP_ASGN;
	    }
	    pushback(c);
	    c = tPOW;
	}
	else {
	    if (c == '=') {
		yylval.id = '*';
		lex_state = EXPR_BEG;
		return tOP_ASGN;
	    }
	    pushback(c);
	    if (IS_ARG() && space_seen && !ISSPACE(c)){
		rb_warning("`*' interpreted as argument prefix");
		c = tSTAR;
	    }
	    else if (lex_state == EXPR_BEG || lex_state == EXPR_MID) {
		c = tSTAR;
	    }
	    else {
		c = '*';
	    }
	}
	switch (lex_state) {
	  case EXPR_FNAME: case EXPR_DOT:
	    lex_state = EXPR_ARG; break;
	  default:
	    lex_state = EXPR_BEG; break;
	}
	return c;

      case '!':
	lex_state = EXPR_BEG;
	if ((c = nextc()) == '=') {
	    return tNEQ;
	}
	if (c == '~') {
	    return tNMATCH;
	}
	pushback(c);
	return '!';

      case '=':
	if (was_bol()) {
	    /* skip embedded rd document */
	    if (strncmp(lex_p, "begin", 5) == 0 && ISSPACE(lex_p[5])) {
		for (;;) {
		    lex_p = lex_pend;
		    c = nextc();
		    if (c == -1) {
			rb_compile_error("embedded document meets end of file");
			return 0;
		    }
		    if (c != '=') continue;
		    if (strncmp(lex_p, "end", 3) == 0 &&
			(lex_p + 3 == lex_pend || ISSPACE(lex_p[3]))) {
			break;
		    }
		}
		lex_p = lex_pend;
		goto retry;
	    }
	}

	switch (lex_state) {
	  case EXPR_FNAME: case EXPR_DOT:
	    lex_state = EXPR_ARG; break;
	  default:
	    lex_state = EXPR_BEG; break;
	}
	if ((c = nextc()) == '=') {
	    if ((c = nextc()) == '=') {
		return tEQQ;
	    }
	    pushback(c);
	    return tEQ;
	}
	if (c == '~') {
	    return tMATCH;
	}
	else if (c == '>') {
	    return tASSOC;
	}
	pushback(c);
	return '=';

      case '<':
	c = nextc();
	if (c == '<' &&
	    lex_state != EXPR_END &&
	    lex_state != EXPR_DOT &&
	    lex_state != EXPR_ENDARG &&
	    lex_state != EXPR_CLASS &&
	    (!IS_ARG() || space_seen)) {
	    int token = heredoc_identifier();
	    if (token) return token;
	}
	switch (lex_state) {
	  case EXPR_FNAME: case EXPR_DOT:
	    lex_state = EXPR_ARG; break;
	  default:
	    lex_state = EXPR_BEG; break;
	}
	if (c == '=') {
	    if ((c = nextc()) == '>') {
		return tCMP;
	    }
	    pushback(c);
	    return tLEQ;
	}
	if (c == '<') {
	    if ((c = nextc()) == '=') {
		yylval.id = tLSHFT;
		lex_state = EXPR_BEG;
		return tOP_ASGN;
	    }
	    pushback(c);
	    return tLSHFT;
	}
	pushback(c);
	return '<';

      case '>':
	switch (lex_state) {
	  case EXPR_FNAME: case EXPR_DOT:
	    lex_state = EXPR_ARG; break;
	  default:
	    lex_state = EXPR_BEG; break;
	}
	if ((c = nextc()) == '=') {
	    return tGEQ;
	}
	if (c == '>') {
	    if ((c = nextc()) == '=') {
		yylval.id = tRSHFT;
		lex_state = EXPR_BEG;
		return tOP_ASGN;
	    }
	    pushback(c);
	    return tRSHFT;
	}
	pushback(c);
	return '>';

      case '"':
	lex_strterm = NEW_STRTERM(str_dquote, '"', 0);
	return tSTRING_BEG;

      case '`':
	if (lex_state == EXPR_FNAME) {
	    lex_state = EXPR_END;
	    return c;
	}
	if (lex_state == EXPR_DOT) {
	    if (cmd_state)
		lex_state = EXPR_CMDARG;
	    else
		lex_state = EXPR_ARG;
	    return c;
	}
	lex_strterm = NEW_STRTERM(str_xquote, '`', 0);
	return tXSTRING_BEG;

      case '\'':
	lex_strterm = NEW_STRTERM(str_squote, '\'', 0);
	return tSTRING_BEG;

      case '?':
	if (lex_state == EXPR_END || lex_state == EXPR_ENDARG) {
	    lex_state = EXPR_BEG;
	    return '?';
	}
	c = nextc();
	if (c == -1) {
	    rb_compile_error("incomplete character syntax");
	    return 0;
	}
	if (ISSPACE(c)){
	    if (!IS_ARG()){
		int c2 = 0;
		switch (c) {
		  case ' ':
		    c2 = 's';
		    break;
		  case '\n':
		    c2 = 'n';
		    break;
		  case '\t':
		    c2 = 't';
		    break;
		  case '\v':
		    c2 = 'v';
		    break;
		  case '\r':
		    c2 = 'r';
		    break;
		  case '\f':
		    c2 = 'f';
		    break;
		}
		if (c2) {
		    rb_warn("invalid character syntax; use ?\\%c", c2);
		}
	    }
	  ternary:
	    pushback(c);
	    lex_state = EXPR_BEG;
	    return '?';
	}
	else if (ismbchar(c)) {
	    rb_warn("multibyte character literal not supported yet; use ?\\%.3o", c);
	    goto ternary;
	}
	else if ((ISALNUM(c) || c == '_') && lex_p < lex_pend && is_identchar(*lex_p)) {
	    goto ternary;
	}
	else if (c == '\\') {
	    c = read_escape();
	}
	c &= 0xff;
	lex_state = EXPR_END;
	yylval.node = NEW_LIT(INT2FIX(c));
	return tINTEGER;

      case '&':
	if ((c = nextc()) == '&') {
	    lex_state = EXPR_BEG;
	    if ((c = nextc()) == '=') {
		yylval.id = tANDOP;
		lex_state = EXPR_BEG;
		return tOP_ASGN;
	    }
	    pushback(c);
	    return tANDOP;
	}
	else if (c == '=') {
	    yylval.id = '&';
	    lex_state = EXPR_BEG;
	    return tOP_ASGN;
	}
	pushback(c);
	if (IS_ARG() && space_seen && !ISSPACE(c)){
	    rb_warning("`&' interpreted as argument prefix");
	    c = tAMPER;
	}
	else if (lex_state == EXPR_BEG || lex_state == EXPR_MID) {
	    c = tAMPER;
	}
	else {
	    c = '&';
	}
	switch (lex_state) {
	  case EXPR_FNAME: case EXPR_DOT:
	    lex_state = EXPR_ARG; break;
	  default:
	    lex_state = EXPR_BEG;
	}
	return c;

      case '|':
	if ((c = nextc()) == '|') {
	    lex_state = EXPR_BEG;
	    if ((c = nextc()) == '=') {
		yylval.id = tOROP;
		lex_state = EXPR_BEG;
		return tOP_ASGN;
	    }
	    pushback(c);
	    return tOROP;
	}
	if (c == '=') {
	    yylval.id = '|';
	    lex_state = EXPR_BEG;
	    return tOP_ASGN;
	}
	if (lex_state == EXPR_FNAME || lex_state == EXPR_DOT) {
	    lex_state = EXPR_ARG;
	}
	else {
	    lex_state = EXPR_BEG;
	}
	pushback(c);
	return '|';

      case '+':
	c = nextc();
	if (lex_state == EXPR_FNAME || lex_state == EXPR_DOT) {
	    lex_state = EXPR_ARG;
	    if (c == '@') {
		return tUPLUS;
	    }
	    pushback(c);
	    return '+';
	}
	if (c == '=') {
	    yylval.id = '+';
	    lex_state = EXPR_BEG;
	    return tOP_ASGN;
	}
	if (lex_state == EXPR_BEG || lex_state == EXPR_MID ||
	    (IS_ARG() && space_seen && !ISSPACE(c))) {
	    if (IS_ARG()) arg_ambiguous();
	    lex_state = EXPR_BEG;
	    pushback(c);
	    if (ISDIGIT(c)) {
		c = '+';
		goto start_num;
	    }
	    return tUPLUS;
	}
	lex_state = EXPR_BEG;
	pushback(c);
	return '+';

      case '-':
	c = nextc();
	if (lex_state == EXPR_FNAME || lex_state == EXPR_DOT) {
	    lex_state = EXPR_ARG;
	    if (c == '@') {
		return tUMINUS;
	    }
	    pushback(c);
	    return '-';
	}
	if (c == '=') {
	    yylval.id = '-';
	    lex_state = EXPR_BEG;
	    return tOP_ASGN;
	}
	if (lex_state == EXPR_BEG || lex_state == EXPR_MID ||
	    (IS_ARG() && space_seen && !ISSPACE(c))) {
	    if (IS_ARG()) arg_ambiguous();
	    lex_state = EXPR_BEG;
	    pushback(c);
	    if (ISDIGIT(c)) {
		return tUMINUS_NUM;
	    }
	    return tUMINUS;
	}
	lex_state = EXPR_BEG;
	pushback(c);
	return '-';

      case '.':
	lex_state = EXPR_BEG;
	if ((c = nextc()) == '.') {
	    if ((c = nextc()) == '.') {
		return tDOT3;
	    }
	    pushback(c);
	    return tDOT2;
	}
	pushback(c);
	if (ISDIGIT(c)) {
	    yyerror("no .<digit> floating literal anymore; put 0 before dot");
	}
	lex_state = EXPR_DOT;
	return '.';

      start_num:
      case '0': case '1': case '2': case '3': case '4':
      case '5': case '6': case '7': case '8': case '9':
	{
	    int is_float, seen_point, seen_e, nondigit;

	    is_float = seen_point = seen_e = nondigit = 0;
	    lex_state = EXPR_END;
	    newtok();
	    if (c == '-' || c == '+') {
		tokadd(c);
		c = nextc();
	    }
	    if (c == '0') {
		int start = toklen();
		c = nextc();
		if (c == 'x' || c == 'X') {
		    /* hexadecimal */
		    c = nextc();
		    if (ISXDIGIT(c)) {
			do {
			    if (c == '_') {
				if (nondigit) break;
				nondigit = c;
				continue;
			    }
			    if (!ISXDIGIT(c)) break;
			    nondigit = 0;
			    tokadd(c);
			} while ((c = nextc()) != -1);
		    }
		    pushback(c);
		    tokfix();
		    if (toklen() == start) {
			yyerror("numeric literal without digits");
		    }
		    else if (nondigit) goto trailing_uc;
		    yylval.node = NEW_LIT(rb_cstr_to_inum(tok(), 16, Qfalse));
		    return tINTEGER;
		}
		if (c == 'b' || c == 'B') {
		    /* binary */
		    c = nextc();
		    if (c == '0' || c == '1') {
			do {
			    if (c == '_') {
				if (nondigit) break;
				nondigit = c;
				continue;
			    }
			    if (c != '0' && c != '1') break;
			    nondigit = 0;
			    tokadd(c);
			} while ((c = nextc()) != -1);
		    }
		    pushback(c);
		    tokfix();
		    if (toklen() == start) {
			yyerror("numeric literal without digits");
		    }
		    else if (nondigit) goto trailing_uc;
		    yylval.node = NEW_LIT(rb_cstr_to_inum(tok(), 2, Qfalse));
		    return tINTEGER;
		}
		if (c == 'd' || c == 'D') {
		    /* decimal */
		    c = nextc();
		    if (ISDIGIT(c)) {
			do {
			    if (c == '_') {
				if (nondigit) break;
				nondigit = c;
				continue;
			    }
			    if (!ISDIGIT(c)) break;
			    nondigit = 0;
			    tokadd(c);
			} while ((c = nextc()) != -1);
		    }
		    pushback(c);
		    tokfix();
		    if (toklen() == start) {
			yyerror("numeric literal without digits");
		    }
		    else if (nondigit) goto trailing_uc;
		    yylval.node = NEW_LIT(rb_cstr_to_inum(tok(), 10, Qfalse));
		    return tINTEGER;
		}
		if (c == '_') {
		    /* 0_0 */
		    goto octal_number;
		}
		if (c == 'o' || c == 'O') {
		    /* prefixed octal */
		    c = nextc();
		    if (c == '_') {
			yyerror("numeric literal without digits");
		    }
		}
		if (c >= '0' && c <= '7') {
		    /* octal */
		  octal_number:
	            do {
			if (c == '_') {
			    if (nondigit) break;
			    nondigit = c;
			    continue;
			}
			if (c < '0' || c > '7') break;
			nondigit = 0;
			tokadd(c);
		    } while ((c = nextc()) != -1);
		    if (toklen() > start) {
			pushback(c);
			tokfix();
			if (nondigit) goto trailing_uc;
			yylval.node = NEW_LIT(rb_cstr_to_inum(tok(), 8, Qfalse));
			return tINTEGER;
		    }
		    if (nondigit) {
			pushback(c);
			goto trailing_uc;
		    }
		}
		if (c > '7' && c <= '9') {
		    yyerror("Illegal octal digit");
		}
		else if (c == '.' || c == 'e' || c == 'E') {
		    tokadd('0');
		}
		else {
		    pushback(c);
		    yylval.node = NEW_LIT(INT2FIX(0));
		    return tINTEGER;
		}
	    }

	    for (;;) {
		switch (c) {
		  case '0': case '1': case '2': case '3': case '4':
		  case '5': case '6': case '7': case '8': case '9':
		    nondigit = 0;
		    tokadd(c);
		    break;

		  case '.':
		    if (nondigit) goto trailing_uc;
		    if (seen_point || seen_e) {
			goto decode_num;
		    }
		    else {
			int c0 = nextc();
			if (!ISDIGIT(c0)) {
			    pushback(c0);
			    goto decode_num;
			}
			c = c0;
		    }
		    tokadd('.');
		    tokadd(c);
		    is_float++;
		    seen_point++;
		    nondigit = 0;
		    break;

		  case 'e':
		  case 'E':
		    if (nondigit) {
			pushback(c);
			c = nondigit;
			goto decode_num;
		    }
		    if (seen_e) {
			goto decode_num;
		    }
		    tokadd(c);
		    seen_e++;
		    is_float++;
		    nondigit = c;
		    c = nextc();
		    if (c != '-' && c != '+') continue;
		    tokadd(c);
		    nondigit = c;
		    break;

		  case '_':	/* `_' in number just ignored */
		    if (nondigit) goto decode_num;
		    nondigit = c;
		    break;

		  default:
		    goto decode_num;
		}
		c = nextc();
	    }

	  decode_num:
	    pushback(c);
	    tokfix();
	    if (nondigit) {
		char tmp[30];
	      trailing_uc:
		sprintf(tmp, "trailing `%c' in number", nondigit);
		yyerror(tmp);
	    }
	    if (is_float) {
		double d = strtod(tok(), 0);
		if (errno == ERANGE) {
		    rb_warn("Float %s out of range", tok());
		    errno = 0;
		}
		yylval.node = NEW_LIT(rb_float_new(d));
		return tFLOAT;
	    }
	    yylval.node = NEW_LIT(rb_cstr_to_inum(tok(), 10, Qfalse));
	    return tINTEGER;
	}

      case ']':
      case '}':
      case ')':
	COND_LEXPOP();
	CMDARG_LEXPOP();
	lex_state = EXPR_END;
	return c;

      case ':':
	c = nextc();
	if (c == ':') {
	    if (lex_state == EXPR_BEG ||  lex_state == EXPR_MID ||
		lex_state == EXPR_CLASS || (IS_ARG() && space_seen)) {
		lex_state = EXPR_BEG;
		return tCOLON3;
	    }
	    lex_state = EXPR_DOT;
	    return tCOLON2;
	}
	if (lex_state == EXPR_END || lex_state == EXPR_ENDARG || ISSPACE(c)) {
	    pushback(c);
	    lex_state = EXPR_BEG;
	    return ':';
	}
	switch (c) {
	  case '\'':
	    lex_strterm = NEW_STRTERM(str_ssym, c, 0);
	    break;
	  case '"':
	    lex_strterm = NEW_STRTERM(str_dsym, c, 0);
	    break;
	  default:
	    pushback(c);
	    break;
	}
	lex_state = EXPR_FNAME;
	return tSYMBEG;

      case '/':
	if (lex_state == EXPR_BEG || lex_state == EXPR_MID) {
	    lex_strterm = NEW_STRTERM(str_regexp, '/', 0);
	    return tREGEXP_BEG;
	}
	if ((c = nextc()) == '=') {
	    yylval.id = '/';
	    lex_state = EXPR_BEG;
	    return tOP_ASGN;
	}
	pushback(c);
	if (IS_ARG() && space_seen) {
	    if (!ISSPACE(c)) {
		arg_ambiguous();
		lex_strterm = NEW_STRTERM(str_regexp, '/', 0);
		return tREGEXP_BEG;
	    }
	}
	switch (lex_state) {
	  case EXPR_FNAME: case EXPR_DOT:
	    lex_state = EXPR_ARG; break;
	  default:
	    lex_state = EXPR_BEG; break;
	}
	return '/';

      case '^':
	if ((c = nextc()) == '=') {
	    yylval.id = '^';
	    lex_state = EXPR_BEG;
	    return tOP_ASGN;
	}
	switch (lex_state) {
	  case EXPR_FNAME: case EXPR_DOT:
	    lex_state = EXPR_ARG; break;
	  default:
	    lex_state = EXPR_BEG; break;
	}
	pushback(c);
	return '^';

      case ';':
	command_start = Qtrue;
      case ',':
	lex_state = EXPR_BEG;
	return c;

      case '~':
	if (lex_state == EXPR_FNAME || lex_state == EXPR_DOT) {
	    if ((c = nextc()) != '@') {
		pushback(c);
	    }
	}
	switch (lex_state) {
	  case EXPR_FNAME: case EXPR_DOT:
	    lex_state = EXPR_ARG; break;
	  default:
	    lex_state = EXPR_BEG; break;
	}
	return '~';

      case '(':
	command_start = Qtrue;
	if (lex_state == EXPR_BEG || lex_state == EXPR_MID) {
	    c = tLPAREN;
	}
	else if (space_seen) {
	    if (lex_state == EXPR_CMDARG) {
		c = tLPAREN_ARG;
	    }
	    else if (lex_state == EXPR_ARG) {
		rb_warn("don't put space before argument parentheses");
		c = '(';
	    }
	}
	COND_PUSH(0);
	CMDARG_PUSH(0);
	lex_state = EXPR_BEG;
	return c;

      case '[':
	if (lex_state == EXPR_FNAME || lex_state == EXPR_DOT) {
	    lex_state = EXPR_ARG;
	    if ((c = nextc()) == ']') {
		if ((c = nextc()) == '=') {
		    return tASET;
		}
		pushback(c);
		return tAREF;
	    }
	    pushback(c);
	    return '[';
	}
	else if (lex_state == EXPR_BEG || lex_state == EXPR_MID) {
	    c = tLBRACK;
	}
	else if (IS_ARG() && space_seen) {
	    c = tLBRACK;
	}
	lex_state = EXPR_BEG;
	COND_PUSH(0);
	CMDARG_PUSH(0);
	return c;

      case '{':
	if (IS_ARG() || lex_state == EXPR_END)
	    c = '{';          /* block (primary) */
	else if (lex_state == EXPR_ENDARG)
	    c = tLBRACE_ARG;  /* block (expr) */
	else
	    c = tLBRACE;      /* hash */
	COND_PUSH(0);
	CMDARG_PUSH(0);
	lex_state = EXPR_BEG;
	return c;

      case '\\':
	c = nextc();
	if (c == '\n') {
	    space_seen = 1;
	    goto retry; /* skip \\n */
	}
	pushback(c);
	return '\\';

      case '%':
	if (lex_state == EXPR_BEG || lex_state == EXPR_MID) {
	    int term;
	    int paren;

	    c = nextc();
	  quotation:
	    if (!ISALNUM(c)) {
		term = c;
		c = 'Q';
	    }
	    else {
		term = nextc();
		if (ISALNUM(term) || ismbchar(term)) {
		    yyerror("unknown type of %string");
		    return 0;
		}
	    }
	    if (c == -1 || term == -1) {
		rb_compile_error("unterminated quoted string meets end of file");
		return 0;
	    }
	    paren = term;
	    if (term == '(') term = ')';
	    else if (term == '[') term = ']';
	    else if (term == '{') term = '}';
	    else if (term == '<') term = '>';
	    else paren = 0;

	    switch (c) {
	      case 'Q':
		lex_strterm = NEW_STRTERM(str_dquote, term, paren);
		return tSTRING_BEG;

	      case 'q':
		lex_strterm = NEW_STRTERM(str_squote, term, paren);
		return tSTRING_BEG;

	      case 'W':
		lex_strterm = NEW_STRTERM(str_dquote | STR_FUNC_QWORDS, term, paren);
		do {c = nextc();} while (ISSPACE(c));
		pushback(c);
		return tWORDS_BEG;

	      case 'w':
		lex_strterm = NEW_STRTERM(str_squote | STR_FUNC_QWORDS, term, paren);
		do {c = nextc();} while (ISSPACE(c));
		pushback(c);
		return tQWORDS_BEG;

	      case 'x':
		lex_strterm = NEW_STRTERM(str_xquote, term, paren);
		return tXSTRING_BEG;

	      case 'r':
		lex_strterm = NEW_STRTERM(str_regexp, term, paren);
		return tREGEXP_BEG;

	      case 's':
		lex_strterm = NEW_STRTERM(str_ssym, term, paren);
		lex_state = EXPR_FNAME;
		return tSYMBEG;

	      default:
		yyerror("unknown type of %string");
		return 0;
	    }
	}
	if ((c = nextc()) == '=') {
	    yylval.id = '%';
	    lex_state = EXPR_BEG;
	    return tOP_ASGN;
	}
	if (IS_ARG() && space_seen && !ISSPACE(c)) {
	    goto quotation;
	}
	switch (lex_state) {
	  case EXPR_FNAME: case EXPR_DOT:
	    lex_state = EXPR_ARG; break;
	  default:
	    lex_state = EXPR_BEG; break;
	}
	pushback(c);
	return '%';

      case '$':
	last_state = lex_state;
	lex_state = EXPR_END;
	newtok();
	c = nextc();
	switch (c) {
	  case '_':		/* $_: last read line string */
	    c = nextc();
	    if (is_identchar(c)) {
		tokadd('$');
		tokadd('_');
		break;
	    }
	    pushback(c);
	    c = '_';
	    /* fall through */
	  case '~':		/* $~: match-data */
	    local_cnt(c);
	    /* fall through */
	  case '*':		/* $*: argv */
	  case '$':		/* $$: pid */
	  case '?':		/* $?: last status */
	  case '!':		/* $!: error string */
	  case '@':		/* $@: error position */
	  case '/':		/* $/: input record separator */
	  case '\\':		/* $\: output record separator */
	  case ';':		/* $;: field separator */
	  case ',':		/* $,: output field separator */
	  case '.':		/* $.: last read line number */
	  case '=':		/* $=: ignorecase */
	  case ':':		/* $:: load path */
	  case '<':		/* $<: reading filename */
	  case '>':		/* $>: default output handle */
	  case '\"':		/* $": already loaded files */
	    tokadd('$');
	    tokadd(c);
	    tokfix();
	    yylval.id = rb_intern(tok());
	    return tGVAR;

	  case '-':
	    tokadd('$');
	    tokadd(c);
	    c = nextc();
	    if (is_identchar(c)) {
		tokadd(c);
	    }
	    else {
		pushback(c);
	    }
	  gvar:
	    tokfix();
	    yylval.id = rb_intern(tok());
	    /* xxx shouldn't check if valid option variable */
	    return tGVAR;

	  case '&':		/* $&: last match */
	  case '`':		/* $`: string before last match */
	  case '\'':		/* $': string after last match */
	  case '+':		/* $+: string matches last paren. */
	    if (last_state == EXPR_FNAME) {
		tokadd('$');
		tokadd(c);
		goto gvar;
	    }
	    yylval.node = NEW_BACK_REF(c);
	    return tBACK_REF;

	  case '1': case '2': case '3':
	  case '4': case '5': case '6':
	  case '7': case '8': case '9':
	    tokadd('$');
	    do {
		tokadd(c);
		c = nextc();
	    } while (ISDIGIT(c));
	    pushback(c);
	    if (last_state == EXPR_FNAME) goto gvar;
	    tokfix();
	    yylval.node = NEW_NTH_REF(atoi(tok()+1));
	    return tNTH_REF;

	  default:
	    if (!is_identchar(c)) {
		pushback(c);
		return '$';
	    }
	  case '0':
	    tokadd('$');
	}
	break;

      case '@':
	c = nextc();
	newtok();
	tokadd('@');
	if (c == '@') {
	    tokadd('@');
	    c = nextc();
	}
	if (ISDIGIT(c)) {
	    if (tokidx == 1) {
		rb_compile_error("`@%c' is not allowed as an instance variable name", c);
	    }
	    else {
		rb_compile_error("`@@%c' is not allowed as a class variable name", c);
	    }
	}
	if (!is_identchar(c)) {
	    pushback(c);
	    return '@';
	}
	break;

      case '_':
	if (was_bol() && whole_match_p("__END__", 7, 0)) {
	    ruby__end__seen = 1;
	    lex_lastline = 0;
	    return -1;
	}
	newtok();
	break;

      default:
	if (!is_identchar(c)) {
	    rb_compile_error("Invalid char `\\%03o' in expression", c);
	    goto retry;
	}

	newtok();
	break;
    }

    do {
	tokadd(c);
	if (ismbchar(c)) {
	    int i, len = mbclen(c)-1;

	    for (i = 0; i < len; i++) {
		c = nextc();
		tokadd(c);
	    }
	}
	c = nextc();
    } while (is_identchar(c));
    if ((c == '!' || c == '?') && is_identchar(tok()[0]) && !peek('=')) {
	tokadd(c);
    }
    else {
	pushback(c);
    }
    tokfix();

    {
	int result = 0;

	last_state = lex_state;
	switch (tok()[0]) {
	  case '$':
	    lex_state = EXPR_END;
	    result = tGVAR;
	    break;
	  case '@':
	    lex_state = EXPR_END;
	    if (tok()[1] == '@')
		result = tCVAR;
	    else
		result = tIVAR;
	    break;

	  default:
	    if (toklast() == '!' || toklast() == '?') {
		result = tFID;
	    }
	    else {
		if (lex_state == EXPR_FNAME) {
		    if ((c = nextc()) == '=' && !peek('~') && !peek('>') &&
			(!peek('=') || (lex_p + 1 < lex_pend && lex_p[1] == '>'))) {
			result = tIDENTIFIER;
			tokadd(c);
			tokfix();
		    }
		    else {
			pushback(c);
		    }
		}
		if (result == 0 && ISUPPER(tok()[0])) {
		    result = tCONSTANT;
		}
		else {
		    result = tIDENTIFIER;
		}
	    }

	    if (lex_state != EXPR_DOT) {
		struct kwtable *kw;

		/* See if it is a reserved word.  */
		kw = rb_reserved_word(tok(), toklen());
		if (kw) {
		    enum lex_state state = lex_state;
		    lex_state = kw->state;
		    if (state == EXPR_FNAME) {
			yylval.id = rb_intern(kw->name);
		    }
		    if (kw->id[0] == kDO) {
			if (COND_P()) return kDO_COND;
			if (CMDARG_P() && state != EXPR_CMDARG)
			    return kDO_BLOCK;
			if (state == EXPR_ENDARG)
			    return kDO_BLOCK;
			return kDO;
		    }
		    if (state == EXPR_BEG)
			return kw->id[0];
		    else {
			if (kw->id[0] != kw->id[1])
			    lex_state = EXPR_BEG;
			return kw->id[1];
		    }
		}
	    }

	    if (lex_state == EXPR_BEG ||
		lex_state == EXPR_MID ||
		lex_state == EXPR_DOT ||
		lex_state == EXPR_ARG ||
		lex_state == EXPR_CMDARG) {
		if (cmd_state) {
		    lex_state = EXPR_CMDARG;
		}
		else {
		    lex_state = EXPR_ARG;
		}
	    }
	    else {
		lex_state = EXPR_END;
	    }
	}
	yylval.id = rb_intern(tok());
	if (is_local_id(yylval.id) &&
	    last_state != EXPR_DOT &&
	    ((dyna_in_block() && rb_dvar_defined(yylval.id)) || local_id(yylval.id))) {
	    lex_state = EXPR_END;
	}
	return result;
    }
}

NODE*
rb_node_newnode(type, a0, a1, a2)
    enum node_type type;
    VALUE a0, a1, a2;
{
    NODE *n = (NODE*)rb_newobj();

    n->flags |= T_NODE;
    nd_set_type(n, type);
    nd_set_line(n, ruby_sourceline);
    n->nd_file = ruby_sourcefile;

    n->u1.value = a0;
    n->u2.value = a1;
    n->u3.value = a2;

    return n;
}

static enum node_type
nodetype(node)			/* for debug */
    NODE *node;
{
    return (enum node_type)nd_type(node);
}

static int
nodeline(node)
    NODE *node;
{
    return nd_line(node);
}

static NODE*
newline_node(node)
    NODE *node;
{
    NODE *nl = 0;
    if (node) {
	if (nd_type(node) == NODE_NEWLINE) return node;
        nl = NEW_NEWLINE(node);
        fixpos(nl, node);
        nl->nd_nth = nd_line(node);
    }
    return nl;
}

static void
fixpos(node, orig)
    NODE *node, *orig;
{
    if (!node) return;
    if (!orig) return;
    if (orig == (NODE*)1) return;
    node->nd_file = orig->nd_file;
    nd_set_line(node, nd_line(orig));
}

static void
parser_warning(node, mesg)
    NODE *node;
    const char *mesg;
{
    int line = ruby_sourceline;
    ruby_sourceline = nd_line(node);
    rb_warning(mesg);
    ruby_sourceline = line;
}

static void
parser_warn(node, mesg)
    NODE *node;
    const char *mesg;
{
    int line = ruby_sourceline;
    ruby_sourceline = nd_line(node);
    rb_warn(mesg);
    ruby_sourceline = line;
}

static NODE*
block_append(head, tail)
    NODE *head, *tail;
{
    NODE *end, *h = head;

    if (tail == 0) return head;

  again:
    if (h == 0) return tail;
    switch (nd_type(h)) {
      case NODE_NEWLINE:
	h = h->nd_next;
	goto again;
      case NODE_LIT:
      case NODE_STR:
	parser_warning(h, "unused literal ignored");
	return tail;
      default:
	h = end = NEW_BLOCK(head);
	end->nd_end = end;
	fixpos(end, head);
	head = end;
	break;
      case NODE_BLOCK:
	end = h->nd_end;
	break;
    }

    if (RTEST(ruby_verbose)) {
	NODE *nd = end->nd_head;
      newline:
	switch (nd_type(nd)) {
	  case NODE_RETURN:
	  case NODE_BREAK:
	  case NODE_NEXT:
	  case NODE_REDO:
	  case NODE_RETRY:
	    parser_warning(nd, "statement not reached");
	    break;

	case NODE_NEWLINE:
	    nd = nd->nd_next;
	    goto newline;

	  default:
	    break;
	}
    }

    if (nd_type(tail) != NODE_BLOCK) {
	tail = NEW_BLOCK(tail);
	tail->nd_end = tail;
    }
    end->nd_next = tail;
    h->nd_end = tail->nd_end;
    return head;
}

/* append item to the list */
static NODE*
list_append(list, item)
    NODE *list, *item;
{
    NODE *last;

    if (list == 0) return NEW_LIST(item);
    if (list->nd_next) {
	last = list->nd_next->nd_end;
    }
    else {
	last = list;
    }

    list->nd_alen += 1;
    last->nd_next = NEW_LIST(item);
    list->nd_next->nd_end = last->nd_next;
    return list;
}

/* concat two lists */
static NODE*
list_concat(head, tail)
    NODE *head, *tail;
{
    NODE *last;

    if (head->nd_next) {
	last = head->nd_next->nd_end;
    }
    else {
	last = head;
    }

    head->nd_alen += tail->nd_alen;
    last->nd_next = tail;
    if (tail->nd_next) {
	head->nd_next->nd_end = tail->nd_next->nd_end;
    }
    else {
	head->nd_next->nd_end = tail;
    }

    return head;
}

/* concat two string literals */
static NODE *
literal_concat(head, tail)
    NODE *head, *tail;
{
    enum node_type htype;

    if (!head) return tail;
    if (!tail) return head;

    htype = nd_type(head);
    if (htype == NODE_EVSTR) {
	NODE *node = NEW_DSTR(rb_str_new(0, 0));
	head = list_append(node, head);
    }
    switch (nd_type(tail)) {
      case NODE_STR:
	if (htype == NODE_STR) {
	    rb_str_concat(head->nd_lit, tail->nd_lit);
	    rb_gc_force_recycle((VALUE)tail);
	}
	else {
	    list_append(head, tail);
	}
	break;

      case NODE_DSTR:
	if (htype == NODE_STR) {
	    rb_str_concat(head->nd_lit, tail->nd_lit);
	    tail->nd_lit = head->nd_lit;
	    rb_gc_force_recycle((VALUE)head);
	    head = tail;
	}
	else {
	    nd_set_type(tail, NODE_ARRAY);
	    tail->nd_head = NEW_STR(tail->nd_lit);
	    list_concat(head, tail);
	}
	break;

      case NODE_EVSTR:
	if (htype == NODE_STR) {
	    nd_set_type(head, NODE_DSTR);
	    head->nd_alen = 1;
	}
	list_append(head, tail);
	break;
    }
    return head;
}

static NODE *
evstr2dstr(node)
    NODE *node;
{
    if (nd_type(node) == NODE_EVSTR) {
	node = list_append(NEW_DSTR(rb_str_new(0, 0)), node);
    }
    return node;
}

static NODE *
new_evstr(node)
    NODE *node;
{
    NODE *head = node;

  again:
    if (node) {
	switch (nd_type(node)) {
	  case NODE_STR: case NODE_DSTR: case NODE_EVSTR:
	    return node;
	  case NODE_NEWLINE:
	    node = node->nd_next;
	    goto again;
	}
    }
    return NEW_EVSTR(head);
}

static NODE *
call_op(recv, id, narg, arg1)
    NODE *recv;
    ID id;
    int narg;
    NODE *arg1;
{
    value_expr(recv);
    if (narg == 1) {
	value_expr(arg1);
	arg1 = NEW_LIST(arg1);
    }
    else {
	arg1 = 0;
    }
    return NEW_CALL(recv, id, arg1);
}

static NODE*
match_gen(node1, node2)
    NODE *node1;
    NODE *node2;
{
    local_cnt('~');

    value_expr(node1);
    value_expr(node2);
    if (node1) {
	switch (nd_type(node1)) {
	  case NODE_DREGX:
	  case NODE_DREGX_ONCE:
	    return NEW_MATCH2(node1, node2);

	  case NODE_LIT:
	    if (TYPE(node1->nd_lit) == T_REGEXP) {
		return NEW_MATCH2(node1, node2);
	    }
	}
    }

    if (node2) {
	switch (nd_type(node2)) {
	  case NODE_DREGX:
	  case NODE_DREGX_ONCE:
	    return NEW_MATCH3(node2, node1);

	  case NODE_LIT:
	    if (TYPE(node2->nd_lit) == T_REGEXP) {
		return NEW_MATCH3(node2, node1);
	    }
	}
    }

    return NEW_CALL(node1, tMATCH, NEW_LIST(node2));
}

static NODE*
gettable(id)
    ID id;
{
    if (id == kSELF) {
	return NEW_SELF();
    }
    else if (id == kNIL) {
	return NEW_NIL();
    }
    else if (id == kTRUE) {
	return NEW_TRUE();
    }
    else if (id == kFALSE) {
	return NEW_FALSE();
    }
    else if (id == k__FILE__) {
	return NEW_STR(rb_str_new2(ruby_sourcefile));
    }
    else if (id == k__LINE__) {
	return NEW_LIT(INT2FIX(ruby_sourceline));
    }
    else if (is_local_id(id)) {
	if (dyna_in_block() && rb_dvar_defined(id)) return NEW_DVAR(id);
	if (local_id(id)) return NEW_LVAR(id);
	/* method call without arguments */
#if 0
	/* Rite will warn this */
	rb_warn("ambiguous identifier; %s() or self.%s is better for method call",
		rb_id2name(id), rb_id2name(id));
#endif
	return NEW_VCALL(id);
    }
    else if (is_global_id(id)) {
	return NEW_GVAR(id);
    }
    else if (is_instance_id(id)) {
	return NEW_IVAR(id);
    }
    else if (is_const_id(id)) {
	return NEW_CONST(id);
    }
    else if (is_class_id(id)) {
	return NEW_CVAR(id);
    }
    rb_compile_error("identifier %s is not valid", rb_id2name(id));
    return 0;
}

static NODE*
assignable(id, val)
    ID id;
    NODE *val;
{
    value_expr(val);
    if (id == kSELF) {
	yyerror("Can't change the value of self");
    }
    else if (id == kNIL) {
	yyerror("Can't assign to nil");
    }
    else if (id == kTRUE) {
	yyerror("Can't assign to true");
    }
    else if (id == kFALSE) {
	yyerror("Can't assign to false");
    }
    else if (id == k__FILE__) {
	yyerror("Can't assign to __FILE__");
    }
    else if (id == k__LINE__) {
	yyerror("Can't assign to __LINE__");
    }
    else if (is_local_id(id)) {
	if (rb_dvar_curr(id)) {
	    return NEW_DASGN_CURR(id, val);
	}
	else if (rb_dvar_defined(id)) {
	    return NEW_DASGN(id, val);
	}
	else if (local_id(id) || !dyna_in_block()) {
	    return NEW_LASGN(id, val);
	}
	else{
	    rb_dvar_push(id, Qnil);
	    return NEW_DASGN_CURR(id, val);
	}
    }
    else if (is_global_id(id)) {
	return NEW_GASGN(id, val);
    }
    else if (is_instance_id(id)) {
	return NEW_IASGN(id, val);
    }
    else if (is_const_id(id)) {
	if (in_def || in_single)
	    yyerror("dynamic constant assignment");
	return NEW_CDECL(id, val, 0);
    }
    else if (is_class_id(id)) {
	if (in_def || in_single) return NEW_CVASGN(id, val);
	return NEW_CVDECL(id, val);
    }
    else {
	rb_compile_error("identifier %s is not valid", rb_id2name(id));
    }
    return 0;
}

static NODE *
aryset(recv, idx)
    NODE *recv, *idx;
{
    if (recv && nd_type(recv) == NODE_SELF)
	recv = (NODE *)1;
    else
	value_expr(recv);
    return NEW_ATTRASGN(recv, tASET, idx);
}

ID
rb_id_attrset(id)
    ID id;
{
    id &= ~ID_SCOPE_MASK;
    id |= ID_ATTRSET;
    return id;
}

static NODE *
attrset(recv, id)
    NODE *recv;
    ID id;
{
    if (recv && nd_type(recv) == NODE_SELF)
	recv = (NODE *)1;
    else
	value_expr(recv);
    return NEW_ATTRASGN(recv, rb_id_attrset(id), 0);
}

static void
rb_backref_error(node)
    NODE *node;
{
    switch (nd_type(node)) {
      case NODE_NTH_REF:
	rb_compile_error("Can't set variable $%d", node->nd_nth);
	break;
      case NODE_BACK_REF:
	rb_compile_error("Can't set variable $%c", (int)node->nd_nth);
	break;
    }
}

static NODE *
arg_concat(node1, node2)
    NODE *node1;
    NODE *node2;
{
    if (!node2) return node1;
    return NEW_ARGSCAT(node1, node2);
}

static NODE *
arg_add(node1, node2)
    NODE *node1;
    NODE *node2;
{
    if (!node1) return NEW_LIST(node2);
    if (nd_type(node1) == NODE_ARRAY) {
	return list_append(node1, node2);
    }
    else {
	return NEW_ARGSPUSH(node1, node2);
    }
}

static NODE*
node_assign(lhs, rhs)
    NODE *lhs, *rhs;
{
    if (!lhs) return 0;

    value_expr(rhs);
    switch (nd_type(lhs)) {
      case NODE_GASGN:
      case NODE_IASGN:
      case NODE_LASGN:
      case NODE_DASGN:
      case NODE_DASGN_CURR:
      case NODE_MASGN:
      case NODE_CDECL:
      case NODE_CVDECL:
      case NODE_CVASGN:
	lhs->nd_value = rhs;
	break;

      case NODE_ATTRASGN:
      case NODE_CALL:
	lhs->nd_args = arg_add(lhs->nd_args, rhs);
	break;

      default:
	/* should not happen */
	break;
    }

    return lhs;
}

static int
value_expr0(node)
    NODE *node;
{
    int cond = 0;

    while (node) {
	switch (nd_type(node)) {
	  case NODE_DEFN:
	  case NODE_DEFS:
	    parser_warning(node, "void value expression");
	    return Qfalse;

	  case NODE_RETURN:
	  case NODE_BREAK:
	  case NODE_NEXT:
	  case NODE_REDO:
	  case NODE_RETRY:
	    if (!cond) yyerror("void value expression");
	    /* or "control never reach"? */
	    return Qfalse;

	  case NODE_BLOCK:
	    while (node->nd_next) {
		node = node->nd_next;
	    }
	    node = node->nd_head;
	    break;

	  case NODE_BEGIN:
	    node = node->nd_body;
	    break;

	  case NODE_IF:
	    if (!value_expr(node->nd_body)) return Qfalse;
	    node = node->nd_else;
	    break;

	  case NODE_AND:
	  case NODE_OR:
	    cond = 1;
	    node = node->nd_2nd;
	    break;

	  case NODE_NEWLINE:
	    node = node->nd_next;
	    break;

	  default:
	    return Qtrue;
	}
    }

    return Qtrue;
}

static void
void_expr0(node)
    NODE *node;
{
    char *useless = 0;

    if (!RTEST(ruby_verbose)) return;

  again:
    if (!node) return;
    switch (nd_type(node)) {
      case NODE_NEWLINE:
	node = node->nd_next;
	goto again;

      case NODE_CALL:
	switch (node->nd_mid) {
	  case '+':
	  case '-':
	  case '*':
	  case '/':
	  case '%':
	  case tPOW:
	  case tUPLUS:
	  case tUMINUS:
	  case '|':
	  case '^':
	  case '&':
	  case tCMP:
	  case '>':
	  case tGEQ:
	  case '<':
	  case tLEQ:
	  case tEQ:
	  case tNEQ:
	    useless = rb_id2name(node->nd_mid);
	    break;
	}
	break;

      case NODE_LVAR:
      case NODE_DVAR:
      case NODE_GVAR:
      case NODE_IVAR:
      case NODE_CVAR:
      case NODE_NTH_REF:
      case NODE_BACK_REF:
	useless = "a variable";
	break;
      case NODE_CONST:
      case NODE_CREF:
	useless = "a constant";
	break;
      case NODE_LIT:
      case NODE_STR:
      case NODE_DSTR:
      case NODE_DREGX:
      case NODE_DREGX_ONCE:
	useless = "a literal";
	break;
      case NODE_COLON2:
      case NODE_COLON3:
	useless = "::";
	break;
      case NODE_DOT2:
	useless = "..";
	break;
      case NODE_DOT3:
	useless = "...";
	break;
      case NODE_SELF:
	useless = "self";
	break;
      case NODE_NIL:
	useless = "nil";
	break;
      case NODE_TRUE:
	useless = "true";
	break;
      case NODE_FALSE:
	useless = "false";
	break;
      case NODE_DEFINED:
	useless = "defined?";
	break;
    }

    if (useless) {
	int line = ruby_sourceline;

	ruby_sourceline = nd_line(node);
	rb_warn("useless use of %s in void context", useless);
	ruby_sourceline = line;
    }
}

static void
void_stmts(node)
    NODE *node;
{
    if (!RTEST(ruby_verbose)) return;
    if (!node) return;
    if (nd_type(node) != NODE_BLOCK) return;

    for (;;) {
	if (!node->nd_next) return;
	void_expr(node->nd_head);
	node = node->nd_next;
    }
}

static NODE *
remove_begin(node)
    NODE *node;
{
    NODE **n = &node;
    while (*n) {
	switch (nd_type(*n)) {
	  case NODE_NEWLINE:
	    n = &(*n)->nd_next;
	    continue;
	  case NODE_BEGIN:
	    *n = (*n)->nd_body;
	  default:
	    return node;
	}
    }
    return node;
}

static int
assign_in_cond(node)
    NODE *node;
{
    switch (nd_type(node)) {
      case NODE_MASGN:
	yyerror("multiple assignment in conditional");
	return 1;

      case NODE_LASGN:
      case NODE_DASGN:
      case NODE_GASGN:
      case NODE_IASGN:
	break;

      case NODE_NEWLINE:
      default:
	return 0;
    }

    switch (nd_type(node->nd_value)) {
      case NODE_LIT:
      case NODE_STR:
      case NODE_NIL:
      case NODE_TRUE:
      case NODE_FALSE:
	/* reports always */
	parser_warn(node->nd_value, "found = in conditional, should be ==");
	return 1;

      case NODE_DSTR:
      case NODE_XSTR:
      case NODE_DXSTR:
      case NODE_EVSTR:
      case NODE_DREGX:
      default:
	break;
    }
#if 0
    if (assign_in_cond(node->nd_value) == 0) {
	parser_warning(node->nd_value, "assignment in condition");
    }
#endif
    return 1;
}

static int
e_option_supplied()
{
    if (strcmp(ruby_sourcefile, "-e") == 0)
	return Qtrue;
    return Qfalse;
}

static void
warn_unless_e_option(node, str)
    NODE *node;
    const char *str;
{
    if (!e_option_supplied()) parser_warn(node, str);
}

static void
warning_unless_e_option(node, str)
    NODE *node;
    const char *str;
{
    if (!e_option_supplied()) parser_warning(node, str);
}

static NODE *cond0();

static NODE*
range_op(node)
    NODE *node;
{
    enum node_type type;

    if (!e_option_supplied()) return node;
    if (node == 0) return 0;

    value_expr(node);
    node = cond0(node);
    type = nd_type(node);
    if (type == NODE_NEWLINE) {
	node = node->nd_next;
	type = nd_type(node);
    }
    if (type == NODE_LIT && FIXNUM_P(node->nd_lit)) {
	warn_unless_e_option(node, "integer literal in conditional range");
	return call_op(node,tEQ,1,NEW_GVAR(rb_intern("$.")));
    }
    return node;
}

static int
literal_node(node)
    NODE *node;
{
    if (!node) return 1;	/* same as NODE_NIL */
    switch (nd_type(node)) {
      case NODE_LIT:
      case NODE_STR:
      case NODE_DSTR:
      case NODE_EVSTR:
      case NODE_DREGX:
      case NODE_DREGX_ONCE:
      case NODE_DSYM:
	return 2;
      case NODE_TRUE:
      case NODE_FALSE:
      case NODE_NIL:
	return 1;
    }
    return 0;
}

static NODE*
cond0(node)
    NODE *node;
{
    if (node == 0) return 0;
    assign_in_cond(node);

    switch (nd_type(node)) {
      case NODE_DSTR:
      case NODE_EVSTR:
      case NODE_STR:
	rb_warn("string literal in condition");
	break;

      case NODE_DREGX:
      case NODE_DREGX_ONCE:
	warning_unless_e_option(node, "regex literal in condition");
	local_cnt('_');
	local_cnt('~');
	return NEW_MATCH2(node, NEW_GVAR(rb_intern("$_")));

      case NODE_AND:
      case NODE_OR:
	node->nd_1st = cond0(node->nd_1st);
	node->nd_2nd = cond0(node->nd_2nd);
	break;

      case NODE_DOT2:
      case NODE_DOT3:
	node->nd_beg = range_op(node->nd_beg);
	node->nd_end = range_op(node->nd_end);
	if (nd_type(node) == NODE_DOT2) nd_set_type(node,NODE_FLIP2);
	else if (nd_type(node) == NODE_DOT3) nd_set_type(node, NODE_FLIP3);
	node->nd_cnt = local_append(internal_id());
	if (!e_option_supplied()) {
	    int b = literal_node(node->nd_beg);
	    int e = literal_node(node->nd_end);
	    if ((b == 1 && e == 1) || (b + e >= 2 && RTEST(ruby_verbose))) {
		parser_warn(node, "range literal in condition");
	    }
	}
	break;

      case NODE_DSYM:
	parser_warning(node, "literal in condition");
	break;

      case NODE_LIT:
	if (TYPE(node->nd_lit) == T_REGEXP) {
	    warn_unless_e_option(node, "regex literal in condition");
	    nd_set_type(node, NODE_MATCH);
	    local_cnt('_');
	    local_cnt('~');
	}
	else {
	    parser_warning(node, "literal in condition");
	}
      default:
	break;
    }
    return node;
}

static NODE*
cond(node)
    NODE *node;
{
    if (node == 0) return 0;
    value_expr(node);
    if (nd_type(node) == NODE_NEWLINE){
	node->nd_next = cond0(node->nd_next);
	return node;
    }
    return cond0(node);
}

static NODE*
logop(type, left, right)
    enum node_type type;
    NODE *left, *right;
{
    value_expr(left);
    if (left && nd_type(left) == type) {
	NODE *node = left, *second;
	while ((second = node->nd_2nd) != 0 && nd_type(second) == type) {
	    node = second;
	}
	node->nd_2nd = NEW_NODE(type, second, right, 0);
	return left;
    }
    return NEW_NODE(type, left, right, 0);
}

static int
cond_negative(nodep)
    NODE **nodep;
{
    NODE *c = *nodep;

    if (!c) return 0;
    switch (nd_type(c)) {
      case NODE_NOT:
	*nodep = c->nd_body;
	return 1;
      case NODE_NEWLINE:
	if (c->nd_next && nd_type(c->nd_next) == NODE_NOT) {
	    c->nd_next = c->nd_next->nd_body;
	    return 1;
	}
    }
    return 0;
}

static void
no_blockarg(node)
    NODE *node;
{
    if (node && nd_type(node) == NODE_BLOCK_PASS) {
	rb_compile_error("block argument should not be given");
    }
}

static NODE *
ret_args(node)
    NODE *node;
{
    if (node) {
	no_blockarg(node);
	if (nd_type(node) == NODE_ARRAY && node->nd_next == 0) {
	    node = node->nd_head;
	}
	if (node && nd_type(node) == NODE_SPLAT) {
	    node = NEW_SVALUE(node);
	}
    }
    return node;
}

static NODE *
new_yield(node)
    NODE *node;
{
    long state = Qtrue;

    if (node) {
        no_blockarg(node);
        if (nd_type(node) == NODE_ARRAY && node->nd_next == 0) {
            node = node->nd_head;
            state = Qfalse;
        }
        if (node && nd_type(node) == NODE_SPLAT) {
            state = Qtrue;
        }
    }
    else {
        state = Qfalse;
    }
    return NEW_YIELD(node, state);
}

static NODE*
negate_lit(node)
    NODE *node;
{
    switch (TYPE(node->nd_lit)) {
      case T_FIXNUM:
	node->nd_lit = LONG2FIX(-FIX2LONG(node->nd_lit));
	break;
      case T_BIGNUM:
	node->nd_lit = rb_funcall(node->nd_lit,tUMINUS,0,0);
	break;
      case T_FLOAT:
	RFLOAT(node->nd_lit)->value = -RFLOAT(node->nd_lit)->value;
	break;
      default:
	break;
    }
    return node;
}

static NODE *
arg_blk_pass(node1, node2)
    NODE *node1;
    NODE *node2;
{
    if (node2) {
	node2->nd_head = node1;
	return node2;
    }
    return node1;
}

static NODE*
arg_prepend(node1, node2)
    NODE *node1, *node2;
{
    switch (nd_type(node2)) {
      case NODE_ARRAY:
	return list_concat(NEW_LIST(node1), node2);

      case NODE_SPLAT:
	return arg_concat(node1, node2->nd_head);

      case NODE_BLOCK_PASS:
	node2->nd_body = arg_prepend(node1, node2->nd_body);
	return node2;

      default:
	rb_bug("unknown nodetype(%d) for arg_prepend", nd_type(node2));
    }
    return 0;			/* not reached */
}

static NODE*
new_call(r,m,a)
    NODE *r;
    ID m;
    NODE *a;
{
    if (a && nd_type(a) == NODE_BLOCK_PASS) {
	a->nd_iter = NEW_CALL(r,m,a->nd_head);
	return a;
    }
    return NEW_CALL(r,m,a);
}

static NODE*
new_fcall(m,a)
    ID m;
    NODE *a;
{
    if (a && nd_type(a) == NODE_BLOCK_PASS) {
	a->nd_iter = NEW_FCALL(m,a->nd_head);
	return a;
    }
    return NEW_FCALL(m,a);
}

static NODE*
new_super(a)
    NODE *a;
{
    if (a && nd_type(a) == NODE_BLOCK_PASS) {
	a->nd_iter = NEW_SUPER(a->nd_head);
	return a;
    }
    return NEW_SUPER(a);
}

static struct local_vars {
    ID *tbl;
    int nofree;
    int cnt;
    int dlev;
    struct RVarmap* dyna_vars;
    struct local_vars *prev;
} *lvtbl;

static void
local_push(top)
    int top;
{
    struct local_vars *local;

    local = ALLOC(struct local_vars);
    local->prev = lvtbl;
    local->nofree = 0;
    local->cnt = 0;
    local->tbl = 0;
    local->dlev = 0;
    local->dyna_vars = ruby_dyna_vars;
    lvtbl = local;
    if (!top) {
	/* preserve reference for GC, but link should be cut. */
	rb_dvar_push(0, (VALUE)ruby_dyna_vars);
	ruby_dyna_vars->next = 0;
    }
}

static void
local_pop()
{
    struct local_vars *local = lvtbl->prev;

    if (lvtbl->tbl) {
	if (!lvtbl->nofree) xfree(lvtbl->tbl);
	else lvtbl->tbl[0] = lvtbl->cnt;
    }
    ruby_dyna_vars = lvtbl->dyna_vars;
    xfree(lvtbl);
    lvtbl = local;
}

static ID*
local_tbl()
{
    lvtbl->nofree = 1;
    return lvtbl->tbl;
}

static int
local_append(id)
    ID id;
{
    if (lvtbl->tbl == 0) {
	lvtbl->tbl = ALLOC_N(ID, 4);
	lvtbl->tbl[0] = 0;
	lvtbl->tbl[1] = '_';
	lvtbl->tbl[2] = '~';
	lvtbl->cnt = 2;
	if (id == '_') return 0;
	if (id == '~') return 1;
    }
    else {
	REALLOC_N(lvtbl->tbl, ID, lvtbl->cnt+2);
    }

    lvtbl->tbl[lvtbl->cnt+1] = id;
    return lvtbl->cnt++;
}

static int
local_cnt(id)
    ID id;
{
    int cnt, max;

    if (id == 0) return lvtbl->cnt;

    for (cnt=1, max=lvtbl->cnt+1; cnt<max;cnt++) {
	if (lvtbl->tbl[cnt] == id) return cnt-1;
    }
    return local_append(id);
}

static int
local_id(id)
    ID id;
{
    int i, max;

    if (lvtbl == 0) return Qfalse;
    for (i=3, max=lvtbl->cnt+1; i<max; i++) {
	if (lvtbl->tbl[i] == id) return Qtrue;
    }
    return Qfalse;
}

static void
top_local_init()
{
    local_push(1);
    lvtbl->cnt = ruby_scope->local_tbl?ruby_scope->local_tbl[0]:0;
    if (lvtbl->cnt > 0) {
	lvtbl->tbl = ALLOC_N(ID, lvtbl->cnt+3);
	MEMCPY(lvtbl->tbl, ruby_scope->local_tbl, ID, lvtbl->cnt+1);
    }
    else {
	lvtbl->tbl = 0;
    }
    if (ruby_dyna_vars)
	lvtbl->dlev = 1;
    else
	lvtbl->dlev = 0;
}

static void
top_local_setup()
{
    int len = lvtbl->cnt;
    int i;

    if (len > 0) {
	i = ruby_scope->local_tbl?ruby_scope->local_tbl[0]:0;

	if (i < len) {
	    if (i == 0 || (ruby_scope->flags & SCOPE_MALLOC) == 0) {
		VALUE *vars = ALLOC_N(VALUE, len+1);
		if (ruby_scope->local_vars) {
		    *vars++ = ruby_scope->local_vars[-1];
		    MEMCPY(vars, ruby_scope->local_vars, VALUE, i);
		    rb_mem_clear(vars+i, len-i);
		}
		else {
		    *vars++ = 0;
		    rb_mem_clear(vars, len);
		}
		ruby_scope->local_vars = vars;
		ruby_scope->flags |= SCOPE_MALLOC;
	    }
	    else {
		VALUE *vars = ruby_scope->local_vars-1;
		REALLOC_N(vars, VALUE, len+1);
		ruby_scope->local_vars = vars+1;
		rb_mem_clear(ruby_scope->local_vars+i, len-i);
	    }
	    if (ruby_scope->local_tbl && ruby_scope->local_vars[-1] == 0) {
		xfree(ruby_scope->local_tbl);
	    }
	    ruby_scope->local_vars[-1] = 0;
	    ruby_scope->local_tbl = local_tbl();
	}
    }
    local_pop();
}

static struct RVarmap*
dyna_push()
{
    struct RVarmap* vars = ruby_dyna_vars;

    rb_dvar_push(0, 0);
    lvtbl->dlev++;
    return vars;
}

static void
dyna_pop(vars)
    struct RVarmap* vars;
{
    lvtbl->dlev--;
    ruby_dyna_vars = vars;
}

static int
dyna_in_block()
{
    return (lvtbl->dlev > 0);
}

static NODE *
dyna_init(node, pre)
    NODE *node;
    struct RVarmap *pre;
{
    struct RVarmap *post = ruby_dyna_vars;
    NODE *var;

    if (!node || !post || pre == post) return node;
    for (var = 0; post != pre && post->id; post = post->next) {
	var = NEW_DASGN_CURR(post->id, var);
    }
    return block_append(var, node);
}

int
ruby_parser_stack_on_heap()
{
#if defined(YYMALLOC)
    return Qfalse;
#else
    return Qtrue;
#endif
}

void
rb_gc_mark_parser()
{
#if defined YYMALLOC
    rb_gc_mark((VALUE)parser_heap);
#elif defined yystacksize
    if (yyvsp) rb_gc_mark_locations((VALUE *)yyvs, (VALUE *)yyvsp);
#endif

    if (!ruby_in_compile) return;

    rb_gc_mark_maybe((VALUE)yylval.node);
    rb_gc_mark(ruby_debug_lines);
    rb_gc_mark(lex_lastline);
    rb_gc_mark(lex_input);
    rb_gc_mark((VALUE)lex_strterm);
}

void
rb_parser_append_print()
{
    ruby_eval_tree =
	block_append(ruby_eval_tree,
		     NEW_FCALL(rb_intern("print"),
			       NEW_ARRAY(NEW_GVAR(rb_intern("$_")))));
}

void
rb_parser_while_loop(chop, split)
    int chop, split;
{
    if (split) {
	ruby_eval_tree =
	    block_append(NEW_GASGN(rb_intern("$F"),
				   NEW_CALL(NEW_GVAR(rb_intern("$_")),
					    rb_intern("split"), 0)),
				   ruby_eval_tree);
    }
    if (chop) {
	ruby_eval_tree =
	    block_append(NEW_CALL(NEW_GVAR(rb_intern("$_")),
				  rb_intern("chop!"), 0), ruby_eval_tree);
    }
    ruby_eval_tree = NEW_OPT_N(ruby_eval_tree);
}

static struct {
    ID token;
    char *name;
} op_tbl[] = {
    {tDOT2,	".."},
    {tDOT3,	"..."},
    {'+',	"+"},
    {'-',	"-"},
    {'+',	"+(binary)"},
    {'-',	"-(binary)"},
    {'*',	"*"},
    {'/',	"/"},
    {'%',	"%"},
    {tPOW,	"**"},
    {tUPLUS,	"+@"},
    {tUMINUS,	"-@"},
    {tUPLUS,	"+(unary)"},
    {tUMINUS,	"-(unary)"},
    {'|',	"|"},
    {'^',	"^"},
    {'&',	"&"},
    {tCMP,	"<=>"},
    {'>',	">"},
    {tGEQ,	">="},
    {'<',	"<"},
    {tLEQ,	"<="},
    {tEQ,	"=="},
    {tEQQ,	"==="},
    {tNEQ,	"!="},
    {tMATCH,	"=~"},
    {tNMATCH,	"!~"},
    {'!',	"!"},
    {'~',	"~"},
    {'!',	"!(unary)"},
    {'~',	"~(unary)"},
    {'!',	"!@"},
    {'~',	"~@"},
    {tAREF,	"[]"},
    {tASET,	"[]="},
    {tLSHFT,	"<<"},
    {tRSHFT,	">>"},
    {tCOLON2,	"::"},
    {'`',	"`"},
    {0,	0}
};

static st_table *sym_tbl;
static st_table *sym_rev_tbl;

void
Init_sym()
{
    sym_tbl = st_init_strtable_with_size(200);
    sym_rev_tbl = st_init_numtable_with_size(200);
}

static ID last_id = tLAST_TOKEN;

static ID
internal_id()
{
    return ID_INTERNAL | (++last_id << ID_SCOPE_SHIFT);
}

static int
is_special_global_name(m)
    const char *m;
{
    switch (*m) {
      case '~': case '*': case '$': case '?': case '!': case '@':
      case '/': case '\\': case ';': case ',': case '.': case '=':
      case ':': case '<': case '>': case '\"':
      case '&': case '`': case '\'': case '+':
      case '0':
	++m;
	break;
      case '-':
	++m;
	if (is_identchar(*m)) m += mbclen(*m);
	break;
      default:
	if (!ISDIGIT(*m)) return 0;
	do ++m; while (ISDIGIT(*m));
    }
    return !*m;
}

int
rb_symname_p(name)
    const char *name;
{
    const char *m = name;
    int localid = Qfalse;

    if (!m) return Qfalse;
    switch (*m) {
      case '\0':
	return Qfalse;

      case '$':
	if (is_special_global_name(++m)) return Qtrue;
	goto id;

      case '@':
	if (*++m == '@') ++m;
	goto id;

      case '<':
	switch (*++m) {
	  case '<': ++m; break;
	  case '=': if (*++m == '>') ++m; break;
	  default: break;
	}
	break;

      case '>':
	switch (*++m) {
	  case '>': case '=': ++m; break;
	}
	break;

      case '=':
	switch (*++m) {
	  case '~': ++m; break;
	  case '=': if (*++m == '=') ++m; break;
	  default: return Qfalse;
	}
	break;

      case '*':
	if (*++m == '*') ++m;
	break;

      case '+': case '-':
	if (*++m == '@') ++m;
	break;

      case '|': case '^': case '&': case '/': case '%': case '~': case '`':
	++m;
	break;

      case '[':
	if (*++m != ']') return Qfalse;
	if (*++m == '=') ++m;
	break;

      default:
	localid = !ISUPPER(*m);
      id:
	if (*m != '_' && !ISALPHA(*m) && !ismbchar(*m)) return Qfalse;
	while (is_identchar(*m)) m += mbclen(*m);
	if (localid) {
	    switch (*m) {
	      case '!': case '?': case '=': ++m;
	    }
	}
	break;
    }
    return *m ? Qfalse : Qtrue;
}

ID
rb_intern(name)
    const char *name;
{
    const char *m = name;
    ID id;
    int last;

    if (st_lookup(sym_tbl, (st_data_t)name, (st_data_t *)&id))
	return id;

    last = strlen(name)-1;
    id = 0;
    switch (*name) {
      case '$':
	id |= ID_GLOBAL;
	if (is_special_global_name(++m)) goto new_id;
	break;
      case '@':
	if (name[1] == '@') {
	    m++;
	    id |= ID_CLASS;
	}
	else {
	    id |= ID_INSTANCE;
	}
	m++;
	break;
      default:
	if (name[0] != '_' && ISASCII(name[0]) && !ISALNUM(name[0])) {
	    /* operators */
	    int i;

	    for (i=0; op_tbl[i].token; i++) {
		if (*op_tbl[i].name == *name &&
		    strcmp(op_tbl[i].name, name) == 0) {
		    id = op_tbl[i].token;
		    goto id_regist;
		}
	    }
	}

	if (name[last] == '=') {
	    /* attribute assignment */
	    char *buf = ALLOCA_N(char,last+1);

	    strncpy(buf, name, last);
	    buf[last] = '\0';
	    id = rb_intern(buf);
	    if (id > tLAST_TOKEN && !is_attrset_id(id)) {
		id = rb_id_attrset(id);
		goto id_regist;
	    }
	    id = ID_ATTRSET;
	}
	else if (ISUPPER(name[0])) {
	    id = ID_CONST;
        }
	else {
	    id = ID_LOCAL;
	}
	break;
    }
    if (!ISDIGIT(*m)) {
	while (m <= name + last && is_identchar(*m)) {
	    m += mbclen(*m);
	}
    }
    if (*m) id = ID_JUNK;
  new_id:
    id |= ++last_id << ID_SCOPE_SHIFT;
  id_regist:
    name = strdup(name);
    st_add_direct(sym_tbl, (st_data_t)name, id);
    st_add_direct(sym_rev_tbl, id, (st_data_t)name);
    return id;
}

char *
rb_id2name(id)
    ID id;
{
    char *name;

    if (id < tLAST_TOKEN) {
	int i = 0;

	for (i=0; op_tbl[i].token; i++) {
	    if (op_tbl[i].token == id)
		return op_tbl[i].name;
	}
    }

    if (st_lookup(sym_rev_tbl, id, (st_data_t *)&name))
	return name;

    if (is_attrset_id(id)) {
	ID id2 = (id & ~ID_SCOPE_MASK) | ID_LOCAL;

      again:
	name = rb_id2name(id2);
	if (name) {
	    char *buf = ALLOCA_N(char, strlen(name)+2);

	    strcpy(buf, name);
	    strcat(buf, "=");
	    rb_intern(buf);
	    return rb_id2name(id);
	}
	if (is_local_id(id2)) {
	    id2 = (id & ~ID_SCOPE_MASK) | ID_CONST;
	    goto again;
	}
    }
    return 0;
}

static int
symbols_i(key, value, ary)
    char *key;
    ID value;
    VALUE ary;
{
    rb_ary_push(ary, ID2SYM(value));
    return ST_CONTINUE;
}

/*
 *  call-seq:
 *     Symbol.all_symbols    => array
 *  
 *  Returns an array of all the symbols currently in Ruby's symbol
 *  table.
 *     
 *     Symbol.all_symbols.size    #=> 903
 *     Symbol.all_symbols[1,20]   #=> [:floor, :ARGV, :Binding, :symlink,
 *                                     :chown, :EOFError, :$;, :String, 
 *                                     :LOCK_SH, :"setuid?", :$<, 
 *                                     :default_proc, :compact, :extend, 
 *                                     :Tms, :getwd, :$=, :ThreadGroup,
 *                                     :wait2, :$>]
 */

VALUE
rb_sym_all_symbols()
{
    VALUE ary = rb_ary_new2(sym_tbl->num_entries);

    st_foreach(sym_tbl, symbols_i, ary);
    return ary;
}

int
rb_is_const_id(id)
    ID id;
{
    if (is_const_id(id)) return Qtrue;
    return Qfalse;
}

int
rb_is_class_id(id)
    ID id;
{
    if (is_class_id(id)) return Qtrue;
    return Qfalse;
}

int
rb_is_instance_id(id)
    ID id;
{
    if (is_instance_id(id)) return Qtrue;
    return Qfalse;
}

int
rb_is_local_id(id)
    ID id;
{
    if (is_local_id(id)) return Qtrue;
    return Qfalse;
}

int
rb_is_junk_id(id)
    ID id;
{
    if (is_junk_id(id)) return Qtrue;
    return Qfalse;
}

static void
special_local_set(c, val)
    char c;
    VALUE val;
{
    int cnt;

    top_local_init();
    cnt = local_cnt(c);
    top_local_setup();
    ruby_scope->local_vars[cnt] = val;
}

VALUE
rb_backref_get()
{
    VALUE *var = rb_svar(1);
    if (var) {
	return *var;
    }
    return Qnil;
}

void
rb_backref_set(val)
    VALUE val;
{
    VALUE *var = rb_svar(1);
    if (var) {
	*var = val;
    }
    else {
	special_local_set('~', val);
    }
}

VALUE
rb_lastline_get()
{
    VALUE *var = rb_svar(0);
    if (var) {
	return *var;
    }
    return Qnil;
}

void
rb_lastline_set(val)
    VALUE val;
{
    VALUE *var = rb_svar(0);
    if (var) {
	*var = val;
    }
    else {
	special_local_set('_', val);
    }
}

#ifdef YYMALLOC
#define HEAPCNT(n, size) ((n) * (size) / sizeof(YYSTYPE))
#define NEWHEAP() rb_node_newnode(NODE_ALLOCA, 0, (VALUE)parser_heap, 0)
#define ADD2HEAP(n, c, p) ((parser_heap = (n))->u1.node = (p), \
			   (n)->u3.cnt = (c), (p))

static void *
rb_parser_malloc(size)
    size_t size;
{
    size_t cnt = HEAPCNT(1, size);
    NODE *n = NEWHEAP();
    void *ptr = xmalloc(size);

    return ADD2HEAP(n, cnt, ptr);
}

static void *
rb_parser_calloc(nelem, size)
    size_t nelem, size;
{
    size_t cnt = HEAPCNT(nelem, size);
    NODE *n = NEWHEAP();
    void *ptr = xcalloc(nelem, size);

    return ADD2HEAP(n, cnt, ptr);
}

static void *
rb_parser_realloc(ptr, size)
    void *ptr;
    size_t size;
{
    NODE *n;
    size_t cnt = HEAPCNT(1, size);

    if (ptr && (n = parser_heap) != NULL) {
	do {
	    if (n->u1.node == ptr) {
		n->u1.node = ptr = xrealloc(ptr, size);
		if (n->u3.cnt) n->u3.cnt = cnt;
		return ptr;
	    }
	} while ((n = n->u2.node) != NULL);
    }
    n = NEWHEAP();
    ptr = xrealloc(ptr, size);
    return ADD2HEAP(n, cnt, ptr);
}

static void
rb_parser_free(ptr)
    void *ptr;
{
    NODE **prev = &parser_heap, *n;

    while (n = *prev) {
	if (n->u1.node == ptr) {
	    *prev = n->u2.node;
	    rb_gc_force_recycle((VALUE)n);
	    break;
	}
	prev = &n->u2.node;
    }
    xfree(ptr);
}
#endif
