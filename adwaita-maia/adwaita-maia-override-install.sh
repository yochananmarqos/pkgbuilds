#!/bin/bash

workdir=/usr/share/applications
prgs=(org.gnome.Totem eog celluloid shotwell org.gnome.gthumb)

for i in "${prgs[@]}"; do
	echo "$workdir/"$i".desktop"
	if [[ -f $workdir/"$i".desktop ]]; then
		sed -i.bck "/adwaita-maia-override/! s/^Exec=/Exec=adwaita-maia-override\ /g" $workdir/$prgs.desktop
	fi
done
