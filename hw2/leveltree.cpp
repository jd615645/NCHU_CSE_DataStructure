#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <string>
#include <cstdio>
#include <queue>
using namespace std;

int levelCount[10] = {1, 4, 13, 40, 121, 364, 1030, 3280, 9841, 29524};
string *tree = new string[30000];
vector<int> node;

int leftChild(int index) { return index * 3 - 1; }
int midChild(int index) { return index * 3; }
int rightChild(int index) { return index * 3 + 1; }

int checkLevel(int num) {
  int level = 1;
  if (num == 0) {
    return level;
  }
  for (int i = 9; i >= 0; i--) {
    if (num > levelCount[i]) {
      level = i + 2;
      break;
    }
  }
  return level;
}

void updateNode() {
  queue<int> haveNode;

  for (int i = 0; i <= 29523; i++) {
    if (tree[i] != "null") {
      haveNode.push(i);
    }
  }
  node.resize(haveNode.size());

  int count = 0;
  while (!haveNode.empty()) {
    node[count++] = haveNode.front();
    haveNode.pop();
  }
}

int findIndex(int findNum) {
  vector<int>::iterator it;

  it = find(node.begin(), node.end(), findNum);

  if (it != node.end()) {
    return (it - node.begin() + 1);
  }
  else {
    return -1;
  }
}

void inOrderRraversal(int root) {
  int left = leftChild(root);
  int mid = midChild(root);
  int right = rightChild(root);

  cout << findIndex(root) << " ";

  if (tree[left] != "null") {
    cout << "[ ";
    inOrderRraversal(left);
    if (tree[mid] == "null" && tree[right] == "null") {
      cout << "] ";
    }
  }
  if (tree[mid] != "null") {
    inOrderRraversal(mid);
    if (tree[right] == "null") {
      cout << "] ";
    }
  }
  if (tree[right] != "null") {
    inOrderRraversal(right);
    cout << "] ";
  }
}

void showFolder() {
  updateNode();
  cout << "當前目錄表: ";
  inOrderRraversal(1);
  cout << endl;
}

void init() {
  for (int i = 0; i < 30000; i++){
    tree[i] = "null";
  }
  tree[1] = "";
  tree[2] = "";
  tree[3] = "World!";
  tree[8] = "";
  tree[9] = "";
  tree[10] = "Hello";
  tree[23] = "";
  tree[24] = "";
  showFolder();
}

int Info() {
  queue<int> haveStr;
  queue<int> haveNode;

  for (int i = 0; i <= 29523; i++) {
    if (tree[i] != "null"){
      if (tree[i] != "") {
        haveStr.push(i);
      }
      haveNode.push(i);
    }
  }

  int treeHeight = checkLevel(haveNode.back());
  int nodeNum = haveNode.size();
  int strNum = haveStr.size();

  cout << "-----INFO-----" << endl;
  cout << "樹高: " << treeHeight << endl;
  cout << "node個數: " << nodeNum << endl;
  // "當前目錄表";
  showFolder();

  cout << "有string的目錄有: ";
  while (!haveStr.empty()) {
    cout << findIndex(haveStr.front()) << " ";
    haveStr.pop();
  }
  cout << endl;
}

void Insert() {
  showFolder();
  int input;
  cout << "輸入欲插入的file: ";
  cin >> input;

  try {
    int val = node[input-1];
  
    int left = leftChild(val);
    int mid = midChild(val);
    int right = rightChild(val);

    int inserted = 0;
    if (tree[left] == "null" && !inserted) {
      tree[left] = "";
      inserted = 1;
    }
    if (tree[mid] == "null" && !inserted) {
      tree[mid] = "";
      inserted = 1;
    }
    if (tree[right] == "null" && !inserted) {
      tree[right] = "";
      inserted = 1;
    }

    if (!inserted) {
      cout << "該節點已經滿無法新增" << endl;
    }
  }
  catch(int e) {
    cout << "無此node或輸入錯誤" << endl;
  }
  showFolder();
}

void inOrderRraversalDel(int root) {
  int left = leftChild(root);
  int mid = midChild(root);
  int right = rightChild(root);

  tree[root] = "null";

  if (tree[left] != "null") {
    inOrderRraversalDel(left);
  }
  if (tree[mid] != "null") {
    inOrderRraversalDel(mid);
  }
  if (tree[right] != "null") {
    inOrderRraversalDel(right);
  }
}

void Delete() {
  showFolder();
  int input;
  cout << "輸入欲刪除的file: ";
  cin >> input;

  try {
    int val = node[input - 1];

    inOrderRraversalDel(val);
  }
  catch(int e) {
    cout << "無此node或輸入錯誤" << endl;
  }
  showFolder();
}

void stringAppend() {
  int input;
  cout << "輸入欲插入的file: ";
  cin >> input;

  try {
    int val = node[input - 1];
    string appendStr;
    cout << "輸入欲存入的string: ";
    cin >> appendStr;

    tree[val] += appendStr;
    cout << "string 存入完成node " << input << " 的內容為 " << tree[val] << endl;
  } catch (int e) {
    cout << "無此node或輸入錯誤" << endl;
  }
}
void stringDelete() {
  int input;
  cout << "輸入欲插入的file: ";
  cin >> input;

  try {
    int val = node[input - 1];
    string appendStr;

    tree[val] = "";
    cout << "node " << input << " 的內容已刪除成功" << endl;
  } catch (int e) {
    cout << "無此node或輸入錯誤" << endl;
  }
}

void stringModify() {
  int input;
  cout << "輸入欲插入的file: ";
  cin >> input;

  try {
    int val = node[input - 1];
    string modifyStr;
    cout << "輸入欲修改的string: ";
    cin >> modifyStr;

    tree[val] = modifyStr;
    cout << "string 修改完成node " << input << " 的內容為 " << tree[val]
         << endl;
  } catch (int e) {
    cout << "無此node或輸入錯誤" << endl;
  }
}

void view() {
  int input;
  cout << "輸入欲檢視的file: ";
  cin >> input;

  try {
    int val = node[input - 1];

    cout << "node " << input << " 的內容為 " << tree[val] << endl;
  } catch (int e) {
    cout << "無此node或輸入錯誤" << endl;
  }
}

int main() {
  // 1[23[4[78]56]]
  init();

  int input = 1;
  while (input) {
    string command;
    cout << "請下指令(info\\insert\\delete\\stringAppend\\stringDelete\\stringModify\\view)： ";
    cin >> command;

    if (command == "info") {
      Info();
    }
    else if (command == "insert") {
      Insert();
    }
    else if (command == "delete") {
      Delete();
    }
    else if (command == "stringAppend") {
      stringAppend();
    }
    else if (command == "stringDelete") {
      stringDelete();
    }
    else if (command == "stringModify") {
      stringModify();
    }
    else if (command == "view") {
      view();
    }
    else {
      cout << "輸入格式錯誤，請重新輸入" << endl;
      cout << "可輸入指令如下" << endl;
      cout << "(info\\insert\\delete\\stringAppend\\stringDelete\\stringmodify\\view)" << endl;
    }
  }
}