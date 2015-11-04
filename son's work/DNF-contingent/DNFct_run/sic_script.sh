#!/bin/sh

echo 
echo Creating dp.pddl file from $1 and $2
cat $1 $2 > dp.pddl

./cpa.pddl2pl dp.pddl

echo Performing statistical analysis ...
cat mult5zsic.pl pddl2pl.pl > new.pl
sicstus -l new.pl --goal 'main,halt.' <input > trash 

echo Running DNFct ...
./DNFct theory_0.al > temp

sed -e 's/cpa_//g' temp > plan-result

cat plan-result 

