<!--
Please Keep this comment on the top of this file

How to write Changelog
-----------------------

https://keepachangelog.com/ja/1.0.0/ に基づいて記述していく

- Merge Request毎に記述を追加していく
- 何を変更したかを要約して書く。以下の分類を使う
  - Added      新機能について。
  - Changed    既存機能の変更について。
  - Deprecated 間もなく削除される機能について。
  - Removed    今回で削除された機能について。
  - Fixed      バグ修正について。
  - Security   脆弱性に関する場合。

-->

Unreleased
-----------
### Added

### Changed

### Fixed
- fix doxygen typo https://github.com/t-hishinuma/DD-AVX_v3/pull/39

2.1.0 - 2020/12/31
-----------
### Added
- create CRS from CRS or COO vectors https://github.com/t-hishinuma/DD-AVX_v3/issues/19
- add doxygen comment https://github.com/t-hishinuma/DD-AVX_v3/issues/36
- add changelog https://github.com/t-hishinuma/DD-AVX_v3/issues/32
- add generate doxygen in github actions https://github.com/t-hishinuma/DD-AVX_v3/issues/31

### Changed
- change MIT -> apache 2.0 license

### Fixed
- delete unnecessary cast https://github.com/t-hishinuma/DD-AVX_v3/pull/30

2.0.0 - 2020/10/10
-----------
### Added
- Support AVX512 and add Makefile.avx512 https://github.com/t-hishinuma/DD-AVX_v3/pull/27

### Removed 
- delete size_t option, only support int32

1.0.0 - 2020/09/07
-----------
### Added
- support Mixed precision
- support AVX/AVX2
- support BLAS Lv.1 and SpMV functions
