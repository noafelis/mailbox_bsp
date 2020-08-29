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
 *  ======== writerTask ========
 */
Void writerTask(UArg arg0, UArg arg1)
{
    MsgObj msg;
    Int i;

    for (i = 0; i < NUMMSGS; i++) {

        msg.id = i;
        msg.val = i + 'a';

        if (Mailbox_post(mbxHandle, &msg, BIOS_NO_WAIT)) {

            System_printf("Mailbox Write: ID = %d and Value = '%c'.\n",
                msg.id, msg.val);
            System_flush();
        }
        else {

            System_printf("Mailbox Write Failed: ID = %d and Value = '%c'.\n",
                            msg.id, msg.val);
            System_flush();
        }

        Task_sleep(500);
    }
}
