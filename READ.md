# Core Rendezvous using Per-Core State Counters

Small experimental demo of a multicore rendezvous mechanism using one state counter per core.

## What it shows
- each core updates only its own state variable
- all cores wait until the others reached the same generation
- no OS wait primitive is required for the core idea
- atomic accesses are used in the C++ demo

## Important limitation
This is not automatically safe on weakly ordered architectures such as ARM.
For ARM-like systems, explicit memory ordering, barriers, and architecture-specific validation are required.

## Why this exists
This demonstrates the kind of synchronization pattern that can appear in early boot, bare-metal, AMP, RTOS startup, or heterogeneous multicore systems.

## Build
MSVC / C++20