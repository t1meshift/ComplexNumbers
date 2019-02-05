#include <cmath>
#include <string>
#include "complex.h"

namespace complex {
const ld EPS = 1e-8;
cartesian::cartesian(ld re, ld im) : re_(re), im_(im) {}
cartesian::cartesian(polar n) {
  re_ = n.rho() * cosl(n.phi());
  im_ = n.rho() * sinl(n.phi());
}
cartesian::cartesian(ld n) {
  re_ = n;
  im_ = 0;
}
cartesian::cartesian() {
  re_ = 0;
  im_ = 0;
}

ld cartesian::re() const {
  return this->re_;
}
ld cartesian::im() const {
  return this->im_;
}
void cartesian::re(ld val) {
  re_ = val;
}
void cartesian::im(ld val) {
  im_ = val;
}

cartesian &cartesian::operator=(ld val) {
  re_ = val;
  im_ = 0;
  return *this;
}

bool cartesian::operator==(const cartesian &val) const {
  return fabsl(re_ - val.re_) < EPS && fabsl(im_ - val.im_) < EPS;
}
bool cartesian::operator==(const polar &val) const {
  return *this == cartesian(val);
}

bool cartesian::operator!=(const cartesian &val) const {
  return !operator==(val);
}
bool cartesian::operator!=(const polar &val) const {
  return !operator==(val);
}

cartesian &cartesian::operator+=(const cartesian &r) {
  re_ += r.re_;
  im_ += r.im_;
  return *this;
}
cartesian &cartesian::operator+=(ld val) {
  re_ += val;
  return *this;
}

cartesian &cartesian::operator-=(const cartesian &val) {
  re_ -= val.re_;
  im_ -= val.im_;
  return *this;
}
cartesian &cartesian::operator-=(ld val) {
  re_ -= val;
  return *this;
}

cartesian &cartesian::operator*=(const cartesian &val) {
  ld old_re = re_;
  re_ = (re_*val.re_ - im_*val.im_);
  im_ = (old_re*val.im_ + im_*val.re_);
  return *this;
}
cartesian &cartesian::operator*=(ld val) {
  re_ *= val;
  im_ *= val;
  return *this;
}

cartesian &cartesian::operator/=(const cartesian &val) {
  cartesian t = *this * val.reciprocal();
  re_ = t.re();
  im_ = t.im();
  return *this;
}
cartesian &cartesian::operator/=(ld val) {
  re_ /= val;
  im_ /= val;
  return *this;
}

cartesian operator+(cartesian l, const cartesian &r) {
  l += r;
  return l;
}
cartesian operator+(cartesian l, ld r) {
  l += r;
  return l;
}
cartesian operator+(ld l, const cartesian &r) {
  cartesian val(l, 0);
  return val += r;
}

cartesian operator-(cartesian l, const cartesian &r) {
  l -= r;
  return l;
}
cartesian operator-(cartesian l, ld r) {
  l -= r;
  return l;
}
cartesian operator-(ld l, const cartesian &r) {
  cartesian val(l, 0);
  return val -= r;
}
cartesian operator-(cartesian val) {
  return val*-1;
}

cartesian operator*(cartesian l, const cartesian &r) {
  l *= r;
  return l;
}
cartesian operator*(cartesian l, ld r) {
  l *= r;
  return l;
}
cartesian operator*(ld l, const cartesian &r) {
  cartesian val(l, 0);
  return val *= r;
}

cartesian operator/(cartesian l, const cartesian &r) {
  l /= r;
  return l;
}
cartesian operator/(cartesian l, ld r) {
  l /= r;
  return l;
}
cartesian operator/(ld l, const cartesian &r) {
  return l * r.reciprocal();
}

cartesian cartesian::conjugate() const {
  return cartesian(re_, -im_);
}
cartesian cartesian::reciprocal() const {
  ld sa = sqr_abs_();
  ld re = re_/sa;
  ld im = -im_/sa;
  return cartesian(re, im);
}
ld cartesian::abs() const {
  return sqrtl(sqr_abs_());
}
ld cartesian::arg() const {
  return atan2l(im_, re_);
}

ld cartesian::sqr_abs_() const {
  return re_*re_ + im_*im_;
}

std::ostream &operator<<(std::ostream &stream, const cartesian &val) {
  return stream << '(' << val.re_ << ", " << val.im_ << ')';
}

cartesian pow(const cartesian &x, uint32_t y) {
  return cartesian(pow(polar(x), y));
}

polar::polar(ld rho, ld phi) : rho_(rho), phi_(phi) {}
polar::polar(cartesian n) {
  rho_ = n.abs();
  phi_ = n.arg();
}
polar::polar(ld n) {
  rho_ = n;
  phi_ = 0;
}
polar::polar() {
  rho_ = 0;
  phi_ = 0;
}

ld polar::rho() const {
  return rho_;
}
ld polar::phi() const {
  return phi_;
}
void polar::rho(ld val) {
  rho_ = val;
}
void polar::phi(ld val) {
  phi_ = val;
}

ld polar::abs() const {
  return rho();
}
ld polar::arg() const {
  return phi();
}

polar &polar::operator=(ld val) {
  rho_ = val;
  phi_ = atan2l(0, val);
  return *this;
}

bool polar::operator==(const polar &val) const {
  return cartesian(*this) == cartesian(val);
}
bool polar::operator==(const cartesian &val) const {
  return cartesian(*this) == val;
}

bool polar::operator!=(const polar &val) const {
  return !operator==(val);
}
bool polar::operator!=(const cartesian &val) const {
  return !operator==(val);
}

polar &polar::operator+=(const polar &val) {
  auto t = *this + val;
  rho_ = t.rho();
  phi_ = t.phi();
  return *this;
}
polar &polar::operator+=(ld val) {
  auto t = *this + val;
  rho_ = t.rho();
  phi_ = t.phi();
  return *this;
}

polar &polar::operator-=(const polar &val) {
  auto t = *this - val;
  rho_ = t.rho();
  phi_ = t.phi();
  return *this;
}
polar &polar::operator-=(ld val) {
  auto t = *this - val;
  rho_ = t.rho();
  phi_ = t.phi();
  return *this;
}

polar &polar::operator*=(const polar &val) {
  rho_ *= val.rho();
  phi_ += val.phi();
  return *this;
}
polar &polar::operator*=(ld val) {
  rho_ *= val;
  return *this;
}

polar &polar::operator/=(const polar &val) {
  rho_ /= val.rho();
  phi_ -= val.phi();
  return *this;
}
polar &polar::operator/=(ld val) {
  rho_ /= val;
  return *this;
}

polar operator+(const polar &l, const polar &r) {
  return polar(cartesian(l) + cartesian(r));
}
polar operator+(const polar &l, ld r) {
  return polar(cartesian(l) + r);
}
polar operator+(ld l, const polar &r) {
  return r + l;
}

polar operator-(const polar &l, const polar &r) {
  return polar(cartesian(l) - cartesian(r));
}
polar operator-(const polar &l, ld r) {
  return polar(cartesian(l) - r);
}
polar operator-(ld l, const polar &r) {
  return -r + l;
}
polar operator-(polar val) {
  return val * -1;
}

polar operator*(polar l, const polar &r) {
  l *= r;
  return l;
}
polar operator*(polar l, ld r) {
  l *= r;
  return l;
}
polar operator*(ld l, polar r) {
  r *= l;
  return r;
}

polar operator/(polar l, const polar &r) {
  l /= r;
  return l;
}
polar operator/(polar l, ld r) {
  l /= r;
  return l;
}
polar operator/(ld l, const polar &r) {
  return polar(cartesian(l, 0)) / r;
}

polar pow(polar x, uint32_t y) {
  x.rho(powl(x.rho(), y));
  x.phi(x.phi() * y);
  return polar(cartesian(x));
}

std::ostream &operator<<(std::ostream &stream, const polar &val) {
  return stream << '(' << val.rho_ << ", " << val.phi_ << ')';
}
}  // namespace complex


