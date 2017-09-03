#ifndef LLUVIA_CORE_MEMORY_H_
#define LLUVIA_CORE_MEMORY_H_


#include <vector>
#include <memory>

#include <vulkan/vulkan.hpp>

#include "lluvia/core/MemoryAllocationInfo.h"
#include "lluvia/core/impl/MemoryFreeSpaceManager.h"


namespace ll {

// forward declarations
class Buffer;


/*
 * \brief Class to manage a particular type of memory. Memory pages of the
 * given type are allocated and managed.
 */
class Memory {

public:
    Memory()                     = default;
    Memory(const Memory& memory) = default;
    Memory(Memory&& memory)      = default;

    Memory(const uint64_t pageSize);

    ~Memory();

    Memory& operator = (const Memory& memory) = default;
    Memory& operator = (Memory&& memory)      = default;

    ll::Buffer allocateBuffer(const uint64_t size);
    void releaseBuffer(const ll::Buffer& buffer);

private:
    vk::Device device;

    std::vector<vk::DeviceMemory> memoryPages;
    std::vector<ll::impl::MemoryFreeSpaceManager> pageManagers;

    uint64_t pageSize;

    std::shared_ptr<int> referenceCounter {nullptr};

};

} // namespace ll

#endif // LLUVIA_CORE_MEMORY_H_
