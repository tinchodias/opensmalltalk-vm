/* Automatically generated by
	SmartSyntaxPluginCodeGenerator VMMaker.oscog-eem.1601 uuid: faa527e8-769c-4c9d-b4c9-8ce48b8edbd5
   from
	GdbARMPlugin Cog-eem.309 uuid: 43ab3a22-74ae-423b-9b07-ad33de700ed4
 */
static char __buildInfo[] = "GdbARMPlugin Cog-eem.309 uuid: 43ab3a22-74ae-423b-9b07-ad33de700ed4 " __DATE__ ;



#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* Default EXPORT macro that does nothing (see comment in sq.h): */
#define EXPORT(returnType) returnType

/* Do not include the entire sq.h file but just those parts needed. */
/*  The virtual machine proxy definition */
#include "sqVirtualMachine.h"
/* Configuration options */
#include "sqConfig.h"
/* Platform specific definitions */
#include "sqPlatformSpecific.h"

#define true 1
#define false 0
#define null 0  /* using 'null' because nil is predefined in Think C */
#ifdef SQUEAK_BUILTIN_PLUGIN
#undef EXPORT
// was #undef EXPORT(returnType) but screws NorCroft cc
#define EXPORT(returnType) static returnType
#endif

#include "GdbARMPlugin.h"
#include "sqMemoryAccess.h"


/*** Constants ***/
#define PrimErrBadReceiver 2
#define PrimErrInappropriate 6
#define PrimErrNoMemory 9


/*** Function Prototypes ***/
static void forceStopOnInterrupt(void);
EXPORT(const char*) getModuleName(void);
EXPORT(sqInt) primitiveDisassembleAtInMemory(void);
EXPORT(sqInt) primitiveErrorAndLog(void);
EXPORT(sqInt) primitiveFlushICacheFromTo(void);
EXPORT(sqInt) primitiveNewCPU(void);
EXPORT(sqInt) primitiveResetCPU(void);
EXPORT(sqInt) primitiveRunInMemoryMinAddressMaxAddressReadWrite(void);
EXPORT(sqInt) primitiveRunInMemoryMinimumAddressReadWrite(void);
EXPORT(sqInt) primitiveSingleStepInMemoryMinAddressMaxAddressReadWrite(void);
EXPORT(sqInt) primitiveSingleStepInMemoryMinimumAddressReadWrite(void);
EXPORT(sqInt) setInterpreter(struct VirtualMachine*anInterpreter);
static sqInt sizeField(sqInt rcvr);
static sqInt sqAssert(sqInt aBool);
static sqInt startOfData(sqInt rcvr);


/*** Variables ***/

