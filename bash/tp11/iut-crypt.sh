#!/bin/bash

lectureChat=$1
repertoireChat="/home/infoens/beaufils/asr3/chat"

#Lecture
#xterm -T "Caisse du chat" -e "tail -f $repertoireChat/$lectureChat" &
xterm -T "Caisse du chat decrypte" -e "tail -fq $repertoireChat/$lectureChat | tr mlkjhgfdsqnbvcxwpoiuytreza abcdefghijklmnopqrstuvwxyz" &

#Ecriture
xterm -T "Ecrire" -e "sed -u -e s/^/\"$USER : \"/ -e y/abcdefghijklmnopqrstuvwxyz/mlkjhgfdsqnbvcxwpoiuytreza/ >>$repertoireChat/loveChat"
echo $USER has left.>>$repertoireChat/loveChat

kill -9 $!
