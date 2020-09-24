# Advanced Programming Project  

## Overview  
In this project we developed a server which operates search algorithms on graphs. A client connects to the server, sends over the graph and algorithm information and gets back the search result.

## The Search Algorithms  
In our project, we implemented 4 search algorithms: DFS, BFS, BestFS, and A*. All of those algorithms are implementing the *Searcher* interface, which represents the functionality of a search algorithm. The search algorithms can work only on objects that implement the *Searchable* interface, which represents the functionality of a searchable object. In this project, the only searchable Graph, which represents a graph which is defined by a matrix.
The *Searcher* and the *Searchable* are communicate between each other according to the *Bridge design pattern*.  
Another interface in the project is the *Solver* interface, which represents the basic functionality of an object which solves a problem. The concrete implementation of it for search algorithms is in the class SearchSolver, which contains a specific searcher object, according to the *Object Adapter design pattern*.  

## The Server  
The interface *Server* represents the functionality of a server, and the classes *SerialServer* and *ParallelServer* implement it. The server works when the method *open* is called, and the clients are handled according to the specific client handler that the *open* method gets, which implement the *ClientHandler* interface. In our project, the only client handler is *SolverClientHandler*, which uses for solving problems, especially search problems.  
The *SolverClientHandler* contains a specific solver object, according to the *Object Adapter design pattern*.     
The server and the client handlers communicate according to the *Bridge design pattern.  

## The Design  
The design of the project performs the *SOLID* principals. The code is very open for changes:
All of the interfaces, like *Searcher*, *Searchable*, and *ClientHandler* are very abstract, and using templates
for making the code more durable by extentions. For example, the *Searcher* interface is a template interface, and gets type parameters: one for the solution of the search, and another for the identifier which represents a specific element
in the searchable object which the searcher is searching on. This makes the code very open for extentions, and allows every searcher to search on different types of searchables and return a different kind of search result.    

## Error Codes  
The *error codes* that the server throws are:  
**Error code 0:** The operation worked successfully.   
**Error code 1:** The path between the given start point and end point does not exist.  
**Error code 2:** One of the given start point and end point is not valid.  
**Error code 3:** The message that the client sent for the request is invalid.  
**Error code 4:** The format of the graph that the client sent is invalid.  
**Error code 5:** The cache manager failed reading/writing to the files in the cache.  
**Error code 6:** Failed writing/reading/closing the client socket.  
