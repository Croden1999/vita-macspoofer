(
cd user;
cmake ./ && make;
rm -rf CMakeFiles && rm cmake_install.cmake && rm CMakeCache.txt && rm Makefile;
rm security_settings.xml.o && rm user && rm user.velf;
rm peripherals_settings.xml.o && rm user_tv && rm user_tv.velf;
rm macspoofer.suprx.out && rm macspoofer_tv.suprx.out;
mv macspoofer.suprx ../macspoofer.suprx;
mv macspoofer_tv.suprx ../macspoofer_tv.suprx;
echo "";
echo "DONE!";
echo "";
)
