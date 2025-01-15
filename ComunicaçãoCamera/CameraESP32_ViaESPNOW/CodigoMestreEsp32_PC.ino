//ESSE CÓDIGO É PARA SER RODADO NO ARDUINO IDE
//Código para o esp Mestre: recebe dados do Python e manda para o ESCRAVO
//Verificar qual endereço MAC do Escravo 


#include <esp_now.h>
#include <WiFi.h>

uint8_t broadcastAddress[] = {0xB0, 0xA7, 0x32, 0x14, 0xDB, 0x1C};  // Endereço MAC do dispositivo receptor (substitua pelo correto)

void setup() {
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);

    if (esp_now_init() != ESP_OK) {
        Serial.println("Erro ao inicializar ESP-NOW");
        return;
    }

    esp_now_peer_info_t peerInfo;
    memcpy(peerInfo.peer_addr, broadcastAddress, 6);
    peerInfo.channel = 0;  
    peerInfo.encrypt = false;

    if (esp_now_add_peer(&peerInfo) != ESP_OK) {
        Serial.println("Erro ao adicionar o peer");
        return;
    }
}

void loop() {
    if (Serial.available()) {
        String incomingMessage = Serial.readStringUntil('\n');  // Lê a mensagem até encontrar uma nova linha
        char message[50];
        incomingMessage.toCharArray(message, 50);

        esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *)message, strlen(message));
        if (result == ESP_OK) {
            Serial.println("Dados enviados via ESP-NOW com sucesso");
        } else {
            Serial.println("Erro ao enviar dados via ESP-NOW");
        }
    }
}
