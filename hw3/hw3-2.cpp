#include <cstdio>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <vector>
using namespace std;
#define INF 99999999

int proMap[26][26], dis[26], book[26], path[26];
int light[26], swLeft[26], swLight[26];

void init() {
  for (int i = 1; i <= 26; i++) {
    path[i] = -1;
    for (int j = 1; j <= 26; j++) {
      if (i == j) {
        proMap[i][j] = 0;
      } else {
        proMap[i][j] = INF;
      }
    }
  }
  // set map
  proMap[1][2] = 21;
  proMap[2][3] = 22;
  proMap[3][4] = 24;
  proMap[4][5] = 23;
  proMap[6][7] = 35;
  proMap[7][8] = 37;
  proMap[8][9] = 69;
  proMap[9][10] = 5;
  proMap[11][12] = 11;
  proMap[12][13] = 45;
  proMap[13][14] = 32;
  proMap[14][15] = 9;
  proMap[16][17] = 35;
  proMap[17][18] = 37;
  proMap[18][19] = 45;
  proMap[19][20] = 26;
  proMap[21][22] = 38;
  proMap[22][23] = 32;
  proMap[23][24] = 64;
  proMap[24][25] = 23;
  proMap[1][6] = 3;
  proMap[6][11] = 45;
  proMap[11][16] = 46;
  proMap[16][21] = 41;
  proMap[1][7] = 43;
  proMap[7][12] = 34;
  proMap[12][17] = 14;
  proMap[17][22] = 24;
  proMap[3][8] = 44;
  proMap[8][13] = 61;
  proMap[13][18] = 25;
  proMap[18][23] = 48;
  proMap[4][9] = 55;
  proMap[9][14] = 9;
  proMap[14][19] = 46;
  proMap[19][24] = 50;
  proMap[5][10] = 8;
  proMap[10][15] = 53;
  proMap[15][20] = 15;
  proMap[20][25] = 18;

  // set init light, red 0, green 1
  light[0] = -1;
  light[1] = -1;
  light[2] = 0;
  light[3] = 1;
  light[4] = 0;
  light[5] = 1;
  light[6] = 1;
  light[7] = 1;
  light[8] = 0;
  light[9] = 0;
  light[10] = 1;
  light[11] = 1;
  light[12] = 0;
  light[13] = 1;
  light[14] = 1;
  light[15] = 0;
  light[16] = 1;
  light[17] = 0;
  light[18] = 1;
  light[19] = 1;
  light[20] = 0;
  light[21] = 0;
  light[22] = 1;
  light[23] = 0;
  light[24] = 0;
  light[25] = -1;

  // set swLeft time
  swLeft[0] = -1;
  swLeft[1] = -1;
  swLeft[2] = 11;
  swLeft[3] = 20;
  swLeft[4] = 7;
  swLeft[5] = 2;
  swLeft[6] = 16;
  swLeft[7] = 12;
  swLeft[8] = 15;
  swLeft[9] = 23;
  swLeft[10] = 14;
  swLeft[11] = 29;
  swLeft[12] = 13;
  swLeft[13] = 18;
  swLeft[14] = 16;
  swLeft[15] = 6;
  swLeft[16] = 23;
  swLeft[17] = 6;
  swLeft[18] = 29;
  swLeft[19] = 20;
  swLeft[20] = 6;
  swLeft[21] = 16;
  swLeft[22] = 19;
  swLeft[23] = 5;
  swLeft[24] = 17;
  swLeft[25] = -1;

  // set swLight
  swLight[0] = -1;
  swLight[1] = -1;
  swLight[2] = 10;
  swLight[3] = 20;
  swLight[4] = 7;
  swLight[5] = 3;
  swLight[6] = 11;
  swLight[7] = 6;
  swLight[8] = 3;
  swLight[9] = 12;
  swLight[10] = 4;
  swLight[11] = 8;
  swLight[12] = 14;
  swLight[13] = 13;
  swLight[14] = 13;
  swLight[15] = 7;
  swLight[16] = 7;
  swLight[17] = 5;
  swLight[18] = 11;
  swLight[19] = 8;
  swLight[20] = 7;
  swLight[21] = 16;
  swLight[22] = 4;
  swLight[23] = 8;
  swLight[24] = 5;
  swLight[25] = -1;
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
  } else {
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
  } else {
    // green
    return 0;
  }
}

int calWait(int x, int t) {
  if (color(x, t)) {
    return 0;
  } else {
    return nextChange(x, t);
  }
}

int sol() {
  int n = 25, m = 40;
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
        if (dis[v] > dis[u] + proMap[u][v] + calWait(u, dis[u])) {
          dis[v] = dis[u] + proMap[u][v] + calWait(u, dis[u]);
          path[v] = u;
        }
      }
    }
  }

  //输出最终的结果
  for (int i = 1; i <= n; i++) {
    cout << i << ": " << dis[i] << endl;
  }

  int go[26];
  int tempPath = path[25];
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
  for (int i = 1; i <= 25; i++) {
    if (i == 1) {
      count++;
      cout << " S";
    } else if (i == 25) {
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

    if (i % 5 != 0) {
      cout << "-";
    } else if (i == 25) {
      cout << endl;
    } else {
      cout << endl;
      cout << " |  |  |  |  |" << endl;
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