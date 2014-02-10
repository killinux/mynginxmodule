#!/bin/sh
nohup /usr/local/java/jdk1.6.0_45/bin/java -cp .:./WebSocket.jar ChatServer >>/data/haoning/mygit/mynginxmodule/nodejs/websocket/java/websocket.log  2>&1 &