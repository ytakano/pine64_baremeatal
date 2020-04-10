# pine64_baremeatal
 baremetal sample on PINE6

## 開発環境の準備

- sudo apt install gcc-arm-none-eabi u-boot-tools

## ハードウェアの接続
シリアルはUART0,LEDはPB2を使っているので、以下のように接続する。

- UART0(USBシリアル等)

  + GND ー＞EXP 10 の9ピン
  + RX  ー＞EXP 10 の7ピン
  + TX  ー＞EXP 10 の8ピン

- LED

  + プラス側 ー＞Euler busの27ピン
  + GND      ー＞Euler busの32ピン


## コンパイル手順

1. SDカードを指す。 
2. （必要なら）Makefileの変数"SD_CARD_PATH"を変える
3. shellで以下を実行すると、コンパイル＆書き込み

````
make write
```` 

