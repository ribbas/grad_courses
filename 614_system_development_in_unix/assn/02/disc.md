# Question 1

One of the confusing aspects regarding building systems based on compiled languages is the relationship between libraries and include files. In this discussion, I would like you to examine this relationship. Why doesn't it make sense to ask about compiling and library files? Or linking and include files? Are include files and library files related? In what way?

# Question 2

The make facility is arguably the initial build capability present for software systems. Many other build systems (e.g. ant, waf, etc.) have evolved since 'make' was introduced. If you are familiar with one of these other build systems (or, you can look into one of them), compare and contrast their capability with 'make'. A list of build systems can be found here: [List of build systems](https://en.wikipedia.org/wiki/List_of_build_automation_software)

From the list of build systems provided, I have used SCons before and have had significantly different experiences with them. My interaction with SCons is relatively limited, since I've only ever used it to compile [gem5](https://www.gem5.org/). It is a build tool that I personally found to be unique since it is built on Python scripts. The programming language is usually considered unfit for tasks championed by lower-level and faster languages, i.e. bash or C being the driving force behind the very popular Make. However, I was able to use the tool for the intended task with relative ease. In some aspects, it was much more user-friendly since Python scripts can be considered a lot more human-readable than Makefiles. The dependency of Python also made SCons cross-platform, whilst Make was limited to UNIX-like systems.

Another build system I noticed in the list was CMake. Although it is considered more of a build tool generator, i.e. a tool that generates tools like Makefiles and ninja files. Personally, understanding the macros and functions was a substantial learning curve. However, the trade off of the build files that CMake generates made up for its complexity.

One other build system I've heard more of recently is Ninja. The Ninja build system is actually meant to entirely replace Make. The reason for this is due to Make's poor performance on large scale projects. Ninja is able to get better performance because it has very constrained build files. While the build files are human readable like Make, they are not intended to be written manually but generated using a higher level language. This is because Ninja has a more restrained syntax and certain oeprations are not feasible to write by a human every time. The NInja organization reccommends using its build system when you have very large projects - for example, Ninja is used on Google Chrome, Android, and LLVM [1].

[1] https://ninja-build.org/

I have heard of ninja before! My experience with the tool is fairly limited as I briefly experimented with it in conjunction with CMake which made the generation of ninja files extremely convenient. One thing I found interesting was that ninja performs parallel builds by default. I was directed by a colleague to an article that performed some heuristic benchmark analysis of ninja against Make. [1] It demonstrated how for smaller builds, the performance of both of the build tools is negligible in comparison. However, as they performed tests with much larger builds, the performance boost of ninja was evident. I think the tool prioritizing parallel builds makes it preferable for large projects like the ones you listed.

[1] https://david.rothlis.net/ninja-benchmark/