#if !defined(SQUEAK_BUILTIN_PLUGIN)
static void * (*arrayValueOf)(sqInt oop);
static sqInt (*byteSizeOf)(sqInt oop);
static sqInt (*classArray)(void);
static sqInt (*classString)(void);
static sqInt (*failed)(void);
static void * (*firstIndexableField)(sqInt oop);
static sqInt (*getInterruptPending)(void);
static sqInt (*instantiateClassindexableSize)(sqInt classPointer, sqInt size);
static sqInt (*integerObjectOf)(sqInt value);
static sqInt (*isWordsOrBytes)(sqInt oop);
static sqInt (*pop)(sqInt nItems);
static sqInt (*popthenPush)(sqInt nItems, sqInt oop);
static sqInt (*popRemappableOop)(void);
static sqInt (*positive32BitIntegerFor)(sqInt integerValue);
static usqInt (*positive32BitValueOf)(sqInt oop);
static usqLong (*positive64BitValueOf)(sqInt oop);
static sqInt (*primitiveFail)(void);
static sqInt (*primitiveFailFor)(sqInt reasonCode);
static sqInt (*pushRemappableOop)(sqInt oop);
static void (*(*setInterruptCheckChain)(void (*aFunction)(void)))() ;
static sqInt (*stackValue)(sqInt offset);
static sqInt (*storePointerofObjectwithValue)(sqInt index, sqInt oop, sqInt valuePointer);
static sqInt (*success)(sqInt aBoolean);
#else /* !defined(SQUEAK_BUILTIN_PLUGIN) */
extern void * arrayValueOf(sqInt oop);
extern sqInt byteSizeOf(sqInt oop);
extern sqInt classArray(void);
extern sqInt classString(void);
extern sqInt failed(void);
extern void * firstIndexableField(sqInt oop);
extern sqInt getInterruptPending(void);
extern sqInt instantiateClassindexableSize(sqInt classPointer, sqInt size);
extern sqInt integerObjectOf(sqInt value);
extern sqInt isWordsOrBytes(sqInt oop);
extern sqInt pop(sqInt nItems);
extern sqInt popthenPush(sqInt nItems, sqInt oop);
extern sqInt popRemappableOop(void);
extern sqInt positive32BitIntegerFor(sqInt integerValue);
extern usqInt positive32BitValueOf(sqInt oop);
extern usqLong positive64BitValueOf(sqInt oop);
extern sqInt primitiveFail(void);
extern sqInt primitiveFailFor(sqInt reasonCode);
extern sqInt pushRemappableOop(sqInt oop);
extern void (*setInterruptCheckChain(void (*aFunction)(void)))() ;
extern sqInt stackValue(sqInt offset);
extern sqInt storePointerofObjectwithValue(sqInt index, sqInt oop, sqInt valuePointer);
extern sqInt success(sqInt aBoolean);
extern
#endif
struct VirtualMachine* interpreterProxy;
static const char *moduleName =
#ifdef SQUEAK_BUILTIN_PLUGIN
	"GdbARMPlugin Cog-eem.309 (i)"
#else
	"GdbARMPlugin Cog-eem.309 (e)"
#endif
;


	/* GdbARMPlugin>>#forceStopOnInterrupt */
static void
forceStopOnInterrupt(void)
{
	if (getInterruptPending()) {
		forceStopRunning();
	}
}


/*	Note: This is hardcoded so it can be run from Squeak.
	The module name is used for validating a module *after*
	it is loaded to check if it does really contain the module
	we're thinking it contains. This is important! */

	/* InterpreterPlugin>>#getModuleName */
EXPORT(const char*)
getModuleName(void)
{
	return moduleName;
}


/*	cpuAlien <GdbARMAlien> */
/*	<Integer> */
/*	<Bitmap|ByteArray|WordArray> */
/*	Return an Array of the instruction length and its decompilation as a
	string for the instruction at address in memory.
 */

	/* GdbARMPlugin>>#primitiveDisassembleAt:InMemory: */
EXPORT(sqInt)
primitiveDisassembleAtInMemory(void)
{
	unsigned long address;
	void *cpu;
	sqInt cpuAlien;
	sqInt instrLenOrErr;
	sqInt log;
	sqInt logLen;
	sqInt logObj;
	sqInt logObjData;
	char *memory;
	sqInt resultObj;

	logLen = 0;
	address = (BytesPerOop == 4
		? positive32BitValueOf(stackValue(1))
		: positive64BitValueOf(stackValue(1)));
	success(isWordsOrBytes(stackValue(0)));
	memory = ((char *) (firstIndexableField(stackValue(0))));
	cpuAlien = stackValue(2);
	if (failed()) {
		return null;
	}
	if (((cpu = ((longAt(cpuAlien + BaseHeaderSize)) > 0
		? (cpuAlien + BaseHeaderSize) + BytesPerOop
		: longAt((cpuAlien + BaseHeaderSize) + BytesPerOop)))) == 0) {
		primitiveFailFor(PrimErrBadReceiver);
		return null;
	}
	instrLenOrErr = disassembleForAtInSize(cpu, address, memory, byteSizeOf(((sqInt)(long)(memory) - BaseHeaderSize)));
	if (instrLenOrErr < 0) {
		primitiveFailFor(PrimErrInappropriate);
		return null;
	}
	log = getlog((&logLen));
	resultObj = instantiateClassindexableSize(classArray(), 2);
	if (resultObj == 0) {
		primitiveFailFor(PrimErrNoMemory);
		return null;
	}
	pushRemappableOop(resultObj);
	logObj = instantiateClassindexableSize(classString(), logLen);
	if (failed()) {
		popRemappableOop();
		primitiveFailFor(PrimErrNoMemory);
		return null;
	}
	logObjData = arrayValueOf(logObj);
	memcpy(logObjData, log, logLen);
	resultObj = popRemappableOop();
	storePointerofObjectwithValue(0, resultObj, integerObjectOf(instrLenOrErr));
	storePointerofObjectwithValue(1, resultObj, logObj);
	if (failed()) {
		return null;
	}
	popthenPush(3, resultObj);
	return null;
}

	/* GdbARMPlugin>>#primitiveErrorAndLog */
