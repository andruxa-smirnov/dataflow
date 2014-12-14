#ifndef MANAGED_MEMORY_CHUNK_H
#define MANAGED_MEMORY_CHUNK_H
#include <cstddef>
#include "interpreter_export.h"

class INTERPRETER_NO_EXPORT ManagedMemoryChunk
{
    void * managedData{};
    std::size_t managedDataSize{};
    void releaseManagedData();
public:
    ManagedMemoryChunk() {};
    explicit ManagedMemoryChunk(std::size_t chunkSize);
    ~ManagedMemoryChunk();

    /*ManagedMemoryChunk(const ManagedMemoryChunk &) = delete;
    ManagedMemoryChunk & operator=(const ManagedMemoryChunk &) = delete;*/

    ManagedMemoryChunk(ManagedMemoryChunk && other);
    ManagedMemoryChunk & operator=(ManagedMemoryChunk && other);

    operator void * ();
};

#endif
