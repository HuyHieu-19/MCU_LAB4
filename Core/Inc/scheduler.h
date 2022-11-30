/*
 * scheduler.h
 *
 *  Created on: Nov 26, 2022
 *      Author: Huy Hieu
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#include <stdint.h>
typedef struct {
	void ( * pTask)(void);
	uint32_t Delay;
	uint32_t Period;
	uint8_t RunMe;
	uint32_t TaskID;
} sTasks;

#define SCH_MAX_TASKS 40
#define NO_TASK_ID 0

void SCH_Init(void);
void SCH_Add_Task( void (*pFunction)(), uint32_t DELAY, uint32_t PERIOD);
//same as setTimer()
void SCH_Update(void); //same as TimerRun()
void SCH_Dispatch_Tasks(void); //same as check Flag
void SCH_Delete_Task(uint32_t TaskID);

#endif /* INC_SCHEDULER_H_ */
