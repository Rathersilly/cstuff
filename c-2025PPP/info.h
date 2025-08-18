#include <chrono>
#include <iomanip>
#include <iostream>
#include <thread>

#include "color_macros.h"

// #define INFO                                                                   \
  // std::cout << "[" << std::this_thread::get_id() << "] " << __FILE__ << ":"    \
  //           << __LINE__ << " " << __PRETTY_FUNCTION__ << "\n";

#define INFO                                                                   \
  std::cout << __FILE__ << ":" << BRIGHT_CYAN << __LINE__ << BRIGHT_GREEN      \
            << "\t" << __PRETTY_FUNCTION__ << RESET << "\n";
//
// #define INFO \
//   std::cout << __FILE__ << ":" << __LINE__ << " -> " << __PRETTY_FUNCTION__ \
//             << "\n";
//
// #define INFO \
//   std::cout << "\t" << "Function: " << __PRETTY_FUNCTION__ << std::endl;

// here are some functions that are like debug hooks to see when entering/
// exiting functions.  function names are mangled
// these compiler optionts are needed:
// -finstrument-functions -rdynamic
//
// #include <cstdio>
// #include <cstring>
//
// #include <dlfcn.h>
//
// extern "C" void __cyg_profile_func_enter(void* this_fn, void* call_site)
//     __attribute__((no_instrument_function));
//
// extern "C" void __cyg_profile_func_enter(void* this_fn, void* call_site) {
//   __attribute__((no_instrument_function));
//   Dl_info info;
//   if (dladdr(this_fn, &info)) {
//     // printf ("%s \n", info.dli_fname);
//     // printf ("%s \n", info.dli_sname);
//
//     // info.dli_fname -> path to binary / shared object
//     // info.dli_sname -> symbol name (mangled)
//     if (strstr(info.dli_fname, "my_vector")) { // filter by filename
//       printf("Enter: %s\n", info.dli_sname ? info.dli_sname : "??");
//       std::cout  << info.dli_fname << info.dli_sname << __PRETTY_FUNCTION__
//       << std::endl;
//     }
//
//   }
// }
