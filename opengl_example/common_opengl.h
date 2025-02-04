#include <chrono>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <thread>
#include <unistd.h>

#ifdef __MACH__        // APPLE:   DO NOT REMOVE THESE
#include <GLUT/glut.h> // COMPILE WIth (e.g., for tetra.cpp)
#include <OpenGL/gl.h> // no extra installations needed for OpenGL
#include <OpenGL/glu.h>
// clang++ -Wall -g -framework OpenGL -framework GLUT
// -Wno-declaration-dependencies -o tetra tetra.cpp
#endif // next file
// clang++ -Wall -g -framework OpenGL -framework GLUT
// -Wno-declaration-dependencies -o hexahendron hexahendron.cpp
//                        // and so on...

// DO NOT REMOVE THESE
#ifdef __linux__   // INSTALL THESE LIBRARIES...     NO COMMAS BETWEEN FILENAMES
#include <GL/gl.h> // sudo apt install libglfw3-dev freeglut3-dv libglew-dev

#include <GL/glu.h> // clang++ -Wall -g -lGL -lGLU -lglfw -lglut -o tetra tetra.cpp
#include <GL/glut.h>    // do NOT say ... tetra.cpp tetra.cpp
#include <GLFW/glfw3.h> // COMPILE with... (e.g., for tetra.cpp)
#endif                  // next file
// clang++ -Wall -g -lGL -lGLU -lglfw -lglut -o hexahendron
// hexahendron.cpp
// ...
// CAN use g++ -Wall ... if you wish...

#define ColoredVertex(c, v)                                                    \
  do {                                                                         \
    glColor3fv(c);                                                             \
    glVertex3fv(v);                                                            \
  } while (0)
#define WIDTH 400
#define HEIGHT 400
