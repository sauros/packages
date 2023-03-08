#include "package.hpp"
#include <libsauros/capi/capi.hpp>
#include <string>

#include <arpa/inet.h>
#include <errno.h>
#include <iostream>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <unordered_map>

namespace {
std::unordered_map<int, sockaddr_in *> g_addrs;
}

sauros::cell_ptr _pkg_net_errno_(sauros::cells_t &cells,
                                 std::shared_ptr<sauros::environment_c> env) {
  return std::make_shared<sauros::cell_c>(sauros::cell_type_e::INTEGER,
                                          (sauros::cell_int_t)errno);
}

sauros::cell_ptr
_pkg_net_inet_addr_(sauros::cells_t &cells,
                    std::shared_ptr<sauros::environment_c> env) {
  std::string target = c_api_process_cell(cells[1], env)->data_as_str();
  return std::make_shared<sauros::cell_c>(
      sauros::cell_type_e::INTEGER,
      (sauros::cell_int_t)inet_addr(target.c_str()));
}

sauros::cell_ptr _pkg_net_htons_(sauros::cells_t &cells,
                                 std::shared_ptr<sauros::environment_c> env) {
  uint16_t target = c_api_process_cell(cells[1], env)->get_integer();
  return std::make_shared<sauros::cell_c>(sauros::cell_type_e::INTEGER,
                                          (sauros::cell_int_t)htons(target));
}

sauros::cell_ptr _pkg_net_socket_(sauros::cells_t &cells,
                                  std::shared_ptr<sauros::environment_c> env) {
  int domain = c_api_process_cell(cells[1], env)->get_integer();
  int type = c_api_process_cell(cells[2], env)->get_integer();
  int protocol = c_api_process_cell(cells[3], env)->get_integer();
  return std::make_shared<sauros::cell_c>(
      sauros::cell_type_e::INTEGER,
      (sauros::cell_int_t)socket(domain, type, protocol));
}

sauros::cell_ptr _pkg_net_close_(sauros::cells_t &cells,
                                 std::shared_ptr<sauros::environment_c> env) {
  int fd = c_api_process_cell(cells[1], env)->get_integer();

  auto result = close(fd);

  if (g_addrs.find(fd) != g_addrs.end()) {
    delete g_addrs[fd];
    g_addrs[fd] = nullptr;
  }

  return std::make_shared<sauros::cell_c>(sauros::cell_type_e::INTEGER,
                                          (sauros::cell_int_t)result);
}

sauros::cell_ptr _pkg_net_sockopt_(sauros::cells_t &cells,
                                   std::shared_ptr<sauros::environment_c> env) {
  int fd = c_api_process_cell(cells[1], env)->get_integer();
  int level = c_api_process_cell(cells[2], env)->get_integer();
  int opt_name = c_api_process_cell(cells[3], env)->get_integer();
  int opt = 1;
  return std::make_shared<sauros::cell_c>(
      sauros::cell_type_e::INTEGER,
      (sauros::cell_int_t)setsockopt(fd, level, opt_name, &opt, sizeof(opt)));
}

sauros::cell_ptr _pkg_net_bind_(sauros::cells_t &cells,
                                std::shared_ptr<sauros::environment_c> env) {
  int fd = c_api_process_cell(cells[1], env)->get_integer();

  if (g_addrs.find(fd) == g_addrs.end() || g_addrs[fd] == nullptr) {
    g_addrs[fd] = new sockaddr_in();
  }

  auto *address = g_addrs[fd];

  address->sin_family = c_api_process_cell(cells[2], env)->get_integer();
  address->sin_port = c_api_process_cell(cells[3], env)->get_integer();
  address->sin_addr.s_addr = c_api_process_cell(cells[4], env)->get_integer();

  auto result = bind(fd, (struct sockaddr *)address, sizeof(*address));
  return std::make_shared<sauros::cell_c>(sauros::cell_type_e::INTEGER,
                                          (sauros::cell_int_t)result);
}

sauros::cell_ptr _pkg_net_connect_(sauros::cells_t &cells,
                                   std::shared_ptr<sauros::environment_c> env) {
  int fd = c_api_process_cell(cells[1], env)->get_integer();

  if (g_addrs.find(fd) == g_addrs.end() || g_addrs[fd] == nullptr) {
    g_addrs[fd] = new sockaddr_in();
  }

  auto *address = g_addrs[fd];

  address->sin_family = c_api_process_cell(cells[2], env)->get_integer();
  address->sin_port = c_api_process_cell(cells[3], env)->get_integer();
  address->sin_addr.s_addr = c_api_process_cell(cells[4], env)->get_integer();

  auto result = connect(fd, (struct sockaddr *)address, sizeof(*address));
  return std::make_shared<sauros::cell_c>(sauros::cell_type_e::INTEGER,
                                          (sauros::cell_int_t)result);
}

sauros::cell_ptr _pkg_net_listen_(sauros::cells_t &cells,
                                  std::shared_ptr<sauros::environment_c> env) {
  int fd = c_api_process_cell(cells[1], env)->get_integer();
  int n = c_api_process_cell(cells[2], env)->get_integer();

  return std::make_shared<sauros::cell_c>(sauros::cell_type_e::INTEGER,
                                          (sauros::cell_int_t)listen(fd, n));
}

sauros::cell_ptr _pkg_net_accept_(sauros::cells_t &cells,
                                  std::shared_ptr<sauros::environment_c> env) {
  int fd = c_api_process_cell(cells[1], env)->get_integer();

  if (g_addrs.find(fd) == g_addrs.end()) {
    return std::make_shared<sauros::cell_c>(sauros::cell_type_e::INTEGER,
                                            (sauros::cell_int_t)-1);
  }

  auto *address = g_addrs[fd];

  auto addrlen = sizeof(*address);

  int new_socket_fd =
      accept(fd, (struct sockaddr *)address, (socklen_t *)&addrlen);

  return std::make_shared<sauros::cell_c>(sauros::cell_type_e::INTEGER,
                                          (sauros::cell_int_t)new_socket_fd);
}

sauros::cell_ptr _pkg_net_read_(sauros::cells_t &cells,
                                std::shared_ptr<sauros::environment_c> env) {
  int fd = c_api_process_cell(cells[1], env)->get_integer();
  int buffer_len = c_api_process_cell(cells[2], env)->get_integer();

  char *buffer = new char[buffer_len];
  memset(buffer, 0, buffer_len);

  int len = read(fd, buffer, buffer_len);

  std::string result_as_string = buffer;
  delete[] buffer;

  auto result = std::make_shared<sauros::cell_c>(sauros::cell_type_e::STRING,
                                                 result_as_string);
  return result;
}

sauros::cell_ptr _pkg_net_send_(sauros::cells_t &cells,
                                std::shared_ptr<sauros::environment_c> env) {
  int fd = c_api_process_cell(cells[1], env)->get_integer();
  std::string data = c_api_process_cell(cells[2], env)->data_as_str();
  int flags = c_api_process_cell(cells[3], env)->get_integer();

  int sent = send(fd, data.data(), data.size(), flags);

  return std::make_shared<sauros::cell_c>(sauros::cell_type_e::INTEGER,
                                          (sauros::cell_int_t)sent);
}

sauros::cell_ptr
_pkg_net_shutdown_(sauros::cells_t &cells,
                   std::shared_ptr<sauros::environment_c> env) {
  int fd = c_api_process_cell(cells[1], env)->get_integer();
  int how = c_api_process_cell(cells[2], env)->get_integer();

  return std::make_shared<sauros::cell_c>(
      sauros::cell_type_e::INTEGER, (sauros::cell_int_t)shutdown(fd, how));
}