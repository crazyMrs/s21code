#!/bin/bash

SUCCESS=0
FAIL=0
COUNTER=0
DIFF_RES=""

declare -a tests=(
"s VAR test_0_grep.txt"
"for VAR s21_grep.c s21_grep.h"
"for VAR s21_grep.c"
"-e for VAR s21_grep.c s21_grep.h"
"-e for -e ^int VAR s21_grep.c"
"-e regex s21_grep.c VAR test_ptrn_grep.txt"
"-e while -e void s21_grep.c VAR test_ptrn_grep.txt"
)

declare -a extra=(
"-n for test_1_grep.txt test_2_grep.txt"
"-n for test_1_grep.txt"
"-n -e ^\} test_1_grep.txt"
"-c ^int test_1_grep.txt test_2_grep.txt"
"-e ^int test_1_grep.txt"
"-n = test_1_grep.txt test_2_grep.txt"
"-e"
"-i INT test_5_grep.txt"
"-r test_1_grep.txt test_2_grep.txt"
"-n = -e out test_5_grep.txt"
"-v int test_5_grep.txt"
"-i int test_5_grep.txt"
"-c -l aboba test_1_grep.txt test_5_grep.txt"
"-v test_1_grep.txt -e ank"
"-n ) test_5_grep.txt"
"-l for test_1_grep.txt test_2_grep.txt"
"-e int test_4_grep.txt"
"-l for no_file.txt test_2_grep.txt"
)

testing()
{
    t=$(echo $@ | sed "s/VAR/$var/")
    ./s21_grep $t > test_s21_grep.log
    grep $t > test_sys_grep.log
    DIFF_RES="$(diff -s test_s21_grep.log test_sys_grep.log)"
    (( COUNTER++ ))
    if [ "$DIFF_RES" == "Files test_s21_grep.log and test_sys_grep.log are identical" ]
    then
      (( SUCCESS++ ))
      echo "\033[31m$FAIL\033[0m/\033[32m$SUCCESS\033[0m/$COUNTER \033[32msuccess\033[0m grep $t"
    else
      (( FAIL++ ))
      echo "\033[31m$FAIL\033[0m/\033[32m$SUCCESS\033[0m/$COUNTER \033[31mfail\033[0m grep $t"
    fi
    rm test_s21_grep.log test_sys_grep.log
}

# спец тесты
for i in "${extra[@]}"
do
    var="-"
    testing $i
done

# 1 параметр
for var1 in v c l n s h
do
    for i in "${tests[@]}"
    do
        var="-$var1"
        testing $i
    done
done

# 2 параметра
for var1 in v c l n s h
do
    for var2 in v c l n s h
    do
        if [ $var1 != $var2 ]
        then
            for i in "${tests[@]}"
            do
                var="-$var1 -$var2"
                testing $i
            done
        fi
    done
done

# 3 параметра
for var1 in v c l n s h
do
    for var2 in v c l n s h
    do
        for var3 in v c l n s h
        do
            if [ $var1 != $var2 ] && [ $var2 != $var3 ] && [ $var1 != $var3 ]
            then
                for i in "${tests[@]}"
                do
                    var="-$var1 -$var2 -$var3"
                    testing $i
                done
            fi
        done
    done
done

#2 сдвоенных параметра
for var1 in v c l n
do
    for var2 in v c l n h
    do
        if [ $var1 != $var2 ]
        then
            for i in "${tests[@]}"
            do
                var="-$var1$var2"
                testing $i
            done
        fi
    done
done

echo "\033[31mFAIL: $FAIL\033[0m"
echo "\033[32mSUCCESS: $SUCCESS\033[0m"
echo "ALL: $COUNTER"
