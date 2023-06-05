#include <bits/stdc++.h>
#include "html.hpp"

using namespace std;
enum types{BLANK, TITLE, TAG, COMMENT, LIST};

int prevLayer = 0;
int prevLine = -1;

vector<pair<html::Tag, int>> elements{
  {html::Tag("html", ""), 0},
  {html::Tag("meta", ""), 1},
  {html::Tag("head", ""), 1},
  {html::Tag("link", "", {{"rel", "stylesheet"}, {"href", "res/stylesheets/dark.css"}}), 2},
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
  // cout << "TIT " << pre << " " << post << '\n';
  int layer = getLayer(pre);
  elements.push_back({html::Tag("h"+to_string(layer), post), 2});
}
void parseTag(string pre, string post) {
  // cout << "TAG " << pre << " " << post << '\n';
  int layer = getLayer(pre);
}
void parseList(string pre, string post) {
  // cout << "LST " << pre << " " << post << '\n';
  int layer = getLayer(pre);
  if (prevLine != LIST) {
    elements.push_back({html::Tag("ol", post), 2});
  } else if (layer > prevLayer) { 
    elements.push_back({html::Tag("ol", post), layer+2});
    elements.push_back({html::Tag("li", post), layer+3});
  } else {
    elements.push_back({html::Tag("li", post), layer+2});
  }
}
void parseText(string pre, string post) {
  // cout << "TXT " << pre << " " << post << '\n';
  int layer = getLayer(pre);
  elements.push_back({html::Tag("p", post), 2});
}

void parse(string path) {
  ifstream fin(path);

  string line;
  while (std::getline(fin, line)) {
    if (line.length() < 2) continue;

    string pre, post;
    pre = line.substr(0, 2);
    post = line.substr(3, line.length()-3);

    if (pre.at(0) == 'x') {
      parseTitle(pre, post);
      prevLine = TITLE;
      prevLayer = getLayer(pre);
    }
    else if (pre.at(0) == '@') {
      parseTag(pre, post);
      prevLine = TAG;
      prevLayer = getLayer(pre);
    }
    else if (pre.at(0) == '.') {
      parseList(pre, post);
      prevLine = LIST;
      prevLayer = getLayer(pre);
    }
    else if (pre.at(0) == '~') {
      parseText(pre, post);
      prevLine = COMMENT;
      prevLayer = getLayer(pre);
    }
    else {
      prevLine = BLANK;
      prevLayer = getLayer(pre);
    }
  }
}

int main() {
  parse("res/examples/testing.ng");
  cout << html::generatePage(elements);
}

/*
0 1 2 3
a b c d
len - idx
*/
