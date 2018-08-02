#include <signal.h>
#include "open62541.h"

UA_Boolean running = true;

static UA_NodeId pointTypeId;
static UA_NodeId pointVariableId;
static UA_NodeId eventType;

UA_NodeId pumpTypeId = {1, UA_NODEIDTYPE_NUMERIC, {1001}};

static void signalHandler(int sig) {//ctrl-c exit
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "received ctrl-c");
    running = false;
}

/**< 1. working with data types */
static void addVariable(UA_Server* server);
static void writeVariable(UA_Server* server);
static void writeWrongVariable(UA_Server* server);

/**< 2. building a simple server */
//static void updateCurrentTime(UA_Server* server);
//static void addCurrentTimeVariable(UA_Server* server);

/**< 3. adding variables to server */
static void beforeReadTime(UA_Server* server, const UA_NodeId* sessionId, void * sessionContext,
                           const UA_NodeId* nodeid, void * nodeContext, const UA_NumericRange* range,
                           const UA_DataValue * data);
static void afterWriteTime(UA_Server* server, const UA_NodeId* sessionId, void * sessionContext,
                           const UA_NodeId* nodeId, void * nodeContext, const UA_NumericRange* range,
                           const UA_DataValue * data);
static void addValueCallbackToCurrentTimeVariable(UA_Server* server);

/**< 4. connecting a variable with a physical process */
//static UA_StatusCode readCurrentTime(UA_Server* server, const UA_NodeId* sessionId, void * sessionContext,
//                                     const UA_NodeId* nodeId, void * nodeContext, UA_Boolean sourceTimeStamp,
//                                     const UA_NumericRange* range, UA_DataValue* dataValue);
//static UA_StatusCode writeCurrentTime(UA_Server* server, const UA_NodeId* sessionId, void * sessionContext,
//                                      const UA_NodeId* nodeId, void * nodeContext, const UA_NumericRange* range,
//                                      const UA_DataValue * data);
//static void addCurrentTimeDataSourceVariable(UA_Server* server);

/**< 5. working with variable types */
//static void addVariableType2DPoint(UA_Server *server);
//static void addVariable(UA_Server *server);
//static void addVariableFail(UA_Server *server);
//static void writeVariable(UA_Server *server);

/**< 6. working with objects and objects types */
//static void manuallyDefinePump(UA_Server *server);
//static void defineObjectTypes(UA_Server *server);
//static void addPumpObjectInstance(UA_Server *server, char *name);
//static UA_StatusCode pumpTypeConstructor(UA_Server *server,
//                    const UA_NodeId *sessionId, void *sessionContext,
//                    const UA_NodeId *typeId, void *typeContext,
//                    const UA_NodeId *nodeId, void **nodeContext);
//static void addPumpTypeConstructor(UA_Server *server);

/**< 7. adding methods to objects */
//static UA_StatusCode helloWorldMethodCallback(UA_Server *server,
//                         const UA_NodeId *sessionId, void *sessionHandle,
//                         const UA_NodeId *methodId, void *methodContext,
//                         const UA_NodeId *objectId, void *objectContext,
//                         size_t inputSize, const UA_Variant *input,
//                         size_t outputSize, UA_Variant *output);
//static void addHellWorldMethod(UA_Server *server);
//static UA_StatusCode IncInt32ArrayMethodCallback(UA_Server *server,
//                            const UA_NodeId *sessionId, void *sessionContext,
//                            const UA_NodeId *methodId, void *methodContext,
//                            const UA_NodeId *objectId, void *objectContext,
//                            size_t inputSize, const UA_Variant *input,
//                            size_t outputSize, UA_Variant *output);
//static void addIncInt32ArrayMethod(UA_Server *server);

/**< 8. generating events */
//static UA_StatusCode addNewEventType(UA_Server *server);
//static UA_StatusCode setUpEvent(UA_Server *server, UA_NodeId *outId);
//static UA_StatusCode generateEventMethodCallback(UA_Server *server,
//                         const UA_NodeId *sessionId, void *sessionHandle,
//                         const UA_NodeId *methodId, void *methodContext,
//                         const UA_NodeId *objectId, void *objectContext,
//                         size_t inputSize, const UA_Variant *input,
//                         size_t outputSize, UA_Variant *output);
//static void addGenerateEventMethod(UA_Server *server);

