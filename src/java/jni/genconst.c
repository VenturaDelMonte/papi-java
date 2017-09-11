/*
 * Copyright (c) 2014 Charles University in Prague
 * Copyright (c) 2014 Vojtech Horky
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * - Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the distribution.
 * - The name of the author may not be used to endorse or promote products
 *   derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS"" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include <stdio.h>
#include <papi.h>
#include <string.h>

#define JAVA_HEADER "/*\n" \
	" * This is generated file. Do not edit.\n" \
	" * To change this file, see the jni/genconst.c script and run\n" \
	" * make afterwards.\n" \
	" */\n\n" \
	"package papi;\n" \
	"\n" \
	"public class Constants {"

#define JAVA_FOOTER "}"

#define START_GROUP(description) \
	printf("\n\t/* %s */\n", description)

#define PRINT_CONST(name) \
	printf("\tpublic static final int %s = %d;\n", #name, name);

int main() {
	printf("%s\n", JAVA_HEADER);

	PRINT_CONST(PAPI_VER_CURRENT);

	START_GROUP("Error codes");
	PRINT_CONST(PAPI_OK);
	PRINT_CONST(PAPI_EINVAL);

	START_GROUP("Mixed events");
	//PRINT_CONST(PAPI_TOT_CYC);
	//PRINT_CONST(PAPI_L1_DCM);

      	PAPI_library_init(PAPI_VER_CURRENT);
	int event_code;
	PAPI_event_info_t info;

	char* names[] = {
			"CPU_CLK_UNHALTED:THREAD_P",
			"IDQ_UOPS_NOT_DELIVERED:CORE",
			"UOPS_ISSUED",
			"UNHALTED_CORE_CYCLES",
			"RESOURCE_STALLS:ANY",
			"INT_MISC:RECOVERY_CYCLES",
			"UOPS_RETIRED:RETIRE_SLOTS",
			"CYCLE_ACTIVITY:CYCLES_LDM_PENDING",
			"UOPS_EXECUTED:CORE_CYCLES_NONE",
			"UOPS_EXECUTED:CORE:c=1",
			"UOPS_EXECUTED:CORE:c=2",
			"CYCLE_ACTIVITY:STALLS_L1D_MISS",
			"CYCLE_ACTIVITY:STALLS_L2_MISS",
			"perf::L1-ICACHE-LOAD-MISSES",
			//"ICACHE_16B:IFDATA_STALL",
			"INST_RETIRED:ANY_P"
			//"CYCLE_ACTIVITY:STALLS_L1D_MISS",
			//"CYCLE_ACTIVITY:STALLS_L2_MISS",
			"CYCLE_ACTIVITY:STALLS_L3_MISS",
			"CYCLE_ACTIVITY:STALLS_MEM_ANY",
			"ICACHE_64B:IFTAG_STALL",
			"ICACHE_16B:IFDATA_STALL",
			"IDQ_UOPS_NOT_DELIVERED:CYCLES_0_UOPS_DELIV_CORE",
			"IDQ_UOPS_NOT_DELIVERED:CYCLES_LE_1_UOPS_DELIV_CORE",
			"IDQ_UOPS_NOT_DELIVERED:CYCLES_LE_2_UOPS_DELIV_CORE"
			"IDQ_UOPS_NOT_DELIVERED:CYCLES_LE_3_UOPS_DELIV_CORE",
			"IDQ_UOPS_NOT_DELIVERED:CYCLES_FE_WAS_OK"
			"UOPS_EXECUTED:CORE_CYCLES_NONE",
			"UOPS_EXECUTED:CORE_CYCLES_GE_1",
			"UOPS_EXECUTED:CORE_CYCLES_GE_2"
			"UOPS_EXECUTED:CORE_CYCLES_GE_3",
			"UOPS_EXECUTED:CORE_CYCLES_GE_4",
			"PAPI_L1_DCM",
			"PAPI_L2_DCM",
			"PAPI_L3_TCM",
			"PAPI_BR_MSP",
			"PAPI_BR_TKN",
			"PAPI_BR_NTK",
			"PAPI_MEM_WCY",
			"PAPI_STL_ICY",
			"PAPI_FUL_ICY",
			"PAPI_STL_CCY",
			"PAPI_FUL_CCY",
			"PAPI_RES_STL"
			"UOPS_ISSUED",
			"PAPI_TOT_CYC",
			"CYCLE_ACTIVITY:STALLS_TOTAL"
			"PAPI_L1_ICM",
			"PAPI_L2_ICM",
			"PAPI_TLB_IM",
			NULL
	};

	for (int i = 0; names[i] != NULL; i++) {
		if (PAPI_event_name_to_code(names[i], &event_code) == PAPI_OK ) {
			if (PAPI_get_event_info(event_code, &info) == PAPI_OK ) {
					char buffer[1024] = { 0 };

					if (strstr(names[i], ":") != NULL) {
						char tmp[256];
						strcpy(tmp, names[i]);
						char* token = strtok(tmp, ":");
						sprintf(buffer, "%s", token);
						while (1) {
							token = strtok(NULL, ":");
							if (token == NULL) {
								break;
							}
							sprintf(buffer, "%s_%s", buffer, token);
						}
					} else {
						sprintf(buffer, "%s", names[i]);
					}

					char* equal = strstr(buffer, "=");
					if (equal != NULL) {
						*equal = '_';
					}

					char* dash = strstr(buffer, "-");
					while (dash != NULL) {
						*dash = '_';
						dash = strstr(buffer, "-");
					}

					printf("\tpublic static final int %s = %d;\n", buffer, info.event_code);
					printf("\tpublic static final String %s_name = \"%s\";\n", buffer, info.symbol);
				} else {
					//fprintf(stderr, "error %s %d\n",names[i],1);
				}
			} else {
			//	fprintf(stderr, "error %s %d\n",names[i],2);
			}
	}

	printf("%s\n", JAVA_FOOTER);

	return 0;
}
