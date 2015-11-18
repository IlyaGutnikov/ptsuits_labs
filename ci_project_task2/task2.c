/**********************************************************************
 * Includes
 **********************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include "altera_avalon_performance_counter.h"
#include "system.h"
#include "alt_types.h"

/**********************************************************************
 * Defines
 **********************************************************************/
#define DATA_BLOCK_SIZE_W	512
#define CYCLE_COUNT			1000

/**********************************************************************
 * Global variables
 **********************************************************************/
alt_u32 data_buffer[DATA_BLOCK_SIZE_W];

/**********************************************************************
 *
 * Function:    ones_ci()
 *
 * Description: Compute the number of ones in a data block
 *              using custom instruction implementation
 *
 * Notes:
 *
 * Returns:     Number of ones in data block
 *
 **********************************************************************/
alt_u32 ones_ci(alt_u32 *data_block, alt_u32 words)
{
    alt_32 i;
	alt_u32 result;

    result = 0;
    for (i=0; i<words; i++)
    {
        result += ALT_CI_COUNTONES(data_block[i]);
    }

    return (result);

}   /* ones_ci() */

/**********************************************************************
 *
 * Function:    ones_sw()
 *
 * Description: Compute the number of ones in a data block
 *              using standard instruction set software implementation
 * 
 * Notes:
 *
 * Returns:     Number of ones in data block
 *
 **********************************************************************/
alt_u32 ones_sw(alt_u32 *data_block, alt_u32 words)
{
    alt_32 i,j;
	alt_u32 result, val;

    result = 0;
    for (i=0; i<words; i++)
    {
    	val=data_block[i];
    	for (j=0; j<(sizeof(alt_u32)*8); j++)
    	{
    		if (val&0x01) result++;
    		val=val>>1;
    	}
    }

    return (result);

}   /* ones_sw() */

/**********************************************************************
 *
 * Function:    main()
 *
 * Notes:
 *
 * Returns:     n/a
 *
 **********************************************************************/
int main(void)
{
	alt_32 i;
	alt_u32 total_result_sw, total_result_ci;

	//Fill data buffer with some data
	for (i=0; i<DATA_BLOCK_SIZE_W; i++) data_buffer[i]=i;

	// Reset and start performance counters
	PERF_RESET (PERFORMANCE_COUNTER_0_BASE);
	PERF_START_MEASURING (PERFORMANCE_COUNTER_0_BASE);

	//Calculate ones in software
	total_result_sw=0;
	for (i=0; i<CYCLE_COUNT; i++)
	{
		PERF_BEGIN (PERFORMANCE_COUNTER_0_BASE, 1);
		//Do some stuff with result so that even if a compiler is extremely smart,
		//it does not skip computation
		total_result_sw+=ones_sw(data_buffer,DATA_BLOCK_SIZE_W);
		PERF_END (PERFORMANCE_COUNTER_0_BASE, 1);
	}

	//Calculate ones with custom instruction
	total_result_ci=0;
	for (i=0; i<CYCLE_COUNT; i++)
	{
		PERF_BEGIN (PERFORMANCE_COUNTER_0_BASE, 2);
		//Do some stuff with result so that even if a compiler is extremely smart,
		//it does not skip computation
		total_result_ci+=ones_ci(data_buffer,DATA_BLOCK_SIZE_W);
		PERF_END (PERFORMANCE_COUNTER_0_BASE, 2);
	}

	//Stop performance counters
	PERF_STOP_MEASURING (PERFORMANCE_COUNTER_0_BASE);

	//Print report
	perf_print_formatted_report(PERFORMANCE_COUNTER_0_BASE, ALT_CPU_FREQ, 2, "SW", "CI");

	//Print results
	// 1. Test output - these should be equal
	// 2. We need to use it to avoid compiler skipping all computation anyway
	printf("Number of ones via software: %u\n", (unsigned int)total_result_sw);
	printf("Number of ones via CI: %u\n", (unsigned int)total_result_ci);
	printf((total_result_sw!=total_result_ci)?"Error!\n":"OK\n");

	return 0;

}   /* main() */

