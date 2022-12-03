#pragma once
#include "Utils.h"

void load_obj(const char* filename, std::vector<floatvec>& vertices, std::vector<floatvec>& normals, std::vector<std::vector<GLushort>>& elements);
void draw_obj(std::vector<floatvec>& vertices, std::vector<floatvec>& normals, std::vector<std::vector<GLushort>>& elements);