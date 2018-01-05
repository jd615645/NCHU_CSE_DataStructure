#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main()
{
  int i;
  unsigned seed;
  // 取得時間序列
  seed = (unsigned)time(NULL);
  // 以時間序列當亂數種子
  srand(seed);

  for (i = 0; i < 5; ++i) {
    printf("%d ", rand() % 2);
  }
  return 0;
}