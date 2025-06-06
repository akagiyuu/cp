
// Basic Type
[dump] my_bool => true, my_double => 3.141592, my_int => 65
[dump] my_string => "This is a string.", my_char => 'a', LF_char => '\n'
[dump] int_ptr => *65, void_ptr => 0x7fffffffffff, nullptr => nullptr

// Container
[dump] my_vector => [
         [ 3, 5, 8, 9, 7 ],
         [ 9, 3, 2, 3, 8 ]
       ]

// Set/Map
[dump] my_set => { 'A', 'e', 'l', 'p' }
[dump] my_map => { 2: 6, 4: 6, 5: 3 }

// Multiset/Multimap
[dump] my_multiset => { 'A' (1), 'e' (1), 'l' (1), 'p' (2) }
[dump] my_multimap => {
         2 (1): [ 4 ],
         4 (2): [ 6, 7 ],
         5 (1): [ 3 ]
       }

// Tuple
[dump] my_tuple => ( 7, 4.500000, "This is a string." )
[dump] my_pair => ( 8, 'a' )

// FIFO/LIFO
[dump] my_queue => std::queue{ size()= 5, front()= 1, back()= 5 }
[dump] my_priority_queue => std::priority_queue{ size()= 5, top()= 5 }
[dump] my_stack => std::stack{ size()= 5, top()= 5 }

// Other
[dump] my_bitset => 0b 0011 1010
[dump] my_complex => 1.000000 - 1.000000i ( abs= 1.414214, arg/pi= -0.250000 )
[dump] my_optional => ?15, std::nullopt => std::nullopt
[dump] my_variant => |"This is a string."

// Combination
[dump] vector_of_pairs => [
         ( 1, "apple" ),
         ( 3, "banana" )
       ]

