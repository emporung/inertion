#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../src/inertia.h"
#include <Eigen/Dense>
#include <doctest/doctest.h>

TEST_CASE("Куб: масса 6, сторона 2 --> I = 4") {
  auto I{inertiaCube(6.0f, 2.0f)};
  CHECK(I(0, 0) == doctest::Approx(4.0f));
  CHECK(I(1, 1) == doctest::Approx(4.0f));
  CHECK(I(2, 2) == doctest::Approx(4.0f));
}

TEST_CASE("Шар: масса 5, радиус 2 --> I = 0.4 * 5 * 4 = 8") {
  auto I{inertiaSphere(5.0f, 2.0f)};
  CHECK(I(0, 0) == doctest::Approx(8.0f));
  CHECK(I(1, 1) == doctest::Approx(8.0f));
  CHECK(I(2, 2) == doctest::Approx(8.0f));
}

TEST_CASE("Параллелепипед: m=12, a=2, b=3, c=4") {
  auto I{inertiaBox(12.0f, 2.0f, 3.0f, 4.0f)};
  // Ixx = 12*(9+16)/12 = 12*25/12 = 25
  CHECK(I(0, 0) == doctest::Approx(25.0f));
  // Iyy = 12*(4+16)/12 = 12*20/12 = 20
  CHECK(I(1, 1) == doctest::Approx(20.0f));
  // Izz = 12*(4+9)/12 = 12*13/12 = 13
  CHECK(I(2, 2) == doctest::Approx(13.0f));
}

TEST_CASE("Цилиндр: m=2, R=3, h=8") {
  auto I{inertiaCylinder(2.0f, 3.0f, 8.0f)};
  // Ixx = m*R²/2 = 2*9/2 = 9
  CHECK(I(0, 0) == doctest::Approx(9.0f));
  // Iyy = m*(3R²+h²)/12 = 2*(27+64)/12 = 2*91/12 ≈ 15.1667
  CHECK(I(1, 1) == doctest::Approx(15.1666667f));
  CHECK(I(2, 2) == doctest::Approx(15.1666667f));
}

TEST_CASE("Конус: m=3, R=2, h=5") {
  auto I{inertiaCone(3.0f, 2.0f, 5.0f)};
  // Ixx = 0.15 * 3 * (4 + 25/4) = 0.45 * (4 + 6.25) = 0.45 * 10.25 = 4.6125
  CHECK(I(0, 0) == doctest::Approx(4.6125f));
  CHECK(I(1, 1) == doctest::Approx(4.6125f));
  // Izz = 0.3 * 3 * 4 = 3.6
  CHECK(I(2, 2) == doctest::Approx(3.6f));
}

TEST_CASE("Нормализация вектора (3,4,0) --> (0.6, 0.8, 0)") {
  auto v{normalizeVector(3.0f, 4.0f, 0.0f)};
  CHECK(v(0) == doctest::Approx(0.6f));
  CHECK(v(1) == doctest::Approx(0.8f));
  CHECK(v(2) == doctest::Approx(0.0f));
}

TEST_CASE("Нормализация нулевого вектора --> возвращает (0,0,0) без ошибки") {
  CHECK_THROWS_AS(normalizeVector(0.0f, 0.0f, 0.0f), std::invalid_argument);
}

TEST_CASE("Инварианты куба: I1=12, I2=48, I3=64 для m=6, a=2") {
  auto I{inertiaCube(6.0f, 2.0f)};
  float I1{I.trace()};
  float I2{I(0, 0) * I(1, 1) + I(1, 1) * I(2, 2) + I(0, 0) * I(2, 2)};
  float I3{I.determinant()};
  CHECK(I1 == doctest::Approx(12.0f));
  CHECK(I2 == doctest::Approx(48.0f));
  CHECK(I3 == doctest::Approx(64.0f));
}



TEST_CASE("Куб: отрицательная масса --> исключение") {
    CHECK_THROWS_AS(inertiaCube(-1.0f, 2.0f), std::invalid_argument);
    CHECK_THROWS_AS(inertiaCube(1.0f, -2.0f), std::invalid_argument);
}

TEST_CASE("Шар: отрицательный радиус --> исключение") {
    CHECK_THROWS_AS(inertiaSphere(-1.0f, 2.0f), std::invalid_argument);
    CHECK_THROWS_AS(inertiaSphere(1.0f, -2.0f), std::invalid_argument);
}

TEST_CASE("Параллелепипед: отрицательный размер --> исключение") {
    CHECK_THROWS_AS(inertiaBox(-1.0f, 2.0f, 3.0f, 4.0f), std::invalid_argument);
    CHECK_THROWS_AS(inertiaBox(1.0f, -2.0f, 3.0f, 4.0f), std::invalid_argument);
    CHECK_THROWS_AS(inertiaBox(1.0f, 2.0f, -3.0f, 4.0f), std::invalid_argument);
    CHECK_THROWS_AS(inertiaBox(1.0f, 2.0f, 3.0f, -4.0f), std::invalid_argument);
}

TEST_CASE("Цилиндр: отрицательный радиус/высота --> исключение") {
    CHECK_THROWS_AS(inertiaCylinder(-1.0f, 3.0f, 8.0f), std::invalid_argument);
    CHECK_THROWS_AS(inertiaCylinder(2.0f, -3.0f, 8.0f), std::invalid_argument);
    CHECK_THROWS_AS(inertiaCylinder(2.0f, 3.0f, -8.0f), std::invalid_argument);
}

TEST_CASE("Конус: отрицательный радиус/высота --> исключение") {
    CHECK_THROWS_AS(inertiaCone(-3.0f, 2.0f, 5.0f), std::invalid_argument);
    CHECK_THROWS_AS(inertiaCone(3.0f, -2.0f, 5.0f), std::invalid_argument);
    CHECK_THROWS_AS(inertiaCone(3.0f, 2.0f, -5.0f), std::invalid_argument);
}
