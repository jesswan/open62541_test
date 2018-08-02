#include <stdio.h>
#include "open62541.h"

int main(int argc, char *argv[])
{
    /* Create a client and connect */
    UA_Client *client = UA_Client_new(UA_ClientConfig_default);
//    UA_StatusCode status = UA_Client_connect(client, "opc.tcp://localhost:4840");
    UA_StatusCode status = UA_Client_connect(client, "opc.tcp://222.20.75.237:4840");
    if(status != UA_STATUSCODE_GOOD) {
        UA_Client_delete(client);
        return status;
    }

    /* Read the value attribute of the node. UA_Client_readValueAttribute is a
     * wrapper for the raw read service available as UA_Client_Service_read. */
    UA_Variant value; /* Variants can hold scalar values and arrays of any type */
    UA_Variant_init(&value);

    /* NodeId of the variable holding the current time*/
//    const UA_NodeId nodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_SERVER_SERVERSTATUS_CURRENTTIME);
//    status = UA_Client_readValueAttribute(client, nodeId, &value);
    status = UA_Client_readValueAttribute(client, UA_NODEID_STRING(1, "the.answer"), &value);
    if(status == UA_STATUSCODE_GOOD && UA_Variant_hasScalarType(&value, &UA_TYPES[UA_TYPES_INT32]))
    {
//          UA_DateTime raw_date = * (UA_DateTime * ) value.data;
//          UA_DateTimeStruct dts = UA_DateTime_toStruct(raw_date);
//          UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "date is: %u-%u-%u %u: %u:%u.%03u\n",
//                        dts.day, dts.month, dts.year, dts.hour, dts.min, dts.sec, dts.milliSec);
        printf("the value of \" the.answer\" is: %i\n", *(UA_Int32*)value.data);
    }

//    /* change the value  */
//    printf("change the value:\n");
//
//    UA_Int32 myValue;
//    scanf("write a new value to (1, \"the.answer\"): %d\n", &myValue);
//
//    UA_Variant* myVar;
//    UA_Variant_init(myVar);
//    UA_Variant_setScalar(myVar, &myValue, &UA_TYPES[UA_TYPES_INT32]);
//
//    status = UA_Client_writeValueAttribute(client, UA_NODEID_STRING(1, "the.answer"), myVar);
//    if(status == UA_STATUSCODE_GOOD)
//    {
//        printf("change successfully !!!\n");
//    }
//
//    status = UA_Client_readValueAttribute(client, UA_NODEID_STRING(1, "the.answer"), &value);
//    if(status == UA_STATUSCODE_GOOD && UA_Variant_hasScalarType(&value, &UA_TYPES[UA_TYPES_INT32]))
//    {
//        printf("the new value is: %i\n", *(UA_Int32*)value.data);
//    }

    /* Clean up */
    UA_Variant_deleteMembers(&value);
    UA_Client_delete(client); /* Disconnects the client internally */
    return status;
}