int main(int argc, char** argv)
{
    signal(SIGINT, signalHandler); /* catch ctrl-c */
    signal(SIGTERM, signalHandler);

    /* Create a server listening on port 4840 */
    UA_ServerConfig *config = UA_ServerConfig_new_default();
    UA_Server *server = UA_Server_new(config);

//    /* Add a variable node */
/**< 3 */
    addVariable(server);
    writeVariable(server);
    writeWrongVariable(server);

/**< 4 */
//    addCurrentTimeVariable(server);
//    addValueCallbackToCurrentTimeVariable(server);
//    addCurrentTimeDataSourceVariable(server);

//    /* 1) Define the node attributes */
//    UA_VariableAttributes attr = UA_VariableAttributes_default;
//    attr.displayName = UA_LOCALIZEDTEXT("en-US", "the answer");
//    UA_Int32 myInteger = 42;
//    UA_Variant_setScalar(&attr.value, &myInteger, &UA_TYPES[UA_TYPES_INT32]);
//
//    /* 2) Define where the node shall be added with which browsename */
//    UA_NodeId newNodeId = UA_NODEID_STRING(1, "the.answer");
//    UA_NodeId parentNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);
//    UA_NodeId parentReferenceNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES);
//    UA_NodeId variableType = UA_NODEID_NULL; /* take the default variable type */
//    UA_QualifiedName browseName = UA_QUALIFIEDNAME(1, "the answer");
//
//    /* 3) Add the node */
//    UA_Server_addVariableNode(server, newNodeId, parentNodeId, parentReferenceNodeId,
//                              browseName, variableType, attr, NULL, NULL);

/**< 5 */
//    addVariableType2DPoint(server);
//    addVariable(server);
//    addVariableFail(server);
//    writeVariable(server);

/**< 6 */
//    manuallyDefinePump(server);
//    defineObjectTypes(server);
//    addPumpObjectInstance(server, "pump2");
//    addPumpObjectInstance(server, "pump3");
//    addPumpTypeConstructor(server);
//    addPumpObjectInstance(server, "pump4");
//    addPumpObjectInstance(server, "pump5");

/**< 7 */
//    addHellWorldMethod(server);
//    addIncInt32ArrayMethod(server);

/**< 8 ÓÐÎÊÌâ*/
//    addNewEventType(server);
//    addGenerateEventMethod(server);

    /* Run the server loop */
    UA_StatusCode status = UA_Server_run(server, &running);
    UA_Server_delete(server);
    UA_ServerConfig_delete(config);
    return status;
}

static void addVariable(UA_Server* server)
{
    /* Define the attribute of the myInteger variable node*/
    UA_VariableAttributes attr = UA_VariableAttributes_default;
    UA_Int32 myInteger = 42;
    UA_Variant_setScalar(&attr.value, &myInteger, &UA_TYPES[UA_TYPES_INT32]);
    attr.description = UA_LOCALIZEDTEXT("en-US","the answer");
    attr.displayName = UA_LOCALIZEDTEXT("en-US","the answer");
    attr.dataType = UA_TYPES[UA_TYPES_INT32].typeId;
    attr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;
    /* Add the variable node to the information model*/
    UA_NodeId myIntegerNodeId = UA_NODEID_STRING(1, "the.answer");
    UA_QualifiedName myIntegerName = UA_QUALIFIEDNAME(1, "the answer");
    UA_NodeId parentNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);
    UA_NodeId parentReferenceNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES);
    UA_Server_addVariableNode(server, myIntegerNodeId, parentNodeId, parentReferenceNodeId, myIntegerName,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), attr, NULL, NULL);
}

static void writeVariable(UA_Server* server)
{
        UA_NodeId myIntegerNodeId = UA_NODEID_STRING(1, "the.answer");
    /* Write a different integer value*/
    UA_Int32 myInteger = 43;
    UA_Variant myVar;
    UA_Variant_init(&myVar);
    UA_Variant_setScalar(&myVar, &myInteger, &UA_TYPES[UA_TYPES_INT32]);
    UA_Server_writeValue(server, myIntegerNodeId, myVar);
    /* Set the status code of the value to an error code. The function
    *UA_Server_write provides access to the raw service. The above
    *UA_Server_writeValue is syntactic sugar for writing a specific node
    *attribute with the write service.
    */
    UA_WriteValue wv;
    UA_WriteValue_init(&wv);
    wv.nodeId = myIntegerNodeId;
    wv.attributeId = UA_ATTRIBUTEID_VALUE;
    wv.value.status = UA_STATUSCODE_BADNOTCONNECTED;
    wv.value.hasStatus = true;
    UA_Server_write(server, &wv);
    /* Reset the variable to a good statuscode with a value*/
    wv.value.hasStatus = false;
    wv.value.value = myVar;
    wv.value.hasValue = true;
    UA_Server_write(server, &wv);
}

