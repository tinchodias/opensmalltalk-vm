/* Automatically generated by
	CCodeGeneratorGlobalStructure VMMaker.oscog-eem.779 uuid: 5ba1d239-a296-47c9-83ad-6d0e0bcabcb4
 */


/*** Function Prototypes ***/


#if defined(PRODUCTION) && !PRODUCTION && defined(__GNUC__) && !defined(NoDbgRegParms)
# define NoDbgRegParms __attribute__ ((regparm (0)))
#endif

#if !defined(NoDbgRegParms)
# define NoDbgRegParms /*empty*/
#endif

sqInt activeProcess(void);
sqInt addressCouldBeObj(sqInt address);
sqInt addressCouldBeOop(sqInt address);
usqInt argumentCountAddress(void);
sqInt argumentCountOfClosure(sqInt closurePointer);
sqInt argumentCountOfMethodHeader(sqInt header);
sqInt argumentCountOf(sqInt methodPointer);
sqInt arrayFormat(void);
void assertValidMachineCodeFrame(sqInt instrPtr);
void beRootIfOld(sqInt oop);
sqInt byteLengthOf(sqInt obj);
sqInt byteSizeOf(sqInt oop);
sqInt byteSwapped(sqInt w);
void callForCogCompiledCodeCompaction(void);
sqInt canContextSwitchIfActivatingheader(sqInt theMethod, sqInt methodHeader);
void ceActivateFailingPrimitiveMethod(sqInt aPrimitiveMethod);
sqInt ceActiveContext(void);
sqInt ceBaseFrameReturn(sqInt returnValue);
sqInt ceCannotResume(void);
void ceCheckForInterrupts(void);
void ceCheckProfileTick(void);
sqInt ceContextinstVar(sqInt maybeContext, sqInt slotIndex);
sqInt ceContextinstVarvalue(sqInt maybeMarriedContext, sqInt slotIndex, sqInt anOop);
sqInt ceInterpretMethodFromPICreceiver(sqInt aMethodObj, sqInt rcvr);
sqInt ceMNUFromPICMNUMethodreceiver(sqInt aMethodObj, sqInt rcvr);
sqInt ceNewArraySlotSize(sqInt slotSize);
sqInt ceNonLocalReturn(sqInt returnValue);
sqInt cePositive32BitIntegerFor(usqInt anInteger);
sqInt ceReturnToInterpreter(sqInt anOop);
sqInt ceSendAborttonumArgs(sqInt selector, sqInt rcvr, sqInt numArgs);
sqInt ceSendFromInLineCacheMiss(CogMethod *cogMethodOrPIC);
sqInt ceSendMustBeBoolean(sqInt anObject);
sqInt ceSendsupertonumArgs(sqInt selector, sqInt superNormalBar, sqInt rcvr, sqInt numArgs);
void ceStackOverflow(sqInt contextSwitchIfNotNil);
sqInt ceStoreCheck(sqInt anOop);
void ceTraceBlockActivation(void);
void ceTraceLinkedSend(sqInt theReceiver);
void ceTraceStoreOfinto(sqInt aValue, sqInt anObject);
sqInt characterObjectOf(sqInt characterCode);
sqInt characterTable(void);
sqInt characterValueOf(sqInt oop);
sqInt checkAllAccessibleObjectsOkay(void);
void checkAssertsEnabledInCoInterpreter(void);
sqInt checkedLongAt(sqInt byteAddress);
sqInt checkOkayInterpreterObjects(sqInt writeBack);
sqInt checkOkayOop(usqInt oop);
sqInt checkOopHasOkayClass(usqInt obj);
sqInt classArray(void);
sqInt classFloat(void);
sqInt classFloatCompactIndex(void);
sqInt classHeader(sqInt oop);
sqInt classSmallInteger(void);
void clearTraceLog(void);
CogMethod * cogMethodOf(sqInt aMethodOop);
sqInt compactClassAt(sqInt ccIndex);
sqInt compactClassIndexOfHeader(sqInt header);
sqInt compactClassIndexOf(sqInt oop);
void compilationBreakpointFor(sqInt selectorOop);
sqInt copiedValueCountOfClosure(sqInt closurePointer);
sqInt createClosureNumArgsnumCopiedstartpc(sqInt numArgs, sqInt numCopied, sqInt initialIP);
char * cStringOrNullFor(sqInt oop);
sqInt doSignalSemaphoreWithIndex(sqInt index);
void dumpPrimTraceLog(void);
void dumpTraceLog(void);
sqInt eeInstantiateClassIndexformatnumSlots(sqInt compactClassIndex, sqInt objFormat, sqInt numSlots);
sqInt eeInstantiateClassindexableSize(sqInt classPointer, sqInt size);
void executeCogMethodfromLinkedSendWithReceiver(CogMethod *cogMethod, sqInt rcvr);
void executeCogMethodfromLinkedSendWithReceiverandCacheTag(CogMethod *cogMethod, sqInt rcvr, sqInt cacheTag);
sqInt failed(void);
sqInt falseObject(void);
sqInt fetchByteofObject(sqInt byteIndex, sqInt oop);
sqInt fetchPointerofObject(sqInt fieldIndex, sqInt oop);
void findStringBeginningWith(char *aCString);
void findString(char *aCString);
sqInt firstByteFormat(void);
sqInt firstCompiledMethodFormat(void);
sqInt firstLongFormat(void);
sqInt flushExternalPrimitiveOf(sqInt methodObj);
sqInt formatOfClass(sqInt classPointer);
usqInt framePointerAddress(void);
usqInt freeStartAddress(void);
void (*functionPointerForCompiledMethodprimitiveIndex(sqInt methodObj, sqInt primIndex))(void) ;
void (*functionPointerForinClass(sqInt primIdx,sqInt theClass))(void) ;
sqInt getCheckAllocFiller(void);
usqLong getNextWakeupUsecs(void);
sqInt * getStackPointer(void);
sqInt headerIndicatesAlternateBytecodeSet(sqInt methodHeader);
sqInt headerOf(sqInt methodPointer);
sqInt highBit(usqInt anUnsignedValue);
void ifValidWriteBackStackPointersSaveTo(void *theCFP, void *theCSP, char **savedFPP, char **savedSPP);
sqInt indexablePointersFormat(void);
sqInt initialPCForHeadermethod(sqInt methodHeader, sqInt theMethod);
sqInt instanceSizeOf(sqInt classObj);
sqInt instantiateClassindexableSize(sqInt classPointer, sqInt size);
usqInt instructionPointerAddress(void);
usqInt interpretAddress(void);
sqInt isCharacterValue(sqInt anInteger);
sqInt isCogMethodReference(sqInt methodHeader);
sqInt isCompiledMethod(sqInt oop);
sqInt isImmediate(sqInt anOop);
sqInt isIntegerValue(sqInt intValue);
sqInt isMarked(sqInt oop);
sqInt isNonIntegerObject(sqInt objectPointer);
sqInt isOopCompiledMethod(sqInt oop);
sqInt isOopImmutable(sqInt anOop);
sqInt isOopMutable(sqInt anOop);
sqInt isPinned(sqInt objOop);
sqInt isQuickPrimitiveIndex(sqInt anInteger);
sqInt isReadMediatedContextInstVarIndex(sqInt index);
sqInt isReallyYoungObject(sqInt obj);
sqInt isWriteMediatedContextInstVarIndex(sqInt index);
sqInt isYoungObject(sqInt obj);
sqInt isYoung(sqInt oop);
sqInt isKindOfClass(sqInt oop, sqInt aClass);
sqInt lastPointerOf(sqInt oop);
sqInt leakCheckBecome(void);
sqInt leakCheckFullGC(void);
sqInt leakCheckIncrementalGC(void);
sqInt leakCheckNewSpaceGC(void);
sqInt lengthOf(sqInt oop);
sqInt literalCountOfHeader(sqInt headerPointer);
sqInt literalofMethod(sqInt offset, sqInt methodPointer);
void longPrintInstancesOf(sqInt aClassOop);
void longPrintOop(sqInt oop);
void longPrintReferencesTo(sqInt anOop);
sqInt longStoreBytecodeForHeader(sqInt methodHeader);
sqInt lookupreceiver(sqInt selector, sqInt rcvr);
void markActiveMethodsAndReferents(void);
sqInt markAndTrace(sqInt oop);
sqInt maxLookupNoMNUErrorCode(void);
sqInt maybeSplObj(sqInt index);
void * methodCacheAddress(void);
sqInt methodClassAssociationOf(sqInt methodPointer);
sqInt methodClassOf(sqInt methodPointer);
sqInt methodHasCogMethod(sqInt aMethodOop);
sqInt methodNeedsLargeContext(sqInt methodObj);
sqInt methodPrimitiveIndex(void);
sqInt methodShouldBeCogged(sqInt aMethodObj);
sqInt methodUsesAlternateBytecodeSet(sqInt aMethodObj);
CogMethod * mframeHomeMethod(char *theFP);
sqInt mMethodClass(void);
usqInt newMethodAddress(void);
usqInt nextProfileTickAddress(void);
sqInt nilObject(void);
sqInt noAssertHeaderOf(sqInt methodPointer);
sqInt nullHeaderForMachineCodeMethod(void);
sqInt numSlotsOf(sqInt obj);
sqInt objectAfter(sqInt oop);
sqInt objectBefore(sqInt address);
sqInt objectExactlyBefore(sqInt oop);
sqInt penultimateLiteralOf(sqInt aMethodOop);
void pinObject(sqInt objOop);
sqInt popRemappableOop(void);
sqInt popStack(void);
sqInt primErrTable(void);
usqInt primFailCodeAddress(void);
void primitiveClosureValueNoContextSwitch(void);
sqInt primitiveErrorTable(void);
sqInt primitiveFail(void);
usqInt primitiveFailAddress(void);
sqInt primitiveFailFor(sqInt reasonCode);
sqInt primitiveFailureCode(void);
usqInt primitiveFunctionPointerAddress(void);
sqInt primitiveIndexOfMethodheader(sqInt theMethod, sqInt methodHeader);
sqInt primitiveIndexOf(sqInt methodPointer);
sqInt primitivePropertyFlags(sqInt primIndex);
void * primTraceLogAddress(void);
usqInt primTraceLogIndexAddress(void);
void printAllStacks(void);
sqInt printCallStackOf(sqInt aContextOrProcessOrFrame);
void printChar(sqInt aByte);
void printCogMethod(CogMethod *cogMethod);
void printFrameWithSP(char *theFP, char *theSP);
void printHex(sqInt n);
void printInstancesOf(sqInt aClassOop);
void printLikelyImplementorsOfSelector(sqInt selector);
void printMethodCache(void);
void printMethodCacheFor(sqInt thing);
void printMethodDictionaryOf(sqInt behavior);
void printMethodDictionary(sqInt dictionary);
void printMethodReferencesTo(sqInt anOop);
void printObjectsFromto(sqInt startAddress, sqInt endAddress);
void printProcessStack(sqInt aProcess);
sqInt printProcsOnList(sqInt procList);
void printReferencesTo(sqInt anOop);
sqInt printStackCallStackOf(char *aFramePointer);
void printWronglySizedContexts(sqInt printContexts);
void print(char *s);
void pushRemappableOop(sqInt oop);
sqInt quickPrimitiveConstantFor(sqInt aQuickPrimitiveIndex);
int (*quickPrimitiveGeneratorFor(sqInt aQuickPrimitiveIndex))(void) ;
sqInt quickPrimitiveInstVarIndexFor(sqInt primIndex);
sqInt rawHeaderOf(sqInt methodPointer);
void rawHeaderOfput(sqInt methodOop, sqInt cogMethodOrMethodHeader);
sqInt remap(sqInt oop);
void reportMinimumUnusedHeadroom(void);
usqInt scavengeThresholdAddress(void);
void setBreakSelector(char *aString);
void setNextWakeupUsecs(usqLong value);
void shortPrintFrameAndNCallers(char *theFP, sqInt n);
sqInt shouldRemapObj(sqInt oop);
sqInt shouldRemapOop(sqInt oop);
sqInt signalNoResume(sqInt aSemaphore);
usqInt sizeOfAlienData(sqInt oop);
sqInt sizeOfCallPrimitiveBytecode(sqInt methodHeader);
sqInt sizeOfLongStoreTempBytecode(sqInt methodHeader);
sqInt specialSelectorNumArgs(sqInt index);
sqInt specialSelector(sqInt index);
sqInt splObj(sqInt index);
usqInt stackLimitAddress(void);
usqInt stackPointerAddress(void);
unsigned long stackPositiveMachineIntegerValue(sqInt offset);
long stackSignedMachineIntegerValue(sqInt offset);
sqInt stackTop(void);
sqInt stackValue(sqInt offset);
void * startOfAlienData(sqInt oop);
sqInt startPCOfMethodHeader(sqInt aCompiledMethodHeader);
sqInt startPCOfMethod(sqInt aCompiledMethod);
sqInt startPCOrNilOfLiteralin(sqInt lit, sqInt aMethodObj);
sqInt storePointerUncheckedofObjectwithValue(sqInt fieldIndex, sqInt oop, sqInt valuePointer);
sqInt stringForCString(const char *aCString);
sqInt tempCountOf(sqInt methodPointer);
sqInt temporaryCountOfMethodHeader(sqInt header);
void tenuringIncrementalGC(void);
sqInt topRemappableOop(void);
sqInt trueObject(void);
void updateStackZoneReferencesToCompiledCodePreCompaction(void);
sqInt weakArrayFormat(void);
char * whereIs(sqInt anOop);
sqInt withoutForwardingOnandsendToCogit(sqInt obj1, sqInt obj2, sqInt (*selector)(sqInt,sqInt));
sqInt withoutForwardingOnandwithsendToCogit(sqInt obj1, sqInt obj2, sqInt aBool, sqInt (*selector)(sqInt,sqInt,sqInt));
usqInt youngStartAddress(void);


/*** Global Variables ***/
char * breakSelector;
sqInt breakSelectorLength ;
sqInt checkAllocFiller;
sqInt checkForLeaks;
sqInt deferDisplayUpdates;
sqInt desiredCogCodeSize;
sqInt desiredEdenBytes;
sqInt desiredNumStackPages;
sqInt extraVMMemory;
usqInt heapBase;
sqInt inIOProcessEvents;
struct VirtualMachine* interpreterProxy;
sqInt maxLiteralCountForCompile ;
sqInt minBackwardJumpCountForCompile ;
volatile int sendTrace;
void * showSurfaceFn;
sqInt suppressHeartbeatFlag;


/*** Macros ***/
#define classFieldOffset() (0 - BaseHeaderSize)
#define compactClassFieldLSB() 12
#define compactClassFieldWidth() 5
#define compilationBreakpoint(sel, len) do { \
	if ((len) == breakSelectorLength \
	 && !strncmp((char *)((sel) + BaseHeaderSize), breakSelector, breakSelectorLength)) { \
		suppressHeartbeatFlag = 1; \
		compilationBreakpointFor(sel); \
	} \
} while (0)
#define instFormatFieldLSB() 8
#define instFormatFieldWidth() 4
#define isForwarded(oop) false

