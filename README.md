# Graph-Algorithms
DFS and BFS traversal, all route and shortest path problems using a linked list represented graph.

Usage:
You can use 'Make' command to compile, or you can use 'GCC -Wall -o <filename> main.c graph.c list.c stack.c queue.c traverse.c' to do the same thing.

After compilation, run the executable using ./<filename> -p [part number] -s [starting vertex] -d [destination vertex] -f [input file representing graph]. For example, let's say that the file name is graph, the input file is vic-roads.txt and we want to know every simple path between the source, 12 (Melbourne) and 11 (Geelong), we could run the programme like this:

    ./graph -p 4 -s 12 -d 11 -f vicroads.txt

 It will subsequenty print out every possible simple path between these two vertices.
 
 If you have any questions, leave a comment down below and feel free to shoot me an email.
 
Hongfei Yang
April 2017
