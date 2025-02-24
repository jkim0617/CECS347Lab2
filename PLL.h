#define SYSDIV2 7
// bus frequency is 400MHz/(SYSDIV2+1) = 400MHz/(7+1) = 50 MHz

// configure the system to get its clock from the PLL
void PLL_Init(void);