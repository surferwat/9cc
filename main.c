#include <stdio.h>
#include "9cc.h"

int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "引数の個数が正しくありません\n");
    return 1;
  }

  // 入力をセット
  user_input = argv[1];

  // 字句解析 → 構文解析
  token = tokenize();
  program();

  // アセンブリの前半
  printf(".intel_syntax noprefix\n");
  printf(".global main\n");
  printf("main:\n");

  // プロローグ
  // ローカル変数２６個分
  printf("  push rbp\n");
  printf("  mov rbp, rsp\n");
  printf("  sub rsp, 208\n");

  // 各文についてコード生成
  for (int i = 0; code[i]; i++) {
    gen(code[i]);
    // 式の結果を捨てる
    printf("  pop rax\n");
  }

  // エビローグ
  printf("  mov rsp, rbp\n");
  printf("  pop rbp\n");
  printf("  ret\n");

  return 0;
}