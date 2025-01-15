//NESSE CÓDIGO ELE RECEBE AS INFORMAÇÕES VIA ESPNOW DO ESP32 MESTRE
//RECEBE A STRING E REPRODUZ O MOVIMENTO DOS DEDOS NOS SERVOS
// OS PARAMETROS RECEBIDOS SÃO 0 OU 1; A ANGULAÇÃO PODE MUDAR CONFORME A TRAÇÃO NA ESTRURTURA



#include <esp_now.h>
#include <WiFi.h>
#include <ESP32Servo.h>

// Definindo os pinos para os servos
#define SERVO_PIN_1 13
#define SERVO_PIN_2 12
#define SERVO_PIN_3 14
#define SERVO_PIN_4 27
#define SERVO_PIN_5 26

Servo servo1, servo2, servo3, servo4, servo5;

void OnDataRecv(const esp_now_recv_info_t *recvInfo, const uint8_t *data, int data_len) {
    char msg[data_len + 1];
    memcpy(msg, data, data_len);
    msg[data_len] = '\0';

    int fingers[5];
    sscanf(msg, "FINGERS %d %d %d %d %d", &fingers[0], &fingers[1], &fingers[2], &fingers[3], &fingers[4]);

    // Controla os servos de acordo com os dedos recebidos
    servo1.write(fingers[0] == 1 ? 0 : 90);
    servo2.write(fingers[1] == 1 ? 0 : 90);
    servo3.write(fingers[2] == 1 ? 0 : 90);
    servo4.write(fingers[3] == 1 ? 0 : 90);
    servo5.write(fingers[4] == 1 ? 0 : 90);
}

void setup() {
    Serial.begin(115200);
    
    // Inicializa os servos
    servo1.attach(SERVO_PIN_1);
    servo2.attach(SERVO_PIN_2);
    servo3.attach(SERVO_PIN_3);
    servo4.attach(SERVO_PIN_4);
    servo5.attach(SERVO_PIN_5);

    // Inicializa o ESP-NOW
    WiFi.mode(WIFI_STA);
    if (esp_now_init() != ESP_OK) {
        Serial.println("Erro ao inicializar ESP-NOW");
        return;
    }

    esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
    // Não há necessidade de código no loop, tudo é feito no callback
}
