#!/usr/bin/python
import requests

headers = {
    'Authorization': 'Bearer aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa',
}

data = {
  'arg': 'gdclosedtest'
}

response = requests.post('https://api.particle.io/v1/devices/dddddddddddddddddddddddd/setgdclosed', headers=headers, data=data)

print response.status_code
print response.text



