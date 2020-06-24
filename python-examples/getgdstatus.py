#!/usr/bin/python

# GET /v1/devices/{DEVICE_ID}/{VARIABLE}

import requests

headers = {
    'Authorization': 'Bearer aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa',
}

data = {
  'arg': 'gdclosedtest'
}

response = requests.get('https://api.particle.io/v1/devices/dddddddddddddddddddddddd/gdoorstatus', headers=headers, data=data)

print response.status_code
print response.text



