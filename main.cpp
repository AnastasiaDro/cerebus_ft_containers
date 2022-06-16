#include <iostream>
#include "test_headers.hpp"
// #include "tester_vector.cpp"
// #include "tester_stack.cpp"
// #include "tester_map.cpp"

#include "vector.hpp"

void my_vector_test() {
    std::cout << "======================== VECTOR ========================" << std::endl;

    vector_constructor_test();
    vector_operator_equel_test();
    vector_iterator_test();
    vector_reverse_iterator_test();
    vector_size_test();
    vector_max_size_test();
    vector_resize_test();
    vector_empty_test();
    vector_reserve_test();
    vector_operator_el_pos_test();
    vector_at_test();
    vector_front_test();
    vector_back_test();
    vector_assign_test();
    vector_push_pop_test();
    vector_insert_test();
    vector_erase_test();
    vector_swap_test();
    vector_clear_test();
    vector_get_allocator_test();
    vector_relational_operators_test();
    vector_swap_rela_test();

    vector_string_begin_end_test();
    vector_string_resize_reserve_test();
    vector_string_swap_test();
    vector_string_insert_erase_test();
}

void my_map_test() {
    std::cout << "========================== MAP =========================" << std::endl;
    map_all_test();
    map_spec_test();
    map_swap_test();
    map_bound_test();
    map_count_test();
    map_equal_range_test();
    map_value_compare_test();
    map_key_compare_test();
    map_get_allocator_test();
    map_comparison_operator_test();
    map_make_pair_test();
    map_speed_test();
}

void my_stack_test() {
    std::cout << "========================= STACK ========================" << std::endl;
    stack_constructor_test();
    stack_empty_test();
    stack_top_test();
    stack_push_pop_test();
}

int main() {
	 //my_vector_test();
	 //my_stack_test();
	my_map_test();
	return (0);
}
