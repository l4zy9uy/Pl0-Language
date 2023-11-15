#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "scanner.h"

TokenType Token;
int Num;
char Id[MAX_IDENT_LEN + 1];

FILE *f;
char ch;

TokenType checkKeyword(char *str)
{
	// TODO: Kiem tra tham so truyen vao co phai la mot Tu khoa khong
	//................

	int i;
	for (int i = 0; i < KEYWORDS_COUNT; i++)
	{
		if (strcmp(Id, keywords[i].string) == 0)
		{
			return keywords[i].Token;
		}
	}

	return IDENT;
}

char getCh()
{
	return toupper(fgetc(f));
}

TokenType getToken()
{
	// TODO:
	//..............

	while (ch == ' '|| ch == '\n'|| ch == 13)
	{
		ch = getCh();
	}

	printf("ch is: %c", ch);

	if (isalpha(ch))
	{
		int p = 0;

		while (isalpha(ch) || isdigit(ch))
		{
			Id[p++] = ch;
			ch = getCh();
		}

		Id[p] = '\0';

		return checkKeyword(Id);
	}
	else if (isdigit(ch))
	{
		Num = 0;
		while (isdigit(ch))
		{
			Num = 10 * Num + ch - 48;
			ch = getCh();
		}
		return NUMBER;
	}
	else if (ch == ';')
	{
		ch = getCh();
		return SEMICOLON;
	} else if (ch == ',')
	{
		ch = getCh();
		return COMMA;
	}
	 else if (ch == '=')
	{
		ch = getCh();
		return ASSIGN;
	}
	 else if (ch == '*')
	{
		ch = getCh();
		return TIMES;
	} else if (ch == ':')
	{
		ch = getCh();
		if (ch == '=')
		{
			ch = getCh();
			return ASSIGN;
		}
		
		return PERIOD;
	} else if (ch == '>')
	{
		ch = getCh();
		if (ch == '=')
		{
			ch = getCh();
			return GEQ;
		}
		return GTR;
	} else if (ch == '<')
	{
		ch = getCh();
		if (ch == '=')
		{
			ch = getCh();
			return LEQ;
		} else if (ch == '>')
		{
			ch = getCh();
			return NEQ;
		}
		
		return LSS;
	} else if (ch == '/')
	{
		ch = getCh();
		return SLASH;
	} else if (ch == '%')
	{
		ch = getCh();
		return PERCENT;
	}
	
	
	
	
	
	
	

	return NONE;
}

void compile(char *filename)
{
	if ((f = fopen(filename, "rt")) == NULL)
		printf("File %s not found", filename);
	else
	{
		ch = ' ';
		do
		{
			Token = getToken();
			// printf(" %d\n", Token);
			printf(" %s",TabToken[Token]);
			if(Token==IDENT) printf("(%s) \n",Id);
			else if(Token==NUMBER) printf("(%d) \n",Num);
			else printf("\n");
		} while (Token != NONE);
	}
	fclose(f);
}