EXPORT(sqInt)
primitiveErrorAndLog(void)
{
	char *log;
	sqInt logLen;
	sqInt logObj;
	char *logObjData;
	sqInt resultObj;

	logLen = 0;
	log = getlog((&logLen));
	resultObj = instantiateClassindexableSize(classArray(), 2);
	if (resultObj == 0) {
		primitiveFailFor(PrimErrNoMemory);
		return null;
	}
	storePointerofObjectwithValue(0, resultObj, integerObjectOf(errorAcorn()));
	if (logLen > 0) {
		pushRemappableOop(resultObj);
		logObj = instantiateClassindexableSize(classString(), logLen);
		if (failed()) {
			popRemappableOop();
			primitiveFailFor(PrimErrNoMemory);
			return null;
		}
		resultObj = popRemappableOop();
		logObjData = arrayValueOf(logObj);
		memcpy(logObjData, log, logLen);
		storePointerofObjectwithValue(1, resultObj, logObj);
	}
	popthenPush(1, resultObj);
	if (failed()) {
		return null;
	}
	return null;
}


/*	cpuAlien <GdbARMAlien> */
/*	<Integer> */
/*	<Integer> */
/*	Flush the icache in the requested range */

	/* GdbARMPlugin>>#primitiveFlushICacheFrom:To: */
EXPORT(sqInt)
primitiveFlushICacheFromTo(void)
{
	void *cpu;
	sqInt cpuAlien;
	unsigned long endAddress;
	unsigned long startAddress;

	startAddress = (BytesPerOop == 4
		? positive32BitValueOf(stackValue(1))
		: positive64BitValueOf(stackValue(1)));
	endAddress = (BytesPerOop == 4
		? positive32BitValueOf(stackValue(0))
		: positive64BitValueOf(stackValue(0)));
	cpuAlien = stackValue(2);
	if (failed()) {
		return null;
	}
	if (((cpu = ((longAt(cpuAlien + BaseHeaderSize)) > 0
		? (cpuAlien + BaseHeaderSize) + BytesPerOop
		: longAt((cpuAlien + BaseHeaderSize) + BytesPerOop)))) == 0) {
		primitiveFailFor(PrimErrBadReceiver);
		return null;
	}
	flushICacheFromTo(cpu, startAddress, endAddress);
	if (failed()) {
		return null;
	}
	pop(2);
	return null;
}

	/* GdbARMPlugin>>#primitiveNewCPU */
EXPORT(sqInt)
primitiveNewCPU(void)
{
	void *cpu;

	cpu = newCPU();
	if (cpu == 0) {
		primitiveFail();
		return null;
	}
	popthenPush(1, positive32BitIntegerFor(((unsigned long) cpu)));
	if (failed()) {
		return null;
	}
	return null;
}

	/* GdbARMPlugin>>#primitiveResetCPU */
