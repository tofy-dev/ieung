#pragma once
#include <bits/stdc++.h>
#include "html.hpp"

using namespace std;

namespace engine {
enum types{BLANK, TITLE, TAG, COMMENT, LIST};

int getLayer(string pre);
void printElements();

void parseTitle(string pre, string post);
void parseTag(string pre, string post);
void parseList(string pre, string post);
void parseText(string pre, string post);

void parse(string path);
void closeTag(int e, string& ret, stack<html::Tag>& closeTags, stack<int>& closeLayers);
string generatePage();
}
