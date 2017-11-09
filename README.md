# jscList
a list that can do insert/delete in constant time and do random access in log time. 
When we want to do random access, we can call toRand() method which switches the list to random access mode. (otherwise it does the random
access in linear time)
When we want to do insert/delete/push/pop, we can call toInsDel() to switch to the insert-delete mode.
Notice that toRand() and toInsDel may take linear time.

Also, although this code is written in C, I tried to use object oriented thinking. jscobj.h/jscobj.c is a framework for this. With this
framework, my code looks object oriented, but it requires some extra code/macro which may look confusing and redundant.

Finally, this project is just for fun.
