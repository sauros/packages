#ifndef SAUROS_PKG_HPP
#define SAUROS_PKG_HPP
#include <sauros/sauros.hpp>
#ifdef WIN32
#define API_EXPORT __declspec(dllexport)
#else
#define API_EXPORT
#endif
extern "C" {

/*
   Get errno
*/
API_EXPORT
extern sauros::cell_ptr
_pkg_net_errno_(sauros::cells_t &cells,
                std::shared_ptr<sauros::environment_c> env);

/*
   Get htons
*/
API_EXPORT
extern sauros::cell_ptr
_pkg_net_htons_(sauros::cells_t &cells,
                std::shared_ptr<sauros::environment_c> env);

/*
   Get inet_addr
*/
API_EXPORT
extern sauros::cell_ptr
_pkg_net_inet_addr_(sauros::cells_t &cells,
                    std::shared_ptr<sauros::environment_c> env);

/*
   Create a socket fd
*/
API_EXPORT
extern sauros::cell_ptr
_pkg_net_socket_(sauros::cells_t &cells,
                 std::shared_ptr<sauros::environment_c> env);

/*
   Close a socket fd
*/
API_EXPORT
extern sauros::cell_ptr
_pkg_net_close_(sauros::cells_t &cells,
                std::shared_ptr<sauros::environment_c> env);

/*
   Set sock opt
*/
API_EXPORT
extern sauros::cell_ptr
_pkg_net_sockopt_(sauros::cells_t &cells,
                  std::shared_ptr<sauros::environment_c> env);

/*
   Set sock opt
*/
API_EXPORT
extern sauros::cell_ptr
_pkg_net_bind_(sauros::cells_t &cells,
               std::shared_ptr<sauros::environment_c> env);

/*
   Set sock opt
*/
API_EXPORT
extern sauros::cell_ptr
_pkg_net_connect_(sauros::cells_t &cells,
                  std::shared_ptr<sauros::environment_c> env);

/*
   Listen on a socket
*/
API_EXPORT
extern sauros::cell_ptr
_pkg_net_listen_(sauros::cells_t &cells,
                 std::shared_ptr<sauros::environment_c> env);

/*
   Listen on a socket
*/
API_EXPORT
extern sauros::cell_ptr
_pkg_net_accept_(sauros::cells_t &cells,
                 std::shared_ptr<sauros::environment_c> env);

/*
   Read on a socket
*/
API_EXPORT
extern sauros::cell_ptr
_pkg_net_read_(sauros::cells_t &cells,
               std::shared_ptr<sauros::environment_c> env);

/*
   Send on a socket
*/
API_EXPORT
extern sauros::cell_ptr
_pkg_net_send_(sauros::cells_t &cells,
               std::shared_ptr<sauros::environment_c> env);

/*
   Shutdown
*/
API_EXPORT
extern sauros::cell_ptr
_pkg_net_shutdown_(sauros::cells_t &cells,
                   std::shared_ptr<sauros::environment_c> env);
}
#endif
