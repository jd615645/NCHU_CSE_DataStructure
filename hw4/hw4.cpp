#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
using namespace std;

int n, m;
int maze[10000][10000];
int solMaze[10000][10000];
int showMaze[10000][10000];
vector<int> path;
int levelCount[10] = {1, 2, 4, 8, 16, 32, 64, 128, 512, 1024};
int heap[2000];
int heapSize = 0;

struct point {
  //横座標纵座標
  int x;
  int y;
};

//保存任意點在路徑中的前一步
point **Pre;
//移動方向，橫豎都可以，4個方向
point direction[4] = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};

void init() {
  for (int i = 0; i < 10000; i++) {
    for (int j = 0; j < 10000; j++) {
      maze[i][j] = -1;
      solMaze[i][j] = 0;
      showMaze[i][j] = -1;
    }
  }

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      maze[i][j] = 0;
    }
  }
  maze[1][1] = 1;
  maze[n][m] = 1;
}

void printMaze() {
  int count = 1;
  for (int i = 0; i <= n; i++) {
    string line1 = "";
    string line2 = "";
    for (int j = 0; j <= m; j++) {
      int now = maze[i + 1][j + 1];
      line1 += " @ ";
      // cout << "maze[" << i+1 << "][" << j+1 << "]: " << maze[i+1][j+1] << endl;
      // cout << "maze[" << i << "][" << j+1 << "]: " << maze[i][j+1] << endl;
      // cout << "maze[" << i+1 << "][" << j << "]: " << maze[i+1][j] << endl;

      if (now == maze[i + 1][j] && now != -1 && now != 0) {
        line2 += "   ";
      } else {
        line2 += " | ";
      }
      if (j != m) {
        if (now == maze[i][j + 1] && now != -1 && now != 0) {
          line1 += "  ";
        } else {
          line1 += "--";
        }

        if (i != n) {
          if (now != 0) {
            string s = std::to_string(count);
            if (count < 10) {
              s = "0" + s;
            }
            showMaze[i + 1][j + 1] = count;
            count++;
            line2 += s;
          }
          else {
            showMaze[i + 1][j + 1] = 0;
            line2 += " #";
          }
        }
      }
    }

    cout << line1 << endl;
    if (i != n) {
      cout << line2 << endl;
    }
  }
  cout << endl;
}

// MazePath(起點x, 起點y, 終點x, 終點y)
bool MazePath(int startX, int startY, int endX, int endY) {
  //判断是否有路徑從入口到出口，保存該路徑
  if (endX == startX && endY == startY) {
    return true;
  }

  //用於廣度優先搜索
  queue<point> q;
  //目前位置
  point now;
  now.x = endX;
  now.y = endY;
  q.push(now);
  solMaze[now.x][now.y] = -1;
  while (!q.empty()) {
    now = q.front();

    q.pop();

    for (int i = 0; i < 4; i++) {
      // 有找到路徑
      if (now.x + direction[i].x == startX && now.y + direction[i].y == startY) {
        solMaze[now.x + direction[i].x][now.y + direction[i].y] = -1;
        Pre[startX][startY] = now;
        return true;
      }

      if (solMaze[now.x + direction[i].x][now.y + direction[i].y] == 1) {
        //下個位置
        point temp;
        temp.x = now.x + direction[i].x;
        temp.y = now.y + direction[i].y;
        q.push(temp);
        solMaze[temp.x][temp.y] = -1;
        Pre[temp.x][temp.y] = now;
      }
    }
  }
  return false;
}

void setSolMaze() {
  for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= m; j++) {
      if (maze[i + 1][j + 1] == 1) {
        solMaze[i + 1][j + 1] = 1;
      } else {
        solMaze[i + 1][j + 1] = 0;
      }
    }
  }
}

void clearMap(int row, int column) {
  Pre = new point *[row + 2];
  for (int i = 0; i < row + 2; i++) {
    Pre[i] = new point[column + 2];
  }
}

void printMazeMap() {
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      if (maze[i][j] < 10) {
        cout << "0";
      }
      cout << maze[i][j] << " ";
    }
    cout << endl;
  }
  cout << "-----" << endl;
}

void printSolMazeMap() {
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      if (solMaze[i][j] < 10) {
        cout << "0";
      }
      cout << solMaze[i][j] << " ";
    }
    cout << endl;
  }
  cout << "-----" << endl;
}

void printPath(int startX, int startY, int endX, int endY) {
  // cout << "startX: " << startX << endl;
  // cout << "startY: " << startY << endl;
  // cout << "endX: " << endX << endl;
  // cout << "endY: " << endY << endl;
  //保存位置
  point temp;
  //保存路径序列
  queue<point> s;
  temp.x = startX;
  temp.y = startY;
  string printPath = "";
  int count = 0;


  while (temp.x != endX || temp.y != endY) {
    s.push(temp);
    temp = Pre[temp.x][temp.y];
  }

  path.resize(s.size());
  string printStr = "";
  while (!s.empty()) {
    temp = s.front();
    path[count++] = showMaze[temp.x][temp.y];

    printStr += std::to_string(showMaze[temp.x][temp.y]);
    if (temp.x != n || temp.y != m) {
      printStr += "-";
    }
    if (s.size() == 1) {
      printStr += std::to_string(showMaze[n][m]);

      cout << printStr << endl;
    }
    s.pop();
  }
}

void insertHeap(int num) {
  heap[heapSize++] = num;
  int leftChild = num * 2 + 1;
  int rightChild = num * 2 + 2;

}
void delMax(int num) {

}
void delMin(int num) {

}

int main() {
  srand(time(NULL));

  // input
  cout << endl << "請輸入迷宮尺寸 ex: 6*6: ";
  scanf("%d*%d", &n, &m);
  cout << endl;
  // n = m = 6;

  init();

  int count = 2;
  while (1) {
    int x1 = rand() % n + 1;
    int y1 = rand() % m + 1;
    int x2 = rand() % n + 1;
    int y2 = rand() % m + 1;

    if (!(x1 == x2 && y1 == y2)) {
      if (maze[x1][y1] == 0) {
        maze[x1][y1] = count++;
      }
      if (maze[x2][y2] == 0) {
        maze[x2][y2] = count++;
      }
      int x = maze[x1][y1];
      int y = maze[x2][y2];
      int min = std::min(x, y);
      int max = std::max(x, y);

      for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
          if (maze[i][j] == max) {
            maze[i][j] = min;
          }
        }
      }

      setSolMaze();
      clearMap(n, m);
      if (MazePath(1, 1, n, m)) {
        break;
      }
    }
  }

  // printSolMazeMap();
  // printMazeMap();
  printMaze();
  printPath(1, 1, n, m);
  
  return 0;
}