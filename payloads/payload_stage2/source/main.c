/*
*   main.c
*/

#include "types.h"
#include "memory.h"
#include "crypto.h"
#include "i2c.h"
#include "cache.h"
#include "fs.h"
#include "../build/bundled.h"

#define A11_PAYLOAD_LOC  0x1FFF4C80
#define A11_ENTRYPOINT   0x1FFFFFF8
#define PAYLOAD_ADDRESS  0x23F00000
#define MAX_PAYLOAD_SIZE 0xFFE00 

static void ownArm11(bool isScreenInit)
{
    memcpy((void *)A11_PAYLOAD_LOC, arm11_bin, arm11_bin_size);

    ((vu32 *)A11_PAYLOAD_LOC)[2] = isScreenInit ? 1 : 0;

    *(vu32 *)A11_ENTRYPOINT = 1;
    *(vu32 *)0x1FFAED80 = 0xE51FF004;
    *(vu32 *)0x1FFAED84 = A11_PAYLOAD_LOC;
    *(vu8 *)0x1FFFFFF0 = 2;
    while(*(vu32 *)A11_ENTRYPOINT != 0);
}

static void loadPayload(bool isNand)
{
    if(fileRead((void *)PAYLOAD_ADDRESS, "payload.bin", MAX_PAYLOAD_SIZE) != 0)
    {
        ownArm11(true);
        i2cWriteRegister(I2C_DEV_MCU, 0x22, 0x2A); 
        if(isNand) restoreShaHashBackup();
        flushEntireDCache();
        flushEntireICache();
        ((void (*)())PAYLOAD_ADDRESS)();
    }
}

void main(void)
{
    if(mountSd())
    {
        loadPayload(false);
        unmountSd();
    }

    //Shutdown
    flushEntireDCache();
    i2cWriteRegister(I2C_DEV_MCU, 0x20, 1 << 0);
    while(true);
}