release_dir=$1
ldd $release_dir/bin/*.exe|grep -iv system32|grep -vi windows|grep -v :$  | cut -f2 -d\> | cut -f1 -d\( | tr '\\' '\/' |while read a; do ! [ -e "$release_dir/bin/`basename $a`" ] && cp -v "$a" $release_dir/bin/; done
ldd $release_dir/bin/*.dll|grep -iv system32|grep -vi windows|grep -v :$  | cut -f2 -d\> | cut -f1 -d\( | tr '\\' '\/' |while read a; do ! [ -e "$release_dir/bin/`basename $a`" ] && cp -v "$a" $release_dir/bin/; done
ldd $release_dir/plugins/*/*.dll|grep -iv system32|grep -vi windows|grep -v :$  | cut -f2 -d\> | cut -f1 -d\( | tr '\\' '\/' |while read a; do ! [ -e "$release_dir/bin/`basename $a`" ] && cp -v "$a" $release_dir/bin/; done
exit 0
