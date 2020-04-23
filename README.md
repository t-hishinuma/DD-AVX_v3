# DD-AVX Library (beta): Library of High Precision Sparse Matrix Operations Accelerated by SIMD AVX2
本ライブラリは
[DD-AVX\_v1](https://github.com/t-hishinuma/DD-AVX_v3/)，
[DD-AVX\_v2](https://github.com/t-hishinuma/DD-AVX_v2/)を混合精度に拡張した
高速な混合精度演算ライブラリである．

## About
DD-AVXは高速・簡単なインタフェースでDouble / Double-Double精度を組み合わせて使うことを目的としたライブラリで，
AVX2(+FMA), OpenMPによるBLAS Lv1, Sparse BLASの機能をもち，Krylov部分空間法の実装が簡単に作れる．

独自型として，std::vectorと同様のI/Fで使える以下のベクトル型
* d\_real\_vector
* dd\_real\_vector

および以下のSparse Matrix型が使える
* d\_real\_SpMat
* dd\_real\_SpMat

それぞれの演算は全ての型の組み合わせについて実装されており，D, DDのどちらの型を入力しても動作する．

使い方は[axpyのテストコード](https://github.com/t-hishinuma/DD-AVX_v3/blob/master/test/vector_blas/axpy.cpp)
を見るとわかりやすい．


# Build and Install

以下のコマンドでビルドおよびインストールができる:

```
> make avx2
> make install
```

まだ未実装だが，将来的にAVX512の場合は以下のコマンドでビルドおよびインストールができる:

```
> make avx512
> make install
```

submoduleとしてスカラ演算のためのQDライブラリが必要で、`make`でgitを使って自動的にダウンロードされる。

インストール先は`DD\AVX_DIR`およびによって指定できる。QDもここにインストールされる。

## Current Status and Restrictions
現在はβ版で，いくつかの制約や変更予定箇所がある．
* templateで明示的に型を切り替えて作りたい場合はtest/の関数を利用する．これらは本体に組み込まれる予定である．
* 現状では、AVX2やOpenMPの無効化はできない。(OpenMPのスレッド数を変更したい場合は環境変数にて行うこと)
	* AVX512に拡張するためにSIMD型の定義とファイル定義を修正中．
* 疎行列クラスのFrontISTR組み込み用に行列の行操作，列操作の実装をしたいのでクラス設計を修正予定．
* レジスタ用のクラスの定義をupdateする
	* SIMD\_REGクラスだとScalarとの共通化がしにくいのでREGクラスにする．
	* コードをもっと書きやすくするためにSIMDクラスのオペレータも定義する
		* SETが問題．ここだけはifdefするしかないのか．．
* BCRS形式への変換ルーチンは現在はマルチスレッド化して作り直そうと思っているため動作しない
* OpenMPのON/OFF切り替えはできない

# Document

Doxygenを用いて生成できる．

# Testing
各機能のテストは一通り揃えている。
`test`ディレクトリにそれぞれ入っている。

```
> cd test; make
```

# 後輩向け：
includeの中はそれぞれ：
* DD-AVX.hpp
BLAS / Sparse BLAS関数の宣言
* DD-AVX\_d\_spmat.hpp
倍精度疎行列型の定義
* DD-AVX\_d\_vector.hpp
倍精度ベクトル型の定義 (std::vector<double>を継承している)
* DD-AVX\_dd\_vector.hpp
倍々精度ベクトル型の定義
* DD-AVX\_AVX2\_core/
AVX2化されたDDのAdd, Mul, 積和演算の実装
* template型の内部演算とオーバーロード型の内部演算が両方実装されている．
どちらも同じ性能なことを確認してある．
切り替えはinclude/DD-AVX.hppのifdefで行う
