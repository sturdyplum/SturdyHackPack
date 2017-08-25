#include <algorithm> //where these algs are
#include <vector>
#include <numberics>

1sort(first_iterator, last_iterator) // To sort the given vector.

reverse(first_iterator, last_iterator) // To reverse a vector.

*max_element (first_iterator, last_iterator) // To find the maximum element of a vector.

*min_element (first_iterator, last_iterator) // To find the minimum element of a vector.

accumulate(first_iterator, last_iterator, initial value of sum) // Does the summation of vector element

count(first_iterator, last_iterator,x) // To count the occurrences of x in vector.

find(first_iterator, last_iterator, x)// Points to last address of vector ((name_of_vector).end()) if element is not present in vector.

binary_search(first_iterator, last_iterator, x) // Tests whether x exists in sorted vector or not.

lower_bound(first_iterator, last_iterator, x) // returns an iterator pointing to the first element in the range [first,last) which has a value not less than 'x'.

upper_bound(first_iterator, last_iterator, x) // returns an iterator pointing to the first element in the range [first,last) which has a value greater than 'x'.

arr.erase(position to be deleted) // This erases selected element in vector and shifts and resizes the vector elements accordingly.

arr.erase(unique(arr.begin(),arr.end()),arr.end()) // This erases the duplicate occurrences in sorted vector in a single line.

next_permutation(first_iterator, last_iterator) // This modified the vector to its next permutation.

prev_permutation(first_iterator, last_iterator) // This modified the vector to its previous permutation.

distance(first_iterator,desired_position) // It returns the distance of desired position from the first iterator.This function is very useful while finding the index.

all_of(array.begin(), array.end(), [](itn x) {return x>0;}) // this checks if all elements in an array have a certain property (greater than 0 in this case)

any_of() // same as 16 but checks if any of the array have this property

none_of() // same as 16 but checks if none have property

merge(firs_it, first.end, second_it, second.end, third_start) // merges two sorted arrays

set_union(beg1, end1, beg2, end2, beg3) 

set_intersection(beg1, end1, beg2, end2, beg3)

set_difference(beg1, end1, beg2, end2, beg3
