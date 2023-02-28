# Introdution to "ft_irc" project

**Goal** : This project is about understanding how an Internet Relay Chat server works.

Internet Relay Chat is a protocol for real-time text messaging between internet-connected computers created in **1988**. It is mainly used for group discussion in chat rooms called “**channels**” although it supports private messages between two users, data transfer, and various client-side commands.
 
**Project requirements**

	- Implement IRC server in C++ 98.
	- Implement multiple clients without hanging.
	- Use only 1 poll() (or equivalent)
	- Implement Non-blocking sockets
	- Use TCP/IP for Client/Server communication
	- Implement authentification, registration (nick/username..), joining rooms/channels, sending and receiving private messages.
	- Implement operators and regular users.
	- Adapt to a specifi IRC Client (we chose IRSSI)


# Commands implemented

1. *Athentification & Registration* : Available for regular users

	- **PASS**: Entering a password.
	
	- **NICK**: Setting a nickname.
	
	- **USER**: Setting an username and realname.
 
 2. *Rooms and Chat* : Available for regulat users
 
	- **PRIVMSG**: Sending message for a one-to-one chat or to all chan users without receiving errors if something's wrong.
	
	- **NOTICE**: Sending message for a one-to-one chat or to all chan users without receiving errors if something's wrong.
	
	- **JOIN**: Accessing/joining a room.
	
	- **TOPIC**: Giving information about a room topic.
	
	- **MODE**: Implementing modes for users.
	
	- **AWAY**: Implementing an away message.
	
	- **INVITE**: Inviting users to join a certain room/chans.
	
	- **NAMES**: Giving information about all users present in a room/chan.
	
	- **PART**: Quitting a chan.
	
	- **QUIT**: Terminating a user session.

3. *Administration/Operations* : Only for Operators

	- **MODE**: Implementing modes for joining some rooms/chans.
	
	- **OPER**: Giving privileges to a certain user.
	
	- **KICK**: Kicking a user from channels.
	
	- **KILL**: Killing a user from the server.
	

# ⚙️ How to use our IRC Server (With IRSSI Client)
To compile the program, use:
  - `make -j re`
  
**To start the Server, use:**

  - `./ircserv <port> <password>`
  
    - **port**: The port number on which your IRC server will be listening to for incoming IRC connections.
    
    - **password**: The connection password. It will be needed by any IRC client that tries to connect to your server.
    
**To connect to the server :**
  - gcl IRSSI in your terminal : (https://github.com/irssi/irssi.git)
  
  - Connect as : irssi --connect 127.0.0.1 --port=<port> --password=<password> --nickname="X" (do it with as many client as you want, don't forget to give different nicknames)
  
  - Let the game begin


# #####


  
Links that helped
-----------
| Subject | Link |
|:--------------|:----------------|

| AF_INET & struct address | https://stackoverflow.com/questions/1593946/what-is-af-inet-and-why-do-i-need-it |

| How internet works | https://www.youtube.com/watch?v=7_LPdttKXPc |

| Socket Types | https://www.ibm.com/docs/pl/aix/7.1?topic=protocols-socket-types |

| Nice guide for Network Programming | [https://www.ibm.com/docs/pl/aix/7.1?topic=protocols-socket-types](https://beej.us/guide/bgnet/pdf/bgnet_usl_c_1.pdf) |

| About socket Blocking | https://dwise1.net/pgm/sockets/blocking.html |

| REUSE PORT | https://blog.flipkart.tech/linux-tcp-so-reuseport-usage-and-implementation-6bfbf642885a |

| Binding to any available port | https://www.baeldung.com/cs/binding-available-ports |

| C10K | [https://trungams.github.io/2020-08-23-a-simple-http-server-from-scratch/](http://www.kegel.com/c10k.html) |

| ePoll | https://suchprogramming.com/epoll-in-3-easy-steps/ |


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
 
 For http, what imports is the transport Layer. It ensures that data is transferred from one point to another reliably and without errors (  making sure data are sent and received in the correct sequence.). The Transport layer provides flow control and error handling, and participates in solving problems concerned with the transmission and reception of packets.

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

> **http servers** : Apache Tomcat, NginX, express JS. First version of HTTP is HTTP/1.1. (latst version is the HTTP/2)

> **CGI**

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

# Main RFCs for basic HTTP 

RFC 2812 

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

7. Difference between POLL/EPOLL/SELECT ?  
	**/!\ They basically provide the same global functionnality (managing multiple sockets and informing when a particular event happens : I/O multiplexing)**

If we classify them by order of appearance :

	- **Select** was the first one to appear in BSD UNIX to check for file descriptor readiness. 
	
	- **Poll** : In each syscall invoke poll() thus needs to copy a lot more over to kernel space. 
	
	- **EPOLL** is a new system call introduced in Linux 2.6. It is designed to replace the **deprecated select** (and also poll). Unlike these earlier system calls, which are O(n), epoll is an O(1) algorithm – this means that it scales well as the number of watched file descriptors increase. select uses a linear search through the list of watched file descriptors, which causes its O(n) behaviour, whereas epoll uses callbacks in the kernel file structure.
	
=> POLL VS SELECT
	
	a) poll( ) does not require that the user calculate the value of the highest- numbered file descriptor +1.
	
	b) poll( ) is more efficient for large-valued file descriptors. Imagine watching a single file descriptor with the value 900 via select()—the kernel would have to check each bit of each passed-in set, up to the 900th bit.
	
	c) select( )’s file descriptor sets are statically sized.
	
	d) With select( ), the file descriptor sets are reconstructed on return, so each subsequent call must reinitialize them. The poll( ) system call separates the input (events field) from the output (revents field), allowing the array to be reused without change.
	
	e) The timeout parameter to select( ) is undefined on return. Portable code needs to reinitialize it. This is not an issue with pselect( ).
	
	f) select( ) is more portable, as some Unix systems do not support poll( )

-> Good resource comparaing poll and select : (https://daniel.haxx.se/docs/poll-vs-select.html#:~:text=select()%20only%20uses%20(at,more%20over%20to%20kernel%20space)

=> EPOLL VS POLL/SELECT
	
	a) We can add and remove file descriptor while waiting.
	
	b) epoll_wait returns only the objects with ready file descriptors.
	
	c) epoll has better performance – O(1) instead of O(n).
	
	d) epoll can behave as level triggered or edge triggered (see man page).
	
	e) epoll is Linux specific so non portable
	
Why did we choose Poll ?

Following the requirements of the subject, we needed an API that can manage multiple file descriptors sets with a good performance and a simpler functionning so Poll was the best option for us.

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
