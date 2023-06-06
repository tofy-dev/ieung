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
  amt += 1; // html div is -2, body is -1, therefore offset by 2
  return string(amt*2, ' ');
}

string generatePage(const vector<pair<Tag, int>>& elements) {
  std::string ret = "";

  stack<Tag> closeTags{};
  stack<int> closeLayers{};

  Tag tag = elements.at(0).first;
  int layer = elements.at(0).second;

  ret += tag.genOpen(layer) + tag.innerText_ + '\n';
  closeTags.push(tag);
  closeLayers.push(layer);

  for (int e = 1; e < elements.size(); e++) {
    tag = elements.at(e).first;
    layer = elements.at(e).second;

    // this has to be a while loop
    while (layer <= closeLayers.top()) {
      ret += closeTags.top().genClose(closeLayers.top()) + '\n';
      closeTags.pop();
      closeLayers.pop();
    }
    ret += tag.genOpen(layer) + tag.innerText_ + '\n';
    closeTags.push(tag);
    closeLayers.push(layer);
  }

  while (closeTags.size() > 0) {
    ret += closeTags.top().genClose(closeLayers.top()) + '\n';
    closeTags.pop();
    closeLayers.pop();
  }
  return ret;
}
}