static void writeWrongVariable(UA_Server* server)
{
    UA_NodeId myIntegerNodeId = UA_NODEID_STRING(1, "the.answer");
    /* Write a string*/
    UA_String myString = UA_STRING("test");
    UA_Variant myVar;
    UA_Variant_init(&myVar);
    UA_Variant_setScalar(&myVar, &myString, &UA_TYPES[UA_TYPES_STRING]);
    UA_StatusCode retval = UA_Server_writeValue(server, myIntegerNodeId, myVar);
    printf("Writing a string returned statuscode %s\n", UA_StatusCode_name(retval));
}

//static void updateCurrentTime(UA_Server* server)
//{
//    UA_DateTime now = UA_DateTime_now();
//    UA_Variant value;
//    UA_Variant_setScalar(&value, &now, &UA_TYPES[UA_TYPES_DATETIME]);
//    UA_NodeId currentNodeId = UA_NODEID_STRING(1, "current-time");
//    UA_Server_writeValue(server, currentNodeId, value);
//}
//
//static void addCurrentTimeVariable(UA_Server* server)
//{
//    UA_DateTime now = 0;
//    UA_VariableAttributes attr = UA_VariableAttributes_default;
//    attr.displayName = UA_LOCALIZEDTEXT("en-US", "Current time");
//    attr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;
//    UA_Variant_setScalar(&attr.value, &now, &UA_TYPES[UA_TYPES_DATETIME]);
//    UA_NodeId currentNodeId = UA_NODEID_STRING(1, "current-time");
//    UA_QualifiedName currentName = UA_QUALIFIEDNAME(1, "current-time");
//    UA_NodeId parentNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);
//    UA_NodeId parentReferenceNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES);
//    UA_NodeId variableTypeNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE);
//    UA_Server_addVariableNode(server, currentNodeId, parentNodeId, parentReferenceNodeId, currentName, variableTypeNodeId, attr, NULL, NULL);
//    updateCurrentTime(server);
//}
//
static void beforeReadTime(UA_Server* server, const UA_NodeId* sessionId, void * sessionContext,
                           const UA_NodeId* nodeid, void * nodeContext, const UA_NumericRange* range,
                           const UA_DataValue * data)
{
    UA_DateTime now = UA_DateTime_now();
    UA_Variant value;
    UA_Variant_setScalar(&value, &now, &UA_TYPES[UA_TYPES_DATETIME]);
    UA_NodeId currentNodeId = UA_NODEID_STRING(1, "current-time");
    UA_Server_writeValue(server, currentNodeId, value);
}

static void afterWriteTime(UA_Server* server, const UA_NodeId* sessionId, void * sessionContext,
                           const UA_NodeId* nodeId, void * nodeContext, const UA_NumericRange* range,
                           const UA_DataValue * data)
{
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "The variable was updated");
}

static void addValueCallbackToCurrentTimeVariable(UA_Server* server)
{
    UA_NodeId currentNodeId = UA_NODEID_STRING(1, "current-time");
    UA_ValueCallback callback ;
    callback.onRead = beforeReadTime;
    callback.onWrite = afterWriteTime;
    UA_Server_setVariableNode_valueCallback(server, currentNodeId, callback);
}

