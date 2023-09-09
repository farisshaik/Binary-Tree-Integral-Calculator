# Binary-Tree-Integral-Calculator
This is an integral calculator in C++. It takes in a string of a polynomial, performs input validation and stores it in a binary search tree. Each node of the tree is a seperate term, and stored in ascending order. The tree is then parsed through and the integrated polynomial is returned, along with the solution if the input was a definite integral. This calculator also features support for basic trigonometric functions. It is able to compute integrals of terms such as sin x, -cos x, 3 sin (30x), -4/3cos(12x) and more.

This project features extensive use of C++ templates and pointers, and features edge case considerations and input validation.

Sample input:
| sinx - cosx dx
-3|2 x^2 + x + sinx + cosx + 1 dx
| x^-7 + 7x^6 - x^-2 +5x+sin 10x- cos4x dx
| x^2 + 3x^-2 - 5x + 30cos 30x + 45 sin 45x + 15 sin 15x dx
| x^3 - cos 5x + 1 dx

Output:
-cos x - sin x + C
(1/3)x^3 + (1/2)x^2 + x - cos x + sin x, -3|2 = 9.167
x^7 + (5/2)x^2 + x^-1 - (1/6)x^-6 - (1/10)cos 10x - (1/4)sin 4x + C
(1/3)x^3 - (5/2)x^2 - 3x^-1 + sin 30x - cos 45x - cos 15x + C
(1/4)x^4 + x - (1/5)sin 5x + C

