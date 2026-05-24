#ifndef NINECC_H
#define NINECC_H

#include <stdbool.h>

// トークンの種類
typedef enum {
  TK_RESERVED, // 記号
  TK_IDENT, // 識別子
  TK_NUM, // 整数トークン
  TK_EOF // 入力の終わりを表すトークン
} TokenKind;

typedef struct Token Token;

// トークン型
struct Token {
  TokenKind kind; // トークンの型
  Token *next; // 次の入力トークン
  int val; // kindがTK＿NUMの場合、その数値
  char *str; // トークン文字例
  int len; // トークンの長さ
};

// 入力プログラム
extern char *user_input;

// 現在差しているトークン
extern Token *token;

// エラーを報告するための関数
// printfと同じ引数を取る。
void error(char *fmt, ...);

//　エラー箇所を報告する
void error_at(char *loc, char *fmt, ...);

// 次のトークンが期待している記号のときには、トークンを一つ読み進めて
// 真を返す。それ以上の場合には為を返す。
bool consume(char *op);

// 次のトークンが期待ている記号のときには、トークンを一つ読み進める。
// それ以外の場合はエラーを報告する。
void expect(char *op);

//　次のトークンが数値の場合、トークンを一つ読み進めてその数値を返す。
//　それ以外の場合にはエラーを報告する。
int expect_number();

bool at_eof();

// 入力文字例pをトークナイズしてそれを返す。
Token *tokenize();

// ローカル変数
typedef struct LVar LVar;

struct LVar {
  LVar *next; // 次の変数 
  char *name; // 変数名
  int len; // 名前の長さ
  int offset; // RBPからのオフセット
};

// 現在のローカル変数リスト
extern LVar *locals;

// 名前でローカル変数を探す
LVar *find_lvar(Token *tok);

// パーサー
typedef enum {
  ND_ADD, // +
  ND_SUB, // -
  ND_MUL, // *
  ND_DIV, // /
  ND_ASSIGN, // =
  ND_EQ, // ==
  ND_NE, // !=
  ND_LT, // <
  ND_LE, // <=
  ND_LVAR, // ローカル変数
  ND_NUM, // Integer
} NodeKind;

// AST ノード形式
typedef struct Node Node;
struct Node {
  NodeKind kind; // Node kind
  Node *lhs; // Left-hand side
  Node *rhs; // Right-hand side
  int val; // Used if kind == ND_NUM
  int offset;
};

// パース結果のノードを順にストアする配列
extern Node *code[100];

// プログラム全体をパースする
void program();

// 式をパースする
Node *expr();

// コードジェネレーター
void gen(Node *node);

#endif