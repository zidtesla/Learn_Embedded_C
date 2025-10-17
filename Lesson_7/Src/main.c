/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Zidane D'souza
 * @brief          : Bit SET/RESET register BSRR
 ******************************************************************************
 */

#define RCC_START_ADDR    0x40021000
#define RCC_AHBENR_OFFSET 0x14
#define RCC_AHBENR        (*((unsigned int volatile *)(RCC_START_ADDR + RCC_AHBENR_OFFSET)))
#define GPIO_B_START_ADDR 0x48000400
#define GPIO_B_MODER_OFST 0x00
#define GPIO_B_ODR_OFST   0x14
#define GPIO_B_PUPDR_OFST 0x0C
#define GPIO_B_BSRR_OFST  0x18
#define GPIO_B_MODER      (*((unsigned int volatile *)(GPIO_B_START_ADDR + GPIO_B_MODER_OFST)))
#define GPIO_B_ODR        (*((unsigned int volatile *)(GPIO_B_START_ADDR + GPIO_B_ODR_OFST)))
#define GPIO_B_PUPDR      (*((unsigned int volatile *)(GPIO_B_START_ADDR + GPIO_B_PUPDR_OFST)))
#define GPIO_B_BSRR       (*((unsigned int volatile *)(GPIO_B_START_ADDR + GPIO_B_BSRR_OFST)))

int main(void)
{
	unsigned int volatile i;
	/*enabling the peripheral clock to the AHB bus TO BLINK the LED*/
	RCC_AHBENR |= (1<<18);
	/*Set the mode of pin PB13 (User LED LD2) to output*/
	GPIO_B_MODER |= (1<<26);
	/*Toggle the LED*/
	while(1)
	{
		/*Set PB13*/
		GPIO_B_BSRR = (1<<13);
		/*delay*/
		for(i=0;i<1000000;i++)
		{
			/*wait*/
		}
		/*Toggle PB13 */
		GPIO_B_BSRR = (1<<29);
		/*delay*/
		for(i=0;i<1000000;i++)
		{
			/*wait*/
		}

	}

    return 0 ;
}
