#!/bin/sh
rm theory_*.al

#Sicstus-Prolog
/usr/bin/time -f "Total time: %e (seconds)" -o result-time ./sic_script.sh $1 $2

#SWI-Prolog
#/usr/bin/time -f "Total time: %e (seconds)" -o result-time ./swi_script.sh $1 $2

cat result-time
