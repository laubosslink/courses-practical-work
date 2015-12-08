#!/bin/bash

lectureChat=$1
repertoireChat="/home/infoens/beaufils/asr3/chat"

#Lecture
xterm -T "Caisse du chat" -e "tail -f $repertoireChat/$lectureChat" &

#Ecriture
xterm -T "Ecrire" -e "cat | sed -u s/^/\"$USER : \"/>>$repertoireChat/loveChat; echo \"$USER has left.\" >>$repertoireChat/loveChat"

