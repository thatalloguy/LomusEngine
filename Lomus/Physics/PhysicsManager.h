#pragma once
#include <PxPhysicsAPI.h>
#include <PxPhysics.h>
#include <iostream>

using namespace physx;

class PhysicsManager
{
public:
    void init();
    void cleanUp();
};

class PxAllocatorCallback
{
public:
    virtual ~PxAllocatorCallback() {}
    virtual void* allocate(size_t size, const char* typeName, const char* filename,
        int line) = 0;
    virtual void deallocate(void* ptr) = 0;
};

class UserErrorCallback : public PxErrorCallback
{
public:
    virtual void reportError(PxErrorCode::Enum code, const char* message, const char* file,
        int line)
    {
        std::cout << "PhysX Error: " << message << "|  at File: " << file << "| Line: " << line << "\n";
        
    }
};