//static UA_StatusCode readCurrentTime(UA_Server* server, const UA_NodeId* sessionId, void * sessionContext,
//                                     const UA_NodeId* nodeId, void * nodeContext, UA_Boolean sourceTimeStamp,
//                                     const UA_NumericRange* range, UA_DataValue* dataValue)
//{
//    UA_DateTime now = UA_DateTime_now();
//    UA_Variant_setScalarCopy(&dataValue->value, &now,
//    &UA_TYPES[UA_TYPES_DATETIME]);
//    dataValue->hasValue = true;
//    return UA_STATUSCODE_GOOD;
//}
//
//static UA_StatusCode writeCurrentTime(UA_Server* server, const UA_NodeId* sessionId, void * sessionContext,
//                                      const UA_NodeId* nodeId, void * nodeContext, const UA_NumericRange* range,
//                                      const UA_DataValue * data)
//{
//    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Changing the system time is not implemented");
//    return UA_STATUSCODE_BADINTERNALERROR;
//}
//
//static void addCurrentTimeDataSourceVariable(UA_Server* server)
//{
//    UA_VariableAttributes attr = UA_VariableAttributes_default;
//    attr.displayName = UA_LOCALIZEDTEXT("en-US", "Current time - data source");
//    attr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;
//    UA_NodeId currentNodeId = UA_NODEID_STRING(1, "current-time-datasource");
//    UA_QualifiedName currentName = UA_QUALIFIEDNAME(1, "current-time-datasource");
//    UA_NodeId parentNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);
//    UA_NodeId parentReferenceNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES);
//    UA_NodeId variableTypeNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE);
//    UA_DataSource timeDataSource;
//    timeDataSource.read = readCurrentTime;
//    timeDataSource.write = writeCurrentTime;
//    UA_Server_addDataSourceVariableNode(server, currentNodeId, parentNodeId,
//    parentReferenceNodeId, currentName,
//    variableTypeNodeId, attr,
//    timeDataSource, NULL, NULL);
//}
//
//static void addVariableType2DPoint(UA_Server *server)
//{
//    UA_VariableTypeAttributes vtAttr = UA_VariableTypeAttributes_default;
//    vtAttr.dataType = UA_TYPES[UA_TYPES_DOUBLE].typeId;
//    vtAttr.valueRank = 1; /* array with one dimension */
//    UA_UInt32 arrayDims[1] = {2};
//    vtAttr.arrayDimensions = arrayDims;
//    vtAttr.arrayDimensionsSize = 1;
//    vtAttr.displayName = UA_LOCALIZEDTEXT("en-US", "2DPoint Type");
//    /* a matching default value is required */
//    UA_Double zero[2] = {0.0, 0.0};
//    UA_Variant_setArray(&vtAttr.value, zero, 2, &UA_TYPES[UA_TYPES_DOUBLE]);
//    UA_Server_addVariableTypeNode(server, UA_NODEID_NULL,
//    UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),
//    UA_NODEID_NUMERIC(0, UA_NS0ID_HASSUBTYPE),
//    UA_QUALIFIEDNAME(1, "2DPoint Type"), UA_NODEID_NULL, vtAttr, NULL, &pointTypeId);
//}
//
//static void addVariable(UA_Server *server)
//{
//    /* Prepare the node attributes */
//    UA_VariableAttributes vAttr = UA_VariableAttributes_default;
//    vAttr.dataType = UA_TYPES[UA_TYPES_DOUBLE].typeId;
//    vAttr.valueRank = 1; /* array with one dimension */
//    UA_UInt32 arrayDims[1] = {2};
//    vAttr.arrayDimensions = arrayDims;
//    vAttr.arrayDimensionsSize = 1;
//    vAttr.displayName = UA_LOCALIZEDTEXT("en-US", "2DPoint Variable");
//    vAttr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;
//    /* vAttr.value is left empty, the server instantiates with the default value */
//    /* Add the node */
//    UA_Server_addVariableNode(server, UA_NODEID_NULL,
//    UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
//    UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
//    UA_QUALIFIEDNAME(1, "2DPoint Type"), pointTypeId,
//    vAttr, NULL, &pointVariableId);
//}
//
//static void addVariableFail(UA_Server *server)
//{
//    /* Prepare the node attributes */
//    UA_VariableAttributes vAttr = UA_VariableAttributes_default;
//    vAttr.dataType = UA_TYPES[UA_TYPES_DOUBLE].typeId;
//    vAttr.valueRank = -1; /* a scalar. this is not allowed per the variable type */
//    vAttr.displayName = UA_LOCALIZEDTEXT("en-US", "2DPoint Variable (fail)");
//    UA_String s = UA_STRING("2dpoint?");
//    UA_Variant_setScalar(&vAttr.value, &s, &UA_TYPES[UA_TYPES_STRING]);
//
//    /* Add the node will return UA_STATUSCODE_BADTYPEMISMATCH*/
//    UA_Server_addVariableNode(server, UA_NODEID_NULL,
//                              UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
//                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
//                              UA_QUALIFIEDNAME(1, "2DPoint Type (fail)"), pointTypeId,
//                              vAttr, NULL, NULL);
//}
//
//static void writeVariable(UA_Server *server)
//{
//    UA_StatusCode retval = UA_Server_writeValueRank(server, pointVariableId, 0);
//    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND,
//                "Setting the Value Rank failed with Status Code %s",
//                UA_StatusCode_name(retval));
//}

