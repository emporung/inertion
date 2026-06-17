#include <GL/glut.h>
#include <cmath>
#include <cstdlib>
#include <iostream>
#ifdef _WIN32
#include <windows.h>
#endif
float camDistance{8.0f};
float angleX{30.0f};
float angleY{30.0f};
float rx{1.0f}, ry{1.0f}, rz{1.0f};
float angle{0.0f};
int bodyType{1};
float p1{1.0f}, p2{1.0f}, p3{1.0f};
float axisX{1.0f}, axisY{0.0f}, axisZ{0.0f};

void keyboard(unsigned char key, int x, int y) {
  switch (key) {
  case '+':
  case '=':
    camDistance -= 0.5f;
    if (camDistance < 2.0f)
      camDistance = 2.0f;
    break;
  case '-':
    camDistance += 0.5f;
    if (camDistance > 50.0f)
      camDistance = 50.0f;
    break;
  case 27:
    exit(0);
    break;
  }
  glutPostRedisplay();
}

void specialKeys(int key, int x, int y) {
  switch (key) {
  case GLUT_KEY_UP:
    angleX += 5.0f;
    break;
  case GLUT_KEY_DOWN:
    angleX -= 5.0f;
    break;
  case GLUT_KEY_LEFT:
    angleY += 5.0f;
    break;
  case GLUT_KEY_RIGHT:
    angleY -= 5.0f;
    break;
  }
  glutPostRedisplay();
}

void drawEllipsoid() {
  int slices{30}, stacks{30};
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  for (int i{0}; i < stacks; ++i) {
    float theta1{static_cast<float>(i * M_PI / stacks)};
    float theta2{static_cast<float>((i + 1) * M_PI / stacks)};
    glBegin(GL_QUAD_STRIP);
    for (int j{0}; j <= slices; ++j) {
      float phi{static_cast<float>(j * 2 * M_PI / slices)};
      float x1{static_cast<float>(rx * sin(theta1) * cos(phi))};
      float y1{static_cast<float>(ry * sin(theta1) * sin(phi))};
      float z1{static_cast<float>(rz * cos(theta1))};
      float x2{static_cast<float>(rx * sin(theta2) * cos(phi))};
      float y2{static_cast<float>(ry * sin(theta2) * sin(phi))};
      float z2{static_cast<float>(rz * cos(theta2))};
      glColor4f(0.2f, 0.4f, 0.8f, 0.3f);
      glVertex3f(x1, y1, z1);
      glVertex3f(x2, y2, z2);
    }
    glEnd();
  }
  glDisable(GL_BLEND);
}

