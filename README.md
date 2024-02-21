# wh_oop

A reconstruction of my disc math homework(theorem auto-proof based on Wang Hao's algorithm) using OOP. **This is my first OOP program.**

A `theorem` class is implemented, as well as it's conversion constructor, which converts from `std::string`. `operator=` is also overloaded to implement a type conversion from `std::string` to `theorem`. Copy constructor and destructor are valid.

compile: `g++ wh_oop.cpp thm.cpp -o wh_oop `