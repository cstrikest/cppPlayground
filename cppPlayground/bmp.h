#pragma once
#include <cstdint>
#include <cstring>
#include <cstdlib>
#include <cassert>

int readBmp(char* file_name, void* p_data);
int writeBmp(char* file_name, void* p_data);


