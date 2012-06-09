@echo off
bcc32 barcode.c xbm.c code39.c kix.c code128.c
barcode code128 0123 www.degrunt.nl >barcode.xbm
