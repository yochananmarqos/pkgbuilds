#!/bin/bash

_site_packages=$(python -c "import site; print(site.getsitepackages()[0])")

gksu "$_site_packages"/keyboard-color-switcher/keyboard-color-switcher.py
