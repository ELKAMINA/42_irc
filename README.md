# Introdution to "Webserv" project

**Goal** : 

This project is about writing our own HTTP server and test it with an actual browser.

**Project requirements**




**Requirements**
  
  

# To start :

# #####


  
Links that helped
-----------
| Subject | Link |
|:--------------|:----------------|

| HTTP server from scratch |  https://medium.com/from-the-scratch/http-server-what-do-you-need-to-know-to-build-a-simple-http-server-from-scratch-d1ef8945e4fa / https://bhch.github.io/posts/2017/11/writing-an-http-server-from-scratch/


# Global glossary

> RFC = Requests for comments. set of informations, documents and norms that standardize, describe, specify regarding network in general.
  
> OSI : Open Systems Interconnection model (OSI model) is a conceptual model that characterizes and standardizes the communication functions of a telecommunication or computing system without regard to its underlying internal structure and technology. Its goal is the interoperability of diverse communication systems with standard protocols.  The model partitions a communication system into abstraction layers. Original version of the model defines 7 layers :
  - physical
  - Data link
  - Network
  - Transport
  - Session 
  - Presentation
  - Application
 
 For http, what imports is the transport Layer. It ensures that data is transferred from one point to another reliably and without errors (  making sure data are sent and received in the correct sequence.). The Transport layer provides flow control and error handling, and participates in solving problems concerned with the transmission and reception of packets.
 
> TCP/IP :  Transmission Control Protocol (TCP) vs User Datagram Protocol (UDP) vs Sequenced Packet Exchange (SPX).
HTTP communication usually takes place over TCP/IP connections. The default port is TCP 80, but other ports can be used. This does not preclude HTTP from being implemented on top of any other protocol on the Internet, or on other networks. but any reliable transport can be used with http protocol.

> http servers : Apache Tomcat, NginX, express JS

> CGI 
