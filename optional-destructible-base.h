#pragma once

#include <cstdlib>
#include <type_traits>
#include <utility>

struct nullopt_t {};
struct in_place_t {};

constexpr inline nullopt_t nullopt;
constexpr inline in_place_t in_place;

namespace optional_traits {

template <typename T, bool is_trivially>
struct optional_destructible_base {
  constexpr optional_destructible_base() noexcept : dummy() {}

  constexpr explicit optional_destructible_base(T&& value)
      : is_calculated(true), value(std::move(value)) {}

  template <typename... Args>
  constexpr explicit optional_destructible_base(in_place_t, Args&&... args)
      : is_calculated(true), value(std::forward<Args>(args)...) {}

  template <typename... Args>
  void construct(Args&&... args) {
    new (&this->value) T(std::forward<Args>(args)...);
    this->is_calculated = true;
  }

  void destroy() noexcept {
    if (is_calculated) {
      value.~T();
      is_calculated = false;
    }
  }

  ~optional_destructible_base() {
    destroy();
  }

  bool is_calculated{false};
  union {
    char dummy;
    T value;
  };
};

template <typename T>
struct optional_destructible_base<T, true> {
  constexpr optional_destructible_base() noexcept : dummy() {}

  constexpr explicit optional_destructible_base(T&& value)
      : is_calculated(true), value(std::move(value)) {}

  template <typename... Args>
  constexpr explicit optional_destructible_base(in_place_t, Args&&... args)
      : is_calculated(true), value(std::forward<Args>(args)...) {}

  template <typename... Args>
  void construct(Args&&... args) {
    new (&this->value) T(std::forward<Args>(args)...);
    this->is_calculated = true;
  }

  void destroy() noexcept {
    if (is_calculated) {
      value.~T();
      is_calculated = false;
    }
  }

  ~optional_destructible_base() = default;

  bool is_calculated{false};
  union {
    char dummy;
    T value;
  };
};

}