void drawBody() {
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glColor3f(1.0f, 0.6f, 0.2f);
  glEnable(GL_LINE_SMOOTH);
  glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
  if (bodyType == 1) {
    float s{p1 / 2.0f};
    glBegin(GL_QUADS);
    glVertex3f(-s, -s, s);
    glVertex3f(s, -s, s);
    glVertex3f(s, s, s);
    glVertex3f(-s, s, s);
    glVertex3f(-s, -s, -s);
    glVertex3f(-s, s, -s);
    glVertex3f(s, s, -s);
    glVertex3f(s, -s, -s);
    glVertex3f(-s, s, -s);
    glVertex3f(-s, s, s);
    glVertex3f(s, s, s);
    glVertex3f(s, s, -s);
    glVertex3f(-s, -s, -s);
    glVertex3f(s, -s, -s);
    glVertex3f(s, -s, s);
    glVertex3f(-s, -s, s);
    glVertex3f(-s, -s, -s);
    glVertex3f(-s, -s, s);
    glVertex3f(-s, s, s);
    glVertex3f(-s, s, -s);
    glVertex3f(s, -s, -s);
    glVertex3f(s, s, -s);
    glVertex3f(s, s, s);
    glVertex3f(s, -s, s);
    glEnd();
  } else if (bodyType == 2) {
    float radius{p1};
    glColor3f(1.0f, 0.6f, 0.2f);
    glutWireSphere(radius, 30, 30);
  } else if (bodyType == 3) {
    float sx{p1 / 2}, sy{p2 / 2}, sz{p3 / 2};
    glBegin(GL_QUADS);
    glVertex3f(-sx, -sy, sz);
    glVertex3f(sx, -sy, sz);
    glVertex3f(sx, sy, sz);
    glVertex3f(-sx, sy, sz);
    glVertex3f(-sx, -sy, -sz);
    glVertex3f(-sx, sy, -sz);
    glVertex3f(sx, sy, -sz);
    glVertex3f(sx, -sy, -sz);
    glVertex3f(-sx, sy, -sz);
    glVertex3f(-sx, sy, sz);
    glVertex3f(sx, sy, sz);
    glVertex3f(sx, sy, -sz);
    glVertex3f(-sx, -sy, -sz);
    glVertex3f(sx, -sy, -sz);
    glVertex3f(sx, -sy, sz);
    glVertex3f(-sx, -sy, sz);
    glVertex3f(-sx, -sy, -sz);
    glVertex3f(-sx, -sy, sz);
    glVertex3f(-sx, sy, sz);
    glVertex3f(-sx, sy, -sz);
    glVertex3f(sx, -sy, -sz);
    glVertex3f(sx, sy, -sz);
    glVertex3f(sx, sy, sz);
    glVertex3f(sx, -sy, sz);
    glEnd();
  } else if (bodyType == 4) {
    float radius{p1};
    float height{p2};
    int slices{30};
    glBegin(GL_QUAD_STRIP);
    for (int i{0}; i <= slices; ++i) {
      float angle{static_cast<float>(2.0f * M_PI * i / slices)};
      float x{static_cast<float>(radius * cos(angle))};
      float z{static_cast<float>(radius * sin(angle))};
      glVertex3f(x, -height / 2, z);
      glVertex3f(x, height / 2, z);
    }
    glEnd();
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0, height / 2, 0);
    for (int i{0}; i <= slices; ++i) {
      float angle{static_cast<float>(2.0f * M_PI * i / slices)};
      float x{static_cast<float>(radius * cos(angle))};
      float z{static_cast<float>(radius * sin(angle))};
      glVertex3f(x, height / 2, z);
    }
    glEnd();
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0, -height / 2, 0);
    for (int i{0}; i <= slices; ++i) {
      float angle{static_cast<float>(2.0f * M_PI * i / slices)};
      float x{static_cast<float>(radius * cos(angle))};
      float z{static_cast<float>(radius * sin(angle))};
      glVertex3f(x, -height / 2, z);
    }
    glEnd();
  } else if (bodyType == 5) {
    float r{p1};
    float h{p2};
    int slices{30};
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glColor3f(1.0f, 0.6f, 0.2f);
    float topZ{h / 2.0f};
    float bottomZ{-h / 2.0f};
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0, 0, topZ);
    for (int i{0}; i <= slices; ++i) {
      float angle{static_cast<float>(2.0f * M_PI * i / slices)};
      float x{static_cast<float>(r * cos(angle))};
      float y{static_cast<float>(r * sin(angle))};
      glVertex3f(x, y, bottomZ);
    }
    glEnd();
    glBegin(GL_LINE_LOOP);
    for (int i{0}; i <= slices; ++i) {
      float angle{static_cast<float>(2.0f * M_PI * i / slices)};
      float x{static_cast<float>(r * cos(angle))};
      float y{static_cast<float>(r * sin(angle))};
      glVertex3f(x, y, bottomZ);
    }
    glEnd();
  }
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  float camX = camDistance * sin(angleX * 3.14159f / 180.0f) *
               cos(angleY * 3.14159f / 180.0f);
  float camY = camDistance * sin(angleX * 3.14159f / 180.0f) *
               sin(angleY * 3.14159f / 180.0f);
  float camZ = camDistance * cos(angleX * 3.14159f / 180.0f);
  gluLookAt(camX, camY, camZ, 0, 0, 0, 0, 1, 0);
  glBegin(GL_LINES);
  glColor3f(1, 0, 0);
  glVertex3f(-5, 0, 0);
  glVertex3f(5, 0, 0);
  glColor3f(0, 1, 0);
  glVertex3f(0, -5, 0);
  glVertex3f(0, 5, 0);
  glColor3f(0, 0, 1);
  glVertex3f(0, 0, -5);
  glVertex3f(0, 0, 5);
  glEnd();
  float L{5.0f};
  glBegin(GL_LINES);
  glColor3f(1.0f, 1.0f, 0.0f);
  glVertex3f(-axisX * L, -axisY * L, -axisZ * L);
  glVertex3f(axisX * L, axisY * L, axisZ * L);
  glEnd();
  drawBody();
  drawEllipsoid();
  glutSwapBuffers();
}

void reshape(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45, (float)w / h, 1, 100);
  glMatrixMode(GL_MODELVIEW);
}

void timer(int) {
  angle += 1.0f;
  glutPostRedisplay();
  glutTimerFunc(16, timer, 0);
}

int main(int argc, char **argv) {

  if (argc >= 8) {
    bodyType = atoi(argv[1]);
    rx = atof(argv[2]);
    ry = atof(argv[3]);
    rz = atof(argv[4]);
    axisX = atof(argv[5]);
    axisY = atof(argv[6]);
    axisZ = atof(argv[7]);
    if (argc >= 8)
      p1 = atof(argv[8]);
    if (argc >= 9)
      p2 = atof(argv[9]);
    if (argc >= 10)
      p3 = atof(argv[10]);
    std::cout << "Body: " << bodyType << ", ellipsoid: rx=" << rx
              << " ry=" << ry << " rz=" << rz << ", rotation axis: (" << axisX
              << ", " << axisY << ", " << axisZ << ")"
              << ", sizes: " << p1 << " " << p2 << " " << p3 << std::endl;
  }
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(800, 600);
  glutCreateWindow(" ");
  glutKeyboardFunc(keyboard);
  glutSpecialFunc(specialKeys);
  glEnable(GL_DEPTH_TEST);
  glClearColor(0, 0, 0, 1);
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutTimerFunc(0, timer, 0);
  glutMainLoop();
  return 0;
}
