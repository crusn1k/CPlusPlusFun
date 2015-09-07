#ifndef CT_MERGESORT_HEADER
#define CT_MERGESORT_HEADER

#include "Common.h"
template<typename X, typename Y> struct Concat{};

template<int... ints1,int... ints2> struct Concat<Ints<ints1...>,Ints<ints2...> >{
	typedef Ints<ints1..., ints2...> type;
};

template<typename ints1, typename ints2, bool done> struct BisectHelper{ };

template<int... ints1, int... ints2> struct BisectHelper<Ints<ints1...>,Ints<ints2...>,true>{
	typedef Ints<ints1...> first;
	typedef Ints<ints2...> second;
};

template<int... ints1, int i, int... ints2> struct BisectHelper<Ints<ints1...>,Ints<i,ints2...>,false>
		: public BisectHelper<Ints<ints1...,i>,Ints<ints2...>,sizeof...(ints1)+1 >= sizeof...(ints2)>{
};

template<typename T> struct Bisect{ };
template<int... ints> struct Bisect<Ints<ints...> >
		: public BisectHelper<Ints<>, Ints<ints...>, sizeof...(ints)==0>{ };

template<typename ints1, typename ints2> struct Merge{ };

template<int i, int... ints1> struct Merge<Ints<i, ints1...>, Ints<> > {
	typedef Ints<i, ints1...> type;
};

template<int i, int... ints2> struct Merge<Ints<>,Ints<i, ints2...> > {
	typedef Ints<i, ints2...> type;
};

template<typename ints1, typename ints2, bool take> struct MergeHelper{ };

template<int i, int... ints1, int j, int... ints2> struct Merge<Ints<i, ints1...>, Ints<j, ints2...> >
		: public MergeHelper<Ints<i,ints1...>,Ints<j, ints2...>, (i>j)> { };

template<int i, int... ints1, int j, int... ints2> struct MergeHelper<Ints<i, ints1...>, Ints<j, ints2...>, true>
		: public Concat<
			Ints<j>,
			typename Merge<Ints<i,ints1...>,Ints<ints2...> >::type
		>{ };
template<int i, int... ints1, int j, int... ints2> struct MergeHelper<Ints<i, ints1...>, Ints<j, ints2...>, false>
		: public Concat<
			Ints<i>,
			typename Merge<Ints<ints1...>,Ints<j, ints2...> >::type
		>{ };

template<typename ints> struct merge_sort{ };

template<> struct merge_sort<Ints<> >{
	typedef Ints<> type;
};

template<int i> struct merge_sort<Ints<i> >{
	typedef Ints<i> type;
};

template<int i, int j, int... ints> struct merge_sort<Ints<i, j, ints...> >{
private:
	typedef Bisect<Ints<i, j, ints...> > bisect;
	typedef typename bisect::first unsorted_first;
	typedef typename bisect::second unsorted_second;
	typedef typename merge_sort<unsorted_first>::type sorted_first;
	typedef typename merge_sort<unsorted_second>::type sorted_second;
public:
	typedef typename Merge<sorted_first, sorted_second>::type type;
};


template<int... ints> struct Sort : merge_sort<Ints<ints...> >{ };

#endif
