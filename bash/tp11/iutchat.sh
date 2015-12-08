#!/bin/bash

lectureChat=$1
repertoireChat="/home/infoens/beaufils/asr3/chat"

#Lecture
xterm -T "Caisse du chat" -e "tail -f $repertoireChat/$lectureChat" &

#Ecriture
cat | sed s/^/"$USER : "/ >>$repertoireChat/loveChat

#MANQUE : quitter proprement !