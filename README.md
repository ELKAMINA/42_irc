# ft_irc project 
The goal of this project is to create our own IRC server. This server is capable of accepting multiple connections without blocking and answer multiple client at the same time.
This project is about creating our own IRC server. For testing purposes, we chose IRSSI as the client part.


## Requirements :

  - Coding in c++98
  - Handling multiple clients at the same time and never blocking
  
  - Using one of the 3 functions : Select/Poll/Epoll (we chose Poll)
  
  - Communicating via TCP/IP (v4) between clients and server
  
  - Features to implement :
    > Authentification
    
    > Setting a nickname/username
    
    > Creating rooms/channels and communitating
    
    > PrivateMessaging
    
    > Defining administrators and operators of channels and server and all commands they're concerned with

## Bonus : 
  - A Bot named "MARVIN" capable of presenting itself, randomly chooses a famous quote from a movie, and gives time and date.
  - Commands implemented 
  
    - HELP
    
    - HELLO
    
    - TIME
    
    - TALK
    
    - SHAKE

# Our IRC Commands
These are the available commands in our IRC Server:
  - **PASS**: for entering the server
  
  - **NICK**: for getting recognized throughout the server
  
  - **USER**: for specifying the username, hostname and realname of a new user
  
  - **OPER**: for obtaining operator privileges
  
  - **MODE**: for changing user modes
  
  - **QUIT**: for quitting a client session. The client is no more on the server but his nickname is registered and can't be used anymore
  
  - **JOIN**: for joining from one to many channels. If the channel doesn't exist, the user became the owner/operator
  
  - **PART**: for leaving one or more channels registered in
  
  - **TOPIC**: for giving the topic of the channel if it exists
  
  - **KICK**: for kicking a user from a channel. The user that wants to kick has to be operator of the channel
  
  - **PRIVMSG**: for sending private messages to another user. If the user we want send to, is away, the user sending the PRIVMSG receives the away message
  
  - **NOTICE**: for sending private messages to another user. If the user we want send to, is away, the user sending the NOTICE doesn't receive the away message
  
  - **RESTART**: for restarting the server
  
  - **KILL**: for killing a client session.Only operators of the server can do this
  
  - **MARVIN*: for starting the bot


# Contributers

