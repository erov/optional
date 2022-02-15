#pragma once

#include "optional-traits.h"

template <typename T>
struct optional
    : optional_traits::optional_move_assignable_base<T, std::is_trivially_move_assignable_v<T>>,
      optional_traits::enable_copy_construct<std::is_copy_constructible_v<T>>,
      optional_traits::enable_move_construct<std::is_move_constructible_v<T>>,
      optional_traits::enable_copy_assign<std::is_copy_assignable_v<T>>,
      optional_traits::enable_move_assign<std::is_move_assignable_v<T>> {
private:
  using base = optional_traits::optional_move_assignable_base<T, std::is_trivially_move_assignable_v<T>>;

public:
  using base::base;

  constexpr optional(nullopt_t) noexcept : optional()  {}

  constexpr optional(optional const& other) = default;
  constexpr optional(optional&& other) = default;
  optional& operator=(optional const& other) = default;
  optional& operator=(optional&& other) = default;

  optional& operator=(nullopt_t) noexcept {
    reset();
    return *this;
  }

  constexpr explicit operator bool() const noexcept {
    return this->is_calculated;
  }

  constexpr T& operator*() noexcept {
    return this->value;
  }

  constexpr T const& operator*() const noexcept {
    return this->value;
  }

  constexpr T* operator->() noexcept {
    return &this->value;
  }

  constexpr T const* operator->() const noexcept {
    return &this->value;
  }

  template <typename... Args>
  void emplace(Args&&... args) {
    reset();
    this->construct(std::forward<Args>(args)...);
  }

  void reset() {
    this->destroy();
  }

  void swap(optional& other) {
    if (!this->is_calculated) {
      if (other.is_calculated) {
        this->construct(std::move(*other));
        other.destroy();
      }
    } else {
      if (other.is_calculated) {
        std::swap(**this, *other);
      } else {
        other.construct(std::move(**this));
        this->destroy();
      }
    }
  }
};

template <typename T>
constexpr bool operator==(optional<T> const& a, optional<T> const& b) {
  if (static_cast<bool>(a) != static_cast<bool>(b)) {
    return false;
  }
  if (!static_cast<bool>(a)) {
    return true;
  }
  return *a == *b;
}

template <typename T>
constexpr bool operator!=(optional<T> const& a, optional<T> const& b) {
  if (static_cast<bool>(a) != static_cast<bool>(b)) {
    return true;
  }
  if (!static_cast<bool>(a)) {
    return false;
  }
  return *a != *b;
}

template <typename T>
constexpr bool operator<(optional<T> const& a, optional<T> const& b) {
  if (!static_cast<bool>(b)) {
    return false;
  }
  if (!static_cast<bool>(a)) {
    return true;
  }
  return *a < *b;
}

template <typename T>
constexpr bool operator<=(optional<T> const& a, optional<T> const& b) {
  return a < b || a == b;
}

template <typename T>
constexpr bool operator>(optional<T> const& a, optional<T> const& b) {
  if (!static_cast<bool>(a)) {
    return false;
  }
  if (!static_cast<bool>(b)) {
    return true;
  }
  return *a > *b;
}

template <typename T>
constexpr bool operator>=(optional<T> const& a, optional<T> const& b) {
  return a > b || a == b;
}
