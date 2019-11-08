#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "../../src/vector/vector3.hpp"
#include "../catch.hpp"
#include "utest.hpp"

using namespace space;
using Vector = Vec3<utest_scalar>;

TEST_CASE("Vector3", "[default construction]") {
  Vector vec;

  REQUIRE(vec.x == 0);
  REQUIRE(vec.y == 0);
  REQUIRE(vec.z == 0);
}

TEST_CASE("Vector3", "[construct with single scalar]") {
  for (size_t i = 0; i < RAND_TEST_NUM; ++i) {
    utest_scalar r = UTEST_RAND;
    Vector v{r};
    REQUIRE(v.x == APPROX(r));
    REQUIRE(v.y == APPROX(r));
    REQUIRE(v.z == APPROX(r));
  }
}

TEST_CASE("Vector3", "[construct with 3 components]") {
  for (size_t i = 0; i < RAND_TEST_NUM; ++i) {
    utest_scalar x = UTEST_RAND;
    utest_scalar y = UTEST_RAND;
    utest_scalar z = UTEST_RAND;
    Vector v{x, y, z};
    REQUIRE(v.x == APPROX(x));
    REQUIRE(v.y == APPROX(y));
    REQUIRE(v.z == APPROX(z));
  }
}

TEST_CASE("Vector3", "[add vector]") {
  for (size_t i = 0; i < RAND_TEST_NUM; ++i) {
    Vector v1{UTEST_RAND, UTEST_RAND, UTEST_RAND}, v2{UTEST_RAND, UTEST_RAND, UTEST_RAND};

    auto v3 = v1 + v2;
    REQUIRE(v3.x == APPROX(v1.x + v2.x));
    REQUIRE(v3.y == APPROX(v1.y + v2.y));
    REQUIRE(v3.z == APPROX(v1.z + v2.z));
  }
}

TEST_CASE("Vector3", "[sub vector]") {
  for (size_t i = 0; i < RAND_TEST_NUM; ++i) {
    Vector v1{UTEST_RAND, UTEST_RAND, UTEST_RAND}, v2{UTEST_RAND, UTEST_RAND, UTEST_RAND};

    auto v3 = v1 - v2;
    REQUIRE(v3.x == APPROX(v1.x - v2.x));
    REQUIRE(v3.y == APPROX(v1.y - v2.y));
    REQUIRE(v3.z == APPROX(v1.z - v2.z));
  }
}

TEST_CASE("Vector3", "[mul vector]") {
  for (size_t i = 0; i < RAND_TEST_NUM; ++i) {
    Vector v1{UTEST_RAND, UTEST_RAND, UTEST_RAND}, v2{UTEST_RAND, UTEST_RAND, UTEST_RAND};

    auto v3 = v1 * v2;
    REQUIRE(v3.x == APPROX(v1.x * v2.x));
    REQUIRE(v3.y == APPROX(v1.y * v2.y));
    REQUIRE(v3.z == APPROX(v1.z * v2.z));
  }
}

TEST_CASE("Vector3", "[div vector]") {
  for (size_t i = 0; i < RAND_TEST_NUM; ++i) {
    Vector v1{UTEST_RAND, UTEST_RAND, UTEST_RAND}, v2{UTEST_RAND, UTEST_RAND, UTEST_RAND};

    auto v3 = v1 / v2;
    REQUIRE(v3.x == APPROX(v1.x / v2.x));
    REQUIRE(v3.y == APPROX(v1.y / v2.y));
    REQUIRE(v3.z == APPROX(v1.z / v2.z));
  }
}

TEST_CASE("Vector3", "[add scalar]") {
  for (size_t i = 0; i < RAND_TEST_NUM; ++i) {
    Vector v1{UTEST_RAND, UTEST_RAND, UTEST_RAND};

    utest_scalar c = UTEST_RAND;

    auto v3 = v1 + c;
    REQUIRE(v3.x == APPROX(v1.x + c));
    REQUIRE(v3.y == APPROX(v1.y + c));
    REQUIRE(v3.z == APPROX(v1.z + c));
  }
}