EXPORT(sqInt)
primitiveResetCPU(void)
{
	void *cpu;
	sqInt cpuAlien;
	sqInt maybeErr;

	cpuAlien = stackValue(0);
	if (failed()) {
		return null;
	}
	if (((cpu = ((longAt(cpuAlien + BaseHeaderSize)) > 0
		? (cpuAlien + BaseHeaderSize) + BytesPerOop
		: longAt((cpuAlien + BaseHeaderSize) + BytesPerOop)))) == 0) {
		primitiveFailFor(PrimErrBadReceiver);
		return null;
	}
	maybeErr = resetCPU(cpu);
	if (maybeErr != 0) {
		primitiveFailFor(PrimErrInappropriate);
		return null;
	}
	if (failed()) {
		return null;
	}
	popthenPush(1, cpuAlien);
	return null;
}


/*	cpuAlien <GdbARMAlien> */
/*	<Bitmap|ByteArray|WordArray> */
/*	<Integer> */
/*	<Integer> */
/*	<Integer> */
/*	Run the cpu using the first argument as the memory and the following
	arguments defining valid addresses, running until it halts or hits an
	exception. 
 */

	/* GdbARMPlugin>>#primitiveRunInMemory:minimumAddress:maximumAddress:readOnlyBelow: */
EXPORT(sqInt)
primitiveRunInMemoryMinAddressMaxAddressReadWrite(void)
{
	void *cpu;
	sqInt cpuAlien;
	unsigned long maxAddress;
	sqInt maybeErr;
	char *memory;
	sqInt memorySize;
	unsigned long minAddress;
	unsigned long minWriteMaxExecAddress;

	success(isWordsOrBytes(stackValue(3)));
	memory = ((char *) (firstIndexableField(stackValue(3))));
	minAddress = (BytesPerOop == 4
		? positive32BitValueOf(stackValue(2))
		: positive64BitValueOf(stackValue(2)));
	maxAddress = (BytesPerOop == 4
		? positive32BitValueOf(stackValue(1))
		: positive64BitValueOf(stackValue(1)));
	minWriteMaxExecAddress = (BytesPerOop == 4
		? positive32BitValueOf(stackValue(0))
		: positive64BitValueOf(stackValue(0)));
	cpuAlien = stackValue(4);
	if (failed()) {
		return null;
	}
	if (((cpu = ((longAt(cpuAlien + BaseHeaderSize)) > 0
		? (cpuAlien + BaseHeaderSize) + BytesPerOop
		: longAt((cpuAlien + BaseHeaderSize) + BytesPerOop)))) == 0) {
		primitiveFailFor(PrimErrBadReceiver);
		return null;
	}
	prevInterruptCheckChain = setInterruptCheckChain(forceStopOnInterrupt);
	if (prevInterruptCheckChain == (forceStopOnInterrupt)) {
		prevInterruptCheckChain == 0;
	}
	memorySize = byteSizeOf(((sqInt)(long)(memory) - BaseHeaderSize));
	maybeErr = runCPUInSizeMinAddressReadWrite(cpu, memory, ((memorySize < maxAddress) ? memorySize : maxAddress), minAddress, minWriteMaxExecAddress);
	setInterruptCheckChain(prevInterruptCheckChain);
	if (maybeErr != 0) {
		primitiveFailFor(PrimErrInappropriate);
		return null;
	}
	if (failed()) {
		return null;
	}
	popthenPush(5, cpuAlien);
	return null;
}


/*	cpuAlien <GdbARMAlien> */
/*	<Bitmap|ByteArray|WordArray> */
/*	<Integer> */
/*	<Integer> */
/*	Run the cpu using the first argument as the memory and the following
	arguments defining valid addresses, running until it halts or hits an
	exception. Note that minWriteMaxExecAddress is both the minimum writeable
	address AND the maximum executable address
 */

	/* GdbARMPlugin>>#primitiveRunInMemory:minimumAddress:readOnlyBelow: */
