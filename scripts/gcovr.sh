
if [ $# -eq 0 ]
then
    path=".."
elif [ "$1" == "cmake" ]
then
    path="../.."
fi


gcovr -r "$path/." --filter "$path/src/" --exclude "$path/src/main.cpp"
gcovr -r "$path/." --filter "$path/src/" --exclude "$path/src/main.cpp" --html -o ../cov_report.html
