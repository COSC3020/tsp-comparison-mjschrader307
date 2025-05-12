# Traveling Salesperson Problem -- Empirical Analysis

For this exercise, you'll need to take the code from the TSP Held-Karp and TSP
Local Search exercises. This can be your own implementation or somebody else's.
You will now do an empirical analysis of the implementations, comparing their
performance. Both the Held-Karp and the Local Search algorithms solve the same
problem, but they do so in completely different ways. This results in different
solutions, and in different times required to get to the solution.

Investigate the implementations' empirical time complexity, i.e. how the runtime
increases as the input size increases. *Measure* this time by running the code
instead of reasoning from the asymptotic complexity (this is the empirical
part). Create inputs of different sizes and plot how the runtime scales (input
size on the $x$ axis, time on the $y$ axis). Your largest input should have a
runtime of *at least* an hour. The input size that gets you to an hour will
probably not be the same for the Held-Karp and Local Search implementations.

In addition to the measured runtime, plot the tour lengths obtained by both
implementations on the same input distance matrices. The length of the tour that
Held-Karp found should always be less than or equal to the tour length that
Local Search found. Why is this?

Add the code to run your experiments, graphs, and an explanation of what you did
to this markdown file.

---

## Answer 

I regrettably waited a little too long to do this exercise and do it completely right. I was worried about attempting to run a C++ program for the Held-Karp algorithm (the implementation of which I found online and changed slightly) for a large size, because I know the runtime complexity is $O(2^n \cdot n^2)$, so it increases ridiculously fast. I was also concerned about memory space, because my laptop only has 32 GB of memory, and I logged into one of the EECS Hive machines, which have about 29 GiB of available memory. 

### Held-Karp

I used an exponential fitting algorithm I developed last semester to fit a curve to some relatively small values for $n$ and estimate what input size would be required to reach an hour of computation time. Here is what I got from running the C++ code with several values of `n`:

| Input Size (number of cities) | Duration (seconds) |
| --- | --- |
| 1 | 0.000002 |
| 2 | 0.000003 |
| 5 | 0.000028 |
| 10 | 0.001911 |
| 15 | 0.112411 |
| 20 | 5.938734 |
| 25 | 287.409284 |

The resulting exponential approximation curve for this data is $T(n) \approx 1.57e{-6} \cdot e^{0.75n}$. Intersecting this curve with $y = 3600$ seconds gives an $n$ value of about 29. I however, did some research and came to the conclusion that with my memory constraints, I can only realistically get up to $n = 26$, unless introducing some counteractive measures in the function implementation. 

After running the code for $n = 26$, I got a duration of 221.282872 seconds, which is less than what I got for $n = 25$, which is really strange. I'm not sure what happened there, but the approximation curve says it should take roughly 462 seconds.

### Local Search

After running a Local Search implementation with the same values of $n$, I now have the following table:

| Input Size (number of cities) | Held-Karp Duration (seconds) | Local Search Duration (seconds) |
| --- | --- | --- |
| 1 | 0.000002 | 0 |
| 2 | 0.000003 | 0 |
| 5 | 0.000028 | 0 |
| 10 | 0.001911 | 0 |
| 15 | 0.112411 | 0 |
| 20 | 5.938734 | 0.001 |
| 25 | 287.409284 | 0.001 |
| 26 | 221.282872 | 0.002 |

Local Search is obviously scaling a lot more slowly than H-K, but I am going to fit a cubic curve to the data to get an approximation for an $n$ value that would make Local Search take an hour. With some random extra values of $n$, I have the following:

| Input Size (number of cities) | Duration (seconds) |
| --- | --- |
| 35 | 0.005 |
| 50 | 0.015 |
| 100 | 0.110 |
| 200 | 1.029 |

Weirdly enough, it took around 200 cities to break a second in runtime.

I used a Least-Squares cubic curve fitting technique also developed last semester to approximate the input size needed to make Local Search take an hour. I did a cubic approximation, because I know the runtime complexity is cubic in the number of vertices. The function I got with the above data came out as:
$T(n) \approx (1.6917 \cdot 10^{-7})n^3 - (1.0726 \cdot 10^{-5})n^2 + (5.6465 \cdot 10^{-4})n - 0.0083$

$T(n) = 3600 \rightarrow n \approx 2792 \text{ cities}$

### Conclusion

Using these estimation techniques, the computation time for Local Search clearly scales a lot slower than Held-Karp, and that is also clear just by looking at the theoretical runtime complexities ($O(2^n \cdot n^2)$ vs $O(n^3)$ with n being number of vertices or cities).

As I understand it, this also makes sense, because Held-Karp is an exact solution, and for a problem like the TSP, that is generally going to have a crazy runtime complexity. On the flip side, Local Search is not exact -- it is a heuristic that doesn't always return optimal solutions. 

---

Sources:
- computergeek.com for C++ algorithm implementations
- ChatGPT for some minor assistance in matplotlib plotting and data cleaning as I have never done that before

**I certify that I have listed all sources used to complete this exercise, including the use
of any Large Language Models. All of the work is my own, except where stated
otherwise. I am aware that plagiarism carries severe penalties and that if plagiarism is
suspected, charges may be filed against me without prior notice.**
