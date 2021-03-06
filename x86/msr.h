#pragma once

#include <x86/cpuid.h>

//! Declarations

namespace x86
{

  //! True if model specific registers are supported
  //! @pre x = cpuid(1)

  constexpr
  auto has_msr (cpuid x) -> bool ;

  //! True if model specific registers are supported
  //! @pre has_cpuid()

  auto has_msr () -> bool ;

  //! Model specific registers

  enum class msr : uint32_t
  {
    IA32_APIC_BASE   = 0x1B,
    IA32_MISC_ENABLE = 0x1A0
  };

  //! Read value of model specific register
  //! @pre has_msr()

  auto read_msr (uint32_t id) -> uint64_t ;

  //! Write value into model specific register
  //! @pre has_msr()

  void write_msr (uint32_t id, uint32_t value);

  //! Write value into model specific register
  //! @pre has_msr()

  void write_msr (uint32_t id, uint64_t value);

  //! Read value of model specific register
  //! @pre has_msr()

  auto read_msr (msr id) -> uint64_t ;

  //! Write value into model specific register
  //! @pre has_msr()

  void write_msr (msr id, uint32_t value);

  //! Write value into model specific register
  //! @pre has_msr()

  void write_msr (msr id, uint64_t value);

}

//! Inline definitions

namespace x86
{

  namespace internal
  {

    extern "C"
    uint64_t __read_msr ( uint32_t id ) __attribute__(( fastcall )) ;

    extern "C"
    void __write_msr_32 ( uint32_t id, uint32_t value ) __attribute__(( fastcall )) ;

    extern "C"
    void __write_msr_64 ( uint32_t id, uint64_t value ) __attribute__(( fastcall ));

  }

  inline constexpr
  auto has_msr (cpuid x) -> bool
  {
    return (x.d() & 0b10000) != 0 ;
  }

  inline
  auto has_msr () -> bool
  {
    return has_msr(cpuid(1));
  }

  inline
  auto read_msr (uint32_t id) -> uint64_t
  {
    return internal::__read_msr(id);
  }

  inline
  void write_msr (uint32_t id, uint32_t value)
  {
    internal::__write_msr_32(id, value);
  }

  inline
  void write_msr (uint32_t id, uint64_t value)
  {
    internal::__write_msr_64(id, value);
  }

  inline
  auto read_msr (msr id) -> uint64_t
  {
    return read_msr((uint32_t)(id));
  }

  inline
  void write_msr (msr id, uint32_t value)
  {
    write_msr((uint32_t)(id), value);
  }

  inline
  void write_msr (msr id, uint64_t value)
  {
    write_msr((uint32_t)(id), value);
  }

}
