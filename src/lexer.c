#include "lexer.h"
#include <stdio.h>

Lexer_* init_lexer(char* code)
{
  Lexer_* lexer = calloc(1,sizeof(*lexer));

  lexer->index = 0;
  lexer->source_code = code;
  lexer->curr_char = lexer->source_code[lexer->index];
  lexer->line = 1;

  return lexer;
}

char peek_next(Lexer_* lexer)
{
  if(!(lexer->source_code[lexer->index+1] == '\0'))
  {
    lexer->index++;
    lexer->curr_char = lexer->source_code[lexer->index];
  }
  return lexer->curr_char;
}

char peek_back(Lexer_* lexer)
{
  if(!(lexer->source_code[lexer->index-1] == '\0'))
  {
    lexer->index--;
    lexer->curr_char = lexer->source_code[lexer->index];
  }
  return lexer->curr_char;
}

void move_pointer(Lexer_* lexer)
{
  if(lexer->curr_char != '\0' && !(lexer->index > strlen(lexer->source_code)))
  {
    lexer->index++;
    lexer->curr_char = lexer->source_code[lexer->index];

    if(lexer->curr_char == '\n') lexer->line++;
  }
}

void skip_whitespace(Lexer_* lexer)
{
  do {
    move_pointer(lexer);
  } while(lexer->curr_char == ' ' || lexer->curr_char == '\t');
}

char* convert_to_str(char value)
{
  char* str = calloc(2,sizeof(*str));
  str[0] = value;
  str[1] = '\0';
  return str;
}

char* gather_keyword(Lexer_* lexer)
{
  char* val = calloc(1,sizeof(*val));
  do {
    char* curr = convert_to_str(lexer->curr_char);

    val = realloc(
      val,
      (strlen(curr)+strlen(val)+2)*sizeof(*val)
    );
    strcat(val,curr);
    move_pointer(lexer);
    if(lexer->curr_char == ':' || lexer->curr_char == ' ' || lexer->curr_char == '\n' || lexer->curr_char == '\0' || lexer->curr_char == ',' || lexer->curr_char == '(' || lexer->curr_char == ')') break;
  } while(1);
  return val;
}

Tokens_* advance_with_token(Lexer_* lexer, int token_id, char* val)
{
  move_pointer(lexer);
  return init_token(token_id,val);
}

char* get_number(Lexer_* lexer)
{
  char* number = calloc(1,sizeof(*number));
  while(isdigit(lexer->curr_char)) {
    char* curr = convert_to_str(lexer->curr_char);

    number = realloc(
      number,
      (strlen(number)+strlen(curr)+2)*sizeof(*curr)
    );
    strcat(number,curr);
    move_pointer(lexer);
  }

  return number;
}

void comment(Lexer_* lexer)
{
  do {
    if(lexer->curr_char == '\n' || lexer->curr_char == '\0') return;
    move_pointer(lexer);
  } while(1);
}
void multi_line_comment(Lexer_* lexer)
{
  do {
    move_pointer(lexer);
    if(lexer->curr_char == '*')
    {
      move_pointer(lexer);
      if(lexer->curr_char == '/') return move_pointer(lexer);
      else {
        fprintf(stderr,"\nSyntax Error\n\t➥ Expected `/` for end of multi-line comment on line %d\n",lexer->line);
        exit(EXIT_FAILURE);
      }
    }
  } while(1);
}

Tokens_* get_next_token(Lexer_* lexer)
{
  do {
    redo:
    if(lexer->curr_char == ' ' || lexer->curr_char == '\t')
      skip_whitespace(lexer);
    
    if(isdigit(lexer->curr_char))
    {
      return init_token(Intval,get_number(lexer));
    }
    if(isalnum(lexer->curr_char))
    {
      char* val = gather_keyword(lexer);
      if(strcmp(val,"DEFINE")==0||strcmp(val,"define")==0) return init_token(Define_Keyword, val);
      else if(strcmp(val,"PRINT")==0 || strcmp(val,"print")==0) return init_token(Print_Keyword,val);
      else if(strcmp(val,"IF")==0 || strcmp(val,"if")==0) return init_token(IfStatement,"if");
      else if(strcmp(val,"endif")==0 || strcmp(val,"ENDIF")==0) return init_token(EndIf,"endif");
      return init_token(Id,val);
    }
    switch(lexer->curr_char)
    {
      case '/':
      {
        if(peek_next(lexer)=='/')
        {
          comment(lexer);
          goto redo;
        }
        peek_back(lexer);
        if(peek_next(lexer)=='*')
        {
          multi_line_comment(lexer);
          goto redo;
        }
        peek_back(lexer);
      }
      case ':':return advance_with_token(lexer,Colon,":");
      case '=':return advance_with_token(lexer,Equals,convert_to_str(lexer->curr_char));
      case ',':return advance_with_token(lexer, Comma, ",");
      case '\n': move_pointer(lexer);goto redo;
      case '(':return advance_with_token(lexer, LP, "(");
      case ')':return advance_with_token(lexer, RP, ")");
      case '>':return advance_with_token(lexer, GT, ">");
      case '<':return advance_with_token(lexer, LT, "<");
      case '&':
      {
        peek_next(lexer);

        if(lexer->curr_char == '&')
        {
          return advance_with_token(lexer, And, "&&");
        }

        peek_back(lexer);
        break;
      }
      default:break;
    }

    move_pointer(lexer);
  } while(lexer->curr_char != '\0');
  return init_token(Eof,"\0");
}