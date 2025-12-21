import paho.mqtt.client as mqtt
import time
import os
import mariadb
from datetime import datetime

# Configuration MQTT
MQTT_BROKER = "localhost"
MQTT_PORT = 1883
TOPIC_IMAGE = "ProjetNichoir/image"
TOPIC_BATTERY = "ProjetNichoir/battery"
TOPIC_INFO = "ProjetNichoir/info"

IMAGES_FOLDER = "images"
if not os.path.exists(IMAGES_FOLDER):
    os.makedirs(IMAGES_FOLDER)

# --- Variables ---
receiving_image = False
image_data = bytearray()
expected_size = 0
image_counter = 0
last_battery = None  # stocke le dernier niveau de batterie reçu

# --- Connexion MariaDB ---
try:
    db_conn = mariadb.connect(
        user="ProjetNichoir",          # ton user MariaDB
        password="12345678",
        host="localhost",
        port=3306,
        database="ProjetNichoir"
    )
    db_cursor = db_conn.cursor()
except mariadb.Error as e:
    print(f"Erreur DB : {e}")
    exit()

# --- Callbacks MQTT ---
def on_connect(client, userdata, flags, rc):
    print("Connecté au broker MQTT avec le code : " + str(rc))
    client.subscribe(TOPIC_INFO)
    client.subscribe(TOPIC_BATTERY)
    client.subscribe(TOPIC_IMAGE)

def on_message(client, userdata, msg):
    global receiving_image, image_data, expected_size, image_counter, last_battery

    if msg.topic == TOPIC_INFO:
        payload_str = msg.payload.decode()
        if payload_str.startswith("START:"):
            try:
                expected_size = int(payload_str.split(":")[1])
                image_data = bytearray()
                receiving_image = True
                print(f"--- Nouvelle image. Taille attendue : {expected_size} octets ---")
            except ValueError:
                print("Erreur: START mal formé.")
        elif payload_str == "END" and receiving_image:
            receiving_image = False
            if len(image_data) == expected_size and len(image_data) > 0:
                image_counter += 1
                filename = os.path.join(IMAGES_FOLDER, f"capture_{image_counter}_{int(time.time())}.jpg")
                # Sauvegarde fichier
                try:
                    with open(filename, "wb") as f:
                        f.write(image_data)
                    print(f"Image enregistrée : {filename} (Taille réelle: {len(image_data)} octets)")
                                            
                    db_cursor.execute(
                                "INSERT INTO Capture (chemin_image, date_capture, taille_image, batterie, resolution, favoris) "
                                "VALUES (?, ?, ?, ?, ?, ?)",
                                (filename, datetime.now(), len(image_data), last_battery if last_battery is not None else 0, "2MP", 0)
                            )
                    db_conn.commit()


                    print("Enregistré dans la DB.")
                except Exception as e:
                    print(f"Erreur enregistrement fichier ou DB : {e}")
            else:
                print(f"Taille reçue ({len(image_data)}) != attendue ({expected_size}). Ignorée.")
                if len(image_data) > 0:
                    with open("debug_partial.bin", "wb") as f:
                        f.write(image_data)

    elif msg.topic == TOPIC_IMAGE and receiving_image:
        image_data.extend(msg.payload)

    elif msg.topic == TOPIC_BATTERY:
        try:
            last_battery = int(msg.payload.decode())
            print(f"Niveau batterie reçu : {last_battery}%")
        except ValueError:
            print("Erreur: valeur batterie invalide.")

# --- Client MQTT ---
client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

print(f"Tentative de connexion au broker {MQTT_BROKER}:{MQTT_PORT}...")
try:
    client.connect(MQTT_BROKER, MQTT_PORT, 60)
except Exception as e:
    print(f"Impossible de se connecter au broker MQTT. Erreur: {e}")
    exit()

client.loop_forever()
