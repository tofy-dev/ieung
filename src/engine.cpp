#include <bits/stdc++.h>
#include "html.hpp"
#include "engine.hpp"
#include "CLI.hpp"

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
  if (layer == 1 || layer > prevLayer) { 
    elements.push_back({html::Tag("ul", ""), (layer-1)*2});
  }
  elements.push_back({html::Tag("li", post), (layer-1)*2+1});
}

void parseText(string pre, string post) {
  // cout << "TXT " << pre << " " << post << '\n';
  int layer = getLayer(pre);
  elements.push_back({html::Tag("p", post), 0});
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
    } else if (pre.at(0) == '@') {
      parseTag(pre, post);
      prevLine = TAG;
    } else if (pre.at(0) == '.') {
      parseList(pre, post);
      prevLine = LIST;
    } else if (pre.at(0) == '~') {
      parseText(pre, post);
      prevLine = COMMENT;
    } else {
      prevLine = BLANK;
    }
    prevLayer = getLayer(pre);
  }
}
}

// CLI interface
int main(int argc, char **argv) {
    CLI::App app{"App description"};

    // Define options
    std::string inp = "res/examples/testing.ng";
    app.add_option("-i", inp, "Input file");

    std::string out = "";
    app.add_option("-o", out, "Output file");

    CLI11_PARSE(app, argc, argv);

    // Define options
    engine::parse(inp);
    engine::printElements();
    string htmlFile = html::generatePage(engine::elements);

    if (out == "") {
      cout << htmlFile;
    } else {
      ofstream fout{out}; // this is dangerous and can overwrite files
      fout << htmlFile;
    }

    return 0;
}
