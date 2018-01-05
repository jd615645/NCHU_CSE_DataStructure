#include <iostream>
#include <queue>
#include <stack>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define KGRN "\x1B[32m"
#define KRED "\x1B[31m"
#define KBLU "\x1B[34m"
#define KWHT "\x1B[37m"

using namespace std;
struct point
{
  //?座標?座標
  int x;
  int y;
};
char solAry[15][15] = {
    {'*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*'},
    {'*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*'},
    {'*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*'},
    {'*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*'},
    {'*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*'},
    {'*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*'},
    {'*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*'},
    {'*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*'},
    {'*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*'},
    {'*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*'},
    {'*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*'},
    {'*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*'},
    {'*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*'},
    {'*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*'},
    {'*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*'}};

bool pass = true;

//初始化迷?
int **Maze;
//保存任意點在路徑中的前一步
point **Pre;
//移?方向，??斜都可以，八個方向
point move[8] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
void Create(int row, int column, int startX, int startY, int endX, int endY)
{
  //?建迷?，注意到用0表示可走，1表示?，?整個?入的迷?再用???，?理的?候就不用特?注意?界??
  int i, j;

  for (i = 0; i < row + 2; i++)
  {
    Maze[i][0] = Maze[i][column + 1] = 1;
  }
  for (j = 0; j < column + 2; j++)
  {
    Maze[0][j] = Maze[row + 1][j] = 1;
  }

  int ary[row][column];
  for (i = 0; i < row; i++)
  {
    for (j = 0; j < column; j++)
    {
      ary[i][j] = rand() % 2;
    }
  }

  for (i = 1; i <= row; i++)
  {
    for (j = 1; j <= column; j++)
    {
      Maze[i][j] = ary[i - 1][j - 1];
    }
  }

  // print origin maze
  for (i = 0; i < row; i++)
  {
    for (j = 0; j < column; j++)
    {
      if ((i == startX - 1 && j == startY - 1) || (i == endX - 1 && j == endY - 1))
      {
        cout << KRED << "2 ";
      }
      else
      {
        if (ary[i][j] == 0)
        {
          cout << KWHT << ary[i][j] << " ";
        }
        else
        {
          cout << KBLU << ary[i][j] << " ";
        }
      }
    }
    cout << KBLU << endl;
  }
  cout << endl;
}
// MazePath(終點x, 終點y, 起點x, 起點y)
bool MazePath(int startX, int startY, int endX, int endY)
{
  //判?是否有路??入口到出口，保存?路?（?列）
  if (endX == startX && endY == startY)
  {
    return true;
  }

  //用于?度优先搜索
  queue<point> q;
  //?前位置
  point now;
  now.x = endX;
  now.y = endY;
  q.push(now);
  Maze[now.x][now.y] = -1;
  while (!q.empty())
  {
    now = q.front();

    q.pop();

    for (int i = 0; i < 8; i++)
    {
      if (now.x + move[i].x == startX && now.y + move[i].y == startY)
      {
        Maze[now.x + move[i].x][now.y + move[i].y] = -1;
        Pre[startX][startY] = now;
        return true;
      }
      if (Maze[now.x + move[i].x][now.y + move[i].y] == 0)
      {
        //下個位置
        point temp;
        temp.x = now.x + move[i].x;
        temp.y = now.y + move[i].y;
        q.push(temp);
        Maze[temp.x][temp.y] = -1;
        Pre[temp.x][temp.y] = now;
      }
    }
  }
  pass = false;
  return false;
}

// PrintPath(終點x, 終點y, 起點x, 起點y)
void PrintPath(int startX, int startY, int endX, int endY, bool mid)
{
  //?出最短路?
  //保存位置
  point temp;
  //保存路?序列
  stack<point> s;
  temp.x = startX;
  temp.y = startY;

  while (temp.x != endX || temp.y != endY)
  {
    s.push(temp);
    temp = Pre[temp.x][temp.y];
  }

  while (!s.empty())
  {
    temp = s.top();
    solAry[temp.x - 1][temp.y - 1] = '0';
    s.pop();
  }
  solAry[endX - 1][endY - 1] = '2';
  solAry[startX - 1][startY - 1] = '2';

  cout << endl;

  int i, j;

  for (i = 0; i < 15; i++)
  {
    for (j = 0; j < 15; j++)
    {
      if (i == startX - 1 && j == startY - 1 && mid)
      {
        cout << KGRN << "3 ";
      }
      else if ((i == startX - 1 && j == startY - 1) || (i == endX - 1 && j == endY - 1))
      {
        cout << KRED << "2 ";
      }
      else if (solAry[i][j] == '2')
      {
        cout << KRED << solAry[i][j] << " ";
      }
      else if (solAry[i][j] == '3')
      {
        cout << KGRN << solAry[i][j] << " ";
      }
      else if (solAry[i][j] == '0')
      {
        cout << KWHT << solAry[i][j] << " ";
      }
      else
      {
        cout << KBLU << solAry[i][j] << " ";
      }
    }
    cout << endl;
  }
  cout << endl;
}
void clearMap(int row, int column)
{
  Maze = new int *[row + 2];
  Pre = new point *[row + 2];
  for (int i = 0; i < row + 2; i++)
  {
    Maze[i] = new int[column + 2];
    Pre[i] = new point[column + 2];
  }
}

int main()
{
  unsigned seed;
  // 取得時間序列
  seed = (unsigned)time(NULL);
  // 以時間序列當亂數種子
  srand(seed);

  //迷?行?
  int row = 15;
  //迷?列?
  int column = 15;

  int startX = rand() % row + 1;
  int startY = rand() % column + 1;
  int endX = rand() % row + 1;
  int endY = rand() % column + 1;

  int midX = -1;
  int midY = -1;

  char haveMid;

  clearMap(row, column);
  Create(row, column, startX, startY, endX, endY);

  cout << KWHT << "請問要輸入中間點嗎？(y/N) ";
  cin >> haveMid;
  if (haveMid == 'y')
  {
    cout << KWHT << "請輸入中間點的X座標(1-15): ";
    cin >> midX;
    cout << KWHT << "請輸入中間點的Y座標(1-15): ";
    cin >> midY;
  }

  if (midX == -1 && midY == -1)
  {
    // 無中間點
    MazePath(startX, startY, endX, endY);
    cout << KWHT << "(" << startX << ", " << startY << ") => (" << endX << ", " << endY << ")" << endl;
    if (pass)
    {
      cout << "有找到路徑" << endl;
      PrintPath(startX, startY, endX, endY, false);
    }
    else
    {
      cout << "沒有找到路徑" << endl;
    }
  }
  else
  {
    // 有中間點
    MazePath(startX, startY, midX, midY);
    if (pass)
    {
      cout << "有找到路徑" << endl;
      PrintPath(startX, startY, midX, midY, false);
    }
    else
    {
      cout << "沒有找到路徑" << endl;
    }

    MazePath(midX, midY, endX, endY);
    cout << KWHT << "(" << startX << ", " << startY << ") => (" << midX << ", " << midY << ") => (" << endX << ", " << endY << ")" << endl;
    if (pass)
    {
      cout << "有找到路徑" << endl;
      PrintPath(midX, midY, endX, endY, true);
    }
    else
    {
      cout << "沒有找到路徑" << endl;
    }
  }

  return 0;
}