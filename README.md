# ft_irc project 
The goal of this project is to create our own IRC server. This server is capable of accepting multiple connections without blocking and answer multiple client at the same time.
This project is about creating our own IRC server. For testing purposes, we choosed IRSSI as the client part.


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
    > HELP
    > HELLO
    > TIME
    > TALK
    > SHAKE

# 🔑 Our IRC Commands
These are the available commands in our IRC Server:
  - **PASS**: for entering the server
  - **NICK**: for getting recognized throughout the server
  - **USER**: for specifying the username, hostname and realname of a new user.
  - **OPER**: for obtaining operator privileges.
  - **MODE**: for changing user modes
  - **QUIT**: for quitting a client session. The client is no more on the server but his nickname is registered and can't be used anymore
  - **JOIN**: for joining from one to many channels. If the channel doesn't exist, the user became the owner/operator
  - **PART**: for leaving one or more channels registered in
  - **TOPIC**: for giving the topic of the channel if it exists
  - **KICK**: for kicking a user from a channel. The user that wants to kick has to be operator of the channel.
  - **PRIVMSG**: for sending private messages to another user. If the user we want send to, is away, the user sending the PRIVMSG receives the away message
  - **NOTICE**: for sending private messages to another user. If the user we want send to, is away, the user sending the NOTICE doesn't receive the away message
  - **RESTART**: for restarting the server
  - **KILL**: for killing a client session.Only operators of the server can do this 
  - **MARVIN*: for starting the bot

# ⚙️ Start IRC Server
To compile the program, use:
  - `make`
To start the Server, use:
  - `./ircserv <port> <password>`
    - **port**: The port number on which your IRC server will be listening to for incoming IRC connections.
    - **password**: The connection password. It will be needed by any IRC client that tries to connect to your server.
To connect to the server, you can use:
  - `nc <IP ADDRESS> <PORT>`
    - **IP ADDRESS**: Host IP address.
    - **PORT**: The PORT that the server listening on.
  - You can also use an IRC Client e.g LimeChat, WeeChat...

# 💪 Contributers

[BARI Mehdi](https://github.com/barimehdi77)<br/>
&emsp;42intra profile : [mbari](https://profile.intra.42.fr/users/mbari) <br/>
<br/>
[SFAIHI Abderrahmane](https://github.com/AbderrSfa)
<br/>
&emsp;42intra profile : [asfaihi](https://profile.intra.42.fr/users/asfaihi)
<br/>
<br/>
[EL KEMMAL Abdelhamid](https://github.com/abdel-ke)
<br/>
&emsp;42intra profile : [abdel-ke](https://profile.intra.42.fr/users/abdel-ke)


# 👨‍💻 Ressources
* [What is a Socket?](https://www.tutorialspoint.com/unix_sockets/what_is_socket.htm)
* [Unix Socket - Network Addresses](https://www.tutorialspoint.com/unix_sockets/network_addresses.htm)
* [Unix Socket - Core Functions](https://www.tutorialspoint.com/unix_sockets/socket_core_functions.htm)
* [Beej's Guide to Network Programming](https://beej.us/guide/bgnet/html/)
* [The UChicago χ-Projects](http://chi.cs.uchicago.edu/chirc/index.html)
* [Internet Relay Chat Protocol](https://datatracker.ietf.org/doc/html/rfc1459)
* [Internet Relay Chat: Architecture](https://datatracker.ietf.org/doc/html/rfc2810)
* [Internet Relay Chat: Channel Management](https://datatracker.ietf.org/doc/html/rfc2811)
* [Internet Relay Chat: Client Protocol](https://datatracker.ietf.org/doc/html/rfc2812)
* [Internet Relay Chat: Server Protocol](https://datatracker.ietf.org/doc/html/rfc2813)

---
[!["Buy Me A Coffee"](https://www.buymeacoffee.com/assets/img/custom_images/orange_img.png)](https://www.buymeacoffee.com/barimehdi77)
[![ko-fi](https://ko-fi.com/img/githubbutton_sm.svg)](https://ko-fi.com/K3K45UOA7)
[![paypal](https://www.paypalobjects.com/en_US/i/btn/btn_donateCC_LG.gif)](https://paypal.me/barimehdi77)
