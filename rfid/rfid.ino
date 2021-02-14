// #define UID "4C 06 7A 32"
// #define UID "DC 96 82 33"
// #define UID "8C 9A 80 32"

#include <SPI.h>
#include <MFRC522.h>

constexpr uint8_t RST_PIN = 9;
constexpr uint8_t SS_PIN = 10;

#define UID_1 "4C 06 7A 32" // 取得した識別子を記述
#define UID_2 "DC 96 82 33" // 取得した識別子を記述
#define UID_3 "8C 9A 80 32" // 取得した識別子を記述


int led_blue = 8;
int led_red = 3;

MFRC522 mfrc522(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key key;

void setup() {
  Serial.begin(9600);
  pinMode(led_blue, OUTPUT);
  pinMode(led_red, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  while (!Serial);
  SPI.begin();
  mfrc522.PCD_Init();
  mfrc522.PCD_DumpVersionToSerial();
  Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));

  dump_byte_array(key.keyByte, MFRC522::MF_KEY_SIZE);
}

void loop() {
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  String strBuf[mfrc522.uid.size];
  Serial.println(mfrc522.uid.size);
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    strBuf[i] =  String(mfrc522.uid.uidByte[i], HEX);
    Serial.println(strBuf[i]);
    if (strBuf[i].length() == 1) {
      strBuf[i] = "0" + strBuf[i];
    }
  }

  String strUID = strBuf[0] + " " + strBuf[1] + " " + strBuf[2] + " " + strBuf[3];
  Serial.println(strUID);
  if ( strUID.equalsIgnoreCase(UID_1) ) {
    Serial.println("耳標番号：１０００の牛です");
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)(5V)
    delay(3000); // 1秒待つ
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW(0V)
  } else if (strUID.equalsIgnoreCase(UID_2)) {
    Serial.println("耳標番号：２０００の牛です");
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)(5V)
    delay(3000); // 1秒待つ
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW(0V)
  } else if (strUID.equalsIgnoreCase(UID_3)) {
    Serial.println("耳標番号：３０００の牛です");
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)(5V)
    delay(3000); // 1秒待つ
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW(0V)
  }else {
    Serial.println("登録されていない耳標です。");
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)(5V)
    delay(3000); // 1秒待つ
    digitalWrite(LED_BUILTIN, LOW);
  }
}

void dump_byte_array(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
}
