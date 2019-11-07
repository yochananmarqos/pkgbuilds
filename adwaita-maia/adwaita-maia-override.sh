#!/usr/bin/env dash
cmd=$1
file="${@}"
gtk_theme=$(dconf read /org/gnome/desktop/interface/gtk-theme | tr -d "'")

if [ -z $1 ]; then
	echo "No command given"
	exit 0
fi

if [ $gtk_theme != Adwaita ]; then
	if [ -z "$file" ]; then
		GTK_THEME="${gtk_theme}" exec "$cmd"
	else
		
	fi
else
	exec "$cmd"
fi

GTK_THEME="${gtk_theme}" exec totem "$file"
