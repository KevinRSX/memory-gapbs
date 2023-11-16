# Smart Page Size Allocation of Parallel Graph Applications in a Tiered-memory
## Links

- [GitHub repo](https://github.com/KevinRSX/memory-gapbs)
- [Project website](./)
- [Proposal (PDF)](./15618_proposal.pdf)
- Milestone report (TBA)
- Final report (TBA)

## Justification for a One-person Team

The course staff permitted me to work on this project individually. The project is an extension of my ongoing research work done in the CAOS group at CMU. Sum Yin Kwok and Kaiyang Zhao, while not enrolled in our class, also contributed to the original project. Their specific effort will be credited in the final report.

## Summary

In this project, we shall analyze the performance of parallel graph applications in a tiered-memory system with multiple page sizes and explore how smartly allocating pages of different sizes interplays with such an environment. Both studies will involve various aspects of parallel applications, including end-to-end performance, TLB pressure, cache performance, work imbalance, etc.

## Background and Challenges

Graph applications are often memory-intensive. Techniques to boost the performance of those applications include: 1) using huge pages to reduce the TLB miss rate to improve address translation overhead, 2) leveraging a tiered-memory system, where the traditional main memory is divided into heterogeneous devices with different latency, bandwidth, and cost, to balance the cost and performance, and 3) utilizing shared-memory-based parallel programming frameworks, such as OpenMPI, to distribute the task to multiple processors.

Currently, studies focusing on huge pages typically assume a homogeneous main memory, whereas those centered on tiered-memory systems, such as CXL, mainly address the migration of standard 4KB pages across the different tiers. For a system with homogeneous main memory extremely optimized for minimizing TLB miss rate using huge pages, it might fail to offload proper cold pages to lower tiers because they are promoted to a huge page and cannot be directly offloaded. On the other hand, if the hotness of smaller regions is imbalanced within a huge page, candidate pages selected for offloading to lower tiers using existing algorithms developed by tiered-memory researchers could be sub-optimal.

Parallelism complicates these issues even more for various reasons. For example, additional TLB shootdown is required whenever a page is migrated, or additional contention can happen since two processors are accessing the same page in the lower-tier memory (CXL) together. It would therefore be challenging to answer the questions such as:

- what pages should be promoted to large pages?
- what pages should be offloaded to the CXL (lower tier) memory?
-  how do different processors behave in a tiered-memory system with multiple page sizes?

## Resources

We will use the Entropy server provided by the Parallel Data Lab to conduct the experiment. We will use modified versions of [QEMU](https://www.qemu.org/) and [The Structural Simulation Toolkit](https://sst-simulator.org/}) to simulate the hardware environment we need. We will use the GAP Benchmark Suite to run the parallel graph applications with OpenMPI.

## Goals and Deliverables

This project is composed of two parts. The first part is an analysis of parallel graph applications running on tiered-memory systems with different page sizes. This part will motivate a need for a set of smart memory management policies in this environment. In the second part, we will propose an algorithm for smartly managing page sizes based on the page access temperature gathered from a novel technique called **hotness walk**. In both parts, we will compare work balance and memory access patterns across different processors, and describe how the environment and our algorithm inter-plays with the parallel workloads.

Specifically, by the deadline of the project's final report, we plan to have completed the following:

- a hardware simulation environment for CXL and multiple page sizes running on multiple cores
- a study that motivates a need for a set of smart memory management policies in a tiered-memory system with different page sizes
- a characterization of the memory access behavior as well as the related overhead in the data cache and TLB on different cores

We hope to complete the following if the previous part shows solid results and if the time permits:

- development of an algorithm that dynamically allocates pages of different sizes based on historical memory access data and an analysis of its effect on parallel graph applications

## Schedule

Please refer to the [proposal](./15618_proposal.pdf) for the schedule. This section will be updated when an item is completed.
