# Introdution to "Webserv" project

**Goal** : 

This project is about writing our own HTTP server and test it with an actual browser.

**Project requirements**




**Requirements**
  
  

# Steps to follow :

1. Implement TCP :
2. 

# #####


  
Links that helped
-----------
| Subject | Link |
|:--------------|:----------------|

| HTTP server from scratch |  https://medium.com/from-the-scratch/http-server-what-do-you-need-to-know-to-build-a-simple-http-server-from-scratch-d1ef8945e4fa / https://bhch.github.io/posts/2017/11/writing-an-http-server-from-scratch/ |

| Nginx Server and Location block | https://www.digitalocean.com/community/tutorials/understanding-nginx-server-and-location-block-selection-algorithms |

| AF_INET & struct address | https://stackoverflow.com/questions/1593946/what-is-af-inet-and-why-do-i-need-it |

| How internet works | https://www.youtube.com/watch?v=7_LPdttKXPc |

| Socket Types | https://www.ibm.com/docs/pl/aix/7.1?topic=protocols-socket-types |

| Nice guide for Network Programming | [https://www.ibm.com/docs/pl/aix/7.1?topic=protocols-socket-types](https://beej.us/guide/bgnet/pdf/bgnet_usl_c_1.pdf) |

| About socket Blocking | https://dwise1.net/pgm/sockets/blocking.html |

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

Link : https://stackoverflow.com/questions/11129212/tcp-can-two-different-sockets-share-a-port


# Main RFCs for basic HTTP 

**7230** : 

**793** : TCP/IP and Sockets
  > *Idea 1* : TCP is to provide reliable, securable logical circuit or connection service between pairs of processes. To provide this services, there are 6 basics :
    - Basic Data Transfer : The TCP is able to transfer a continuous stream of octets in each direction between its users by packaging some       number of octets into segments for transmission through the internet system ( see push function)
    - Reliability
    - Flow control
    - Multiplexing
    - Connections
    - Precedence and Security

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


# Issues

1. Bind results in a permission denied when using port 81 

Quick answer : Ports below 1024 are considered to be privileged in Linux,

  **Rep : https://stackoverflow.com/questions/31899673/bind-returning-permission-denied-c**

2. Failed to connect: Socket operation on non-socket

**Rep**: https://www.sendblaster.com/support/error-trapping/socket-operation-a-non-socket-error/#:~:text=The%20%E2%80%9CSocket%20operation%20on%20a%20non%2Dsocket%E2%80%9D%20error%20means,has%20been%20shut%20down%20abruptly.

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
