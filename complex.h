#pragma once
#include <type_traits>
#include <ostream>

namespace complex {
typedef long double ld;
class polar;
class cartesian {
 public:
  cartesian(ld, ld);
  explicit cartesian(polar);
  cartesian(ld);
  cartesian();

  ld re() const;
  ld im() const;
  void re(ld);
  void im(ld);

  ld abs() const;
  ld arg() const;
  cartesian conjugate() const;
  cartesian reciprocal() const;

  cartesian &operator=(const cartesian &) = default;
  cartesian &operator=(ld);

  bool operator==(const cartesian &) const;
  bool operator==(const polar &) const;

  bool operator!=(const cartesian &) const;
  bool operator!=(const polar &) const;

  cartesian &operator+=(const cartesian &);
  cartesian &operator+=(ld);

  cartesian &operator-=(const cartesian &);
  cartesian &operator-=(ld);

  cartesian &operator*=(const cartesian &);
  cartesian &operator*=(ld);

  cartesian &operator/=(const cartesian &);
  cartesian &operator/=(ld);

  friend cartesian operator+(cartesian, const cartesian &);
  friend cartesian operator+(cartesian, ld);
  friend cartesian operator+(ld, const cartesian &);

  friend cartesian operator-(cartesian, const cartesian &);
  friend cartesian operator-(cartesian, ld);
  friend cartesian operator-(ld, const cartesian &);
  friend cartesian operator-(cartesian);

  friend cartesian operator*(cartesian, const cartesian &);
  friend cartesian operator*(cartesian, ld);
  friend cartesian operator*(ld, const cartesian &);

  friend cartesian operator/(cartesian, const cartesian &);
  friend cartesian operator/(cartesian, ld);
  friend cartesian operator/(ld, const cartesian &);

  friend cartesian pow(const cartesian &, uint32_t);

  friend std::ostream &operator<<(std::ostream &, const cartesian &);

 private:
  ld re_, im_;
  inline ld sqr_abs_() const;
};

class polar {
 public:
  polar(ld, ld);
  explicit polar(cartesian);
  polar(ld);
  polar();

  ld rho() const;
  ld phi() const;
  void rho(ld);
  void phi(ld);

  ld abs() const;
  ld arg() const;

  polar &operator=(const polar &) = default;
  polar &operator=(ld);

  bool operator==(const polar &) const;
  bool operator==(const cartesian &) const;

  bool operator!=(const polar &) const;
  bool operator!=(const cartesian &) const;

  polar &operator+=(const polar &);
  polar &operator+=(ld);

  polar &operator-=(const polar &);
  polar &operator-=(ld);

  polar &operator*=(const polar &);
  polar &operator*=(ld);

  polar &operator/=(const polar &);
  polar &operator/=(ld);

  friend polar operator+(const polar &, const polar &);
  friend polar operator+(const polar &, ld);
  friend polar operator+(ld, const polar &);

  friend polar operator-(const polar &, const polar &);
  friend polar operator-(const polar &, ld);
  friend polar operator-(ld, const polar &);
  friend polar operator-(polar);

  friend polar operator*(polar, const polar &);
  friend polar operator*(polar, ld);
  friend polar operator*(ld, polar);

  friend polar operator/(polar, const polar &);
  friend polar operator/(polar, ld);
  friend polar operator/(ld, const polar &);

  friend polar pow(polar, uint32_t);

  friend std::ostream &operator<<(std::ostream &, const polar &);

 private:
  ld rho_, phi_;
};
const cartesian I(0, 1);
}  // namespace complex