TEST_CASE("Vector3", "[sub scalar]") {
  for (size_t i = 0; i < RAND_TEST_NUM; ++i) {
    Vector v1{UTEST_RAND, UTEST_RAND, UTEST_RAND};

    utest_scalar c = UTEST_RAND;

    auto v3 = v1 - c;
    REQUIRE(v3.x == APPROX(v1.x - c));
    REQUIRE(v3.y == APPROX(v1.y - c));
    REQUIRE(v3.z == APPROX(v1.z - c));
  }
}

TEST_CASE("Vector3", "[mul scalar]") {
  for (size_t i = 0; i < RAND_TEST_NUM; ++i) {
    Vector v1{UTEST_RAND, UTEST_RAND, UTEST_RAND};

    utest_scalar c = UTEST_RAND;

    auto v3 = v1 * c;
    REQUIRE(v3.x == APPROX(v1.x * c));
    REQUIRE(v3.y == APPROX(v1.y * c));
    REQUIRE(v3.z == APPROX(v1.z * c));
  }
}

TEST_CASE("Vector3", "[div scalar]") {
  for (size_t i = 0; i < RAND_TEST_NUM; ++i) {
    Vector v1{UTEST_RAND, UTEST_RAND, UTEST_RAND};

    utest_scalar c = UTEST_RAND;

    auto v3 = v1 / c;
    REQUIRE(v3.x == APPROX(v1.x / c));
    REQUIRE(v3.y == APPROX(v1.y / c));
    REQUIRE(v3.z == APPROX(v1.z / c));
  }
}

TEST_CASE("Vector3", "[negative]") {
  for (size_t i = 0; i < RAND_TEST_NUM; ++i) {
    Vector v1{UTEST_RAND, UTEST_RAND, UTEST_RAND};
    auto v3 = -v1;
    REQUIRE(v3.x == APPROX(-v1.x));
    REQUIRE(v3.y == APPROX(-v1.y));
    REQUIRE(v3.z == APPROX(-v1.z));
  }
}

TEST_CASE("Vector3", "[absolute value]") {
  for (size_t i = 0; i < RAND_TEST_NUM; ++i) {
    Vector v1{UTEST_RAND, UTEST_RAND, UTEST_RAND};
    auto v3 = v1.abs();
    REQUIRE(v3.x == APPROX(fabs(v1.x)));
    REQUIRE(v3.y == APPROX(fabs(v1.y)));
    REQUIRE(v3.z == APPROX(fabs(v1.z)));
  }
}

TEST_CASE("Vector3", "[operator += vector]") {
  for (size_t i = 0; i < RAND_TEST_NUM; ++i) {
    utest_scalar x = UTEST_RAND;
    utest_scalar y = UTEST_RAND;
    utest_scalar z = UTEST_RAND;

    Vector v1{x, y, z}, v2{UTEST_RAND, UTEST_RAND, UTEST_RAND};
    v1 += v2;
    REQUIRE(v1.x == APPROX(x + v2.x));
    REQUIRE(v1.y == APPROX(y + v2.y));
    REQUIRE(v1.z == APPROX(z + v2.z));
  }
}

TEST_CASE("Vector3", "[operator-= vector]") {
  for (size_t i = 0; i < RAND_TEST_NUM; ++i) {
    utest_scalar x = UTEST_RAND;
    utest_scalar y = UTEST_RAND;
    utest_scalar z = UTEST_RAND;

    Vector v1{x, y, z}, v2{UTEST_RAND, UTEST_RAND, UTEST_RAND};
    v1 -= v2;
    REQUIRE(v1.x == APPROX(x - v2.x));
    REQUIRE(v1.y == APPROX(y - v2.y));
    REQUIRE(v1.z == APPROX(z - v2.z));
  }
}

TEST_CASE("Vector3", "[operator *= vector]") {
  for (size_t i = 0; i < RAND_TEST_NUM; ++i) {
    utest_scalar x = UTEST_RAND;
    utest_scalar y = UTEST_RAND;
    utest_scalar z = UTEST_RAND;

    Vector v1{x, y, z}, v2{UTEST_RAND, UTEST_RAND, UTEST_RAND};
    v1 *= v2;
    REQUIRE(v1.x == APPROX(x * v2.x));
    REQUIRE(v1.y == APPROX(y * v2.y));
    REQUIRE(v1.z == APPROX(z * v2.z));
  }
}

