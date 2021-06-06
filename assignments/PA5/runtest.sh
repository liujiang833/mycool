#!/bin/bash 
rm -rf ./grading 
perl pa4-grading.pl -x
sed -i 's/\/usr\/class\/cs143\/cool/\.\./g' ./grading/*
perl pa4-grading.pl -r
