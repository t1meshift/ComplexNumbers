#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <string>
#include "complex.h"

using complex::I;

TEST_CASE("Getters") {
  SECTION("Zero args initialization") {
    complex::cartesian a;
    REQUIRE(a.re() == 0);
    REQUIRE(a.im() == 0);

    complex::polar b;
    REQUIRE(b.rho() == 0);
    REQUIRE(b.phi() == 0);
  }
  SECTION("Non-zero args initialization") {
    complex::cartesian a(1, 1);
    REQUIRE(a.re() == 1);
    REQUIRE(a.im() == 1);

    complex::polar b(1, 1);
    REQUIRE(b.rho() == 1);
    REQUIRE(b.phi() == 1);
  }
}

TEST_CASE("Convert between types") {
  SECTION("Cartesian to polar") {
    complex::cartesian a(1, 0);
    complex::polar expected(1, 0);

    REQUIRE(complex::polar(a) == expected);
  }
  SECTION("Polar to cartesian") {
    complex::polar a(1, M_PI_2);
    complex::cartesian expected = I;

    REQUIRE(complex::cartesian(a) == expected);
  }
}

TEST_CASE("Comparison") {
  SECTION("Same-typed comparison") {
    {
      complex::cartesian num(2, 3);
      complex::cartesian expected = 2 + 3*I;

      REQUIRE(num == expected);
      REQUIRE_FALSE(num != expected);
    }
    {
      complex::polar num(2, 0);
      complex::polar expected(2, 2*M_PI);

      REQUIRE(num == expected);
      REQUIRE_FALSE(num != expected);
    }
  }
  SECTION("Different-typed comparison") {
    {
      complex::cartesian a(1, 0);
      complex::polar expected(1, 0);

      REQUIRE(a == expected);
      REQUIRE_FALSE(a != expected);
    }
    {
      complex::polar a(1, M_PI_2);
      complex::cartesian expected = I;

      REQUIRE(a == expected);
      REQUIRE_FALSE(a != expected);
    }
  }
}

TEST_CASE("Setters") {
  complex::cartesian a;
  a.re(1);
  a.im(2);
  REQUIRE(a == 1+2*I);

  complex::polar b;
  b.rho(1);
  b.phi(M_PI_2);
  REQUIRE(b == I);
}

TEST_CASE("Assignments") {
  SECTION("Assign cartesian to cartesian") {
    complex::cartesian a = I;
    REQUIRE(a == I);
  }
  SECTION("Assign polar to polar") {
    complex::polar a;
    complex::polar b(1, 1);
    a = b;
    REQUIRE(a == b);
  }
  SECTION("Assign real to cartesian") {
    {
      complex::cartesian a = 228;
      complex::cartesian expected(228, 0);
      REQUIRE(a == expected);
    }
    {
      complex::cartesian a;
      complex::cartesian expected(228, 0);
      a = 228;
      REQUIRE(a == expected);
    }
  }
  SECTION("Assign real to polar") {
    {
      complex::polar a = 228;
      complex::polar expected(228, 0);
      REQUIRE(a == expected);
    }
    {
      complex::polar a;
      complex::polar expected(228, 0);
      a = 228;
      REQUIRE(a == expected);
    }
  }
}

TEST_CASE("Complex arithmetics (cartesian)") {
  SECTION("Addition of cartesian") {
    complex::cartesian a(2, 3);
    complex::cartesian b(4, 5);
    complex::cartesian expected(6, 8);
    REQUIRE(a + b == expected);
    REQUIRE(b + a == expected);

    a += b;
    REQUIRE(a == expected);
  }
  SECTION("Addition of real") {
    complex::cartesian a(2, 3);
    auto b = 6;
    complex::cartesian expected(8, 3);
    REQUIRE(a + b == expected);
    REQUIRE(b + a == expected);

    a += b;
    REQUIRE(a == expected);
  }

  SECTION("Subtraction of cartesian") {
    complex::cartesian a(2, 3);
    complex::cartesian b(4, 6);
    complex::cartesian expected(-2, -3);
    REQUIRE(a - b == expected);
    REQUIRE(b - a == -expected);

    a -= b;
    REQUIRE(a == expected);
  }
  SECTION("Subtraction of real") {
    complex::cartesian a(2, 3);
    auto b = 6;
    complex::cartesian expected(-4, 3);
    REQUIRE(a - b == expected);
    REQUIRE(b - a == -expected);

    a -= b;
    REQUIRE(a == expected);
  }

  SECTION("Multiplication of cartesian") {
    complex::cartesian a(2, 3);
    complex::cartesian b(4, 6);
    complex::cartesian expected(-10, 24);
    REQUIRE(a * b == expected);
    REQUIRE(b * a == expected);

    a *= b;
    REQUIRE(a == expected);
  }
  SECTION("Multiplication of real") {
    complex::cartesian a(2, 3);
    auto b = 6;
    complex::cartesian expected(12, 18);
    REQUIRE(a * b == expected);
    REQUIRE(b * a == expected);

    a *= b;
    REQUIRE(a == expected);
  }

  SECTION("Division of cartesian") {
    complex::cartesian a(2, 3);
    complex::cartesian b = I;
    complex::cartesian expected(3, -2);
    REQUIRE(a / b == expected);
    a /= b;
    REQUIRE(a == expected);
  }
  SECTION("Division of cartesian by real") {
    complex::cartesian a(6, 12);
    auto b = 2;
    complex::cartesian expected(3, 6);
    REQUIRE(a / b == expected);
    a /= b;
    REQUIRE(a == expected);
  }
  SECTION("Division of real by cartesian") {
    auto a = 25;
    complex::cartesian b(3, 4);
    complex::cartesian expected(3, -4);
    REQUIRE(a / b == expected);
  }
}

