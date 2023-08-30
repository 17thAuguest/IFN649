import serial
import time
import string
import paho.mqtt.client as mqtt
import paho.mqtt.publish as publish
import threading

def on_connect(client, userdata, flags, rc): # func for making connection
    print("Connected to MQTT")
    print("Connection returned result: " + str(rc) )
    client.subscribe("ifn649/downstream")
def on_message(client, userdata, msg): # Func for Sending msg
    print(msg.topic+" "+str(msg.payload))
    ser.write(msg.payload)
ser = serial.Serial("/dev/rfcomm0", 9600)
client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message
client.connect("3.106.55.166", 1883, 60)

#threading target function
def read_and_publish(client):
    while True:
        time.sleep(0.5)
        bluetooth_msg = ser.readline()
        publish.single("ifn649/upstream", bluetooth_msg, hostname="3.106.55.166")
serial_thread = threading.Thread(target=read_and_publish, args=(client,))
serial_thread.start()

client.loop_forever()
