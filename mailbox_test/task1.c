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


/*
 *  ======== readerTask ========
 */
Void readerTask(UArg arg0, UArg arg1)
{
    MsgObj msg;
    Int i;

    for (i = 0; i < NUMMSGS; i++) {

        Mailbox_pend(mbxHandle, &msg, BIOS_WAIT_FOREVER);

        System_printf("Mailbox Read: ID = %d and Value = '%c'.\n",
            msg.id, msg.val);
        System_flush();
    }

    System_printf("All messages received. Exiting...\n");

    BIOS_exit(0);
}
