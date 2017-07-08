#include "common.h"
#include "draw.h"
#include "hid.h"
#include "i2c.h"

#define START_X 10
#define START_Y 10

void PowerOff()
{
    i2cWriteRegister(I2C_DEV_MCU, 0x20, 1 << 0);
    while (true);
}

int main()
{
	int i;
    bool use_top = true;
	char *texto[] = {	"POC Seguridad en el proceso de arranque",
						"para sistemas embebidos cerrados",
						" ",
						"Estudiantes: David Herdoiza",
						"             Neil Garcia Vargas",
						"7/7/2017"};
	
	while(true){
		for(i=0; i<6; i++)
			DrawStringF(START_X, START_Y + (i*10), use_top, texto[i]);
        if (InputWait() & (BUTTON_B | BUTTON_START))
            break;
	}
    PowerOff();
    return 0;
}
