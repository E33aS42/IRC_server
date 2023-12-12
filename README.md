# A command line chat server based on the IRC (Internet Relay Chat)

# Instructions:
1. run *make* in the file folder
2. launch the irc server:
   `> .`/ircserv `<portnumber`> `<password`>
   
4. Launch one or more client server windows (or any computer on the same local network) such as irssi or netcat and connect to the chat server:
  .with irssi, type in the command line:
     > irssi
     
     in the irssi command line, type:
     > /connect <hostmachineaddress> <portnumber> <password>
  .with netcat, type in the command line:
     > nc <hostmachineaddress> <portnumber>
     > user <username> <hostname> <servername> <realname>
     > nick <nickname>
     > pass <password>
6. the following commands have been implemented and can be used in the client with the chat server:
   JOIN
   KICK
   MODE
   MOTD
   NAMES
   NICK
   NOTICE
   OPER
   PART
   PASS
   PING
   PONG
   PRIVMSG
   QUIT
   TOPIC
   USER
   WHOIS
   
