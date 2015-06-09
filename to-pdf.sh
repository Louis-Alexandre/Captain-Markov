#!/bin/bash
(
cd ./r/
for f in ./*.r 
do
  R CMD BATCH $f
  rm $f
done

for f in ./*.r.Rout
do
  rm $f
done
)