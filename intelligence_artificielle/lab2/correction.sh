#!/bin/sh

echo $#
if [ $# -lt 1 ]
then
    echo "Usage: %0 g1"
    exit 1
fi

pause() {
    echo "Hit a key."
    read a
}

for i in ../$1/*.py
do

cp $i solvers.py
name=`basename $i`
echo
echo
echo
echo
echo

echo $name

echo "##################################################################"
echo "** Exercise 1: Forward Checking (/X)"
pause
python sudoku.py -s CSPSolver1 -g grid5 -m -t 30 -c
echo "##################################################################"
echo "** Exercise 2: Arc consistency (/X)"
pause
python sudoku.py -s CSPSolver2  -g grid5 -t 30 -c
echo "##################################################################"
echo "** Exercise 3: heuristics (/4)"
pause
python sudoku.py -s CSPSolver1 -g grid5 -f myHeuristic -m -t 30 -c
echo "##################################################################"
echo "** Exercise 4 Maintening Arc Consistenct (/3)"
pause
python sudoku.py -s CSPSolver3 -g grid5 -f myHeuristic -m -t 30 -c

pause
mv $i ../done/$1/$name
done
