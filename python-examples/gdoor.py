#!/usr/bin/python

from __future__ import print_function

import requests

device = 'dddddddddddddddddddddddd'

authorization = {
    'Authorization': 'Bearer aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa',
}

def getgdstatus(device_id, auth_id):

  data = {
    'arg': 'gdstatustest'
  }

  response = requests.get('https://api.particle.io/v1/devices/' + device_id + '/gdoorstatus', headers=auth_id, data=data)

  return response



def closegdoor(device_id, auth_id):

  data = {
    'arg': 'closegdoortest'
  }

  response = requests.post('https://api.particle.io/v1/devices/' + device_id + '/closegdoor', headers=auth_id, data=data)

  return response


def setgdclosed(device_id, auth_id):
  data = {
    'arg': 'py-gdclosedtest'
  }

  response = requests.post('https://api.particle.io/v1/devices/' + device_id + '/setgdclosed', headers=auth_id, data=data)

  return response

def setgdopen(device_id, auth_id):

  data = {
    'arg': 'py-gdopentest'
  }

  response = requests.post('https://api.particle.io/v1/devices/' + device_id + '/setgdopen', headers=auth_id, data=data)

  return response

print("\nsetting garage door status to open")
r = setgdopen(device, authorization)
print(r.status_code)
print(r.text)
r = getgdstatus(device, authorization)
print(r.status_code)
print(r.text)

print("\nsetting garage door status to closed")
r = setgdclosed(device, authorization)
print(r.status_code)
print(r.text)
r = getgdstatus(device, authorization)
print(r.status_code)
print(r.text)

print("\nclosing garage door")
r = closegdoor(device, authorization)
print(r.status_code)
print(r.text)
r = getgdstatus(device, authorization)
print(r.status_code)
print(r.text)