TEST_CASE("Vector3", "[operator/= vector]") {
  for (size_t i = 0; i < RAND_TEST_NUM; ++i) {
    utest_scalar x = UTEST_RAND;
    utest_scalar y = UTEST_RAND;
    utest_scalar z = UTEST_RAND;

    Vector v1{x, y, z}, v2{UTEST_RAND, UTEST_RAND, UTEST_RAND};
    v1 /= v2;
    REQUIRE(v1.x == APPROX(x / v2.x));
    REQUIRE(v1.y == APPROX(y / v2.y));
    REQUIRE(v1.z == APPROX(z / v2.z));
  }
}

TEST_CASE("Vector3", "[operator+= scalar]") {
  for (size_t i = 0; i < RAND_TEST_NUM; ++i) {
    utest_scalar x = UTEST_RAND;
    utest_scalar y = UTEST_RAND;
    utest_scalar z = UTEST_RAND;
    utest_scalar r = UTEST_RAND;

    Vector v1{x, y, z};
    v1 += r;
    REQUIRE(v1.x == APPROX(x + r));
    REQUIRE(v1.y == APPROX(y + r));
    REQUIRE(v1.z == APPROX(z + r));
  }
}

TEST_CASE("Vector3", "[operator-= scalar]") {
  for (size_t i = 0; i < RAND_TEST_NUM; ++i) {
    utest_scalar x = UTEST_RAND;
    utest_scalar y = UTEST_RAND;
    utest_scalar z = UTEST_RAND;
    utest_scalar r = UTEST_RAND;

    Vector v1{x, y, z};
    v1 -= r;
    REQUIRE(v1.x == APPROX(x - r));
    REQUIRE(v1.y == APPROX(y - r));
    REQUIRE(v1.z == APPROX(z - r));
  }
}

TEST_CASE("Vector3", "[operator*= scalar]") {
  for (size_t i = 0; i < RAND_TEST_NUM; ++i) {
    utest_scalar x = UTEST_RAND;
    utest_scalar y = UTEST_RAND;
    utest_scalar z = UTEST_RAND;
    utest_scalar r = UTEST_RAND;

    Vector v1{x, y, z};
    v1 *= r;
    REQUIRE(v1.x == APPROX(x * r));
    REQUIRE(v1.y == APPROX(y * r));
    REQUIRE(v1.z == APPROX(z * r));
  }
}

TEST_CASE("Vector3", "[operator/= scalar]") {
  for (size_t i = 0; i < RAND_TEST_NUM; ++i) {
    utest_scalar x = UTEST_RAND;
    utest_scalar y = UTEST_RAND;
    utest_scalar z = UTEST_RAND;
    utest_scalar r = UTEST_RAND;

    Vector v1{x, y, z};
    v1 /= r;
    REQUIRE(v1.x == APPROX(x / r));
    REQUIRE(v1.y == APPROX(y / r));
    REQUIRE(v1.z == APPROX(z / r));
  }
}

TEST_CASE("Vector3", "[operator=]") {
  for (size_t i = 0; i < RAND_TEST_NUM; ++i) {
    Vector v1{UTEST_RAND, UTEST_RAND, UTEST_RAND};
    Vector v2;
    v2 = v1;
    REQUIRE(v1.x == APPROX(v2.x));
    REQUIRE(v1.y == APPROX(v2.y));
    REQUIRE(v1.z == APPROX(v2.z));
  }
}

TEST_CASE("Vector3", "[norm]") {
  for (size_t i = 0; i < RAND_TEST_NUM; ++i) {
    Vector v1{UTEST_RAND, UTEST_RAND, UTEST_RAND};
    auto m = norm(v1);
    REQUIRE(m == APPROX(sqrt(v1.x * v1.x + v1.y * v1.y + v1.z * v1.z)));
  }
}

TEST_CASE("Vector3", "[norm2]") {
  for (size_t i = 0; i < RAND_TEST_NUM; ++i) {
    Vector v1{UTEST_RAND, UTEST_RAND, UTEST_RAND};
    auto m = norm2(v1);
    REQUIRE(m == APPROX(v1.x * v1.x + v1.y * v1.y + v1.z * v1.z));
  }
}

