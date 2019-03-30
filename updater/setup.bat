rmdir /S /Q innosetup\src
mkdir innosetup\src

rmdir /S /Q build_updater
rmdir /S /Q dist_updater
c:\python25\python setup_updater.py install > setup.log
move build build_updater
move dist dist_updater

rmdir /S /Q build_patcher
c:\python25\python setup.py install >> setup.log
move build build_patcher
xcopy /E /Y dist innosetup\src\updater

copy dist_updater\atyscape.exe innosetup\src\updater
copy atyscape.cf_ innosetup\src\updater
copy atyscape_user.cfg_ innosetup\src\updater\atyscape_user.cfg
mkdir innosetup\src\updater\imgs
xcopy /E /Y imgs innosetup\src\updater\imgs
rem copy unzip.exe innosetup\src
copy msvcp71.dll innosetup\src\updater
copy gdiplus.dll innosetup\src\updater
copy launcher.exe.manifest innosetup\src\updater
copy atyscape.exe.manifest innosetup\src\updater

mkdir innosetup\src\updater\directx\
copy dxwebsetup.exe innosetup\src\updater\directx\

cd scripts
rmdir /S /Q atyscape
del atyscape.zip
c:\python25\python make_packages.py ../../cclient/trunk/bin atyscape atyscape.zip full
cd ..

xcopy /E /Y  scripts\atyscape innosetup\src\

pause