//static void manuallyDefinePump(UA_Server *server)
//{
//    UA_NodeId pumpId; /* get the nodeid assigned by the server */
//    UA_ObjectAttributes oAttr = UA_ObjectAttributes_default;
//    oAttr.displayName = UA_LOCALIZEDTEXT("en-US", "Pump (Manual)");
//    UA_Server_addObjectNode(server, UA_NODEID_NULL,
//                            UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
//                            UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),
//                            UA_QUALIFIEDNAME(1, "Pump (Manual)"), UA_NODEID_NUMERIC(0, UA_NS0ID_BASEOBJECTTYPE),
//                            oAttr, NULL, &pumpId);
//
//    UA_VariableAttributes mnAttr = UA_VariableAttributes_default;
//    UA_String manufacturerName = UA_STRING("Pump King Ltd.");
//    UA_Variant_setScalar(&mnAttr.value, &manufacturerName, &UA_TYPES[UA_TYPES_STRING]);
//    mnAttr.displayName = UA_LOCALIZEDTEXT("en-US", "ManufacturerName");
//    UA_Server_addVariableNode(server, UA_NODEID_NULL, pumpId,
//                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
//                              UA_QUALIFIEDNAME(1, "ManufacturerName"),
//                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), mnAttr, NULL, NULL);
//
//    UA_VariableAttributes modelAttr = UA_VariableAttributes_default;
//    UA_String modelName = UA_STRING("Mega Pump 3000");
//    UA_Variant_setScalar(&modelAttr.value, &modelName, &UA_TYPES[UA_TYPES_STRING]);
//    modelAttr.displayName = UA_LOCALIZEDTEXT("en-US", "ModelName");
//    UA_Server_addVariableNode(server, UA_NODEID_NULL, pumpId,
//                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
//                              UA_QUALIFIEDNAME(1, "ModelName"),
//                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), modelAttr, NULL, NULL);
//
//    UA_VariableAttributes statusAttr = UA_VariableAttributes_default;
//    UA_Boolean status = true;
//    UA_Variant_setScalar(&statusAttr.value, &status, &UA_TYPES[UA_TYPES_BOOLEAN]);
//    statusAttr.displayName = UA_LOCALIZEDTEXT("en-US", "Status");
//    UA_Server_addVariableNode(server, UA_NODEID_NULL, pumpId,
//                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
//                              UA_QUALIFIEDNAME(1, "Status"),
//                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), statusAttr, NULL, NULL);
//
//    UA_VariableAttributes rpmAttr = UA_VariableAttributes_default;
//    UA_Double rpm = 50.0;
//    UA_Variant_setScalar(&rpmAttr.value, &rpm, &UA_TYPES[UA_TYPES_DOUBLE]);
//    rpmAttr.displayName = UA_LOCALIZEDTEXT("en-US", "MotorRPM");
//    UA_Server_addVariableNode(server, UA_NODEID_NULL, pumpId,
//                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
//                              UA_QUALIFIEDNAME(1, "MotorRPMs"),
//                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), rpmAttr, NULL, NULL);
//}
//
//static void defineObjectTypes(UA_Server *server)
//{
//    /* Define the object type for "Device" */
//    UA_NodeId deviceTypeId; /* get the nodeid assigned by the server */
//    UA_ObjectTypeAttributes dtAttr = UA_ObjectTypeAttributes_default;
//    dtAttr.displayName = UA_LOCALIZEDTEXT("en-US", "DeviceType");
//    UA_Server_addObjectTypeNode(server, UA_NODEID_NULL,
//                                UA_NODEID_NUMERIC(0, UA_NS0ID_BASEOBJECTTYPE),
//                                UA_NODEID_NUMERIC(0, UA_NS0ID_HASSUBTYPE),
//                                UA_QUALIFIEDNAME(1, "DeviceType"), dtAttr,
//                                NULL, &deviceTypeId);
//
//    UA_VariableAttributes mnAttr = UA_VariableAttributes_default;
//    mnAttr.displayName = UA_LOCALIZEDTEXT("en-US", "ManufacturerName");
//    UA_NodeId manufacturerNameId;
//    UA_Server_addVariableNode(server, UA_NODEID_NULL, deviceTypeId,
//                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
//                              UA_QUALIFIEDNAME(1, "ManufacturerName"),
//                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), mnAttr, NULL, &manufacturerNameId);
//    /* Make the manufacturer name mandatory */
//    UA_Server_addReference(server, manufacturerNameId,
//                           UA_NODEID_NUMERIC(0, UA_NS0ID_HASMODELLINGRULE),
//                           UA_EXPANDEDNODEID_NUMERIC(0, UA_NS0ID_MODELLINGRULE_MANDATORY), true);
//
//
//    UA_VariableAttributes modelAttr = UA_VariableAttributes_default;
//    modelAttr.displayName = UA_LOCALIZEDTEXT("en-US", "ModelName");
//    UA_Server_addVariableNode(server, UA_NODEID_NULL, deviceTypeId,
//                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
//                              UA_QUALIFIEDNAME(1, "ModelName"),
//                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), modelAttr, NULL, NULL);
//
//    /* Define the object type for "Pump" */
//    UA_ObjectTypeAttributes ptAttr = UA_ObjectTypeAttributes_default;
//    ptAttr.displayName = UA_LOCALIZEDTEXT("en-US", "PumpType");
//    UA_Server_addObjectTypeNode(server, pumpTypeId,
//                                deviceTypeId, UA_NODEID_NUMERIC(0, UA_NS0ID_HASSUBTYPE),
//                                UA_QUALIFIEDNAME(1, "PumpType"), ptAttr,
//                                NULL, NULL);
//
//    UA_VariableAttributes statusAttr = UA_VariableAttributes_default;
//    statusAttr.displayName = UA_LOCALIZEDTEXT("en-US", "Status");
//    statusAttr.valueRank = -1;
//    UA_NodeId statusId;
//    UA_Server_addVariableNode(server, UA_NODEID_NULL, pumpTypeId,
//                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
//                              UA_QUALIFIEDNAME(1, "Status"),
//                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), statusAttr, NULL, &statusId);
//    /* Make the status variable mandatory */
//    UA_Server_addReference(server, statusId,
//                           UA_NODEID_NUMERIC(0, UA_NS0ID_HASMODELLINGRULE),
//                           UA_EXPANDEDNODEID_NUMERIC(0, UA_NS0ID_MODELLINGRULE_MANDATORY), true);
//
//    UA_VariableAttributes rpmAttr = UA_VariableAttributes_default;
//    rpmAttr.displayName = UA_LOCALIZEDTEXT("en-US", "MotorRPM");
//    rpmAttr.valueRank = -1;
//    UA_Server_addVariableNode(server, UA_NODEID_NULL, pumpTypeId,
//                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
//                              UA_QUALIFIEDNAME(1, "MotorRPMs"),
//                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), rpmAttr, NULL, NULL);
//}
//
//static void addPumpObjectInstance(UA_Server *server, char *name)
//{
//    UA_ObjectAttributes oAttr = UA_ObjectAttributes_default;
//    oAttr.displayName = UA_LOCALIZEDTEXT("en-US", name);
//    UA_Server_addObjectNode(server, UA_NODEID_NULL,
//                            UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
//                            UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),
//                            UA_QUALIFIEDNAME(1, name),
//                            pumpTypeId, /* this refers to the object type
//                                           identifier */
//                            oAttr, NULL, NULL);
//}
//
//static UA_StatusCode pumpTypeConstructor(UA_Server *server,
//                    const UA_NodeId *sessionId, void *sessionContext,
//                    const UA_NodeId *typeId, void *typeContext,
//                    const UA_NodeId *nodeId, void **nodeContext)
//{
//    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "New pump created");
//
//    /* Find the NodeId of the status child variable */
//    UA_RelativePathElement rpe;
//    UA_RelativePathElement_init(&rpe);
//    rpe.referenceTypeId = UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT);
//    rpe.isInverse = false;
//    rpe.includeSubtypes = false;
//    rpe.targetName = UA_QUALIFIEDNAME(1, "Status");
//
//    UA_BrowsePath bp;
//    UA_BrowsePath_init(&bp);
//    bp.startingNode = *nodeId;
//    bp.relativePath.elementsSize = 1;
//    bp.relativePath.elements = &rpe;
//
//    UA_BrowsePathResult bpr =
//        UA_Server_translateBrowsePathToNodeIds(server, &bp);
//    if(bpr.statusCode != UA_STATUSCODE_GOOD ||
//       bpr.targetsSize < 1)
//        return bpr.statusCode;
//
//    /* Set the status value */
//    UA_Boolean status = true;
//    UA_Variant value;
//    UA_Variant_setScalar(&value, &status, &UA_TYPES[UA_TYPES_BOOLEAN]);
//    UA_Server_writeValue(server, bpr.targets[0].targetId.nodeId, value);
//    UA_BrowsePathResult_deleteMembers(&bpr);
//
//    /* At this point we could replace the node context .. */
//
//    return UA_STATUSCODE_GOOD;
//}
//
//static void addPumpTypeConstructor(UA_Server *server)
//{
//    UA_NodeTypeLifecycle lifecycle;
//    lifecycle.constructor = pumpTypeConstructor;
//    lifecycle.destructor = NULL;
//    UA_Server_setNodeTypeLifecycle(server, pumpTypeId, lifecycle);
//}
//

