#!/bin/bash
case $1 in
    pa02.c)
	rm -f -- pa02
	gcc pa02.c 
	if [ $? -ne 0 ]; then 
	    echo "Compile of pa02.c failed"
	    echo "Good bye!"
	    exit 1 
	fi
	EXE="./pa02"
	;;
    pa02.cpp)
	rm -f -- pa02
	g++ pa02.cpp -o pa02
	if [ $? -ne 0 ]; then 
	    echo "Compile of pa02.cpp failed"
	    echo "Good bye!"
	    exit 1 
	fi
	EXE="./pa02"
	;;
    pa02.go)
	rm -f -- pa02
	go build pa02.go
	if [ $? -ne 0 ]; then 
	    echo "Compile of pa02.go failed"
	    echo "Good bye!"
	    exit 1 
	fi
	EXE="./pa02"
	;;
    pa02.java)
	rm -f -- pa02.class
	javac pa02.java
	if [ $? -ne 0 ]; then 
	    echo "Compile of pa02.java failed"
	    echo "Good bye!"
	    exit 1 
	fi
	EXE="java pa02"
	;;
    pa02.py)
	EXE="python3 pa02.py"
	;;
    pa02.rs)
    rm -f -- pa02
    rustc pa02.rs
    if [ $? -ne 0 ]; then
        echo "Compile of pa02.rs failed"
        echo "Good bye!"
        exit 1
    fi
    EXE="./pa02"
  ;;
    *)
    echo "Invalid source file name"
    echo "->  should be pa02.c, pa02.cpp, pa02.go, pa02.java, pa02.py or pa02.rs"
    exit 1
esac

echo "Compile of pa02 succeded."

echo "Case #1"
eval $EXE k1.txt p1.txt >stu1Output.txt
diff -w stu1Output.txt base1.txt
echo "Case #1 - complete"

echo "Case #2"
eval $EXE k2.txt p2.txt >stu2Output.txt
diff -w stu2Output.txt base2.txt
echo "Case #2 - complete"

echo "Case #3"
eval $EXE k3.txt p3.txt >stu3Output.txt
diff -w stu3Output.txt base3.txt
echo "Case #3 - complete"

echo "Case #4"
eval $EXE k4.txt p4.txt >stu4Output.txt
diff -w stu4Output.txt base4.txt
echo "Case #4 - complete"

echo "Case #5"
eval $EXE k5.txt p5.txt >stu5Output.txt
diff -w stu5Output.txt base5.txt
echo "Case #5 - complete"
