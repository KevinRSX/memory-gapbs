# Understanding the Performance of Parallel Applications in a Tiered-memory System
## Links

- [GitHub repo](https://github.com/KevinRSX/memory-gapbs)
- [Project website](./)
- [Proposal (PDF)](./15618_proposal.pdf)
- [Milestone report (PDF)](./15618_milestone.pdf)
- [Final report (PDF)](./15618_report.pdf)
- [Poster (PDF)](./15618_poster.pdf)

## Project Updates

Please refer to the [milestone report](./15618_milestone.pdf) for a description of the updates to this project as of December 4th, and the [final report](./15618_report.pdf) for the final report.

## Summary

This project serves as a motivation for research that aims at solving these problems. We first discuss the memory manage- ment background and review the issues with existing solutions in detail. To overcome these problems, we propose *hotness walk*, a design that provides architectural support for detecting the hotness of pages in any range. Then, we extend a full-system simulator to prepare us to implement offloading and page size promotion algorithms. Using the simulator, we profile the performance of the parallel applications to profile the challenge and discuss the feasibility of the design. Finally, we use the evaluation results to direct the future work to be done to complete the details of this design.

## Background and Challenges

Graph applications are often memory-intensive. Techniques to boost the performance of those applications include: 1) using huge pages to reduce the TLB miss rate to improve address translation overhead, 2) leveraging a tiered-memory system, where the traditional main memory is divided into heterogeneous devices with different latency, bandwidth, and cost, to balance the cost and performance, and 3) utilizing shared-memory-based parallel programming frameworks, such as OpenMPI, to distribute the task to multiple processors.

Currently, studies focusing on huge pages typically assume a homogeneous main memory, whereas those centered on tiered-memory systems, such as CXL, mainly address the migration of standard 4KB pages across the different tiers. For a system with homogeneous main memory extremely optimized for minimizing TLB miss rate using huge pages, it might fail to offload proper cold pages to lower tiers because they are promoted to a huge page and cannot be directly offloaded. On the other hand, if the hotness of smaller regions is imbalanced within a huge page, candidate pages selected for offloading to lower tiers using existing algorithms developed by tiered-memory researchers could be sub-optimal.

Parallelism complicates these issues even more for various reasons. For example, additional TLB shootdown is required whenever a page is migrated, or additional contention can happen since two processors are accessing the same page in the lower-tier memory (CXL) together. It would therefore be challenging to answer the questions such as:

- what pages should be promoted to large pages?
- what pages should be offloaded to the CXL (lower tier) memory?
-  how do different processors behave in a tiered-memory system with multiple page sizes?

## Central Problem - What is Hot?

Four requirements of hotness:

- Tracked in a fine granularity
- Low overhead of tracking
- Low overhead of a decision policy
- Need per-process hotness to ensure fairness

Take a look at Section 3 in the [final report](./15618_report.pdf) for how we tackle these requirements!

## Evaluation Goals

1. What is the performance of parallel applications running on a tiered-memory system with multiple page sizes?
2. Will workload be more imbalanced due to the longer la- tency of accessing the slower memory tier? Is the tiered- memory environment something that requires the paral- lel application programmer to react upon?
3. What are the TLB miss rates under different configura- tions of page sizes and memory tiers?
4. What is the cost to synchronize the hotness update of multiple cores?
5. Why is it necessary to track hotness in a fine granularity? How imbalanced is page hotness among the address space?

Take a look at Section 5 in the [final report](./15618_report.pdf) for a discussion of it!

## Schedule

**As of the submission of the final report, all items have been completed. The last item of designing an algorithm is left as future research work.** Please refer to the [proposal](./15618_proposal) for an initial schedule and the [milestone report](./15618_milestone) for an updated schedule.
