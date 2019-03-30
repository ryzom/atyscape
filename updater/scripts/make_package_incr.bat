rmdir /S /Q atyscape
del atyscape.zip
c:\python25\python make_packages.py ../../cclient/trunk/bin atyscape atyscape.zip incr
del control.sha
pause