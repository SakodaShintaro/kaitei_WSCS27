﻿# 概要
将棋ソフト『海底』はUSIプロトコル準拠の思考エンジンです。

ReleaseされているものはWindows10 64bit環境でのみ動作確認済みです。SDT5バージョンからはbmi、bmi2が使える必要があります。

## 利用方法
使用しているOSがWindowsであれば上方の"Release"タブを選択し、必要な実行ファイルおよび評価パラメータファイルをダウンロードしてお使いください。

ソースコードはgccでコンパイルすることもできます。コンパイルしたいバージョンのディレクトリに入り、makeコマンドを実行してください。  
例)kaiteiをダウンロードしてきてSDT5バージョンをコンパイルする  
  git clone http://github.com/SakodaShintaro/kaitei  
  cd ./kaitei/kaitei_SDT5  
  make  

評価パラメータはReleaseタブからダウンロードしてください。

## 各バージョンの説明
* kaitei_WCSC27  
第27回世界コンピュータ将棋選手権に出場した際のバージョンです。駒割、玉周り8マスの利きの数、盤上の利きの総数から局面の評価を行い、アルファベータ法を基本として探索をしています。検討モードには対応しておりません。レートはhttp://www.uuunuuun.com/ によると715となっています。

* kaitei_mini  
kaitei_WCSC27を改良したものとなります。棋力が多少向上し、検討モードに対応しました。レートは1080ほどと予想されます。

* kaitei_SDT5  
第5回将棋電王トーナメントに出場した際のバージョンです。Bitboardによる盤面情報の管理を導入し、2駒関係をボナンザメソッドで学習させました。レートは1200ほどと予想されます。
