#include "CT_MergeSort.h"
#include "CT_insertion_sort.h"

using namespace std;
int main(){
	typedef Ints<9,1,44,2> the_array;
	(merge_sort<the_array>::type::_printer());
	//(insertion_sort<the_array>::type::_printer());
	return 0;
}

