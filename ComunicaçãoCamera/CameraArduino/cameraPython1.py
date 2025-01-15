#Nesse código há a importação de três bibliotecas: opencv-python,mediapipe e cvzone.
#Há a criação de uma nova janela, no qual é possivel ver o reconhecimento da mão.
#para fechar a janela, basta clicar na tecla 'q'


import cv2
import cvzone
from cvzone.HandTrackingModule import HandDetector
from cvzone.SerialModule import SerialObject
import mediapipe as mp



cap = cv2.VideoCapture(0) #pega a imagem da webcam
detector = HandDetector(detectionCon=0.8,maxHands=1) #reconhece quantas mão há
mySerial=SerialObject("COM5",9600,1) #define porta usb usada, baudrate e quantos bits transmite 
while True:
    sucess,img=cap.read()
    hands, img = detector.findHands(img)     #reconhece a mão
    if hands:                                #define parametros da mão(posição na tela,dedos, qual mão)
        hand1=hands[0]
        fingers1=detector.fingersUp(hand1)   #detecta se dedo está levantado(1) ou abaixado(0) criando array
        mySerial.sendData(fingers1)          #envia o array para a porta selecionada pelo porta serial(comunicação arduino)


        print(fingers1)

    cv2.imshow('frame', img)                 #mostra imagem na tela em nova janela
    if cv2.waitKey(1) == ord('q'):           #fechar a janela da imagem, apertar tecla 'q'
       break
cap.release()
cv2.destroyAllWindows() 
