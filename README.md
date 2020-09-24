# Project Plan
## Requirements
Need to write a server.
The server solves problems.

**The server side:**

To start the server, the following command is executed:

 ```
 ./ex4.out <port> [server type]
 ```

The server will listen on *port*, and will operate parallel or serial (as specified in *server type*)

**The client side**:

The client starts the connection with the server and sends the first message.
The following message is sent to the server for solving a problem:

```
solve <problem> [algorithm]
<two line breaks>
```

If the server received the message, it will return a reply. Next, the client will send the graph in the specified format: *specified in the instruction file*. 
The server tries solving the problem and returns a suitable message.

## Design

![alt text](https://github.com/yonatan-E/APproject/blob/design/absHierarchy.PNG?raw=true)

### Server

Abstract Class **Server**:

```
open(port, ClientHandler) //open the server on this port and listen to clients
close() //close this server
```

Class **SerialServer**
```
SerialServer implements Server
```

Class **ParallelServer**
```
ParallelServer implements Server
```

### Client Handler

Abstract class **ClientHandler**
```
handleClient(inputStream, outputStream) 
```
handles the client input and returns the necessary output.
  
Class **AlgorithmClientHandler**
```
Solver solver

CacheManager cacheManager
```

### Solver
Abstract Class **Solver**
```
Solve<ProblemType, SolutionType>() 
```
    
Class **DFSSolver, BFSSolver, BestFSSolver, AStarSolver** implement solver interface, and they will choose The parameters 
<ProblemType, SolutionType> for the Solve method .

### Searcher and Searchable
Interface **Searchable** will represent an object that can be searched on.  
Interface **Searcher** will represent a searcher, that can search on a **Searchable**.  
Those interfaces will interact with each other according to the **Bridge** design pattern, which seperate between the algorithm (in this case, the search algorithm), and the problem which this algorithm solves (in this case, the object to search in).

## Coding

***Bottom – up approach***
	
### Step 1 -  solver
* abstract class
* BFS, DFS,.. solver classes.
  
### Step 2 - client handler
* abstract class
* algorithm handler class


### Step 3 - Server
* abstract class
* SerialServer class
* ParallelServer class





