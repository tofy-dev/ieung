#include <bits/stdc++.h>
#include "html.hpp"
#include "engine.hpp"

using namespace std;
namespace engine {
// Global variables
int prevLayer = 0;
int prevLine = -1;

vector<pair<html::Tag, int>> elements{
  {html::Tag("html", ""), -2},
  {html::Tag("meta", ""), -1},
  {html::Tag("head", ""), -1},
  {html::Tag("link", "", {{"rel", "stylesheet"}, {"href", "res/stylesheets/dark.css"}}), 0},
  {html::Tag("body", ""), -1}
};


// Helper functions
int getLayer(string pre) {
  char a = pre.at(0), b = pre.at(1);
  if (b == ' ') return 1;
  if (a == b) return 2;
  if (isdigit(b)) return b - '0';
  return 0;
}

void printElements() {
  for (auto elem : elements) {
    cout << elem.first.type_ << " " << elem.second << '\n';
  }
}


// Parsing functions
void parseTitle(string pre, string post) {
  // cout << "TIT " << pre << " " << post << '\n';
  int layer = getLayer(pre);
  elements.push_back({html::Tag("h"+to_string(layer), post), 0});
}

void parseTag(string pre, string post) {
  // cout << "TAG " << pre << " " << post << '\n';
  int layer = getLayer(pre);
}

void parseList(string pre, string post) {
  // cout << "LST " << pre << " " << post << '\n';
  int layer = getLayer(pre);
  string type = (pre.at(0) == '.') ? "ul" : "ol";
  if ((layer == 1 && prevLine != LIST) || layer > prevLayer) { 
    elements.push_back({html::Tag(type, ""), (layer-1)*2});
  }
  elements.push_back({html::Tag("li", post), (layer-1)*2+1});
}

void parseText(string pre, string post) {
  // cout << "TXT " << pre << " " << post << '\n';
  int layer = getLayer(pre);
  elements.push_back({html::Tag("p", post), 0});
  // elements.push_back({html::Tag("br", ""), 0});
}

void parse(string path) {
  ifstream fin(path);

  string line;
  while (std::getline(fin, line)) {
    if (line.length() < 2) continue;

    string pre, post;
    pre = line.substr(0, 2);
    post = line.substr(3, line.length()-3);

    char ch = pre.at(0);
    if (ch == 'x') {
      parseTitle(pre, post);
      prevLine = TITLE;
    } else if (ch == '@') {
      parseTag(pre, post);
      prevLine = TAG;
    } else if (ch == '.' || ch == '-') {
      parseList(pre, post);
      prevLine = LIST;
    } else if (ch == '~') {
      parseText(pre, post);
      prevLine = COMMENT;
    } else {
      prevLine = BLANK;
    }
    prevLayer = getLayer(pre);
  }
}


// Generating functions
void closeTag(int e, string& ret, stack<html::Tag>& closeTags, stack<int>& closeLayers) {
  if (closeTags.top().id_ == e-1) {
    ret += closeTags.top().genClose() + '\n';
  } else {
    ret += closeTags.top().genClose(closeLayers.top()) + '\n';
  }
  closeTags.pop();
  closeLayers.pop();
}

string generatePage() {
  std::string ret = "";

  stack<html::Tag> closeTags{};
  stack<int> closeLayers{};

  html::Tag tag;
  int layer;

  int e;
  for (e = 0; e < elements.size(); e++) {
    tag = elements.at(e).first;
    layer = elements.at(e).second;
    tag.id_ = e;

    bool goUpLayer = false;
    while (e > 0 && layer <= closeLayers.top()) {
      closeTag(e, ret, closeTags, closeLayers);
      goUpLayer = true;
    }

    if (!goUpLayer) ret += '\n';
    ret += tag.genOpen(layer) + tag.innerText_;

    closeTags.push(tag);
    closeLayers.push(layer);
  }

  while (closeTags.size() > 0) {
    closeTag(e, ret, closeTags, closeLayers);
  }
  return ret;
}
}
