make
gcc test/test_jsnd.c _build/jsnd.o -o /tmp/J0001test -Iinclude
gcc test/test_snd.c _build/snd.o _build/jsnd.o -o /tmp/J0002test -Iinclude `pkg-config SDL2_mixer --cflags --libs`
#gcc test/test_full.c _build/snd.o _build/jsnd.o -o test/test_full -Iinclude `pkg-config SDL2_mixer --cflags --libs`
/tmp/./J0001test
echo
echo "next"
echo
/tmp/./J0002test
rm /tmp/./J0002test
rm /tmp/./J0001test
