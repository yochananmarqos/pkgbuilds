#!/usr/bin/bash
cd /usr/share/savedesktop
if [ "$1" == "" ]
then 
  python /usr/share/savedesktop/main_window.py
elif [ "$1" == "--background" ]
  then
    echo "Periodic saving is currently only supported in Flatpak."
fi

cd
