#! /bin/bash
function fix_link_path() {
    bin_file=$1
    echo "fix link bin file: $bin_file"
    for lib in `otool -L $bin_file | grep "/usr/local/" | grep -v ${bin_file##*/} | awk '{print $1}'`;
    do
        lib_name=${lib##*/}
        echo " + fix link library $lib_name"
        new_link_path="@executable_path/../Frameworks/$lib_name"
        install_name_tool -change $lib $new_link_path $bin_file
    done
}


function copy_library() {
    bin_file=$1
    bin_path=$2
    echo "resolve bin file: $bin_file"
    for lib in `otool -L $bin_file | grep "/usr/local/" | grep -v ${bin_file##*/} | awk '{print $1}'`;
    do
        echo " - copy library $lib"
        cp -n $lib $bin_path/${lib##*/}
        if [ $? -eq 0 ]; then
            chmod 777 $bin_path/${lib##*/}
            copy_library $bin_path/${lib##*/} $bin_path
        fi
    done
}


exe_path=bin/FlvParser.app/Contents/MacOS/FlvParser
framework_path=bin/FlvParser.app/Contents/Frameworks
mkdir -p $framework_path
copy_library $exe_path $framework_path
fix_link_path $exe_path
for lib in `ls -1 $framework_path`;
do 
    fix_link_path $framework_path/$lib
done


