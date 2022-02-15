#pragma once

#include "optional-copy-assignable-base.h"

namespace optional_traits {

template <typename T, bool is_trivially>
struct optional_move_assignable_base
    : optional_copy_assignable_base<T, std::is_trivially_copy_assignable_v<T>> {
  using base = optional_copy_assignable_base<T, std::is_trivially_copy_assignable_v<T>>;
  using base::base;

  constexpr optional_move_assignable_base(optional_move_assignable_base const&) = default;
  constexpr optional_move_assignable_base(optional_move_assignable_base&&) = default;
  optional_move_assignable_base& operator=(optional_move_assignable_base const&) = default;
  optional_move_assignable_base& operator=(optional_move_assignable_base&& other) {
    if (this != &other) {
      if (this->is_calculated) {
        if (!other.is_calculated) {
          this->destroy();
        } else {
          this->value = std::move(other.value);
        }
      } else {
        if (other.is_calculated) {
          this->construct(std::move(other.value));
        }
      }
    }
    return *this;
  }
};

template <typename T>
struct optional_move_assignable_base<T, true>
    : optional_copy_assignable_base<T, std::is_trivially_copy_assignable_v<T>> {
  using base =  optional_copy_assignable_base<T, std::is_trivially_copy_assignable_v<T>>;
  using base::base;

  constexpr optional_move_assignable_base(optional_move_assignable_base const&) = default;
  constexpr optional_move_assignable_base(optional_move_assignable_base&&) = default;
  optional_move_assignable_base& operator=(optional_move_assignable_base const&) = default;
  optional_move_assignable_base& operator=(optional_move_assignable_base&&) = default;
};

}
