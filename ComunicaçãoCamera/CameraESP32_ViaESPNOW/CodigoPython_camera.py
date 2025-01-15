## NESSE CÓDIGO ABRE O CAMERA DO PC E USA A BIBLIOTECA OPENCV PARA RECONHECER A MÃO DO USUÁRIO
## PARA SEU FUNCIONAMENTO É NECESSÁRIO CONECTAR O ESP32 MESTRE EM UMA PORTA USB E CONFIGURAR NO CÓDIGO QUAL A COM USADA, NESSE CASO A COM9
## NO SERIAL MONITOR, ATENTAR-SE SE ESTÁ SENDO USADA A PORTA CORRESPONDENTE E O BAUDRATE
##IMPORTANTE: NENHUM OUTRO APLICATIVO PODE SER USADO EM CONJUNTO. PODE DAR CONFLITO NA PORTA USB



import cv2
import cvzone
from cvzone.HandTrackingModule import HandDetector
import serial
import time

# Configuração da porta serial
try:
    ser = serial.Serial('COM9', 115200)  # Substitua 'COM3' pela sua porta serial
    time.sleep(2)  # Tempo para garantir que a conexão foi estabelecida
except Exception as e:
    print(f"Erro ao conectar na porta serial: {e}")
    exit()

# Configuração do cvzone para detecção de mãos
cap = cv2.VideoCapture(0)  # Captura da câmera
detector = HandDetector(detectionCon=0.8, maxHands=1)  # Detector de mãos com confiança de 80% e máximo de 1 mão

# Função para processar os dados e enviar ao ESP32 via serial
def enviar_dados(fingers):
    mensagem = f"FINGERS {fingers[0]} {fingers[1]} {fingers[2]} {fingers[3]} {fingers[4]}\n"
    tentativas = 3
    for i in range(tentativas):
        try:
            ser.write(mensagem.encode())  # Envia a mensagem como bytes
            print(f"Dados enviados: {mensagem.strip()}")
            break
        except Exception as e:
            print(f"Tentativa {i + 1}/{tentativas} falhou: {e}")
            time.sleep(1)

# Inicializa variáveis
ultimo_envio = time.time()
intervalo = 2  # Tempo em segundos entre envios
ultima_posicao_fingers = [-1, -1, -1, -1, -1]  # Para armazenar a última posição dos dedos

while True:
    success, img = cap.read()  # Leitura da imagem da câmera
    if not success:
        break

    hands, img = detector.findHands(img)  # Detecção de mãos

    if hands:
        hand1 = hands[0]
        fingers1 = detector.fingersUp(hand1)  # Detecta se os dedos estão levantados ou abaixados

        # Verifica se houve mudança na posição dos dedos ou se passou o intervalo de tempo
        if fingers1 != ultima_posicao_fingers or time.time() - ultimo_envio > intervalo:
            enviar_dados(fingers1)
            ultima_posicao_fingers = fingers1.copy()
            ultimo_envio = time.time()

    cv2.imshow('frame', img)  # Mostra a imagem na tela

    if cv2.waitKey(1) == ord('q'):  # Fechar a janela da imagem ao pressionar a tecla 'q'
        break

cap.release()
ser.close()  # Fecha a conexão serial
cv2.destroyAllWindows()
