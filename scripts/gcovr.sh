
script_dir=$(realpath $0)
dir=$(dirname $script_dir)
echo "$dir"
cd $dir/..

gcovr -r . --filter src/. --exclude src/main.cpp
gcovr -r . --filter src/. --exclude src/main.cpp --html -o ../cov_report.html
