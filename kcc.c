#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// トークンの種類
typedef enum
{
	TK_RESERVED, // 記号
	TK_NUM,      // 整数トークン
	TK_EOF,      // 入力の終わりを表すトークン
} TokenKind; // TokenKindとしてenum型の定数集合を定義

typedef struct Token Token; // 下記の構造体をTokenとして定義

struct Token //Token型の構造体を定義
{
	TokenKind kind; // トークンの型
	Token *next;    // 次の入力トークン
	int val;        // kindがTK_NUMの場合，その数値
	char *str;      // トークン文字列
};

// 現在着目しているトークン
Token *token; // 再定義したToken構造体のポインタ変数tokenを定義

void error(char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	fprintf(stderr, "\n");
	exit(1);
}

bool consume(char op)
{
	if ( token -> kind != TK_RESERVED || token -> str[0] != op )
		return false;
	token = token -> next;
	return true;
}

void expect(char op)
{
	if ( token -> kind != TK_RESERVED || token -> str[0] != op )
		error("'%c'ではありません", op);
	token = token -> next;
}

int expect_number()
{
	if ( token -> kind != TK_NUM )
		error("数ではありません");
	int val = token -> val;
	token = token -> next;
	return val;
}

bool at_eof()
{
	return token -> kind == TK_EOF;
}

Token *tokenize(char *p)
{
	Token head;
	head.next = NULL;
	Token *cur = &head;

	while ( *p )
	{
		if ( isspace(*p) )
		{
			p++;
			continue;
		}

		if ( *p == '+' || *p == '-' )
		{
			cur = new_token(TK_RESERVED, cur, p++);
			continue;
		}

		if ( isdigit(*p) )
		{
			cur = new_token(TK_NUM, cur, p);
			cur -> val = strtol(p, &p, 10);
			continue;
		}

		error("トークナイズできません");
	}

	new_token(TK_EOF, cur, p);
	return head.next;
}

int main(int argc, char **argv)
{
	if ( argc != 2 )
	{
		error("引数の個数が正しくありません");
		return 1;
	}

	char *p = argv[1];

	printf(".intel_syntax noprefix\n");
	printf(".global main\n");
	printf("main:\n");

	printf("    mov rax, %d\n", expect_number());

	while ( !at_eof() )
	{
		if ( consume('+') )
		{
			printf("    add rax, %d\n", expect_number());
			continue;
		}

		expect('-')
		printf("    sub rax, %d\n", expect_number());
	}

	printf("    ret\n");

	return 0;
}
