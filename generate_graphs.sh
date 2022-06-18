#!/bin/sh

for file in output/*.txt; do
	python3 plot_state.py instances/a.txt $file graph/$(basename $file .txt).pdf
	# python3 plot_state.py instances/a.txt $file graph/$(basename $file .txt).pdf
	# echo output/$(basename $file .txt).png
done