TEST_CASE("Vector3", "[scalar add]") {
  for (size_t i = 0; i < RAND_TEST_NUM; ++i) {
    Vector v1{UTEST_RAND, UTEST_RAND, UTEST_RAND};

    utest_scalar c = UTEST_RAND;

    auto v3 = c + v1;
    REQUIRE(v3.x == APPROX(v1.x + c));
    REQUIRE(v3.y == APPROX(v1.y + c));
    REQUIRE(v3.z == APPROX(v1.z + c));
  }
}

TEST_CASE("Vector3", "[scalar sub]") {
  for (size_t i = 0; i < RAND_TEST_NUM; ++i) {
    Vector v1{UTEST_RAND, UTEST_RAND, UTEST_RAND};

    utest_scalar c = UTEST_RAND;

    auto v3 = c - v1;
    REQUIRE(v3.x == APPROX(c - v1.x));
    REQUIRE(v3.y == APPROX(c - v1.y));
    REQUIRE(v3.z == APPROX(c - v1.z));
  }
}

TEST_CASE("Vector3", "[scalar mul]") {
  for (size_t i = 0; i < RAND_TEST_NUM; ++i) {
    Vector v1{UTEST_RAND, UTEST_RAND, UTEST_RAND};

    utest_scalar c = UTEST_RAND;

    auto v3 = c * v1;
    REQUIRE(v3.x == APPROX(v1.x * c));
    REQUIRE(v3.y == APPROX(v1.y * c));
    REQUIRE(v3.z == APPROX(v1.z * c));
  }
}

TEST_CASE("Vector3", "[scalar div]") {
  for (size_t i = 0; i < RAND_TEST_NUM; ++i) {
    Vector v1{UTEST_RAND, UTEST_RAND, UTEST_RAND};

    utest_scalar c = UTEST_RAND;

    auto v3 = c / v1;
    REQUIRE(v3.x == APPROX(c / v1.x));
    REQUIRE(v3.y == APPROX(c / v1.y));
    REQUIRE(v3.z == APPROX(c / v1.z));
  }
}

TEST_CASE("Vector3", "[dot product]") {
  for (size_t i = 0; i < RAND_TEST_NUM; ++i) {
    Vector v1{UTEST_RAND, UTEST_RAND, UTEST_RAND};
    Vector v2{UTEST_RAND, UTEST_RAND, UTEST_RAND};

    auto p = dot(v1, v2);

    REQUIRE(p == APPROX(v1.x * v2.x + v1.y * v2.y + v1.z * v2.z));
  }
}

TEST_CASE("Vector3", "[dot product]") {
  for (size_t i = 0; i < RAND_TEST_NUM; ++i) {
    Vector v1{UTEST_RAND, UTEST_RAND, UTEST_RAND};
    Vector v2{UTEST_RAND, UTEST_RAND, UTEST_RAND};

    auto p = dot(v1, v2);

    REQUIRE(p == APPROX(v1.x * v2.x + v1.y * v2.y + v1.z * v2.z));
  }
}

TEST_CASE("Vector3", "[cross product]") {
  for (size_t i = 0; i < RAND_TEST_NUM; ++i) {
    Vector v1{UTEST_RAND, UTEST_RAND, UTEST_RAND};
    Vector v2{UTEST_RAND, UTEST_RAND, UTEST_RAND};

    auto p = cross(v1, v2);

    REQUIRE(p.x == APPROX(v1.y * v2.z - v1.z * v2.y));
    REQUIRE(p.y == APPROX(v1.z * v2.x - v1.x * v2.z));
    REQUIRE(p.z == APPROX(v1.x * v2.y - v1.y * v2.x));
  }
}

TEST_CASE("Vector3", "[distance]") {
  for (size_t i = 0; i < RAND_TEST_NUM; ++i) {
    Vector v1{UTEST_RAND, UTEST_RAND, UTEST_RAND};
    Vector v2{UTEST_RAND, UTEST_RAND, UTEST_RAND};

    auto d = distance(v1, v2);
    auto dx = v1.x - v2.x;
    auto dy = v1.y - v2.y;
    auto dz = v1.z - v2.z;

    REQUIRE(d == APPROX(sqrt(dx * dx + dy * dy + dz * dz)));
  }
}