EXPORT(sqInt)
primitiveRunInMemoryMinimumAddressReadWrite(void)
{
	void *cpu;
	sqInt cpuAlien;
	sqInt maybeErr;
	char *memory;
	unsigned long minAddress;
	unsigned long minWriteMaxExecAddress;

	success(isWordsOrBytes(stackValue(2)));
	memory = ((char *) (firstIndexableField(stackValue(2))));
	minAddress = (BytesPerOop == 4
		? positive32BitValueOf(stackValue(1))
		: positive64BitValueOf(stackValue(1)));
	minWriteMaxExecAddress = (BytesPerOop == 4
		? positive32BitValueOf(stackValue(0))
		: positive64BitValueOf(stackValue(0)));
	cpuAlien = stackValue(3);
	if (failed()) {
		return null;
	}
	if (((cpu = ((longAt(cpuAlien + BaseHeaderSize)) > 0
		? (cpuAlien + BaseHeaderSize) + BytesPerOop
		: longAt((cpuAlien + BaseHeaderSize) + BytesPerOop)))) == 0) {
		primitiveFailFor(PrimErrBadReceiver);
		return null;
	}
	prevInterruptCheckChain = setInterruptCheckChain(forceStopOnInterrupt);
	if (prevInterruptCheckChain == (forceStopOnInterrupt)) {
		prevInterruptCheckChain == 0;
	}
	maybeErr = runCPUInSizeMinAddressReadWrite(cpu, memory, byteSizeOf(((sqInt)(long)(memory) - BaseHeaderSize)), minAddress, minWriteMaxExecAddress);
	setInterruptCheckChain(prevInterruptCheckChain);
	if (maybeErr != 0) {
		primitiveFailFor(PrimErrInappropriate);
		return null;
	}
	if (failed()) {
		return null;
	}
	popthenPush(4, cpuAlien);
	return null;
}


/*	cpuAlien <GdbARMAlien> */
/*	<Bitmap|ByteArray|WordArray> */
/*	<Integer> */
/*	<Integer> */
/*	<Integer> */
/*	Single-step the cpu using the first argument as the memory and the
	following arguments defining valid addresses, running until it halts or
	hits an exception.
 */

	/* GdbARMPlugin>>#primitiveSingleStepInMemory:minimumAddress:maximumAddress:readOnlyBelow: */
EXPORT(sqInt)
primitiveSingleStepInMemoryMinAddressMaxAddressReadWrite(void)
{
	void *cpu;
	sqInt cpuAlien;
	unsigned long maxAddress;
	sqInt maybeErr;
	char *memory;
	sqInt memorySize;
	unsigned long minAddress;
	unsigned long minWriteMaxExecAddress;

	success(isWordsOrBytes(stackValue(3)));
	memory = ((char *) (firstIndexableField(stackValue(3))));
	minAddress = (BytesPerOop == 4
		? positive32BitValueOf(stackValue(2))
		: positive64BitValueOf(stackValue(2)));
	maxAddress = (BytesPerOop == 4
		? positive32BitValueOf(stackValue(1))
		: positive64BitValueOf(stackValue(1)));
	minWriteMaxExecAddress = (BytesPerOop == 4
		? positive32BitValueOf(stackValue(0))
		: positive64BitValueOf(stackValue(0)));
	cpuAlien = stackValue(4);
	if (failed()) {
		return null;
	}
	if (((cpu = ((longAt(cpuAlien + BaseHeaderSize)) > 0
		? (cpuAlien + BaseHeaderSize) + BytesPerOop
		: longAt((cpuAlien + BaseHeaderSize) + BytesPerOop)))) == 0) {
		primitiveFailFor(PrimErrBadReceiver);
		return null;
	}
	prevInterruptCheckChain = setInterruptCheckChain(forceStopOnInterrupt);
	if (prevInterruptCheckChain == (forceStopOnInterrupt)) {
		prevInterruptCheckChain == 0;
	}
	memorySize = byteSizeOf(((sqInt)(long)(memory) - BaseHeaderSize));
	maybeErr = singleStepCPUInSizeMinAddressReadWrite(cpu, memory, ((memorySize < maxAddress) ? memorySize : maxAddress), minAddress, minWriteMaxExecAddress);
	setInterruptCheckChain(prevInterruptCheckChain);
	if (maybeErr != 0) {
		primitiveFailFor(PrimErrInappropriate);
		return null;
	}
	if (failed()) {
		return null;
	}
	popthenPush(5, cpuAlien);
	return null;
}


