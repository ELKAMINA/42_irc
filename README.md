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

> **Socket** : is the mechanism that most popular operating systems provide to give programs access to the network. It allows messages to be sent and received between applications (unrelated processes) on different networked machines. The sockets mechanism has been created to be independent of any specific type of network. **IP (Internet Protocol), however, is by far the most dominant network and the most popular use of sockets.**

> **Network byte ordering** : convention defines the bit-order of network addresses as they pass through the network
See also : Host byte order (same same)

> **Address family** : The address family configuration options allow you to specify how a particular routing protocol behaves with regards to multiple Layer 3 protocols. An address family can be IPv4, IPv6. An address family configuration simply tells the routing protocol how to deal with routes that are learned via a routing protocol.

# Pending questionning

1. Socket operations are synchronous


# Issues

1. Bind results in a permission denied when using port 81 

Quick answer : Ports below 1024 are considered to be privileged in Linux,

  **Rep : https://stackoverflow.com/questions/31899673/bind-returning-permission-denied-c**

2. Failed to connect: Socket operation on non-socket

**Rep**: https://www.sendblaster.com/support/error-trapping/socket-operation-a-non-socket-error/#:~:text=The%20%E2%80%9CSocket%20operation%20on%20a%20non%2Dsocket%E2%80%9D%20error%20means,has%20been%20shut%20down%20abruptly.
