#ifndef CT_INSERTION_SORT_HEADER
#define CT_INSERTION_SORT_HEADER

#include "Common.h"

template<int val, int cnt, typename T> struct __counter_helper{ };
template<int val,int cnt, int first, int... ints> struct __counter_helper<val, cnt, Ints<first, ints...> >{
	enum { count = val > first ? cnt : __counter_helper<val, cnt + 1,Ints<ints...> >::count };
};
template<int val,int cnt, int first> struct __counter_helper<val, cnt, Ints<first> >{
	enum { count = val > first ? cnt : -1 };
};
template<int val, int cnt> struct __counter_helper<val, cnt, Ints<> >{
	enum { count = 0 };
};
template<typename T, typename U,int val, int cnt> struct __insert_helper{ };
template<int... ints1, int sf, int... ints2,int val, int cnt> struct __insert_helper<Ints<ints1...>,Ints<sf, ints2...>,val , cnt>
	:public __insert_helper<Ints<ints1...,sf>,Ints<ints2...>,val, cnt - 1>{ };
template<int... ints1, int... ints2, int val> struct __insert_helper<Ints<ints1...>,Ints<ints2...>,val, 0>{
	typedef Ints<ints1...> first;
	typedef Ints<val, ints2...> second;
};
template<int... ints1, int... ints2, int val> struct __insert_helper<Ints<ints1...>,Ints<ints2...>,val, -1>{
	typedef Ints<ints1...> first;
	typedef Ints<ints2..., val> second;
};

template<typename T, typename U> struct __join_helper{ };
template<int... ints1, int...ints2> struct __join_helper<Ints<ints1...>,Ints<ints2...> >{
	typedef Ints<ints1...,ints2...> type;
};

template<typename T, int val> struct __insert{ };
template<int... ints, int val> struct __insert<Ints<ints...>, val>{
	typedef typename  __insert_helper<Ints<>, Ints<ints...>,val, __counter_helper<val,0,Ints<ints...> >::count>::first first;
	typedef typename __insert_helper<Ints<>, Ints<ints...>,val, __counter_helper<val,0,Ints<ints...> >::count>::second second;
	typedef typename __join_helper<first, second>::type type;
};

template<typename T, typename U, bool stop> struct __reverse_helper{ };
template<int... ints1, int first, int... ints2> struct __reverse_helper<Ints<ints1...>,Ints<first,ints2...>, true>
	: public __reverse_helper<Ints<first,ints1...>,Ints<ints2...>,(sizeof...(ints2) > 0)>{ };
template<int... ints1, int first, int... ints2> struct __reverse_helper<Ints<ints1...>,Ints<first,ints2...>, false>{
	typedef Ints<first, ints1...> type;
};
template<typename T> struct rev{ };
template<int first, int... ints> struct rev<Ints<first,ints...> >
	: public __reverse_helper<Ints<>,Ints<first, ints...>, sizeof...(ints)>{
};

template<typename T, typename U> struct __insertion_sort_helper{ };
template<int... ints1, int first, int... ints2> struct __insertion_sort_helper<Ints<ints1...>, Ints<first,ints2...> >
	: public __insertion_sort_helper<typename __insert<Ints<ints1...>, first>::type, Ints<ints2...> >{ };
template<int... ints1, int first> struct __insertion_sort_helper<Ints<ints1...>, Ints<first> >{
	typedef typename rev<typename __insert<Ints<ints1...>, first>::type>::type type;
};

template<typename T> struct insertion_sort{ };
template<int first, int... ints> struct insertion_sort<Ints<first,ints...> >
	: public __insertion_sort_helper<typename __insert<Ints<>, first>::type, Ints<ints...> >{ };

#endif