/*	cpuAlien <GdbARMAlien> */
/*	<Bitmap|ByteArray|WordArray> */
/*	<Integer> */
/*	<Integer> */
/*	Single-step the cpu using the first argument as the memory and the
	following arguments defining valid addresses.
 */

	/* GdbARMPlugin>>#primitiveSingleStepInMemory:minimumAddress:readOnlyBelow: */
EXPORT(sqInt)
primitiveSingleStepInMemoryMinimumAddressReadWrite(void)
{
	void *cpu;
	sqInt cpuAlien;
	sqInt maybeErr;
	char *memory;
	unsigned long minAddress;
	unsigned long minWriteMaxExecAddress;

	success(isWordsOrBytes(stackValue(2)));
	memory = ((char *) (firstIndexableField(stackValue(2))));
	minAddress = (BytesPerOop == 4
		? positive32BitValueOf(stackValue(1))
		: positive64BitValueOf(stackValue(1)));
	minWriteMaxExecAddress = (BytesPerOop == 4
		? positive32BitValueOf(stackValue(0))
		: positive64BitValueOf(stackValue(0)));
	cpuAlien = stackValue(3);
	if (failed()) {
		return null;
	}
	if (((cpu = ((longAt(cpuAlien + BaseHeaderSize)) > 0
		? (cpuAlien + BaseHeaderSize) + BytesPerOop
		: longAt((cpuAlien + BaseHeaderSize) + BytesPerOop)))) == 0) {
		primitiveFailFor(PrimErrBadReceiver);
		return null;
	}
	maybeErr = singleStepCPUInSizeMinAddressReadWrite(cpu, memory, byteSizeOf(((sqInt)(long)(memory) - BaseHeaderSize)), minAddress, minWriteMaxExecAddress);
	if (maybeErr != 0) {
		primitiveFailFor(PrimErrInappropriate);
		return null;
	}
	if (failed()) {
		return null;
	}
	popthenPush(4, cpuAlien);
	return null;
}


/*	Note: This is coded so that it can be run in Squeak. */

	/* InterpreterPlugin>>#setInterpreter: */
EXPORT(sqInt)
setInterpreter(struct VirtualMachine*anInterpreter)
{
	sqInt ok;

	interpreterProxy = anInterpreter;
	ok = ((interpreterProxy->majorVersion()) == (VM_PROXY_MAJOR))
	 && ((interpreterProxy->minorVersion()) >= (VM_PROXY_MINOR));
	if (ok) {
		
#if !defined(SQUEAK_BUILTIN_PLUGIN)
		arrayValueOf = interpreterProxy->arrayValueOf;
		byteSizeOf = interpreterProxy->byteSizeOf;
		classArray = interpreterProxy->classArray;
		classString = interpreterProxy->classString;
		failed = interpreterProxy->failed;
		firstIndexableField = interpreterProxy->firstIndexableField;
		getInterruptPending = interpreterProxy->getInterruptPending;
		instantiateClassindexableSize = interpreterProxy->instantiateClassindexableSize;
		integerObjectOf = interpreterProxy->integerObjectOf;
		isWordsOrBytes = interpreterProxy->isWordsOrBytes;
		pop = interpreterProxy->pop;
		popthenPush = interpreterProxy->popthenPush;
		popRemappableOop = interpreterProxy->popRemappableOop;
		positive32BitIntegerFor = interpreterProxy->positive32BitIntegerFor;
		positive32BitValueOf = interpreterProxy->positive32BitValueOf;
		positive64BitValueOf = interpreterProxy->positive64BitValueOf;
		primitiveFail = interpreterProxy->primitiveFail;
		primitiveFailFor = interpreterProxy->primitiveFailFor;
		pushRemappableOop = interpreterProxy->pushRemappableOop;
		setInterruptCheckChain = interpreterProxy->setInterruptCheckChain;
		stackValue = interpreterProxy->stackValue;
		storePointerofObjectwithValue = interpreterProxy->storePointerofObjectwithValue;
		success = interpreterProxy->success;
#endif /* !defined(SQUEAK_BUILTIN_PLUGIN) */
	}
	return ok;
}


