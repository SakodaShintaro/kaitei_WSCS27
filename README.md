# kaitei

将棋ソフト『海底』はUSIプロトコル準拠の思考エンジンです。

ReleaseされているものはWindows10 64bit環境でのみ動作確認済みです。

WCSC27
駒割、玉周り8マスの利きの数、盤上の危機の総数から局面の評価を行い、アルファベータ法を基本として探索をしています。
検討モードには対応しておりません。


SDT5
2駒関係をボナンザメソッドにより学習した評価関数を利用しています。また盤面の情報はBitboardで保持しています。
検討モードにも対応しましたが、MultiPVには対応していません。