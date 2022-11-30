/*
 * scheduler.c
 *
 *  Created on: Nov 26, 2022
 *      Author: Huy Hieu
 */

#include "scheduler.h"

sTasks SCH_tasks_G[SCH_MAX_TASKS];
uint8_t current_index_task = 0;

void SCH_Init(void)
{
	unsigned char i;
	for(i = 0;i<SCH_MAX_TASKS;i++)
	{
		SCH_Delete_Task(i);
	}
	current_index_task = 0;
}
void SCH_Add_Task(void (* pFunction)(), uint32_t DELAY, uint32_t PERIOD)
{
	if(current_index_task < SCH_MAX_TASKS)
	{
		SCH_tasks_G[current_index_task].pTask = pFunction;
		SCH_tasks_G[current_index_task].Delay = DELAY;
		SCH_tasks_G[current_index_task].Period = PERIOD;
		SCH_tasks_G[current_index_task].RunMe = 0;

		SCH_tasks_G[current_index_task].TaskID = current_index_task;

		current_index_task++;
	}
}

void SCH_Update(void)
{
	unsigned char Index;
	for (Index = 0; Index < SCH_MAX_TASKS; Index++) {
		//kiem tra tat ca xem cai nao co task
		if (SCH_tasks_G[Index].pTask){
			if (SCH_tasks_G[Index].Delay == 0) {
				//neu delay == 0 thi thuc hien
				//runme = 1 => thuc hien
				SCH_tasks_G[Index].RunMe += 1;
				if (SCH_tasks_G[Index].Period) {
					SCH_tasks_G[Index].Delay = SCH_tasks_G[Index].Period;
					//gan delay = period
					//tuc la no dang trong qua trinh thuc hien task nay
				}
			} else {
				//neu chua ready to run => se tru Delay di 1 cho den khi nao ready
				//tuc la dang trong qua trinh execute
				SCH_tasks_G[Index].Delay -= 1;
			}
		}
	}
}

void SCH_Dispatch_Tasks(void)
{
	for(int i=0;i<current_index_task;i++)
	{
		if(SCH_tasks_G[i].RunMe > 0)
		{
			(*SCH_tasks_G[i].pTask)();
			SCH_tasks_G[i].RunMe--;
		}

		if(SCH_tasks_G[i].Period == 0)
		{
			SCH_Delete_Task(i);
		}
	}
}

void SCH_Delete_Task(uint32_t TaskID)
{
    SCH_tasks_G[TaskID].pTask = 0x0000;
    SCH_tasks_G[TaskID].Delay = 0;
    SCH_tasks_G[TaskID].Period = 0;
    SCH_tasks_G[TaskID].RunMe = 0;
}

