/* sqUnixSpurMemory.c -- dynamic memory management for Spur on unix
 * 
 * Author: eliot.miranda@gmail.com
 * 
 *   This file is part of Unix Squeak.
 * 
 *   Permission is hereby granted, free of charge, to any person obtaining a
 *   copy of this software and associated documentation files (the "Software"),
 *   to deal in the Software without restriction, including without limitation
 *   the rights to use, copy, modify, merge, publish, distribute, sublicense,
 *   and/or sell copies of the Software, and to permit persons to whom the
 *   Software is furnished to do so, subject to the following conditions:
 * 
 *   The above copyright notice and this permission notice shall be included in
 *   all copies or substantial portions of the Software.
 * 
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *   FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 *   DEALINGS IN THE SOFTWARE.
 */

#if !SPURVM
# error "this should only be used with the Spur VM, included from sqUnixMemory.c
#endif

/* Spur uses a segmented heap; it can add or remove segments, provided they are
 * above the first segment, without impacting other users of mmap.  For this to
 * work well on linux (i.e. to be able to allocate lots of memory) we need the
 * first alloc to be at as low an address as possible.
 *
 * We would like subsequent mmaps to be at ascending addresses.  But on linux
 * 2.6.x the address parameter is only observed if either there is no existing
 * overlapping mapping in the [address, address + size) range or if MAP_FIXED
 * is used.  If MAP_FIXED is not used and there is an existing mapping mmap
 * answers a mapping at a high address (not to be confused with a mapping in
 * high memory).  One approach would then be to search for the first gap in the
 * address space above the end of the last segment.  MAP_FIXED is unnecessary
 * since, given the address would be at the start of a suitable gap, mmap would
 * map at the requested address.  But how to probe for the gap?  Some have
 * advocated using mincore (2), but mincore (at least in pre 2013 kernels)
 * *only works* for non MAP_ANON mappings (file mappings).  And so one cannot
 * use it to probe for e.g. the AMP_ANON mappings made by the malloc library in
 * e.g. glibc 2.5.  Of course, mmap itself can be used.
 *
 * mmap obeys the address hint if it can.  So if mmap answers a mapping at other
 * than the hint we can infer there is an extant mapping in [hint, hint+bytes).
 * We can then free the mapping and continue the search with a hint further up.
 *
 * So we find the lowest suitable address for the initial mapping at startup
 * via sbrk, and then using the hint passed from the Spur memory manager for
 * subsequent mappings.  When there is an existing mapping we search for the
 * next available gap in e.g. 1 Mb increments.  This effectively allocates at
 * the the nearest address above that requested, something one might expect
 * mmap would do anyway.
 */

static long          pageSize = 0;
static unsigned long pageMask = 0;

#define roundDownToPage(v) ((v)&pageMask)
#define roundUpToPage(v) (((v)+pageSize-1)&pageMask)

int mmapErrno = 0;

#if !defined(HAVE_MMAP)
# error "Spur requires mmap"
#endif
#if !defined(MAP_ANON) && !defined(MAP_ANONYMOUS)
# error "Spur assumes MAP_ANON or MAP_ANONYMOUS"
# error "You're going to have to add a file descriptor."
# error "You can cpy the code in sqUnixMemory.c"
#endif

#if !defined(MAP_ANON)
# define MAP_ANON MAP_ANONYMOUS
#endif

static int min(int x, int y) { return (x < y) ? x : y; }
static int max(int x, int y) { return (x > y) ? x : y; }

/* answer the address of minHeapSize rounded up to page size bytes of memory. */

usqInt
sqAllocateMemory(usqInt minHeapSize, usqInt desiredHeapSize)
{
	char *hint, *address, *alloc;
	long bytes, allocBytes;

	if (pageSize) {
		fprintf(stderr, "sqAllocateMemory: already called\n");
		exit(1);
	}
	pageSize = getpagesize();
	pageMask = ~(pageSize - 1);

	hint = sbrk(0);

	bytes = max(pageSize,1024*1024);
	address = (char *)(((usqInt)hint + bytes - 1) & ~(bytes - 1));
	allocBytes = roundUpToPage(desiredHeapSize);

#if TEST_MEMORY
	printf("hint at %p\n", hint);
	alloc = mmap(0, allocBytes, PROT_READ | PROT_WRITE,
					 MAP_ANON | MAP_PRIVATE, -1, 0);
	printf("mmap at %p\n", alloc);
	if (alloc != MAP_FAILED)
		(void)munmap(alloc, allocBytes);
#endif

	alloc = mmap(address, allocBytes, PROT_READ | PROT_WRITE,
				 MAP_ANON | MAP_FIXED | MAP_PRIVATE, -1, 0);
	if (alloc != MAP_FAILED)
		return (usqInt)alloc;
	mmapErrno = errno;
	perror("sqAllocateMemory initial allocation mmap");
	exit(errno);
	return 0;
}

