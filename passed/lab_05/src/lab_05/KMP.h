#pragma once

#include <string>
#include <mutex>

using namespace std;

void KMP(string str, string sub, mutex &mtx);