#include <stdio.h>
#include "scanner.h"
#include <ctype.h>
#include <string.h>

TokenType Token;
char	  Id[MAX_IDENT_LEN + 1];
int num;

FILE * f;
char ch;

TokenType checkKeyword(char * str){
	//TODO: Kiem tra tham so truyen vao co phai la mot Tu khoa khong
	//................
	for(int i = 0; i < KEYWORDS_COUNT; i++)
	{
		if(strcmp(str, keywords[i].string) == 0)
		{
			return keywords[i].Token;
		}
	}
	return IDENT;
}

char getCh(){
  return toupper(fgetc(f));
}

TokenType getToken(){
//TODO:
//..............
	while(isspace(ch))//ch == ' ' || ch == 13 || ch == '\n') 
	{
		ch = getCh();
	}
	if(isalpha(ch))
	{
		int i = 0;
		while(isalpha(ch) || isdigit(ch))
		{
			if(i < MAX_IDENT_LEN)
			{
				Id[i++] = ch;
			}
			ch = getCh();
		}
		Id[i] = '\0';
		return checkKeyword(Id);
	}
	else if(isdigit(ch))
	{
		num = 0;
		while(isdigit(ch))
		{
			num = num * 10 + ch - 48;
			ch = getCh();
		}
		return NUMBER;
	}
	else if(ch == ';')
	{
		ch = getCh();
		return SEMICOLON;
	}
	else if(ch == ',')
	{
		ch = getCh();
		return COMMA;
	}
	else if(ch == '(')
	{
		ch = getCh();
		return LPARENT;
	}
	else if(ch == ')')
	{
		ch = getCh();
		return RPARENT;
	}
	else if(ch == '[')
	{
		ch = getCh();
		return LBRACK;
	}
	else if(ch == ']')
	{
		ch = getCh();
		return RBRACK;
	}
	else if (ch == ':')
	{
		ch = getCh();
		if(ch == '=')
		{
			ch = getCh();
			return ASSIGN;
		}
		return EQU;
	}
	else if(ch == '>')
	{
		ch = getCh();
		return GTR;
	}
	else if(ch == '*')
	{
		ch = getCh();
		return TIMES;
	}
	else if(ch == '.')
	{
		ch = getCh();
		return PERIOD;
	}
	else if (ch == ':')
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


void compile(char * filename){
  	if((f = fopen(filename,"rt")) == NULL) printf("File %s not found",filename);
  	else{
		ch =' ';
		do{
		 	Token = getToken();
			//printf("%d", Token);
			printf("%d %s", Token,TabToken[Token]);
			if(Token==IDENT) printf("(%s) \n",Id);
			else if(Token==NUMBER) printf("(%d) \n",num);
			else printf("\n");
		}while(Token != NONE);
	}
  fclose(f);
}