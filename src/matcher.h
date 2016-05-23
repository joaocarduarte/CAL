/*
 * matcher.h
 *
 *  Created on: 23/05/2016
 *      Author: jp
 */

#ifndef SRC_MATCHER_H_
#define SRC_MATCHER_H_


#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>

using namespace std;

int kmp(string text, string pattern);

void pre_kmp(string pattern, vector<int> & prefix);

int numStringMatching(string filename,string toSearch);
int editDistance(string pattern, string text);
float numApproximateStringMatching(string filename,string toSearch);

#endif /* SRC_MATCHER_H_ */
