import serial # necessaire pour communiquer entre l'arduino et l'ordinateur
import time # necessaire pour l'utilisation de la fonction sleep (équivalente à un delay sous arduino)
import pyautogui # c'est la librairie qui possède 

ArduinoSerial = serial.Serial('/dev/cu.usbmodem14302',9600) #Crée un port série 
time.sleep(2) # suspend le programme python pour s'assurer que la communication avec l'arduino soit bien mise en place

while 1: # on ecoute sans arret le programme arduino
    incoming = str(ArduinoSerial.readline()) # lit une ligne de la sortie standard du programme arduino
    print(incoming) # nous permet de voir ce que recoit le programme python

# si on rentre dans ce if, c'est que le geste PLAY/PAUSE vient d'être réalisé
 
    if 'PLAY/PAUSE' in incoming:
        pyautogui.press('space') # simule une pression sur la touche espace


# idem pour l'avancement dans la lecture     
    if 'REWIND' in incoming:
        pyautogui.press('left')
    if 'FORWARD' in incoming:
        pyautogui.press('right')
 
# idem pour le réglage du son
    if 'SON++' in incoming:
        pyautogui.press('up')
    if 'SON--' in incoming:
        pyautogui.press('down')

    
