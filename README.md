<h1 align="center">mini_talk</h1>

> Hive Helsinki (School 42) 7th curriculum project (Rank02)

<h2 align="center">
	<a href="#about">About</a>
	<span> · </span>
	<a href="#program">Program</a>
	<span> · </span>
	<a href="#requirements">Requirements</a>
	<span> · </span>
	<a href="#instructions">Instructions</a>
	<span> · </span>
	<a href="#references">References</a>
</h2>

## About
The repository contains files for creating two executables (./server and ./client) which can communicate with each other by utilising signals.

## Program
Launching the server executable presents a `PID` in the terminal which can be used as first argument for the client executable which in turn
needs to be launched in a second terminal window. The second argument for the ./client is the message which should be transferred to the server (if writing sentences, the whole arguement 
needs to be put into quotes `" "`). Also emojis are supported.  
The program makes use of several signal functions of the `signal.h` library, such as `sigaction` for setting up respective signal handlers.   
Overall logic: First the client sends the length of the message which should be transferred to the server. The server allocates memory accordingly for the incoming message which is terminated by '/0'. As the project requirements only allow the usage of the two signals `SIGUSER1` and `SIGUSER2` for sending the information, the message is encoded from client with help of bitshifting into bits and then decoded again on server side.

## Requirements
- `gcc` compiler

## Instructions

### 1. Compiling the program

To compile the two executables, navigate into the repo folder and run:

```
$ make 
```

### 2. Launch server

Start the server and check the PID on the terminal.
```
$ ./server
```

### 3. Launch client

Start the client by inserting the command below in a second terminal window (replace PID with the PID number displayed by the server and message with any text).
```
$ ./client <PID> <"message">
```
The sent message will appear in the terminal window of the server. The client terminal window in turn shows every bit transfer to the server for this message.