//static UA_StatusCode helloWorldMethodCallback(UA_Server *server,
//                         const UA_NodeId *sessionId, void *sessionHandle,
//                         const UA_NodeId *methodId, void *methodContext,
//                         const UA_NodeId *objectId, void *objectContext,
//                         size_t inputSize, const UA_Variant *input,
//                         size_t outputSize, UA_Variant *output)
//{
//    UA_String *inputStr = (UA_String*)input->data;
//    UA_String tmp = UA_STRING_ALLOC("Hello ");
//    if(inputStr->length > 0) {
//        tmp.data = (UA_Byte *)UA_realloc(tmp.data, tmp.length + inputStr->length);
//        memcpy(&tmp.data[tmp.length], inputStr->data, inputStr->length);
//        tmp.length += inputStr->length;
//    }
//    UA_Variant_setScalarCopy(output, &tmp, &UA_TYPES[UA_TYPES_STRING]);
//    UA_String_deleteMembers(&tmp);
//    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "Hello World was called");
//    return UA_STATUSCODE_GOOD;
//}
//
//static void addHellWorldMethod(UA_Server *server)
//{
//    UA_Argument inputArgument;
//    UA_Argument_init(&inputArgument);
//    inputArgument.description = UA_LOCALIZEDTEXT("en-US", "A String");
//    inputArgument.name = UA_STRING("MyInput");
//    inputArgument.dataType = UA_TYPES[UA_TYPES_STRING].typeId;
//    inputArgument.valueRank = -1; /* scalar */
//
//    UA_Argument outputArgument;
//    UA_Argument_init(&outputArgument);
//    outputArgument.description = UA_LOCALIZEDTEXT("en-US", "A String");
//    outputArgument.name = UA_STRING("MyOutput");
//    outputArgument.dataType = UA_TYPES[UA_TYPES_STRING].typeId;
//    outputArgument.valueRank = -1; /* scalar */
//
//    UA_MethodAttributes helloAttr = UA_MethodAttributes_default;
//    helloAttr.description = UA_LOCALIZEDTEXT("en-US","Say `Hello World`");
//    helloAttr.displayName = UA_LOCALIZEDTEXT("en-US","Hello World");
//    helloAttr.executable = true;
//    helloAttr.userExecutable = true;
//    UA_Server_addMethodNode(server, UA_NODEID_NUMERIC(1,62541),
//                            UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
//                            UA_NODEID_NUMERIC(0, UA_NS0ID_HASORDEREDCOMPONENT),
//                            UA_QUALIFIEDNAME(1, "hello world"),
//                            helloAttr, &helloWorldMethodCallback,
//                            1, &inputArgument, 1, &outputArgument, NULL, NULL);
//}
//
//static UA_StatusCode IncInt32ArrayMethodCallback(UA_Server *server,
//                            const UA_NodeId *sessionId, void *sessionContext,
//                            const UA_NodeId *methodId, void *methodContext,
//                            const UA_NodeId *objectId, void *objectContext,
//                            size_t inputSize, const UA_Variant *input,
//                            size_t outputSize, UA_Variant *output)
//{
//    UA_Int32 *inputArray = (UA_Int32*)input[0].data;
//    UA_Int32 delta = *(UA_Int32*)input[1].data;
//
//    /* Copy the input array */
//    UA_StatusCode retval = UA_Variant_setArrayCopy(output, inputArray, 5,
//                                                   &UA_TYPES[UA_TYPES_INT32]);
//    if(retval != UA_STATUSCODE_GOOD)
//        return retval;
//
//    /* Increate the elements */
//    UA_Int32 *outputArray = (UA_Int32*)output->data;
//    for(size_t i = 0; i < input->arrayLength; i++)
//        outputArray[i] = inputArray[i] + delta;
//
//    return UA_STATUSCODE_GOOD;
//}
//
//static void addIncInt32ArrayMethod(UA_Server *server)
//{
//    /* Two input arguments */
//    UA_Argument inputArguments[2];
//    UA_Argument_init(&inputArguments[0]);
//    inputArguments[0].description = UA_LOCALIZEDTEXT("en-US", "int32[5] array");
//    inputArguments[0].name = UA_STRING("int32 array");
//    inputArguments[0].dataType = UA_TYPES[UA_TYPES_INT32].typeId;
//    inputArguments[0].valueRank = 1;
//    UA_UInt32 pInputDimension = 5;
//    inputArguments[0].arrayDimensionsSize = 1;
//    inputArguments[0].arrayDimensions = &pInputDimension;
//
//    UA_Argument_init(&inputArguments[1]);
//    inputArguments[1].description = UA_LOCALIZEDTEXT("en-US", "int32 delta");
//    inputArguments[1].name = UA_STRING("int32 delta");
//    inputArguments[1].dataType = UA_TYPES[UA_TYPES_INT32].typeId;
//    inputArguments[1].valueRank = -1; /* scalar */
//
//    /* One output argument */
//    UA_Argument outputArgument;
//    UA_Argument_init(&outputArgument);
//    outputArgument.description = UA_LOCALIZEDTEXT("en-US", "int32[5] array");
//    outputArgument.name = UA_STRING("each entry is incremented by the delta");
//    outputArgument.dataType = UA_TYPES[UA_TYPES_INT32].typeId;
//    outputArgument.valueRank = 1;
//    UA_UInt32 pOutputDimension = 5;
//    outputArgument.arrayDimensionsSize = 1;
//    outputArgument.arrayDimensions = &pOutputDimension;
//
//    /* Add the method node */
//    UA_MethodAttributes incAttr = UA_MethodAttributes_default;
//    incAttr.description = UA_LOCALIZEDTEXT("en-US", "IncInt32ArrayValues");
//    incAttr.displayName = UA_LOCALIZEDTEXT("en-US", "IncInt32ArrayValues");
//    incAttr.executable = true;
//    incAttr.userExecutable = true;
//    UA_Server_addMethodNode(server, UA_NODEID_STRING(1, "IncInt32ArrayValues"),
//                            UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
//                            UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
//                            UA_QUALIFIEDNAME(1, "IncInt32ArrayValues"),
//                            incAttr, &IncInt32ArrayMethodCallback,
//                            2, inputArguments, 1, &outputArgument,
//                            NULL, NULL);
//}

