#!/bin/bash

workdir=/usr/share/applications
prgs=(eog celluloid shotwell totem)


for i in $prgs; do
	if [[ -f $workdir/$prgs.desktop ]]; then
		sed -i.bck "/Exec/d" $workdir/$prgs.desktop
		echo "Exec=/usr/bin/adwaita-maia-override $prgs %U" >> $workdir/$prgs.desktop
	fi
done



