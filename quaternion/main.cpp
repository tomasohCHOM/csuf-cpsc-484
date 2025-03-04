//============================================================
// file: main.cpp
//============================================================
#include <cassert>
#include <cstring>

// MATRIX and VECTOR classes assignment
#include "matrix3d.h"
#include "quaternion.h"
#include "vector3d.h"

int main(int argc, const char *argv[]) {
  vector3D::run_tests();
  matrix3D::run_tests();
  quaternionD::run_tests();

  return 0;
}
