# python3.6

import os, random
from paho.mqtt import client as mqtt_client
from playsound import playsound

  

broker = '192.168.0.14'
port = 1883
topic = "livingroom/barkbox"
# generate client ID with pub prefix randomly
client_id = f'python-mqtt-{random.randint(0, 100)}'


def connect_mqtt() -> mqtt_client:
    def on_connect(client, userdata, flags, rc):
        if rc == 0:
            print("Connected to MQTT Broker!")
        else:
            print("Failed to connect, return code %d\n", rc)

    client = mqtt_client.Client(client_id)
#   client.username_pw_set(username, password)
    client.on_connect = on_connect
    client.connect(broker, port)
    return client


def subscribe(client: mqtt_client):
    def on_message(client, userdata, msg):
        print(f"Received `{msg.payload.decode()}` from `{msg.topic}` topic")
        audiofile = os.path.dirname(__file__) + "/audio/" + random_soundfile() 
        print(f"Playing audio file `{audiofile}`")
        playsound(audiofile)

    client.subscribe(topic)
    client.on_message = on_message

def random_soundfile():
    dirname = os.path.dirname(__file__)
    fulldir = os.path.join(dirname, 'audio')
    return random.choice(os.listdir(fulldir))

def run():
    client = connect_mqtt()
    subscribe(client)
    client.loop_forever()


if __name__ == '__main__':
    run()

