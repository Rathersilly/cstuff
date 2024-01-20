// CLRS ch2

// Insertion sort loop invariant:
//
// A[0..i] is sorted part of list
// A[i+1..n] is unsorted
//
// We must show 3 things about the loop invariant:
//
// Initialization
//  show invariant is true prior to the first iteration
//    ex. A[0..0] is sorted, since it is 1 element
//
// Maintenance
//  show invariant is true before each iteration
//    ex. sort moves element i to sorted part of list,
//    so invariant holds
//
// Termination
//  show invariant is true after the final iteration
//    ex. algo terminates when i == n, at which point
//    invariant holds for entire list
