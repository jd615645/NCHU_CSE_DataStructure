#include <cstdio>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <vector>
using namespace std;
#define INF 99999999

int proMap[7][7], dis[7], book[7], path[7];
int light[7], swLeft[7], swLight[7];

void init() {
  for (int i = 1; i <= 6; i++) {
    path[i] = -1;
    for (int j = 1; j <= 6; j++) {
      if (i == j) {
        proMap[i][j] = 0;
      } else {
        proMap[i][j] = INF;
      }
    }
  }
  proMap[1][2] = 5;
  proMap[2][3] = 7;
  proMap[4][5] = 5;
  proMap[5][6] = 6;
  proMap[1][4] = 2;
  proMap[2][5] = 3;
  proMap[3][6] = 8;

  light[0] = -1;
  light[1] = 1;
  light[2] = 0;
  light[3] = 1;
  light[4] = 1;
  light[5] = 0;
  light[6] = -1;

  swLeft[0] = -1;
  swLeft[1] = INF;
  swLeft[2] = 4;
  swLeft[3] = 3;
  swLeft[4] = 1;
  swLeft[5] = 4;
  swLeft[6] = -1;

  swLight[0] = -1;
  swLight[1] = -1;
  swLight[2] = 8;
  swLight[3] = 7;
  swLight[4] = 4;
  swLight[5] = 4;
  swLight[6] = -1;
}
// 計算x點在t時間變燈的顏色
int color(int x, int t) {
  // 時間在切換前
  if (t < swLeft[x]) {
    return light[x];
  }

  t = (t - swLeft[x]) % (swLight[x] * 2);

  if (!light[x]) {
    // red
    return (t < swLight[x]) ? 1 : 0;
  }
  else {
    // green
    return (t < swLight[x]) ? 0 : 1;
  }
}

// 計算x點下一次變換燈號可以過的時間
int nextChange(int x, int t) {
  // x: 4, t: 2, swLeft[x]: 1
  if (t < swLeft[x]) {
    return swLeft[x];
  }

  if (!color(x, t)) {
    // red
    return swLight[x] - ((t - swLeft[x]) % swLight[x]);
  }
  else {
    // green
    return 0;
  }
}

int calWait(int x, int t) {
  if (color(x, t)) {
    return 0;
  }
  else {
    return nextChange(x, t);
  }
}

int sol() {
  int n = 6, m = 7;
  int u, min;

  // 初始化dis陣列，這裡是1號頂點到其餘各個頂點的初始路線
  for (int i = 1; i <= n; i++) dis[i] = proMap[1][i];
  // book陣列初始化
  for (int i = 1; i <= n; i++) book[i] = 0;
  book[1] = 1;

  // Dijkstra演算法核心
  for (int i = 1; i <= n - 1; i++) {
    // 找到離1點頂點最近的頂點
    min = INF;
    for (int j = 1; j <= n; j++) {
      if (book[j] == 0 && dis[j] < min) {
        min = dis[j];
        u = j;
      }
    }
    book[u] = 1;
    for (int v = 1; v <= n; v++) {
      if (proMap[u][v] < INF) {
        if (dis[v] > proMap[u][v] + dis[u] + calWait(u, dis[u])) {
          dis[v] = proMap[u][v] + dis[u] + calWait(u, dis[u]);
          path[v] = u;
        }
      }
    }
  }

  //输出最终的结果
  // for (int i = 1; i <= n; i++) {
  //   cout << i << ": " << dis[i] << endl;
  //   cout << "path " << i << ": " << path[i] << endl;
  // }

  int go[7];
  int tempPath = path[6];
  int count = 0;

  while (tempPath) {
    go[count++] = tempPath;
    tempPath = path[tempPath];
  }
  int goPaht[count - 1];
  int count2 = 0;
  for (int i = count; i > 0; i--) {
    goPaht[count2++] = go[i - 1];
    // 1 -> 100 的路徑
    // cout << goPaht[count2 - 1] << " ";
  }
  cout << endl;

  count = 0;
  for (int i = 1; i <= 6; i++) {
    if (i == 1) {
      count++;
      cout << " S";
    } else if (i == 6) {
      cout << " D";
    } else if (goPaht[count] == i) {
      cout << " @";
      count++;
    } else {
      if (i < 10) {
        cout << "0";
      }
      cout << i;
    }

    if (i % 3 != 0) {
      cout << "-";
    } else if (i == 6) {
      cout << endl;
    } else {
      cout << endl;
      cout << " |  |  |" << endl;
    }
  }

  cout << "最短路徑 Cost 數: " << dis[n] << endl;
  cout << endl;
}

int main() {
  init();
  sol();

  return 0;
}