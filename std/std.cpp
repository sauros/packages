#include "std.hpp"

#include <libsauros/capi/capi.hpp>
#include <string>

sauros::cell_ptr
_pkg_std_list_make_assigned_(sauros::cells_t &cells,
                             std::shared_ptr<sauros::environment_c> env) {
  auto value = c_api_process_cell(cells[1], env);
  auto size = c_api_process_cell(cells[2], env);

  if (size->type != sauros::cell_type_e::INTEGER) {
    throw sauros::exceptions::runtime_c(
        "size parameter expected to be of type integer", cells[2]);
  }

  sauros::cell_ptr result =
      std::make_shared<sauros::cell_c>(sauros::cell_type_e::LIST);
  result->list.assign(size->get_integer(), value);
  return result;
}

sauros::cell_ptr
_pkg_std_list_sort_(sauros::cells_t &cells,
                    std::shared_ptr<sauros::environment_c> env) {
  auto data = c_api_process_cell(cells[1], env);

  if (data->type != sauros::cell_type_e::LIST) {
    throw sauros::exceptions::runtime_c(
        "data parameter expected to be of type list", cells[1]);
  }

  std::sort(data->list.begin(), data->list.end(),
            [cells](const sauros::cell_ptr &lhs,
                    const sauros::cell_ptr &rhs) -> bool {
              auto is_valid_for_sorty = [](const sauros::cell_ptr &c) -> bool {
                return !(c->type != sauros::cell_type_e::INTEGER &&
                         c->type != sauros::cell_type_e::REAL);
              };
              auto force_double = [](const sauros::cell_ptr &l,
                                     const sauros::cell_ptr &r) -> bool {
                return (l->type == sauros::cell_type_e::REAL ||
                        r->type == sauros::cell_type_e::REAL);
              };

              if (!is_valid_for_sorty(lhs) || !is_valid_for_sorty(rhs)) {
                throw sauros::exceptions::runtime_c(
                    "Unable to sort non-numerical item in list", cells[0]);
              }

              if (force_double(lhs, rhs)) {
                double lhs_d = lhs->get_real();
                double rhs_d = rhs->get_real();
                if (lhs->type == sauros::cell_type_e::INTEGER) {
                  lhs_d = lhs->get_integer();
                }
                if (rhs->type == sauros::cell_type_e::INTEGER) {
                  rhs_d = rhs->get_integer();
                }
                return lhs_d, rhs_d;
              }

              return lhs->get_integer() < rhs->get_integer();
            });
  return data;
}
