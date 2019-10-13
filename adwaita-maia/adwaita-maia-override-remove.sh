#!/bin/bash

workdir=/usr/share/applications
prgs=(eog celluloid shotwell)


for i in $prgs; do
	if [[ -f $workdir/$prgs.desktop ]]; then
		rm -f $workdir/$prgs.desktop
		mv $workdir/$prgs.desktop.bck $workdir/$prgs.desktop
	fi
done



