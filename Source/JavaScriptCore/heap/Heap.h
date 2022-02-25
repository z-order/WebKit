/*
 *  Copyright (C) 1999-2000 Harri Porten (porten@kde.org)
 *  Copyright (C) 2001 Peter Kelly (pmk@post.com)
 *  Copyright (C) 2003-2021 Apple Inc. All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#pragma once

#include "ArrayBuffer.h"
#include "CellState.h"
#include "CollectionScope.h"
#include "CollectorPhase.h"
#include "CompleteSubspace.h"
#include "DeleteAllCodeEffort.h"
#include "GCConductor.h"
#include "GCIncomingRefCountedSet.h"
#include "GCMemoryOperations.h"
#include "GCRequest.h"
#include "HandleSet.h"
#include "HeapFinalizerCallback.h"
#include "HeapObserver.h"
#include "IsoCellSet.h"
#include "IsoHeapCellType.h"
#include "IsoInlinedHeapCellType.h"
#include "IsoSubspace.h"
#include "JSDestructibleObjectHeapCellType.h"
#include "MarkedBlock.h"
#include "MarkedSpace.h"
#include "MutatorState.h"
#include "Options.h"
#include "StructureIDTable.h"
#include "Synchronousness.h"
#include "WeakHandleOwner.h"
#include <wtf/AutomaticThread.h>
#include <wtf/ConcurrentPtrHashSet.h>
#include <wtf/Deque.h>
#include <wtf/HashCountedSet.h>
#include <wtf/HashSet.h>
#include <wtf/Lock.h>
#include <wtf/Markable.h>
#include <wtf/ParallelHelperPool.h>
#include <wtf/Threading.h>

namespace JSC {

class CodeBlock;
class CodeBlockSet;
class CollectingScope;
class ConservativeRoots;
class GCDeferralContext;
class EdenGCActivityCallback;
class FastMallocAlignedMemoryAllocator;
class FullGCActivityCallback;
class GCActivityCallback;
class GCAwareJITStubRoutine;
class GigacageAlignedMemoryAllocator;
class Heap;
class HeapProfiler;
class HeapVerifier;
class IncrementalSweeper;
class JITStubRoutine;
class JITStubRoutineSet;
class JSCell;
class JSImmutableButterfly;
class JSString;
class JSValue;
class MachineThreads;
class MarkStackArray;
class MarkStackMergingConstraint;
class MarkedJSValueRefArray;
class BlockDirectory;
class MarkedArgumentBufferBase;
class MarkingConstraint;
class MarkingConstraintSet;
class MutatorScheduler;
class RunningScope;
class SlotVisitor;
class SpaceTimeMutatorScheduler;
class StopIfNecessaryTimer;
class SweepingScope;
class VM;
class VerifierSlotVisitor;
class WeakGCHashTable;
struct CurrentThreadState;

#ifdef JSC_GLIB_API_ENABLED
class JSCGLibWrapperObject;
#endif

namespace DFG {
class SpeculativeJIT;
}

typedef HashCountedSet<JSCell*> ProtectCountSet;
typedef HashCountedSet<const char*> TypeCountSet;

enum HeapType { SmallHeap, LargeHeap };

class HeapUtil;

class Heap {
    WTF_MAKE_NONCOPYABLE(Heap);
public:
    friend class JIT;
    friend class DFG::SpeculativeJIT;
    static Heap* heap(const JSValue); // 0 for immediate values
    static Heap* heap(const HeapCell*);

    // This constant determines how many blocks we iterate between checks of our 
    // deadline when calling Heap::isPagedOut. Decreasing it will cause us to detect 
    // overstepping our deadline more quickly, while increasing it will cause 
    // our scan to run faster. 
    static constexpr unsigned s_timeCheckResolution = 16;

    bool isMarked(const void*);
    static bool testAndSetMarked(HeapVersion, const void*);
    
    static size_t cellSize(const void*);

    void writeBarrier(const JSCell* from);
    void writeBarrier(const JSCell* from, JSValue to);
    void writeBarrier(const JSCell* from, JSCell* to);

    void mutatorFence();
    
    // Take this if you know that from->cellState() < barrierThreshold.
    JS_EXPORT_PRIVATE void writeBarrierSlowPath(const JSCell* from);

    Heap(VM&, HeapType);
    ~Heap();
    void lastChanceToFinalize();
    void releaseDelayedReleasedObjects();

    VM& vm() const;

    MarkedSpace& objectSpace() { return m_objectSpace; }
    MachineThreads& machineThreads() { return *m_machineThreads; }

    SlotVisitor& collectorSlotVisitor() { return *m_collectorSlotVisitor; }

    JS_EXPORT_PRIVATE GCActivityCallback* fullActivityCallback();
    JS_EXPORT_PRIVATE GCActivityCallback* edenActivityCallback();
    JS_EXPORT_PRIVATE void setGarbageCollectionTimerEnabled(bool);

    JS_EXPORT_PRIVATE IncrementalSweeper& sweeper();

    void addObserver(HeapObserver* observer) { m_observers.append(observer); }
    void removeObserver(HeapObserver* observer) { m_observers.removeFirst(observer); }

    MutatorState mutatorState() const { return m_mutatorState; }
    std::optional<CollectionScope> collectionScope() const { return m_collectionScope; }
    bool hasHeapAccess() const;
    bool worldIsStopped() const;
    bool worldIsRunning() const { return !worldIsStopped(); }

    // We're always busy on the collection threads. On the main thread, this returns true if we're
    // helping heap.
    JS_EXPORT_PRIVATE bool currentThreadIsDoingGCWork();
    
    typedef void (*CFinalizer)(JSCell*);
    JS_EXPORT_PRIVATE void addFinalizer(JSCell*, CFinalizer);
    using LambdaFinalizer = WTF::Function<void(JSCell*)>;
    JS_EXPORT_PRIVATE void addFinalizer(JSCell*, LambdaFinalizer);

    void notifyIsSafeToCollect();
    bool isSafeToCollect() const { return m_isSafeToCollect; }
    
    bool isShuttingDown() const { return m_isShuttingDown; }

    JS_EXPORT_PRIVATE void sweepSynchronously();

    bool shouldCollectHeuristic();
    
    // Queue up a collection. Returns immediately. This will not queue a collection if a collection
    // of equal or greater strength exists. Full collections are stronger than std::nullopt collections
    // and std::nullopt collections are stronger than Eden collections. std::nullopt means that the GC can
    // choose Eden or Full. This implies that if you request a GC while that GC is ongoing, nothing
    // will happen.
    JS_EXPORT_PRIVATE void collectAsync(GCRequest = GCRequest());
    
    // Queue up a collection and wait for it to complete. This won't return until you get your own
    // complete collection. For example, if there was an ongoing asynchronous collection at the time
    // you called this, then this would wait for that one to complete and then trigger your
    // collection and then return. In weird cases, there could be multiple GC requests in the backlog
    // and this will wait for that backlog before running its GC and returning.
    JS_EXPORT_PRIVATE void collectSync(GCRequest = GCRequest());
    
    JS_EXPORT_PRIVATE void collect(Synchronousness, GCRequest = GCRequest());
    
    // Like collect(), but in the case of Async this will stopIfNecessary() and in the case of
    // Sync this will sweep synchronously.
    JS_EXPORT_PRIVATE void collectNow(Synchronousness, GCRequest = GCRequest());
    
    JS_EXPORT_PRIVATE void collectNowFullIfNotDoneRecently(Synchronousness);
    
    void collectIfNecessaryOrDefer(GCDeferralContext* = nullptr);

    void completeAllJITPlans();
    
    // Use this API to report non-GC memory referenced by GC objects. Be sure to
    // call both of these functions: Calling only one may trigger catastropic
    // memory growth.
    void reportExtraMemoryAllocated(size_t);
    JS_EXPORT_PRIVATE void reportExtraMemoryVisited(size_t);

#if ENABLE(RESOURCE_USAGE)
    // Use this API to report the subset of extra memory that lives outside this process.
    JS_EXPORT_PRIVATE void reportExternalMemoryVisited(size_t);
    size_t externalMemorySize() { return m_externalMemorySize; }
#endif

    // Use this API to report non-GC memory if you can't use the better API above.
    void deprecatedReportExtraMemory(size_t);

    JS_EXPORT_PRIVATE void reportAbandonedObjectGraph();

    JS_EXPORT_PRIVATE void protect(JSValue);
    JS_EXPORT_PRIVATE bool unprotect(JSValue); // True when the protect count drops to 0.
    
    JS_EXPORT_PRIVATE size_t extraMemorySize(); // Non-GC memory referenced by GC objects.
    JS_EXPORT_PRIVATE size_t size();
    JS_EXPORT_PRIVATE size_t capacity();
    JS_EXPORT_PRIVATE size_t objectCount();
    JS_EXPORT_PRIVATE size_t globalObjectCount();
    JS_EXPORT_PRIVATE size_t protectedObjectCount();
    JS_EXPORT_PRIVATE size_t protectedGlobalObjectCount();
    JS_EXPORT_PRIVATE std::unique_ptr<TypeCountSet> protectedObjectTypeCounts();
    JS_EXPORT_PRIVATE std::unique_ptr<TypeCountSet> objectTypeCounts();

    HashSet<MarkedArgumentBufferBase*>& markListSet();
    void addMarkedJSValueRefArray(MarkedJSValueRefArray*);
    
    template<typename Functor> void forEachProtectedCell(const Functor&);
    template<typename Functor> void forEachCodeBlock(const Functor&);
    template<typename Functor> void forEachCodeBlockIgnoringJITPlans(const AbstractLocker& codeBlockSetLocker, const Functor&);

    HandleSet* handleSet() { return &m_handleSet; }

    void willStartIterating();
    void didFinishIterating();

    Seconds lastFullGCLength() const { return m_lastFullGCLength; }
    Seconds lastEdenGCLength() const { return m_lastEdenGCLength; }
    void increaseLastFullGCLength(Seconds amount) { m_lastFullGCLength += amount; }

    size_t sizeBeforeLastEdenCollection() const { return m_sizeBeforeLastEdenCollect; }
    size_t sizeAfterLastEdenCollection() const { return m_sizeAfterLastEdenCollect; }
    size_t sizeBeforeLastFullCollection() const { return m_sizeBeforeLastFullCollect; }
    size_t sizeAfterLastFullCollection() const { return m_sizeAfterLastFullCollect; }

    void deleteAllCodeBlocks(DeleteAllCodeEffort);
    void deleteAllUnlinkedCodeBlocks(DeleteAllCodeEffort);

    void didAllocate(size_t);
    bool isPagedOut();
    
    const JITStubRoutineSet& jitStubRoutines() { return *m_jitStubRoutines; }
    
    void addReference(JSCell*, ArrayBuffer*);
    
    bool isDeferred() const { return !!m_deferralDepth; }

    StructureIDTable& structureIDTable() { return m_structureIDTable; }

    CodeBlockSet& codeBlockSet() { return *m_codeBlocks; }

#if USE(FOUNDATION)
    template<typename T> void releaseSoon(RetainPtr<T>&&);
#endif
#ifdef JSC_GLIB_API_ENABLED
    void releaseSoon(std::unique_ptr<JSCGLibWrapperObject>&&);
#endif

    JS_EXPORT_PRIVATE void registerWeakGCHashTable(WeakGCHashTable*);
    JS_EXPORT_PRIVATE void unregisterWeakGCHashTable(WeakGCHashTable*);

    void addLogicallyEmptyWeakBlock(WeakBlock*);

#if ENABLE(RESOURCE_USAGE)
    size_t blockBytesAllocated() const { return m_blockBytesAllocated; }
#endif

    void didAllocateBlock(size_t capacity);
    void didFreeBlock(size_t capacity);
    
    bool mutatorShouldBeFenced() const { return m_mutatorShouldBeFenced; }
    const bool* addressOfMutatorShouldBeFenced() const { return &m_mutatorShouldBeFenced; }
    
    unsigned barrierThreshold() const { return m_barrierThreshold; }
    const unsigned* addressOfBarrierThreshold() const { return &m_barrierThreshold; }

    // If true, the GC believes that the mutator is currently messing with the heap. We call this
    // "having heap access". The GC may block if the mutator is in this state. If false, the GC may
    // currently be doing things to the heap that make the heap unsafe to access for the mutator.
    bool hasAccess() const;
    
    // If the mutator does not currently have heap access, this function will acquire it. If the GC
    // is currently using the lack of heap access to do dangerous things to the heap then this
    // function will block, waiting for the GC to finish. It's not valid to call this if the mutator
    // already has heap access. The mutator is required to precisely track whether or not it has
    // heap access.
    //
    // It's totally fine to acquireAccess() upon VM instantiation and keep it that way. This is how
    // WebCore uses us. For most other clients, JSLock does acquireAccess()/releaseAccess() for you.
    void acquireAccess();
    
    // Releases heap access. If the GC is blocking waiting to do bad things to the heap, it will be
    // allowed to run now.
    //
    // Ordinarily, you should use the ReleaseHeapAccessScope to release and then reacquire heap
    // access. You should do this anytime you're about do perform a blocking operation, like waiting
    // on the ParkingLot.
    void releaseAccess();
    
    // This is like a super optimized way of saying:
    //
    //     releaseAccess()
    //     acquireAccess()
    //
    // The fast path is an inlined relaxed load and branch. The slow path will block the mutator if
    // the GC wants to do bad things to the heap.
    //
    // All allocations logically call this. As an optimization to improve GC progress, you can call
    // this anywhere that you can afford a load-branch and where an object allocation would have been
    // safe.
    //
    // The GC will also push a stopIfNecessary() event onto the runloop of the thread that
    // instantiated the VM whenever it wants the mutator to stop. This means that if you never block
    // but instead use the runloop to wait for events, then you could safely run in a mode where the
    // mutator has permanent heap access (like the DOM does). If you have good event handling
    // discipline (i.e. you don't block the runloop) then you can be sure that stopIfNecessary() will
    // already be called for you at the right times.
    void stopIfNecessary();
    
    // This gives the conn to the collector.
    void relinquishConn();
    
    bool mayNeedToStop();

    void performIncrement(size_t bytes);
    
    // This is a much stronger kind of stopping of the collector, and it may require waiting for a
    // while. This is meant to be a legacy API for clients of collectAllGarbage that expect that there
    // is no GC before or after that function call. After calling this, you are free to start GCs
    // yourself but you can be sure that none are running.
    //
    // This both prevents new collections from being started asynchronously and waits for any
    // outstanding collections to complete.
    void preventCollection();
    void allowCollection();
    
    uint64_t mutatorExecutionVersion() const { return m_mutatorExecutionVersion; }
    uint64_t phaseVersion() const { return m_phaseVersion; }
    
    JS_EXPORT_PRIVATE void addMarkingConstraint(std::unique_ptr<MarkingConstraint>);
    
    HeapVerifier* verifier() const { return m_verifier.get(); }
    
    void addHeapFinalizerCallback(const HeapFinalizerCallback&);
    void removeHeapFinalizerCallback(const HeapFinalizerCallback&);
    
    void runTaskInParallel(RefPtr<SharedTask<void(SlotVisitor&)>>);
    
    template<typename Func>
    void runFunctionInParallel(const Func& func)
    {
        runTaskInParallel(createSharedTask<void(SlotVisitor&)>(func));
    }

    template<typename Func>
    void forEachSlotVisitor(const Func&);
    
    Seconds totalGCTime() const { return m_totalGCTime; }

    HashMap<JSImmutableButterfly*, JSString*> immutableButterflyToStringCache;

    bool isMarkingForGCVerifier() const { return m_isMarkingForGCVerifier; }

private:
    friend class AllocatingScope;
    friend class CodeBlock;
    friend class CollectingScope;
    friend class DeferGC;
    friend class DeferGCForAWhile;
    friend class GCAwareJITStubRoutine;
    friend class GCLogging;
    friend class GCThread;
    friend class HandleSet;
    friend class HeapUtil;
    friend class HeapVerifier;
    friend class JITStubRoutine;
    friend class LLIntOffsetsExtractor;
    friend class MarkStackMergingConstraint;
    friend class MarkedSpace;
    friend class BlockDirectory;
    friend class MarkedBlock;
    friend class RunningScope;
    friend class SlotVisitor;
    friend class SpaceTimeMutatorScheduler;
    friend class StochasticSpaceTimeMutatorScheduler;
    friend class SweepingScope;
    friend class IncrementalSweeper;
    friend class VM;
    friend class VerifierSlotVisitor;
    friend class WeakSet;

    class HeapThread;
    friend class HeapThread;

    static constexpr size_t minExtraMemory = 256;
    
    class CFinalizerOwner final : public WeakHandleOwner {
        void finalize(Handle<Unknown>, void* context) final;
    };

    class LambdaFinalizerOwner final : public WeakHandleOwner {
        void finalize(Handle<Unknown>, void* context) final;
    };

    JS_EXPORT_PRIVATE void reportExtraMemoryAllocatedSlowCase(size_t);
    JS_EXPORT_PRIVATE void deprecatedReportExtraMemorySlowCase(size_t);
    
    bool shouldCollectInCollectorThread(const AbstractLocker&);
    void collectInCollectorThread();
    
    void checkConn(GCConductor);

    enum class RunCurrentPhaseResult {
        Finished,
        Continue,
        NeedCurrentThreadState
    };
    RunCurrentPhaseResult runCurrentPhase(GCConductor, CurrentThreadState*);
    
    // Returns true if we should keep doing things.
    bool runNotRunningPhase(GCConductor);
    bool runBeginPhase(GCConductor);
    bool runFixpointPhase(GCConductor);
    bool runConcurrentPhase(GCConductor);
    bool runReloopPhase(GCConductor);
    bool runEndPhase(GCConductor);
    bool changePhase(GCConductor, CollectorPhase);
    bool finishChangingPhase(GCConductor);
    
    void collectInMutatorThread();
    
    void stopThePeriphery(GCConductor);
    void resumeThePeriphery();
    
    // Returns true if the mutator is stopped, false if the mutator has the conn now.
    bool stopTheMutator();
    void resumeTheMutator();
    
    JS_EXPORT_PRIVATE void stopIfNecessarySlow();
    bool stopIfNecessarySlow(unsigned extraStateBits);
    
    template<typename Func>
    void waitForCollector(const Func&);
    
    JS_EXPORT_PRIVATE void acquireAccessSlow();
    JS_EXPORT_PRIVATE void releaseAccessSlow();
    
    bool handleNeedFinalize(unsigned);
    void handleNeedFinalize();
    
    bool relinquishConn(unsigned);
    void finishRelinquishingConn();
    
    void setNeedFinalize();
    void waitWhileNeedFinalize();
    
    void setMutatorWaiting();
    void clearMutatorWaiting();
    void notifyThreadStopping(const AbstractLocker&);
    
    typedef uint64_t Ticket;
    Ticket requestCollection(GCRequest);
    void waitForCollection(Ticket);
    
    void suspendCompilerThreads();
    void willStartCollection();
    void prepareForMarking();
    
    void gatherStackRoots(ConservativeRoots&);
    void gatherJSStackRoots(ConservativeRoots&);
    void gatherScratchBufferRoots(ConservativeRoots&);
    void beginMarking();
    void visitCompilerWorklistWeakReferences();
    void removeDeadCompilerWorklistEntries();
    void updateObjectCounts();
    void endMarking();

    void reapWeakHandles();
    void pruneStaleEntriesFromWeakGCHashTables();
    void sweepArrayBuffers();
    void snapshotUnswept();
    void deleteSourceProviderCaches();
    void notifyIncrementalSweeper();
    void harvestWeakReferences();

    template<typename CellType, typename CellSet>
    void finalizeMarkedUnconditionalFinalizers(CellSet&);

    void finalizeUnconditionalFinalizers();

    void deleteUnmarkedCompiledCode();
    JS_EXPORT_PRIVATE void addToRememberedSet(const JSCell*);
    void updateAllocationLimits();
    void didFinishCollection();
    void resumeCompilerThreads();
    void gatherExtraHeapData(HeapProfiler&);
    void removeDeadHeapSnapshotNodes(HeapProfiler&);
    void finalize();
    void sweepInFinalize();
    
    void sweepAllLogicallyEmptyWeakBlocks();
    bool sweepNextLogicallyEmptyWeakBlock();

    bool shouldDoFullCollection();

    void incrementDeferralDepth();
    void decrementDeferralDepth();
    void decrementDeferralDepthAndGCIfNeeded();
    JS_EXPORT_PRIVATE void decrementDeferralDepthAndGCIfNeededSlow();

    size_t visitCount();
    size_t bytesVisited();
    
    void forEachCodeBlockImpl(const ScopedLambda<void(CodeBlock*)>&);
    void forEachCodeBlockIgnoringJITPlansImpl(const AbstractLocker& codeBlockSetLocker, const ScopedLambda<void(CodeBlock*)>&);
    
    void setMutatorShouldBeFenced(bool value);
    
    void addCoreConstraints();

    enum class MemoryThresholdCallType {
        Cached,
        Direct
    };

    bool overCriticalMemoryThreshold(MemoryThresholdCallType memoryThresholdCallType = MemoryThresholdCallType::Cached);
    
    template<typename Visitor>
    void iterateExecutingAndCompilingCodeBlocks(Visitor&, const Function<void(CodeBlock*)>&);
    
    template<typename Func, typename Visitor>
    void iterateExecutingAndCompilingCodeBlocksWithoutHoldingLocks(Visitor&, const Func&);
    
    void assertMarkStacksEmpty();

    void setBonusVisitorTask(RefPtr<SharedTask<void(SlotVisitor&)>>);

    void dumpHeapStatisticsAtVMDestruction();

    static bool useGenerationalGC();
    static bool shouldSweepSynchronously();
    
    void verifyGC();

    const HeapType m_heapType;
    MutatorState m_mutatorState { MutatorState::Running };
    const size_t m_ramSize;
    const size_t m_minBytesPerCycle;
    size_t m_sizeAfterLastCollect { 0 };
    size_t m_sizeAfterLastFullCollect { 0 };
    size_t m_sizeBeforeLastFullCollect { 0 };
    size_t m_sizeAfterLastEdenCollect { 0 };
    size_t m_sizeBeforeLastEdenCollect { 0 };

    size_t m_bytesAllocatedThisCycle { 0 };
    size_t m_bytesAbandonedSinceLastFullCollect { 0 };
    size_t m_maxEdenSize;
    size_t m_maxEdenSizeWhenCritical;
    size_t m_maxHeapSize;
    size_t m_totalBytesVisited { 0 };
    size_t m_totalBytesVisitedThisCycle { 0 };
    double m_incrementBalance { 0 };
    
    bool m_shouldDoFullCollection { false };
    Markable<CollectionScope, EnumMarkableTraits<CollectionScope>> m_collectionScope;
    Markable<CollectionScope, EnumMarkableTraits<CollectionScope>> m_lastCollectionScope;
    Lock m_raceMarkStackLock;

    StructureIDTable m_structureIDTable;
    MarkedSpace m_objectSpace;
    GCIncomingRefCountedSet<ArrayBuffer> m_arrayBuffers;
    size_t m_extraMemorySize { 0 };
    size_t m_deprecatedExtraMemorySize { 0 };

    ProtectCountSet m_protectedValues;
    std::unique_ptr<HashSet<MarkedArgumentBufferBase*>> m_markListSet;
    SentinelLinkedList<MarkedJSValueRefArray, BasicRawSentinelNode<MarkedJSValueRefArray>> m_markedJSValueRefArrays;

    std::unique_ptr<MachineThreads> m_machineThreads;
    
    std::unique_ptr<SlotVisitor> m_collectorSlotVisitor;
    std::unique_ptr<SlotVisitor> m_mutatorSlotVisitor;
    std::unique_ptr<MarkStackArray> m_mutatorMarkStack;
    std::unique_ptr<MarkStackArray> m_raceMarkStack;
    std::unique_ptr<MarkingConstraintSet> m_constraintSet;
    std::unique_ptr<VerifierSlotVisitor> m_verifierSlotVisitor;

    // We pool the slot visitors used by parallel marking threads. It's useful to be able to
    // enumerate over them, and it's useful to have them cache some small amount of memory from
    // one GC to the next. GC marking threads claim these at the start of marking, and return
    // them at the end.
    Vector<std::unique_ptr<SlotVisitor>> m_parallelSlotVisitors;
    Vector<SlotVisitor*> m_availableParallelSlotVisitors WTF_GUARDED_BY_LOCK(m_parallelSlotVisitorLock);
    
    HandleSet m_handleSet;
    std::unique_ptr<CodeBlockSet> m_codeBlocks;
    std::unique_ptr<JITStubRoutineSet> m_jitStubRoutines;
    CFinalizerOwner m_cFinalizerOwner;
    LambdaFinalizerOwner m_lambdaFinalizerOwner;
    
    Lock m_parallelSlotVisitorLock;
    bool m_isSafeToCollect { false };
    bool m_isShuttingDown { false };
    bool m_mutatorShouldBeFenced { Options::forceFencedBarrier() };
    bool m_isMarkingForGCVerifier { false };

    unsigned m_barrierThreshold { Options::forceFencedBarrier() ? tautologicalThreshold : blackThreshold };

    Seconds m_lastFullGCLength { 10_ms };
    Seconds m_lastEdenGCLength { 10_ms };

    Vector<WeakBlock*> m_logicallyEmptyWeakBlocks;
    size_t m_indexOfNextLogicallyEmptyWeakBlockToSweep { WTF::notFound };
    
    RefPtr<FullGCActivityCallback> m_fullActivityCallback;
    RefPtr<GCActivityCallback> m_edenActivityCallback;
    Ref<IncrementalSweeper> m_sweeper;
    Ref<StopIfNecessaryTimer> m_stopIfNecessaryTimer;

    Vector<HeapObserver*> m_observers;
    
    Vector<HeapFinalizerCallback> m_heapFinalizerCallbacks;
    
    std::unique_ptr<HeapVerifier> m_verifier;

#if USE(FOUNDATION)
    Vector<RetainPtr<CFTypeRef>> m_delayedReleaseObjects;
    unsigned m_delayedReleaseRecursionCount { 0 };
#endif
#ifdef JSC_GLIB_API_ENABLED
    Vector<std::unique_ptr<JSCGLibWrapperObject>> m_delayedReleaseObjects;
    unsigned m_delayedReleaseRecursionCount { 0 };
#endif
    unsigned m_deferralDepth { 0 };

    HashSet<WeakGCHashTable*> m_weakGCHashTables;
    
    std::unique_ptr<MarkStackArray> m_sharedCollectorMarkStack;
    std::unique_ptr<MarkStackArray> m_sharedMutatorMarkStack;
    unsigned m_numberOfActiveParallelMarkers { 0 };
    unsigned m_numberOfWaitingParallelMarkers { 0 };

    ConcurrentPtrHashSet m_opaqueRoots;
    static constexpr size_t s_blockFragmentLength = 32;

    ParallelHelperClient m_helperClient;
    RefPtr<SharedTask<void(SlotVisitor&)>> m_bonusVisitorTask;

#if ENABLE(RESOURCE_USAGE)
    size_t m_blockBytesAllocated { 0 };
    size_t m_externalMemorySize { 0 };
#endif
    
    std::unique_ptr<MutatorScheduler> m_scheduler;
    
    static constexpr unsigned mutatorHasConnBit = 1u << 0u; // Must also be protected by threadLock.
    static constexpr unsigned stoppedBit = 1u << 1u; // Only set when !hasAccessBit
    static constexpr unsigned hasAccessBit = 1u << 2u;
    static constexpr unsigned needFinalizeBit = 1u << 3u;
    static constexpr unsigned mutatorWaitingBit = 1u << 4u; // Allows the mutator to use this as a condition variable.
    Atomic<unsigned> m_worldState;
    bool m_worldIsStopped { false };
    Lock m_markingMutex;
    Condition m_markingConditionVariable;

    MonotonicTime m_beforeGC;
    MonotonicTime m_afterGC;
    MonotonicTime m_stopTime;
    
    Deque<GCRequest> m_requests;
    GCRequest m_currentRequest;
    Ticket m_lastServedTicket { 0 };
    Ticket m_lastGrantedTicket { 0 };

    CollectorPhase m_lastPhase { CollectorPhase::NotRunning };
    CollectorPhase m_currentPhase { CollectorPhase::NotRunning };
    CollectorPhase m_nextPhase { CollectorPhase::NotRunning };
    bool m_collectorThreadIsRunning { false };
    bool m_threadShouldStop { false };
    bool m_mutatorDidRun { true };
    bool m_didDeferGCWork { false };
    bool m_shouldStopCollectingContinuously { false };

    uint64_t m_mutatorExecutionVersion { 0 };
    uint64_t m_phaseVersion { 0 };
    Box<Lock> m_threadLock;
    Ref<AutomaticThreadCondition> m_threadCondition; // The mutator must not wait on this. It would cause a deadlock.
    RefPtr<AutomaticThread> m_thread;

    RefPtr<Thread> m_collectContinuouslyThread { nullptr };
    
    MonotonicTime m_lastGCStartTime;
    MonotonicTime m_lastGCEndTime;
    MonotonicTime m_currentGCStartTime;
    Seconds m_totalGCTime;
    
    uintptr_t m_barriersExecuted { 0 };
    
    CurrentThreadState* m_currentThreadState { nullptr };
    Thread* m_currentThread { nullptr }; // It's OK if this becomes a dangling pointer.

#if USE(BMALLOC_MEMORY_FOOTPRINT_API)
    unsigned m_percentAvailableMemoryCachedCallCount { 0 };
    bool m_overCriticalMemoryThreshold { false };
#endif

    bool m_parallelMarkersShouldExit { false };
    Lock m_collectContinuouslyLock;
    Condition m_collectContinuouslyCondition;

public:
    // HeapCellTypes
    HeapCellType auxiliaryHeapCellType;
    HeapCellType immutableButterflyHeapCellType;
    HeapCellType cellHeapCellType;
    HeapCellType destructibleCellHeapCellType;
    IsoHeapCellType apiGlobalObjectHeapCellType;
    IsoHeapCellType callbackConstructorHeapCellType;
    IsoHeapCellType callbackGlobalObjectHeapCellType;
    IsoHeapCellType callbackObjectHeapCellType;
    IsoHeapCellType customGetterFunctionHeapCellType;
    IsoHeapCellType customSetterFunctionHeapCellType;
    IsoHeapCellType dateInstanceHeapCellType;
    IsoHeapCellType errorInstanceHeapCellType;
    IsoHeapCellType finalizationRegistryCellType;
    IsoHeapCellType globalLexicalEnvironmentHeapCellType;
    IsoHeapCellType globalObjectHeapCellType;
    IsoHeapCellType injectedScriptHostSpaceHeapCellType;
    IsoHeapCellType javaScriptCallFrameHeapCellType;
    IsoHeapCellType jsModuleRecordHeapCellType;
    IsoHeapCellType moduleNamespaceObjectHeapCellType;
    IsoHeapCellType nativeStdFunctionHeapCellType;
    IsoInlinedHeapCellType<JSString> stringHeapCellType;
    IsoHeapCellType weakMapHeapCellType;
    IsoHeapCellType weakSetHeapCellType;
    JSDestructibleObjectHeapCellType destructibleObjectHeapCellType;
#if JSC_OBJC_API_ENABLED
    IsoHeapCellType apiWrapperObjectHeapCellType;
    IsoHeapCellType objCCallbackFunctionHeapCellType;
#endif
#ifdef JSC_GLIB_API_ENABLED
    IsoHeapCellType apiWrapperObjectHeapCellType;
    IsoHeapCellType callbackAPIWrapperGlobalObjectHeapCellType;
    IsoHeapCellType jscCallbackFunctionHeapCellType;
#endif
    IsoHeapCellType intlCollatorHeapCellType;
    IsoHeapCellType intlDateTimeFormatHeapCellType;
    IsoHeapCellType intlDisplayNamesHeapCellType;
    IsoHeapCellType intlListFormatHeapCellType;
    IsoHeapCellType intlLocaleHeapCellType;
    IsoHeapCellType intlNumberFormatHeapCellType;
    IsoHeapCellType intlPluralRulesHeapCellType;
    IsoHeapCellType intlRelativeTimeFormatHeapCellType;
    IsoHeapCellType intlSegmentIteratorHeapCellType;
    IsoHeapCellType intlSegmenterHeapCellType;
    IsoHeapCellType intlSegmentsHeapCellType;
#if ENABLE(WEBASSEMBLY)
    IsoHeapCellType webAssemblyExceptionHeapCellType;
    IsoHeapCellType webAssemblyFunctionHeapCellType;
    IsoHeapCellType webAssemblyGlobalHeapCellType;
    IsoHeapCellType webAssemblyInstanceHeapCellType;
    IsoHeapCellType webAssemblyMemoryHeapCellType;
    IsoHeapCellType webAssemblyModuleHeapCellType;
    IsoHeapCellType webAssemblyModuleRecordHeapCellType;
    IsoHeapCellType webAssemblyTableHeapCellType;
    IsoHeapCellType webAssemblyTagHeapCellType;
#endif

    // AlignedMemoryAllocators
    std::unique_ptr<FastMallocAlignedMemoryAllocator> fastMallocAllocator;
    std::unique_ptr<GigacageAlignedMemoryAllocator> primitiveGigacageAllocator;
    std::unique_ptr<GigacageAlignedMemoryAllocator> jsValueGigacageAllocator;

    // Subspaces
    CompleteSubspace primitiveGigacageAuxiliarySpace; // Typed arrays, strings, bitvectors, etc go here.
    CompleteSubspace jsValueGigacageAuxiliarySpace; // Butterflies, arrays of JSValues, etc go here.
    CompleteSubspace immutableButterflyJSValueGigacageAuxiliarySpace; // JSImmutableButterfly goes here.

    // We make cross-cutting assumptions about typed arrays being in the primitive Gigacage and butterflies
    // being in the JSValue gigacage. For some types, it's super obvious where they should go, and so we
    // can hardcode that fact. But sometimes it's not clear, so we abstract it by having a Gigacage::Kind
    // constant somewhere.
    // FIXME: Maybe it would be better if everyone abstracted this?
    // https://bugs.webkit.org/show_bug.cgi?id=175248
    ALWAYS_INLINE CompleteSubspace& gigacageAuxiliarySpace(Gigacage::Kind kind)
    {
        switch (kind) {
        case Gigacage::Primitive:
            return primitiveGigacageAuxiliarySpace;
        case Gigacage::JSValue:
            return jsValueGigacageAuxiliarySpace;
        case Gigacage::NumberOfKinds:
            break;
        }
        RELEASE_ASSERT_NOT_REACHED();
        return primitiveGigacageAuxiliarySpace;
    }
    
    // Whenever possible, use subspaceFor<CellType>(vm) to get one of these subspaces.
    CompleteSubspace cellSpace;
    CompleteSubspace variableSizedCellSpace; // FIXME: This space is problematic because we have things in here like DirectArguments and ScopedArguments; those should be split into JSValueOOB cells and JSValueStrict auxiliaries. https://bugs.webkit.org/show_bug.cgi?id=182858
    CompleteSubspace destructibleObjectSpace;

    IsoSubspace arraySpace;
    IsoSubspace bigIntSpace;
    IsoSubspace calleeSpace;
    IsoSubspace clonedArgumentsSpace;
    IsoSubspace customGetterSetterSpace;
    IsoSubspace dateInstanceSpace;
    IsoSubspace domAttributeGetterSetterSpace;
    IsoSubspace exceptionSpace;
    IsoSubspace executableToCodeBlockEdgeSpace;
    IsoSubspace functionSpace;
    IsoSubspace getterSetterSpace;
    IsoSubspace globalLexicalEnvironmentSpace;
    IsoSubspace internalFunctionSpace;
    IsoSubspace jsProxySpace;
    IsoSubspace nativeExecutableSpace;
    IsoSubspace numberObjectSpace;
    IsoSubspace plainObjectSpace;
    IsoSubspace promiseSpace;
    IsoSubspace propertyNameEnumeratorSpace;
    IsoSubspace propertyTableSpace;
    IsoSubspace regExpSpace;
    IsoSubspace regExpObjectSpace;
    IsoSubspace ropeStringSpace;
    IsoSubspace scopedArgumentsSpace;
    IsoSubspace sparseArrayValueMapSpace;
    IsoSubspace stringSpace;
    IsoSubspace stringObjectSpace;
    IsoSubspace structureChainSpace;
    IsoSubspace structureRareDataSpace;
    IsoSubspace structureSpace;
    IsoSubspace brandedStructureSpace;
    IsoSubspace symbolTableSpace;

#define DYNAMIC_ISO_SUBSPACE_DEFINE_MEMBER(name) \
    template<SubspaceAccess mode> \
    IsoSubspace* name() \
    { \
        if (m_##name || mode == SubspaceAccess::Concurrently) \
            return m_##name.get(); \
        return name##Slow(); \
    } \
    JS_EXPORT_PRIVATE IsoSubspace* name##Slow(); \
    std::unique_ptr<IsoSubspace> m_##name;


#if JSC_OBJC_API_ENABLED
    DYNAMIC_ISO_SUBSPACE_DEFINE_MEMBER(apiWrapperObjectSpace)
    DYNAMIC_ISO_SUBSPACE_DEFINE_MEMBER(objCCallbackFunctionSpace)
#endif
#ifdef JSC_GLIB_API_ENABLED
    DYNAMIC_ISO_SUBSPACE_DEFINE_MEMBER(apiWrapperObjectSpace)
    DYNAMIC_ISO_SUBSPACE_DEFINE_MEMBER(jscCallbackFunctionSpace)
    DYNAMIC_ISO_SUBSPACE_DEFINE_MEMBER(callbackAPIWrapperGlobalObjectSpace)
#endif
    DYNAMIC_ISO_SUBSPACE_DEFINE_MEMBER(apiGlobalObjectSpace)
    DYNAMIC_ISO_SUBSPACE_DEFINE_MEMBER(apiValueWrapperSpace)
    DYNAMIC_ISO_SUBSPACE_DEFINE_MEMBER(arrayBufferSpace)
    DYNAMIC_ISO_SUBSPACE_DEFINE_MEMBER(arrayIteratorSpace)
    DYNAMIC_ISO_SUBSPACE_DEFINE_MEMBER(asyncGeneratorSpace)
    DYNAMIC_ISO_SUBSPACE_DEFINE_MEMBER(bigInt64ArraySpace)
    DYNAMIC_ISO_SUBSPACE_DEFINE_MEMBER(bigIntObjectSpace)
    DYNAMIC_ISO_SUBSPACE_DEFINE_MEMBER(bigUint64ArraySpace)
    DYNAMIC_ISO_SUBSPACE_DEFINE_MEMBER(booleanObjectSpace)
    DYNAMIC_ISO_SUBSPACE_DEFINE_MEMBER(boundFunctionSpace)
    DYNAMIC_ISO_SUBSPACE_DEFINE_MEMBER(callbackConstructorSpace)
    DYNAMIC_ISO_SUBSPACE_DEFINE_MEMBER(callbackGlobalObjectSpace)
    DYNAMIC_ISO_SUBSPACE_DEFINE_MEMBER(callbackFunctionSpace)
    DYNAMIC_ISO_SUBSPACE_DEFINE_MEMBER(callbackObjectSpace)
    DYNAMIC_ISO_SUBSPACE_DEFINE_MEMBER(customGetterFunctionSpace)
    DYNAMIC_ISO_SUBSPACE_DEFINE_MEMBER(customSetterFunctionSpace)
    DYNAMIC_ISO_SUBSPACE_DEFINE_MEMBER(dataViewSpace)
    DYNAMIC_ISO_SUBSPACE_DEFINE_MEMBER(debuggerScopeSpace)
    DYNAMIC_ISO_SUBSPACE_DEFINE_MEMBER(errorInstanceSpace)
    DYNAMIC_ISO_SUBSPACE_DEFINE_MEMBER(float32ArraySpace)
    DYNAMIC_ISO_SUBSPACE_DEFINE_MEMBER(float64ArraySpace)
    DYNAMIC_ISO_SUBSPACE_DEFINE_MEMBER(functionRareDataSpace)
    DYNAMIC_ISO_SUBSPACE_DEFINE_MEMBER(generatorSpace)
    DYNAMIC_ISO_SUBSPACE_DEFINE_MEMBER(globalObjectSpace)
    DYNAMIC_ISO_SUBSPACE_DEFINE_MEMBER(injectedScriptHostSpace)
    DYNAMIC_ISO_SUBSPACE_DEFINE_MEMBER(int8ArraySpace)
    DYNAMIC_ISO_SUBSPACE_DEFINE_MEMBER(int16ArraySpace)
    DYNAMIC_ISO_SUBSPACE_DEFINE_MEMBER(int32ArraySpace)
    DYNAMIC_ISO_SUBSPACE_DEFINE_MEMBER(javaScriptCallFrameSpace)
    DYNAMIC_ISO_SUBSPACE_DEFINE_MEMBER(jsModuleRecordSpace)
    DYNAMIC_ISO_SUBSPACE_DEFINE_MEMBER(mapBucketSpace)
    DYNAMIC_ISO_SUBSPACE_DEFINE_MEMBER(mapIteratorSpace)
    DYNAMIC_ISO_SUBSPACE_DEFINE_MEMBER(mapSpace)
    DYNAMIC_ISO_SUBSPACE_DEFINE_MEMBER(moduleNamespaceObjectSpace)
    DYNAMIC_ISO_SUBSPACE_DEFINE_MEMBER(nativeStdFunctionSpace)
    DYNAMIC_ISO_SUBSPACE_DEFINE_MEMBER(proxyObjectSpace)
    DYNAMIC_ISO_SUBSPACE_DEFINE_MEMBER(proxyRevokeSpace)
    DYNAMIC_ISO_SUBSPACE_DEFINE_MEMBER(scopedArgumentsTableSpace)
    DYNAMIC_ISO_SUBSPACE_DEFINE_MEMBER(scriptFetchParametersSpace)
    DYNAMIC_ISO_SUBSPACE_DEFINE_MEMBER(scriptFetcherSpace)
    DYNAMIC_ISO_SUBSPACE_DEFINE_MEMBER(setBucketSpace)
    DYNAMIC_ISO_SUBSPACE_DEFINE_MEMBER(setIteratorSpace)
    DYNAMIC_ISO_SUBSPACE_DEFINE_MEMBER(setSpace)
    DYNAMIC_ISO_SUBSPACE_DEFINE_MEMBER(shadowRealmSpace);
    DYNAMIC_ISO_SUBSPACE_DEFINE_MEMBER(strictEvalActivationSpace)
    DYNAMIC_ISO_SUBSPACE_DEFINE_MEMBER(stringIteratorSpace)
    DYNAMIC_ISO_SUBSPACE_DEFINE_MEMBER(sourceCodeSpace)
    DYNAMIC_ISO_SUBSPACE_DEFINE_MEMBER(symbolSpace)
    DYNAMIC_ISO_SUBSPACE_DEFINE_MEMBER(symbolObjectSpace)
    DYNAMIC_ISO_SUBSPACE_DEFINE_MEMBER(templateObjectDescriptorSpace)
    DYNAMIC_ISO_SUBSPACE_DEFINE_MEMBER(temporalCalendarSpace)
    DYNAMIC_ISO_SUBSPACE_DEFINE_MEMBER(temporalDurationSpace)
    DYNAMIC_ISO_SUBSPACE_DEFINE_MEMBER(temporalInstantSpace)
    DYNAMIC_ISO_SUBSPACE_DEFINE_MEMBER(temporalPlainTimeSpace)
    DYNAMIC_ISO_SUBSPACE_DEFINE_MEMBER(temporalTimeZoneSpace)
    DYNAMIC_ISO_SUBSPACE_DEFINE_MEMBER(uint8ArraySpace)
    DYNAMIC_ISO_SUBSPACE_DEFINE_MEMBER(uint8ClampedArraySpace)
    DYNAMIC_ISO_SUBSPACE_DEFINE_MEMBER(uint16ArraySpace)
    DYNAMIC_ISO_SUBSPACE_DEFINE_MEMBER(uint32ArraySpace)
    DYNAMIC_ISO_SUBSPACE_DEFINE_MEMBER(unlinkedEvalCodeBlockSpace)
    DYNAMIC_ISO_SUBSPACE_DEFINE_MEMBER(unlinkedFunctionCodeBlockSpace)
    DYNAMIC_ISO_SUBSPACE_DEFINE_MEMBER(unlinkedModuleProgramCodeBlockSpace)
    DYNAMIC_ISO_SUBSPACE_DEFINE_MEMBER(unlinkedProgramCodeBlockSpace)
    DYNAMIC_ISO_SUBSPACE_DEFINE_MEMBER(finalizationRegistrySpace)
    DYNAMIC_ISO_SUBSPACE_DEFINE_MEMBER(weakObjectRefSpace)
    DYNAMIC_ISO_SUBSPACE_DEFINE_MEMBER(weakSetSpace)
    DYNAMIC_ISO_SUBSPACE_DEFINE_MEMBER(weakMapSpace)
    DYNAMIC_ISO_SUBSPACE_DEFINE_MEMBER(withScopeSpace)
    DYNAMIC_ISO_SUBSPACE_DEFINE_MEMBER(intlCollatorSpace)
    DYNAMIC_ISO_SUBSPACE_DEFINE_MEMBER(intlDateTimeFormatSpace)
    DYNAMIC_ISO_SUBSPACE_DEFINE_MEMBER(intlDisplayNamesSpace)
    DYNAMIC_ISO_SUBSPACE_DEFINE_MEMBER(intlListFormatSpace)
    DYNAMIC_ISO_SUBSPACE_DEFINE_MEMBER(intlLocaleSpace)
    DYNAMIC_ISO_SUBSPACE_DEFINE_MEMBER(intlNumberFormatSpace)
    DYNAMIC_ISO_SUBSPACE_DEFINE_MEMBER(intlPluralRulesSpace)
    DYNAMIC_ISO_SUBSPACE_DEFINE_MEMBER(intlRelativeTimeFormatSpace)
    DYNAMIC_ISO_SUBSPACE_DEFINE_MEMBER(intlSegmentIteratorSpace)
    DYNAMIC_ISO_SUBSPACE_DEFINE_MEMBER(intlSegmenterSpace)
    DYNAMIC_ISO_SUBSPACE_DEFINE_MEMBER(intlSegmentsSpace)
#if ENABLE(WEBASSEMBLY)
    DYNAMIC_ISO_SUBSPACE_DEFINE_MEMBER(jsToWasmICCalleeSpace)
    DYNAMIC_ISO_SUBSPACE_DEFINE_MEMBER(webAssemblyExceptionSpace)
    DYNAMIC_ISO_SUBSPACE_DEFINE_MEMBER(webAssemblyFunctionSpace)
    DYNAMIC_ISO_SUBSPACE_DEFINE_MEMBER(webAssemblyGlobalSpace)
    DYNAMIC_ISO_SUBSPACE_DEFINE_MEMBER(webAssemblyInstanceSpace)
    DYNAMIC_ISO_SUBSPACE_DEFINE_MEMBER(webAssemblyMemorySpace)
    DYNAMIC_ISO_SUBSPACE_DEFINE_MEMBER(webAssemblyModuleSpace)
    DYNAMIC_ISO_SUBSPACE_DEFINE_MEMBER(webAssemblyModuleRecordSpace)
    DYNAMIC_ISO_SUBSPACE_DEFINE_MEMBER(webAssemblyTableSpace)
    DYNAMIC_ISO_SUBSPACE_DEFINE_MEMBER(webAssemblyTagSpace)
    DYNAMIC_ISO_SUBSPACE_DEFINE_MEMBER(webAssemblyWrapperFunctionSpace)
#endif

#undef DYNAMIC_ISO_SUBSPACE_DEFINE_MEMBER
    
    IsoCellSet executableToCodeBlockEdgesWithConstraints;
    IsoCellSet executableToCodeBlockEdgesWithFinalizers;

#define DYNAMIC_SPACE_AND_SET_DEFINE_MEMBER(name) \
    template<SubspaceAccess mode> \
    IsoSubspace* name() \
    { \
        if (auto* spaceAndSet = m_##name.get()) \
            return &spaceAndSet->space; \
        if (mode == SubspaceAccess::Concurrently) \
            return nullptr; \
        return name##Slow(); \
    } \
    IsoSubspace* name##Slow(); \
    std::unique_ptr<SpaceAndSet> m_##name;
    
    struct SpaceAndSet {
        WTF_MAKE_STRUCT_FAST_ALLOCATED;

        IsoSubspace space;
        IsoCellSet set;
        
        template<typename... Arguments>
        SpaceAndSet(Arguments&&... arguments)
            : space(std::forward<Arguments>(arguments)...)
            , set(space)
        {
        }
        
        static IsoCellSet& setFor(Subspace& space)
        {
            return *bitwise_cast<IsoCellSet*>(
                bitwise_cast<char*>(&space) -
                OBJECT_OFFSETOF(SpaceAndSet, space) +
                OBJECT_OFFSETOF(SpaceAndSet, set));
        }
    };
    
    SpaceAndSet codeBlockSpace;

    template<typename Func>
    void forEachCodeBlockSpace(const Func& func)
    {
        func(codeBlockSpace);
    }

    DYNAMIC_SPACE_AND_SET_DEFINE_MEMBER(evalExecutableSpace)
    DYNAMIC_SPACE_AND_SET_DEFINE_MEMBER(moduleProgramExecutableSpace)
    SpaceAndSet functionExecutableSpace;
    SpaceAndSet programExecutableSpace;

    template<typename Func>
    void forEachScriptExecutableSpace(const Func& func)
    {
        if (m_evalExecutableSpace)
            func(*m_evalExecutableSpace);
        func(functionExecutableSpace);
        if (m_moduleProgramExecutableSpace)
            func(*m_moduleProgramExecutableSpace);
        func(programExecutableSpace);
    }

    SpaceAndSet unlinkedFunctionExecutableSpace;

#undef DYNAMIC_SPACE_AND_SET_DEFINE_MEMBER
};

} // namespace JSC