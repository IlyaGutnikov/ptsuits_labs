#include <stdio.h>
#include "altera_avalon_pwm_regs.h"
#include "system.h"

int main()
{ 
	int rx_char;
	char line[100];
	
  printf("Nios II PWM Lab\n");
  
  printf("\nPlease enter LED intensity between 1 to 4 (0 to exit)\n");
  
  IOWR_ALTERA_AVALON_PWM_DIVIDER(MY_PWM_BASE,99999999);
  IOWR_ALTERA_AVALON_PWM_DUTY(MY_PWM_BASE,99999999);
  
  while (1)
	{
  
	  fgets(line, sizeof(line),stdin);
	  sscanf(line,"%d",&rx_char);
	
		switch (rx_char)
		{
			case 4:
				IOWR_ALTERA_AVALON_PWM_DUTY(MY_PWM_BASE,99999999); //255
				printf("Level 4 intensity\n");
				break;
	
			case 3:
				IOWR_ALTERA_AVALON_PWM_DUTY(MY_PWM_BASE,74999999); //128
				printf("Level 3 intensity\n");
				break;
	
			case 2:
				IOWR_ALTERA_AVALON_PWM_DUTY(MY_PWM_BASE,49999999); //48
				printf("Level 2 intensity\n");
				break;
	
			case 1:
				IOWR_ALTERA_AVALON_PWM_DUTY(MY_PWM_BASE,24999999);//16
				printf("Level 1 intensity\n");
				break;
	
			case 0:
			  return 0;
				break;
	
			default:
			  printf("Please enter an integer value from 0 to 4\n");
				break;
		}
	}
  return 0;
}
