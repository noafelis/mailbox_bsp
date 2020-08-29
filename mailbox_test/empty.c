// https://github.com/Hesquibet/cc2640r2_SDK_1.50.00.08/blob/master/examples/rtos/CC2640R2_LAUNCHXL/sysbios/mailbox/mailbox.c

/* XDC module Headers */
#include <xdc/std.h>
#include <xdc/runtime/System.h>

/* BIOS module Headers */
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Mailbox.h>

/* Example/Board Header files */
#include "Board.h"

#include "shared_resources.h"

MailboxMsgObj mailboxBuffer[NUMMSGS];
Mailbox_Struct mbxStruct;
Mailbox_Handle mbxHandle;

Task_Struct task0Struct, task1Struct;
Char task0Stack[TASKSTACKSIZE], task1Stack[TASKSTACKSIZE];

Void readerTask(UArg arg0, UArg arg1);
Void writerTask(UArg arg0, UArg arg1);

/*
 *  ======== main ========
 */
int main()
{
    Task_Params taskParams;
    Mailbox_Params mbxParams;

    /* Call Driver init functions */
    Board_initGeneral();

    /* Construct read and writer tasks */
    Task_Params_init(&taskParams);
    taskParams.stackSize = TASKSTACKSIZE;
    taskParams.stack = &task0Stack;
    Task_construct(&task0Struct, (Task_FuncPtr)writerTask, &taskParams, NULL);
    taskParams.stack = &task1Stack;
    Task_construct(&task1Struct, (Task_FuncPtr)readerTask, &taskParams, NULL);

    /* Construct a Mailbox instance */
    Mailbox_Params_init(&mbxParams);
    mbxParams.buf = (Ptr)mailboxBuffer;
    mbxParams.bufSize = sizeof(mailboxBuffer);
    Mailbox_construct(&mbxStruct, sizeof(MsgObj), NUMMSGS, &mbxParams, NULL);
    mbxHandle = Mailbox_handle(&mbxStruct);

    BIOS_start();

    return(0);
}

