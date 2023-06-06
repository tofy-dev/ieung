#include <bits/stdc++.h>
#include "html.hpp"
using namespace std;

namespace html {
// Constructors
Tag::Tag() {};
Tag::Tag(string type, string innerText)
  : type_{type}, innerText_{innerText} {};
Tag::Tag(string type, string innerText, vector<pair<string, string>> attrs)
  : type_{type}, innerText_{innerText}, attrs_{attrs} {};


// genOpen
string Tag::genOpen(int layer) {
  string ret = "";
  ret += genIndent(layer);
  ret += "<" + type_;
  
  for (auto a : attrs_) {
    ret += " ";
    ret += a.first + "=";
    ret += "\"" + a.second + "\"";
  }

  ret += ">";
  return ret;
}
string Tag::genOpen() { return genOpen(-2); }


// genClose
string Tag::genClose(int layer) {
  return genIndent(layer) + "</" + type_ + ">"; 
}
string Tag::genClose() { return genClose(-2); }


// genIndent
string Tag::genIndent(int amt) {
  amt += 2; // html div is -2, body is -1, therefore offset by 2
  return string(amt*2, ' ');
}
}