/*	Answer the first field of rcvr which is assumed to be an Alien of at least
	8 bytes
 */

	/* GdbARMPlugin>>#sizeField: */
static sqInt
sizeField(sqInt rcvr)
{
	return longAt(rcvr + BaseHeaderSize);
}

	/* SmartSyntaxInterpreterPlugin>>#sqAssert: */
static sqInt
sqAssert(sqInt aBool)
{
	/* missing DebugCode */;
	return aBool;
}


/*	<Alien oop> ^<Integer> */
/*	Answer the start of rcvr's data. For direct aliens this is the address of
	the second field. For indirect and pointer aliens it is what the second
	field points to. */

	/* GdbARMPlugin>>#startOfData: */
static sqInt
startOfData(sqInt rcvr)
{
	return ((longAt(rcvr + BaseHeaderSize)) > 0
		? (rcvr + BaseHeaderSize) + BytesPerOop
		: longAt((rcvr + BaseHeaderSize) + BytesPerOop));
}


#ifdef SQUEAK_BUILTIN_PLUGIN

void* GdbARMPlugin_exports[][3] = {
	{"GdbARMPlugin", "getModuleName", (void*)getModuleName},
	{"GdbARMPlugin", "primitiveDisassembleAtInMemory\000\000", (void*)primitiveDisassembleAtInMemory},
	{"GdbARMPlugin", "primitiveErrorAndLog\000\377", (void*)primitiveErrorAndLog},
	{"GdbARMPlugin", "primitiveFlushICacheFromTo\000\000", (void*)primitiveFlushICacheFromTo},
	{"GdbARMPlugin", "primitiveNewCPU\000\377", (void*)primitiveNewCPU},
	{"GdbARMPlugin", "primitiveResetCPU\000\000", (void*)primitiveResetCPU},
	{"GdbARMPlugin", "primitiveRunInMemoryMinAddressMaxAddressReadWrite\000\000", (void*)primitiveRunInMemoryMinAddressMaxAddressReadWrite},
	{"GdbARMPlugin", "primitiveRunInMemoryMinimumAddressReadWrite\000\000", (void*)primitiveRunInMemoryMinimumAddressReadWrite},
	{"GdbARMPlugin", "primitiveSingleStepInMemoryMinAddressMaxAddressReadWrite\000\000", (void*)primitiveSingleStepInMemoryMinAddressMaxAddressReadWrite},
	{"GdbARMPlugin", "primitiveSingleStepInMemoryMinimumAddressReadWrite\000\000", (void*)primitiveSingleStepInMemoryMinimumAddressReadWrite},
	{"GdbARMPlugin", "setInterpreter", (void*)setInterpreter},
	{NULL, NULL, NULL}
};

#else /* ifdef SQ_BUILTIN_PLUGIN */

signed char primitiveDisassembleAtInMemoryAccessorDepth = 0;
signed char primitiveFlushICacheFromToAccessorDepth = 0;
signed char primitiveResetCPUAccessorDepth = 0;
signed char primitiveRunInMemoryMinAddressMaxAddressReadWriteAccessorDepth = 0;
signed char primitiveRunInMemoryMinimumAddressReadWriteAccessorDepth = 0;
signed char primitiveSingleStepInMemoryMinAddressMaxAddressReadWriteAccessorDepth = 0;
signed char primitiveSingleStepInMemoryMinimumAddressReadWriteAccessorDepth = 0;

#endif /* ifdef SQ_BUILTIN_PLUGIN */