[JM Cervoni](https://github.com/ElRealMitch)<br/>

[ELAMINA](https://github.com/ELKAMINA)
<br/>

Links that helped
-----------
| Subject | Link |
|:--------------|:----------------|

| Nginx Server and Location block | https://www.digitalocean.com/community/tutorials/understanding-nginx-server-and-location-block-selection-algorithms |

| AF_INET & struct address | https://stackoverflow.com/questions/1593946/what-is-af-inet-and-why-do-i-need-it |

| How internet works | https://www.youtube.com/watch?v=7_LPdttKXPc |

| Socket Types | https://www.ibm.com/docs/pl/aix/7.1?topic=protocols-socket-types |

| Nice guide for Network Programming | [https://www.ibm.com/docs/pl/aix/7.1?topic=protocols-socket-types](https://beej.us/guide/bgnet/pdf/bgnet_usl_c_1.pdf) |

| About socket Blocking | https://dwise1.net/pgm/sockets/blocking.html |

| REUSE PORT | https://blog.flipkart.tech/linux-tcp-so-reuseport-usage-and-implementation-6bfbf642885a |

| Binding to any available port | https://www.baeldung.com/cs/binding-available-ports |

| Simple HTTP Server | https://trungams.github.io/2020-08-23-a-simple-http-server-from-scratch/ |


| C10K | [https://trungams.github.io/2020-08-23-a-simple-http-server-from-scratch/](http://www.kegel.com/c10k.html) |

| HTTP Benchmarking Tool | https://github.com/wg/wrk |


# Global glossary

> **RFC** = Requests for comments. set of informations, documents and norms that standardize, describe, specify regarding network in general.
is a type of publication from the Internet Engineering Task Force (IETF) and the Internet Society(ISOC), the principal technical development and standards-setting bodies for the Internet.
 
 
> **OSI** : Open Systems Interconnection model (OSI model) is a conceptual model that characterizes and standardizes the communication functions of a telecommunication or computing system without regard to its underlying internal structure and technology. Its goal is the interoperability of diverse communication systems with standard protocols.  The model partitions a communication system into abstraction layers. Original version of the model defines 7 layers :
  - physical
  
  - Data link
  
  - Network
  
  - Transport
  
  - Session
  
  - Presentation
  
  - Application
 
A socket programming interface provides the routines required for interprocess communication between applications, either on the local system or spread in a distributed, **TCP/IP** based network environment. Once a peer-to-peer connection is established, a socket descriptor is used to uniquely identify the connection. The socket descriptor itself is a task specific numerical value.
One end of a peer-to-peer connection of a TCP/IP based distributed network application described by a socket is uniquely defined by

*Internet address*

for example 127.0.0.1 (in an IPv4 network) or FF01::101 (in an IPv6 network).

*Communication protocol*

User Datagram Protocol (UDP)
Transmission Control Protocol (TCP)

*Port*

A numerical value, identifying an application. We distinguish between "well known" ports, for example port 23 for Telnet
user defined ports
 
> **TCP/IP** :  Transmission Control Protocol (TCP) vs User Datagram Protocol (UDP) vs Sequenced Packet Exchange (SPX).
HTTP communication usually takes place over TCP/IP connections. The default port is TCP 80, but other ports can be used. This does not preclude HTTP from being implemented on top of any other protocol on the Internet, or on other networks. but any reliable transport can be used with http protocol.

> **Network interface**

Network interface may refer to:

  *Network interface controller*, a computer hardware component that connects a computer to a computer network
  *Network interface device*, a device that serves as the demarcation point between a telephone carrier's local loop and the customer's wiring
  *Virtual network interface*, an abstract virtualized representation of a computer network interface
  *Loopback interface*, a virtual network interface that connects a host to itself

> **Socket** : is the mechanism that most popular operating systems provide to give programs access to the network. It allows messages to be sent and received between applications (unrelated processes) on different networked machines. The sockets mechanism has been created to be independent of any specific type of network. **IP (Internet Protocol), however, is by far the most dominant network and the most popular use of sockets.**

There are some differents sockets :
  - Unix domain socket : are file descriptors. Every I/O is done by writing or reading a file descriptor. 4 types :
    
      a. Socket Stream : (interests for this one) : it works like a pipe and implemented on the transmission Control Protocol/Internet Protocol
      b. Datagram Socket
      c. Raw socket
      d. Sequenced packet Socket
  - TCP/IP socket : Open a network port to allow communicatio a system process.

** Non-blocking sockets** : Very important

/!\ Simple Fact : Sockets block. Why ?

--> Any function (normal function though) performs its task or fails for some reason.
and then it returns. If it takes that function a long time to perform its task, then it's going to be a long time before it returns. That's only natural. Well, that's exactly what a blocking sockets function call does, only since that function's task is to read a socket, that means that it won't return until it has read that socket. That means that if there's nothing ready to be read, then it's going to wait until there is something there, which will usually be a very noticeably long indeterminate time. That is why a sockets function call will block. Because it can't perform its task until data is available to be read. Or, in the case of accept, until a client tries to connect to the server *(EXAMPLE : waiting for user's input in standard input. It can block a long until the user write smthg.)

In sockets, the functions that are particular problematic are accept() and recv() and recvfrom(). Especially in a multi-client server, you cannot afford to sit there waiting for the next client to connect -- which could literally take days to happen -- and be unable to handle any of the clients who have already connected. This makes learning how to deal with blocking functions absolutely essential.

*So how to deal with blocking sockets ?*

4 techniques :

  1. Have a design that doesn't care about blocking => (nope for webserver project)

  2. Use the "select" function (nope but intersting for EXAM 05) :

    As we want to deal with blocking sockets. Select function resolve this problem by making you toknow before you make that function call whether there's any data waiting to be read in a socket. If there is then you make the function call, but if there isn't then you skip that socket this time around and launch it later once data is available.

    /!\ **Select** is a good way to deal with blocking socket and is easy to use when starting socket programming, but you have to keep in mind that select can iterate through a significant amount of fds (define by the nfds argument), so the downside of this function is that in the long run and on a solicited server the program will lose in performance.

  3. Use non-blocking sockets (nope)

  4. Use multithreading or multitasking (Yes, for webserver project)

> **Network byte ordering** : convention defines the bit-order of network addresses as they pass through the network
See also : Host byte order (same same)

> **Address family** : The address family configuration options allow you to specify how a particular routing protocol behaves with regards to multiple Layer 3 protocols. An address family can be IPv4, IPv6. An address family configuration simply tells the routing protocol how to deal with routes that are learned via a routing protocol.

> **Stateless application ** : A stateless app is an application program that does not save client data generated in one session for use in the next session with that client. Each session is carried out as if it was the first time and responses are not dependent upon data from a previous session

> **Optical Fiver cable :** backbone of the internet

> **URL :** Universal Resource Locator

> **REST APIs :** Application programming interface, is a set of rules that define how applications or devices can connect to and communicate with each other. A REST API is an API that conforms to the design principles of the REST, or representational state transfer architectural style.

> **Gateways :** A gateway is a network node used in telecommunications that connects two networks with different transmission protocols together. Gateways serve as an entry and exit point for a network as all data must pass through or communicate with the gateway prior to being routed.

> **out-of-band data transmission** : without passing by the LAN (Local Area Network)

> **Pipelining HTTP** : is a feature of HTTP/1.1 which allows multiple HTTP requests to be sent over a single TCP connection without waiting for the corresponding responses. HTTP/1.1 requires servers to respond to pipelined requests correctly, with non-pipelined but valid responses even if server does not support HTTP pipelining. 
  Limitations : he server must send its responses in the same order that the requests were received—so the entire connection remains first-in-first-out[1] and HOL blocking can occur. HTTP pipelining requires both the client and the server to support it. HTTP/1.1 conforming servers are required to produce valid responses to pipelined requests, but may not actually process requests concurrently.
  /!\ Non-idempotent requests such as POST should not be pipelined.

> ** Socket Pair ** : 

> **ICP** : InterProcess Communication (Mutex!!!!!!).

> **no-op** : A no op (or no-op), for no operation , is a computer instruction that takes up a small amount of space but specifies no operation. The computer processor simply moves to the next sequential instruction. The no op is included in most assembler languages. It may have a label and can serve as a placeholder for a useful instruction to be inserted later during code development.

> **Three way handshake** : SYN / SYN-ACK (synchronize, aknowledge) / ACK (permet d'etablir une connexion entre le client et le serveur ).

Link : https://stackoverflow.com/questions/11129212/tcp-can-two-different-sockets-share-a-port

> **C10K problem in webservs** : http://www.kegel.com/c10k.html

# Questionning

1. Socket operations are synchronous

2.  Difference between socket and TCP/IP ? {Check Global glossary on `Socket`}

**TCP/IP** is the most common protocol stack used in the internet. It specifies how data should be addressed, transmitted, routed and received at the destination. It has 4 Layers: Application layer, Transport layer, Internet layer and Link layer.

One of the most important protocol in this stack is TCP. TCP is a connection-oriented, end-to-end reliable protocol designed to fit into a layered hierarchy of protocols which support multi-network applications. TCP provides a reliable connection between two pairs of processes of computer hosts attached to a network. A TCP connection is defined by two endpoints aka sockets.

**A socket** represents endpoints of communication between two programs in computer network. In order to communicate, we have to identify the computer using IP Address and specify the program using Port number.

*Following what was said in the glossary Socket part :*
  A UNIX socket, AKA Unix Domain Socket, is an inter-process communication mechanism that allows bidirectional data exchange between processes running on the same machine.

  IP sockets (especially TCP/IP sockets) are a mechanism allowing communication between processes over the network. In some cases, you can use TCP/IP sockets to talk with processes running on the same computer (by using the loopback interface).

  UNIX domain sockets know that they’re executing on the same system, so they can avoid some checks and operations (like routing); which makes them faster and lighter than IP sockets. So if you plan to communicate with processes on the same host, this is a better option than IP sockets.
  As per Nils Toedtmann's comment: UNIX domain sockets are subject to file system permissions, while TCP sockets can be controlled only on the packet filter level.
  
** Socket Communiation Domain : **

* Maybe response : * https://stackoverflow.com/questions/48443105/does-tcp-ip-connection-automatically-closed-when-os-do-a-garbage-collection-afte

Sockets that share common communication properties, such as naming conventions and protocol address formats, are grouped into communication domains. A communication domain is sometimes referred to as name or address space.

The communication domain includes the following:
- Rules for manipulating and interpreting names
- Collection of related address formats that comprise an address family
- Set of protocols, called the protocol family

Communication domains also consist of two categories, socket types and descriptors. Socket types include stream, datagram, sequenced packet, raw, and connection-oriented datagram.

3. Why connections cannot be closed immediately or bind to the same port in TCP/IP sockets ?

4. What is the diff between read vs recv and write vs send() ?

  - send and write work only on socket descriptors and give the possibility to specity options for op and flags
  - read and recv are the universal file descriptor functions working on all fds.

5. Blocking Socket function : Is  a function that blocks because it has to wait for smthing to read so it wait until there is something there.
The functions that are particularly problematic are : accept(), recv(), recvfrom().
Blocking is a normal behavior but we need to take this behavior into account to deliver a robust responsive application

6. Difference TCP / UDP :
  TCP server needs multiple sockets (The listening socket and a separate socket for each client)  to handle multiple clients whereas UDP needs one socket to handle multiple clients but can't do anything while waiting for the next diagram.

7. Why choosing ePoll for handling multi-client server ? 

**epoll** is a new system call introduced in Linux 2.6. It is designed to replace the **deprecated select** (and also poll). Unlike these earlier system calls, which are O(n), epoll is an O(1) algorithm – this means that it scales well as the number of watched file descriptors increase. select uses a linear search through the list of watched file descriptors, which causes its O(n) behaviour, whereas epoll uses callbacks in the kernel file structure.

# Issues

1. Bind results in a permission denied when using port 81 

Quick answer : Ports below 1024 are considered to be privileged in Linux,

  **Rep : https://stackoverflow.com/questions/31899673/bind-returning-permission-denied-c**

2. Failed to connect: Socket operation on non-socket

**Rep**: https://www.sendblaster.com/support/error-trapping/socket-operation-a-non-socket-error/#:~:text=The%20%E2%80%9CSocket%20operation%20on%20a%20non%2Dsocket%E2%80%9D%20error%20means,has%20been%20shut%20down%20abruptly.

3. Noticing that wehn a request is made by a browser, the server receives two requests.

**Rep**: its a feature included in Chrome. Reference : https://stackoverflow.com/questions/41686296/why-does-node-hear-two-requests-favicon (same same for c++ i guess)

# Good to know : How does the Internet works ?

/!\  Internet & Web : are 2 different things. Internet is **the backbone of the web**. it's the technical infrastructure that makes the Web possible.

/!\  Our computer at home are not servers bc they are not connected directly to the server. THEY ARE CLIENTS BC THEY ARE INDIRECTLY CONNECTED TO THE INTERNET THROUGH AN ISP (*INTERNET SERVICE PROVIDER)**

/!\  Whenever an email/pictures or webpage travels accross the internet, computers break the information into smaller pieces (PAQUETS) and then reassemble it.

/!\  Everything connected directly/indirectly to internet has an IP Address( computers, servers, cellphones, equipment in between). At every intersection with internet, there is a router helping each paquets getting one step closer to its destination.

/!\  it's the ISP that gives an IP address to the equipment

/!\  Internet usses DNS (phonebook) : equivalence between the IP address and the domain name.


> Internet : is a large network of computers which communicate all together and whatever happens, they find a way to stay connected.

> Protocols : Management of the flow of the data paquets. They set the rules for data paquets conversion, attachment of the source and destination addresses to each paquet and the rules for routers ...

# Commands 

> netstat -pn (deprecated, replace by SS) : lists all the connections made by Unix Sockets or netstat -lpn for listenning sockets

> lsof : list open files on unix system