static long map_flags = MAP_ANON | MAP_PRIVATE;

/* Allocate a region of memory of at least size bytes, at or above minAddress.
 *  If the attempt fails, answer null.  If the attempt succeeds, answer the
 * start of the region and assign its size through allocatedSizePointer.
 */
void *
sqAllocateMemorySegmentOfSizeAboveAllocatedSizeInto(sqInt size, void *minAddress, sqInt *allocatedSizePointer)
{
	char *address, *alloc;
	long bytes, delta;

	address = (char *)roundUpToPage((unsigned long)minAddress);
	bytes = roundUpToPage(size);
	delta = max(pageSize,1024*1024);

	while ((unsigned long)(address + bytes) > (unsigned long)address) {
		alloc = mmap(address, bytes, PROT_READ | PROT_WRITE,
					 MAP_ANON | MAP_PRIVATE, -1, 0);
		if (alloc == MAP_FAILED) {
			mmapErrno = errno;
			perror("sqAllocateMemorySegmentOfSizeAboveAllocatedSizeInto mmap");
			return 0;
		}
		if (alloc >= address && alloc <= address + delta) {
			*allocatedSizePointer = bytes;
			return alloc;
		}
		/* mmap answered a mapping well away from where Spur prefers.  Discard
		 * the mapping and try again delta higher.
		 */
		if (munmap(alloc, bytes) != 0)
			perror("sqAllocateMemorySegment... munmap");
		address += delta;
	}
	return 0;
}

/* Deallocate a region of memory previously allocated by
 * sqAllocateMemorySegmentOfSizeAboveAllocatedSizeInto.  Cannot fail.
 */
void
sqDeallocateMemorySegmentAtOfSize(void *addr, sqInt sz)
{
	if (munmap(addr, sz) != 0)
		perror("sqDeallocateMemorySegment... munmap");
}

#if COGVM
void
sqMakeMemoryExecutableFromTo(unsigned long startAddr, unsigned long endAddr)
{
	unsigned long firstPage = roundDownToPage(startAddr);
	if (mprotect((void *)firstPage,
				 endAddr - firstPage + 1,
				 PROT_READ | PROT_WRITE | PROT_EXEC) < 0)
		perror("mprotect(x,y,PROT_READ | PROT_WRITE | PROT_EXEC)");
}

void
sqMakeMemoryNotExecutableFromTo(unsigned long startAddr, unsigned long endAddr)
{
# if 0
	unsigned long firstPage = roundDownToPage(startAddr);
	/* Arguably this is pointless since allocated memory always includes write
	 * permission by default.  Annoyingly the mprotect call fails on both linux
	 * and mac os x.  So make the whole thing a nop.
	 */
	if (mprotect((void *)firstPage,
				 endAddr - firstPage + 1,
				 PROT_READ | PROT_WRITE) < 0)
		perror("mprotect(x,y,PROT_READ | PROT_WRITE)");
# endif
}
#endif /* COGVM */

#if TEST_MEMORY

#define MBytes	*1024UL*1024UL

int main()
{
	char *mem;
	usqInt i, t = 16 MBytes;

	mem= (char *)sqAllocateMemory(t, t);
	printf("memory allocated at %p\n", mem);
	/* create some roadbumps */
	for (i = 80 MBytes; i < 2048UL MBytes; i += 80 MBytes)
		printf("roadbump created at %p\n",
				mmap(mem + i, pageSize, PROT_READ | PROT_WRITE,
					 MAP_ANON | MAP_PRIVATE, -1, 0));
	for (;;) {
		sqInt segsz = 0;
		char *seg = sqAllocateMemorySegmentOfSizeAboveAllocatedSizeInto(32 MBytes, mem + 16 MBytes, &segsz);
		if (!seg)
			return 0;
		t += segsz;
		printf("memory extended at %p (total %ld Mb)\n", seg, t / (1 MBytes));
	}
	return 0;
}
#endif /* TEST_MEMORY */
