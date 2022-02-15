#pragma once

#include "optional-move-assignable-base.h"

namespace optional_traits {

  template <bool enable>
  struct enable_copy_construct {
    constexpr enable_copy_construct() = default;
    enable_copy_construct(enable_copy_construct const&) = delete;
    constexpr enable_copy_construct(enable_copy_construct&&) = default;
    enable_copy_construct& operator=(enable_copy_construct const&) = default;
    enable_copy_construct& operator=(enable_copy_construct&&) = default;
  };

  template <>
  struct enable_copy_construct<true> {
    constexpr enable_copy_construct() = default;
    constexpr enable_copy_construct(enable_copy_construct const&) = default;
    constexpr enable_copy_construct(enable_copy_construct&&) = default;
    enable_copy_construct& operator=(enable_copy_construct const&) = default;
    enable_copy_construct& operator=(enable_copy_construct&&) = default;
  };

  template <bool enable>
  struct enable_move_construct {
    constexpr enable_move_construct() = default;
    constexpr enable_move_construct(enable_move_construct const&) = default;
    enable_move_construct(enable_move_construct&&) = delete;
    enable_move_construct& operator=(enable_move_construct const&) = default;
    enable_move_construct& operator=(enable_move_construct&&) = default;
  };

  template <>
  struct enable_move_construct<true> {
    constexpr enable_move_construct() = default;
    constexpr enable_move_construct(enable_move_construct const&) = default;
    constexpr enable_move_construct(enable_move_construct&&) = default;
    enable_move_construct& operator=(enable_move_construct const&) = default;
    enable_move_construct& operator=(enable_move_construct&&) = default;
  };

  template <bool enable>
  struct enable_copy_assign {
    constexpr enable_copy_assign() = default;
    constexpr enable_copy_assign(enable_copy_assign const&) = default;
    constexpr enable_copy_assign(enable_copy_assign&&) = default;
    enable_copy_assign& operator=(enable_copy_assign const&) = delete;
    enable_copy_assign& operator=(enable_copy_assign&&) = default;
  };

  template <>
  struct enable_copy_assign<true> {
    constexpr enable_copy_assign() = default;
    constexpr enable_copy_assign(enable_copy_assign const&) = default;
    constexpr enable_copy_assign(enable_copy_assign&&) = default;
    enable_copy_assign& operator=(enable_copy_assign const&) = default;
    enable_copy_assign& operator=(enable_copy_assign&&) = default;
  };

  template <bool enable>
  struct enable_move_assign {
    constexpr enable_move_assign() = default;
    constexpr enable_move_assign(enable_move_assign const&) = default;
    constexpr enable_move_assign(enable_move_assign&&) = default;
    enable_move_assign& operator=(enable_move_assign const&) = default;
    enable_move_assign& operator=(enable_move_assign&&) = delete;
  };

  template <>
  struct enable_move_assign<true> {
    constexpr enable_move_assign() = default;
    constexpr enable_move_assign(enable_move_assign const&) = default;
    constexpr enable_move_assign(enable_move_assign&&) = default;
    enable_move_assign& operator=(enable_move_assign const&) = default;
    enable_move_assign& operator=(enable_move_assign&&) = default;
  };
}
