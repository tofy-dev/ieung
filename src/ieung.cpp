#include <bits/stdc++.h>
#include "html.hpp"

using namespace std;

vector<pair<html::Tag, int>> elements{
  {html::Tag("html", ""), 0},
  {html::Tag("meta", ""), 1},
  {html::Tag("body", ""), 1}
};

int getLayer(string pre) {
  char a = pre.at(0), b = pre.at(1);
  if (b == ' ') return 1;
  if (a == b) return 2;
  if (isdigit(b)) return b - '0';
  return -1;
}

void parseTitle(string pre, string post) {
  cout << "TIT " << pre << " " << post << '\n';
  int layer = getLayer(pre);
  elements.push_back({html::Tag("h"+to_string(layer), post), 2});
}
void parseTag(string pre, string post) {
  cout << "TAG " << pre << " " << post << '\n';
}
void parseList(string pre, string post) {
  cout << "LST " << pre << " " << post << '\n';
  int layer = getLayer(pre);
  elements.push_back({html::Tag("li", post), layer+2});
}
void parseText(string pre, string post) {
  cout << "TXT " << pre << " " << post << '\n';
  elements.push_back({html::Tag("p", post), 2});
}

void parse(string path) {
  ifstream fin(path);

  string line;
  int prevLine = -1;
  while (std::getline(fin, line)) {
    if (line.length() < 2) continue;

    string pre, post;
    pre = line.substr(0, 2);
    post = line.substr(3, line.length()-3);

    if (pre.at(0) == 'x') {
      parseTitle(pre, post);
      prevLine = 0;
    }
    if (pre.at(0) == '@') {
      parseTag(pre, post);
      prevLine = 1;
    }
    if (pre.at(0) == '.') {
      if (prevLine != 2)
        elements.push_back({html::Tag("ul", ""), 2});
      parseList(pre, post);
      prevLine = 2;
    }
    if (pre.at(0) == '~') {
      parseText(pre, post);
      prevLine = 3;
    }
  }
}

int main() {
  parse("res/testing.ng");
  for (auto elem : elements) {
    cout << elem.first.type_ << " " << elem.second << '\n';
  }

  cout << html::generatePage(elements);
}

/*
0 1 2 3
a b c d
len - idx
*/
