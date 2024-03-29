#ifndef SAUROS_PKG_SIGNAL
#define SAUROS_PKG_SIGNAL

#include <libsauros/sauros.hpp>

#ifdef WIN32
#define API_EXPORT __declspec(dllexport)
#else
#define API_EXPORT
#endif

extern "C" {

/*
   Set the signal handler function for all signals
*/
API_EXPORT
extern sauros::cell_ptr
_pkg_set_signal_handler_all_(sauros::cells_t &cells,
                             std::shared_ptr<sauros::environment_c> env);
/*
   Set the signal handler function for specific signal
*/
API_EXPORT
extern sauros::cell_ptr
_pkg_set_signal_handler_(sauros::cells_t &cells,
                         std::shared_ptr<sauros::environment_c> env);
}

#endif