//static UA_StatusCode addNewEventType(UA_Server *server)
//{
//    UA_ObjectTypeAttributes attr = UA_ObjectTypeAttributes_default;
//    attr.displayName = UA_LOCALIZEDTEXT("en-US", "SimpleEventType");
//    attr.description = UA_LOCALIZEDTEXT("en-US", "The simple event type we created");
//    return UA_Server_addObjectTypeNode(server, UA_NODEID_NULL,
//                                       UA_NODEID_NUMERIC(0, UA_NS0ID_BASEEVENTTYPE),
//                                       UA_NODEID_NUMERIC(0, UA_NS0ID_HASSUBTYPE),
//                                       UA_QUALIFIEDNAME(0, "SimpleEventType"),
//                                       attr, NULL, &eventType);
//}
//
//static UA_StatusCode setUpEvent(UA_Server *server, UA_NodeId *outId)
//{
//    UA_StatusCode retval = UA_Server_createEvent(server, eventType, outId);
//    if (retval != UA_STATUSCODE_GOOD) {
//        UA_LOG_WARNING(UA_Log_Stdout, UA_LOGCATEGORY_SERVER,
//                       "createEvent failed. StatusCode %s", UA_StatusCode_name(retval));
//        return retval;
//    }
//
//    /* Set the Event Attributes */
//    UA_UInt16 eventSeverity = 100;
//    UA_Server_writeObjectProperty_scalar(server, *outId, UA_QUALIFIEDNAME(0, "Severity"),
//                                         &eventSeverity, &UA_TYPES[UA_TYPES_UINT16]);
//
//    UA_LocalizedText eventMessage = UA_LOCALIZEDTEXT("en-US", "An event has been generated.");
//    UA_Server_writeObjectProperty_scalar(server, *outId, UA_QUALIFIEDNAME(0, "Message"),
//                                         &eventMessage, &UA_TYPES[UA_TYPES_LOCALIZEDTEXT]);
//
//    return UA_STATUSCODE_GOOD;
//}
//
//static UA_StatusCode generateEventMethodCallback(UA_Server *server,
//                         const UA_NodeId *sessionId, void *sessionHandle,
//                         const UA_NodeId *methodId, void *methodContext,
//                         const UA_NodeId *objectId, void *objectContext,
//                         size_t inputSize, const UA_Variant *input,
//                         size_t outputSize, UA_Variant *output)
//{
//
//    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Creating event");
//
//    /* set up event */
//    UA_NodeId eventNodeId;
//    UA_StatusCode retval = setUpEvent(server, &eventNodeId);
//    if(retval != UA_STATUSCODE_GOOD) {
//        UA_LOG_WARNING(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND,
//                       "Creating event failed. StatusCode %s", UA_StatusCode_name(retval));
//        return retval;
//    }
//
//    retval = UA_Server_triggerEvent(server, eventNodeId,
//                                    UA_NODEID_NUMERIC(0, UA_NS0ID_SERVER),
//                                    NULL, UA_TRUE);
//    if(retval != UA_STATUSCODE_GOOD)
//        UA_LOG_WARNING(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND,
//                       "Triggering event failed. StatusCode %s", UA_StatusCode_name(retval));
//
//    return retval;
//}
//
//static void addGenerateEventMethod(UA_Server *server)
//{
//    UA_MethodAttributes generateAttr = UA_MethodAttributes_default;
//    generateAttr.description = UA_LOCALIZEDTEXT("en-US","Generate an event.");
//    generateAttr.displayName = UA_LOCALIZEDTEXT("en-US","Generate Event");
//    generateAttr.executable = true;
//    generateAttr.userExecutable = true;
//    UA_Server_addMethodNode(server, UA_NODEID_NUMERIC(1, 62541),
//                            UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
//                            UA_NODEID_NUMERIC(0, UA_NS0ID_HASORDEREDCOMPONENT),
//                            UA_QUALIFIEDNAME(1, "Generate Event"),
//                            generateAttr, &generateEventMethodCallback,
//                            0, NULL, 0, NULL, NULL, NULL);
//}

