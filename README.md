# DD-AVX Library: Library of High Precision Sparse Matrix Operations Accelerated by SIMD AVX2

## About
DD-AVXは高速・簡単なインタフェースでDouble / Double-Double精度を組み合わせて使うことを目的としたライブラリである。

AVX2(+FMA), OpenMPによる高速化がされている。

現状では、AVX2やOpenMPの無効化はできない。(OpenMPのスレッド数を変更したい場合は環境変数にて行うこと)

# Build and Install

以下のコマンドでビルドおよびインストールができる:

```
> make
> make install
```

submoduleとしてスカラ演算のためのQDライブラリが必要で、`make`でgitを使って自動的にダウンロードされる。
インストール先は`DD\AVX_DIR`および`DD_AVX_INC`によって指定できる。QDもここにインストールされる。

# Document

Doxygenにて生成する．

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

# Restrictions
* BCRS形式への変換ルーチンは現在はマルチスレッド化して作り直そうと思っているため動作しない
* OpenMPのON/OFF切り替えはできない
