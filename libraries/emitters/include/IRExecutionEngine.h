////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Project:  Embedded Learning Library (ELL)
//  File:     IRExecutionEngine.h (emitters)
//  Authors:  Umesh Madan
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once

// llvm
#include "llvm/ADT/Triple.h"
#include "llvm/IR/Module.h"
#include "llvm/ExecutionEngine/ExecutionEngine.h"

namespace ell
{
namespace emitters
{
    class IRModuleEmitter;

    /// <summary> Function signature for a basic function that takes no input and returns no output </summary>
    typedef void (*DynamicFunction)(void);

    /// <summary> Wrapper class to setup and manage the LLVM Execution Engine. By default, we us the new "MCJIT" </summary>
    class IRExecutionEngine
    {
    public:
        /// <summary>
        /// Move the primary "owner" module into the execution engine.
        /// </summary>
        ///
        /// <param name="module"> [in,out] The module. </param>
        IRExecutionEngine(IRModuleEmitter&& module);

        /// <summary> Inject the primary "owner" module into the execution engine. </summary>
        ///
        /// <param name="pModule"> The module. </param>
        IRExecutionEngine(std::unique_ptr<llvm::Module> pModule);

        /// <summary> Add an additional module to the execution engine. </summary>
        ///
        /// <param name="pModule"> The module to add. </param>
        void AddModule(std::unique_ptr<llvm::Module> pModule);

        /// <summary>
        /// Return the address of a named function, JITTing code as needed. Returns 0 if not found.
        /// </summary>
        ///
        /// <param name="name"> Name of the requested function. </param>
        ///
        /// <returns> The function address. </returns>
        uint64_t GetFunctionAddress(const std::string& name);

        /// <summary> Return the address of a named function. Throws if not found. </summary>
        ///
        /// <param name="name"> Name of the requested function. </param>
        ///
        /// <returns> The function address. </returns>
        uint64_t ResolveFunctionAddress(const std::string& name);

        /// <summary> Set the address of a named function. </summary>
        ///
        /// <param name="func"> The function being defined. </param>
        /// <param name="address"> The address of the function being defined. </param>
        void DefineFunction(llvm::Function* func, uint64_t address);

        /// <summary>
        /// Return a main function that takes no arguments - if one exists. Returns nullptr if not found.
        /// </summary>
        ///
        /// <returns> The main function. </returns>
        DynamicFunction GetMain();

        /// <summary> Return a main function that takes no arguments. Throws if not found. </summary>
        ///
        /// <returns> The main function. </returns>
        DynamicFunction ResolveMain();

        /// <summary> Resolve and run the default Main function, if any. </summary>
        void RunMain();

    private:
        void EnsureEngine();
        void EnsureClockGetTime();

        std::unique_ptr<llvm::EngineBuilder> _pBuilder;
        std::unique_ptr<llvm::ExecutionEngine> _pEngine;
    };
}
}
