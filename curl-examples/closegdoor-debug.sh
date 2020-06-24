#!/bin/bash
curl -X POST -H "Authorization: Bearer aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa" \
  https://api.particle.io/v1/devices/dddddddddddddddddddddddd/closegdoor \
  -d arg=closegdoortest --trace-ascii foo.txt



