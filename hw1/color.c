#include <stdio.h>

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KBLU "\x1B[34m"
#define KWHT "\x1B[37m"

int main()
{
  printf("%sred\n", KRED);
  printf("%sblue\n", KBLU);
  printf("%swhite\n", KWHT);
  printf("%snormal\n", KNRM);

  return 0;
}