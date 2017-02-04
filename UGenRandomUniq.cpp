//---------------------------------------------------------------------------

#pragma hdrstop

#include "UGenRandomUniq.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* ================================================================ */
bool gen_random_uniq(int arr_size, int *parr, int range_min, int range_max) {

srand( time( NULL ) );

if ( arr_size<0) {
	fprintf( stderr, "Invalid array size\n" );
	return false ;
}
int i, j;
int dup_flag;
int rand_val, range_width= range_max-range_min+1;

if ( range_width<1 || arr_size<0 || arr_size>range_width ) {
	return false;
}

for ( i= 0; i<arr_size; i++ ) {
	for ( ; ; ) {
		rand_val= range_min+rand()%range_width;
		dup_flag= 0;
		for ( j= 0; j<i; j++ ) {
			if ( rand_val == parr[j] ) { dup_flag= 1; break; }
		}
		if ( !dup_flag ) { break; }
	}
	parr[i]= rand_val;
}

return true;
} /* main() */

