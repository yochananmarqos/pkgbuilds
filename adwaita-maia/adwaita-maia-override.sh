#/usr/bin/env dash
cmd=$1
gtk_theme=$(dconf read /org/gnome/desktop/interface/gtk-theme | tr -d "'")
if [ $gtk_theme != Adwaita ] && [ $DESKTOP_SESSION = "gnome" ]; then
	GTK_THEME=${gtk_theme} exec $1
else
	exec $1
fi
