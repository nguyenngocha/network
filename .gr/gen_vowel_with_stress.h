wchar_t valves_with_stress[1000][5];
int valves_with_stress_size=0;
void insert_stress(wchar_t *valve);
void insert_stress_end_ptk(wchar_t *valve);
void insert_stress_non_end_ptk(wchar_t *valve);
int  is_end_ptk(wchar_t *valve);
int find_index_to_insert_stress(wchar_t *valve);
void add_element(wchar_t *valve);
void print_array_of_string(int size,int len,wchar_t arrString[size][len]);
void insert_stress_for_all_element();
#include "gen_valve_with_stress.c"