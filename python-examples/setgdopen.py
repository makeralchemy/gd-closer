#!/usr/bin/python
import requests

headers = {
    'Authorization': 'Bearer aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa',
}

data = {
  'arg': 'gdopentest'
}

response = requests.post('https://api.particle.io/v1/devices/dddddddddddddddddddddddd/setgdopen', headers=headers, data=data)

print(response.status_code)
print(response.text)
