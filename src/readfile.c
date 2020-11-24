#include "readfile.h"


char* readFile(char* filename)
{
  FILE* file = fopen(filename,"rb");
  long size;
  char* code = calloc(1,sizeof(*code));

  if(file)
  {
    fseek(file,0,SEEK_END);
    size = ftell(file);
    fseek(file,0,SEEK_SET);

    code = realloc(
      code,
      (size+1)*sizeof(*code)
    );

    if(code)
    {
      fread(code,1,size,file);
      return code;
    }
  }

  fprintf(stderr,"\nFile doesn't exist");
  exit(EXIT_FAILURE);
}