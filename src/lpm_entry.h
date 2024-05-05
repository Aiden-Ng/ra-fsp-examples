/*
 * lpm_entry.h
 *
 *  Created on: 3 May 2024
 *      Author: Ng Hong Xi
 */

#ifndef LPM_ENTRY_H_
#define LPM_ENTRY_H_

#include "Initialization.h"
#include "LPM_Module/LPM_handler.h"

void lpm_entry(void);
void lpm_operation(lpm_state_t * lpm_state_args_ptr);

#endif /* LPM_ENTRY_H_ */
