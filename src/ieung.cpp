#include <bits/stdc++.h>
#include "html.hpp"
using namespace std;

void parse(string path) {
  ifstream fin(path);

  string line;
  while (std::getline(fin, line)) {
    if (line.length() < 2) continue;

    string pre, post;
    pre = line.substr(0, 1);
    post = line.substr(3, line.length()-3);

    if (pre == "!") cout << "TITLE\n";
    if (pre == "@") cout << "TAG\n";
    if (pre == ".") cout << "LIST\n";
    if (pre == "#") cout << "COMMENT\n";
    if (pre == "~") cout << "TEXT\n";
    if (pre == "~") cout << "CODE\n";
  }
}

int main() {
  parse("res/testing.ng");
  
  vector<pair<html::Tag, int>> elements{};
  elements.push_back(make_pair(html::Tag("zero", ""), 0));
  elements.push_back(make_pair(html::Tag("one", "hi"), 1));
  elements.push_back(make_pair(html::Tag("one", ""), 1));
  elements.push_back(make_pair(html::Tag("two", ""), 2));
  elements.push_back(make_pair(html::Tag("three", ""), 3));
  elements.push_back(make_pair(html::Tag("two", ""), 2));
  elements.push_back(make_pair(html::Tag("one", ""), 1));
  elements.push_back(make_pair(html::Tag("two", ""), 2));

  int start = 0;
  std::cout << html::generatePage(elements);
}

/*
0 1 2 3
a b c d
len - idx
*/