TEST_CASE("Complex arithmetics (polar)") {
  SECTION("Addition of polar") {
    complex::polar a(complex::cartesian(2, 3));
    complex::polar b(complex::cartesian(4, 5));
    complex::polar expected(complex::cartesian(6, 8));
    REQUIRE(a + b == expected);
    REQUIRE(b + a == expected);

    a += b;
    REQUIRE(a == expected);
  }
  SECTION("Addition of real") {
    complex::polar a(complex::cartesian(2, 3));
    auto b = 6;
    complex::polar expected(complex::cartesian(8, 3));
    REQUIRE(a + b == expected);
    REQUIRE(b + a == expected);

    a += b;
    REQUIRE(a == expected);
  }

  SECTION("Subtraction of polar") {
    complex::polar a(complex::cartesian(2, 3));
    complex::polar b(complex::cartesian(4, 6));
    complex::polar expected(complex::cartesian(-2, -3));
    REQUIRE(a - b == expected);
    REQUIRE(b - a == -expected);

    a -= b;
    REQUIRE(a == expected);
  }
  SECTION("Subtraction of real") {
    complex::polar a(complex::cartesian(2, 3));
    auto b = 6;
    complex::polar expected(complex::cartesian(-4, 3));
    REQUIRE(a - b == expected);
    REQUIRE(b - a == -expected);

    a -= b;
    REQUIRE(a == expected);
  }

  SECTION("Multiplication of polar") {
    complex::polar a(complex::cartesian(2, 3));
    complex::polar b(complex::cartesian(4, 6));
    complex::polar expected(complex::cartesian(-10, 24));
    REQUIRE(a * b == expected);
    REQUIRE(b * a == expected);

    a *= b;
    REQUIRE(a == expected);
  }
  SECTION("Multiplication of real") {
    complex::polar a(complex::cartesian(2, 3));
    auto b = 6;
    complex::polar expected(complex::cartesian(12, 18));
    REQUIRE(a * b == expected);
    REQUIRE(b * a == expected);

    a *= b;
    REQUIRE(a == expected);
  }

  SECTION("Division of polar") {
    complex::polar a(complex::cartesian(2, 3));
    complex::polar b(I);
    complex::polar expected(complex::cartesian(3, -2));
    REQUIRE(a / b == expected);
    a /= b;
    REQUIRE(a == expected);
  }
  SECTION("Division of polar by real") {
    complex::polar a(complex::cartesian(6, 12));
    auto b = 2;
    complex::polar expected(complex::cartesian(3, 6));
    REQUIRE(a / b == expected);
    a /= b;
    REQUIRE(a == expected);
  }
  SECTION("Division of real by polar") {
    auto a = 25;
    complex::polar b(complex::cartesian(3, 4));
    complex::polar expected(complex::cartesian(3, -4));
    REQUIRE(a / b == expected);
  }
}

TEST_CASE("Conjugation (cartesian)") {
  complex::cartesian a(3, 4);
  complex::cartesian expected(3, -4);
  REQUIRE(a.conjugate() == expected);
}

TEST_CASE("Absolute value and argument") {
  SECTION("Polar") {
    complex::polar a(3, M_PI_4);
    REQUIRE(a.abs() == 3);
    REQUIRE(a.arg() == M_PI_4);
  }
  SECTION("Cartesian") {
    complex::cartesian a = 3*I;
    REQUIRE(a.abs() == 3);
    REQUIRE(a.arg() == Approx(M_PI_2).margin(1e-8));
  }
}

TEST_CASE("Power by integer") {
  SECTION("Polar") {
    complex::polar a(4, M_PI_4);
    complex::polar expected(16, M_PI_2);
    REQUIRE(pow(a, 2) == expected);
  }
  SECTION("Cartesian") {
    complex::cartesian a = I;
    complex::cartesian expected = -1;
    REQUIRE(pow(a, 2) == expected);
  }
}

TEST_CASE("Output to stream") {
  SECTION("Cartesian") {
    std::stringstream ss;
    complex::cartesian a = I;
    std::string expected = "(0, 1)";
    ss << a;
    REQUIRE(ss.str() == expected);
  }
  SECTION("Polar") {
    std::stringstream ss;
    complex::polar a(1, 1);
    std::string expected = "(1, 1)";
    ss << a;
    REQUIRE(ss.str() == expected);
  }
}