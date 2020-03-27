#!/bin/bash

make
echo 実行ファイルを生成しました．
echo

echo 入力してください．
read variable
echo $variable
echo

./1cc $variable > tmp.s
echo アセンブリを生成しました．
echo -------------------------------------
cat tmp.s
echo -------------------------------------
echo

echo コンパイラのテストを行います．
./test.sh
echo

echo テストに合格したので，アセンブラを実行します．
cc -o tmp tmp.s
./tmp

echo 結果は以下のとおりです．
echo -------------------------------------
echo $?
echo -------------------------------------

echo 「実行ファイル」「アセンブリ」を消去します．
make clean
