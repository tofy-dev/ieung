#pragma once
#include <bits/stdc++.h>
using namespace std;

namespace html {
// e.g. <html>, <div>, <a>
struct Tag {
  string type_;
  string innerText_;
  vector<pair<string, string>> attrs_;

  Tag(string type, string innerText);
  Tag(string type, string innerText, vector<pair<string, string>> attrs);

  string genOpen();
  string genOpen(int);

  string genClose();
  string genClose(int);

  static inline string genIndent(int);
};

string generatePage(const vector<pair<Tag, int>>& elements, int& idx);
}
