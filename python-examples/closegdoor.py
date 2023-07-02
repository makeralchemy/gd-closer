#!/usr/bin/python
import requests

headers = {
    'Authorization': 'Bearer aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa',
}

data = {
  'arg': 'closegdoortest'
}

response = requests.post('https://api.particle.io/v1/devices/dddddddddddddddddddddddd/closegdoor', headers=headers, data=data)

print(response.status_code)
print(response.text)


