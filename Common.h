#ifndef COMMON_HEADER
#define COMMON_HEADER
#include <iostream>

template<int... ints> struct Ints{
	static void _printer(){
		_print(ints...);
	}
	static void _print(){
	}
	template<typename X, typename... Y>
	static void _print(X i,Y... is){
		std::cout << i << "\t";
		_printer(is...);
	}
};


#endif
