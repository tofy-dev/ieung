#include <bits/stdc++.h>
#include "html.hpp"
using namespace std;

namespace html {
// Constructors
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
string Tag::genOpen() { return genOpen(0); }


// genClose
string Tag::genClose(int layer) {
  return genIndent(layer) + "</" + type_ + ">"; 
}
string Tag::genClose() { return genClose(0); }


// genIndent
string Tag::genIndent(int amt) {
  return string(amt, '\t');
}


string generatePage(const vector<pair<Tag, int>>& elements, int& idx) {
  Tag tag = elements.at(idx).first;
  int layer = elements.at(idx).second;

  bool createNested = false;
  if (idx < elements.size()-1) {
    int layerB = elements.at(idx+1).second;
    if (layer < layerB) createNested = true;
  }

  if (createNested) {
    idx++; // continue adding elements
    return tag.genOpen(layer) + '\n' + generatePage(elements, idx) + tag.genClose(layer) + '\n';
  } else if (idx != elements.size()-1) {
    idx++; // continue adding elements
    return tag.genOpen(layer) + tag.genClose() + '\n' + generatePage(elements, idx);
  } else {
    // base case
    return tag.genOpen(layer) + tag.innerText_ + tag.genClose() + '\n';
  }
}
}
